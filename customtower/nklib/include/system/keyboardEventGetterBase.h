//=============================================================================
/*!	@file	keyboardEventGetterBase.h

	@brief	�L�[�{�[�h�C�x���g�擾�C���^�[�t�F�[�X

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

#ifndef __KEYBOARD_EVENT_GETTER_BASE_H__
#define __KEYBOARD_EVENT_GETTER_BASE_H__

#include "eventGetterBase.h"
#include "keyboardEvent.h"

namespace nk {
namespace system {


//=============================================================================
/*!
					�L�[�{�[�h�C�x���g�擾�C���^�[�t�F�|�X
*/
//=============================================================================
class KeyboardEventGetterBase : public EventGetterBase {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�C�x���g�擾
		@param		KeyboardEvent�萔
	*/
	//===========================================================================
	virtual bool	IsOn( u32 key ) const { return false; }
	
private:
	//-----------------------���\�b�h------------------------

	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			KeyboardEventGetterBase() : EventGetterBase() {}
	virtual~KeyboardEventGetterBase() {}
};
	
}	// namespace system
}	// namespace nk






#endif  // __KEYBOARD_EVENT_GETTER_BASE_H__