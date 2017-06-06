//=============================================================================
/*!	@file	math.h

	@brief	���w�֌W�̒萔.�֐����܂Ƃ߂��t�@�C��

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __MATH_H__
#define __MATH_H__

#include <math.h>
#include "../typedef.h"

namespace nk {
namespace math {

static const f64	PI			= 3.1415926535897932384626433832795;
static const f64	QUARTER_PI	= PI * 0.25;
static const f64	HALF_PI		= PI * 0.5;
static const f64	DOUBLE_PI	= PI * 2.0;
static const f64	RADIAN		= PI / 180.0;
static const f64	ROOT2		= 1.41421356;

//========================================================================
//	@brief	������Ԃ�
//	@param	a		: ���ׂ鐔��
//	@retval	true	: ���i0�܂ށj
//			false	: ��
//	 memo �F
//========================================================================
template <typename T>
bool Sign( T a )
{
	if( 0 < a ) {
		return true;
	}

	return false;
}

//========================================================================
//	���@�e�F���W�A���l���v�Z
//	���@���Fdeg	: �p�x
//	�߂�l�F���W�A��
//	 memo �F
//========================================================================
template <typename T>
inline f32 Rad( T deg )
{

	return static_cast<f32>(deg / 180.0f * PI);
}




//========================================================================
//	���@�e�F���W�A������p�x���v�Z
//	���@���Frad	: ���W�A���p�x
//	�߂�l�F�x
//	 memo �F
//========================================================================
template <typename T>
inline f32 Deg( T rad )
{

	return static_cast<f32>(rad) * 180.0f / PI;
}


//===========================================================================
/*!	@brief	�͈͓��Ɏ��߂�
	@param	num		: ���肷��l
	@param	min		: �ŏ��l
	@param	max		: �ő�l
	@return	�͈͓��ɂ܂�߂��l
*/
//===========================================================================
template <typename T>
inline T Clamp( const T& num, const T& min, const T& max )
{
	if( num < min ) {
		return min;
	}
	if( max < num ) {
		return max;
	}

	return num;
}


//===========================================================================
/*!	@brief		�傫�������擾
	@param		rhs
	@param		lhs
	@return		----
*/
//===========================================================================
template <typename T>
inline T Max( const T& lhs, const T& rhs )
{
	if( lhs < rhs ) {
		return rhs;
	}
	return lhs;
}


//===========================================================================
/*!	@brief		�����������擾
	@param		rhs
	@param		lhs
	@return		----
*/
//===========================================================================
template <typename T>
inline T Min( const T& lhs, const T& rhs )
{
	if( rhs < lhs ) {
		return rhs;
	}
	return lhs;
}


//===========================================================================
/*!	@brief		��Βl���擾
	@param		rhs
	@param		lhs
	@return		----
*/
//===========================================================================
template <typename T>
inline T Abs( const T& value )
{
	if( value < 0 ) {
		return -value;
	}
	return value;
}

	

}	// namespace math
}	// namespace nk


#endif  // __MATH_H__