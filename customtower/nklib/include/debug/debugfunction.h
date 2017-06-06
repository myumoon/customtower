/*-------------------------------------------------------------------------
	説　明：デバッグ機能
	作成日：2010/09/11
	更新日：2010/09/11
--------------------------------------------------------------------------*/

#ifndef __DEBUGFUNCTION_H__
#define __DEBUGFUNCTION_H__

#include <stdio.h>

//#include <SDL/SDL.h>

#include "../typedef.h"

//class BoundaryVolume;

//extern BoundaryVolume *g_debug_bv;

//extern Uint32	g_debug_average;
//extern Uint32	g_debug_sum;
//extern s32		g_debug_cnt;
//extern Uint32	g_debug_start;
extern u32	g_debug_average;
extern u32	g_debug_sum;
extern s32	g_debug_cnt;
extern u32	g_debug_start;

/*
#define DEBUG_TIME_START {												\
	g_debug_start = SDL_GetTicks();										\
}

#define DEBUG_TIME_ADD {												\
	g_debug_average += SDL_GetTicks() - g_debug_start;					\
	g_debug_sum += SDL_GetTicks() - g_debug_start;						\
}

#define DEBUG_TIME_AVERAGE_DISP {										\
	g_debug_cnt++;														\
	if( g_debug_cnt % 30 == 0 ) {										\
		PRINTF("average = %d\n", g_debug_average / g_debug_cnt);		\
		g_debug_average = g_debug_cnt = 0;								\
	}																	\
}

#define DEBUG_TIME_DISP {												\
	PRINTF("time = %d\n", g_debug_average);								\
	g_debug_average = g_debug_cnt = 0;									\
}

#define DEBUG_TIME_SUM_DISP {											\
	PRINTF("sum = %d\n", g_debug_sum);									\
	g_debug_sum = 0;													\
}
*/

/*
	ビットを表示
	str	:	デバッグ用文字列
	ucp	:	ビットへのアドレス
	len	:	格納変数のサイズ
*/
void	DispBit(char *str, u8 *ucp, size_t len);

//! コンソール表示
void	_DebugPrintf(const char* fmt, ...);

#endif  // __DEBUGFUNCTION_H__