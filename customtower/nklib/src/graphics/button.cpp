//=============================================================================
/*!	@file	button.h

	@brief	�{�^��

	@author	ryunosuke ide
	@date	2013.06.07
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/graphics/button.h"

#include "../../include/utility/utility.h"
#include "../../include/graphics/buttonEventListener.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

	
}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

namespace nk {

namespace graphics {


}	// namespace graphics
	
}	// namespace nk

//---------------------------------�֐���`---------------------------------


namespace nk {

namespace graphics {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
Button::Button()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Button::~Button()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Button::_Init( void )
{
	SetTagName("button");
	
	m_spriteAnimation.resize( ANIMATION_MAX );
	for( u32 i = 0; i < m_spriteAnimation.size(); ++i ) {
		m_spriteAnimation[i].sprite	= NULL;
	}
	
	m_activeAnimation	= NULL;
	m_eventChecker		= NULL;
	m_prevPressedTime	= 0;

	m_updater			= NULL;
	m_eventListener		= NULL;
	m_screenID			= 0;

	m_outsizeFrame.SetColor( Color( 0x009cffff ) );	// �`���F
	m_outsizeFrame.SetRenderMode( Line::RENDER_MODE_2D );
	m_outsizeFrameSize.SetVector( 60, 30, 0 );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Button::_Term( void )
{
	if( m_updater ) {
		m_updater->OnExit( this );
	}
	SafeDelete( m_updater );

	for( u32 i = 0; i < m_spriteAnimation.size(); ++i ) {
		if( m_spriteAnimation[i].innerCreate ) {
			SafeDelete( m_spriteAnimation[i].sprite );
		}
	}
	
}

//===========================================================================
/*!	@brief		�C�x���g���X�i�[�ݒ�
	@param		eventChecker	�`�F�b�J�[
	@return		----
*/
//===========================================================================
void Button::SetEventListener( ButtonEventListener* listener )
{
	m_eventListener	= listener;
}

	
//===========================================================================
/*!	@brief		�C�x���g�`�F�b�J�[�ݒ�
	@param		eventChecker	�`�F�b�J�[
	@return		----
*/
//===========================================================================
void Button::SetEventChecker( EventChecker* eventChecker )
{
	m_eventChecker	= eventChecker;
}


