//=============================================================================
/*!	@file	keyboardEvent.h

	@brief	キーボードイベント

	@author	ryunosuke ide
	@date	2013.06.29
*/
//=============================================================================


#ifndef __KEYBOARD_EVENT_H__
#define __KEYBOARD_EVENT_H__


namespace nk {
namespace system {

//! キーボードイベント
struct KeyboardEvent {
	
	//! キーイベント
	enum {
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

		/* 記号 */
		KEY_COLON,			// :
		KEY_SEMICOLON,		// ;
		KEY_LESS,			// <
		KEY_EQUALS,			// =
		KEY_GREATER,		// >
		KEY_QUESTION,		// ?
		KEY_AT,				// @
		KEY_LEFTBRACKET,	// [
		KEY_BACKSLASH,		// バックスラッシュ
		KEY_RIGHTBRACKET,	// ]
		KEY_CARET,			// ^
		KEY_UNDERSCORE,		// _
		KEY_BACKQUOTE,		// `

		/* 数字キー */
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

		/* ファンクションキー */
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

		/* テンキー */
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

		/* 矢印キー */
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT,

		/* オプションキー */
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
		
		KEY_EVENT_MAX,		//!< イベント数
	};
	
	//! 1ビット
	struct _Bool {
		u32		flag : 1;
	};

	//! イベント
	_Bool	event[KEY_EVENT_MAX];

	//! コンストラクタ
	KeyboardEvent( void ) {
		this->Clear();
	}

	//! クリア
	void Clear( void ) {
		for( u32 i = 0; i < KEY_EVENT_MAX; ++i ) {
			this->event[i].flag	= 0;
		}
	}

	//! イベントセット
	void EventOn( u32 bit ) {
		this->event[bit].flag = 1;
	}
	void EventOff( u32 bit ) {
		this->event[bit].flag = 0;
	}
	
	//! イベント取得
	bool IsOn( u32 bit ) const {
		return (this->event[bit].flag != 0) ? true : false;
	}
};
	
}	// namespace system
}	// namespace nk






#endif  // __KEYBOARD_EVENT_H__