//=============================================================================
/*!	@file	searchHostScene.h

	@brief	ホスト検索シーン

	@author	ryunosuke ide
	@date	2013.05.26
*/
//=============================================================================

#ifndef __SEARCH_HOST_SCENE_H__
#define __SEARCH_HOST_SCENE_H__





#include "net/socket.h"
#include "thread/thread.h"
#include "utility/selector.h"

#include "game/scene/sceneInterface.h"
#include "network/client/hostFinder.h"

namespace network {
class HostFinder;
}

namespace game {


//=============================================================================
/*!
								ホスト部屋
*/
//=============================================================================
class SearchHostRoomScene : public SceneInterface, public network::HostFinder::SearchResultReceiver {
public:
	//-----------------------型定義--------------------------
	//! メニュー
	enum {
		MENU_ID_MAX,
	};
	typedef std::vector<network::HostFinder::HostInfo>	VecHostInfo;	//!< ホスト情報

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

	//===========================================================================
	/*!	@brief		検索
	*/
	//===========================================================================
	void			Search( void );

	//===========================================================================
	/*!	@brief		停止
	*/
	//===========================================================================
	void			StopSearch( void )
	{
		m_hostFinder->Close();
	}


protected:
	
	//===========================================================================
	/*!	@brief		検索結果取得コールバック
	*/
	//===========================================================================
 	void			CallbackReceivedResult( network::HostFinder::SearchResult& result );
	
private:
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();


	//----------------------メンバ変数-----------------------
	//nk::Selector<SearchHostRoomScene>*	m_menuSelector;			//!< セレクタ
 	network::HostFinder*			m_hostFinder;			//!< ホスト検索
	VecHostInfo						m_hostInfos;			//!< ホスト情報

public:
	//-------------コンストラクタ・デストラクタ--------------
			SearchHostRoomScene();
	virtual~SearchHostRoomScene();
};
	
}	// namespace game






#endif  // __SEARCH_HOST_SCENE_H__