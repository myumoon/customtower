//=============================================================================
/*!	@file	packetReceiver.h

	@brief	パケットレシーバ

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================

#ifndef __PACKET_RECEIVER_H__
#define __PACKET_RECEIVER_H__

#include "./socket.h"

namespace nk {

namespace net {

//=============================================================================
/*!
					パケット受信インターフェース
*/
//=============================================================================
class PacketReceiver {
public:
	//! コンストラクタ・デストラクタ
			 PacketReceiver();
	virtual ~PacketReceiver();

	//===========================================================================
	/*!	@brief		受信
	*/
	//===========================================================================
	virtual void		Receive( void* packet, u32 packetSize ) = 0;

	//===========================================================================
	/*!	@brief		バッファ取得
	*/
	//===========================================================================
	//virtual void		GetBuffer( void** buffer, u32* bufferSize ) = 0;
	virtual void*		GetBuffer( void ) = 0;
	virtual u32			GetBufferSize( void ) const = 0;

	//===========================================================================
	/*!	@brief		送信者情報を取得
	*/
	//===========================================================================
	void				GetIPAddressStr( IPAddressStr* outIpAddress ) const;
	IPAddress			GetIPAddress( void ) const;

	//===========================================================================
	/*!	@brief		受信したならtrueを返す
	*/
	//===========================================================================
	bool				IsReceived( void ) const;
	

	//===========================================================================
	/*!	@brief		受信時コールバック
	*/
	//===========================================================================
	void				ReceiveCallback( Socket receiveSocket, void* packet, u32 packetSize, Address senderAddr );


private:
	IPAddressStr			m_ipAddressStr;		//!< 送信者情報
	IPAddress				m_ipAddress;		//!< 送信者情報
	bool					m_received;			//!< 受信したならtrue
};
	
}	// namespace net
	
}	// namespace nk







#endif  // __PACKET_RECEIVER_H__
