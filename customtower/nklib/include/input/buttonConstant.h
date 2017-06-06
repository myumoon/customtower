//=============================================================================
/*!	@file	buttonConstant.h

	@brief	ボタン定数をまとめたファイル

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __BUTTONCONSTANT_H__
#define __BUTTONCONSTANT_H__


/*
	スペース[32] ～ ＠[64]
	[[91] ～ `[96]
	a[97] ～ z[122]

	1:左クリック
	2:右クリック
	3:ホイールクリック
*/



namespace nk {
namespace input {

//enum ButtonPress {
//	PRESS		= 1<<0,		// 押している
//	RELEASE		= 1<<1,		// 離している
//	PRESSED		= 1<<2,		// 押した
//	RELEASED	= 1<<3,		// 離した
//};

//typedef u32 ButtonState;	// ボタンの状態


//-------------------------------------------
//		ゲームパッド(PSコントローラー)
//-------------------------------------------
enum PAD_NUM {
	PAD_RU	= 0,		// △
	PAD_RR	= 1,		// ○
	PAD_RD	= 2,		// ×
	PAD_RL	= 3,		// □

	/* 現在のところここの入力がスティック入力として扱われるため取得できない */
	PAD_LU	= -1,		// ↑
	PAD_LR	= -1,		// →
	PAD_LD	= -1,		// ↓
	PAD_LL	= -1,		// ←

	PAD_R1	= 7,		// R1
	PAD_R2	= 5,		// R2
	PAD_R3	= 11,		// R3(右スティック押し込み)
	PAD_L1	= 6,		// L1
	PAD_L2	= 4,		// L2
	PAD_L3	= 10,		// L3(左スティック押し込み)

	PAD_SELECT	= 9,	// select
	PAD_START	= 8,	// start

	PAD_MAX	= 12
};

//-------------------------------------------
//		マウス
//-------------------------------------------
//enum MOUSE_NUM {
//	MOUSE_LEFT = 0,
//	MOUSE_RIGHT,
//	MOUSE_CENTER,
//	MOUSE_MAX,
//};


//-------------------------------------------
//		キーボード
//-------------------------------------------
/* キーボード */
//enum KEY_NUM {

//	/* アルファベット */
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

//	/* 記号 */
//	KEY_COLON,			// :
//	KEY_SEMICOLON,		// ;
//	KEY_LESS,			// <
//	KEY_EQUALS,			// =
//	KEY_GREATER,		// >
//	KEY_QUESTION,		// ?
//	KEY_AT,				// @
//	KEY_LEFTBRACKET,	// [
//	KEY_BACKSLASH,		// バックスラッシュ
//	KEY_RIGHTBRACKET,	// ]
//	KEY_CARET,			// ^
//	KEY_UNDERSCORE,		// _
//	KEY_BACKQUOTE,		// `

//	/* 数字キー */
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

//	/* ファンクションキー */
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

//	/* テンキー */
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

//	/* 矢印キー */
//	KEY_UP,
//	KEY_DOWN,
//	KEY_RIGHT,
//	KEY_LEFT,

//	/* オプションキー */
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