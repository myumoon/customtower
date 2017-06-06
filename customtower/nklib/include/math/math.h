//=============================================================================
/*!	@file	math.h

	@brief	数学関係の定数.関数をまとめたファイル

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
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
//	@brief	符号を返す
//	@param	a		: 調べる数字
//	@retval	true	: 正（0含む）
//			false	: 負
//	 memo ：
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
//	内　容：ラジアン値を計算
//	引　数：deg	: 角度
//	戻り値：ラジアン
//	 memo ：
//========================================================================
template <typename T>
inline f32 Rad( T deg )
{

	return static_cast<f32>(deg / 180.0f * PI);
}




//========================================================================
//	内　容：ラジアンから角度を計算
//	引　数：rad	: ラジアン角度
//	戻り値：度
//	 memo ：
//========================================================================
template <typename T>
inline f32 Deg( T rad )
{

	return static_cast<f32>(rad) * 180.0f / PI;
}


//===========================================================================
/*!	@brief	範囲内に収める
	@param	num		: 判定する値
	@param	min		: 最小値
	@param	max		: 最大値
	@return	範囲内にまるめた値
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
/*!	@brief		大きい方を取得
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
/*!	@brief		小さい方を取得
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
/*!	@brief		絶対値を取得
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