//=============================================================================
/*!	@file	joinClientChecker.h

	@brief	クライアント追加確認

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "utility/utility.h"
#include "general.h"

#include "joinClientChecker.h"

#include "gameDef.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace network {

//--------------------------------JoinClientChecker::PacketSendThread--------------------------------

	
//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
JoinClientChecker::PacketSendThread::PacketSendThread()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
JoinClientChecker::PacketSendThread::~PacketSendThread()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void JoinClientChecker::PacketSendThread::_Init( void )
{
	m_sendNum		= DEFAULT_SEND_NUM;
	m_sendInterval	= DEFAULT_SEND_INTERVAL_MILLISEC;

	m_sendInfos.reserve( 128 );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void JoinClientChecker::PacketSendThread::_Term( void )
{
	_DeleteSockets();
}

//===========================================================================
/*!	@brief		パケット設定
	@param		packet		設定パケット
	@return		----
*/
//===========================================================================
void JoinClientChecker::PacketSendThread::AddSendSocket(
	nk::net::IPAddress				ipAddress,
	u32								port,
	const Packet_FindHostToClient&	packet
)
{
	PRINTF("JoinClientChecker::PacketSendThread::AddSendSocket start\n");

	// 設定
	{
		SendInfo	addInfo;
		
		SCOPE_CRITICAL_SECTION( m_criticalSection );

		nk::net::IPAddressStr	clientAddressStr;
		nk::net::IPAddressToIPAddressStr( &clientAddressStr, ipAddress );

		addInfo.sendCount	= 0;
		addInfo.sendSocket.CreateUDP( clientAddressStr.ipAddress, port );
		addInfo.sendPacket	= packet;

		m_sendInfos.push_back( addInfo );
	}

	Thread::Setup( THREAD_PRIORITY_NORMAL, 0, "JoinClientChecker::PacketSendThread::AddSendSocket" );

	PRINTF("JoinClientChecker::PacketSendThread::AddSendSocket end\n");
}
	
//===========================================================================
/*!	@brief		ソケット削除
	@param		----
	@return		----
*/
//===========================================================================
void JoinClientChecker::PacketSendThread::_DeleteSockets( void )
{
	for( u32 i = 0; i < m_sendInfos.size(); ++i ) {
		m_sendInfos[i].sendSocket.Close();
	}
	m_sendInfos.clear();
	
}

//===========================================================================
/*!	@brief		スレッド処理
	@param		----
	@return		----
*/
//===========================================================================
void JoinClientChecker::PacketSendThread::ThreadFunc( void )
{
	PRINTF("JoinClientChecker::PacketSendThread::ThreadFunc start\n");
	
	while( 1 ) {
		{
			SCOPE_CRITICAL_SECTION( m_criticalSection );

			VecSendInfo::iterator	itr	= m_sendInfos.begin();
			for( ; itr != m_sendInfos.end(); ) {

				(*itr).sendSocket.Send( &(*itr).sendPacket, sizeof((*itr).sendPacket) );

				(*itr).sendCount++;
				
				if( m_sendNum <= (*itr).sendCount ) {
					(*itr).sendSocket.Close();
					itr	= m_sendInfos.erase( itr );					
				}
				else {
					++itr;
				}
				nk::SleepThread( m_sendInterval );
			}
		}

		// 停止
		nk::SleepThread( m_sendInterval );
	}

	PRINTF("JoinClientChecker::PacketSendThread::ThreadFunc end\n");
}


//===========================================================================
/*!	@brief		オプション設定
	@param		sendNum				送信回数
	@param		intervalMilliSec	送信間隔
	@return		----
*/
//===========================================================================
void JoinClientChecker::PacketSendThread::SetOption( s32 sendNum, s32 intervalMilliSec )
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	m_sendNum		= sendNum;
	m_sendInterval	= intervalMilliSec;
}

