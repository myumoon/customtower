//=============================================================================
/*!	@file	window.h

	@brief	�E�C���h�E���Ǘ�����N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __WINDOW_H__
#define __WINDOW_H__

//-------------------------------�C���N���[�h-------------------------------
#include <string>
#if defined(_WINDOWS)
#include <winsock2.h>
#include <windows.h>
#endif

#include "../typedef.h"
#include "../math/matrix.h"


namespace nk {


// �E�C���h�E�X�V���R�[���o�b�N
typedef void (*WindowCallback)(void*);


//=============================================================================
/*!
                              �E�C���h�E�N���X
*/
//=============================================================================
class Window {
public:
	
	//-----------------------�^��`--------------------------
	struct WindowInfo {
		s32			width;
		s32			height;
		f32			depth;
		bool		fullscreen;
	};
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ������
	//void				Initialize(f32 screenWidth, f32 screenHeight);
	bool				Create( s32 width, s32 height, f32 depth, bool fullscreen = false );
	bool				Create( const WindowInfo& info );

	//! �E�C���h�E�R�[���o�b�N���Z�b�g
	void				SetWindowCallback( WindowCallback func, void* param );

	//! �^�C�g��������
	void				SetTitle(const char* title);

	//! �A�C�R�����Z�b�g
	void				SetIcon( const char* iconPath );

	//! �v���W�F�N�V�����ϊ��s��(�E����W)
	void				SetMatrixPerspectiveFovRH();

	//! ���E�����E�[�x�̏K��
	math::Vector		GetScreenParam( void ) const;

	//! �E�C���h�E�n���h�����K��
	NK_WINDOW_HANDLE	GetWindowHandle( void ) const;

	//! �r���[�|�[�g�s����K��
	math::Matrix44		GetViewPortMatrix( void ) const;
	
	//! �E�C���h�E�R�[���o�b�N
	//static NK_RESULT NK_CALLBACK WndProc(  );
	//LRESULT CALLBACK WndProc( HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
	//static LRESULT CALLBACK WndProc(){}
	
private:
	//----------------------�����o�ϐ�-----------------------
	f32							m_screenWidth;			//!< �X�N���[���̕�
	f32							m_screenHeight;			//!< �X�N���[���̍���
	f32							m_screenDepth;			//!< �X�N���[���[�x
	bool						m_fullScreen;			//!< �t���X�N���[���t���O

	NK_WINDOW_HANDLE			m_windowHandle;			//!< �E�C���h�E�n���h��
	
#if defined(_WINDOWS)
	WNDCLASS					m_windowClass;			//!< �E�C���h�E winAPI
#endif
	
	//-----------------------���\�b�h------------------------
	void				_Initialize( void );
	void				_Finalize( void );
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 Window();
	virtual ~Window();
};

}







#endif  // __WINDOW_H__