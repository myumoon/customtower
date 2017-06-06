//=============================================================================
/*!	@file	system.cpp

	/*!	@brief	メインクラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../include/system.h"
#include "../include/render/drawpacket.h"
#include "../include/utility/autoTime.h"

#if defined(_WINDOWS)
#include <winsock2.h>
#include <windows.h>
#endif

#if defined(NK_USE_DIRECTX)

#elif defined(NK_USE_SDLGL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_opengl.h>
#include <GL/glut.h>

#elif defined(NK_USE_GL)
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glpng.h>

#elif defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#endif

#if defined(_DEBUG)
	#define _DEBUG_FUNC_ENABLE
#else
	#define _DEBUG_FUNC_ENABLE
#endif

namespace nk {
//namespace system {

//------------------------------静的メンバ定義------------------------------
const f32	Main::DEFAULT_SCREEN_WIDTH		= 1024;
const f32	Main::DEFAULT_SCREEN_HEIGHT		= 768;
const s32	Main::DEFAULT_FRAME_RATE		= 30;
const s32	Main::SYSTEM_FONT_SIZE			= 8;


namespace {

	
// ウインドウコールバック時に参照するポインタ
struct _SystemPointer {
	NK_WINDOW_HANDLE	windowHandle;	// ウインドウ識別ハンドル
	Main*				system;			// システムへのポインタ

	_SystemPointer() {
		system	= NULL;
	}
};

std::vector<_SystemPointer>		_systemPointer;	// システムへの参照


// デバッグ用
#if defined(_DEBUG_FUNC_ENABLE)
Main*		_system	= NULL;
#endif

}	// unnamed


//--------------------------------static関数--------------------------------

namespace {

//===========================================================================
/*!	@brief	ウインドウコールバック
	@param	----
	@return	----
*/
//===========================================================================
void _WindowCallback( void* param )
{
	if( param ) {
		nk::Main*	system	= static_cast<nk::Main*>(param);
		system->UpdateCallback();
	}
}
	
#if defined(_WINDOWS)

//===========================================================================
/*!	@brief	ウインドウコールバック
	@param	----
	@return	----
*/
//===========================================================================
LRESULT CALLBACK _WindowCallback( HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{	
	//int pixelFormat;
	//BOOL	bResult;

	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
		1,                     // version number 
		PFD_DRAW_TO_WINDOW |   // support window 
		PFD_SUPPORT_OPENGL |   // support OpenGL 
		PFD_DOUBLEBUFFER,      // double buffered 
		PFD_TYPE_RGBA,         // RGBA type 
		24,                    // 24-bit color depth 
		0, 0, 0, 0, 0, 0,      // color bits ignored 
		0,                     // no alpha buffer 
		0,                     // shift bit ignored 
		0,                     // no accumulation buffer 
		0, 0, 0, 0,            // accum bits ignored 
		32,                    // 32-bit z-buffer 
		0,                     // no stencil buffer 
		0,                     // no auxiliary buffer 
		PFD_MAIN_PLANE,        // main layer 
		0,                     // reserved 
		0, 0, 0                // layer masks ignored 
	};

	
#if 0
	switch (iMsg) {

	case WM_CREATE:

		g_hDC			= GetDC( hwnd );
		pixelFormat		= ChoosePixelFormat( g_hDC, &pfd );
		bResult			= SetPixelFormat( g_hDC, pixelFormat, &pfd );

		g_hRC			= wglCreateContext( g_hDC );
		wglMakeCurrent( g_hDC, g_hRC );


		// 画像読込みスレッド作成
		if( 1 )
		{
			g_bThreadFinish = false;
			wglMakeCurrent( NULL, NULL );

			/* スレッド用パラメータ */
			HANDLE	hWnd;
			DWORD	dwID;
			//CreateThread( NULL, 0, ThreadFunc, (LPVOID)hWnd, 0, &dwID );
			CreateThread( NULL, 0, ThreadFunc, NULL, 0, &dwID );
		}
		
		
 		pngInfo info;
 		g_nTextureId	= pngBind( "ika.png", PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST );

		return 0;

	case WM_PAINT:

		// レンダリングコンテキストを戻す
		{
			wglMakeCurrent( g_hDC, g_hRC );
		}
		
		glClearColor(0.0, 0.4, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//glRectd(-0.5,-0.5,0.5,0.5);
		
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			
			struct sPoint {
				float	x, y;
				float	u, v;
			};
			sPoint point[] = {
				{ -1.0f,  1.0f, 0.0f, 0.0f },
				{ -1.0f, -1.0f, 0.0f, 1.0f },				
				{  1.0f,  1.0f, 1.0f, 0.0f },
				{  1.0f, -1.0f, 1.0f, 1.0f }
			};

			if( g_bThreadFinish ) {

				glEnable( GL_CULL_FACE );				// カリングを有効にする
				glFrontFace( GL_CCW );					// CCW反時計回り、CW時計回り
				glCullFace( GL_BACK );					// 背面ポリゴンを描画しないようにする。
				glEnable( GL_TEXTURE_2D );				//テクスチャON
				
				
				glBindTexture( GL_TEXTURE_2D, g_nTextureId );

				glBegin( GL_TRIANGLES );
				{
					glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
					
					glTexCoord2f( point[0].u, point[0].v );
					glVertex2f( point[0].x, point[0].y );

					glTexCoord2f( point[1].u, point[1].v );
					glVertex2f( point[1].x, point[1].y );

					glTexCoord2f( point[2].u, point[2].v );
					glVertex2f( point[2].x, point[2].y );
				}
				glEnd();

				glBindTexture( GL_TEXTURE_2D, 0 );
			}
		}

		glFlush();
		SwapBuffers(g_hDC);

		return 0;

	case WM_DESTROY :

		wglMakeCurrent(g_hDC, 0);
		wglDeleteContext(g_hRC);

		PostQuitMessage(0);
		return 0;

	}
#endif
	

	return DefWindowProc( hwnd, iMsg, wParam, lParam );

}

