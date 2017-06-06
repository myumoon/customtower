//=============================================================================
/*!	@file	networkScene.h

	@brief	�l�b�g���[�N

	@author	ryunosuke ide
	@date	2013.05.26
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "networkScene.h"
#include "searchHostRoomScene.h"
#include "game/gameMain.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace game {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
NetworkScene::NetworkScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
NetworkScene::~NetworkScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
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
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void NetworkScene::_Term( void )
{

}


//===========================================================================
/*!	@brief		���\�[�X����
	@param		parent	�e
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
/*!	@brief		���\�[�X�폜
	@param		parent	�e
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
/*!	@brief		�X�V
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
/*!	@brief		�`��
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
/*!	@brief		���j���[���莞�R�[���o�b�N
	@param		menuIndex	���j���[�C���f�b�N�X
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
/*!	@brief		�����쐬
	@param		----
	@return		----
*/
//===========================================================================
void NetworkScene::InitializeCreateRoom( void )
{
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_HOST_ROOM );
}


//===========================================================================
/*!	@brief		��������
	@param		----
	@return		----
*/
//===========================================================================
void NetworkScene::InitializeSearchRoom( void )
{
	m_searchHostRoomScene->Search();
}

//===========================================================================
/*!	@brief		�^�C�g���ɖ߂�
	@param		----
	@return		----
*/
//===========================================================================
void NetworkScene::InitializeReturnTitle( void )
{
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_TITLE );
}

}	// namespace game
