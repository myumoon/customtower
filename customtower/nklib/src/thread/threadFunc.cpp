//=============================================================================
/*!	@file	threadFunc.cpp


	@brief	スレッド

	@author	ryunosuke ide
	@date	2012.09.08
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/thread/threadFunc.h"
#include "../../include/general.h"
#include "../../include/utility/utility.h"
#include <SDL/SDL.h>

//--------------------------------define定義--------------------------------




//--------------------------------static変数--------------------------------
namespace {


// スレッドデータ
struct _ThreadData {
	bool					validData;		//!< 有効？
	nk::THREAD_HANDLE		handle;			//!< スレッドハンドル
	nk::THREAD_ID			id;				//!< スレッドID
	nk::THREAD_FUNC			func;			//!< 関数
	void*					argument;		//!< スレッド引数
	nk::THREAD_STATE		prevState;		//!< 前の状態
	nk::THREAD_STATE		nowState;		//!< スレッドの状態
	s64						createdTime;	//!< 生成時間
#if defined(_DEBUG)
	char					name[128];		//!< スレッド名
#endif

	_ThreadData()
	{
		this->validData		= false;
		this->handle		= 0;
		this->id			= 0;
		this->createdTime	= 0;
#if defined(_DEBUG)
		memset( name, 0, sizeof(name) );
#endif
	}

	~_ThreadData()
	{
#if defined(_DEBUG)
		printf("DeleteThread : name = %s\n", name);
#endif
	}

	bool Initialized( void ) const
	{
		return this->validData == true;
	}

	bool operator ==( nk::THREAD_HANDLE handle )
	{
		if( this->handle == handle ) {
			return true;
		}
		return false;
	}
};

	
// 生成したスレッドを管理
class _ThreadManager {
public:
	_ThreadManager()
	{
		m_vecThread.reserve( 256 );
	}

	void Add( _ThreadData* data )
	{
		data->validData	= data->handle != 0;
		m_vecThread.push_back( data );
	}

	_ThreadData& GetData( nk::THREAD_HANDLE handle )
	{
		std::vector<_ThreadData*>::iterator	itr	= m_vecThread.begin();
		std::vector<_ThreadData*>::iterator	end	= m_vecThread.end();
		for( ; itr != end; ++itr ) {
			if( (*itr)->handle == handle ) {
				return *(*itr);
			}
		}

		return m_dummy;
	}


	_ThreadData& GetData( u32 idx )
	{
		ASSERT( idx < m_vecThread.size(), "index over." );
		return *m_vecThread[idx];
	}

	u32 GetSize() const
	{
		return m_vecThread.size();
	}
	

	void Remove( nk::THREAD_HANDLE handle )
	{
		std::vector<_ThreadData*>::iterator	itr	= m_vecThread.begin();
		std::vector<_ThreadData*>::iterator	end	= m_vecThread.end();
		for( ; itr != end; ++itr ) {
			if( (*itr)->handle == handle ) {
				nk::SafeDelete( *itr );
				break;
			}
		}
		m_vecThread.erase( itr );
	}

	void Destroy( void )
	{
		std::vector<_ThreadData*>::iterator	itr	= m_vecThread.begin();
		std::vector<_ThreadData*>::iterator	end	= m_vecThread.end();
		for( ; itr != end; ++itr ) {
			nk::SafeDelete( *itr );
		}
	}
	
private:
	std::vector<_ThreadData*>		m_vecThread;	// 管理スレッド
	_ThreadData						m_dummy;		// 失敗時ダミー
};

_ThreadManager*		_threadManager	= NULL;			// スレッド管理
	
}	// unnamed



//--------------------------------static関数--------------------------------
namespace {

_ThreadManager* _GetThreadMng( void )
{
	ASSERT( _threadManager != NULL, "thread not initialized.\n" );
	
	return _threadManager;
}

#if !defined(_WIN32)
// ポインタ -> ハンドル
inline nk::THREAD_HANDLE _GetThreadHandle( void* p )
{
	
	return reinterpret_cast<u32>( p );
}


// スレッドハンドル -> ポインタ
inline SDL_Thread*	_GetThreadPointer( nk::THREAD_HANDLE handle )
{
	
	return reinterpret_cast<SDL_Thread*>( handle );
}


// ポインタ -> ハンドル
inline nk::THREAD_HANDLE _GetMutexHandle( void* p )
{
	
	return reinterpret_cast<u32>( p );
}

// ミューテックスハンドル -> ポインタ
inline SDL_mutex*	_GetMutexPointer( nk::MUTEX_HANDLE handle )
{
	
	return reinterpret_cast<SDL_mutex*>( handle );
}
#else
#endif



#if defined(_WIN32)
u32 __stdcall _ThreadCallback( void* param )
{
	_ThreadData*	threadData	= static_cast<_ThreadData*>( param );
	(*threadData->func)( threadData->argument );
	
	_GetThreadMng()->Remove( threadData->handle );

	return 0;
}
	
#else
s32 _ThreadCallback( void* param )
{
	nk::ThreadData*	threadData	= static_cast<nk::ThreadData*>( param );
	(*threadData->func)( threadData->argument );

	_GetThreadMng()->Remove( threadData->handle );

	return 0;
}
#endif


}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void InitializeThread( void )
{
	if( _threadManager == NULL ) {
		_threadManager	= new _ThreadManager();
	}
}



//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void FinalizeThread( void )
{
	for( u32 i = 0; i < _GetThreadMng()->GetSize(); ++i ) {
		_ThreadData&	thread	= _GetThreadMng()->GetData( i );
#if defined(_WIN32)
		::CloseHandle( thread.handle );
#else
#endif		
	}

	// メモリ解放
	_GetThreadMng()->Destroy();
	
}
	
	

//===========================================================================
/*!	@brief	スレッド生成
	@param	func		呼び出し関数
	@param	arg			スレッド関数引数
	@param	priority	優先度
	@param	stackSize	スタックサイズ(デフォルト0)
	@return	true.生成成功	false.生成失敗
*/
//===========================================================================
THREAD_HANDLE CreateThread( THREAD_FUNC func, void* arg, s32 priority, u32 stackSize, const char* name )
{
	_ThreadData	*threadData	= new _ThreadData();

	threadData->prevState	= THREAD_STATE_SUSPEND; 
	threadData->nowState	= THREAD_STATE_SUSPEND;
	threadData->func		= func;
	threadData->argument 	= arg;
	threadData->createdTime	= GetTimeMillSec();

#if defined(_DEBUG)
	strcpy_s( threadData->name, name );
	printf("CreateThread : name = %s\n", name);
#endif


#if defined(_WIN32)
	threadData->handle	= (HANDLE)_beginthreadex(
		NULL,
        stackSize,
		_ThreadCallback,
        threadData,
        CREATE_SUSPENDED,
        (u32*)&threadData->id
	);
	threadData->handle		= ::OpenThread( SYNCHRONIZE | STANDARD_RIGHTS_REQUIRED | THREAD_SUSPEND_RESUME | THREAD_SET_INFORMATION, TRUE, threadData->id );
#else
	(void*)priority;
	(void*)stackSize;
	
	SDL_Thread*	thread		= SDL_CreateThread( func, threadData );
	threadData.handle		= _GetThreadHandle( thread );
#endif
	
    if( threadData->handle == 0 ) {
        PRINTF("error : create thread\n");
        return false;
    }

#if defined(_WIN32)
	::SetThreadPriority( threadData->handle, priority );
#else
	// SDLは優先度設定無し
#endif

	_GetThreadMng()->Add( threadData );
	
	
	return threadData->handle;
}


