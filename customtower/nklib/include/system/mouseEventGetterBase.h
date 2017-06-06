//=============================================================================
/*!	@file	MouseEventGetterBase.h

	@brief	�}�E�X�C�x���g�擾

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================


#ifndef __MOUSE_EVENT_GETTER_BASE_H__
#define __MOUSE_EVENT_GETTER_BASE_H__

#include "eventGetterBase.h"
#include "mouseEvent.h"

namespace nk {
namespace system {


//=============================================================================
/*!
							�}�E�X�C�x���g�擾
*/
//=============================================================================
class MouseEventGetterBase : public EventGetterBase {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		��Ԏ擾
		@param		button		MouseEvent�̃C�x���g�萔
	*/
	//===========================================================================
	virtual bool	IsOn( u32 button ) const { return false; }

	//===========================================================================
	/*!	@brief		���W�擾
	*/
	//===========================================================================
	virtual void	GetPos( u32* x, u32* y ) const = 0;
	
private:
	//-----------------------���\�b�h------------------------

	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			MouseEventGetterBase() : EventGetterBase() {}
	virtual~MouseEventGetterBase() {}
};
	
}	// namespace system
}	// namespace nk





#endif  // __MOUSE_EVENT_GETTER_BASE_H__