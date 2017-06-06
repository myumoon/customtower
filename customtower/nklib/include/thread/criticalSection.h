//=============================================================================
/*!	@file	mutex.h

	@brief	�N���e�B�J���Z�N�V����

	@author	ryunosuke ide
	@date	2013.05.13
*/
//=============================================================================

#ifndef __CRITICAL_SECTION_H__
#define __CRITICAL_SECTION_H__

#include "./threadFunc.h"

namespace nk {

//=============================================================================
/*!
								�~���[�e�b�N�X
*/
//=============================================================================
class CriticalSection {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		���b�N
	*/
	//===========================================================================
	void				Lock( void );

	//===========================================================================
	/*!	@brief		�A�����b�N
	*/
	//===========================================================================
	void				Unlock( void );

	//===========================================================================
	/*!	@brief		�R�s�[
	*/
	//===========================================================================
	CriticalSection&	operator =( const CriticalSection& rhs );
	
private:
	//-----------------------���\�b�h------------------------
	// ����
	void			_Create( void );

	// �폜
	void			_Delete( void );

	// �R�s�[
	void			_Copy( const CriticalSection& rhs);

	// �I������
	void			_Term( void );

	//----------------------�����o�ϐ�-----------------------
	s32							m_copyCount;	//!< �R�s�[�J�E���^
	CRITICAL_SECTION_HANDLE		m_handle;		//!< �n���h��

	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			CriticalSection();
			CriticalSection( CRITICAL_SECTION_HANDLE handle );
			CriticalSection( const CriticalSection& rhs );
	virtual~CriticalSection();
	
private:
	
};

	
}	// namespace nk






#endif  // __CRITICAL_SECTION_H__