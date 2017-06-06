//=============================================================================
/*!	@file	buttonConstant.h

	@brief	�{�^���萔���܂Ƃ߂��t�@�C��

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __BUTTONCONSTANT_H__
#define __BUTTONCONSTANT_H__


/*
	�X�y�[�X[32] �` ��[64]
	[[91] �` `[96]
	a[97] �` z[122]

	1:���N���b�N
	2:�E�N���b�N
	3:�z�C�[���N���b�N
*/



namespace nk {
namespace input {

//enum ButtonPress {
//	PRESS		= 1<<0,		// �����Ă���
//	RELEASE		= 1<<1,		// �����Ă���
//	PRESSED		= 1<<2,		// ������
//	RELEASED	= 1<<3,		// ������
//};

//typedef u32 ButtonState;	// �{�^���̏��


//-------------------------------------------
//		�Q�[���p�b�h(PS�R���g���[���[)
//-------------------------------------------
enum PAD_NUM {
	PAD_RU	= 0,		// ��
	PAD_RR	= 1,		// ��
	PAD_RD	= 2,		// �~
	PAD_RL	= 3,		// ��

	/* ���݂̂Ƃ��낱���̓��͂��X�e�B�b�N���͂Ƃ��Ĉ����邽�ߎ擾�ł��Ȃ� */
	PAD_LU	= -1,		// ��
	PAD_LR	= -1,		// ��
	PAD_LD	= -1,		// ��
	PAD_LL	= -1,		// ��

	PAD_R1	= 7,		// R1
	PAD_R2	= 5,		// R2
	PAD_R3	= 11,		// R3(�E�X�e�B�b�N��������)
	PAD_L1	= 6,		// L1
	PAD_L2	= 4,		// L2
	PAD_L3	= 10,		// L3(���X�e�B�b�N��������)

	PAD_SELECT	= 9,	// select
	PAD_START	= 8,	// start

	PAD_MAX	= 12
};

//-------------------------------------------
//		�}�E�X
//-------------------------------------------
//enum MOUSE_NUM {
//	MOUSE_LEFT = 0,
//	MOUSE_RIGHT,
//	MOUSE_CENTER,
//	MOUSE_MAX,
//};


//-------------------------------------------
//		�L�[�{�[�h
//-------------------------------------------
/* �L�[�{�[�h */
//enum KEY_NUM {

//	/* �A���t�@�x�b�g */
//	KEY_A,
//	KEY_B,
//	KEY_C,
//	KEY_D,
//	KEY_E,
//	KEY_F,
//	KEY_G,
//	KEY_H,
//	KEY_I,
//	KEY_J,
//	KEY_K,
//	KEY_L,
//	KEY_M,
//	KEY_N,
//	KEY_O,
//	KEY_P,
//	KEY_Q,
//	KEY_R,
//	KEY_S,
//	KEY_T,
//	KEY_U,
//	KEY_V,
//	KEY_W,
//	KEY_X,
//	KEY_Y,
//	KEY_Z,

//	/* �L�� */
//	KEY_COLON,			// :
//	KEY_SEMICOLON,		// ;
//	KEY_LESS,			// <
//	KEY_EQUALS,			// =
//	KEY_GREATER,		// >
//	KEY_QUESTION,		// ?
//	KEY_AT,				// @
//	KEY_LEFTBRACKET,	// [
//	KEY_BACKSLASH,		// �o�b�N�X���b�V��
//	KEY_RIGHTBRACKET,	// ]
//	KEY_CARET,			// ^
//	KEY_UNDERSCORE,		// _
//	KEY_BACKQUOTE,		// `

//	/* �����L�[ */
//	KEY_0,
//	KEY_1,
//	KEY_2,
//	KEY_3,
//	KEY_4,
//	KEY_5,
//	KEY_6,
//	KEY_7,
//	KEY_8,
//	KEY_9,

//	/* �t�@���N�V�����L�[ */
//	KEY_F1,
//	KEY_F2,
//	KEY_F3,
//	KEY_F4,
//	KEY_F5,
//	KEY_F6,
//	KEY_F7,
//	KEY_F8,
//	KEY_F9,
//	KEY_F10,
//	KEY_F11,
//	KEY_F12,

//	/* �e���L�[ */
//	KEY_TEN_0,
//	KEY_TEN_1,
//	KEY_TEN_2,
//	KEY_TEN_3,
//	KEY_TEN_4,
//	KEY_TEN_5,
//	KEY_TEN_6,
//	KEY_TEN_7,
//	KEY_TEN_8,
//	KEY_TEN_9,
//	KEY_TEN_PERIOD,		// .
//	KEY_TEN_DIVIDE,		// %
//	KEY_TEN_MULTIPLY,	// *
//	KEY_TEN_MINUS,		// -
//	KEY_TEN_PLUS,		// +
//	KEY_TEN_ENTER,		// enter
//	KEY_TEN_EQUALS,		// =

//	/* ���L�[ */
//	KEY_UP,
//	KEY_DOWN,
//	KEY_RIGHT,
//	KEY_LEFT,

//	/* �I�v�V�����L�[ */
//	KEY_RSHIFT,
//	KEY_LSHIFT,
//	KEY_RCTRL,
//	KEY_LCTRL,
//	KEY_RALT,
//	KEY_LALT,
//	KEY_BACKSPACE,
//	KEY_TAB,
//	KEY_SPACE,
//	KEY_ENTER,
//	KEY_ESC,

//	KEY_MAX,
//};


}	// namespace input
}	// namespace nk



#endif