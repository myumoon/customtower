//=============================================================================
/*!	@file	inputBase.h

	@brief	���͊��N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __INPUTBASE_H__
#define __INPUTBASE_H__


//-------------------------------�C���N���[�h-------------------------------
#include <assert.h>

#include "../typedef.h"


namespace nk {
namespace input {

/* ���̓f�o�C�X�̎�� */
typedef u32 INPUT_KIND;



//=============================================================================
/*!
                              ���͊��N���X
*/
//=============================================================================
class Input {
public:
	//-----------------------�^��`--------------------------
	enum ButtonPress {
		NONE		= 0,
		PRESS		= 1<<0,		//!< �����Ă���
		RELEASE		= 1<<1,		//!< �����Ă���
		PRESSED		= 1<<2,		//!< ������
		RELEASED	= 1<<3,		//!< ������

		USER_SHIFT	= 4,		//!< ���[�U�[�g�p
	};
	typedef u32 ButtonState;	// �{�^���̏��


	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	//! ���͎�ނ��Z�b�g
	void			SetKind( INPUT_KIND kind ) { m_kind = kind; }
	
	//! ���͎�ނ��擾
	INPUT_KIND		GetKind() const { return m_kind; }

	//!	�X�V
	virtual void	Update() = 0;

	//! ������Ă��邩�ǂ����̔���
	virtual bool	IsPress( s32 i ) const = 0;

	//! �O��̃t���[���ł͗�����Ă��č��̃t���[���ł͉�����Ă��邩�ǂ����̔���
	virtual bool	IsPressed( s32 i ) const = 0;

	//! �����Ă��邩�ǂ����̔���
	virtual bool	IsRelease( s32 i ) const = 0;

	//! �O�̃t���[���ŉ����Ă��č��̃t���[���ŗ����ꂽ���ǂ����̔���
	virtual bool	IsReleased( s32 i ) const = 0;

private:
	//----------------------�����o�ϐ�-----------------------
	INPUT_KIND				m_kind;					// �f�o�C�X�̎��
	
	
	//-----------------------���\�b�h------------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 Input();
	virtual ~Input();
};



}	// namespace input
}	// namespace nk



#endif  // __INPUTBASE_H__