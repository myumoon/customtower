//=============================================================================
/*!	@file	gameMain.h

	@brief	���C���֐�

	@author	ryunosuke ide
	@date	2011/11/15
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "gameMain.h"

#if defined(_WIN32)
#include <winsock2.h>
#include <windows.h>
#include <wchar.h>
#endif


#if defined(NK_USE_GL)
//#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>	// GL�̑O�ɃC���N���[�h���Ă����Ȃ���"APIENTRY���Ē�`�����"
#include <GL/glpng.h>
//#include <GL/glut.h>
//#include <GL/glu.h>
//#include <GL/gl.h>
#endif
#if defined(NK_USE_SDL)
//#include <SDL/SDL.h>			// �C���N���[�h�����
//#include <SDL/SDL_openGL.h>	// �O���Q�ƃG���[
//#include <SDL/SDL_image.h>	// �ɂȂ��Ă��܂�
#endif

#include "scene/sceneManager.h"
#include "file/csvLoader.h"
#include "file/file.h"

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
GameMain::GameMain() : Main(0, NULL, SCREEN_WIDTH, SCREEN_HEIGHT, 60, false, "jinroh")
{
	_Init();
}

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
GameMain::GameMain(s32 c, char** v)	: Main(c, v, SCREEN_WIDTH, SCREEN_HEIGHT, 60, false, "jinroh")
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
GameMain::~GameMain()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void GameMain::_Init( void )
{
	m_flickMoveCamera	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void GameMain::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		----
	@return		----
*/
//===========================================================================
bool GameMain::Initialize( void )
{

	// �f�o�b�O���j���[�ݒ�
	{
		DEBUG_MENU_INIT( 30, 100, 10 );

		DEBUG_MENU_ADD_LINE( DEBUG_MENU_LINE_SCENE_CHANGE, "Scene Change" );

		#ifdef SCENE_TBL
			#undef SCENE_TBL
		#endif
		#define SCENE_TBL( id, classname, title )	{ DEBUG_MENU_ADD_ITEM( DEBUG_MENU_LINE_SCENE_CHANGE, GameMain, DebugCallback_SceneChange, title ); }
			#include "game/scene/sceneTbl.tbl"
		#undef SCENE_TBL
	}
	
	GameObject::m_gameManager		= this;
	GameObject::m_gameObjectManager	= &m_gameObjectManager;
	
	m_renderObjectManager			= NULL;
	m_renderObjectManager			= new RenderObjectManager();
	
	// ���[�h�A�C�R��
	{
		const char*	iconPath		= DATA_SYSTEM_LOADING_ICON_IMG;
		GetResourceManager()->LoadFile( iconPath );
		m_loadingIcon				= new nk::graphics::SpriteAnimation();
		m_loadingIcon->Init( iconPath, 64, 64, 6, 1, 5, true );
		m_loadingIcon->Start();
		m_loadingIcon->SetScreenId( eSCREEN_ID_1 );
	}

	// zerces������
	{
		const bool xercesResult	= nk::XercesUtility::Initialize();
		
		if( xercesResult == false ) {
			PRINTF("xercesc error\n");
			return false;
		}
	}


	// @@@@@
	{
		nk::LayoutXmlWriter	writer;
		writer.WriteToFile( "data/interface/layout.xml", NULL );
	}
	
	
	m_sceneManager					= new SceneManager();
	
	
	
	

	// ���[�h�A�C�R��
	m_resourceLoader	= new resource::ResourceLoader();
	m_resourceLoader->Load( DATA_LOADFILE_TXT );
	

	// �J�����ݒ�
	{
		system::NormalCamera*	normalCamera = GetCameraManager()->CreateCamera<system::NormalCamera>(
			math::Vector(0.0f, 0.0f, 400.0f),
			math::Vector(0.0f, 0.0f, 0.0f),
			math::Vector(0.0f, 1.0f, 0.0f)
		);

		
		m_flickMoveCamera	= GetCameraManager()->CreateCamera<FlickMoveCamera>(
			math::Vector(0.0f, 0.0f, 400.0f),
			math::Vector(0.0f, 0.0f, 0.0f),
			math::Vector(0.0f, 1.0f, 0.0f)
		);
		m_flickMoveCamera->Initialize( GetMouse(), nk::input::Mouse::CLICK_WHEEL );
	}

	GetScreen()->CreateScreen( GetScreenWidth(), GetScreenHeight(), eSCREEN_ID_1			);
	GetScreen()->CreateScreen( GetScreenWidth(), GetScreenHeight(), eSCREEN_ID_SHADOWMAP	);

	m_sceneManager->CreateScene();
	m_sceneManager->SetNextActiveScene( SceneManager::SCENE_ID_TITLE );

	
	
	return true;
}