#endif

	
}

// システムプリント
void SystemPrint( s32 x, s32 y, const char* fmt, ... )
{
#if defined(_DEBUG_FUNC_ENABLE)
	
	NULL_ASSERT( _system );

	char outBuff[512]	= { 0 };
	
	va_list argPtr;
	va_start( argPtr, fmt );
	
	if ( !vsprintf_s( outBuff, sizeof(outBuff), fmt, argPtr ) ) {
	   return;
	}
	
	_system->GetFontRenderer()->Render( Main::DEBUG_SCREEN_ID, x, y, Main::SYSTEM_FONT_SIZE, Color(0.2f, 0.2f, 0.2f, 1.0f), outBuff );
#endif
}

// システムプリント
void SystemPrint( s32 x, s32 y, Color color, const char* fmt, ... )
{
#if defined(_DEBUG_FUNC_ENABLE)
	NULL_ASSERT( _system );

	char outBuff[512]	= { 0 };
	
	va_list argPtr;
	va_start( argPtr, fmt );
	
	if ( !vsprintf_s( outBuff, sizeof(outBuff), fmt, argPtr ) ) {
	   return;
	}

	_system->GetFontRenderer()->Render( Main::DEBUG_SCREEN_ID, x, y, Main::SYSTEM_FONT_SIZE, color, outBuff );
#endif
}
	
//---------------------------------関数定義---------------------------------



