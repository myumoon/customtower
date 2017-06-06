//=============================================================================
/*!	@file	kyuboard.cpp

	@brief	キーボード入力クラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/input/keyboard.h"
#include "../../include/project.h"

#if defined(_WINDOWS)
#include <winsock2.h>
#include <windows.h>
#endif

#if defined(NK_USE_SDL)
#include <SDL/SDL.h>
#endif

namespace nk {
namespace input {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Keyboard::Keyboard() : Input()
{
	/* 押下状態を初期化 */
	for(s32 i = 0; i < KEY_MAX; i++) {
		m_state[i] = 0;
	}

	m_eventGetter	= NULL;

#if defined(_WINDOWS)
	/* アルファベット (ASCII 'A'-'Z') */
	m_keyIdx[KEY_A]			= 0x41;
	m_keyIdx[KEY_B]			= 0x42;
	m_keyIdx[KEY_C]			= 0x43;
	m_keyIdx[KEY_D]			= 0x44;
	m_keyIdx[KEY_E]			= 0x45;
	m_keyIdx[KEY_F]			= 0x46;
	m_keyIdx[KEY_G]			= 0x47;
	m_keyIdx[KEY_H]			= 0x48;
	m_keyIdx[KEY_I]			= 0x49;
	m_keyIdx[KEY_J]			= 0x4A;
	m_keyIdx[KEY_K]			= 0x4B;
	m_keyIdx[KEY_L]			= 0x4C;
	m_keyIdx[KEY_M]			= 0x4D;
	m_keyIdx[KEY_N]			= 0x4E;
	m_keyIdx[KEY_O]			= 0x4F;
	m_keyIdx[KEY_P]			= 0x50;
	m_keyIdx[KEY_Q]			= 0x51;
	m_keyIdx[KEY_R]			= 0x52;
	m_keyIdx[KEY_S]			= 0x53;
	m_keyIdx[KEY_T]			= 0x54;
	m_keyIdx[KEY_U]			= 0x55;
	m_keyIdx[KEY_V]			= 0x56;
	m_keyIdx[KEY_W]			= 0x57;
	m_keyIdx[KEY_X]			= 0x58;
	m_keyIdx[KEY_Y]			= 0x59;
	m_keyIdx[KEY_Z]			= 0x5A;

	/* 記号 (58~64 91~96) */
	m_keyIdx[KEY_COLON]			= VK_OEM_1;
	m_keyIdx[KEY_SEMICOLON]		= VK_OEM_PLUS;
	m_keyIdx[KEY_LESS]			= VK_OEM_COMMA;
	m_keyIdx[KEY_EQUALS]		= VK_OEM_MINUS;
	m_keyIdx[KEY_GREATER]		= VK_OEM_PERIOD;
	m_keyIdx[KEY_QUESTION]		= VK_OEM_2;
	m_keyIdx[KEY_AT]			= VK_OEM_3;
	m_keyIdx[KEY_LEFTBRACKET]	= VK_OEM_4;
	m_keyIdx[KEY_BACKSLASH]		= VK_OEM_5;
	m_keyIdx[KEY_RIGHTBRACKET]	= VK_OEM_6;
	m_keyIdx[KEY_CARET]			= VK_OEM_7;
	m_keyIdx[KEY_UNDERSCORE]	= VK_OEM_102;
	m_keyIdx[KEY_BACKQUOTE]		= VK_OEM_3;

	/* 数字キー (ASCII '0'-'9') */
	m_keyIdx[KEY_0]				= 0x30;
	m_keyIdx[KEY_1]				= 0x31;
	m_keyIdx[KEY_2]				= 0x32;
	m_keyIdx[KEY_3]				= 0x33;
	m_keyIdx[KEY_4]				= 0x34;
	m_keyIdx[KEY_5]				= 0x35;
	m_keyIdx[KEY_6]				= 0x36;
	m_keyIdx[KEY_7]				= 0x37;
	m_keyIdx[KEY_8]				= 0x38;
	m_keyIdx[KEY_9]				= 0x39;

	/* ファンクションキー (282~293) */
	m_keyIdx[KEY_F1]			= VK_F1;
	m_keyIdx[KEY_F2]			= VK_F2;
	m_keyIdx[KEY_F3]			= VK_F3;
	m_keyIdx[KEY_F4]			= VK_F4;
	m_keyIdx[KEY_F5]			= VK_F5;
	m_keyIdx[KEY_F6]			= VK_F6;
	m_keyIdx[KEY_F7]			= VK_F7;
	m_keyIdx[KEY_F8]			= VK_F8;
	m_keyIdx[KEY_F9]			= VK_F9;
	m_keyIdx[KEY_F10]			= VK_F10;
	m_keyIdx[KEY_F11]			= VK_F11;
	m_keyIdx[KEY_F12]			= VK_F12;

	/* テンキー (256~272) */
	m_keyIdx[KEY_TEN_0]			= VK_NUMPAD0;
	m_keyIdx[KEY_TEN_1]			= VK_NUMPAD1;
	m_keyIdx[KEY_TEN_2]			= VK_NUMPAD2;
	m_keyIdx[KEY_TEN_3]			= VK_NUMPAD3;
	m_keyIdx[KEY_TEN_4]			= VK_NUMPAD4;
	m_keyIdx[KEY_TEN_5]			= VK_NUMPAD5;
	m_keyIdx[KEY_TEN_6]			= VK_NUMPAD6;
	m_keyIdx[KEY_TEN_7]			= VK_NUMPAD7;
	m_keyIdx[KEY_TEN_8]			= VK_NUMPAD8;
	m_keyIdx[KEY_TEN_9]			= VK_NUMPAD9;
	m_keyIdx[KEY_TEN_PERIOD]	= VK_DECIMAL;
	m_keyIdx[KEY_TEN_DIVIDE]	= VK_DIVIDE;
	m_keyIdx[KEY_TEN_MULTIPLY]	= VK_MULTIPLY;
	m_keyIdx[KEY_TEN_MINUS]		= VK_SUBTRACT;
	m_keyIdx[KEY_TEN_PLUS]		= VK_ADD;
	m_keyIdx[KEY_TEN_ENTER]		= 0;
	m_keyIdx[KEY_TEN_EQUALS]	= 0;

	/* 矢印キー (273~276) */
	m_keyIdx[KEY_UP]			= VK_UP;
	m_keyIdx[KEY_DOWN]			= VK_DOWN;
	m_keyIdx[KEY_RIGHT]			= VK_RIGHT;
	m_keyIdx[KEY_LEFT]			= VK_LEFT;

	/* オプションキー */
	m_keyIdx[KEY_RSHIFT]		= VK_RSHIFT;
	m_keyIdx[KEY_LSHIFT]		= VK_LSHIFT;
	m_keyIdx[KEY_RCTRL]			= VK_RCONTROL;
	m_keyIdx[KEY_LCTRL]			= VK_LCONTROL;
	m_keyIdx[KEY_RALT]			= VK_MENU;
	m_keyIdx[KEY_LALT]			= VK_MENU;
	m_keyIdx[KEY_BACKSPACE]		= VK_BACK;
	m_keyIdx[KEY_TAB]			= VK_TAB;
	m_keyIdx[KEY_SPACE]			= VK_SPACE;
	m_keyIdx[KEY_ENTER]			= VK_RETURN;
	m_keyIdx[KEY_ESC]			= VK_ESCAPE;
	
