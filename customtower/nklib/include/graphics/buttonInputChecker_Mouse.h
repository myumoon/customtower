//=============================================================================
/*!	@file	buttonInputChecker_Mouse.h

	@brief	�{�^���p�}�E�X���̓`�F�b�N

	@author	ryunosuke ide
	@date	2013.06.08
*/
//=============================================================================

#ifndef __BUTTON_INPUT_CHECKER_MOUSE_H__
#define __BUTTON_INPUT_CHECKER_MOUSE_H__

#include "button.h"
#include "../input/input.h"

namespace nk {

namespace graphics {

//=============================================================================
/*!
							�{�^���p�}�E�X���̓`�F�b�N
*/
//=============================================================================
class ButtonInputChecker_Mouse : public Button::EventChecker {
public:
	//-----------------------�^��`--------------------------
	static const	s32	INPUT_CHECK_BUTTON	= input::Mouse::CLICK_LEFT;
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	virtual void	Initialize( const input::Mouse* mouse );

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
// 	virtual void	Update( void );

	//===========================================================================
	/*!	@brief		�A�N�e�B�u�H
	*/
	//===========================================================================
	virtual bool	IsActive( const CheckInfo& info ) const;


	//===========================================================================
	/*!	@brief		������Ă���H
	*/
	//===========================================================================
	virtual bool	IsPress( void ) const;
	
	
private:
	//-----------------------���\�b�h------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------�����o�ϐ�-----------------------
	const input::Mouse*		m_mouse;		//! �}�E�X

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			ButtonInputChecker_Mouse( const input::Mouse* mouse );
			ButtonInputChecker_Mouse();
	virtual~ButtonInputChecker_Mouse();
};


// void						InitializeDefaultButtonInputChecker_Mouse( const input::Mouse* mouse );
// void						TerminateDefaultButtonInputChecker_Mouse( void );
// ButtonInputChecker_Mouse*	GetDefaultButtonInputChecker_Mouse( void );
	
}	// namespace graphics
	
}	// namespace nk





#endif  // __BUTTON_INPUT_CHECKER_MOUSE_H__