//===========================================================================
/*!	@brief	コンストラクタ
	@param	argc			: プログラム引数
	@param	argv			: プログラム引数
	@param	screenWidth		: スクリーンの幅
	@param	screenHeight	: スクリーンの高さ
	@param	frameRate		: フレームレート
	@param	fullScreen		: フルスクリーン
	@param	appName			: アプリケーション名
*/
//===========================================================================
Main::Main( s32 argc, char** argv, f32 screenWidth, f32 screenHeight, u32 frameRate, bool fullScreen, const char* appName ) :
	m_initParam( argc, argv, screenWidth, screenHeight, frameRate, fullScreen, appName ),
	//m_fieldOfVision( 60.0f ),
	//m_near(1.0f),		// 0より大きい数
	//m_far(3000.0f),
	m_keyboard(NULL),
	m_mouse(NULL),
	m_drawMng(NULL),
	m_cameraMng(NULL)
{
#if defined(_DEBUG_FUNC_ENABLE)
	_system	= this;
#endif
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
Main::~Main()
{
	RenderableTexture::Delete();
}


//===========================================================================
/*!	@brief	初期化
	@param	width	: ウインドウの幅
	@param	height	: ウインドウの高さ
	@return	true:正常	false:異常
*/
//===========================================================================
bool Main::_Init()
{
	// システムの初期化
	m_exit			= false;
	m_prevTime		= 0;
	m_window		= NULL;
	m_fontRenderer	= NULL;
	m_drawPacketMng	= NULL;

	InitializeThread();

	//---------------生成---------------
	m_window		= new Window();
	m_keyboard		= new input::Keyboard();
	m_mouse			= new input::Mouse( m_window );
	m_drawPacketMng	= new graphics::DrawPacketManager();
	m_drawMng		= new graphics::RenderManager();
	m_resourceMng	= new resource::ResourceManager();
	m_screenMng		= new ScreenManager();
	m_cameraMng		= new system::CameraManager();
	m_taskMng		= new system::TaskManager();
	m_socketMng		= new net::SocketManager();

	system::EventGetter::Initialize();

	m_mouse->SetEventGetter( &m_mouseEventGetter );
	m_keyboard->SetEventGetter( &m_keyboardEventGetter );
	

	// 機能ごとの初期化
	bool	initResult = true;
	initResult	&= initResult && _InitSystem();
	initResult	&= initResult && _InitWindow();
	initResult	&= initResult && _InitAudio();
	initResult	&= initResult && _InitApplicationParameter();

	if( initResult == false ) {
		return false;
	}

	m_drawPacketMng->Initialize();
	m_drawPacketMng->SetRenderManager( m_drawMng );
	m_drawMng->Initialize();
	m_socketMng->Initialize();

	//---------------関連付け---------------
	graphics::Sprite::SetResourceManager( m_resourceMng );			// スプライトクラスにリソース管理を関連付け
	graphics::Sprite::SetCameraManager( m_cameraMng );				// カメラをスプライトクラスに登録
	resource::XFile::SetResourceManager( m_resourceMng );			// Xファイルクラスにリソース管理を関連付け
	resource::ToyFile::SetResourceManager( m_resourceMng );			// toystudioクラスにリソース管理を関連付け
	graphics::AnimationModel::SetResourceManager( m_resourceMng );	// アニメーションモデルクラスにリソース管理を関連付け
	graphics::AnimationModel::SetCameraManager( m_cameraMng );		// アニメーションモデルクラスにカメラ管理を関連付け
	BoundaryVolume::SetCameraManager( m_cameraMng );				// 境界ヒットの描画用にカメラをセット
	resource::LoadMqoFile::SetResourceManager( m_resourceMng );		// mqoロードクラスにリソース管理を関連付け
	graphics::RenderModel::SetCameraManager( m_cameraMng );			// モデル描画基底にカメラを関連付け
	graphics::RenderModel::SetResourceManager( m_resourceMng );		// モデル描画基底にリソース管理を関連付け
	graphics::RenderModel::SetDrawPacketManager( m_drawPacketMng );	// モデル描画基底にリソース管理を関連付け
	resource::ResourceLoader::SetResourceMnager( m_resourceMng );	// リソース管理関連付け

// 	graphics::InitializeDefaultButtonInputChecker_Mouse( GetMouse() );

	m_drawMng->LoadShader( new graphics::PhongShader(),		"data/shader/phong.cgfx",			"PhongShader"	);
	m_drawMng->LoadShader( new graphics::ShadowMapping(),	"data/shader/shadowmapping.cgfx",	"ShadowMapping"	);

	// レイアウト管理生成
	LayoutChanger::Initialize();
	
	// タイマーの初期化
	InitializeTimer();
	
#if defined(_DEBUG)
	GetScreen()->CreateScreen( m_initParam.screenWidth, m_initParam.screenHeight, DEBUG_SCREEN_ID );
#endif
	
	// 継承先の初期化
	if( !Initialize() ) {
		return false;
	}

	return true;
}


//===========================================================================
/*!	@brief	終了処理
	@param	なし
	@return	なし
*/
//===========================================================================
void Main::_Term()
{
	// 継承先終了処理
	Terminate();

// 	TerminateDefaultButtonInputChecker_Mouse();

	// レイアウト管理削除
	LayoutChanger::Terminate();

#if defined(_DENUG)
	GetScreen()->DestroyScreen( DEBUG_SCREEN_ID );
#endif

	m_drawMng->DeleteShader();

	SafeDelete( m_keyboard		);
	SafeDelete( m_mouse			);
	SafeDelete( m_drawMng		);
	SafeDelete( m_drawPacketMng	);
	SafeDelete( m_resourceMng	);
	SafeDelete( m_cameraMng		);
	SafeDelete( m_screenMng		);
	SafeDelete( m_window		);
	SafeDelete( m_socketMng		);

	system::EventGetter::Terminate();

	FinalizeThread();
}




//===========================================================================
/*!	@brief	システムの初期化
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_InitSystem( void )
{
#if defined(NK_USE_SDL)

	/* SDLの初期化 */
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) == -1 ) {
		RELEASE_PRINTF("システムの初期化に失敗しました：%s\n", SDL_GetError());
		return false;
	}
	
