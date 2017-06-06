//=============================================================================
/*!	@file	socketManager.h

	@brief	ソケット管理

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/net/socketManager.h"

#include <winsock2.h>
#include <windows.h>


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace nk {
namespace net {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
SocketManager::SocketManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
SocketManager::~SocketManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void SocketManager::_Init( void )
{

	m_initialized	= false;
	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void SocketManager::_Term( void )
{
	Finalize();
}

	
//===========================================================================
/*!	@brief		初期化
	@param		----
	@return		----
*/
//===========================================================================
void SocketManager::Initialize( void )
{
#if defined(_WIN32)
	WSADATA data;
	WSAStartup( MAKEWORD(2,0), &data );
#endif

	m_initialized	= true;
	
}



//===========================================================================
/*!	@brief		終了処理
	@param		----
	@return		----
*/
//===========================================================================
void SocketManager::Finalize( void )
{
#if defined(_WIN32)
	if( m_initialized ) {
		WSACleanup();
	}
#endif
	
}

	
}	// namespace net
}	// namespace nk
