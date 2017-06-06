//=============================================================================
/*!	@file	mouseEvent.h

	@brief	マウスイベント

	@author	ryunosuke ide
	@date	2013.06.29
*/
//=============================================================================

#ifndef __MOUSE_EVENT_H__
#define __MOUSE_EVENT_H__


namespace nk {
namespace system {

//! マウス入力イベント
struct MouseEvent {
	enum {
		LEFT,
		RIGHT,
		WHEEL,
		WHEEL_UP,
		WHEEL_DOWN,
		INPUT_OPTION_OFFSET,
	};
	
	s32		x;			//!< 座標
	s32		y;			//!< 座標
	u32		event;		//!< 入力

	//! コンストラクタ
	MouseEvent( void ) {
		this->Clear();
	}

	//! クリア
	void	Clear( void ) {
		this->x		= 0;
		this->y		= 0;
		this->event	= 0;
	}

	//! セット
	void	EventOn( u32 bit ) {
		this->event |= (1 << bit);
	}
	void	EventOff( u32 bit ) {
		this->event &= ~(1 << bit);
	}

	//! イベント取得
	bool	IsOn( u32 bit ) const {
		return ((this->event & (1 << bit)) != 0) ? true : false;
	}
};
	
}	// namespace system	
}	// namespace nk






#endif  // __MOUSE_EVENT_H__