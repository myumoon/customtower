//=============================================================================
/*!	@file	mouse.h

	@brief	マウスクラス

	@author	井手 竜之介
	@date	2012/02/16
	@todo	なし
	@bug	なし
*/
//=============================================================================

#include "../../include/input/mouse.h"
#include "../../include/general.h"
#include "../../include/system/window.h"
#include "../../include/utility/utility.h"
#include "../../include/input/flick.h"

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
Mouse::Mouse( const Window* window ) : Input(), m_window( window )
{

	/* 押下状態を初期化 */
	for(s32 i = 0; i < MOUSE_MAX; i++) {
		m_state[i] 			= 0;
	}

	m_eventGetter				= NULL;
	m_clickPressInterval		= DEFAULT_CLICK_PRESS_INTERVAL_MILLISEC;
	
#if defined(_WINDOWS)
// 	m_buttonIdx[CLICK_LEFT]		= VK_LBUTTON;
// 	m_buttonIdx[CLICK_RIGHT]	= VK_RBUTTON;
// 	m_buttonIdx[CLICK_WHEEL]	= VK_MBUTTON;
// 	//#error 未実装
// 	m_buttonIdx[WHEEL_UP]		= VK_MBUTTON;
// 	m_buttonIdx[WHEEL_DOWN]		= VK_MBUTTON;
	
#elif defined(NK_USE_SDL)
// 	m_buttonIdx[CLICK_LEFT]		= SDL_BUTTON( SDL_BUTTON_LEFT		);
// 	m_buttonIdx[CLICK_RIGHT]	= SDL_BUTTON( SDL_BUTTON_RIGHT		);
// 	m_buttonIdx[CLICK_WHEEL]	= SDL_BUTTON( SDL_BUTTON_MIDDLE		);
// 	m_buttonIdx[WHEEL_UP]		= SDL_BUTTON( SDL_BUTTON_WHEELUP	);
// 	m_buttonIdx[WHEEL_DOWN]		= SDL_BUTTON( SDL_BUTTON_WHEELDOWN	);
#endif
	m_buttonIdx[CLICK_LEFT]		= system::MouseEvent::LEFT;
	m_buttonIdx[CLICK_RIGHT]	= system::MouseEvent::RIGHT;
	m_buttonIdx[CLICK_WHEEL]	= system::MouseEvent::WHEEL;
	m_buttonIdx[WHEEL_UP]		= system::MouseEvent::WHEEL_UP;
	m_buttonIdx[WHEEL_DOWN]		= system::MouseEvent::WHEEL_DOWN;

	m_flick	= new Flick();
	m_flick->Initialize( this );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
Mouse::~Mouse()
{
	SafeDelete( m_flick );
}

//===========================================================================
/*!	@brief		イベント取得者設定
	@param		eventGetter	イベント取得者
	@return		----
*/
//===========================================================================
void Mouse::SetEventGetter( const system::MouseEventGetterBase* eventGetter )
{
	m_eventGetter	= eventGetter;
}

//===========================================================================
/*!	@brief	更新
	@param	なし
	@return	なし
*/
//===========================================================================
void Mouse::Update()
{
#if defined(_WINDOWS)
// 	BYTE	mouseState[256];
// 
// 	BOOL	result	= GetKeyboardState( mouseState );
// 	if( result == FALSE ) {
// 		// 習得できなかった
// 		return;
// 	}
// 
// 	if( m_window ) {
// 		POINT point;
// 		GetCursorPos( &point );
// 		ScreenToClient( m_window->GetWindowHandle(), &point );
// 	}

	
#elif defined(NK_USE_SDL)
	
	//---------------座標を取得---------------
// 	s32 x, y;
// 	Uint8 	state 		= SDL_GetMouseState(&x, &y);
// 	Uint8*	mouseState	= &state;
// 	m_pos.x = static_cast<f32>(x);
// 	m_pos.y = static_cast<f32>(y);
// 	m_pos.z = 0.0f;
	
#endif

	if( m_eventGetter ) {
		u32	x, y;
		m_eventGetter->GetPos( &x, &y );
		m_pos.x = static_cast<f32>(x);
		m_pos.y = static_cast<f32>(y);
		m_pos.z = 0.0f;
	}

	//	ボタンの情報を更新
	//---------------------------------------
	for(s32 i = 0; i < MOUSE_MAX; i++) {

		/* 初期化 */
		m_state[i] &= ~(PRESSED | RELEASED);


// 		if( _IsPress( mouseState, m_buttonIdx[i] ) ) {
		if( _IsPress( m_buttonIdx[i] ) ) {
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

	// シングルクリック・ダブルクリック状態更新
	{
		for( s32 i = 0; i < MOUSE_MAX; ++i ) {
			
			m_state[i]	&= ~(CLICK_DOUBLE | CLICK_SINGLE);
			
			if( IsPressed( i ) ) {

				// ダブルクリック
				if( m_clickInfo[i].state == RELEASED ) {
					const u64	diffTime	= GetTimeMillSec() - m_clickInfo[i].time;
					if( diffTime <= m_clickPressInterval ) {
						m_state[i]				|= CLICK_DOUBLE;
						m_clickInfo[i].state	= NONE;
					}
					else {
						m_clickInfo[i].state	= NONE;
						m_clickInfo[i].time		= 0;
					}
				}
				else {
					m_clickInfo[i].state	= PRESSED;
					m_clickInfo[i].time		= GetTimeMillSec();
				}
			}
			else if( IsReleased( i ) ) {

				// シングルクリック
				// クリック時間と離した時間が短い場合のみクリックとみなす
				const u64	diffTime	= GetTimeMillSec() - m_clickInfo[i].time;
				if( diffTime <= m_clickPressInterval ) {
					m_clickInfo[i].state	= RELEASED;
					m_clickInfo[i].time		= GetTimeMillSec();

					m_state[i]				|= CLICK_SINGLE;
				}
				else {
					m_clickInfo[i].state	= NONE;
					m_clickInfo[i].time		= 0;
				}
			}
		}
	}


	// フリック更新
	m_flick->Update();
}

//===========================================================================
/*!	@brief	押されているか
	@param	mouseAry	マウス状態格納配列
	@param	mouseNo		習得ボタン
	@return	true:押されている	false:離されている
*/
//===========================================================================
// bool Mouse::_IsPress( void* mouseAry, s32 mouseNo ) const
bool Mouse::_IsPress( u32 mouseNo ) const
{
	if( m_eventGetter ) {
		return m_eventGetter->IsOn( mouseNo );
	}
	
// #if defined(_WINDOWS)
// 	BYTE*	mouse	= reinterpret_cast<BYTE*>(mouseAry);
// 
// 	return (mouse[mouseNo] & 0x80) ? true : false;
// 	
// #elif defined(NK_USE_SDL)
// 
// 	Uint8*	mouse	= reinterpret_cast<Uint8*>(mouseAry);
// 
// 	return (*mouse & mouseNo) ? true : false;
// 	
// #endif

	return false;
}



//===========================================================================
/*!	@brief	押されているか
	@param	i: MOUSE_NUM
	@return	true:押されている	false:離されている
*/
//===========================================================================
bool Mouse::IsPress(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & PRESS ? true : false;
	
	return flag;
}


//===========================================================================
/*!	@brief	押されたか
	@param	i: MOUSE_NUM
	@return	true:押された	false:それ以外
*/
//===========================================================================
bool Mouse::IsPressed(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & PRESSED ? true : false;
	
	return flag;
}


//===========================================================================
/*!	@brief	離されているか
	@param	i: MOUSE_NUM
	@return	true:離されている	false:押されている
*/
//===========================================================================
bool Mouse::IsRelease(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & RELEASE ? true : false;
	
	return flag;
}

//===========================================================================
/*!	@brief	押されたか
	@param	i: MOUSE_NUM
	@return	true:押された	false:それ以外
*/
//===========================================================================
bool Mouse::IsReleased(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & RELEASED ? true : false;

	return flag;
}

//===========================================================================
/*!	@brief	座標を取得
	@param	なし
	@return	座標
*/
//===========================================================================
math::Vector Mouse::GetPos() const
{
	return m_pos;
}


//===========================================================================
/*!	@brief		クリック許容時間を設定
	@param		millisec	ミリ秒
	@return		----
*/
//===========================================================================
void Mouse::SetClickPressInterval( u64 millisec )
{
	m_clickPressInterval	= millisec;
	
}

//===========================================================================
/*!	@brief		フリック情報取得
	@param		----
	@return		----
*/
//===========================================================================
Flick* Mouse::GetFlick( void )
{
	
	return m_flick;
}

//===========================================================================
/*!	@brief		フリック情報取得
	@param		----
	@return		----
*/
//===========================================================================
const Flick* Mouse::GetFlick( void ) const
{
	
	return m_flick;
}

}	// namespace input
}	// namespace nk