//===========================================================================
/*!	@brief	スレッド終了
	@param	handle	終了するスレッドハンドル
	@return	----
*/
//===========================================================================
void DestroyThread( THREAD_HANDLE handle )
{
	_ThreadData&	thread	= _GetThreadMng()->GetData( handle );
	ASSERT( thread.validData == true, "invalid thread." );


#if defined(_WIN32)
	::CloseHandle( (HANDLE)thread.handle );
#else
	SDL_KillThread( _GetThreadPointer(handle) );
#endif

	_GetThreadMng()->Remove( handle );

}


//===========================================================================
/*!	@brief	スレッド開始
	@param	handle	開始するスレッドハンドル
	@return	----
*/
//===========================================================================
void StartThread( THREAD_HANDLE handle )
{
	_ThreadData&	thread	= _GetThreadMng()->GetData( handle );
	ASSERT( thread.validData == true, "invalid thread." );
	
	thread.prevState	= thread.nowState;
	thread.nowState		= THREAD_STATE_START;
	thread.createdTime	= GetTimeMillSec();

#if defined(_WIN32)
	::ResumeThread( handle );
#else
	// TODO
#endif

}



//===========================================================================
/*!	@brief	スレッド中断
	@param	handle	中断するスレッドハンドル
	@return	----
*/
//===========================================================================
void SuspendThread( THREAD_HANDLE handle )
{
	_ThreadData&	thread	= _GetThreadMng()->GetData( handle );
	ASSERT( thread.validData == true, "invalid thread." );

	thread.prevState	= thread.nowState;
	thread.nowState		= THREAD_STATE_SUSPEND;
	
#if defined(_WIN32)
	const s64	THREAD_LIFE_TIME	= 5;
	const s64	nowTime				= GetTimeMillSec();
	if( nowTime < thread.createdTime + THREAD_LIFE_TIME ) {
		nk::SleepThread( thread.createdTime + THREAD_LIFE_TIME - nowTime );
	}
	::SuspendThread( (HANDLE)thread.handle );
#else
	// TODO
#endif
	
	
}


