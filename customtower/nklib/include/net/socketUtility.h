//=============================================================================
/*!	@file	socketUtility.h

	@brief	ソケット

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================

#ifndef __SOCKET_UTILITY_H__
#define __SOCKET_UTILITY_H__

#if defined(_WIN32)
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif	// defined(_WIN32)

#include <stdio.h>
#include <string.h>

namespace nk {

namespace net {
	

#if defined(_WIN32)
typedef SOCKET			SocketID;
typedef	int				SocketLength;
#else
typedef int				SocketID;
typedef	socklen_t		SocketLength;
#endif
//typedef char			IPAddressStr[32];	//!< "255.255.255.255"形式のIPアドレス格納用
struct IPAddressStr {
	char	ipAddress[32];
	
	IPAddressStr() {
		memset( ipAddress, 0, sizeof(ipAddress) );
	}
	IPAddressStr( const char* str ) {
		strcpy_s( ipAddress, sizeof(ipAddress), str );
	}
	IPAddressStr operator=( const char* rhs ) {
		strcpy_s( ipAddress, sizeof(ipAddress), rhs );
		return *this;
	}
	IPAddressStr operator=( const IPAddressStr& rhs ) {
		strcpy_s( ipAddress, sizeof(ipAddress), rhs.ipAddress );
		return *this;
	}	
};

//typedef unsigned char	IPAddress[4];		//!< IPアドレス格納
typedef u32				IPAddress;			//!< IPアドレス格納


//! ソケットの種類
enum SOCKET_TYPE {
	SOCKET_TYPE_TCP,
	SOCKET_TYPE_UDP,
};

//! ソケット処理結果
enum SOCKET_RESULT {
	// OK
	SOCKET_RESULT_OK,						//!< エラー無し

	// 待機
	SOCKET_RESULT_NONBLOCKING_WAIT,			//!< ノンブロック受信待機中

	// エラー
	SOCKET_RESULT_INVALID_ARGS,				//!< 無効な引数
	SOCKET_RESULT_ALREADY,					//!< 既に処理中

	// 無効
	SOCKET_RESULT_UNKNOW_ERROR,				//!< エラー
};

//=============================================================================
/*!
							送受信アドレス
*/
//=============================================================================
struct Address {
	IPAddressStr	ipAddress;		//!< IPアドレス
	//IPAddress		ipAddress;		//!< IPアドレス
	u32				port;			//!< ポート番号

	//! コンストラクタ
	Address( void ) {
		Init();
	}

	//! 初期化
	void	Init( void );

	//! 設定
	void	SetIpAddress( const char* ipAddress, u32 port );
	//void	SetIpAddress( IPAddress ipAddress, u32 port );
};



//=============================================================================
/*!
							アダプタ情報
*/
//=============================================================================
struct AdapterInfo {
	IPAddressStr	ipAddress;				//!< IP
	IPAddressStr	subnetMask;				//!< サブネットマスク
	char			physicalAddress[256];	//!< 物理アドレス
};


//=============================================================================
/*!
							パケットヘッダ
*/
//=============================================================================
struct PacketHeader {
	u32			headerSize;		//!< このデータサイズ
	u32			dataSize;		//!< データサイズ
	u64			packetNo;		//!< パケット番号
};


//=============================================================================
/*!
							受信確認パケット
*/
//=============================================================================
struct ReceiveCheckPacket {
	u64			packetNo;
};

//===========================================================================
/*!	@brief		ソケットの生成
*/
//===========================================================================
s32		CreateSocket( SOCKET_TYPE type );


//===========================================================================
/*!	@brief		ソケットをクローズ
*/
//===========================================================================
void	CloseSocket( SocketID socket );

//===========================================================================
/*!	@brief		接続
*/
//===========================================================================
s32		ConnectSocket( SocketID socket, struct sockaddr* addr, SocketLength addrSize );


//===========================================================================
/*!	@brief		アダプタ情報を取得
*/
//===========================================================================
bool	GetAdapterInfo( AdapterInfo* outAdapterInfo, s32 adapterNo );
	

//===========================================================================
/*!	@brief		"255.255.255.255" -> FFFFFFFF
*/
//===========================================================================
void	IPAddressStrToIPAddress( IPAddress* outIpAddress, IPAddressStr ipAddress );


//===========================================================================
/*!	@brief		FFFFFFFF -> "255.255.255.255"
*/
//===========================================================================
void	IPAddressToIPAddressStr( IPAddressStr* outIpAddress, IPAddress ipAddress );


//===========================================================================
/*!	@brief		ブロードキャストアドレスを取得
*/
//===========================================================================
bool	GetBroadcastAddressStr( IPAddressStr* outIpAddress, s32 adapterNo = 0 );

//===========================================================================
/*!	@brief		結果取得
*/
//===========================================================================
SOCKET_RESULT GetLastResult( void );
	
}	// namespace net
	
}	// namespace nk







#endif  // __SOCKET_UTILITY_H__