#elif defined(_WINDOWS)

	glutInit( &m_initParam.argc, m_initParam.argv );
	
#endif

	return true;
}


//===========================================================================
/*!	@brief	ウインドウの初期化
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_InitWindow( void )
{
	NULL_ASSERT( GetWindow() );

	/* ウインドウにタイトルをつける */
	if( m_initParam.strApplicationName ) {
		GetWindow()->SetTitle( m_initParam.strApplicationName );
	}


	// ウインドウの生成
	{
		// コールバック設定
		GetWindow()->SetWindowCallback( _WindowCallback, this );
		
		bool windowResult = GetWindow()->Create( m_initParam.screenWidth, m_initParam.screenHeight, 1.0f, m_initParam.fullScreen );
		if( windowResult == false ) {
			RELEASE_PRINTF( "failed in the initialization window.\n" );
			
			return false;
		}

		// コールバック用
		{
			_SystemPointer registerData;
			registerData.windowHandle	= GetWindow()->GetWindowHandle();
			registerData.system			= this;
			
			_systemPointer.push_back( registerData );
		}

	}
	
#if defined(NK_USE_SDL)	
	
#elif defined(_WINDOWS)
	
#endif

	return true;
}



//===========================================================================
/*!	@brief	システムの初期化
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_InitAudio( void )
{
	sound::SoundManager::Initialize();

#if defined(NK_USE_SDL)
	
#elif defined(_WINDOWS)
	
#endif

	return true;
}



//===========================================================================
/*!	@brief	プログラム設定を初期化
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_InitApplicationParameter( void )
{
	
#if defined(NK_USE_GL)
	/* GLUTの初期化 */
	//glutInit(&m_initParam.argc, m_initParam.argv);

	//その他描画設定
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// 背景を黒に
	glClearDepth(1.0f);						// デプスバッファを初期化
	glDepthFunc(GL_LEQUAL);					// デプスバッファテストを使用する
	glEnable(GL_DEPTH_TEST);				// デプステストを有効にする
	glShadeModel(GL_SMOOTH);				// スムースシェーディング法を使用する。
	glEnable(GL_TEXTURE_2D);				// テクスチャを有効にする

	// パースペクティブ（遠近感）計算をより正確に行う設定にする。
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/* 透過処理 */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//アルファの設定
	glEnable(GL_BLEND);									//アルファのブレンド有効


	//カリング関連
	glEnable(GL_CULL_FACE);					// カリングを有効にする
	glFrontFace(GL_CCW);					// CCW反時計回り、CW時計回り
	glCullFace(GL_BACK);					// 背面ポリゴンを描画しないようにする。


	/* モデルビュー変換 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// 線の設定
	glEnable(GL_LINE_SMOOTH);				// アンチエイリアス
	glLineWidth(1.0f);						// 線の太さ
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	
#endif	// NK_USE_GL

	
#if defined(NK_USE_SDL)
#endif	// NK_USE_SDL

	
#if defined(_WINDOWS)
	
#endif	// _WINDOWS

	/* カメラ行列を設定 */
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	m_cameraMng->Initialize();

	// レンダテクスチャ
	RenderableTexture::Create();


	// フォント
	{
		const s32				characterWidth	= 16;	// 文字幅(px)
		const s32				characterHeight	= 30;	// 文字高さ(px)
		const s32				col				= 16;	// 列
		resource::ImageSurface	surface;				// 画像

 		bool	result	= m_systemFont.RegisterImage( "data/system/fonttable_16x30.png", characterWidth, characterHeight, col );
		if( result == false ) {
			printf("____________________________________\n");
			printf( "error : cannot open font image.\n" );
			printf("____________________________________\n");
		}

		m_fontRenderer	= new font::FontRenderer();
		m_fontRenderer->Register( &m_systemFont );
	}

	m_framerateCalclator.Initialize();
	
	return true;
}



