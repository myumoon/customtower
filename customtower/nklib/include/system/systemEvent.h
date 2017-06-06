//=============================================================================
/*!	@file	systemEvent.h

	@brief	�V�X�e���C�x���g

	@author	ryunosuke ide
	@date	2013.06.29
*/
//=============================================================================


#ifndef __SYSTEM_EVENT_H__
#define __SYSTEM_EVENT_H__



namespace nk {
namespace system {

//! �V�X�e���C�x���g
struct SystemEvent {
	enum {
		WINDOW_ACTIVE,
		WINDOW_RESIZE,
		QUIT,
	};

	//! �C�x���g
	u32		event;

	//! �R���X�g���N�^
	SystemEvent( void ) {
		this->Clear();
	}

	//! �N���A
	void Clear( void ) {
		this->event	= 0;
	}

	//! �ݒ�
	void EventOn( u8 bit ) {
		this->event |= (1 << bit);
	}

	//! �C�x���g�擾
	bool IsOn( u8 bit ) const {
		return ((this->event & (1 << bit)) != 0) ? true : false;
	}
};
	
}	// namespace system
}	// namespace nk





#endif  // __SYSTEM_EVENT_H__