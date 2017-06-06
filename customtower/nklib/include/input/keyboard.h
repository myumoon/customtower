//=============================================================================
/*!	@file	keyboard.h

	@brief	キーボード入力クラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

//-------------------------------インクルード-------------------------------
#include "../typedef.h"
#include "./inputBase.h"
#include "./buttonConstant.h"
#include "../system/keyboardEventGetterBase.h"


namespace nk {
namespace input {

//=============================================================================
/*!
                              キーボードクラス
*/
//=============================================================================
class Keyboard : public Input {
public:
	//-----------------------型定義--------------------------
	enum KEY_NUM {

		/* アルファベット */
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

		KEY_MAX,
	};
		

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	virtual void	SetEventGetter( const system::KeyboardEventGetterBase* eventGetter );

	//! 押されているかどうかの判定
	virtual bool	IsPress( s32 i ) const;

	//! 前回のフレームでは離されていて今のフレームでは押されているかどうかの判定
	virtual bool	IsPressed( s32 i ) const;

	//! 離しているかどうかの判定
	virtual bool	IsRelease( s32 i ) const;

	//! 前のフレームで押していて今のフレームで離されたかどうかの判定
	virtual bool	IsReleased( s32 i ) const;
	
	//! 更新
	void	Update();

private:
	//! 押されていたらtrueを返す
	bool	_IsPress( void* keyAry, s32 keyNo ) const;
	
private:
	//----------------------メンバ変数-----------------------
	const system::KeyboardEventGetterBase*	m_eventGetter;			//!< イベント取得
	ButtonState								m_state[KEY_MAX];		//!< 押下状態
	s32										m_keyIdx[KEY_MAX];		//!< SDLでのキー番号格納配列
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 Keyboard();
	~Keyboard();
};


}	// namespace input
}	// namespace nk




#endif  // __KEYBOARD_H__