//===========================================================================
/*!	@brief	フレームウェイト
	@param	なし
	@return	なし
*/
//===========================================================================
void Main::_FrameWait()
{
	const s64 NEXT_FRAME_START = m_prevTime + 1000 / m_initParam.frameRate;

	const s64 nowTimeMilSec	= GetTimeMillSec();
	if( 0 < NEXT_FRAME_START - nowTimeMilSec ) {
		//SDL_Delay( NEXT_FRAME_START - nowTimeMilSec );
		SleepThread( NEXT_FRAME_START - nowTimeMilSec );
	}
	
	m_prevTime = GetTimeMillSec();
	
}


//===========================================================================
/*!	@brief	処理を実行
	@param	なし
	@return	true:処理中	false:終了
*/
//===========================================================================
void Main::Run()
{

	if( !_Init() ) {
		return;
	}


	_Loop();
	
	_Term();

}


//===========================================================================
/*!	@brief	初期化
	@param	なし
	@return	正常なのでtrueを返す
*/
//===========================================================================
bool Main::Initialize()
{
	return true;
}


//===========================================================================
/*!	@brief	終了処理
	@param	なし
	@return	なし
*/
//===========================================================================
void Main::Terminate()
{
}


//===========================================================================
/*!	@brief	ループ
	@param	なし
	@return	true:ループ続行	false:ループ終了
*/
//===========================================================================
void Main::_Loop()
{
	m_prevTime = GetTimeMillSec();
	
#if defined(_WINDOWS)

	glutMainLoop();
	
#else
	bool isLoop = true;
	while( isLoop ) {
		isLoop	= _UpdateFrame();
		
		if( IsExit() ) {
			CallbackEvent( SYSTEM_EVENT_EXIT );
			break;
		}

		// フレームウェイト
		_FrameWait();		
	}
#endif

}

//===========================================================================
/*!	@brief	ループ内更新
	@param	なし
	@return	true:ループ続行	false:ループ終了
*/
//===========================================================================
bool Main::_UpdateFrame( void )
{
	bool	isLoop	= true;

	// スレッド再開
	//ReturnAllThread();
	
	// SDLのイベントを取得
	isLoop	= ObtainEvent();

	// イベント更新
	system::EventGetter::GetInstance()->UpdateEvent();
	m_mouseEventGetter.Update();
	m_keyboardEventGetter.Update();
	m_systemEventGetter.Update();

	// キーボードの押下状態を更新
	if( m_keyboard ) {
		m_keyboard->Update();
	}

	// マウスの状態を更新
	if( m_mouse ) {
		m_mouse->Update();
	}

	// スレッド一時停止
	//SuspendAllThread();

	if( m_drawPacketMng ) {
		m_drawPacketMng->ChangeStateDisuseAllPacket();
	}

	{
		AUTO_TIME( GameUpdate );
		isLoop &= Update();
	}
	

	// レイアウト更新
	LayoutChanger::GetInstance()->Update();


#if defined(_DEBUG_FUNC_ENABLE)
	GetScreen()->ClearScreen( DEBUG_SCREEN_ID );
#endif
	DrawInitialize();

	// フレームレート表示
	{
		char	outBuf[256]	= { 0 };
		m_framerateCalclator.UpdateDrawCount();
		sprintf( outBuf, "%s [%.2ffps]", m_initParam.strApplicationName, m_framerateCalclator.GetFramerate() );
		GetWindow()->SetTitle( outBuf );
	}

	
	m_drawMng->Draw( this );	// モデル描画
	

	ChangeMode2D();
	
	DrawTerminate();
	LayoutChanger::GetInstance()->Draw();
	
#if defined(_DEBUG_FUNC_ENABLE)
	GetScreen()->Draw( DEBUG_SCREEN_ID );
#endif
	_SwapBuffers();
	
	// スレッド再開
	//ReturnAllThread();

	//_FrameWait();				// フレームウェイト

	// スレッド一時停止
	//SuspendAllThread();


	return isLoop;
}


