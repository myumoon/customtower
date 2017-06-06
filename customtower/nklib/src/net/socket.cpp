//=============================================================================
/*!	@file	socket.h

	@brief	ソケット

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/net/socket.h"

#if defined(_WIN32)
#include <ws2tcpip.h>
#endif

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "../../include/general.h"

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
Socket::Socket()
{
	//m_copyCounter	= 0;
	_Init();
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	id		ソケット番号
*/
//===========================================================================
Socket::Socket( SocketID id, SOCKET_TYPE type )
{
	_Init();
	
	m_id			= id;
	m_type			= type;
	m_initialized	= true;
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Socket::~Socket()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Socket::_Init( void )
{
	m_initialized	= false;
	m_type			= SOCKET_TYPE_UNKNOWN;
	m_blocking		= true;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Socket::_Term( void )
{
	
}

	
//===========================================================================
/*!	@brief		ソケット生成
	@param		type	TCP/UDP
	@return		true.成功	false.失敗
*/
//===========================================================================
bool Socket::_CreateSocket( SOCKET_TYPE type )
{
	if( type == SOCKET_TYPE_TCP ) {
		m_id	= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		//m_id	= socket( AF_INET, SOCK_STREAM, 0 );
	}
	else {
		m_id	= socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
		//m_id	= socket( AF_INET, SOCK_DGRAM, 0 );
	}

	PRINTF("Created socket : id = %u\n", m_id);
		
	return (0 <= m_id);
}

//===========================================================================
/*!	@brief		IP・ポート設定
	@param		ipAddress	IPアドレス(NULLでINADDR_ANY指定)
	@param		port		ポート
	@return		----
*/
//===========================================================================
void Socket::_SetAddress( const char* ipAddress, s32 port )
{
	memset( &m_addr, 0, sizeof(m_addr) );
	
	m_addr.sin_family		= AF_INET;
	m_addr.sin_addr.s_addr	= ipAddress ? inet_addr( ipAddress ) : htonl( INADDR_ANY );
	m_addr.sin_port			= port == 0 ? 0 : htons( port );
	
}

	
//===========================================================================
/*!	@brief		生成
	@param		ipAddress	IPアドレス
	@param		port		ポート
	@param		blocking	ブロッキング設定(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateTCP( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_TCP;
	
	bool	result	= true;
	result	&= _CreateSocket( SOCKET_TYPE_TCP );

	_SetAddress( ipAddress, port );

	_Bind();

	_SetBlocking( blocking );

	//s32		connectResult	= connect( m_id, (struct sockaddr *)&m_addr, sizeof(m_addr) );
	//result	&= (0 <= connectResult);
	
	m_initialized	= result;

	
	return m_initialized;
}



//===========================================================================
/*!	@brief		生成
	@param		ipAddress	IPアドレス
	@param		port		ポート
	@param		blocking	ブロッキング設定(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateUDP( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_UDP;
	
	bool	result	= true;
	result	&= _CreateSocket( SOCKET_TYPE_UDP );

	_SetAddress( ipAddress, port );

	_Bind();

	_SetBlocking( blocking );

	m_initialized	= result;

	
	return m_initialized;
}



//===========================================================================
/*!	@brief		生成
	@param		ipAddress	IPアドレス
	@param		port		ポート
	@param		blocking	ブロッキング設定(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateUDP_Broadcast( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_UDP_BROADCAST;
	
	bool	result	= true;
	result	&= _CreateSocket( SOCKET_TYPE_UDP_BROADCAST );

	//_SetAddress( "255.255.255.255", port );
	_SetAddress( ipAddress, port );

	///_Bind();

	int	yes	= 1;	// オプション用
	result	&= (0 == setsockopt( m_id, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes) ));

	_SetBlocking( blocking );

	m_initialized	= result;

	
	return m_initialized;
}



//===========================================================================
/*!	@brief		生成
	@param		ipAddress	IPアドレス
	@param		port		ポート
	@param		blocking	ブロッキング設定(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateUDP_Multicast( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_UDP_MULTICAST;
	
	bool	result	= true;
	
	result	&= _CreateSocket( SOCKET_TYPE_UDP_MULTICAST );

	_SetAddress( ipAddress, port );

	/* マルチキャスト用 */
	sockaddr_in		addrLocal;
	ip_mreq			stMreq;	
	
	addrLocal.sin_family			= AF_INET;
	addrLocal.sin_addr.s_addr		= htonl(INADDR_ANY);
	addrLocal.sin_port				= 0;
	
	bind( m_id, (struct sockaddr*)&addrLocal, sizeof(addrLocal) );
	
	stMreq.imr_multiaddr.s_addr		= m_addr.sin_addr.s_addr;
	stMreq.imr_interface.s_addr		= INADDR_ANY;

	int	ttl	= 32;
	
	setsockopt( m_id, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&stMreq, sizeof(stMreq)	);	// メンバシップ
	setsockopt( m_id, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl)			);	// TTL

	_SetBlocking( blocking );

	m_initialized	= result;

	
	return m_initialized;
}


