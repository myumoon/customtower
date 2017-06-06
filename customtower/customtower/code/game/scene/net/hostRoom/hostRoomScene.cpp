//=============================================================================
/*!	@file	hostRoomScene.h
	@brief	接続待機部屋

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "hostRoomScene.h"

#include "general.h"
#include "game/gameMain.h"
#include "network/server/joinClientChecker.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

namespace game {

HostRoomScene*	HostRoomScene::_hostRoomScene	= NULL;
}

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
HostRoomScene::HostRoomScene()
{
	_hostRoomScene	= this;
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
HostRoomScene::~HostRoomScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void HostRoomScene::_Init( void )
{

	m_menuSelector	= new nk::Selector<HostRoomScene>( this );
	m_menuSelector->Setup<nk::UpdateRepeat>(
		MENU_ID_MAX,
		GetGameManager()->GetKeyboard(),
		nk::input::Keyboard::KEY_UP,
		nk::input::Keyboard::KEY_DOWN,
		nk::input::Keyboard::KEY_ENTER
	);
	m_menuSelector->SetDecideCallback( &game::HostRoomScene::CallbackMenuDecide );
	

	m_joinClientChecker		= new network::JoinClientChecker();
	m_joinClientChecker->m_callbackReceive	= CallbackClientAccess;
	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void HostRoomScene::_Term( void )
{
	nk::SafeDelete( m_menuSelector );
	
}


//===========================================================================
/*!	@brief		初期化
	@param		parent	親
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeScene( SceneInterface* parent )
{
	m_accessIPAddress.clear();
	m_accessIPAddress.reserve( 128 );

	RegisterToRenderManager();
}


//===========================================================================
/*!	@brief		終了
	@param		parent	親
	@return		----
*/
//===========================================================================
void HostRoomScene::TerminateScene( SceneInterface* parent )
{
	RemoveFromRenderManager();
}

//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
s32 HostRoomScene::ExecuteLocal( s32 parentMessage )
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
void HostRoomScene::RenderLocal( void )
{
	SystemPrint( 0, 0, "HostRoom" );

	
	const char*	menuTbl[]	= {
		"Create Room",
		"Delete Room",
		"Return",
	};

	{
		const s32	offsetX		= 200;
		const s32	offsetY		= 300;
		const s32	lineHeight	= 30;
		for( s32 i = 0; i < MENU_ID_MAX; ++i ) {
			SystemPrint( offsetX, offsetY + i * lineHeight, "%s", menuTbl[i] );
		}
		SystemPrint( offsetX - 20, offsetY + m_menuSelector->GetSelectNo() * lineHeight, ">" );
	}

	{
		const s32	lineHeight	= 30;
		const s32	offsetX		= 400;
		const s32	offsetY		= 70;
		const s32	hostInfoNum	= 1;
		
		SystemPrint( offsetX, offsetY, "================= Access IP =================" );

		nk::net::IPAddressStr	str;
		u32 i	= 0;
		for( i = 0; i < m_accessIPAddress.size(); ++i ) {
			nk::net::IPAddressToIPAddressStr( &str, m_accessIPAddress[i] );
			SystemPrint( offsetX, offsetY + (i + 1) * lineHeight, "IP Address : %s", str.ipAddress	);
		}
		SystemPrint( offsetX, offsetY + lineHeight * (m_accessIPAddress.size() + hostInfoNum) + lineHeight * 1, "=============================================" );
	}

}



//===========================================================================
/*!	@brief		メニュー決定時コールバック
	@param		menuIndex	メニューインデックス
	@return		----
*/
//===========================================================================
void HostRoomScene::CallbackMenuDecide( s32 menuIndex )
{
	if( menuIndex == MENU_ID_CREATE_ROOM ) {
		InitializeCreateRoom();
	}
	else if( menuIndex == MENU_ID_DELETE_ROOM ) {
		InitializeDeleteRoom();
	}
	else if( menuIndex == MENU_ID_RETURN ) {
		InitializeReturn();
	}
}

//===========================================================================
/*!	@brief		部屋作成
	@param		----
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeCreateRoom( void )
{
	bool b = m_joinClientChecker->Setup();
	if( b ) {
		GetGameManager()->StartLoadingIcon();
		printf("HostRoomScene::ExecuteLocal m_joinClientChecker->CheckReceive() true\n");
	}
	else {
		printf("HostRoomScene::ExecuteLocal m_joinClientChecker->CheckReceive() false\n");
	}
}


//===========================================================================
/*!	@brief		部屋削除
	@param		----
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeDeleteRoom( void )
{
	GetGameManager()->StopLoadingIcon();
	
	m_joinClientChecker->Close();
}


//===========================================================================
/*!	@brief		戻る
	@param		----
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeReturn( void )
{
	GetGameManager()->StopLoadingIcon();
	
	m_joinClientChecker->Close();
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_NETWORK );
}

	
}	// namespace game