//===========================================================================
/*!	@brief	SDLのイベントを取得
	@param	なし
	@return	true:続行	false:終了
*/
//===========================================================================
bool Main::_ObtainSDLEvent( void )
{

	return true;
}



//===========================================================================
/*!	@brief	スクリーンの幅を取得
	@param	なし
	@return	スクリーン幅
*/
//===========================================================================
f32 Main::GetScreenWidth( void ) const
{
	return m_initParam.screenWidth;
}


//===========================================================================
/*!	@brief	スクリーンの高さを取得
	@param	なし
	@return	スクリーン高さ
*/
//===========================================================================
f32 Main::GetScreenHeight() const
{
	return m_initParam.screenHeight;
}


//===========================================================================
/*!	@brief	スクリーンのデプスを取得
	@param	なし
	@return	スクリーンデプス
*/
//===========================================================================
f32 Main::GetScreenDepth() const
{
	return 5000.0f;
}



//===========================================================================
/*!	@brief	軸を描画
	@param	なし
	@return	なし
*/
//===========================================================================
void Main::DrawAxis()
{
	const s32	lineNum			= 20;
	const s32	firstIndex		= -lineNum / 2;
	const s32	lastIndex		= lineNum / 2;
	const f32	lineInterval	= 10.0f;
	const f32	lineLength		= 1000.0f;
	const f32	minPoint		= -lineLength;
	const f32	maxPoint		= lineLength;

	m_line.SetColor( Color( 1.0f, 0.0f, 0.0f, 1.0f ) );

	// x
	for( s32 x = firstIndex; x < lastIndex; ++x ) {
		m_line.ClearPoints();
		m_line.AddPoint( math::Vector( minPoint, x * lineInterval, 0.0f ) );
		m_line.AddPoint( math::Vector( maxPoint, x * lineInterval, 0.0f ) );
		m_line.Draw();
	}

	// y
	for( s32 y = firstIndex; y < lastIndex; ++y ) {
		m_line.ClearPoints();
		m_line.AddPoint( math::Vector( y * lineInterval, minPoint, 0.0f ) );
		m_line.AddPoint( math::Vector( y * lineInterval, maxPoint, 0.0f ) );
		m_line.Draw();
	}

	// z
	m_line.SetColor( Color( 0.0f, 0.0f, 1.0f, 1.0f ) );
	m_line.ClearPoints();
	m_line.AddPoint( math::Vector( 0.0f, 0.0f, minPoint ) );
	m_line.AddPoint( math::Vector( 0.0f, 0.0f, maxPoint ) );
	m_line.Draw();
// 	for( s32 z = firstIndex; z < lastIndex; ++z ) {
// 		m_line.ClearPoints();
// 		m_line.AddPoint( math::Vector( minPoint, 0.0f, z * lineInterval ) );
// 		m_line.AddPoint( math::Vector( maxPoint, 0.0f, z * lineInterval ) );
// 		m_line.Draw();
// 	}
	
#if	0//defined(NK_USE_GL)

	ChangeMode3D();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	math::Matrix44 view = m_cameraMng->GetUseCameraMatrix();
	glLoadMatrixf(view.GetMatrix().ary16);


	glDisable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);

		/* X軸 */
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(5000.0f, 0.0f, 0.0f);

		/* Y軸 */
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 5000, 0.0f);

		/* Z軸 */
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 5000.0f);
		
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnd();
	
