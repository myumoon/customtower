//=============================================================================
/*!	@file	hostFinder.h

	@brief	ホスト検索

	@author	ryunosuke ide
	@date	2013.05.23
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "net/socketReceiver.h"
#include "utility/utility.h"
#include "general.h"

#include "hostFinder.h"
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

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
HostFinder::HostFinder()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
HostFinder::~HostFinder()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void HostFinder::_Init( void )
{
	m_initialized	= false;
	m_finished		= false;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void HostFinder::_Term( void )
{
	if( m_initialized ) {
		Close();
	}
}

//===========================================================================
/*!	@brief		セットアップ
	@param		----
	@return		----
*/
//===========================================================================
void HostFinder::Setup( void )
{
	printf("HostFinder::Setup start\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	// 送信ソケット作成
	{
		m_findSockets.clear();
		
		// ブロードキャストアドレス取得
		nk::net::IPAddressStr	ipStr;
		bool					result		= true;
		s32						adapterNo	= 0;

		do {
			result = nk::net::GetBroadcastAddressStr( &ipStr, adapterNo );
			if( result ) {
				nk::net::Socket	addSocket;
				addSocket.CreateUDP_Broadcast( ipStr.ipAddress, PORT_FIND_HOST_CLIENT_TO_SERVER );

				m_findSockets.push_back( addSocket );
				
				++adapterNo;
			}
		} while( result );

		m_sendPacket.port	= PORT_FIND_HOST_SERVER_TO_CLIENT;
		memset( m_sendPacket.str, 0, 128 );
		strcpy_s( m_sendPacket.str, 128, "hello world" );
	}

	// 受信ソケット作成
	{
		m_receiveSocket.CreateUDP( NULL, PORT_FIND_HOST_SERVER_TO_CLIENT );
		m_receiver.Init();
		m_receiver.AddReceiveScoket( m_receiveSocket, this );
	}

	

	// スレッド作成
	Thread::Setup( THREAD_PRIORITY_NORMAL, 0, "HostFinder::Setup" );

	m_initialized	= true;

	printf("HostFinder::Setup end\n");
}

//===========================================================================
/*!	@brief		クローズ
	@param		----
	@return		----
*/
//===========================================================================
void HostFinder::Close( void )
{
	printf("HostFinder::Close start\n");

	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	// ソケットを閉じる
	for( u32 i = 0; i < m_findSockets.size(); ++i ) {
		m_findSockets[i].Close();
	}	
	m_receiveSocket.Close();
	m_receiver.Clear();

	m_result.results.clear();
	m_initialized	= false;

	printf("HostFinder::Close end\n");
}


//===========================================================================
/*!	@brief		受信時コールバック追加
	@param		receiver	レシーバ
	@return		----
*/
//===========================================================================
void HostFinder::AddReceiver( SearchResultReceiver* receiver )
{
	printf("HostFinder::AddReceiver start\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	m_receiveCallbacks.push_back( receiver );

	printf("HostFinder::AddReceiver end\n");
}



//===========================================================================
/*!	@brief		受信時コールバック削除
	@param		receiver	レシーバ
	@return		----
*/
//===========================================================================
void HostFinder::RemoveReceiver( SearchResultReceiver* receiver )
{
	printf("HostFinder::RemoveReceiver start\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );

	std::vector<SearchResultReceiver*>::iterator	itr	= m_receiveCallbacks.begin();
	for( ; itr != m_receiveCallbacks.end(); ) {
		if( (*itr) == receiver ) {
			itr	= m_receiveCallbacks.erase( itr );
		}
		else {
			++itr;
		}
	}

	printf("HostFinder::RemoveReceiver end\n");
}


//===========================================================================
/*!	@brief		スレッド処理
	@param		----
	@return		----
*/
//===========================================================================
void HostFinder::ThreadFunc( void )
{
	printf("HostFinder::ThreadFunc start\n");
	bool	result		= false;
	u64		startTime	= nk::GetTimeMillSec();

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );
		m_result.Clear();
	}
	
	while( 1 ) {

		// ホストからのメッセージを受信
		{
			SCOPE_CRITICAL_SECTION( m_criticalSection );
			result	= _ReceiveMessageFromHost();
			//_ReceiveMessageFromHost();
		}

		if( DEFAULT_TIMEOUT_MILLISEC < nk::GetTimeMillSec() - startTime ) {
			break;
		}
		
		nk::SleepThread( 1 );
	}

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );
		
// 		if( 0 < m_result.GetResultNum() ) {

		// 受信時コールバック
		for( u32 i = 0; i < m_receiveCallbacks.size(); ++i ) {
			m_receiveCallbacks[i]->CallbackReceivedResult( m_result );
		}
// 		}
// 		else {
// 			printf("not found.\n");
// 		}

		Close();
	
		m_finished	= true;
	}

	printf("HostFinder::ThreadFunc end\n");
}

