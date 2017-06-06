//=============================================================================
/*!	@file	general.h

	@brief	�ėp�C�����C���֐�

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __INLINE_H__
#define __INLINE_H__

//-------------------------------�C���N���[�h-------------------------------
#include <stdlib.h>
#include <stdio.h>
#include "./debug/debugfunction.h"

/*! �r�b�g���V�t�g */
#define BIT_SHIFT_LEFT(a)			(1 << a)
#define BIT_SHIFT_RIGHT(a)			(1 >> a)
#define ARRAY_SIZE(ary)				( sizeof(ary) / sizeof(ary[0]) )

#if		defined(_DEBUG)
	#define	PRINTF(fmt, ...)			_DebugPrintf(fmt, __VA_ARGS__)
	//#define	PRINTF(fmt, ...)			_DebugPrintf(fmt, __VA_ARGS__)
	#define RELEASE_PRINTF(fmt, ...)	{_DebugPrintf(fmt, __VA_ARGS__); printf(fmt, __VA_ARGS__);}
	
	//! ��~
	#define ABORT()														\
	{																	\
		int* a = NULL;													\
		*a = 0;															\
	}
	
	//! �A�T�[�g
	#define	ASSERT(test, fmt, ...)														\
	{																					\
		if( !(test) ) {																	\
			PRINTF("assert : file %s. line %d.\n", __FILE__, __LINE__ );				\
			PRINTF(fmt, __VA_ARGS__);													\
			PRINTF("\n");																\
			ABORT();																	\
		}																				\
	}
	#define INDEX_ASSERT(idx, max, fmt, ...)	ASSERT( (0 <= idx) && (idx < max), fmt, __VA_ARGS__ )

//#elif	defined(_RELEASE)
#else
	#define PRINTF(...)							((void)0)
	#define RELEASE_PRINTF(fmt, ...)			printf(fmt, __VA_ARGS__)
	#define ABORT()								((void)0)
	#define ASSERT(test, fmt, ...)				((void)0)
	#define INDEX_ASSERT(idx, max, fmt, ...)	((void)0)
#endif



//! null�`�F�b�N
#define NULL_ASSERT(test) ASSERT(test,"null")


namespace nk {
	

//===========================================================================
/*!	@brief	�Z�[�t�f���[�g
	@param	obj : �폜����I�u�W�F�N�g
	@return	�Ȃ�
*/
//===========================================================================
template <typename T>
inline void SafeDelete( T*& obj )
{
	if( obj ) {
		delete obj;
	}
	obj = NULL;

}



//===========================================================================
/*!	@brief	�z��ŃZ�[�t�f���[�g
	@param	obj : �폜����I�u�W�F�N�g
	@return	�Ȃ�
*/
//===========================================================================
template <typename T>
inline void SafeDeleteArray( T*& obj )
{
	delete[] obj;
	obj = NULL;

}




//===========================================================================
/*!	@brief	�z��ŃZ�[�t�t���[
	@param	obj : �폜����I�u�W�F�N�g
	@return	�Ȃ�
*/
//===========================================================================
template <typename T>
inline void SafeFree( T*& obj )
{
	if( obj ) {
		free( obj );
	}
	obj = NULL;

}




//===========================================================================
/*!	@brief	�I�u�W�F�N�g�̓���ւ�
	@param	s1,s2	: ����ւ���I�u�W�F�N�g
	@return	�Ȃ�
*/
//===========================================================================
template <typename T>
inline void Swap( T& s1, T& s2 )
{
	T temp = s1;
	s1 = s2;
	s2 = temp;
}


//===========================================================================
/*!	@brief		�ő�K��
	@param		a, b��r����I�u�W�F�N�g
	@return		----
	@note		operator<()����`����Ă���K�v������܂�
*/
//===========================================================================
template <typename T>
inline T Max( const T& a, const T& b )
{
	
	return (b < a) ? a : b;
}


//===========================================================================
/*!	@brief		�ŏ��K��
	@param		a, b��r����I�u�W�F�N�g
	@return		----
	@note		operator<()����`����Ă���K�v������܂�
*/
//===========================================================================
template <typename T>
inline T Min( const T& a, const T& b )
{
	
	return (a < b) ? a : b;
}


//===========================================================================
/*!	@brief		�͈͓��Ɋۂ߂�
	@param		value		���肷��I�u�W�F�N�g
	@param		min			�ŏ�
	@param		max			�ő�
	@return		----
	@note		operator<()����`����Ă���K�v������܂�
*/
//===========================================================================
template <typename T>
inline T Clamp( const T& value, const T& min, const T& max )
{
	
	return (max < value) ? max : ((value < min) ? min : value);
}

}	// nk

#endif  // __INLINE_H__