//===========================================================================
/*!	@brief		�I������
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::Terminate( void )
{
	DEBUG_MENU_DELETE_LINE_ALL();

	m_renderObjectManager->RemoveAll();
	m_sceneManager->DeleteScene();

	SafeDelete( m_loadingIcon );
	SafeDelete( m_resourceLoader );
	SafeDelete( m_sceneManager );
	SafeDelete( m_renderObjectManager );

	nk::XercesUtility::Terminate();
	
}

//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
bool GameMain::Update( void )
{
	
	m_loadingIcon->Update();
	if( m_resourceLoader->Update() == false ) {
		m_loadingIcon->Draw( math::Vector() );

		return true;
	}

	m_loadingIcon->Draw( math::Vector( GetScreenWidth() - 100, GetScreenHeight() - 100, 0.0f ) );

	DEBUG_MENU_UPDATE();

	if( m_flickMoveCamera ) {
		m_flickMoveCamera->Update();
	}
	m_sceneManager->Execute();

	_Draw();


	return true;
}

//===========================================================================
/*!	@brief		�`��O����
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::DrawInitialize( void )
{
	GetScreen()->ClearScreen( eSCREEN_ID_1 );
	GetScreen()->ClearScreen( eSCREEN_ID_SHADOWMAP );

	RENDERABLE_TEXTURE->RestoreRenderTarget();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	// �f�o�b�O
	{
		RENDERABLE_TEXTURE->SetRenderTarget( eSCREEN_ID_1 );
		DrawAxis();
	}
}

//===========================================================================
/*!	@brief		�`��㏈��
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::DrawTerminate( void )
{
	

	RENDERABLE_TEXTURE->RestoreRenderTarget();
	ChangeMode2D();
	GetScreen()->Draw( eSCREEN_ID_1 );
}




//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::_Draw( void )
{
	//m_sceneManager->Render();			// �V�[�����̕`��o�^
	m_renderObjectManager->Render();
	DEBUG_MENU_DRAW();

// 	m_renderObjectManager->RemoveAll();
}


//===========================================================================
/*!	@brief		���̃V�[����ݒ�
	@param		id		�V�[��ID
	@return		true.�؂�ւ����
*/
//===========================================================================
void GameMain::SetNextScene( SceneManager::SCENE_ID id )
{
	NULL_ASSERT( GetSceneManager() );

	GetSceneManager()->SetNextActiveScene( id );

}

//===========================================================================
/*!	@brief		�V�[���Ǘ��擾
	@param		----
	@return		----
*/
//===========================================================================
SceneManager* GameMain::GetSceneManager( void ) const
{
	
	return m_sceneManager;
}


//===========================================================================
/*!	@brief		���[�f�B���O�A�C�R���J�n
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::StartLoadingIcon( void )
{
	m_loadingIcon->SetVisible( true );
	m_loadingIcon->Start();
}

//===========================================================================
/*!	@brief		���[�f�B���O�A�C�R����~
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::StopLoadingIcon( void )
{
	m_loadingIcon->SetVisible( false );
}


//===========================================================================
/*!	@brief		�V�X�e���C�x���g�R�[���o�b�N
	@param		event	�C�x���g
	@return		----
*/
//===========================================================================
void GameMain::CallbackEvent( nk::Main::SYSTEM_EVENT event )
{
	m_gameObjectManager.CallbackSystemEvent( event );
}


//===========================================================================
/*!	@brief		�f�o�b�O�R�[���o�b�N
	@param		event	�C�x���g
	@return		----
*/
//===========================================================================
void GameMain::DebugCallback_SceneChange( u32 lineNo, nk::debug::CALL_EVENT event )
{
	if( event == nk::debug::CALL_EVENT_DECIDE ) {
		PRINTF("Debug Scene change : %d\n", lineNo);
		GetSceneManager()->SetNextActiveScene( static_cast<SceneManager::SCENE_ID>(lineNo) );
	}
	
}

	
}	// namespace game



