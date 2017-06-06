//=============================================================================
/*!	@file	TitleScene.h
	@brief	タイトル

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "system.h"

#include "titleScene.h"
#include "game/gameMain.h"

#include "out/data_list.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace game {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
TitleScene::TitleScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
TitleScene::~TitleScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void TitleScene::_Init( void )
{
	m_eventChecker	= NULL;
	
	m_menuSelector	= new nk::Selector<TitleScene>( this );
	m_menuSelector->Setup<nk::UpdateRepeat>(
		MENU_ID_MAX,
		GetGameManager()->GetKeyboard(),
		nk::input::Keyboard::KEY_UP,
		nk::input::Keyboard::KEY_DOWN,
		nk::input::Keyboard::KEY_ENTER
	);
	m_menuSelector->SetDecideCallback( &game::TitleScene::CallbackMenuDecide );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void TitleScene::_Term( void )
{
	nk::SafeDelete( m_menuSelector );
	nk::SafeDelete( m_eventChecker );
}



//===========================================================================
/*!	@brief		初期化
	@param		parent	親
	@return		----
*/
//===========================================================================
void TitleScene::InitializeScene( SceneInterface* parent )
{

	nk::graphics::Button*	button	= new nk::graphics::Button();
	button->SetScreen( GameMain::eSCREEN_ID_1 );

	button->SetEventChecker( m_eventChecker = new nk::graphics::ButtonInputChecker_Mouse( GetGameManager()->GetMouse() ) );
	
	button->CreateButton_Normal(	DATA_INTERFACE_COMMON_BUTTON_TEST_BUTTON_NORMAL_IMG,	150, 50, 1, 1, true  );
	button->CreateButton_Active(	DATA_INTERFACE_COMMON_BUTTON_TEST_BUTTON_ACTIVE_IMG,	150, 50, 1, 1, true  );
	button->CreateButton_Pushed(	DATA_INTERFACE_COMMON_BUTTON_TEST_BUTTON_PUSH_IMG,		150, 50, 1, 1		 );
	button->CreateButton_Hold(		DATA_INTERFACE_COMMON_BUTTON_TEST_BUTTON_HOLD_IMG,		150, 50, 1, 1, true  );
	button->CreateButton_Released(	DATA_INTERFACE_COMMON_BUTTON_TEST_BUTTON_RELEASE_IMG,	150, 50, 1, 1		 );
	button->CreateButton_Decide(	DATA_INTERFACE_COMMON_BUTTON_TEST_BUTTON_DECIDE_IMG,	150, 50, 1, 1		 );

	button->SetEventListener( this );

	m_layout.Initialize( GetGameManager()->GetMouse(), GetGameManager()->GetKeyboard() );
	m_layout.GetRoot()->AddParts( button );


	// ロードアイコン停止
	GetGameManager()->StopLoadingIcon();

	RegisterToRenderManager();
}


//===========================================================================
/*!	@brief		終了
	@param		parent	親
	@return		----
*/
//===========================================================================
void TitleScene::TerminateScene( SceneInterface* parent )
{
	m_layout.DeleteParts();

	nk::SafeDelete( m_eventChecker );
	
	RemoveFromRenderManager();
}

//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
s32 TitleScene::ExecuteLocal( s32 parentMessage )
{
	//m_menuSelector->Update();

	m_layout.UpdateParts();


	return MESSAGE_NONE;
}

//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void TitleScene::RenderLocal( void )
{
	nk::SystemPrint( 0, 0, "Title" );

	const char*	menuTbl[]	= {
		"Normal  battle",
		"Network battle",
		"Model Viewer",
		"Stage Viewer",
	};
	const s32	offsetX		= 400;
	const s32	offsetY		= 300;
	const s32	lineHeight	= 30;
	for( s32 i = 0; i < MENU_ID_MAX; ++i ) {
		SystemPrint( offsetX, offsetY + i * lineHeight, "%s", menuTbl[i] );
	}
	SystemPrint( offsetX - 20, offsetY + m_menuSelector->GetSelectNo() * lineHeight, ">" );

	m_layout.DrawParts();

}


//===========================================================================
/*!	@brief		メニュー決定時コールバック
	@param		menuIndex	メニューインデックス
	@return		----
*/
//===========================================================================
void TitleScene::CallbackMenuDecide( s32 menuIndex )
{
	if( menuIndex == MENU_ID_NORMAL_BATTLE ) {
		GetGameManager()->SetNextScene( SceneManager::SCENE_ID_NORMAL_BATTLE );
	}
	else if( menuIndex == MENU_ID_NETWORK_BATTLE ) {
		InitializeNetwork();
	}
	else if( menuIndex == MENU_ID_MODEL_VIEWER ) {
		GetGameManager()->SetNextScene( SceneManager::SCENE_ID_MODEL_VIEWER );
	}
	else if( menuIndex == MENU_ID_STAGE_VIEWER ) {
		GetGameManager()->SetNextScene( SceneManager::SCENE_ID_STAGE_VIEWER );
	}
}

//===========================================================================
/*!	@brief		ネットワーク対戦初期化
	@param		----
	@return		----
*/
//===========================================================================
void TitleScene::InitializeNetwork( void )
{
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_NETWORK );
}


}	// namespace game