//===========================================================================
/*!	@brief	スレッド再開
	@param	handle	再開するスレッドハンドル
	@return	----
*/
//===========================================================================
void ResumeThread( THREAD_HANDLE handle )
{
	_ThreadData&	thread	= _GetThreadMng()->GetData( handle );
	ASSERT( thread.validData == true, "invalid thread." );

	thread.prevState	= thread.nowState;
	thread.nowState		= THREAD_STATE_START;
	
#if defined(_WIN32)
	::ResumeThread( (HANDLE)thread.handle );
#else
	// TODO
#endif
	

}



//===========================================================================
/*!	@brief		スレッド待ち
	@param		handle	待つスレッド
	@return		----
*/
//===========================================================================
void JoinThread( THREAD_HANDLE handle )
{
	_ThreadData&	thread	= _GetThreadMng()->GetData( handle );
	ASSERT( thread.validData == true, "invalid thread." );

#if defined(_WIN32)
	::WaitForSingleObject( thread.handle, INFINITE );
#else
	// TODO
#endif
}


	
//===========================================================================
/*!	@brief	ミューテックスの作成
	@param	----
	@return	----
*/
//===========================================================================
MUTEX_HANDLE CreateMutexObject( void )
{
	MUTEX_HANDLE	retMutex;

#if defined(_WIN32)
    retMutex	= ::CreateMutex( NULL, FALSE, "Mutex" );
	//retMutex	= ::CreateMutex( NULL, TRUE, "Mutex" );
	NULL_ASSERT( retMutex );
#else
	SDL_mutex*	mutex	= SDL_CreateMutex();
	retMutex	= _GetMutexHandle( mutex );
#endif

	
	return retMutex;
}



//===========================================================================
/*!	@brief	ミューテックスの作成
	@param	停止するミューテックスのハンドル
	@return	----
*/
//===========================================================================
void DeleteMutexObject( MUTEX_HANDLE handle )
{
#if defined(_WIN32)	
	NULL_ASSERT( handle );

	::CloseHandle( handle );
	
#else
	SDL_DestroyMutex( _GetMutexPointer(handle) );
	
#endif
	
}



