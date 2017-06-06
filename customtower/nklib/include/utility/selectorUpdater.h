//=============================================================================
/*!	@file	selectorUpdater.h

	@brief	�Z���N�^

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

//! �J�[�\���X�V�C���^�[�t�F�[�X
class CursorUpdater {
public:
	virtual s32 Update( s32 nowSelectNo, input::Input* input, s32 prevButton, s32 nextButton )	= 0;
};


//! ���s�[�g
class UpdateRepeat : public CursorUpdater {
private:
	static const s32	STOP_COUNT		= 30;	//!< ��U��~����J�E���g
	static const s32	UPDATE_INTERVAL	= 10;	//!< �X�V�Ԋu
public:
	UpdateRepeat() {
		m_counter	= 0;
	}
	virtual s32 Update( s32 nowSelectNo, input::Input* input, s32 prevButton, s32 nextButton );
private:
	s32	m_counter;
};

//! ��x����
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