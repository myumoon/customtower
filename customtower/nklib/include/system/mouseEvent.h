//=============================================================================
/*!	@file	mouseEvent.h

	@brief	�}�E�X�C�x���g

	@author	ryunosuke ide
	@date	2013.06.29
*/
//=============================================================================

#ifndef __MOUSE_EVENT_H__
#define __MOUSE_EVENT_H__


namespace nk {
namespace system {

//! �}�E�X���̓C�x���g
struct MouseEvent {
	enum {
		LEFT,
		RIGHT,
		WHEEL,
		WHEEL_UP,
		WHEEL_DOWN,
		INPUT_OPTION_OFFSET,
	};
	
	s32		x;			//!< ���W
	s32		y;			//!< ���W
	u32		event;		//!< ����

	//! �R���X�g���N�^
	MouseEvent( void ) {
		this->Clear();
	}

	//! �N���A
	void	Clear( void ) {
		this->x		= 0;
		this->y		= 0;
		this->event	= 0;
	}

	//! �Z�b�g
	void	EventOn( u32 bit ) {
		this->event |= (1 << bit);
	}
	void	EventOff( u32 bit ) {
		this->event &= ~(1 << bit);
	}

	//! �C�x���g�擾
	bool	IsOn( u32 bit ) const {
		return ((this->event & (1 << bit)) != 0) ? true : false;
	}
};
	
}	// namespace system	
}	// namespace nk






#endif  // __MOUSE_EVENT_H__