//===========================================================================
/*!	@brief		検索
	@param		timeoutMilliSec	タイムアウトミリ秒
	@return		----
*/
//===========================================================================
bool HostFinder::Find( s32 timeoutMilliSec )
{
	if( Running() ) {
		return false;
	}

	printf("SCOPE_CRITICAL_SECTION\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	printf("_Find\n");
	return _Find( timeoutMilliSec );
}


//===========================================================================
/*!	@brief		検索
	@param		timeoutMilliSec	タイムアウトミリ秒
	@return		----
*/
//===========================================================================
bool HostFinder::_Find( s32 timeoutMilliSec )
{
	printf("HostFinder::_Find start\n");
	
	HostFinder::Setup();
	
	if( m_initialized == false ) {
		printf("HostFinder::_Find false\n");
		return false;
	}
	
	bool	result	= false;

	// こっちの情報を送信
	do {
		// あらかじめ受信待機しておく
		Thread::Start();
		
		// ホスト検索
		result	= _SendMessage();
		if( result == false ) {
			break;
		}

	} while( 0 );


	printf("HostFinder::_Find end\n");

	return result;
}

//===========================================================================
/*!	@brief		こちらの情報をブロードキャストで送信
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::_SendMessage( void )
{
	PRINTF("HostFinder::_SendMessage start\n");
	bool	result = true;

	for( u32 i = 0; i < m_findSockets.size(); ++i ) {
		result	&= m_findSockets[i].Send( &m_sendPacket, sizeof(m_sendPacket) );
		nk::SleepThread( 1 );
	}

	PRINTF("HostFinder::_SendMessage end\n");
	
	return result;
}

//===========================================================================
/*!	@brief		ホストからのメッセージを受信
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::_ReceiveMessageFromHost( void )
{
	printf("HostFinder::_ReceiveMessageFromHost start\n");
	bool	result = false;

	m_receiver.SetTimeout( 0, DEFAULT_TIMEOUT_MILLISEC * 1000 );
	result	= m_receiver.ReceiveWait();

	printf("HostFinder::_ReceiveMessageFromHost end\n");
	
	return result;
}


//===========================================================================
/*!	@brief		受信時コールバック
	@param		packet		受信パケット
	@param		packetSize	パケットサイズ
	@return		----
*/
//===========================================================================
void HostFinder::Receive( void* packet, u32 packetSize )
{
	printf("HostFinder::Receive start\n");
	Packet_FindHostToClient*	hostInfo	= static_cast<Packet_FindHostToClient*>(packet);

	HostInfo	addInfo;
	nk::net::IPAddressToIPAddressStr( &addInfo.ipAddressStr, hostInfo->ipAddress );
	strcpy_s( addInfo.hostName, sizeof(hostInfo->hostName), hostInfo->hostName );
	strcpy_s( addInfo.roomName, sizeof(hostInfo->roomName), hostInfo->roomName );

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );

		// 同じホストの情報は弾く
		if( _Registered( addInfo ) == false ) {
			m_result.results.push_back( addInfo );
		}
	}

	printf("HostFinder::Receive end\n");
}


//===========================================================================
/*!	@brief		終了？
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::IsEnd( void ) const
{
	nk::CriticalSection	criticalSectiom	= m_criticalSection;
	SCOPE_CRITICAL_SECTION( criticalSectiom );
	
	return m_finished;
}


//===========================================================================
/*!	@brief		バッファ取得
	@param		buffer		取得バッファ
	@param		bufferSize	バッファサイズ
	@return		----
*/
//===========================================================================
void* HostFinder::GetBuffer( void )
{
	
	return static_cast<void*>(&m_receivePacket);
}

//===========================================================================
/*!	@brief		バッファサイズ取得
	@param		----
	@return		----
*/
//===========================================================================
u32 HostFinder::GetBufferSize( void ) const
{
	
	return sizeof(m_receivePacket);
}


//===========================================================================
/*!	@brief		同じ情報が登録されているならtrueを返す
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::_Registered( const HostInfo& info )
{
	printf("HostFinder::_Registered start\n");
	
	for( u32 i = 0; i < m_result.GetResultNum(); ++i ) {
		if( m_result.GetResult(i)->IsSameInfo( info ) ) {
			printf("HostFinder::_Registered true\n");
			return true;
		}
	}

	printf("HostFinder::_Registered end\n");

	return false;
}


	
}	// namespace network
