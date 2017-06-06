//=============================================================================
/*!	@file	gameMain.h

	@brief	メイン関数

	@author	ryunosuke ide
	@date	2011/11/15
*/
//=============================================================================

#ifndef __GAME_MAIN_H__
#define __GAME_MAIN_H__


#include "system.h"
#include "game/scene/sceneManager.h"
#include "system/renderObjectManager.h"
#include "debug/gameDebug.h"
#include "system/camera/flickMoveCamera.h"
//#include "debug/debugCaller.h"
//#include "gameObject.h"
//#include "renderObject.h"
//#include "renderObjectManager.h"


using namespace nk;

class RenderObjectManager;

namespace game {

class RenderObject;
class SceneManager;
	
//=============================================================================
/*!
								ゲームメイン
*/
//=============================================================================
class GameMain : public nk::Main {
public:
	//-----------------------型定義--------------------------

	//! スクリーン
	enum eSCREEN_ID {
		eSCREEN_ID_1			= Main::eSCREEN_ID_USER,
		eSCREEN_ID_SHADOWMAP,
	};

	static const s32	SCREEN_WIDTH	= 1024;	//!< スクリーン幅
	static const s32	SCREEN_HEIGHT	= 768;	//!< スクリーン高さ


	//----------------------静的メンバ-----------------------

	//! シーン変更デバッグ
	DEBUG_MENU_PROC_CALLBACK( DebugCallback_SceneChange );

	
	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	virtual bool		Initialize( void );

	//===========================================================================
	/*!	@brief		終了処理
	*/
	//===========================================================================
	virtual void		Terminate( void );

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual bool		Update( void );

	//===========================================================================
	/*!	@brief		描画前処理
	*/
	//===========================================================================
	virtual void		DrawInitialize( void );

	//===========================================================================
	/*!	@brief		描画後処理
	*/
	//===========================================================================
	virtual void		DrawTerminate( void );

	//===========================================================================
	/*!	@brief		シーン切り替え
	*/
	//===========================================================================
	void				SetNextScene( SceneManager::SCENE_ID id );

	//===========================================================================
	/*!	@brief		シーケンス管理取得
	*/
	//===========================================================================
	SceneManager*		GetSceneManager( void ) const;

	//===========================================================================
	/*!	@brief		ロードアイコン開始
	*/
	//===========================================================================
	void				StartLoadingIcon( void );

	//===========================================================================
	/*!	@brief		ロードアイコン停止
	*/
	//===========================================================================
	void				StopLoadingIcon( void );

	//===========================================================================
	/*!	@brief		システムコールバック
	*/
	//===========================================================================
	virtual void		CallbackEvent( nk::Main::SYSTEM_EVENT event );
protected:

private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	// 描画
	void	_Draw( void );


	//----------------------メンバ変数-----------------------
	SceneManager*						m_sceneManager;				//!< シーケンス管理
	RenderObjectManager*				m_renderObjectManager;		//!< レンダリングオブエジェクト管理

	//nk::graphics::Sprite				m_loadIcon;					//!< ロードアイコン
	nk::resource::ResourceLoader*		m_resourceLoader;			//!< リソースロード
	nk::graphics::SpriteAnimation*		m_loadingIcon;				//!< ローディングアイコン
	
	GameObjectManager					m_gameObjectManager;		//!< ゲームオブジェクト管理

	FlickMoveCamera*					m_flickMoveCamera;			//!< バトル用カメラ
public:
	//-------------コンストラクタ・デストラクタ--------------
			GameMain();
			GameMain(s32 c, char** v);
	virtual~GameMain();
};


}	// namespace game

#endif  // __GAME_MAIN_H__


