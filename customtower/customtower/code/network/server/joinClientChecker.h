//=============================================================================
/*!	@file	joinClientChecker.h

	@brief	クライアント追加確認

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================


#ifndef __JOIN_CLIENT_CHECKER_H__
#define __JOIN_CLIENT_CHECKER_H__

#include <vector>
#include "net/socket.h"
#include "net/socketReceiver.h"
#include "net/packetReceiver.h"
#include "thread/thread.h"

#include "../packet.h"

namespace network {



//=============================================================================
/*!
							クライアント追加確認
*/
//=============================================================================
class JoinClientChecker : public nk::net::PacketReceiver, public nk::Thread {
public:
	//-----------------------型定義--------------------------

	//! パケット送信スレッド
	class PacketSendThread : public nk::Thread {
	public:
		static const s32	DEFAULT_SEND_NUM				= 10;	//!< デフォルト送信回数
		static const s32	DEFAULT_SEND_INTERVAL_MILLISEC	= 100;	//!< 送信間隔

		//! 送信情報
		struct SendInfo {
			nk::net::Socket				sendSocket;			//!< 送信ソケット
			Packet_FindHostToClient		sendPacket;			//!< 送信パケット
			s32							sendCount;			//!< 送信開始時間
		};
		typedef std::vector<SendInfo>	VecSendInfo;
		
	public:
		//! コンストラクタ・デストラクタ
				 PacketSendThread();
		virtual ~PacketSendThread();

		//! 設定
		void		AddSendSocket(
			nk::net::IPAddress				ipAddress,
			u32								port,
			const Packet_FindHostToClient&	packet
		);
		
		//! 設定
		void		SetOption( s32 sendNum, s32 intervalMilliSec );

		//! スレッド処理
		void		ThreadFunc( void );
		
	private:
		//! 初期化
		void		_Init( void );
		void		_Term( void );

		//! ソケット削除
		void		_DeleteSockets( void );
		
	private:
		nk::CriticalSection				m_criticalSection;	//!< クリティカルセクション
		VecSendInfo						m_sendInfos;		//!< 送信情報
		s32								m_sendNum;			//!< 送信回数
		s32								m_sendInterval;		//!< 送信間隔
	};

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		セットアップ
	*/
	//===========================================================================
	bool	Setup( void );

	//===========================================================================
	/*!	@brief		クローズ
	*/
	//===========================================================================
	void	Close( void );	
		
	//===========================================================================
	/*!	@brief		受信チェック
		@note		データを受信するまでブロックします
	*/
	//===========================================================================
	bool	CheckReceive( void );
	
	//===========================================================================
	/*!	@brief		バッファ取得
	*/
	//===========================================================================
	virtual void*	GetBuffer( void )			{ return &m_receivePacket; }
	virtual u32		GetBufferSize( void ) const	{ return sizeof(m_receivePacket); }

	//===========================================================================
	/*!	@brief		受信
	*/
	//===========================================================================
	virtual void	Receive( void* packet, u32 packetSize );

	void	(*m_callbackReceive)( nk::net::IPAddress );

protected:
	//===========================================================================
	/*!	@brief		スレッド処理
	*/
	//===========================================================================
	virtual void	ThreadFunc( void );
	
private:
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

	//----------------------メンバ変数-----------------------
	nk::net::Socket					m_receiveCheckSocket;	//!< ブロードキャスト受信ソケット
	nk::net::SocketReceiver			m_receiver;				//!< レシーバ
	Packet_FindClientToHost			m_receivePacket;		//!< 受信パケット
	PacketSendThread				m_sendThread;			//!< 送信スレッド
	nk::CriticalSection				m_criticalSection;	//!< クリティカルセクション
	//nk::net::Socket					m_sendSocket;			//!< 通知ソケット
	
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			JoinClientChecker();
	virtual~JoinClientChecker();
};
	
}	// namespace network




#endif  // __JOIN_CLIENT_CHECKER_H__