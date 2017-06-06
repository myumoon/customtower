//=============================================================================
/*!	@file	titleScene.h

	@brief	タイトルシーン

	@author	ryunosuke ide
	@date	2013.05.25
*/
//=============================================================================

#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "utility/selector.h"
#include "graphics/graphics.h"


#include "game/scene/sceneInterface.h"

#include "debug/debug.h"
#include "graphics/buttonInputChecker_Mouse.h"

namespace game {


//=============================================================================
/*!
								タイトル
*/
//=============================================================================
class TitleScene : public SceneInterface, public nk::graphics::ButtonEventListener {
public: 
	//-----------------------型定義--------------------------
	
	//! メニュー
	enum MENU_ID {
		MENU_ID_NORMAL_BATTLE,		//!< 通常バトル
		MENU_ID_NETWORK_BATTLE,		//!< ネットワークバトル
		MENU_ID_MODEL_VIEWER,		//!< モデルビューアー
		MENU_ID_STAGE_VIEWER,		//!< ステージビューアー
		MENU_ID_MAX,				//!< 最大
	};

	enum {
		_DEBUG_1,
		_DEBUG_2,
		_DEBUG_3,
	};


	class _DebugListener : public nk::debug::DebugEventListener {
	public:
		virtual void		InputEvent_Left( s32 lineNo, s32& nowNo, char* dispStr, u32 dispStrSize )
		{
			sprintf_s( dispStr, dispStrSize, "lineNo(%d), nowNo(%d)", lineNo, nowNo );
		}
		virtual void		InputEvent_Right( s32 lineNo, s32& nowNo, char* dispStr, u32 dispStrSize )
		{
			sprintf_s( dispStr, dispStrSize, "lineNo(%d), nowNo(%d)", lineNo, nowNo );
		}
		virtual void		InputEvent_Decision( s32 lineNo, s32& nowNo, char* dispStr, u32 dispStrSize )
		{
			sprintf_s( dispStr, dispStrSize, "*lineNo(%d), nowNo(%d)", lineNo, nowNo );
		}
	};
	_DebugListener				m_lisntener;


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
	/*!	@brief		ネット対戦
	*/
	//===========================================================================
	virtual void	InitializeNetwork( void );

	//===========================================================================
	/*!	@brief		メニュー決定時コールバック
	*/
	//===========================================================================
	virtual void	CallbackMenuDecide( s32 menuIndex );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	nk::Selector<TitleScene>*		m_menuSelector;		//!< メニューセレクタ

	// @@@
	nk::graphics::Layout					m_layout;
	nk::graphics::ButtonInputChecker_Mouse*	m_eventChecker;
	//===========================================================================
	/*!	@brief		入場時
	*/
	//===========================================================================
	virtual void	OnCursorOver( nk::graphics::Button* eventButton )
	{
		printf("OnCursorOver\n");
	}

	//===========================================================================
	/*!	@brief		退場時
	*/
	//===========================================================================
	virtual void	OnCursorOut( nk::graphics::Button* eventButton )
	{
		printf("OnCursorOut\n");
	}

	//===========================================================================
	/*!	@brief		押された瞬間(アニメーション開始時)
	*/
	//===========================================================================
	virtual void	OnCursorDownStart( nk::graphics::Button* eventButton )
	{
		printf("OnCursorDownStart\n");
	}

	//===========================================================================
	/*!	@brief		押された瞬間(アニメーション終了時)
	*/
	//===========================================================================
	virtual void	OnCursorDownEnd( nk::graphics::Button* eventButton )
	{
		printf("OnCursorDownEnd\n");
	}

	//===========================================================================
	/*!	@brief		離された瞬間(アニメーション開始時)
	*/
	//===========================================================================
	virtual void	OnCursorUpStart( nk::graphics::Button* eventButton )
	{
		printf("OnCursorUpStart\n");
	}

	//===========================================================================
	/*!	@brief		離された瞬間(アニメーション終了時)
	*/
	//===========================================================================
	virtual void	OnCursorUpEnd( nk::graphics::Button* eventButton )
	{
		printf("OnCursorUpEnd\n");
	}

	//===========================================================================
	/*!	@brief		ホールド時
	*/
	//===========================================================================
	virtual void	OnHold( nk::graphics::Button* eventButton )
	{
		printf("OnHold\n");
	}

	// @@@
public:
	//-------------コンストラクタ・デストラクタ--------------
			TitleScene();
	virtual~TitleScene();
};
	
}	// namespace game




#endif  // __TITLE_SCENE_H__