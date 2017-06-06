//=============================================================================
/*!	@file	selectorUpdater.h

	@brief	セレクタ

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

#ifndef __SELECTOR_UPDATER_H__
#define __SELECTOR_UPDATER_H__


namespace nk {

namespace input {
class Input;
}

//! カーソル更新インターフェース
class CursorUpdater {
public:
	virtual s32 Update( s32 nowSelectNo, input::Input* input, s32 prevButton, s32 nextButton )	= 0;
};


//! リピート
class UpdateRepeat : public CursorUpdater {
private:
	static const s32	STOP_COUNT		= 30;	//!< 一旦停止するカウント
	static const s32	UPDATE_INTERVAL	= 10;	//!< 更新間隔
public:
	UpdateRepeat() {
		m_counter	= 0;
	}
	virtual s32 Update( s32 nowSelectNo, input::Input* input, s32 prevButton, s32 nextButton );
private:
	s32	m_counter;
};

//! 一度きり
class UpdateOnce : public CursorUpdater {
public:
	UpdateOnce() {
		m_counter	= 0;
	}
	virtual s32 Update( s32 nowSelectNo, input::Input* input, s32 prevButton, s32 nextButton );
private:
	s32	m_counter;
};
}	// namespace nk

#endif  // __SELECTOR_UPDATER_H__