#endif

}


//===========================================================================
/*!	@brief	2Dモードに変更
	@param	なし
	@return	なし
*/
//===========================================================================
void Main::ChangeMode2D()
{
#if		defined(NK_USE_GL)
	
	glDisable( GL_DEPTH_TEST );
	
	// カメラ行列を設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const f32	screenWidth		= m_window->GetScreenParam().x;
	const f32	screenHeight	= m_window->GetScreenParam().y;
	const f32	screenDeapth	= m_window->GetScreenParam().z;

	// 正射影設定（画面の見え方）右上原点
	glOrtho(0, screenWidth, screenHeight, 0, 0, 1);


	// パースペクティブ（遠近感）計算をより正確に行う設定にする。
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
#endif

}



//===========================================================================
/*!	@brief	3Dモードに変更
	@param	なし
	@return	なし
*/
//===========================================================================
void Main::ChangeMode3D( void )
{
#if	defined(NK_USE_GL)
	glEnable(GL_DEPTH_TEST);				// デプステストを有効にする

	
	/* カメラ行列を設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const f32	fieldOfVision	= m_cameraMng->GetCurrentFieldOfVision();
	const f32	nearDistance	= m_cameraMng->GetCurrentNearDistance();
	const f32	farDistance		= m_cameraMng->GetCurrentFarDistance();
	const f32	screenWidth		= m_window->GetScreenParam().x;
	const f32	screenHeight	= m_window->GetScreenParam().y;

	/* 透視法射影（右手座標系） */
	gluPerspective( fieldOfVision, screenWidth / screenHeight, nearDistance, farDistance );
	glViewport(0, 0, static_cast<s32>(screenWidth), static_cast<s32>(screenHeight));

	// パースペクティブ（遠近感）計算をより正確に行う設定にする。
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
#endif

}


//===========================================================================
/*!	@brief	カメラマネージャーを習得
	@param	なし
	@return	カメラマネージャー
*/
//===========================================================================
system::CameraManager* Main::GetCameraManager( void ) const
{
	return m_cameraMng;
}


//===========================================================================
/*!	@brief	リソースマネージャーを習得
	@param	なし
	@return	リソースマネージャー
*/
//===========================================================================
resource::ResourceManager* Main::GetResourceManager( void ) const
{
	return m_resourceMng;
}



//===========================================================================
/*!	@brief	描画前処理
	@param	----
	@return	----
*/
//===========================================================================
void Main::DrawInitialize( void )
{
	//glClearColor(1.0, 1.0f, 1.0f, 1.0f);

}


//===========================================================================
/*!	@brief	描画後処理
	@param	----
	@return	----
*/
//===========================================================================
void Main::DrawTerminate( void )
{
	DrawAxis();
}


//===========================================================================
/*!	@brief	スクリーンを習得
	@param	----
	@return	----
*/
//===========================================================================
ScreenManager* Main::GetScreen( void ) const
{
	return m_screenMng;
}


//===========================================================================
/*!	@brief	描画リストにバッファクリア処理を挿入
	@param	priority	: 挿入場所
	@return	なし
*/
//===========================================================================
// void AddListForBufferClear( u32 priority )
// {
// 	graphics::DrawPacket packet;
// 
// 	packet.SetPriority(priority);
// 	packet.AddListForBufferClear();
// }



//===========================================================================
/*!	@brief	描画バッファ入れ替え
	@param	----
	@return	----
*/
//===========================================================================
void Main::_SwapBuffers( void )
{
	
#if	defined(NK_USE_GL) && defined(NK_USE_SDL)
	glFlush();
	SDL_GL_SwapBuffers();

#elif defined(NK_USE_GL)
	//glFlush();
	glutSwapBuffers();
	
#endif
	
}



