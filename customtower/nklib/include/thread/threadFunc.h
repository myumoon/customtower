//=============================================================================
/*!	@file	threadFunc.h


	@brief	�X���b�h

	@author	ryunosuke ide
	@date	2012.09.08
*/
//=============================================================================

#ifndef __THREAD_FUNC_H__
#define __THREAD_FUNC_H__

#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <vector>
#include "../typedef.h"


#define	HANDLE_LIST_MAX		(128)		//!< �n���h���쐬�ő吔
#define	THREAD_MAX			(32)		//!< �X���b�h��

namespace nk {

typedef u32 (*THREAD_FUNC)( void* );

#if defined(_WIN32)	// windows
//! �X���b�h�֐�

//! �X���b�h�n���h��
typedef HANDLE				THREAD_HANDLE;

//! �~���[�e�b�N�X�n���h��
typedef HANDLE				MUTEX_HANDLE;

//! 
typedef LPCRITICAL_SECTION	CRITICAL_SECTION_HANDLE;

//! �C�x���g�n���h��
//typedef HANDLE			EVENT_HANDLE;

//! �X���b�hID
typedef DWORD				THREAD_ID;

#else	// SDL

//! �X���b�h�n���h��
typedef u32					THREAD_HANDLE;

//! �~���[�e�b�N�X�n���h��
typedef u32					MUTEX_HANDLE;

//! �N���e�B�J���Z�N�V�����n���h��
typedef void*				CRITICAL_SECTION_HANDLE;	// �R���p�C���G���[�ł�͂�

//! �X���b�hID
typedef u32					THREAD_ID;
	
#endif

enum THREAD_STATE {
	THREAD_STATE_START,		//!< �J�n
	THREAD_STATE_SUSPEND,	//!< ���f
	THREAD_STATE_WAIT,		//!< �҂�
};





//===========================================================================
/*!	@brief	�X���b�h������
	@param	----
	@return	----
*/
//===========================================================================
void			InitializeThread( void );


	
//===========================================================================
/*!	@brief	�X���b�h�I������
	@param	----
	@return	----
*/
//===========================================================================
void			FinalizeThread( void );
	

//===========================================================================
/*!	@brief	�X���b�h����
	@param	func		�Ăяo���֐�
	@param	arg			�X���b�h�֐�����
	@param	priority	�D��x
	@param	stackSize	�X�^�b�N�T�C�Y(�f�t�H���g��0)
	@return	���������X���b�h�̃n���h��
*/
//===========================================================================
THREAD_HANDLE	CreateThread( THREAD_FUNC func, void* arg, s32 priority = THREAD_PRIORITY_NORMAL, u32 stackSize = 0, const char* name = "" );
	

//===========================================================================
/*!	@brief	�X���b�h�폜
	@param	handle		�폜����X���b�h�̃n���h��
	@return	----
*/
//===========================================================================
void			DestroyThread( THREAD_HANDLE handle );


	
//===========================================================================
/*!	@brief	�X���b�h�J�n
	@param	�J�n����X���b�h�n���h��
	@return	----
*/
//===========================================================================
void			StartThread( THREAD_HANDLE handle );



//===========================================================================
/*!	@brief	�X���b�h���f
	@param	���f����X���b�h�n���h��
	@return	----
*/
//===========================================================================
void			SuspendThread( THREAD_HANDLE handle );


//===========================================================================
/*!	@brief	�X���b�h�ĊJ
	@param	�ĊJ����X���b�h�n���h��
	@return	----
*/
//===========================================================================
void			ResumeThread( THREAD_HANDLE handle );

	
//===========================================================================
/*!	@brief	�X���b�h�I���ҋ@
	@param	�҂X���b�h
	@return	----
*/
//===========================================================================
void			JoinThread( THREAD_HANDLE handle );



//===========================================================================
/*!	@brief	�~���[�e�b�N�X�̍쐬
	@param	----
	@return	���������~���[�e�b�N�X�̃n���h��
*/
//===========================================================================
MUTEX_HANDLE	CreateMutexObject( void );



//===========================================================================
/*!	@brief	�~���[�e�b�N�X�̍폜
	@param	handle	�폜����~���[�e�b�N�X�̃n���h��
	@return	----
*/
//===========================================================================
void			DeleteMutexObject( MUTEX_HANDLE handle );


//===========================================================================
/*!	@brief	�~���[�e�b�N�X�����b�N
	@param	handle	���b�N�����݂�~���[�e�b�N�X
	@return	true.���b�N����		false.���s
*/
//===========================================================================
bool			LockMutex( MUTEX_HANDLE handle );


//===========================================================================
/*!	@brief	�~���[�e�b�N�X���A�����b�N
	@param	handle	�A�����b�N�����݂�~���[�e�b�N�X
	@return	true.�A�����b�N����		false.���s
*/
//===========================================================================
bool			UnlockMutex( MUTEX_HANDLE handle );


//===========================================================================
/*!	@brief		�N���e�B�J���Z�N�V�����̍쐬
	@param		----
	@return		----
*/
//===========================================================================
CRITICAL_SECTION_HANDLE	CreateCriticalSection( void );


//===========================================================================
/*!	@brief		�N���e�B�J���Z�N�V�����̍폜
	@param		handle	�폜����N���e�B�J���Z�N�V�����n���h��
	@return		----
*/
//===========================================================================
void			DeleteCriticalSection( CRITICAL_SECTION_HANDLE handle );


//===========================================================================
/*!	@brief		�N���e�B�J���Z�N�V�����̃��b�N
	@param		�N���e�B�J���Z�N�V�����n���h��
	@return		----
*/
//===========================================================================
void			LockCriticalSection( CRITICAL_SECTION_HANDLE handle );


//===========================================================================
/*!	@brief		�N���e�B�J���Z�N�V�����̃A�����b�N
	@param		�N���e�B�J���Z�N�V�����n���h��
	@return		----
*/
//===========================================================================
void			UnlockCriticalSection( CRITICAL_SECTION_HANDLE handle );

//===========================================================================
/*!	@brief	�S�ẴX���b�h���~������
	@param	----
	@return	----
*/
//===========================================================================
void			SuspendAllThread( void );



//===========================================================================
/*!	@brief	�S�ẴX���b�h���ȑO�̏�Ԃɖ߂�
	@param	----
	@return	----
*/
//===========================================================================
void			ReturnAllThread( void );


//===========================================================================
/*!	@brief	�S�ẴX���b�h���ĊJ������
	@param	----
	@return	----
*/
//===========================================================================
void			ResumeAllThread( void );

#if 0
//===========================================================================
/*!	@brief	�C�x���g�I�u�W�F�N�g�̍쐬
	@param	manualReset		�蓮���Z�b�gon,off
	@param	initialState	�������
	@param	addEventList	�ǉ�����C�x���g���X�g��ID(�f�t�H���g��0)
	@return	���������C�x���g�I�u�W�F�N�g�̃n���h��
*/
//===========================================================================
EVENT_HANDLE	CreateEventObject( bool manualReset, bool initialState, HANDLE_CHUNK_ID addEventList = 0 );



//===========================================================================
/*!	@brief	�C�x���g�I�u�W�F�N�g�̍폜
	@param	handle	�폜����C�x���g�I�u�W�F�N�g�̃n���h��
	@return	----
*/
//===========================================================================
void			DeleteEventObject( EVENT_HANDLE handle );




//===========================================================================
/*!	@brief	�S�ẴC�x���g���V�O�i����ԂɂȂ�܂ő҂�
	@param	----
	@return	----
*/
//===========================================================================
bool			WaitEvent( HANDLE_CHUNK_ID id = 0 );
#endif
	

}	// namespace nk


#endif  // __THREAD_FUNC_H__