//=============================================================================
/*!	@file	system.cpp

	/*!	@brief	���C���N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
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

//------------------------------�ÓI�����o��`------------------------------
const f32	Main::DEFAULT_SCREEN_WIDTH		= 1024;
const f32	Main::DEFAULT_SCREEN_HEIGHT		= 768;
const s32	Main::DEFAULT_FRAME_RATE		= 30;
const s32	Main::SYSTEM_FONT_SIZE			= 8;


namespace {

	
// �E�C���h�E�R�[���o�b�N���ɎQ�Ƃ���|�C���^
struct _SystemPointer {
	NK_WINDOW_HANDLE	windowHandle;	// �E�C���h�E���ʃn���h��
	Main*				system;			// �V�X�e���ւ̃|�C���^

	_SystemPointer() {
		system	= NULL;
	}
};

std::vector<_SystemPointer>		_systemPointer;	// �V�X�e���ւ̎Q��


// �f�o�b�O�p
#if defined(_DEBUG_FUNC_ENABLE)
Main*		_system	= NULL;
#endif

}	// unnamed


//--------------------------------static�֐�--------------------------------

namespace {

//===========================================================================
/*!	@brief	�E�C���h�E�R�[���o�b�N
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
/*!	@brief	�E�C���h�E�R�[���o�b�N
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


		// �摜�Ǎ��݃X���b�h�쐬
		if( 1 )
		{
			g_bThreadFinish = false;
			wglMakeCurrent( NULL, NULL );

			/* �X���b�h�p�p�����[�^ */
			HANDLE	hWnd;
			DWORD	dwID;
			//CreateThread( NULL, 0, ThreadFunc, (LPVOID)hWnd, 0, &dwID );
			CreateThread( NULL, 0, ThreadFunc, NULL, 0, &dwID );
		}
		
		
 		pngInfo info;
 		g_nTextureId	= pngBind( "ika.png", PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST );

		return 0;

	case WM_PAINT:

		// �����_�����O�R���e�L�X�g��߂�
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

				glEnable( GL_CULL_FACE );				// �J�����O��L���ɂ���
				glFrontFace( GL_CCW );					// CCW�����v���ACW���v���
				glCullFace( GL_BACK );					// �w�ʃ|���S����`�悵�Ȃ��悤�ɂ���B
				glEnable( GL_TEXTURE_2D );				//�e�N�X�`��ON
				
				
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

// �V�X�e���v�����g
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

// �V�X�e���v�����g
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
	
//---------------------------------�֐���`---------------------------------



