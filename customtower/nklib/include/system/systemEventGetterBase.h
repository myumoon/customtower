//=============================================================================
/*!	@file	systemEventGetterBase.h

	@brief	�V�X�e���C�x���g�擾�C���^�[�t�F�[�X

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================


#ifndef __SYSTEM_EVENT_GETTER_BASE_H__
#define __SYSTEM_EVENT_GETTER_BASE_H__

#include "eventGetterBase.h"
#include "systemEvent.h"



namespace nk {
namespace system {

//=============================================================================
/*!
					�V�X�e���C�x���g�擾�C���^�[�t�F�[�X
*/
//=============================================================================
class SystemEventGetterBase : public EventGetterBase {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�C�x���g�擾
	*/
	//===========================================================================
	bool	IsOn( u32 eventType ) const { return false; }
	
private:
	//-----------------------���\�b�h------------------------

	
	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			SystemEventGetterBase() : EventGetterBase() {}
	virtual~SystemEventGetterBase() {}
};
	
}	// namespace system
}	// namespace nk



#endif  // __SYSTEM_EVENT_GETTER_BASE_H__