#elif defined(NK_USE_SDL)

	/* KEY定数をSDLのキー番号に対応させる */

	/* アルファベット (97~122) */
	m_keyIdx[KEY_A]			= SDLK_a;
	m_keyIdx[KEY_B]			= SDLK_b;
	m_keyIdx[KEY_C]			= SDLK_c;
	m_keyIdx[KEY_D]			= SDLK_d;
	m_keyIdx[KEY_E]			= SDLK_e;
	m_keyIdx[KEY_F]			= SDLK_f;
	m_keyIdx[KEY_G]			= SDLK_g;
	m_keyIdx[KEY_H]			= SDLK_h;
	m_keyIdx[KEY_I]			= SDLK_i;
	m_keyIdx[KEY_J]			= SDLK_j;
	m_keyIdx[KEY_K]			= SDLK_k;
	m_keyIdx[KEY_L]			= SDLK_l;
	m_keyIdx[KEY_M]			= SDLK_m;
	m_keyIdx[KEY_N]			= SDLK_n;
	m_keyIdx[KEY_O]			= SDLK_o;
	m_keyIdx[KEY_P]			= SDLK_p;
	m_keyIdx[KEY_Q]			= SDLK_q;
	m_keyIdx[KEY_R]			= SDLK_r;
	m_keyIdx[KEY_S]			= SDLK_s;
	m_keyIdx[KEY_T]			= SDLK_t;
	m_keyIdx[KEY_U]			= SDLK_u;
	m_keyIdx[KEY_V]			= SDLK_v;
	m_keyIdx[KEY_W]			= SDLK_w;
	m_keyIdx[KEY_X]			= SDLK_x;
	m_keyIdx[KEY_Y]			= SDLK_y;
	m_keyIdx[KEY_Z]			= SDLK_z;

	/* 記号 (58~64 91~96) */
	m_keyIdx[KEY_COLON]			= SDLK_COLON;
	m_keyIdx[KEY_SEMICOLON]		= SDLK_SEMICOLON;
	m_keyIdx[KEY_LESS]			= SDLK_LESS;
	m_keyIdx[KEY_EQUALS]		= SDLK_EQUALS;
	m_keyIdx[KEY_GREATER]		= SDLK_GREATER;
	m_keyIdx[KEY_QUESTION]		= SDLK_QUESTION;
	m_keyIdx[KEY_AT]			= SDLK_AT;
	m_keyIdx[KEY_LEFTBRACKET]	= SDLK_LEFTBRACKET;
	m_keyIdx[KEY_BACKSLASH]		= SDLK_BACKSLASH;
	m_keyIdx[KEY_RIGHTBRACKET]	= SDLK_RIGHTBRACKET;
	m_keyIdx[KEY_CARET]			= SDLK_CARET;
	m_keyIdx[KEY_UNDERSCORE]	= SDLK_UNDERSCORE;
	m_keyIdx[KEY_BACKQUOTE]		= SDLK_BACKQUOTE;

	/* 数字キー (48~57) */
	m_keyIdx[KEY_0]				= SDLK_0;
	m_keyIdx[KEY_1]				= SDLK_1;
	m_keyIdx[KEY_2]				= SDLK_2;
	m_keyIdx[KEY_3]				= SDLK_3;
	m_keyIdx[KEY_4]				= SDLK_4;
	m_keyIdx[KEY_5]				= SDLK_5;
	m_keyIdx[KEY_6]				= SDLK_6;
	m_keyIdx[KEY_7]				= SDLK_7;
	m_keyIdx[KEY_8]				= SDLK_8;
	m_keyIdx[KEY_9]				= SDLK_9;

	/* ファンクションキー (282~293) */
	m_keyIdx[KEY_F1]			= SDLK_F1;
	m_keyIdx[KEY_F2]			= SDLK_F2;
	m_keyIdx[KEY_F3]			= SDLK_F3;
	m_keyIdx[KEY_F4]			= SDLK_F4;
	m_keyIdx[KEY_F5]			= SDLK_F5;
	m_keyIdx[KEY_F6]			= SDLK_F6;
	m_keyIdx[KEY_F7]			= SDLK_F7;
	m_keyIdx[KEY_F8]			= SDLK_F8;
	m_keyIdx[KEY_F9]			= SDLK_F9;
	m_keyIdx[KEY_F10]			= SDLK_F10;
	m_keyIdx[KEY_F11]			= SDLK_F11;
	m_keyIdx[KEY_F12]			= SDLK_F12;

	/* テンキー (256~272) */
	m_keyIdx[KEY_TEN_0]			= SDLK_KP0;
	m_keyIdx[KEY_TEN_1]			= SDLK_KP1;
	m_keyIdx[KEY_TEN_2]			= SDLK_KP2;
	m_keyIdx[KEY_TEN_3]			= SDLK_KP3;
	m_keyIdx[KEY_TEN_4]			= SDLK_KP4;
	m_keyIdx[KEY_TEN_5]			= SDLK_KP5;
	m_keyIdx[KEY_TEN_6]			= SDLK_KP6;
	m_keyIdx[KEY_TEN_7]			= SDLK_KP7;
	m_keyIdx[KEY_TEN_8]			= SDLK_KP8;
	m_keyIdx[KEY_TEN_9]			= SDLK_KP9;
	m_keyIdx[KEY_TEN_PERIOD]	= SDLK_KP_PERIOD;
	m_keyIdx[KEY_TEN_DIVIDE]	= SDLK_KP_DIVIDE;
	m_keyIdx[KEY_TEN_MULTIPLY]	= SDLK_KP_MULTIPLY;
	m_keyIdx[KEY_TEN_MINUS]		= SDLK_KP_MINUS;
	m_keyIdx[KEY_TEN_PLUS]		= SDLK_KP_PLUS;
	m_keyIdx[KEY_TEN_ENTER]		= SDLK_KP_ENTER;
	m_keyIdx[KEY_TEN_EQUALS]	= SDLK_KP_EQUALS;

	/* 矢印キー (273~276) */
	m_keyIdx[KEY_UP]			= SDLK_UP;
	m_keyIdx[KEY_DOWN]			= SDLK_DOWN;
	m_keyIdx[KEY_RIGHT]			= SDLK_RIGHT;
	m_keyIdx[KEY_LEFT]			= SDLK_LEFT;

	/* オプションキー */
	m_keyIdx[KEY_RSHIFT]		= SDLK_RSHIFT;
	m_keyIdx[KEY_LSHIFT]		= SDLK_LSHIFT;
	m_keyIdx[KEY_RCTRL]			= SDLK_RCTRL;
	m_keyIdx[KEY_LCTRL]			= SDLK_LCTRL;
	m_keyIdx[KEY_RALT]			= SDLK_RALT;
	m_keyIdx[KEY_LALT]			= SDLK_LALT;
	m_keyIdx[KEY_BACKSPACE]		= SDLK_BACKSPACE;
	m_keyIdx[KEY_TAB]			= SDLK_TAB;
	m_keyIdx[KEY_SPACE]			= SDLK_SPACE;
	m_keyIdx[KEY_ENTER]			= SDLK_RETURN;
	m_keyIdx[KEY_ESC]			= SDLK_ESCAPE;
