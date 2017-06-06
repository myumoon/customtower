//=============================================================================
/*!	@file	mouse.h

	@brief	�}�E�X�N���X

	@author	��� ���V��
	@date	2012/02/16
	@todo	�Ȃ�
	@bug	�Ȃ�
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
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Mouse::Mouse( const Window* window ) : Input(), m_window( window )
{

	/* ������Ԃ������� */
	for(s32 i = 0; i < MOUSE_MAX; i++) {
		m_state[i] 			= 0;
	}

	m_eventGetter				= NULL;
	m_clickPressInterval		= DEFAULT_CLICK_PRESS_INTERVAL_MILLISEC;
	
#if defined(_WINDOWS)
// 	m_buttonIdx[CLICK_LEFT]		= VK_LBUTTON;
// 	m_buttonIdx[CLICK_RIGHT]	= VK_RBUTTON;
// 	m_buttonIdx[CLICK_WHEEL]	= VK_MBUTTON;
// 	//#error ������
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
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
Mouse::~Mouse()
{
	SafeDelete( m_flick );
}

//===========================================================================
/*!	@brief		�C�x���g�擾�Ґݒ�
	@param		eventGetter	�C�x���g�擾��
	@return		----
*/
//===========================================================================
void Mouse::SetEventGetter( const system::MouseEventGetterBase* eventGetter )
{
	m_eventGetter	= eventGetter;
}

//===========================================================================
/*!	@brief	�X�V
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Mouse::Update()
{
#if defined(_WINDOWS)
// 	BYTE	mouseState[256];
// 
// 	BOOL	result	= GetKeyboardState( mouseState );
// 	if( result == FALSE ) {
// 		// �K���ł��Ȃ�����
// 		return;
// 	}
// 
// 	if( m_window ) {
// 		POINT point;
// 		GetCursorPos( &point );
// 		ScreenToClient( m_window->GetWindowHandle(), &point );
// 	}

	
#elif defined(NK_USE_SDL)
	
	//---------------���W���擾---------------
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

	//	�{�^���̏����X�V
	//---------------------------------------
	for(s32 i = 0; i < MOUSE_MAX; i++) {

		/* ������ */
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

	// �V���O���N���b�N�E�_�u���N���b�N��ԍX�V
	{
		for( s32 i = 0; i < MOUSE_MAX; ++i ) {
			
			m_state[i]	&= ~(CLICK_DOUBLE | CLICK_SINGLE);
			
			if( IsPressed( i ) ) {

				// �_�u���N���b�N
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

				// �V���O���N���b�N
				// �N���b�N���ԂƗ��������Ԃ��Z���ꍇ�̂݃N���b�N�Ƃ݂Ȃ�
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


	// �t���b�N�X�V
	m_flick->Update();
}

//===========================================================================
/*!	@brief	������Ă��邩
	@param	mouseAry	�}�E�X��Ԋi�[�z��
	@param	mouseNo		�K���{�^��
	@return	true:������Ă���	false:������Ă���
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
/*!	@brief	������Ă��邩
	@param	i: MOUSE_NUM
	@return	true:������Ă���	false:������Ă���
*/
//===========================================================================
bool Mouse::IsPress(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & PRESS ? true : false;
	
	return flag;
}


//===========================================================================
/*!	@brief	�����ꂽ��
	@param	i: MOUSE_NUM
	@return	true:�����ꂽ	false:����ȊO
*/
//===========================================================================
bool Mouse::IsPressed(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & PRESSED ? true : false;
	
	return flag;
}


//===========================================================================
/*!	@brief	������Ă��邩
	@param	i: MOUSE_NUM
	@return	true:������Ă���	false:������Ă���
*/
//===========================================================================
bool Mouse::IsRelease(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & RELEASE ? true : false;
	
	return flag;
}

//===========================================================================
/*!	@brief	�����ꂽ��
	@param	i: MOUSE_NUM
	@return	true:�����ꂽ	false:����ȊO
*/
//===========================================================================
bool Mouse::IsReleased(s32 i) const
{
	assert((0 <= i) && (i < MOUSE_MAX));
	bool flag = m_state[i] & RELEASED ? true : false;

	return flag;
}

//===========================================================================
/*!	@brief	���W���擾
	@param	�Ȃ�
	@return	���W
*/
//===========================================================================
math::Vector Mouse::GetPos() const
{
	return m_pos;
}


//===========================================================================
/*!	@brief		�N���b�N���e���Ԃ�ݒ�
	@param		millisec	�~���b
	@return		----
*/
//===========================================================================
void Mouse::SetClickPressInterval( u64 millisec )
{
	m_clickPressInterval	= millisec;
	
}

//===========================================================================
/*!	@brief		�t���b�N���擾
	@param		----
	@return		----
*/
//===========================================================================
Flick* Mouse::GetFlick( void )
{
	
	return m_flick;
}

//===========================================================================
/*!	@brief		�t���b�N���擾
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