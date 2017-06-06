//=============================================================================
/*!	@file	hostFinder.h

	@brief	ホスト検索

	@author	ryunosuke ide
	@date	2013.05.23
*/
//=============================================================================

#ifndef __HOST_FINDER_H__
#define __HOST_FINDER_H__

#include "net/socket.h"
#include "net/socketReceiver.h"
#include "net/packetReceiver.h"
#include "thread/thread.h"

#include "../packet.h"

namespace network {


//=============================================================================
/*!
								ホスト検索
*/
//=============================================================================
class HostFinder : public nk::net::PacketReceiver, public nk::Thread {
public:
	//-----------------------型定義--------------------------
	static const s32	DEFAULT_TIMEOUT_MILLISEC	= 1000;	//!< デフォルトタイムアウト時間

	//! ホスト情報
	struct HostInfo {
		nk::net::IPAddressStr	ipAddressStr;
		char					hostName[64];
		char					roomName[64];

		//! 同じ？
		bool	IsSameInfo( const HostInfo& rhs )
		{
			if( strcmp( ipAddressStr.ipAddress, rhs.ipAddressStr.ipAddress ) != 0 ) {
				return false;
			}
			if( strcmp( hostName, rhs.hostName ) != 0 )  {
				return false;
			}
			if( strcmp( roomName, rhs.roomName ) != 0 )  {
				return false;
			}

			return true;
		}
	};
	//typedef std::vector<HostInfo>	VecHostInfo;

	//! 検索結果格納用
	struct SearchResult {
		std::vector<HostInfo>		results;	//!< 検索結果

		SearchResult()
		{
			results.reserve( 32 );
		}
		
		//! ヒット数取得
		u32			GetResultNum( void )
		{
			return results.size();
		}

		//! ホスト情報取得
		HostInfo*	GetResult( u32 index )
		{
			if( (0 <= index) && (index < GetResultNum()) ) {
				return &results[index];
			}
			
			return NULL;
		}

		//! クリア
		void		Clear( void )
		{
			results.clear();
		}
	};

	//! 検索結果レシーバー
	class SearchResultReceiver {
	public:
		//! @brief		取得時コールバック
		//! @caution	resultはこの関数内でのみ有効です。
		virtual void	CallbackReceivedResult( SearchResult& result )	= 0;
	};


	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		受信時コールバック追加
	*/
	//===========================================================================
	void				AddReceiver( SearchResultReceiver* receiver );

	//===========================================================================
	/*!	@brief		受信時コールバック追加
	*/
	//===========================================================================
	void				RemoveReceiver( SearchResultReceiver* receiver );

	//===========================================================================
	/*!	@brief		検索
	*/
	//===========================================================================
	bool				Find( s32 timeoutMilliSec = DEFAULT_TIMEOUT_MILLISEC );

	//===========================================================================
	/*!	@brief		終了？
	*/
	//===========================================================================
	bool				IsEnd( void ) const;
	
	//===========================================================================
	/*!	@brief		バッファ取得
	*/
	//===========================================================================
	virtual void*		GetBuffer( void );
	virtual u32			GetBufferSize( void ) const;
	
	//===========================================================================
	/*!	@brief		クローズ
	*/
	//===========================================================================
	void				Close( void );

	
protected:
	//===========================================================================
	/*!	@brief		セットアップ
	*/
	//===========================================================================
	void				Setup( void );

	
	//===========================================================================
	/*!	@brief		受信
	*/
	//===========================================================================
	virtual void		Receive( void* packet, u32 packetSize );

	//===========================================================================
	/*!	@brief		スレッド
	*/
	//===========================================================================
	virtual void		ThreadFunc( void );
	

private:
	//-----------------------メソッド------------------------
	void		_Init( void );
	void		_Term( void );

	//! 検索
	bool		_Find( s32 timeoutMilliSec );

	//! ブロードキャストで送信
	bool		_SendMessage( void );

	//! ホストからのメッセージを受信
	bool		_ReceiveMessageFromHost( void );

	//! 既に登録されていたらtrueを返す
	bool 		_Registered( const HostInfo& info );

	//----------------------メンバ変数-----------------------
	bool								m_initialized;			//!< 初期化
	std::vector<nk::net::Socket>		m_findSockets;			//!< 検索ソケット
	//nk::net::Socket						m_findSocket;			//!< 検索ソケット
	nk::net::Socket						m_receiveSocket;		//!< 受信用ソケット
	nk::net::SocketReceiver				m_receiver;				//!< レシーバ
	nk::net::IPAddress					m_broadcastAddress;		//!< ブロードキャストアドレス
	Packet_FindClientToHost				m_sendPacket;			//!< 送信パケット
	Packet_FindHostToClient				m_receivePacket;		//!< 受信パケット
	
	nk::CriticalSection					m_criticalSection;		//!< クリティカルセクション
	bool								m_finished;				//!< 終了

	SearchResult						m_result;				//!< ホスト情報送信用
	std::vector<SearchResultReceiver*>	m_receiveCallbacks;		//!< 結果受信時コールバック
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			HostFinder();
	virtual~HostFinder();
};


}	// namespace network

#endif  // __HOST_FINDER_H__