//===========================================================================
/*!	@brief		�ʏ�A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Normal( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_NORMAL, sprite );
	
}


//===========================================================================
/*!	@brief		�A�N�e�B�u�A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Active( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_ACTIVE, sprite );
	
}



//===========================================================================
/*!	@brief		�������A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Pushed( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_PUSHED, sprite );
	
}




//===========================================================================
/*!	@brief		�z�[���h�A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Hold( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_HOLD, sprite );
	
}




//===========================================================================
/*!	@brief		���������A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Released( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_RELEASED, sprite );
	
}


//===========================================================================
/*!	@brief		���莞�A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Decide( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_DECIDE, sprite );
	
}



//===========================================================================
/*!	@brief		�����A�j���[�V�����o�^
	@param		idx			�C���f�b�N�X
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::RegisterButton( u32 idx, SpriteAnimation* sprite )
{
	ASSERT( idx < m_spriteAnimation.size(), "array size is not enough." );

	if( m_spriteAnimation[idx].sprite != NULL ) {
		if( m_spriteAnimation[idx].innerCreate ) {
			SafeDelete( m_spriteAnimation[idx].sprite );
		}
	}
	m_spriteAnimation[idx].sprite		= sprite;
	m_spriteAnimation[idx].innerCreate	= false;

	_SetScreenID();
}







//===========================================================================
/*!	@brief		�ʏ�A�j���[�V��������
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::CreateButton_Normal( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	CreateButton( ANIMATION_NORMAL, path, frame_w, frame_h, row, updateFrame, loop );

	SetSize( frame_w, frame_h );
}


//===========================================================================
/*!	@brief		�A�N�e�B�u�A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::CreateButton_Active( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	CreateButton( ANIMATION_ACTIVE, path, frame_w, frame_h, row, updateFrame, loop );
	
}



//===========================================================================
/*!	@brief		�������A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::CreateButton_Pushed( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame )
{
	CreateButton( ANIMATION_PUSHED, path, frame_w, frame_h, row, updateFrame, false );
	
}


//===========================================================================
/*!	@brief		�z�[���h�A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::CreateButton_Hold( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	CreateButton( ANIMATION_HOLD, path, frame_w, frame_h, row, updateFrame, loop );
	
}




//===========================================================================
/*!	@brief		���������A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::CreateButton_Released( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame )
{
	CreateButton( ANIMATION_RELEASED, path, frame_w, frame_h, row, updateFrame, false );
	
}


//===========================================================================
/*!	@brief		���莞�A�j���[�V�����ݒ�
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::CreateButton_Decide( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame )
{
	CreateButton( ANIMATION_DECIDE, path, frame_w, frame_h, row, updateFrame, false );
	
}



//===========================================================================
/*!	@brief		�A�j���[�V��������
	@param		idx			�C���f�b�N�X
	@param		sprite		�A�j���[�V�����摜
	@return		----
*/
//===========================================================================
void Button::CreateButton( u32 idx, const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	ASSERT( idx < m_spriteAnimation.size(), "array size is not enough." );

	if( m_spriteAnimation[idx].sprite != NULL ) {
		if( m_spriteAnimation[idx].innerCreate ) {
			SafeDelete( m_spriteAnimation[idx].sprite );
		}
	}

	SpriteAnimation*	anim	= new SpriteAnimation( path, frame_w, frame_h, row, updateFrame, loop );
	m_spriteAnimation[idx].sprite		= anim;
	m_spriteAnimation[idx].innerCreate	= true;
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void Button::Update( void )
{
	if( m_eventChecker == NULL ) {
		return;
	}
	
	
	m_eventChecker->Update();

	if( m_updater == NULL ) {
		m_updater	= new UpdateNormal();
		m_updater->OnEnter( this );
	}
	
	if( m_activeAnimation ) {
		m_activeAnimation->Update();
	}
	Updater*	nextUpdater	= m_updater->OnUpdate( this );
	
	if( nextUpdater != NULL ) {
		if( nextUpdater != m_updater ) {
			m_updater->OnExit( this );
			SafeDelete( m_updater );

			m_updater	= nextUpdater;
			m_updater->OnEnter( this );
		}
	}
	
}

//===========================================================================
/*!	@brief		�C�x���g�`�F�b�J�[�擾
	@param		----
	@return		----
*/
//===========================================================================
const Button::EventChecker* Button::GetEventChecker( void ) const
{

	return m_eventChecker;
}


//===========================================================================
/*!	@brief		�A�N�e�B�u�A�j���[�V�����ݒ�
	@param		animType	�A�j���[�V����
	@return		----
*/
//===========================================================================
void Button::SetActiveAnimation( ANIMATION animType )
{
	SpriteAnimation*	nextAnim	= m_spriteAnimation[animType].sprite;
	if( nextAnim ) {
		m_activeAnimation	= nextAnim;
	}
	
}


//===========================================================================
/*!	@brief		�ݒ�\�Ȃ�true��Ԃ�
	@param		----
	@return		----
*/
//===========================================================================
bool Button::IsEnableSetting( void ) const
{

	return ((m_activeAnimation != NULL) && (m_eventChecker != NULL));
}



//===========================================================================
/*!	@brief		�A�j���[�V�����J�n
	@param		loop	���[�v
	@return		----
*/
//===========================================================================
void Button::StartActiveAnimation( bool loop )
{
	if( m_activeAnimation ) {
		m_activeAnimation->SetVisible( true );
		m_activeAnimation->SetAnimationLoop( loop );
		m_activeAnimation->Start();
	}
	
}




//===========================================================================
/*!	@brief		�A�j���[�V������~
	@param		----
	@return		----
*/
//===========================================================================
void Button::StopActiveAnimation( void )
{
	if( m_activeAnimation ) {
		m_activeAnimation->Stop();
		m_activeAnimation->SetVisible( false );
	}
	
}


//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void Button::Draw( void )
{
	if( m_activeAnimation ) {
		m_activeAnimation->Draw( GetPos() );
	}
	// �X�v���C�g���ݒ肳��Ă��Ȃ������牼�Ő��Ń{�^���̘g�����
	else {
		const math::Vector	lu( GetPos().x, 						GetPos().y							);	// ����
		const math::Vector	ld( GetPos().x, 						GetPos().y + m_outsizeFrameSize.y	);	// ����
		const math::Vector	rd( GetPos().x + m_outsizeFrameSize.x, GetPos().y + m_outsizeFrameSize.y	);	// �E��
		const math::Vector	ru( GetPos().x + m_outsizeFrameSize.x, GetPos().y							);	// ����

		m_outsizeFrame.ClearPoints();
		m_outsizeFrame.AddPoint( lu );
		m_outsizeFrame.AddPoint( ld );
		m_outsizeFrame.AddPoint( rd );
		m_outsizeFrame.AddPoint( ru );
		m_outsizeFrame.AddPoint( lu );

		m_outsizeFrame.Draw();
	}
	
}



//===========================================================================
/*!	@brief		�O�g�T�C�Y�ݒ�
	@param		size	�T�C�Y
	@return		----
*/
//===========================================================================
void Button::SetOutsideFrameSize( const math::Vector& size )
{
	m_outsizeFrameSize	= size;
	
}



//===========================================================================
/*!	@brief		�O�g�F�ݒ�
	@param		color	�F
	@return		----
*/
//===========================================================================
void Button::SetOutsideFrameColor( const Color& color )
{
	m_outsizeFrame.SetColor( color );
	
}



//===========================================================================
/*!	@brief		���X�i�[�ɒʒm
	@param		----
	@return		----
*/
//===========================================================================
void Button::_CallEventListener( EVENT_LISTENER_CALLBACK callbackType )
{
	const EventCallback	eventCallbacks[] = {
		&nk::graphics::ButtonEventListener::OnCursorOver,
		&nk::graphics::ButtonEventListener::OnCursorOut,
		&nk::graphics::ButtonEventListener::OnCursorDownStart,
		&nk::graphics::ButtonEventListener::OnCursorDownEnd,
		&nk::graphics::ButtonEventListener::OnCursorUpStart,
		&nk::graphics::ButtonEventListener::OnCursorUpEnd,
		&nk::graphics::ButtonEventListener::OnHold,
	};

	if( m_eventListener ) {
		(m_eventListener->*eventCallbacks[callbackType])( this );
	}
	
}

	
//--------------------------------�X�V--------------------------------


	

//===========================================================================
/*!	@brief		�ʏ����
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateNormal::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_NORMAL );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( true );		
	}
}

//===========================================================================
/*!	@brief		�ʏ�X�V
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateNormal::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		Button::EventChecker::CheckInfo	info( button->m_activeAnimation, button->GetPos() );
		const bool	active	= button->GetEventChecker()->IsActive( info );

		if( active ) {
			button->SetActiveAnimation( Button::ANIMATION_ACTIVE );
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_OVER );
			return new Button::UpdateActive();
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief		�ʏ����
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateNormal::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}
	
}
	
//===========================================================================
/*!	@brief		�A�N�e�B�u����
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateActive::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_ACTIVE );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( true );
	}
	m_pressTime		= 0;
	m_pushable		= (button->GetEventChecker()->IsPress() == false);
	m_reserveDecide	= false;
}

//===========================================================================
/*!	@brief		�A�N�e�B�u�X�V
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateActive::OnUpdate( Button* button )
{
	static const u32	MOVE_HOLD_MILLISEC	= 100;

	// ����\�񂪓����Ă����炻�����������
	if( m_reserveDecide ) {
		if( button->m_activeAnimation->IsEnd() ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END );
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_START );
			return new Button::UpdateDecide();
		}
	}
	else {
		if( button->IsEnableSetting() ) {
			Button::EventChecker::CheckInfo	info( button->m_activeAnimation, button->GetPos() );
			const bool	active	= button->GetEventChecker()->IsActive( info );
			const bool	press	= button->GetEventChecker()->IsPress();	

			if( active == false ) {
				button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_OUT );
				return new Button::UpdateRelease();
			}

			m_pushable	|= (button->GetEventChecker()->IsPress() == false);

			if( press ) {
				if(/* m_pushable &&*/ (m_pressTime == 0) ) {
					// �A�N�e�B�u�A�j�����I��
					button->StopActiveAnimation();

					// �����A�j���Đ�
					button->SetActiveAnimation( ANIMATION_PUSHED );
					if( button->IsEnableSetting() ) {
						button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_START );
						button->StartActiveAnimation( false );
					}
					
					m_pressTime	= GetTimeMillSec();
				}
				else if( (MOVE_HOLD_MILLISEC <= m_pressTime) && (button->m_activeAnimation->IsEnd()) ) {
					button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END );
					button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_HOVER );
					return new Button::UpdateHold();
				}
			}
			else {
				if( m_pressTime != 0 ) {
					if( button->m_activeAnimation->IsEnd() ) {
						button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END );
						button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_START );
						return new Button::UpdateDecide();
					}
					else {
						m_reserveDecide	= true;
					}
				}
			}
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		�A�N�e�B�u�ޏ�
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateActive::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}

	
//===========================================================================
/*!	@brief		�z�[���h����
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateHold::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_HOLD );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( true );
	}
	
}

//===========================================================================
/*!	@brief		�z�[���h�X�V
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateHold::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		Button::EventChecker::CheckInfo	info( button->m_activeAnimation, button->GetPos() );
		const bool	active	= button->GetEventChecker()->IsActive( info );
		const bool	press	= button->GetEventChecker()->IsPress();	

		if( active == false ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_OUT );
			return new Button::UpdateRelease();
		}

		if( press == false ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_START );
			return new Button::UpdateDecide();
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		�z�[���h�ޏ�
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateHold::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}



//===========================================================================
/*!	@brief		�����[�X����
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateRelease::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_RELEASED );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( false );
	}
	
}

//===========================================================================
/*!	@brief		�����[�X�X�V
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateRelease::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		if( button->m_activeAnimation->IsEnd() ) {
			return new Button::UpdateNormal();
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		�����[�X�ޏ�
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateRelease::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}



//===========================================================================
/*!	@brief		�������
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateDecide::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_DECIDE );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( false );
	}
	
}

//===========================================================================
/*!	@brief		����X�V
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateDecide::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		if( button->m_activeAnimation->IsEnd() ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_END );
			return new Button::UpdateNormal();
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		����ޏ�
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateDecide::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}


//===========================================================================
/*!	@brief		�X�N���[��ID�ݒ�
	@param		screenID	id
	@return		----
*/
//===========================================================================
void Button::SetScreen( s32 screenID )
{
	m_screenID	= screenID;

	_SetScreenID();
	
}


//===========================================================================
/*!	@brief		�X�N���[��ID�ݒ�
	@param		----
	@return		----
*/
//===========================================================================
void Button::_SetScreenID( void )
{
	for( u32 i = 0; i < m_spriteAnimation.size(); ++i ) {
		if( m_spriteAnimation[i].sprite ) {
			m_spriteAnimation[i].sprite->SetScreenId( m_screenID );
		}
	}
}

	
}	// namespace graphics
	
}	// namespace nk