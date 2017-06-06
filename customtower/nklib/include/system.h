//=============================================================================
/*!	@file	system.h

	@brief	���C���N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __SYSTEM_H__
#define __SYSTEM_H__


#include <new.h>
#include <new>
#include <string>
#include <iostream>
#include <list>
#include <vector>

#include "./typedef.h"

#include "./general.h"
#include "./utility/utility.h"

#include "./debug/debugfunction.h"
#include "./debug/layoutChanger.h"


#include "./project.h"

#include "./system/window.h"
#include "./system/camera.h"
#include "./system/cameraManager.h"
#include "./system/task.h"
#include "./system/treeTask.h"
#include "./system/listTask.h"
#include "./system/taskManager.h"
#include "./system/framerateCalclator.h"

#include "./font/font.h"
#include "./font/fontRenderer.h"

#include "./math/math.h"
#include "./math/vector.h"
#include "./math/matrix.h"

#include "./graphics/attitude.h"

#include "./collision/boundaryVolume.h"

#include "./input/keyboard.h"
#include "./input/mouse.h"
#include "./system/eventGetter.h"
#include "./system/mouseEventGetter.h"
#include "./system/keyboardEventGetter.h"
#include "./system/systemEventGetter.h"

#include "./graphics/graphics.h"
#include "./resource/material.h"
#include "./resource/texture.h"
#include "./resource/resourceLoader.h"
#include "./render/renderManager.h"
#include "./resource/resourcemanager.h"
#include "./shader/shader.h"
#include "./shader/phongShader.h"
#include "./shader/shadowMapping.h"
#include "./render/screenManager.h"
#include "./render/drawPacketManager.h"
#include "./sound/soundManager.h"

#include "./resource/renderableTexture.h"

#include "./thread/thread.h"

#include "./net/socketUtility.h"
#include "./net/socket.h"
#include "./net/socketManager.h"
#include "./net/packetReceiver.h"
#include "./net/socketReceiver.h"


#pragma warning(disable:4996)
#pragma warning(disable:4985)


#if 1
	#define	nekolibPrintf		printf
#else
	#define	nekolibPrintf(...)	((void)0)
#endif

//! �f�o�b�O�`��
#if defined(_DEBUG)
	#define DISP_PRINT			SystemPrint
#else
	//#define DISP_PRINT(...)		(void)0
	#define DISP_PRINT(...)		SystemPrint
#endif



#define DISP_DRAW_TIME_CONSOLE

namespace nk {
//namespace system {

//----------------------------------�\����----------------------------------
/*! �������p�����[�^ */
struct InitParam {
	s32			argc;					//!<	�v���O��������
	char**		argv;					//!<	�v���O��������
	f32			screenWidth;			//!<	�X�N���[������
	f32			screenHeight;			//!<	�X�N���[���c��
	u32			frameRate;				//!<	�t���[�����[�g
	bool		fullScreen;				//!<	�t���X�N���[��
	char		strApplicationName[50];	//!<	�A�v���P�[�V������

	InitParam( s32 param1, char** param2, f32 screenWidth, f32 screenHeight, u32 frameRate, bool fullScreen, const char* appName )
	{
		this->argc				= param1;
		this->argv				= param2;
		this->screenWidth		= screenWidth;
		this->screenHeight		= screenHeight;
		this->frameRate			= frameRate;
		this->fullScreen		= fullScreen;
		strcpy( this->strApplicationName, appName );
	}

};





//=============================================================================
/*!
							  �V�X�e���N���X
*/
//=============================================================================
class Main {
public:
	//-----------------------�^��`--------------------------
	
	
	//----------------------�ÓI�����o-----------------------
	static const f32	DEFAULT_SCREEN_WIDTH;			//!< �����X�N���[����(1024)
	static const f32	DEFAULT_SCREEN_HEIGHT;			//!< �����X�N���[������(768)
	static const s32	DEFAULT_FRAME_RATE;				//!< �f�t�H���g�t���[�����[�g(30FPS)
	static const s32	DEBUG_SCREEN_ID			= 0xFF;	//!< �f�o�b�O�X�N���[��
	static const s32	SYSTEM_FONT_SIZE;				//!< �t�H���g�T�C�Y
	
