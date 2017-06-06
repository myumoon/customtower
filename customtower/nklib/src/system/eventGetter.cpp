//=============================================================================
/*!	@file	eventGetter.h

	@brief	�C�x���g�擾

	@author	ryunosuke ide
	@date	2013.06.29
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------

#if defined(NK_USE_SDL)
#include <SDL/SDL.h>
#else
#endif

#include "../../include/system/eventGetter.h"
#include "../../include/general.h"

//--------------------------------define��`--------------------------------



//--------------------------------static--------------------------------
namespace nk {
namespace system {

EventGetter* EventGetter::m_instance	= NULL;

//===========================================================================
/*!	@brief		������
	@param		----
	@return		----
*/
//===========================================================================
void EventGetter::Initialize( void )
{
	if( m_instance == NULL ) {
		m_instance	= new EventGetter();
	}
}

//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		----
*/
//===========================================================================
void EventGetter::Terminate( void )
{
	if( m_instance ) {
		delete m_instance;
		m_instance	= NULL;
	}
}

//===========================================================================
/*!	@brief		�C���X�^���X�擾
	@param		----
	@return		----
*/
//===========================================================================
EventGetter* EventGetter::GetInstance( void )
{

	return m_instance;
}

}	// namespace system
}	// namespace nk

//---------------------------------�֐���`---------------------------------


namespace nk {
namespace system {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
EventGetter::EventGetter()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
EventGetter::~EventGetter()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void EventGetter::_Init( void )
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void EventGetter::_Term( void )
{

}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void EventGetter::UpdateEvent( void )
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );

	const u32	mouseX	= m_mouseEvent.x;
	const u32	mouseY	= m_mouseEvent.y;
	
// 	m_mouseEvent.Clear();
// 	m_keyboardEvent.Clear();
// 	m_systemEvent.Clear();
// 	m_mouseEvent.x	= mouseX;
// 	m_mouseEvent.y	= mouseY;

#if defined(NK_USE_SDL)
	{
		SDL_Event event;

		// �z�C�[����on,off�����C�x���g����̂ł����ōŏ�off�ɂ��Ă���
		m_mouseEvent.EventOff( MouseEvent::WHEEL_UP );
		m_mouseEvent.EventOff( MouseEvent::WHEEL_DOWN );

		while ( SDL_PollEvent( &event ) ) {
			
			switch ( event.type ) {
				// �}�E�X�ړ�
				case SDL_MOUSEMOTION : {
// 					event.motion.xrel;
// 					event.motion.yrel;
					m_mouseEvent.x	= event.motion.x;
					m_mouseEvent.y	= event.motion.y;
				} break;

				// �}�E�X�{�^��On
				case SDL_MOUSEBUTTONDOWN : {
					
					switch( event.button.button ) {
						case SDL_BUTTON_RIGHT : {
							m_mouseEvent.EventOn( MouseEvent::RIGHT );
						} break;

						case SDL_BUTTON_LEFT : {
							m_mouseEvent.EventOn( MouseEvent::LEFT );
						} break;

						case SDL_BUTTON_MIDDLE : {
							m_mouseEvent.EventOn( MouseEvent::WHEEL );
						} break;

						case SDL_BUTTON_WHEELUP : {
							m_mouseEvent.EventOn( MouseEvent::WHEEL_UP );
						} break;

						case SDL_BUTTON_WHEELDOWN : {
							m_mouseEvent.EventOn( MouseEvent::WHEEL_DOWN );
						} break;
					}
					
					m_mouseEvent.x	= event.button.x;
					m_mouseEvent.y	= event.button.y;
					
				} break;

				// �}�E�X�{�^��Off
				case SDL_MOUSEBUTTONUP : {
					
					switch( event.button.button ) {
						case SDL_BUTTON_RIGHT : {
							m_mouseEvent.EventOff( MouseEvent::RIGHT );
						} break;

						case SDL_BUTTON_LEFT : {
							m_mouseEvent.EventOff( MouseEvent::LEFT );
						} break;

						case SDL_BUTTON_MIDDLE : {
							m_mouseEvent.EventOff( MouseEvent::WHEEL );
						} break;

// 						case SDL_BUTTON_WHEELUP : {
// 							m_mouseEvent.EventOff( MouseEvent::WHEEL_UP );
// 						} break;
// 
// 						case SDL_BUTTON_WHEELDOWN : {
// 							m_mouseEvent.EventOff( MouseEvent::WHEEL_DOWN );
// 						} break;
					}
					
					m_mouseEvent.x	= event.button.x;
					m_mouseEvent.y	= event.button.y;
					
				} break;
				
				case SDL_QUIT : {
					m_systemEvent.EventOn( SystemEvent::QUIT );
				} break;

				// �L�[�_�E��
				case SDL_KEYDOWN : {
				} break;
			}
			
		}

		// �L�[���̓C�x���g
		{
		}
	}
#else
#endif
}

//===========================================================================
/*!	@brief		�}�E�X�C�x���g�擾
	@param		----
	@return		----
*/
//===========================================================================
const MouseEvent& EventGetter::GetMouseEvent( void ) const
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	return m_mouseEvent;
}

//===========================================================================
/*!	@brief		�L�[�{�[�h�C�x���g�擾
	@param		----
	@return		----
*/
//===========================================================================
const KeyboardEvent& EventGetter::GetKeyboardEvent( void ) const
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	return m_keyboardEvent;
}


//===========================================================================
/*!	@brief		�V�X�e���C�x���g�擾
	@param		----
	@return		----
*/
//===========================================================================
const SystemEvent& EventGetter::GetSystemEvent( void ) const
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	return m_systemEvent;
}
	
}	// namespace system
}	// namespace nk
