//=============================================================================
/*!	@file	gameMain.h

	@brief	メイン関数

	@author	ryunosuke ide
	@date	2011/11/15
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "gameMain.h"

#if defined(_WIN32)
#include <winsock2.h>
#include <windows.h>
#include <wchar.h>
#endif


#if defined(NK_USE_GL)
//#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>	// GLの前にインクルードしておかないと"APIENTRYが再定義される"
#include <GL/glpng.h>
//#include <GL/glut.h>
//#include <GL/glu.h>
//#include <GL/gl.h>
#endif
#if defined(NK_USE_SDL)
//#include <SDL/SDL.h>			// インクルードすると
//#include <SDL/SDL_openGL.h>	// 外部参照エラー
//#include <SDL/SDL_image.h>	// になってしまう
#endif

#include "scene/sceneManager.h"
#include "file/csvLoader.h"
#include "file/file.h"

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
GameMain::GameMain() : Main(0, NULL, SCREEN_WIDTH, SCREEN_HEIGHT, 60, false, "jinroh")
{
	_Init();
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
GameMain::GameMain(s32 c, char** v)	: Main(c, v, SCREEN_WIDTH, SCREEN_HEIGHT, 60, false, "jinroh")
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
GameMain::~GameMain()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void GameMain::_Init( void )
{
	m_flickMoveCamera	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void GameMain::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		----
	@return		----
*/
//===========================================================================
bool GameMain::Initialize( void )
{

	// デバッグメニュー設定
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
	
	// ロードアイコン
	{
		const char*	iconPath		= DATA_SYSTEM_LOADING_ICON_IMG;
		GetResourceManager()->LoadFile( iconPath );
		m_loadingIcon				= new nk::graphics::SpriteAnimation();
		m_loadingIcon->Init( iconPath, 64, 64, 6, 1, 5, true );
		m_loadingIcon->Start();
		m_loadingIcon->SetScreenId( eSCREEN_ID_1 );
	}

	// zerces初期化
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
	
	
	
	

	// ロードアイコン
	m_resourceLoader	= new resource::ResourceLoader();
	m_resourceLoader->Load( DATA_LOADFILE_TXT );
	

	// カメラ設定
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
/*!	@brief		終了処理
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
/*!	@brief		更新
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
/*!	@brief		描画前処理
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

	// デバッグ
	{
		RENDERABLE_TEXTURE->SetRenderTarget( eSCREEN_ID_1 );
		DrawAxis();
	}
}

//===========================================================================
/*!	@brief		描画後処理
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
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::_Draw( void )
{
	//m_sceneManager->Render();			// シーン毎の描画登録
	m_renderObjectManager->Render();
	DEBUG_MENU_DRAW();

// 	m_renderObjectManager->RemoveAll();
}


//===========================================================================
/*!	@brief		次のシーンを設定
	@param		id		シーンID
	@return		true.切り替わった
*/
//===========================================================================
void GameMain::SetNextScene( SceneManager::SCENE_ID id )
{
	NULL_ASSERT( GetSceneManager() );

	GetSceneManager()->SetNextActiveScene( id );

}

//===========================================================================
/*!	@brief		シーン管理取得
	@param		----
	@return		----
*/
//===========================================================================
SceneManager* GameMain::GetSceneManager( void ) const
{
	
	return m_sceneManager;
}


//===========================================================================
/*!	@brief		ローディングアイコン開始
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
/*!	@brief		ローディングアイコン停止
	@param		----
	@return		----
*/
//===========================================================================
void GameMain::StopLoadingIcon( void )
{
	m_loadingIcon->SetVisible( false );
}


//===========================================================================
/*!	@brief		システムイベントコールバック
	@param		event	イベント
	@return		----
*/
//===========================================================================
void GameMain::CallbackEvent( nk::Main::SYSTEM_EVENT event )
{
	m_gameObjectManager.CallbackSystemEvent( event );
}


//===========================================================================
/*!	@brief		デバッグコールバック
	@param		event	イベント
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



