//=============================================================================
/*!	@file	packetReceiveThread.h

	@brief	パケット受信スレッド

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================

#ifndef __PACKET_RECEIVE_THREAD_H__
#define __PACKET_RECEIVE_THREAD_H__

#include <vector>
#include <map>
#include "../thread/thread.h"
#include "./socket.h"

namespace nk {
namespace net {

class PacketReceiver;

//=============================================================================
/*!
						パケット受信スレッド
*/
//=============================================================================
class PacketReceiveThread : public Thread {
public:
	//-----------------------型定義--------------------------
		

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		受信時コールバック追加
	*/
	//===========================================================================
	void			Add( const Socket& socket, PacketReceiver* receiver );

	//===========================================================================
	/*!	@brief		タイムアウト設定
	*/
	//===========================================================================
	void			SetTimeout( s32 sec, s32 micSec );

protected:
	virtual void	ThreadFunc( void );

	//===========================================================================
	/*!	@brief		受信チェック
	*/
	//===========================================================================
	bool			Receive( void );
	
private:
	//----------------------メンバ変数-----------------------
	//std::map<Socket::SocketID, PacketReceiver*>	m_receivers;	//!< パケット受信
	std::vector<SocketInfo>		m_vecSocketInfo;	//!< ソケット情報
	fd_set						m_fd;				//!< 受信状態管理
	timeval						m_timeout;			//!< タイムアイト
	u32							m_maxID;			//!< 最大ID

	CriticalSection				m_criticalSection;	//!< ミューテックス
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			PacketReceiveThread();
	virtual~PacketReceiveThread();
};

}	// namespace net
}	// namespace nk


#endif  // __PACKET_RECEIVE_THREAD_H__