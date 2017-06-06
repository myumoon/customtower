//=============================================================================
/*!	@file	general.h

	@brief	汎用インライン関数

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __INLINE_H__
#define __INLINE_H__

//-------------------------------インクルード-------------------------------
#include <stdlib.h>
#include <stdio.h>
#include "./debug/debugfunction.h"

/*! ビット左シフト */
#define BIT_SHIFT_LEFT(a)			(1 << a)
#define BIT_SHIFT_RIGHT(a)			(1 >> a)
#define ARRAY_SIZE(ary)				( sizeof(ary) / sizeof(ary[0]) )

#if		defined(_DEBUG)
	#define	PRINTF(fmt, ...)			_DebugPrintf(fmt, __VA_ARGS__)
	//#define	PRINTF(fmt, ...)			_DebugPrintf(fmt, __VA_ARGS__)
	#define RELEASE_PRINTF(fmt, ...)	{_DebugPrintf(fmt, __VA_ARGS__); printf(fmt, __VA_ARGS__);}
	
	//! 停止
	#define ABORT()														\
	{																	\
		int* a = NULL;													\
		*a = 0;															\
	}
	
	//! アサート
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



//! nullチェック
#define NULL_ASSERT(test) ASSERT(test,"null")


namespace nk {
	

//===========================================================================
/*!	@brief	セーフデリート
	@param	obj : 削除するオブジェクト
	@return	なし
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
/*!	@brief	配列版セーフデリート
	@param	obj : 削除するオブジェクト
	@return	なし
*/
//===========================================================================
template <typename T>
inline void SafeDeleteArray( T*& obj )
{
	delete[] obj;
	obj = NULL;

}




//===========================================================================
/*!	@brief	配列版セーフフリー
	@param	obj : 削除するオブジェクト
	@return	なし
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
/*!	@brief	オブジェクトの入れ替え
	@param	s1,s2	: 入れ替えるオブジェクト
	@return	なし
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
/*!	@brief		最大習得
	@param		a, b比較するオブジェクト
	@return		----
	@note		operator<()が定義されている必要があります
*/
//===========================================================================
template <typename T>
inline T Max( const T& a, const T& b )
{
	
	return (b < a) ? a : b;
}


//===========================================================================
/*!	@brief		最小習得
	@param		a, b比較するオブジェクト
	@return		----
	@note		operator<()が定義されている必要があります
*/
//===========================================================================
template <typename T>
inline T Min( const T& a, const T& b )
{
	
	return (a < b) ? a : b;
}


//===========================================================================
/*!	@brief		範囲内に丸める
	@param		value		判定するオブジェクト
	@param		min			最小
	@param		max			最大
	@return		----
	@note		operator<()が定義されている必要があります
*/
//===========================================================================
template <typename T>
inline T Clamp( const T& value, const T& min, const T& max )
{
	
	return (max < value) ? max : ((value < min) ? min : value);
}

}	// nk

#endif  // __INLINE_H__