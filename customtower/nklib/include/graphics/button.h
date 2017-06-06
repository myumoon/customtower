//=============================================================================
/*!	@file	button.h

	@brief	�{�^��

	@author	ryunosuke ide
	@date	2013.06.07
*/
//=============================================================================


#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "../math/vector.h"
#include "layoutParts.h"
#include "spriteAnimation.h"
#include "buttonEventListener.h"
#include "line.h"


namespace nk {

namespace graphics {

class SpriteAnimation;

//=============================================================================
/*!
								�{�^��
*/
//=============================================================================
class Button : public LayoutParts {
public:
	//-----------------------�^��`--------------------------

	//! ��ԃ`�F�b�J�[
	class EventChecker {
	public:
		struct CheckInfo {
			SpriteAnimation*	sprite;
			math::Vector		pos;
			
			CheckInfo() {
				this->sprite	= NULL;
			}
			CheckInfo( SpriteAnimation* sprite, const math::Vector& pos ) {
				this->sprite	= sprite;
				this->pos		= pos;
			}
		};
	public:
		virtual void	Update( void ) 							{}						//!< ��ԍX�V
		virtual bool	IsActive( const CheckInfo& info ) const	{ return true; }		//!< �A�N�e�B�u�H
		virtual bool	IsPress( void ) const					{ return false; }		//!< ������Ă���H
	};
	
	//! �A�j���[�V�������
	enum ANIMATION {
		ANIMATION_NORMAL,			//!< �ʏ�
		ANIMATION_ACTIVE,			//!< �A�N�e�B�u
		ANIMATION_PUSHED,			//!< �����ꂽ
		ANIMATION_HOLD,				//!< �z�[���h
		ANIMATION_RELEASED,			//!< �����ꂽ
		ANIMATION_DECIDE,			//!< ����
		
		ANIMATION_MAX,				//!< �A�j���[�V�����ő�
	};

	//! �X�v���C�g���
	struct SpriteInfo {
		SpriteAnimation*	sprite;			//!< �X�v���C�g
		bool				innerCreate;	//!< ���������H

		//! �R���X�g���N�^
		SpriteInfo() {
			this->sprite		= NULL;
			this->innerCreate	= false;
		}
	};

	typedef std::vector<SpriteInfo>	VecSprite;

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�`��X�N���[���ݒ�
	*/
	//===========================================================================
	void			SetScreen( s32 screenID );

	//===========================================================================
	/*!	@brief		�C�x���g���X�i�[�ݒ�
	*/
	//===========================================================================
	void			SetEventListener( ButtonEventListener* listener );

	//===========================================================================
	/*!	@brief		�C�x���g�`�F�b�N�����ݒ�
	*/
	//===========================================================================
	void			SetEventChecker( EventChecker* eventChecker );	

	//===========================================================================
	/*!	@brief		�ʏ�A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			RegisterButton_Normal( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		�A�N�e�B�u���A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			RegisterButton_Active( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		�����ꂽ���A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			RegisterButton_Pushed( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		�������ςȂ����A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			RegisterButton_Hold( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		�����ꂽ���A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			RegisterButton_Released( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		���莞�A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			RegisterButton_Decide( SpriteAnimation* sprite );


	//===========================================================================
	/*!	@brief		�ʏ�A�j���[�V��������
	*/
	//===========================================================================
	void			CreateButton_Normal( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop = true );

	//===========================================================================
	/*!	@brief		�A�N�e�B�u���A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			CreateButton_Active( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop = true );

	//===========================================================================
	/*!	@brief		�����ꂽ���A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			CreateButton_Pushed( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame );

	//===========================================================================
	/*!	@brief		�������ςȂ����A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			CreateButton_Hold( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop = true );

	//===========================================================================
	/*!	@brief		�����ꂽ���A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			CreateButton_Released( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame );

	//===========================================================================
	/*!	@brief		���莞�A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void			CreateButton_Decide( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame );


	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual void	UpdateParts( void )	{ if( IsActive() ) { Update(); } }

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	virtual void	DrawParts( void ) { if( IsVisible() ) { Draw(); } }
	
	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual void	Update( void );

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	void			Draw( void );

	//===========================================================================
	/*!	@brief		�O�g�ݒ�
	*/
	//===========================================================================
	void			SetOutsideFrameSize( const math::Vector& size );	//!< �T�C�Y
	void			SetOutsideFrameColor( const Color& color );			//!< �F


protected:
	//===========================================================================
	/*!	@brief		�A�j���[�V�����ݒ�
	*/
	//===========================================================================
	void					RegisterButton( u32 idx, SpriteAnimation* sprite );
	
