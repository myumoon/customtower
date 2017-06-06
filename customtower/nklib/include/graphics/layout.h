//=============================================================================
/*!	@file	layout.h

	@brief	���C�A�E�g

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "layoutEventListener.h"
#include "layoutParts.h"
#include "layoutPartsBox.h"
#include "spriteAnimation.h"
#include "button.h"



namespace nk {

namespace input {
class Mouse;
class Keyboard;
}

namespace graphics {

//=============================================================================
/*!
								���C�A�E�g
*/
//=============================================================================
class Layout {
public:
	//-----------------------�^��`--------------------------

	//! �p�[�c���
	struct PartsInfo {
		LayoutParts*	parts;		//!< �p�[�c
		s32				depth;		//!< �[��

		//! �R���X�g���N�^
		PartsInfo() {
			this->parts	= NULL;
			this->depth	= 0;
		}

		//! ��r
		bool operator ==( const PartsInfo& rhs ) const {
			return this->parts == rhs.parts;
		}

		//! ��r
		bool operator ==( const LayoutParts* rhs ) const {
			return this->parts == rhs;
		}

		bool operator <( const PartsInfo& rhs ) const {
			return this->depth < rhs.depth;
		}
	};

	//! �p�[�c
	typedef std::vector<PartsInfo>	VecParts;

	//----------------------�ÓI�����o-----------------------
	static const	s32		KEYBOARD_MOVE_AMOUNT		= 5;		//!< �L�[�{�[�h�ł̈ړ���
	static const	s32		CTRL_KEYBOARD_MOVE_AMOUNT	= 1;		//!< ctrl+�L�[�{�[�h�ł̈ړ���
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	void			Initialize( const input::Mouse* mouse, const input::Keyboard* keyboard );

	//===========================================================================
	/*!	@brief		�Z�b�g�A�b�v
	*/
	//===========================================================================
	bool			Setup( const char* layoutFilePath, LayoutEventListener* listener = NULL );

	//===========================================================================
	/*!	@brief		�Z�[�u
	*/
	//===========================================================================
	bool			SaveToFile( const char* outputPath );

	//===========================================================================
	/*!	@brief		���[�g�擾
	*/
	//===========================================================================
	LayoutPartsBox*	GetRoot( void );

	//===========================================================================
	/*!	@brief		�p�[�c�̍폜
		@note		delete���܂�
	*/
	//===========================================================================
	void			DeleteParts( void );

	//===========================================================================
	/*!	@brief		�p�[�c�̍X�V
	*/
	//===========================================================================
	void			UpdateParts( void );

	//===========================================================================
	/*!	@brief		�p�[�c�̕`��
	*/
	//===========================================================================
	void			DrawParts( void );

	//===========================================================================
	/*!	@brief		�p�[�c�̌���
		@attention	�����p�[�c���������ꍇ�͐e�̃p�[�c���D�悳��܂��B
	*/
	//===========================================================================
	LayoutParts*	FindParts( const char* partsname );

	//===========================================================================
	/*!	@brief		�{�b�N�X�p�[�c�̌���
	*/
	//===========================================================================
	LayoutPartsBox*	FindPartsBox( const char* partsboxname );


	//===========================================================================
	/*!	@brief		���C�A�E�g�ύX�X�V
	*/
	//===========================================================================
	virtual void	UpdateLayoutChange( void );


	//===========================================================================
	/*!	@brief		�A�N�e�B�u�p�[�c�̘g��`��
	*/
	//===========================================================================
	void			DrawActivePartsFrame( void );

	//===========================================================================
	/*!	@brief		�ύX���������ꍇtruye��Ԃ�
	*/
	//===========================================================================
	bool			Changed( void ) const	{ return false; }
	
private:

	//! �C�x���g�擾
	//! Layout�ɂ͒��g�����J
	class EventObserver : public ButtonEventListener {
	private:
		friend class Layout;

		virtual void	OnCursorOver( nk::graphics::Button* eventButton );
		virtual void	OnCursorOut( nk::graphics::Button* eventButton );
		virtual void	OnCursorDownStart( nk::graphics::Button* eventButton );
		virtual void	OnCursorDownEnd( nk::graphics::Button* eventButton );
		virtual void	OnCursorUpStart( nk::graphics::Button* eventButton );
		virtual void	OnCursorUpEnd( nk::graphics::Button* eventButton );
		virtual void	OnHold( nk::graphics::Button* eventButton );

		LayoutEventListener*	m_eventListener;
	};
	
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//===========================================================================
	/*!	@brief		�A�N�e�B�u�p�[�c�ǉ�
	*/
	//===========================================================================
	void			_AddActiveParts( LayoutParts* parts, s32 depth );

	//===========================================================================
	/*!	@brief		�A�N�e�B�u�p�[�c���O
	*/
	//===========================================================================
	void			_RemoveActiveParts( LayoutParts* parts );

	//===========================================================================
	/*!	@brief		�A�N�e�B�u�p�[�c���Z�b�g
	*/
	//===========================================================================
	void			_ClearActiveParts( void );

	//----------------------�����o�ϐ�-----------------------
	LayoutPartsBox			m_root;				//!< ���[�g
	const input::Mouse*		m_mouse;			//!< �}�E�X
	const input::Keyboard*	m_keyboard;			//!< �L�[�{�[�h
	EventObserver			m_eventObserver;	//!< �C�x���g�ʒm

	math::Vector			m_prevMousePos;		//!< �O��}�E�X���W
	VecParts				m_activeParts;		//!< �I�𒆃p�[�c
	bool					m_moveable;			//!< �ړ��\
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Layout();
			Layout( const nk::input::Mouse* mouse );
	virtual~Layout();
};
	
}	// namespace graphics	
}	// namespace nk



#endif  // __LAYOUT_H__