//===========================================================================
/*!	@brief	ミューテックスのロック
	@param	handle	ミューテックスハンドル
	@return	----
*/
//===========================================================================
bool LockMutex( MUTEX_HANDLE handle )
{
#if defined(_WIN32)
	DWORD	result	= ::WaitForSingleObject( handle, INFINITE );

	if( result == WAIT_FAILED ) {
		return false;
	}

#else
	if( SDL_mutexP( _GetMutexPointer(handle) ) < 0 ) {
		return false;
	}
#endif
	
	return true;
}


//===========================================================================
/*!	@brief	ミューテックスのアンロック
	@param	handle	ミューテックスハンドル
	@return	----
*/
//===========================================================================
bool UnlockMutex( MUTEX_HANDLE handle )
{
	
#if defined(_WIN32)
	BOOL	result	= ::ReleaseMutex( handle );
	if( result == 0 ) {
		return false;
	}

#else
	if( SDL_mutexV( _GetMutexPointer(handle) ) < 0 ) {
		return false;
	}
#endif
	
	return true;
}


//===========================================================================
/*!	@brief		クリティカルセクションの作成
	@param		----
	@return		----
*/
//===========================================================================
CRITICAL_SECTION_HANDLE CreateCriticalSection( void )
{
#if defined(_WIN32)
	//::InitializeCriticalSection();
	LPCRITICAL_SECTION	retHandle	= new CRITICAL_SECTION;
	::InitializeCriticalSection( retHandle );
	
	return retHandle;
#else
	#error
#endif
}



//===========================================================================
/*!	@brief		クリティカルセクションの削除
	@param		handle	削除するクリティカルセクション
	@return		----
*/
//===========================================================================
void DeleteCriticalSection( CRITICAL_SECTION_HANDLE handle )
{
#if defined(_WIN32)
	::DeleteCriticalSection( handle );
	SafeDelete( handle );
	
#else
	#error
#endif
}


//===========================================================================
/*!	@brief		クリティカルセクションをロック
	@param		handle	クリティカルセクションハンドル
	@return		----
*/
//===========================================================================
void LockCriticalSection( CRITICAL_SECTION_HANDLE handle )
{
#if defined(_WIN32)
	::EnterCriticalSection( handle );
#else
	#error
#endif
}


//===========================================================================
/*!	@brief		クリティカルセクションをアンロック
	@param		handle	クリティカルセクションハンドル
	@return		----
*/
//===========================================================================
void UnlockCriticalSection( CRITICAL_SECTION_HANDLE handle )
{
#if defined(_WIN32)
	::LeaveCriticalSection( handle );
#else
	#error
#endif
}


#if 0
//===========================================================================
/*!	@brief	イベントオブジェクトの作成
	@param	manualReset		手動リセットon,off
	@param	initialState	初期状態
	@param	addEventList	追加するイベントリストのID(デフォルトで0)
	@return	生成したイベントオブジェクトのハンドル
*/
//===========================================================================
EVENT_HANDLE CreateEventObject( bool manualReset, bool initialState, HANDLE_CHUNK_ID addEventList )
{
	EVENT_HANDLE	retHandle;
	
    retHandle = ::CreateEvent(NULL, manualReset, initialState, NULL);
	
	NULL_ASSERT( retHandle );


	if( _vecHandleList.size() <= addEventList ) {
		_vecHandleList.resize( addEventList + 1 );
	}


	// リストに追加
	_vecHandleList[addEventList].handleList.push_back( retHandle );	

	
	return retHandle;
}



//===========================================================================
/*!	@brief	イベントオブジェクトの削除
	@param	handle	削除するイベントオブジェクトのハンドル
	@return	----
*/
//===========================================================================
void DeleteEventObject( EVENT_HANDLE handle )
{
	
	NULL_ASSERT( handle );

	::CloseHandle( handle );


	// リストから削除
	std::vector<_HandleChunk>::iterator itr1 = _vecHandleList.begin();
	
	for( ; itr1 != _vecHandleList.end(); ++itr1 ) {
		
		std::vector<HANDLE>::iterator itr2 = (*itr1).handleList.begin();
		
		for( ; itr2 < (*itr1).handleList.end(); ) {
			if( (*itr2) == handle ) {
				itr2 = (*itr1).handleList.erase( itr2 );
			} else {
				++itr2;
			}
		}
	}
	
	
	
}