	//===========================================================================
	/*!	@brief		�A�j���[�V��������
	*/
	//===========================================================================
	void					CreateButton( u32 idx, const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop );

	//===========================================================================
	/*!	@brief		�C�x���g�`�F�b�J�[�擾
	*/
	//===========================================================================
	const EventChecker*		GetEventChecker( void ) const;

	//===========================================================================
	/*!	@brief		�摜�`�F�b�N
	*/
	//===========================================================================
	bool					IsEnableSetting( void ) const;

	//===========================================================================
	/*!	@brief		�A�N�e�B�u�A�j���[�V������ݒ�
	*/
	//===========================================================================
	void					SetActiveAnimation( ANIMATION animType );

	//===========================================================================
	/*!	@brief		�A�j���[�V�����J�n
	*/
	//===========================================================================
	void					StartActiveAnimation( bool loop );

	//===========================================================================
	/*!	@brief		�A�j���[�V������~
	*/
	//===========================================================================
	void					StopActiveAnimation( void );


	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	enum EVENT_LISTENER_CALLBACK {
		EVENT_LISTENER_CALLBACK_CURSOR_OVER,
		EVENT_LISTENER_CALLBACK_CURSOR_OUT,
		EVENT_LISTENER_CALLBACK_CURSOR_DOWN_START,
		EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END,
		EVENT_LISTENER_CALLBACK_CURSOR_UP_START,
		EVENT_LISTENER_CALLBACK_CURSOR_UP_END,
		EVENT_LISTENER_CALLBACK_CURSOR_HOVER,
		
		EVENT_LISTENER_CALLBACK_MAX,
	};
		
	typedef void (nk::graphics::ButtonEventListener::*EventCallback)( nk::graphics::Button* );

	
	//===========================================================================
	/*!	@brief		���X�i�[�ɒʒm
	*/
	//===========================================================================
	void		_CallEventListener( EVENT_LISTENER_CALLBACK eventType );

	//===========================================================================
	/*!	@brief		�X�N���[��ID�ݒ�
	*/
	//===========================================================================
	void		_SetScreenID( void );

private:
	//-----------------------�^��`--------------------------
	//! �X�V
	//! ���̃��[�h��OnUpdate�ŕԂ�
	class Updater {
	public:
		virtual void		OnEnter( Button* button )  {}				//!< ����
		virtual Updater*	OnUpdate( Button* button ) { return NULL; }	//!< �X�V
		virtual void		OnExit( Button* button )   {}				//!< �ޏ�
	};
	//! �ʏ펞
	class UpdateNormal : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	//! �A�N�e�B�u��
	class UpdateActive : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	private:
		u64					m_pressTime;
		bool				m_pushable;
		bool				m_reserveDecide;
	};
	//! �z�[���h��
	class UpdateHold : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	//! �����[�X��
	class UpdateRelease : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	//! ���莞
	class UpdateDecide : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	
private:
	//----------------------�����o�ϐ�-----------------------
	VecSprite					m_spriteAnimation;		//!< �A�j���[�V����
	SpriteAnimation*			m_activeAnimation;		//!< �A�N�e�B�u�ȃA�j���[�V����
	EventChecker*				m_eventChecker;			//!< �C�x���g�`�F�b�J�[
	u32							m_prevPressedTime;		//!< �O�񉟉�����
	Updater*					m_updater;				//!< �X�V����
	s32							m_screenID;				//!< �X�N���[��ID

	ButtonEventListener*		m_eventListener;		//!< �C�x���g���X�i�[

	//! ���`��ݒ�
	Line						m_outsizeFrame;			//!< �O�g
	math::Vector				m_outsizeFrameSize;		//!< �O�g�T�C�Y
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Button();
	virtual~Button();
};


	
}	// namespace graphics
	
}	// namespace nk


#endif  // __BUTTON_H__