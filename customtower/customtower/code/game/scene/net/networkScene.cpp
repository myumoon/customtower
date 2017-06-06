//=============================================================================
/*!	@file	networkScene.h

	@brief	ネットワーク

	@author	ryunosuke ide
	@date	2013.05.26
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "networkScene.h"
#include "searchHostRoomScene.h"
#include "game/gameMain.h"

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
NetworkScene::NetworkScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
NetworkScene::~NetworkScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void NetworkScene::_Init( void )
{
	m_searchHostRoomScene	= NULL;
	
	m_menuSelector	= new nk::Selector<NetworkScene>( this );
	m_menuSelector->Setup<nk::UpdateRepeat>(
		MENU_ID_MAX,
		GetGameManager()->GetKeyboard(),
		nk::input::Keyboard::KEY_UP,
		nk::input::Keyboard::KEY_DOWN,
		nk::input::Keyboard::KEY_ENTER
	);
	m_menuSelector->SetDecideCallback( &game::NetworkScene::CallbackMenuDecide );

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void NetworkScene::_Term( void )
{

}


//===========================================================================
/*!	@brief		リソース生成
	@param		parent	親
	@return		----
*/
//===========================================================================
void NetworkScene::InitializeScene( SceneInterface* parent )
{
	m_searchHostRoomScene	= static_cast<SearchHostRoomScene*>( GetGameManager()->GetSceneManager()->GetScene( SceneManager::SCENE_ID_SEARCH_HOST_ROOM ) );
	
	ConnectChild( m_searchHostRoomScene );

	RegisterToRenderManager();
}


//===========================================================================
/*!	@brief		リソース削除
	@param		parent	親
	@return		----
*/
//===========================================================================
void NetworkScene::TerminateScene( SceneInterface* parent )
{
	if( m_searchHostRoomScene ) {
		m_searchHostRoomScene->StopSearch();
		m_searchHostRoomScene	= NULL;
	}
	
	DisconnectChild( GetGameManager()->GetSceneManager()->GetScene( SceneManager::SCENE_ID_SEARCH_HOST_ROOM ) );

	RemoveFromRenderManager();
}

//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
s32 NetworkScene::ExecuteLocal( s32 parentMessage )
{
	m_menuSelector->Update();

	return MESSAGE_NONE;
}

//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void NetworkScene::RenderLocal( void )
{
	nk::SystemPrint( 0, 0, "Network" );

	const char*	menuTbl[]	= {
		"Create Room",
		"Search Room",
		"Return Title",
	};
	const s32	offsetX		= 200;
	const s32	offsetY		= 300;
	const s32	lineHeight	= 30;
	for( s32 i = 0; i < MENU_ID_MAX; ++i ) {
		SystemPrint( offsetX, offsetY + i * lineHeight, "%s", menuTbl[i] );
	}
	SystemPrint( offsetX - 20, offsetY + m_menuSelector->GetSelectNo() * lineHeight, ">" );

}


//===========================================================================
/*!	@brief		メニュー決定時コールバック
	@param		menuIndex	メニューインデックス
	@return		----
*/
//===========================================================================
void NetworkScene::CallbackMenuDecide( s32 menuIndex )
{
	if( menuIndex == MENU_ID_CREATE_ROOM ) {
		InitializeCreateRoom();
	}
	else if( menuIndex == MENU_ID_SEARCH_ROOM ) {
		InitializeSearchRoom();
	}
	else if( menuIndex == MENU_ID_RETURN_TITLE ) {
		InitializeReturnTitle();
	}
	
}

//===========================================================================
/*!	@brief		部屋作成
	@param		----
	@return		----
*/
//===========================================================================
void NetworkScene::InitializeCreateRoom( void )
{
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_HOST_ROOM );
}


//===========================================================================
/*!	@brief		部屋検索
	@param		----
	@return		----
*/
//===========================================================================
void NetworkScene::InitializeSearchRoom( void )
{
	m_searchHostRoomScene->Search();
}

//===========================================================================
/*!	@brief		タイトルに戻る
	@param		----
	@return		----
*/
//===========================================================================
void NetworkScene::InitializeReturnTitle( void )
{
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_TITLE );
}

}	// namespace game