//--------------------------------JoinClientChecker--------------------------------



	
//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
JoinClientChecker::JoinClientChecker()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
JoinClientChecker::~JoinClientChecker()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void JoinClientChecker::_Init( void )
{
	m_callbackReceive	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void JoinClientChecker::_Term( void )
{

}

//===========================================================================
/*!	@brief		セットアップ
	@param		----
	@return		----
*/
//===========================================================================
bool JoinClientChecker::Setup( void )
{
	PRINTF("JoinClientChecker::Setup start\n");

	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	if( Thread::Running() ) {
		return false;
	}
	
	m_receiveCheckSocket.CreateUDP( NULL, PORT_FIND_HOST_CLIENT_TO_SERVER );
	m_receiver.AddReceiveScoket( m_receiveCheckSocket, this );

	// スレッド設定
	m_sendThread.Setup( THREAD_PRIORITY_NORMAL, 0, "JoinClientChecker::m_sendThread" );
	m_sendThread.Start();

	// 待機
	Thread::Setup( THREAD_PRIORITY_NORMAL, 0, "JoinClientChecker::Setup" );
	Thread::Start();

	PRINTF("JoinClientChecker::Setup end\n");

	return true;
}

//===========================================================================
/*!	@brief		クローズ
	@param		----
	@return		----
*/
//===========================================================================
void JoinClientChecker::Close( void )
{
	PRINTF("JoinClientChecker::Close start\n");

	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	Thread::Cancel();
	m_sendThread.Cancel();
	
	m_receiver.Clear();
	m_receiveCheckSocket.Close();

	PRINTF("JoinClientChecker::Close end\n");
	
}

//===========================================================================
/*!	@brief		受信チェック
	@param		----
	@return		----
*/
//===========================================================================
bool JoinClientChecker::CheckReceive( void )
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	m_receiver.SetTimeout( 0, 1000 );
	bool	b	= m_receiver.ReceiveWait();
	
	return b;
}


//===========================================================================
/*!	@brief		スレッド処理
	@param		----
	@return		----
*/
//===========================================================================
void JoinClientChecker::ThreadFunc( void )
{
	PRINTF("JoinClientChecker::ThreadFunc start\n");
	
	while( 1 ) {
		
		CheckReceive();
		
		nk::SleepThread( 1 );
	}

	Close();

	PRINTF("JoinClientChecker::ThreadFunc end\n");
}

//===========================================================================
/*!	@brief		受信
	@param		----
	@return		----
*/
//===========================================================================
void JoinClientChecker::Receive( void* packet, u32 packetSize )
{
	PRINTF("JoinClientChecker::Receive start\n");

	Packet_FindClientToHost*	receivePacket	= static_cast<Packet_FindClientToHost*>( packet );
	PRINTF("packet.str = %s\n", receivePacket->str);

	// クライアントに通知
	{
		nk::net::IPAddress				ipAddress;
		nk::net::AdapterInfo			ownInfo;

		bool	result		= true;
		s32		adapterNo	= 0;
		do {
			result	= GetAdapterInfo( &ownInfo, adapterNo );
			if( result ) {
				nk::net::IPAddressStrToIPAddress( &ipAddress, ownInfo.ipAddress );

				Packet_FindHostToClient	sendPacket;
				sendPacket.ipAddress	= ipAddress;
				strcpy_s( sendPacket.roomName, sizeof(sendPacket.roomName), "room name" );
				strcpy_s( sendPacket.hostName, sizeof(sendPacket.hostName), "host name" );
				
				nk::net::IPAddress			clientIP	= GetIPAddress();
				{
					SCOPE_CRITICAL_SECTION( m_criticalSection );
					
					(*m_callbackReceive)( clientIP );
					m_sendThread.AddSendSocket( clientIP, PORT_FIND_HOST_SERVER_TO_CLIENT, sendPacket );
				}
				++adapterNo;
			}
		} while( result );
		
	}

	PRINTF("JoinClientChecker::Receive end\n");
}
	
	
}	// namespace network

