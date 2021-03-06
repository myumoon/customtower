//=============================================================================
/*!	@file	socketReceiver.h

	@brief	レシーバー

	@author	ryunosuke ide
	@date	2013.05.17
*/
//=============================================================================

#ifndef __SOCKET_RECEIVER_H__
#define __SOCKET_RECEIVER_H__

#include <vector>
#include "./socket.h"


namespace nk {
namespace net {

class PacketReceiver;
	
//=============================================================================
/*!
							ソケットレシーバー
*/
//=============================================================================
class SocketReceiver {
public:
	//-----------------------型定義--------------------------
	struct SocketInfo {
		Socket				socket;
		PacketReceiver*	receiver;

		SocketInfo( const Socket& socket, PacketReceiver* receiver ) {
			this->socket	= socket;
			this->receiver	= receiver;
		}
	};

	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		登録
	*/
	//===========================================================================
	virtual void	AddReceiveScoket( const Socket& socket, PacketReceiver* packetReceiver );

	//===========================================================================
	/*!	@brief		受信待機
	*/
	//===========================================================================
	virtual bool	ReceiveWait( void );
	
	//===========================================================================
	/*!	@brief		タイムアウト設定
	*/
	//===========================================================================
	void			SetTimeout( s32 sec, s32 micSec );

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	void			Init( void );
	
	//===========================================================================
	/*!	@brief		クリア
	*/
	//===========================================================================
	void			Clear( void );
	
private:
	//----------------------メンバ変数-----------------------
	std::vector<SocketInfo>		m_vecSocketInfo;	//!< ソケット情報
	fd_set						m_fd;				//!< 受信状態管理
	timeval						m_timeout;			//!< タイムアイト
	u32							m_maxID;			//!< 最大ID
	
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			SocketReceiver();
	virtual~SocketReceiver();
};
	
}	// namespace net
}	// namespace nk




#endif  // __SOCKET_RECEIVER_H__