//===========================================================================
/*!	@brief	全てのイベントがシグナル状態になるまで待つ
	@param	イベントリスト(デフォルトで0)
	@return	----
*/
//===========================================================================
bool WaitEvent( HANDLE_CHUNK_ID id )
{
	
	ASSERT( id < _vecHandleList.size(), "index error" );

	// 普通の配列にコピー
	for( u32 i = 0; i < _vecHandleList[id].handleList.size(); ++i ) {
		_tempHandleAry[i] = _vecHandleList[id].handleList[i];
	}
	

	// 待ち状態に変更
	for( u32 i = 0; i < _vecThreadData.size(); ++i ) {
		for( u32 j = 0; j < _vecHandleList[id].handleList.size(); ++j ) {
			if( _vecThreadData[i].handle == _vecHandleList[id].handleList[j] ) {
				_vecThreadData[i].prevState	= _vecThreadData[i].nowState;
				_vecThreadData[i].nowState	= eTHREAD_STATE_SUSPEND;
				break;
			}
		}
	}
	
	::WaitForMultipleObjects( _vecHandleList[id].handleList.size(), _tempHandleAry, TRUE, INFINITE);

	// もとの状態に変更
	for( u32 i = 0; i < _vecThreadData.size(); ++i ) {
		for( u32 j = 0; j < _vecHandleList[id].handleList.size(); ++j ) {
			if( _vecThreadData[i].handle == _vecHandleList[id].handleList[j] ) {
				_vecThreadData[i].nowState = _vecThreadData[i].prevState;
				break;
			}
		}
	}

	return true;
}
#endif


//===========================================================================
/*!	@brief	全てのスレッドを停止させる
	@param	----
	@return	----
*/
//===========================================================================
void SuspendAllThread( void )
{
	for( u32 i = 0; i < _GetThreadMng()->GetSize(); ++i ) {
		_ThreadData&	thread	= _GetThreadMng()->GetData( i );

		if( thread.nowState != THREAD_STATE_SUSPEND ) {
			thread.prevState	= thread.nowState;
			thread.nowState		= THREAD_STATE_SUSPEND;
			
#if defined(_WIN32)
			::SuspendThread( thread.handle );
#else
			SDL_KillThread( _GetThreadPointer(thread.handle) );
#endif
		}
	}

}


//===========================================================================
/*!	@brief	全てのスレッドを以前の状態に戻す
	@param	----
	@return	----
*/
//===========================================================================
void ReturnAllThread( void )
{
	for( u32 i = 0; i < _GetThreadMng()->GetSize(); ++i ) {
		_ThreadData&	thread	= _GetThreadMng()->GetData( i );

		if( thread.nowState != thread.prevState ) {
#if defined(_WIN32)
			if( thread.nowState == THREAD_STATE_SUSPEND ) {
				::ResumeThread( thread.handle );
			}
			else if( thread.nowState == THREAD_STATE_START ) {
				::SuspendThread( thread.handle );
			}
#else
			// TODO
			//SDL_KillThread( _GetThreadPointer(thread.handle) );
#endif
		}

		thread.nowState		= thread.prevState;
		thread.prevState	= THREAD_STATE_WAIT;
	}

}


//===========================================================================
/*!	@brief	全てのスレッドを再開させる
	@param	----
	@return	----
*/
//===========================================================================
void ResumeAllThread( void )
{
	for( u32 i = 0; i < _GetThreadMng()->GetSize(); ++i ) {
		_ThreadData&	thread	= _GetThreadMng()->GetData( i );

		if( thread.nowState != THREAD_STATE_START ) {
			thread.prevState	= thread.nowState;
			thread.nowState		= THREAD_STATE_START;
			
#if defined(_WIN32)
			::ResumeThread( thread.handle );
#else
			// TODO
#endif
		}
	}
	
}


}	// namespace nk
