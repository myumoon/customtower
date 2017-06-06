//=============================================================================
/*!	@file	utility.h

	@brief	共通関数

	@author	ryunosuke ide
	@date	2013.02.14
*/
//=============================================================================


#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "../typedef.h"
#include "./selector.h"
//#include "./stringfunction.h"
//#include "./csvLoader.h"
//#include "./csvReader.h"

namespace nk {


//! タイマーの初期化
extern void InitializeTimer( void );

//! 起動時からの経過時間をミリ秒で習得
extern u64 GetTimeMillSec( void );

//! 起動時からの経過時間をマイクロ秒で習得
//extern u64 GetTimeMicSec( void );

//! 指定ミリ秒停止
extern void SleepThread( u64 millsec );


	


}	// namespace nk


#endif  // __UTILITY_H__