//===========================================================================
/*!	@brief	イベント取得
	@param	----
	@return	----
*/
//===========================================================================
bool Main::ObtainEvent( void )
{
	if( system::EventGetter::GetInstance()->GetSystemEvent().IsOn( system::SystemEvent::QUIT ) ) {
		return false;
	}

	
	return true;
}




//===========================================================================
/*!	@brief	プロセスのインスタンスを習得
	@param	----
	@return	----
*/
//===========================================================================
NK_PROCESS_INSTANCE Main::GetProcessInstance( void )
{
#if defined(_WINDOWS)
	return GetModuleHandle(0);	// windowsAPI
#endif

	return 0;
}



//===========================================================================
/*!	@brief	
	@param	----
	@return	----
*/
//===========================================================================
math::Matrix44 Main::GetPerspectiveFieldOfView( void ) const
{
	const f32			fieldOfVision	= m_cameraMng->GetCurrentFieldOfVision();
	const f32			nearDistance	= m_cameraMng->GetCurrentNearDistance();
	const f32			farDistance		= m_cameraMng->GetCurrentFarDistance();
	const math::Vector	screenParam		= m_window->GetScreenParam();

	return math::CreatePerspectiveFieldOfView( fieldOfVision, screenParam.x / screenParam.y, nearDistance, farDistance );
}




//===========================================================================
/*!	@brief	ウインドウハンドルを習得
	@param	----
	@return	----
*/
//===========================================================================
NK_WINDOW_HANDLE Main::GetWindowHandle( void ) const
{
	NULL_ASSERT( m_window );

	return m_window->GetWindowHandle();
}


//===========================================================================
/*!	@brief	ウインドウを取得
	@param	----
	@return	----
*/
//===========================================================================
Window* Main::GetWindow( void ) const
{
	
	return m_window;
}


//===========================================================================
/*!	@brief	タスクマネージャーを取得
	@param	----
	@return	----
*/
//===========================================================================
system::TaskManager* Main::GetTaskManager( void ) const
{
	
	return m_taskMng;
}

//===========================================================================
/*!	@brief	更新コールバック
	@param	----
	@return	----
*/
//===========================================================================
void Main::UpdateCallback( void )
{
	if( _Updateable() ) {

		//m_prevTime		+= GetUpdateIntervalMillSec();
		m_prevTime		= GetTimeMillSec();
#if 1
		bool	loop	= _UpdateFrame();

		if( loop == false ) {
			Exit();
		}
#else
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
		glFlush();

#endif
	}
	
}


//===========================================================================
/*!	@brief	更新フレームならtrue
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_Updateable( void ) const
{
	u64	nowMillSec	= GetTimeMillSec();
	u64	nextMillSec	= m_prevTime + GetUpdateIntervalMillSec();
	
	if( nextMillSec <= nowMillSec ) {
		return true;
	}

	return false;
}



//===========================================================================
/*!	@brief	更新間隔を取得
	@param	----
	@return	----
*/
//===========================================================================
u32 Main::GetUpdateIntervalMillSec( void ) const
{

	return 1000 / m_initParam.frameRate;
}


//===========================================================================
/*!	@brief	終了
	@param	----
	@return	----
*/
//===========================================================================
void Main::Exit( void )
{
	m_exit	= true;
}

	
//===========================================================================
/*!	@brief	終了ならtrue
	@param	----
	@return	----
*/
//===========================================================================
bool Main::IsExit( void ) const
{
	
	return m_exit;
}

	
//===========================================================================
/*!	@brief	システムフォントレンダラ
	@param	----
	@return	----
*/
//===========================================================================
font::FontRenderer* Main::GetFontRenderer( void ) const
{
	
	return m_fontRenderer;
}

//===========================================================================
/*!	@brief		キーボード取得
	@param		----
	@return		----
*/
//===========================================================================
input::Keyboard* Main::GetKeyboard( void ) const
{

	return m_keyboard;
}

//===========================================================================
/*!	@brief		マウス取得
	@param		----
	@return		----
*/
//===========================================================================
input::Mouse* Main::GetMouse( void ) const
{

	return m_mouse;
}


	
//}	// namespace system
}	// namespace nk
