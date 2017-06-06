//=============================================================================
/*!	@file	socket.h

	@brief	ソケット

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================


#ifndef __SOCKET_H__
#define __SOCKET_H__

#if defined(_WIN32)
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif	// defined(_WIN32)

#include "./socketUtility.h"

namespace nk {

namespace net {
	
//=============================================================================
/*!
								ソケット
*/
//=============================================================================
class Socket {
public:
	//-----------------------型定義--------------------------
	enum SOCKET_TYPE {
		SOCKET_TYPE_UNKNOWN,		//!< 不明
		SOCKET_TYPE_TCP,			//!< TCP
		SOCKET_TYPE_UDP,			//!< UDP
		SOCKET_TYPE_UDP_BROADCAST,	//!< UDP ブロードキャスト
		SOCKET_TYPE_UDP_MULTICAST,	//!< UDP マルチキャスト
		
		SOCKET_TYPE_USER,			//!< ユーザー定義
	};


	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		生成
	*/
	//===========================================================================
	//virtual bool			Create( const char* ipAddress, s32 port ) = 0;
	
	bool			CreateTCP			( const char* ipAddress, s32 port, bool blocking = true );	//!< TCP
	bool			CreateUDP			( const char* ipAddress, s32 port, bool blocking = true );	//!< UDP
	bool			CreateUDP_Broadcast	( const char* ipAddress, s32 port, bool blocking = true );	//!< UDP ブロードキャスト
	bool			CreateUDP_Multicast	( const char* ipAddress, s32 port, bool blocking = true );	//!< UDP マルチキャスト


	//===========================================================================
	/*!	@brief		閉じる
	*/
	//===========================================================================
	void				Close( void );


	//===========================================================================
	/*!	@brief		送信
	*/
	//===========================================================================
	virtual bool		Send( void* packet, u32 packetSize );


	//===========================================================================
	/*!	@brief		受信
	*/
	//===========================================================================
	virtual SOCKET_RESULT		Receive( void* packet, u32 packetSize, Address* senderAddr = NULL );


	//===========================================================================
	/*!	@brief		バインド
	*/
	//===========================================================================
	virtual void		Bind( void );


	//===========================================================================
	/*!	@brief		リスン
	*/
	//===========================================================================
	virtual void		Listen( s32 backlog );


	//===========================================================================
	/*!	@brief		接続要求
	*/
	//===========================================================================
	virtual bool		Connect( void );
	

	//===========================================================================
	/*!	@brief		ソケット番号取得
	*/
	//===========================================================================
	virtual SocketID	GetID( void ) const;

	//===========================================================================
	/*!	@brief		ブロッキング設定
	*/
	//===========================================================================
	void				SetBlocking( bool block = true );

	//===========================================================================
	/*!	@brief		ブロッキング設定取得
	*/
	//===========================================================================
	bool				IsBlocking( void ) const;


protected:
	// ソケット生成
	bool			_CreateSocket( SOCKET_TYPE type );

	// IP・ポート設定
	void			_SetAddress( const char* ipAddress, s32 port );

	// バインド
	void			_Bind( void );

	// リスン
	void			_Listen( s32 backlog );
	
	// 接続
	bool			_Connect( void );

	// ブロッキング設定
	void			_SetBlocking( bool block );
	
protected:
	//----------------------メンバ変数-----------------------
	SocketID		m_id;			//!< ソケット識別子
	sockaddr_in		m_addr;			//!< アドレス
	SOCKET_TYPE		m_type;			//!< 通信タイプ
	bool			m_initialized;	//!< 初期化済みならtrue
	bool			m_blocking;		//!< ブロッキングならtrue
	//s32				m_copyCounter;	//!< コピーカウンタ
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

public:
	//-------------コンストラクタ・デストラクタ--------------
			Socket();
			Socket( SocketID id, SOCKET_TYPE type );
	virtual~Socket();
};


	
}	// namespace net
	
}	// namespace nk







#endif  // __SOCKET_H__