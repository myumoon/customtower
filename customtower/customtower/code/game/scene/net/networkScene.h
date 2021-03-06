//=============================================================================
/*!	@file	networkScene.h

	@brief	ネットワーク

	@author	ryunosuke ide
	@date	2013.05.26
*/
//=============================================================================

#ifndef __NETWORK_SCENE_H__
#define __NETWORK_SCENE_H__

#include "utility/selector.h"

#include "game/scene/sceneInterface.h"



namespace game {

class SearchHostRoomScene;

//=============================================================================
/*!
								タイトル
*/
//=============================================================================
class NetworkScene : public SceneInterface {
public: 
	//-----------------------型定義--------------------------
	
	//! メニュー
	enum MENU_ID {
		MENU_ID_CREATE_ROOM,		//!< 部屋作成
		MENU_ID_SEARCH_ROOM,		//!< 部屋検索
		MENU_ID_RETURN_TITLE,		//!< タイトルに戻る
		MENU_ID_MAX,				//!< 最大
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
	/*!	@brief		部屋検索
	*/
	//===========================================================================
	virtual void	InitializeSearchRoom( void );

	//===========================================================================
	/*!	@brief		タイトルに戻る
	*/
	//===========================================================================
	virtual void	InitializeReturnTitle( void );

	

private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	nk::Selector<NetworkScene>*		m_menuSelector;			//!< メニューセレクタ
	SearchHostRoomScene*			m_searchHostRoomScene;	//!< サーチシーン
	
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			NetworkScene();
	virtual~NetworkScene();
};
	
}	// namespace game





#endif  // __NETWORK_SCENE_H__