#endif
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
Keyboard::~Keyboard()
{
	
}


//===========================================================================
/*!	@brief		イベントゲッター設定
	@param		eventGetter	イベントゲッター
	@return		----
*/
//===========================================================================
void Keyboard::SetEventGetter( const system::KeyboardEventGetterBase* eventGetter )
{
	m_eventGetter	= eventGetter;
}


//===========================================================================
/*!	@brief	更新
	@param	なし
	@return	なし
*/
//===========================================================================
void Keyboard::Update()
{
#if defined(_WINDOWS)
	BYTE	key[256];

	BOOL	result	= GetKeyboardState( key );
	if( result == FALSE ) {
		// 習得できなかった
		return;
	}
	
#elif defined(NK_USE_SDL)

	Uint8* key = SDL_GetKeyState( NULL );
	
#endif
	
	//	ボタンの情報を更新
	//---------------------------------------
	for(s32 i = 0; i < KEY_MAX; i++) {

		/* 初期化 */
		m_state[i] &= ~(PRESSED | RELEASED);


		if( _IsPress( key, m_keyIdx[i] ) ) {
		//if( key[m_keyIdx[i]] ) {
			if( !(m_state[i] & PRESS) ) {
				m_state[i] |= PRESSED;
			}
			m_state[i] |= PRESS;
			m_state[i] &= ~RELEASE;
		}
		else {
			if( (m_state[i] & PRESS) && !(m_state[i] & RELEASE) ) {
				m_state[i] |= RELEASED;
			}
			m_state[i] |= RELEASE;
			m_state[i] &= ~PRESS;
		}
	}

}

