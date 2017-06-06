//=============================================================================
/*!	@file	selector.h

	@brief	�Z���N�^

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include <stdio.h>
#include "selectorUpdater.h"

namespace nk {

namespace input {
class Input;
}


namespace {
class _Dummy {
public:
	 _Dummy() {}
	~_Dummy() {}
};
}

//=============================================================================
/*!
								�Z���N�^
*/
//=============================================================================
template<typename T = _Dummy>
class Selector {
public:
	//-----------------------�^��`--------------------------

	//! �C�x���g�R�[���o�b�N
	typedef void (T::*SelectEventCallback)( s32 selectNo );
	
	static const s32	NOT_SELECTED	= -2;		//!< ���I��


	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�Z�b�g�A�b�v
	*/
	//===========================================================================
	template<class Updater>
	void Setup(
		s32					max,					// �I���ő�l
		nk::input::Input*	inputChecker,			// ���̓`�F�b�N
		s32					prevButton,				// �O�ɖ߂�{�^��
		s32					nextButton,				// ���ւ̓��̓{�^��	
		s32					decisionButton,			// ����{�^��
		bool				loop			= true,	// �[���[�v
		s32					defaultSelectNo	= 0		// �����l(-1�Ŗ��I��)
	)
	{
		m_nowSelectNo		= defaultSelectNo;
		m_maxSelectNo		= max;
		m_loop				= loop;
		m_inputChecker		= inputChecker;
		m_nextButton		= nextButton;
		m_prevButton		= prevButton;
		m_decisionButton	= decisionButton;
		m_cursorUpdater		= new Updater();
	}

	//===========================================================================
	/*!	@brief		�X�V
		@return		���ݑI�𒆂̔ԍ�
	*/
	//===========================================================================
	bool	Update( void );

	//===========================================================================
	/*!	@brief		���ݑI�𒆂̔ԍ�
	*/
	//===========================================================================
	s32		GetSelectNo( void ) const;

	//===========================================================================
	/*!	@brief		�R�[���o�b�N�ݒ�
	*/
	//===========================================================================
	void	SetCallbackReceiver( T* callbackReceiver );
	void	SetOnSelectCallback( SelectEventCallback callbackFunc );	//!< �I���ɂȂ����Ƃ��R�[���o�b�N
	void	SetOffSelectCallback( SelectEventCallback callbackFunc );	//!< �I�t�ɂȂ����Ƃ��R�[���o�b�N
	void	SetDecideCallback( SelectEventCallback callbackFunc );		//!< ���莞�R�[���o�b�N

	//===========================================================================
	/*!	@brief		�ő�ԍ��ݒ�
	*/
	//===========================================================================
	void	SetMaxSelectNo( s32 maxSelectNo );

	//===========================================================================
	/*!	@brief		���ݔԍ��ݒ�
	*/
	//===========================================================================
	void	SetNowSelectNo( s32 nowSelectNo );

private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	s32					m_nowSelectNo;			//!< ����
	s32					m_maxSelectNo;			//!< �ő�
	bool				m_loop;					//!< ���[�v
	input::Input*		m_inputChecker;			//!< ���̓`�F�b�N
	s32					m_prevButton;			//!< �O�ɖ߂�{�^���ԍ�
	s32					m_nextButton;			//!< ���ɐi�ރ{�^���ԍ�	
	s32					m_decisionButton;		//!< ����{�^��
	CursorUpdater*		m_cursorUpdater;		//!< �J�[�\���X�V

	//! �C�x���g�R�[���o�b�N
	SelectEventCallback	m_callbackOnSelect;		//!< �I����
	SelectEventCallback	m_callbackOffSelect;	//!< �I�t��
	SelectEventCallback	m_callbackDecideSelect;	//!< ���莞
	T*					m_callbackReceiver;		//!< �R�[���o�b�N�擾

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Selector( T* callbackReceiver );
			Selector();
	virtual~Selector();
};


#include "../../src/utility/selector.cpp"

}	// namespace nk




#endif  // __SELECTOR_H__