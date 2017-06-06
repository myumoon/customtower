//=============================================================================
/*!	@file	window.cpp

	@brief	ウインドウを管理するクラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/system/window.h"
#include "../../include/project.h"


#define _WINDOW_TYPE_GLUT		0
#define _WINDOW_TYPE_WINAPI		!(_WINDOW_TYPE_GLUT)

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
#include <gl/gl.h>

#elif defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#endif
#include "../../include/math/vector.h"
#include "../../include/system.h"

namespace {

LRESULT CALLBACK _WindowCallback( HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc( hwnd, iMsg, wParam, lParam );
}


struct _WindowCallbackHandle {
	nk::Window*			window;
	nk::WindowCallback	func;
	void*				param;

	void Init( nk::Window* window, nk::WindowCallback func, void* param )
	{
		this->window	= window;
		this->func		= func;
		this->param		= param;
	}
	
};

typedef std::vector<_WindowCallbackHandle>	_VecWindowCallbackHandle;

_VecWindowCallbackHandle					_vecWindowCallbackHandle;	// ウインドウハンドル


// コールバック登録
void _AddWindowCallback( nk::Window* window, nk::WindowCallback func, void* param )
{
	_WindowCallbackHandle	handle;
	handle.Init( window, func, param );
	
	_vecWindowCallbackHandle.push_back( handle );
	
}



// ウインドウコールバック
void _GlutDysplayCallback( void )
{
	_VecWindowCallbackHandle::iterator	itr	= _vecWindowCallbackHandle.begin();
	_VecWindowCallbackHandle::iterator	end	= _vecWindowCallbackHandle.end();
	for( ; itr != end; ++itr ) {
		if( (*itr).func ) {
			((*itr).func)( (*itr).param );
		}
	}
	
}

	


}	// unnamed



namespace nk {

	

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Window::Window()
{
	_Initialize();	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
Window::~Window()
{
	_Finalize();
}


//===========================================================================
/*!	@brief	初期化
	@param	なし
*/
//===========================================================================
void Window::_Initialize( void )
{
	
}



//===========================================================================
/*!	@brief	終了
	@param	なし
*/
//===========================================================================
void Window::_Finalize( void )
{
	
}


//===========================================================================
/*!	@brief	初期化
	@param	width			: スクリーンの幅
	@param	height			: スクリーンの高さ
	@param	depth			: スクリーン深度
	@param	fullscreen		: true.フルスクリーン
	@return	true.成功		false.失敗
*/
//===========================================================================
bool Window::Create( s32 width, s32 height, f32 depth, bool fullscreen )
{
	m_screenWidth		= static_cast<f32>(width);
	m_screenHeight		= static_cast<f32>(height);
	m_screenDepth		= depth;
	m_fullScreen		= fullscreen;
	
	
#if defined(NK_USE_SDLGL)
	
	/* 画面を初期化 */
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,	8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,	8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,	8 );


	/* 深度バッファとダブルバッファリングの設定 */
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 	32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,	1  );


	/* スクリーンの設定 */
	Uint32 Vflags;
	if( m_fullScreen ) {
		Vflags = SDL_HWSURFACE | SDL_OPENGLBLIT | SDL_FULLSCREEN;
	} else {
		Vflags = SDL_HWSURFACE | SDL_OPENGLBLIT;
	}

	SDL_Surface* screen = SDL_SetVideoMode(
		static_cast<s32>(m_screenWidth),
		static_cast<s32>(m_screenHeight),
		32,
		Vflags
	);
	if( !screen ) {
		RELEASE_PRINTF("failed in the initialization window ：%s\n", SDL_GetError());
		return false;
	}


	/* サーフェスを使用するためにαチャンネルを初期化しておく */
	SDL_FillRect( screen, NULL, SDL_MapRGBA( screen->format, 0, 0, 0, 0) );


#elif defined(_WINDOWS)

	// glut
#if _WINDOW_TYPE_GLUT

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( m_screenWidth, m_screenHeight );
	glutCreateWindow( "" );

	glutDisplayFunc( _GlutDysplayCallback );
	
	// win api
	// エラー出ます
#elif _WINDOW_TYPE_WINAPI
	
	//@@@@@
	m_windowClass.style         = CS_HREDRAW | CS_VREDRAW;
	m_windowClass.lpfnWndProc   = _WindowCallback;
	//m_windowClass.lpfnWndProc   = NULL;
	m_windowClass.cbClsExtra    = 0;
	m_windowClass.cbWndExtra    = 0;
	m_windowClass.hInstance     = Main::GetProcessInstance();
	m_windowClass.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
	m_windowClass.hCursor       = LoadCursor( NULL, IDC_ARROW );
	m_windowClass.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	m_windowClass.lpszMenuName  = NULL;
	//m_windowClass.lpszClassName = L"CWindow";
	m_windowClass.lpszClassName = "CWindow";

	RegisterClass( &m_windowClass );

	m_windowHandle	= CreateWindow (
		TEXT("CWindow"),
		TEXT("OpenGL表示テスト"),
		//WS_OVERLAPPEDWINDOW,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,   // ウィンドウサイズ固定
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		Main::GetProcessInstance(),
		NULL
	);
	

	s32 windowSize	= fullscreen ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL;	// ウインドウサイズ

	ShowWindow( m_windowHandle, windowSize );	// ウインドウを表示
	UpdateWindow( m_windowHandle );				// 再描画
#endif
	
#endif	// _WINDOWS

	return true;
}


//===========================================================================
/*!	@brief	タイトル設定
	@param	title	セットするタイトル
	@return	----
*/
//===========================================================================
void Window::SetTitle( const char* title )
{
#if defined(NK_USE_SDL)
	SDL_WM_SetCaption( title, NULL );
	
#elif defined(_WINDOWS)
#endif
}


//===========================================================================
/*!	@brief	幅・高さ・深度を習得
	@param	----
	@return	----
*/
//===========================================================================
math::Vector Window::GetScreenParam( void ) const
{

	return math::Vector( m_screenWidth, m_screenHeight, m_screenDepth );
}



//===========================================================================
/*!	@brief	幅・高さ・深度を習得
	@param	----
	@return	----
*/
//===========================================================================
NK_WINDOW_HANDLE Window::GetWindowHandle( void ) const
{

	return m_windowHandle;
}



//===========================================================================
/*!	@brief	ビューポート行列を習得
	@param	なし
	@return	ビューポート行列
*/
//===========================================================================
math::Matrix44 Window::GetViewPortMatrix( void ) const
{
	const f32 w = m_screenWidth;
	const f32 h = m_screenHeight;

	return math::Matrix44(
		w / 2.0f,	0.0,		0.0,	0.0,
		0.0,		-h / 2.0f,	0.0,	0.0,
		0.0,		0.0,		1.0,	0.0,
		w / 2.0f,	h / 2.0f,	0.0,	1.0
	);
}


//===========================================================================
/*!	@brief	コールバック設定
	@param	func	コールバック関数
	@param	param	引数
	@return	----
*/
//===========================================================================
void Window::SetWindowCallback( WindowCallback func, void* param )
{
	_AddWindowCallback( this, func, param );
	
}
	
}