	enum eSCREEN_ID {
		eSCREEN_ID_DEFAULT,			//!< �f�t�H���g�X�N���[��
		eSCREEN_ID_USER,			//!< �g�p�҂̓X�N���[��ID������ȍ~�ɐݒ肷��
	};

	enum SYSTEM_EVENT {
		SYSTEM_EVENT_EXIT,		//!< �I��
	};

	//-----------------------���\�b�h------------------------
	
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	Main( s32 argc = 0, char** argv = NULL, f32 screenWidth = DEFAULT_SCREEN_HEIGHT, f32 screenHeight = DEFAULT_SCREEN_HEIGHT, u32 frameRate = DEFAULT_FRAME_RATE, bool fullScreen = false, const char* appName = "" );
	virtual ~Main();

	
	//! ���s
	virtual void				Run( void );

	//! �t���[���R�[���o�b�N
	void						UpdateCallback( void );

	//! �I��
	void						Exit( void );

	//! �V�X�e���C�x���g�R�[���o�b�N
	virtual void				CallbackEvent( SYSTEM_EVENT event ) {}
	

	//! �X�N���[���̕����擾
	f32							GetScreenWidth( void ) const;

	//! �X�N���[���̍������擾
	f32							GetScreenHeight( void ) const;

	//! �X�N���[���f�v�X���擾
	f32							GetScreenDepth( void ) const;
	
	//! ����`��
	void						DrawAxis( void );

	//! 2D���[�h�ɕύX
	void						ChangeMode2D( void );

	//! 3D���[�h�ɕύX
	void						ChangeMode3D( void );

	//! �X�V�~���b���K��
	u32							GetUpdateIntervalMillSec( void ) const;

	//! ����p��ύX(�����l��45�x)
	//void						ChangeFieldOfVision( f32 deg );

	//! �r���[�|�[�g�s����K��
	//math::Matrix44				GetViewPortMatrix( void ) const;

	//! �V�F�[�_�[��Ǎ���
	void						LoadShader( graphics::Shader* shader, std::string path, std::string name );

	//! �J�����}�l�[�W�����K��
	system::CameraManager*		GetCameraManager( void ) const;

	//! ���\�[�X�Ǘ����K��
	resource::ResourceManager*	GetResourceManager( void ) const;

	//! �X�N���[�����K��
	ScreenManager*				GetScreen( void ) const;

	//! �v���Z�X�C���X�^���X���K��
	static NK_PROCESS_INSTANCE	GetProcessInstance( void );

	//! �X�N���[�����W�ϊ��s����K��
	math::Matrix44				GetPerspectiveFieldOfView( void ) const;

	//! �E�C���h�E�n���h�����K��
	NK_WINDOW_HANDLE			GetWindowHandle( void ) const;

	//! �E�C���h�E�̏K��
	Window*						GetWindow( void ) const;

	//! �^�X�N�}�l�[�W���[
	system::TaskManager*		GetTaskManager( void ) const;

	//! �V�X�e���t�H���g�����_��
	font::FontRenderer*			GetFontRenderer( void ) const;

	//! �L�[�{�[�h�擾
	input::Keyboard*			GetKeyboard( void ) const;

	//! �}�E�X�擾
	input::Mouse*				GetMouse( void ) const;

protected:		
	//-----------------------���\�b�h------------------------

	//! ������
	virtual bool				Initialize( void );

	//! �X�V
	virtual bool				Update( void ) { return true; }

	//! �I������
	virtual void				Terminate( void );

	/**		�`��O����
	
		@param	----
		@retval	----
		\note	�`��O��ɌĂ΂��B
				�f�t�H���g�ł͉�ʃN���A���Ă΂��
	*/
	virtual	void				DrawInitialize( void );


