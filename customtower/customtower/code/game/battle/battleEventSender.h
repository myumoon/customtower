//=============================================================================
/*!	@file	battleEventSender.h

	@brief	UI�C�x���g���X�i�[

	@author	ryunosuke ide
	@date	2013.06.24
*/
//=============================================================================

#ifndef __BATTLE_EVENT_SENDER_H__
#define __BATTLE_EVENT_SENDER_H__

#include "input/input.h"
#include "graphics/button.h"
#include "graphics/buttonEventListener.h"
#include "battleExecutor.h"


namespace game {

namespace battle {

//=============================================================================
/*!
							�o�g���C�x���g���X�i�[
*/
//=============================================================================
class BattleEventSender : nk::graphics::ButtonEventListener {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�o�g���ݒ�
	*/
	//===========================================================================
	void		SetBattleExecutor( BattleExecutor* battle );

	//===========================================================================
	/*!	@brief		�L�[�{�[�h�ݒ�
	*/
	//===========================================================================
	void		SetKeyboard( const nk::input::Keyboard* keyboard );

	//===========================================================================
	/*!	@brief		�}�E�X�ݒ�
	*/
	//===========================================================================
	void		SetMouse( const nk::input::Mouse* mouse );


protected:
	//===========================================================================
	/*!	@brief		���ꎞ
	*/
	//===========================================================================
	virtual void	OnCursorOver( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�ޏꎞ
	*/
	//===========================================================================
	virtual void	OnCursorOut( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����J�n��)
	*/
	//===========================================================================
	virtual void	OnCursorDownStart( nk::graphics::Button* eventButton );

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����I����)
	*/
	//===========================================================================
	virtual void	OnCursorDownEnd( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����J�n��)
	*/
	//===========================================================================
	virtual void	OnCursorUpStart( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����I����)
	*/
	//===========================================================================
	virtual void	OnCursorUpEnd( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�z�[���h��
	*/
	//===========================================================================
	virtual void	OnHold( nk::graphics::Button* eventButton ) {}

private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	BattleExecutor*				m_battleExecutor;	//!< �o�g�����s
	const nk::input::Keyboard*	m_keyboard;			//!< �L�[�{�[�h
	const nk::input::Mouse*		m_mouse;			//!< �}�E�X

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			BattleEventSender();
	virtual~BattleEventSender();
};
	
}	// namespace battle
	
}	// namespace game



#endif  // __BATTLE_EVENT_SENDER_H__