//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	argc			: �v���O��������
	@param	argv			: �v���O��������
	@param	screenWidth		: �X�N���[���̕�
	@param	screenHeight	: �X�N���[���̍���
	@param	frameRate		: �t���[�����[�g
	@param	fullScreen		: �t���X�N���[��
	@param	appName			: �A�v���P�[�V������
*/
//===========================================================================
Main::Main( s32 argc, char** argv, f32 screenWidth, f32 screenHeight, u32 frameRate, bool fullScreen, const char* appName ) :
	m_initParam( argc, argv, screenWidth, screenHeight, frameRate, fullScreen, appName ),
	//m_fieldOfVision( 60.0f ),
	//m_near(1.0f),		// 0���傫����
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
/*!	@brief	�f�X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Main::~Main()
{
	RenderableTexture::Delete();
}


//===========================================================================
/*!	@brief	������
	@param	width	: �E�C���h�E�̕�
	@param	height	: �E�C���h�E�̍���
	@return	true:����	false:�ُ�
*/
//===========================================================================
bool Main::_Init()
{
	// �V�X�e���̏�����
	m_exit			= false;
	m_prevTime		= 0;
	m_window		= NULL;
	m_fontRenderer	= NULL;
	m_drawPacketMng	= NULL;

	InitializeThread();

	//---------------����---------------
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
	

	// �@�\���Ƃ̏�����
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

	//---------------�֘A�t��---------------
	graphics::Sprite::SetResourceManager( m_resourceMng );			// �X�v���C�g�N���X�Ƀ��\�[�X�Ǘ����֘A�t��
	graphics::Sprite::SetCameraManager( m_cameraMng );				// �J�������X�v���C�g�N���X�ɓo�^
	resource::XFile::SetResourceManager( m_resourceMng );			// X�t�@�C���N���X�Ƀ��\�[�X�Ǘ����֘A�t��
	resource::ToyFile::SetResourceManager( m_resourceMng );			// toystudio�N���X�Ƀ��\�[�X�Ǘ����֘A�t��
	graphics::AnimationModel::SetResourceManager( m_resourceMng );	// �A�j���[�V�������f���N���X�Ƀ��\�[�X�Ǘ����֘A�t��
	graphics::AnimationModel::SetCameraManager( m_cameraMng );		// �A�j���[�V�������f���N���X�ɃJ�����Ǘ����֘A�t��
	BoundaryVolume::SetCameraManager( m_cameraMng );				// ���E�q�b�g�̕`��p�ɃJ�������Z�b�g
	resource::LoadMqoFile::SetResourceManager( m_resourceMng );		// mqo���[�h�N���X�Ƀ��\�[�X�Ǘ����֘A�t��
	graphics::RenderModel::SetCameraManager( m_cameraMng );			// ���f���`����ɃJ�������֘A�t��
	graphics::RenderModel::SetResourceManager( m_resourceMng );		// ���f���`����Ƀ��\�[�X�Ǘ����֘A�t��
	graphics::RenderModel::SetDrawPacketManager( m_drawPacketMng );	// ���f���`����Ƀ��\�[�X�Ǘ����֘A�t��
	resource::ResourceLoader::SetResourceMnager( m_resourceMng );	// ���\�[�X�Ǘ��֘A�t��

// 	graphics::InitializeDefaultButtonInputChecker_Mouse( GetMouse() );

	m_drawMng->LoadShader( new graphics::PhongShader(),		"data/shader/phong.cgfx",			"PhongShader"	);
	m_drawMng->LoadShader( new graphics::ShadowMapping(),	"data/shader/shadowmapping.cgfx",	"ShadowMapping"	);

	// ���C�A�E�g�Ǘ�����
	LayoutChanger::Initialize();
	
	// �^�C�}�[�̏�����
	InitializeTimer();
	
#if defined(_DEBUG)
	GetScreen()->CreateScreen( m_initParam.screenWidth, m_initParam.screenHeight, DEBUG_SCREEN_ID );
#endif
	
	// �p����̏�����
	if( !Initialize() ) {
		return false;
	}

	return true;
}


//===========================================================================
/*!	@brief	�I������
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Main::_Term()
{
	// �p����I������
	Terminate();

// 	TerminateDefaultButtonInputChecker_Mouse();

	// ���C�A�E�g�Ǘ��폜
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
/*!	@brief	�V�X�e���̏�����
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_InitSystem( void )
{
#if defined(NK_USE_SDL)

	/* SDL�̏����� */
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) == -1 ) {
		RELEASE_PRINTF("�V�X�e���̏������Ɏ��s���܂����F%s\n", SDL_GetError());
		return false;
	}
	
#elif defined(_WINDOWS)

	glutInit( &m_initParam.argc, m_initParam.argv );
	
#endif

	return true;
}


//===========================================================================
/*!	@brief	�E�C���h�E�̏�����
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_InitWindow( void )
{
	NULL_ASSERT( GetWindow() );

	/* �E�C���h�E�Ƀ^�C�g�������� */
	if( m_initParam.strApplicationName ) {
		GetWindow()->SetTitle( m_initParam.strApplicationName );
	}


	// �E�C���h�E�̐���
	{
		// �R�[���o�b�N�ݒ�
		GetWindow()->SetWindowCallback( _WindowCallback, this );
		
		bool windowResult = GetWindow()->Create( m_initParam.screenWidth, m_initParam.screenHeight, 1.0f, m_initParam.fullScreen );
		if( windowResult == false ) {
			RELEASE_PRINTF( "failed in the initialization window.\n" );
			
			return false;
		}

		// �R�[���o�b�N�p
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
/*!	@brief	�V�X�e���̏�����
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
/*!	@brief	�v���O�����ݒ��������
	@param	----
	@return	----
*/
//===========================================================================
bool Main::_InitApplicationParameter( void )
{
	
#if defined(NK_USE_GL)
	/* GLUT�̏����� */
	//glutInit(&m_initParam.argc, m_initParam.argv);

	//���̑��`��ݒ�
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// �w�i������
	glClearDepth(1.0f);						// �f�v�X�o�b�t�@��������
	glDepthFunc(GL_LEQUAL);					// �f�v�X�o�b�t�@�e�X�g���g�p����
	glEnable(GL_DEPTH_TEST);				// �f�v�X�e�X�g��L���ɂ���
	glShadeModel(GL_SMOOTH);				// �X���[�X�V�F�[�f�B���O�@���g�p����B
	glEnable(GL_TEXTURE_2D);				// �e�N�X�`����L���ɂ���

	// �p�[�X�y�N�e�B�u�i���ߊ��j�v�Z����萳�m�ɍs���ݒ�ɂ���B
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/* ���ߏ��� */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//�A���t�@�̐ݒ�
	glEnable(GL_BLEND);									//�A���t�@�̃u�����h�L��


	//�J�����O�֘A
	glEnable(GL_CULL_FACE);					// �J�����O��L���ɂ���
	glFrontFace(GL_CCW);					// CCW�����v���ACW���v���
	glCullFace(GL_BACK);					// �w�ʃ|���S����`�悵�Ȃ��悤�ɂ���B


	/* ���f���r���[�ϊ� */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// ���̐ݒ�
	glEnable(GL_LINE_SMOOTH);				// �A���`�G�C���A�X
	glLineWidth(1.0f);						// ���̑���
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	
#endif	// NK_USE_GL

	
#if defined(NK_USE_SDL)
#endif	// NK_USE_SDL

	
#if defined(_WINDOWS)
	
#endif	// _WINDOWS

	/* �J�����s���ݒ� */
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	m_cameraMng->Initialize();

	// �����_�e�N�X�`��
	RenderableTexture::Create();


	// �t�H���g
	{
		const s32				characterWidth	= 16;	// ������(px)
		const s32				characterHeight	= 30;	// ��������(px)
		const s32				col				= 16;	// ��
		resource::ImageSurface	surface;				// �摜

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
/*!	@brief	�t���[���E�F�C�g
	@param	�Ȃ�
	@return	�Ȃ�
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
/*!	@brief	���������s
	@param	�Ȃ�
	@return	true:������	false:�I��
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
/*!	@brief	������
	@param	�Ȃ�
	@return	����Ȃ̂�true��Ԃ�
*/
//===========================================================================
bool Main::Initialize()
{
	return true;
}


//===========================================================================
/*!	@brief	�I������
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Main::Terminate()
{
}


//===========================================================================
/*!	@brief	���[�v
	@param	�Ȃ�
	@return	true:���[�v���s	false:���[�v�I��
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

		// �t���[���E�F�C�g
		_FrameWait();		
	}
#endif

}

//===========================================================================
/*!	@brief	���[�v���X�V
	@param	�Ȃ�
	@return	true:���[�v���s	false:���[�v�I��
*/
//===========================================================================
bool Main::_UpdateFrame( void )
{
	bool	isLoop	= true;

	// �X���b�h�ĊJ
	//ReturnAllThread();
	
	// SDL�̃C�x���g���擾
	isLoop	= ObtainEvent();

	// �C�x���g�X�V
	system::EventGetter::GetInstance()->UpdateEvent();
	m_mouseEventGetter.Update();
	m_keyboardEventGetter.Update();
	m_systemEventGetter.Update();

	// �L�[�{�[�h�̉�����Ԃ��X�V
	if( m_keyboard ) {
		m_keyboard->Update();
	}

	// �}�E�X�̏�Ԃ��X�V
	if( m_mouse ) {
		m_mouse->Update();
	}

	// �X���b�h�ꎞ��~
	//SuspendAllThread();

	if( m_drawPacketMng ) {
		m_drawPacketMng->ChangeStateDisuseAllPacket();
	}

	{
		AUTO_TIME( GameUpdate );
		isLoop &= Update();
	}
	

	// ���C�A�E�g�X�V
	LayoutChanger::GetInstance()->Update();


#if defined(_DEBUG_FUNC_ENABLE)
	GetScreen()->ClearScreen( DEBUG_SCREEN_ID );
#endif
	DrawInitialize();

	// �t���[�����[�g�\��
	{
		char	outBuf[256]	= { 0 };
		m_framerateCalclator.UpdateDrawCount();
		sprintf( outBuf, "%s [%.2ffps]", m_initParam.strApplicationName, m_framerateCalclator.GetFramerate() );
		GetWindow()->SetTitle( outBuf );
	}

	
	m_drawMng->Draw( this );	// ���f���`��
	

	ChangeMode2D();
	
	DrawTerminate();
	LayoutChanger::GetInstance()->Draw();
	
#if defined(_DEBUG_FUNC_ENABLE)
	GetScreen()->Draw( DEBUG_SCREEN_ID );
#endif
	_SwapBuffers();
	
	// �X���b�h�ĊJ
	//ReturnAllThread();

	//_FrameWait();				// �t���[���E�F�C�g

	// �X���b�h�ꎞ��~
	//SuspendAllThread();


	return isLoop;
}


//===========================================================================
/*!	@brief	SDL�̃C�x���g���擾
	@param	�Ȃ�
	@return	true:���s	false:�I��
*/
//===========================================================================
bool Main::_ObtainSDLEvent( void )
{

	return true;
}



//===========================================================================
/*!	@brief	�X�N���[���̕����擾
	@param	�Ȃ�
	@return	�X�N���[����
*/
//===========================================================================
f32 Main::GetScreenWidth( void ) const
{
	return m_initParam.screenWidth;
}


//===========================================================================
/*!	@brief	�X�N���[���̍������擾
	@param	�Ȃ�
	@return	�X�N���[������
*/
//===========================================================================
f32 Main::GetScreenHeight() const
{
	return m_initParam.screenHeight;
}


//===========================================================================
/*!	@brief	�X�N���[���̃f�v�X���擾
	@param	�Ȃ�
	@return	�X�N���[���f�v�X
*/
//===========================================================================
f32 Main::GetScreenDepth() const
{
	return 5000.0f;
}



//===========================================================================
/*!	@brief	����`��
	@param	�Ȃ�
	@return	�Ȃ�
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

		/* X�� */
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(5000.0f, 0.0f, 0.0f);

		/* Y�� */
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 5000, 0.0f);

		/* Z�� */
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 5000.0f);
		
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnd();
	
#endif

}


//===========================================================================
/*!	@brief	2D���[�h�ɕύX
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Main::ChangeMode2D()
{
#if		defined(NK_USE_GL)
	
	glDisable( GL_DEPTH_TEST );
	
	// �J�����s���ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const f32	screenWidth		= m_window->GetScreenParam().x;
	const f32	screenHeight	= m_window->GetScreenParam().y;
	const f32	screenDeapth	= m_window->GetScreenParam().z;

	// ���ˉe�ݒ�i��ʂ̌������j�E�㌴�_
	glOrtho(0, screenWidth, screenHeight, 0, 0, 1);


	// �p�[�X�y�N�e�B�u�i���ߊ��j�v�Z����萳�m�ɍs���ݒ�ɂ���B
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
#endif

}



//===========================================================================
/*!	@brief	3D���[�h�ɕύX
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Main::ChangeMode3D( void )
{
#if	defined(NK_USE_GL)
	glEnable(GL_DEPTH_TEST);				// �f�v�X�e�X�g��L���ɂ���

	
	/* �J�����s���ݒ� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const f32	fieldOfVision	= m_cameraMng->GetCurrentFieldOfVision();
	const f32	nearDistance	= m_cameraMng->GetCurrentNearDistance();
	const f32	farDistance		= m_cameraMng->GetCurrentFarDistance();
	const f32	screenWidth		= m_window->GetScreenParam().x;
	const f32	screenHeight	= m_window->GetScreenParam().y;

	/* �����@�ˉe�i�E����W�n�j */
	gluPerspective( fieldOfVision, screenWidth / screenHeight, nearDistance, farDistance );
	glViewport(0, 0, static_cast<s32>(screenWidth), static_cast<s32>(screenHeight));

	// �p�[�X�y�N�e�B�u�i���ߊ��j�v�Z����萳�m�ɍs���ݒ�ɂ���B
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
#endif

}


//===========================================================================
/*!	@brief	�J�����}�l�[�W���[���K��
	@param	�Ȃ�
	@return	�J�����}�l�[�W���[
*/
//===========================================================================
system::CameraManager* Main::GetCameraManager( void ) const
{
	return m_cameraMng;
}


//===========================================================================
/*!	@brief	���\�[�X�}�l�[�W���[���K��
	@param	�Ȃ�
	@return	���\�[�X�}�l�[�W���[
*/
//===========================================================================
resource::ResourceManager* Main::GetResourceManager( void ) const
{
	return m_resourceMng;
}



//===========================================================================
/*!	@brief	�`��O����
	@param	----
	@return	----
*/
//===========================================================================
void Main::DrawInitialize( void )
{
	//glClearColor(1.0, 1.0f, 1.0f, 1.0f);

}


//===========================================================================
/*!	@brief	�`��㏈��
	@param	----
	@return	----
*/
//===========================================================================
void Main::DrawTerminate( void )
{
	DrawAxis();
}


//===========================================================================
/*!	@brief	�X�N���[�����K��
	@param	----
	@return	----
*/
//===========================================================================
ScreenManager* Main::GetScreen( void ) const
{
	return m_screenMng;
}


//===========================================================================
/*!	@brief	�`�惊�X�g�Ƀo�b�t�@�N���A������}��
	@param	priority	: �}���ꏊ
	@return	�Ȃ�
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
/*!	@brief	�`��o�b�t�@����ւ�
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
/*!	@brief	�C�x���g�擾
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
/*!	@brief	�v���Z�X�̃C���X�^���X���K��
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
/*!	@brief	�E�C���h�E�n���h�����K��
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
/*!	@brief	�E�C���h�E���擾
	@param	----
	@return	----
*/
//===========================================================================
Window* Main::GetWindow( void ) const
{
	
	return m_window;
}


//===========================================================================
/*!	@brief	�^�X�N�}�l�[�W���[���擾
	@param	----
	@return	----
*/
//===========================================================================
system::TaskManager* Main::GetTaskManager( void ) const
{
	
	return m_taskMng;
}

//===========================================================================
/*!	@brief	�X�V�R�[���o�b�N
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
/*!	@brief	�X�V�t���[���Ȃ�true
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
/*!	@brief	�X�V�Ԋu���擾
	@param	----
	@return	----
*/
//===========================================================================
u32 Main::GetUpdateIntervalMillSec( void ) const
{

	return 1000 / m_initParam.frameRate;
}


//===========================================================================
/*!	@brief	�I��
	@param	----
	@return	----
*/
//===========================================================================
void Main::Exit( void )
{
	m_exit	= true;
}

	
//===========================================================================
/*!	@brief	�I���Ȃ�true
	@param	----
	@return	----
*/
//===========================================================================
bool Main::IsExit( void ) const
{
	
	return m_exit;
}

	
//===========================================================================
/*!	@brief	�V�X�e���t�H���g�����_��
	@param	----
	@return	----
*/
//===========================================================================
font::FontRenderer* Main::GetFontRenderer( void ) const
{
	
	return m_fontRenderer;
}

//===========================================================================
/*!	@brief		�L�[�{�[�h�擾
	@param		----
	@return		----
*/
//===========================================================================
input::Keyboard* Main::GetKeyboard( void ) const
{

	return m_keyboard;
}

//===========================================================================
/*!	@brief		�}�E�X�擾
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
