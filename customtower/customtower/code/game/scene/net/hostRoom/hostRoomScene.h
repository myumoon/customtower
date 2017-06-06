//=============================================================================
/*!	@file	hostRoomScene.h
	@brief	接続待機部屋

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

#ifndef __HOST_ROOM_SCENE_H__
#define __HOST_ROOM_SCENE_H__

#include "net/socket.h"
#include "thread/thread.h"
#include "utility/selector.h"

#include "game/scene/sceneInterface.h"

namespace network {
class JoinClientChecker;
}

namespace game {


//=============================================================================
/*!
								ホスト部屋
*/
//=============================================================================
class HostRoomScene : public SceneInterface {
public:
	//-----------------------型定義--------------------------
	//! メニュー
	enum {
		MENU_ID_CREATE_ROOM,	//!< 部屋作成
		MENU_ID_DELETE_ROOM,	//!< 部屋削除
		MENU_ID_RETURN,			//!< 戻る
		MENU_ID_MAX,
	};

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		ローカル更新
	*/
	//===========================================================================
	virtual s32		ExecuteLocal( s32 parentMessage );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	virtual void	RenderLocal( void );
	
	//===========================================================================
	/*!	@brief		ツリー生成
	*/
	//===========================================================================
	virtual void	CreateTree( void ) {}

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	virtual void	InitializeScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		終了
	*/
	//===========================================================================
	virtual void	TerminateScene( SceneInterface* parent );

protected:
	//===========================================================================
	/*!	@brief		メニュー決定時コールバック
	*/
	//===========================================================================
	virtual void	CallbackMenuDecide( s32 menuIndex );
	
	//===========================================================================
	/*!	@brief		部屋作成
	*/
	//===========================================================================
	virtual void	InitializeCreateRoom( void );

	//===========================================================================
	/*!	@brief		部屋作成
	*/
	//===========================================================================
	virtual void	InitializeDeleteRoom( void );	

	//===========================================================================
	/*!	@brief		戻る
	*/
	//===========================================================================
	virtual void	InitializeReturn( void );

	static HostRoomScene*	_hostRoomScene;
	static void		CallbackClientAccess( nk::net::IPAddress ip )
	{
		_hostRoomScene->CallbackAccess( ip );
	}
	void CallbackAccess( nk::net::IPAddress ip )
	{
		m_accessIPAddress.push_back( ip );
	}
	
private:
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();


	//----------------------メンバ変数-----------------------
	nk::Selector<HostRoomScene>*	m_menuSelector;			//!< セレクタ
	network::JoinClientChecker*		m_joinClientChecker;	//!< 接続要求確認

	std::vector<nk::net::IPAddress>	m_accessIPAddress;		//!< 受信IPアドレス

public:
	//-------------コンストラクタ・デストラクタ--------------
			HostRoomScene();
	virtual~HostRoomScene();
};
	
}	// namespace game



#endif  // __HOST_ROOM_SCENE_H__