//===========================================================================
/*!	@brief		閉じる
	@param		----
	@return		----
*/
//===========================================================================
void Socket::Close( void )
{
	if( m_initialized ) {
		PRINTF("Closed socket : %u\n", m_id);
		closesocket( m_id );
	}
	
}


//===========================================================================
/*!	@brief		ソケットID取得
	@param		----
*/
//===========================================================================
SocketID Socket::GetID( void ) const
{
	
	return m_id;
}



//===========================================================================
/*!	@brief		パケット送信
	@param		packet		送信パケット
	@param		packetSize	パケットサイズ
	@return		----
*/
//===========================================================================
bool Socket::Send( void* packet, u32 packetSize )
{
	s32	result;
	if( m_type == SOCKET_TYPE_TCP ) {
		result	= send( m_id, (char*)packet, packetSize, 0 );
	}
	else {
		result	= sendto( m_id, (char*)packet, packetSize, 0, (sockaddr*)&m_addr, sizeof(m_addr) );
	}

	return (0 <= result);
}

//===========================================================================
/*!	@brief		パケット受信
	@param[out]	packet		受信パケット
	@param[in]	packetSize	パケットサイズ
	@param[out]	fromAddress	送信者情報(=NULL)
	@return		----
*/
//===========================================================================
SOCKET_RESULT Socket::Receive( void* packet, u32 packetSize, Address* fromAddress )
{
	int	result	= -1;

	
	if( m_type == SOCKET_TYPE_TCP ) {
		if( packet ) {
			result	= recv( GetID(), (char*)packet, packetSize, 0 );
		}
	}
	else {
		if( packet ) {
			sockaddr_in 	fromInfo;
			SocketLength 	fromInfoLen	= sizeof(fromInfo);
			memset( &fromInfo, 0, sizeof(fromInfo) );
			result	= recvfrom( GetID(), (char*)packet, packetSize, 0, (struct sockaddr*)&fromInfo, &fromInfoLen );
			//result	= recvfrom( GetID(), (char*)packet, packetSize, 0, NULL, NULL );

			if( fromAddress ) {
				const char*	addrStr	= inet_ntoa( fromInfo.sin_addr );
				const s32	port	= fromInfo.sin_port;
				fromAddress->SetIpAddress( addrStr, port );
			}
			
		}
	}

	// エラー
	if( result < 0 ) {
		SOCKET_RESULT	result	= GetLastResult();
		return result;
		//printf("error : Socket::Receive() error code = %d\n", WSAGetLastError() );
		//return false;
	}

	return SOCKET_RESULT_OK;
}

//===========================================================================
/*!	@brief		バインド
	@param		----
	@return		----
*/
//===========================================================================
void Socket::Bind( void )
{
	_Bind();
}


//===========================================================================
/*!	@brief		リスン
	@param		backlog		バックログ数
	@return		----
*/
//===========================================================================
void Socket::Listen( s32 backlog )
{
	_Listen( backlog );
}


//===========================================================================
/*!	@brief		接続要求
	@param		----
	@return		----
*/
//===========================================================================
bool Socket::Connect( void )
{
	const bool	result	= _Connect();
	
	return result;
}


//===========================================================================
/*!	@brief		バインド
	@param		----
	@return		----
*/
//===========================================================================
void Socket::_Bind( void )
{

	bind( m_id, (sockaddr*)&m_addr, sizeof(m_addr) );
	
}

//===========================================================================
/*!	@brief		リスン
	@param		backlog		バックログキュー
	@return		----
*/
//===========================================================================
void Socket::_Listen( s32 backlog )
{

	listen( m_id, backlog );
	
}

//===========================================================================
/*!	@brief		接続
	@param		----
	@return		----
*/
//===========================================================================
bool Socket::_Connect( void )
{
	s32	result	= connect( m_id, (struct sockaddr*)&m_addr, sizeof(m_addr) );

	return (0 <= result);
}


//===========================================================================
/*!	@brief		ブロッキング設定
	@param		block	true.ブロック	false.ノンブロック
	@return		----
*/
//===========================================================================
void Socket::SetBlocking( bool block )
{
	_SetBlocking( block );
	
}



//===========================================================================
/*!	@brief		ブロッキング設定
	@param		block	true.ブロック	false.ノンブロック
	@return		----
*/
//===========================================================================
void Socket::_SetBlocking( bool block )
{
	m_blocking	= block;
	
#if defined(_WIN32)
	u_long		val	= block ? 0 : 1;
	ioctlsocket( GetID(), FIONBIO, &val );

#else
	int		val	= block ? 0 : 1;
	ioctl( GetID(), FIONBIO, &val );
	
#endif
	
}


//===========================================================================
/*!	@brief		ブロッキング設定取得
	@param		----
	@return		----
*/
//===========================================================================
bool Socket::IsBlocking( void ) const
{
	
	return m_blocking;
}


}	// namespace net
	
}	// namespace nk
