//=============================================================================
/*!	@file	TitleScene.h
	@brief	�^�C�g��

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "system.h"

#include "titleScene.h"
#include "game/gameMain.h"

#include "out/data_list.h"

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
TitleScene::TitleScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
TitleScene::~TitleScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
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
/*!	@brief	�I������
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
/*!	@brief		������
	@param		parent	�e
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


	// ���[�h�A�C�R����~
	GetGameManager()->StopLoadingIcon();

	RegisterToRenderManager();
}


//===========================================================================
/*!	@brief		�I��
	@param		parent	�e
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
/*!	@brief		�X�V
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
/*!	@brief		�`��
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
/*!	@brief		���j���[���莞�R�[���o�b�N
	@param		menuIndex	���j���[�C���f�b�N�X
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
/*!	@brief		�l�b�g���[�N�ΐ평����
	@param		----
	@return		----
*/
//===========================================================================
void TitleScene::InitializeNetwork( void )
{
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_NETWORK );
}


}	// namespace game