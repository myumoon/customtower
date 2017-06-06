//=============================================================================
/*!	@file	mutex.h

	@brief	ミューテックス

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/thread/mutex.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace nk {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Mutex::Mutex()
{
	m_copyCount	= 0;
	_Create();
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Mutex::Mutex( MUTEX_HANDLE handle )
{
	m_copyCount	= 1;
	m_handle	= handle;
}



//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Mutex::Mutex( const Mutex& mutex )
{
	_Copy( mutex );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Mutex::~Mutex()
{
	_Term();
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Mutex::_Term()
{
	if( m_copyCount == 0 ) {
		_Delete();
	}
}


//===========================================================================
/*!	@brief	コピー
	@param	----
	@return	----
*/
//===========================================================================
void Mutex::_Copy( const Mutex& mutex )
{
	m_copyCount	= mutex.m_copyCount + 1;
	m_handle	= mutex.m_handle;

}


//===========================================================================
/*!	@brief	コピー
	@param	----
	@return	----
*/
//===========================================================================
Mutex& Mutex::operator =( const Mutex& mutex )
{
	_Copy( mutex );

	return *this;
}



//===========================================================================
/*!	@brief	ロック
	@param	----
	@return	----
*/
//===========================================================================
void Mutex::Lock( void )
{

	nk::LockMutex( m_handle );
	
}


//===========================================================================
/*!	@brief	アンロック
	@param	----
	@return	----
*/
//===========================================================================
void Mutex::Unlock( void )
{

	nk::UnlockMutex( m_handle );
	
}


//===========================================================================
/*!	@brief	生成
	@param	----
	@return	----
*/
//===========================================================================
void Mutex::_Create( void )
{
	m_handle	= nk::CreateMutexObject();
	
}



//===========================================================================
/*!	@brief	削除
	@param	----
	@return	----
*/
//===========================================================================
void Mutex::_Delete( void )
{
	nk::DeleteMutexObject( m_handle );
	
}


}	// namespace nk