//===========================================================================
/*!	@brief	押されているか
	@param	keyNum: キーボード定数
	@return	true:押されている	false:離されている
*/
//===========================================================================
bool Keyboard::_IsPress( void* keyAry, s32 keyNo ) const
{
#if defined(_WINDOWS)
	BYTE*	key	= reinterpret_cast<BYTE*>(keyAry);

	return (key[keyNo] & 0x80) ? true : false;
	
#elif defined(NK_USE_SDL)

	Uint8*	key	= reinterpret_cast<Uint8*>(keyAry);

	return key[keyNo] ? true : false;
	
#endif

	return false;
}


//===========================================================================
/*!	@brief	押されているか
	@param	keyNum: キーボード定数
	@return	true:押されている	false:離されている
*/
//===========================================================================
bool Keyboard::IsPress(s32 i) const
{
	assert((0 <= i) && (i < KEY_MAX));
	bool flag = m_state[i] & PRESS ? true : false;
	
	return flag;
}


//===========================================================================
/*!	@brief	押されたか
	@param	keyNum: キーボード定数
	@return	true:押された	false:それ以外
*/
//===========================================================================
bool Keyboard::IsPressed(s32 i) const
{
	assert((0 <= i) && (i < KEY_MAX));
	bool flag = m_state[i] & PRESSED ? true : false;
	
	return flag;
}


//===========================================================================
/*!	@brief	離されているか
	@param	keyNum: キーボード定数
	@return	true:離されている	false:押されている
*/
//===========================================================================
bool Keyboard::IsRelease(s32 i) const
{
	assert((0 <= i) && (i < KEY_MAX));
	bool flag = m_state[i] & RELEASE ? true : false;
	
	return flag;
}

//===========================================================================
/*!	@brief	押されたか
	@param	keyNum: キーボード定数
	@return	true:押された	false:それ以外
*/
//===========================================================================
bool Keyboard::IsReleased(s32 i) const
{
	assert((0 <= i) && (i < KEY_MAX));
	bool flag = m_state[i] & RELEASED ? true : false;

	return flag;
}

}	// namespace input
}	// namespace nk


