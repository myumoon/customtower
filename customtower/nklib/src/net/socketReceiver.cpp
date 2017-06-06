//=============================================================================
/*!	@file	socketReceiver.h

	@brief	レシーバー

	@author	ryunosuke ide
	@date	2013.05.17
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/net/socketReceiver.h"
#include "../../include/utility/utility.h"
#include "../../include/net/packetReceiver.h"
#include "../../include/net/socket.h"


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
SocketReceiver::SocketReceiver()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
SocketReceiver::~SocketReceiver()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void SocketReceiver::_Init( void )
{
	m_maxID	= 0;

	FD_ZERO( &m_fd );
	memset( &m_timeout, 0, sizeof(m_timeout) );

	m_vecSocketInfo.clear();
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void SocketReceiver::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		----
	@return		----
*/
//===========================================================================
void SocketReceiver::Init( void )
{
	_Init();
}


//===========================================================================
/*!	@brief		受信確認
	@param		----
	@return		----
*/
//===========================================================================
bool SocketReceiver::ReceiveWait( void )
{
	fd_set	fds;	// チェック用
	memcpy( &fds, &m_fd, sizeof(m_fd) );
	
	s32	lasttime = 0;
	{
		if( (m_timeout.tv_sec == 0) && (m_timeout.tv_usec == 0) ) {
			lasttime	= select( m_maxID + 1, &fds, NULL, NULL, NULL );
		}
		else {
			lasttime	= select( m_maxID + 1, &fds, NULL, NULL, &m_timeout );
		}
	}

	// タイムアウト
	if( lasttime == 0 ) {
		return false;
	}

	{		
		for( u32 i = 0; i < m_vecSocketInfo.size(); ++i ) {
			if( FD_ISSET( m_vecSocketInfo[i].socket.GetID(), &fds ) ) {
								
				void*	buffer		= m_vecSocketInfo[i].receiver->GetBuffer();
				u32		bufferSize	= m_vecSocketInfo[i].receiver->GetBufferSize();
				
				memset( buffer, 0, bufferSize );
				Address		senderAddr;
				const SOCKET_RESULT	result	= m_vecSocketInfo[i].socket.Receive( buffer, bufferSize, &senderAddr );
				if( (result != SOCKET_RESULT_OK) && (result != SOCKET_RESULT_NONBLOCKING_WAIT) ) {
					printf("error : %d\n", WSAGetLastError());
				}
				m_vecSocketInfo[i].receiver->ReceiveCallback( m_vecSocketInfo[i].socket, buffer, bufferSize, senderAddr );
			}
		}
	}

	return true;
}

//===========================================================================
/*!	@brief		追加
	@param		socket		ソケット
	@param		receiver	受信クラス
	@return		----
*/
//===========================================================================
void SocketReceiver::AddReceiveScoket( const Socket& socket, PacketReceiver* receiver )
{
	
	FD_SET( socket.GetID(), &m_fd );

	m_vecSocketInfo.push_back( SocketInfo( socket, receiver) );
	//m_receivers.insert( std::pair<Socket::SocketID, PacketReceiver*>( socket.GetID(), receiver ) );

	if( m_maxID < socket.GetID() ) {
		m_maxID	= socket.GetID();
	}
}

//===========================================================================
/*!	@brief		タイムアウト設定
	@param		sec		秒 
	@param		micSec	マイクロ秒
	@return		----
*/
//===========================================================================
void SocketReceiver::SetTimeout( s32 sec, s32 micSec )
{
	
	m_timeout.tv_sec	= sec;
	m_timeout.tv_usec	= micSec;

}


//===========================================================================
/*!	@brief		クリア
	@param		----
	@return		----
*/
//===========================================================================
void SocketReceiver::Clear( void )
{
	_Init();
}

}	// namespace net
}	// namespace nk