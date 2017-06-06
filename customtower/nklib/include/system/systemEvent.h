//=============================================================================
/*!	@file	systemEvent.h

	@brief	システムイベント

	@author	ryunosuke ide
	@date	2013.06.29
*/
//=============================================================================


#ifndef __SYSTEM_EVENT_H__
#define __SYSTEM_EVENT_H__



namespace nk {
namespace system {

//! システムイベント
struct SystemEvent {
	enum {
		WINDOW_ACTIVE,
		WINDOW_RESIZE,
		QUIT,
	};

	//! イベント
	u32		event;

	//! コンストラクタ
	SystemEvent( void ) {
		this->Clear();
	}

	//! クリア
	void Clear( void ) {
		this->event	= 0;
	}

	//! 設定
	void EventOn( u8 bit ) {
		this->event |= (1 << bit);
	}

	//! イベント取得
	bool IsOn( u8 bit ) const {
		return ((this->event & (1 << bit)) != 0) ? true : false;
	}
};
	
}	// namespace system
}	// namespace nk





#endif  // __SYSTEM_EVENT_H__