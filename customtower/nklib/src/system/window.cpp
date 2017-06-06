//=============================================================================
/*!	@file	window.cpp

	@brief	�E�C���h�E���Ǘ�����N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
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

_VecWindowCallbackHandle					_vecWindowCallbackHandle;	// �E�C���h�E�n���h��


// �R�[���o�b�N�o�^
void _AddWindowCallback( nk::Window* window, nk::WindowCallback func, void* param )
{
	_WindowCallbackHandle	handle;
	handle.Init( window, func, param );
	
	_vecWindowCallbackHandle.push_back( handle );
	
}



// �E�C���h�E�R�[���o�b�N
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
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Window::Window()
{
	_Initialize();	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Window::~Window()
{
	_Finalize();
}


//===========================================================================
/*!	@brief	������
	@param	�Ȃ�
*/
//===========================================================================
void Window::_Initialize( void )
{
	
}



//===========================================================================
/*!	@brief	�I��
	@param	�Ȃ�
*/
//===========================================================================
void Window::_Finalize( void )
{
	
}


//===========================================================================
/*!	@brief	������
	@param	width			: �X�N���[���̕�
	@param	height			: �X�N���[���̍���
	@param	depth			: �X�N���[���[�x
	@param	fullscreen		: true.�t���X�N���[��
	@return	true.����		false.���s
*/
//===========================================================================
bool Window::Create( s32 width, s32 height, f32 depth, bool fullscreen )
{
	m_screenWidth		= static_cast<f32>(width);
	m_screenHeight		= static_cast<f32>(height);
	m_screenDepth		= depth;
	m_fullScreen		= fullscreen;
	
	
#if defined(NK_USE_SDLGL)
	
	/* ��ʂ������� */
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,	8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,	8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,	8 );


	/* �[�x�o�b�t�@�ƃ_�u���o�b�t�@�����O�̐ݒ� */
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 	32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,	1  );


	/* �X�N���[���̐ݒ� */
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
		RELEASE_PRINTF("failed in the initialization window �F%s\n", SDL_GetError());
		return false;
	}


	/* �T�[�t�F�X���g�p���邽�߂Ƀ��`�����l�������������Ă��� */
	SDL_FillRect( screen, NULL, SDL_MapRGBA( screen->format, 0, 0, 0, 0) );


#elif defined(_WINDOWS)

	// glut
#if _WINDOW_TYPE_GLUT

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( m_screenWidth, m_screenHeight );
	glutCreateWindow( "" );

	glutDisplayFunc( _GlutDysplayCallback );
	
	// win api
	// �G���[�o�܂�
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
		TEXT("OpenGL�\���e�X�g"),
		//WS_OVERLAPPEDWINDOW,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,   // �E�B���h�E�T�C�Y�Œ�
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		Main::GetProcessInstance(),
		NULL
	);
	

	s32 windowSize	= fullscreen ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL;	// �E�C���h�E�T�C�Y

	ShowWindow( m_windowHandle, windowSize );	// �E�C���h�E��\��
	UpdateWindow( m_windowHandle );				// �ĕ`��
#endif
	
#endif	// _WINDOWS

	return true;
}


//===========================================================================
/*!	@brief	�^�C�g���ݒ�
	@param	title	�Z�b�g����^�C�g��
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
/*!	@brief	���E�����E�[�x���K��
	@param	----
	@return	----
*/
//===========================================================================
math::Vector Window::GetScreenParam( void ) const
{

	return math::Vector( m_screenWidth, m_screenHeight, m_screenDepth );
}



//===========================================================================
/*!	@brief	���E�����E�[�x���K��
	@param	----
	@return	----
*/
//===========================================================================
NK_WINDOW_HANDLE Window::GetWindowHandle( void ) const
{

	return m_windowHandle;
}



//===========================================================================
/*!	@brief	�r���[�|�[�g�s����K��
	@param	�Ȃ�
	@return	�r���[�|�[�g�s��
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
/*!	@brief	�R�[���o�b�N�ݒ�
	@param	func	�R�[���o�b�N�֐�
	@param	param	����
	@return	----
*/
//===========================================================================
void Window::SetWindowCallback( WindowCallback func, void* param )
{
	_AddWindowCallback( this, func, param );
	
}
	
}