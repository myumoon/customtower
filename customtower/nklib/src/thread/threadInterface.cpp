//=============================================================================
/*!	@file	threadInterface.h

	@brief	スレッドクラス

	@author	ryunosuke ide
	@date	2013.03.06
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/thread/threadInterface.h"
#include "../../include/utility/utility.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {


}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {

// スレッドコールバック
u32 Thread::_ThreadCallback( void* param )
{
	nk::Thread*	thread	= reinterpret_cast<nk::Thread*>(param);
	thread->ThreadCallback();
	//thread->ThreadFunc();

	return 0;
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Thread::Thread()
{
	_Init();
}



//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Thread::~Thread()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Thread::_Init()
{
	m_status	= STATUS_NOT_INITIALIZED;
	m_created	= false;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Thread::_Term()
{
	if( m_created ) {
// 		Pause();
		Cancel();
		Join();
	}
}

//===========================================================================
/*!	@brief	スレッドコールバック
	@param	----
*/
//===========================================================================
void Thread::ThreadCallback( void )
{

	this->ThreadFunc();
	m_status	= STATUS_EXIT;
	m_created	= false;

	printf("Thread::ThreadCallback end\n");
}

//===========================================================================
/*!	@brief	セットアップ
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Setup( u32 priority, u32 stackSize, const char* name )
{
	if( m_created == false ) {
		m_handle	= nk::CreateThread( _ThreadCallback, this, priority, stackSize, name );
		m_created	= true;
		m_status	= Thread::STATUS_NOT_INITIALIZED;
	}

}

//===========================================================================
/*!	@brief	開始
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Start( void )
{
	bool	startableStatus	= (GetStatus() == Thread::STATUS_NOT_INITIALIZED) || (GetStatus() == Thread::STATUS_PAUSE);
	if( m_created && startableStatus ) {
		const u32	tempStatus	= m_status;
		m_status	= STATUS_RUN;
		
		if( tempStatus == STATUS_PAUSE ) {
			ResumeThread( m_handle );
		}
		else {
			StartThread( m_handle );
		}
	}
	
	
}



//===========================================================================
/*!	@brief	停止
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Pause( void )
{
	if( m_created && (m_status == Thread::STATUS_RUN) ) {
		m_status	= STATUS_PAUSE;
		SuspendThread( m_handle );
	}
}



//===========================================================================
/*!	@brief	終了
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Cancel( void )
{
	if( m_created && (m_status == Thread::STATUS_RUN) ) {
		m_status	= STATUS_CANCEL;
		//DestroyThread( m_handle );
	}
	//m_created	= false;
	
}



//===========================================================================
/*!	@brief	ステータスの取得
	@param	----
	@return	ステータス
*/
//===========================================================================
u32 Thread::GetStatus( void ) const
{

	return m_status;
}

//===========================================================================
/*!	@brief	実行中ならtrueを返す
	@param	----
*/
//===========================================================================
bool Thread::Running( void ) const
{

	return (GetStatus() == STATUS_RUN);
}


//===========================================================================
/*!	@brief		待機
	@param		----
	@return		----
*/
//===========================================================================
void Thread::Join( void )
{
	JoinThread( m_handle );
}


//===========================================================================
/*!	@brief		キャンセルならtrueを返す
	@param		----
	@return		----
*/
//===========================================================================
bool Thread::IsCancel( void ) const
{
	
	return m_status == STATUS_CANCEL;
}
	
}	// namespace nk