	/**		�`��㏈��
	
		@param	----
		@retval	----
		\note	�f�t�H���g�ł͎��`�悪�Ă΂��
	*/
	virtual void				DrawTerminate( void );


	//! �C�x���g�K��
	virtual bool				ObtainEvent( void );

	//! �I���Ȃ�true
	bool						IsExit( void ) const;
	
	
	//----------------------�����o�ϐ�-----------------------
	//nk::math::Matrix44			m_PFOVmatrix;		//!< �X�N���[���ϊ��s��
	nk::input::Keyboard*		m_keyboard;				//!< �L�[�{�[�h
	nk::input::Mouse*			m_mouse;				//!< �}�E�X
	resource::ResourceManager*	m_resourceMng;			//!< ���\�[�X�Ǘ�
	system::CameraManager*		m_cameraMng;			//!< �J�����Ǘ�
	graphics::RenderManager*	m_drawMng;				//!< �`��Ǘ�
	ScreenManager*				m_screenMng;			//!< �X�N���[��
	Window*						m_window;				//!< �E�C���h�E
	system::TaskManager*		m_taskMng;				//!< �^�X�N�}�l�[�W���[
	net::SocketManager*			m_socketMng;			//!< �\�P�b�g�Ǘ�
	graphics::DrawPacketManager*m_drawPacketMng;		//!< �`��p�P�b�g�Ǘ�

	font::Font					m_systemFont;			//!< �V�X�e���t�H���g
	font::FontRenderer*			m_fontRenderer;			//!< �t�H���g�����_��
	system::MouseEventGetter	m_mouseEventGetter;		//!< �}�E�X�C�x���g�擾
	system::KeyboardEventGetter	m_keyboardEventGetter;	//!< �}�E�X�C�x���g�擾
	system::SystemEventGetter	m_systemEventGetter;	//!< �}�E�X�C�x���g�擾
	graphics::Line				m_line;					//!< ���`��
	
private:		
	//-----------------------���\�b�h------------------------

	//! ������
	bool	_Init( void );

	//! �I������
	void	_Term( void );

	//! �t���[���E�F�C�g
	void	_FrameWait( void );

	//! �V�X�e���̏�����
	bool	_InitSystem( void );

	//! �E�C���h�E�̏�����
	bool	_InitWindow( void );

	//! �I�[�f�B�I�̏�����
	bool	_InitAudio( void );

	//! �v���O�����p�����[�^�[���Z�b�g
	bool	_InitApplicationParameter( void );

	//! ���[�v
	void	_Loop( void );

	//! ���[�v���X�V
	bool	_UpdateFrame( void );

	//! �X�V�t���[���Ȃ�true
	bool	_Updateable( void ) const;

	//! SDL�̃C�x���g���擾
	bool	_ObtainSDLEvent( void );



	//! GL�̏�����
	bool	_InitWinGL( void );

	//! �`��o�b�t�@����ւ�
	void	_SwapBuffers( void );

	//----------------------�����o�ϐ�-----------------------
	nk::InitParam			m_initParam;			//!< �������p�����[�^
	u32						m_prevTime;				//!< �O��̎���(�t���[���E�F�C�g�Ɏg�p)
	FramerateCalclator		m_framerateCalclator;	//!< �t���[�����[�g�v��
	bool					m_exit;					//!< �I���t���O

#ifdef _WIN32
	HDC						m_hDC;				//!< 
	HGLRC					m_hRC;				//!< 
	HDC						m_hOldDC;			//!< 
	HGLRC					m_hOldRC;			//!< 
#endif
	

};


//! �`�惊�X�g�Ƀo�b�t�@�N���A������}��
// void				AddListForBufferClear( u32 priority );

//! �V�X�e��������`��
void				SystemPrint( s32 x, s32 y, 				const char* fmt, ... );
void				SystemPrint( s32 x, s32 y, Color color, const char* fmt, ... );


//}	// namespace system
}	// namespace nk





#endif  // __SYSTEM_H__