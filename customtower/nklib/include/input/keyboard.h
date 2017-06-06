//=============================================================================
/*!	@file	keyboard.h

	@brief	�L�[�{�[�h���̓N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

//-------------------------------�C���N���[�h-------------------------------
#include "../typedef.h"
#include "./inputBase.h"
#include "./buttonConstant.h"
#include "../system/keyboardEventGetterBase.h"


namespace nk {
namespace input {

//=============================================================================
/*!
                              �L�[�{�[�h�N���X
*/
//=============================================================================
class Keyboard : public Input {
public:
	//-----------------------�^��`--------------------------
	enum KEY_NUM {

		/* �A���t�@�x�b�g */
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		/* �L�� */
		KEY_COLON,			// :
		KEY_SEMICOLON,		// ;
		KEY_LESS,			// <
		KEY_EQUALS,			// =
		KEY_GREATER,		// >
		KEY_QUESTION,		// ?
		KEY_AT,				// @
		KEY_LEFTBRACKET,	// [
		KEY_BACKSLASH,		// �o�b�N�X���b�V��
		KEY_RIGHTBRACKET,	// ]
		KEY_CARET,			// ^
		KEY_UNDERSCORE,		// _
		KEY_BACKQUOTE,		// `

		/* �����L�[ */
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,

		/* �t�@���N�V�����L�[ */
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,

		/* �e���L�[ */
		KEY_TEN_0,
		KEY_TEN_1,
		KEY_TEN_2,
		KEY_TEN_3,
		KEY_TEN_4,
		KEY_TEN_5,
		KEY_TEN_6,
		KEY_TEN_7,
		KEY_TEN_8,
		KEY_TEN_9,
		KEY_TEN_PERIOD,		// .
		KEY_TEN_DIVIDE,		// %
		KEY_TEN_MULTIPLY,	// *
		KEY_TEN_MINUS,		// -
		KEY_TEN_PLUS,		// +
		KEY_TEN_ENTER,		// enter
		KEY_TEN_EQUALS,		// =

		/* ���L�[ */
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT,

		/* �I�v�V�����L�[ */
		KEY_RSHIFT,
		KEY_LSHIFT,
		KEY_RCTRL,
		KEY_LCTRL,
		KEY_RALT,
		KEY_LALT,
		KEY_BACKSPACE,
		KEY_TAB,
		KEY_SPACE,
		KEY_ENTER,
		KEY_ESC,

		KEY_MAX,
	};
		

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	virtual void	SetEventGetter( const system::KeyboardEventGetterBase* eventGetter );

	//! ������Ă��邩�ǂ����̔���
	virtual bool	IsPress( s32 i ) const;

	//! �O��̃t���[���ł͗�����Ă��č��̃t���[���ł͉�����Ă��邩�ǂ����̔���
	virtual bool	IsPressed( s32 i ) const;

	//! �����Ă��邩�ǂ����̔���
	virtual bool	IsRelease( s32 i ) const;

	//! �O�̃t���[���ŉ����Ă��č��̃t���[���ŗ����ꂽ���ǂ����̔���
	virtual bool	IsReleased( s32 i ) const;
	
	//! �X�V
	void	Update();

private:
	//! ������Ă�����true��Ԃ�
	bool	_IsPress( void* keyAry, s32 keyNo ) const;
	
private:
	//----------------------�����o�ϐ�-----------------------
	const system::KeyboardEventGetterBase*	m_eventGetter;			//!< �C�x���g�擾
	ButtonState								m_state[KEY_MAX];		//!< �������
	s32										m_keyIdx[KEY_MAX];		//!< SDL�ł̃L�[�ԍ��i�[�z��
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 Keyboard();
	~Keyboard();
};


}	// namespace input
}	// namespace nk




#endif  // __KEYBOARD_H__