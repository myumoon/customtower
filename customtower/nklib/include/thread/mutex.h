//=============================================================================
/*!	@file	mutex.h

	@brief	�~���[�e�b�N�X

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "./threadFunc.h"
#include "./mutex.h"

namespace nk {

//=============================================================================
/*!
								�~���[�e�b�N�X
*/
//=============================================================================
class Mutex {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ���b�N
	void			Lock( void );

	//! �A�����b�N
	void			Unlock( void );

	//! �R�s�[
	Mutex&			operator =( const Mutex& mutex );
	
private:
	//-----------------------���\�b�h------------------------
	//! ����
	void			_Create( void );

	//! �폜
	void			_Delete( void );

	//! �R�s�[
	void			_Copy( const Mutex& mutex );

	//! �I������
	void			_Term( void );

	//----------------------�����o�ϐ�-----------------------
	s32				m_copyCount;	//!< �~���[�e�b�N�X�R�s�[�J�E���^
	MUTEX_HANDLE	m_handle;		//!< �~���[�e�b�N�X�n���h��	
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Mutex();
			Mutex( MUTEX_HANDLE handle );
			Mutex( const Mutex& mutex );
	virtual~Mutex();
	
private:
	
};

	
}	// namespace nk






#endif  // __MUTEX_H__