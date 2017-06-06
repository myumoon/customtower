//=============================================================================
/*!	@file	keyboardEventGetter.h

	@brief	�L�[�C�x���g�擾

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================


#ifndef __KEYBOARD_EVENT_GETTER_H__
#define __KEYBOARD_EVENT_GETTER_H__

#include "keyboardEventGetterBase.h"

namespace nk {
namespace system {

//=============================================================================
/*!
							�}�E�X�C�x���g�擾
*/
//=============================================================================
class KeyboardEventGetter: public KeyboardEventGetterBase {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�{�^�������`�F�b�N
	*/
	//===========================================================================
	virtual bool	IsOn( u32 button ) const;

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual void	Update( void );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	KeyboardEvent				m_event;				//!< �C�x���g�i�[
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			KeyboardEventGetter();
	virtual~KeyboardEventGetter();
};
	
}	// namespace system
}	// namespace nk


#endif  // __KEYBOARD_EVENT_GETTER_H__