/*-------------------------------------------------------------------------
	説　明：デバッグ機能
	作成日：2010/09/11
	更新日：2010/09/11
--------------------------------------------------------------------------*/
#include <stdarg.h>
#include <winsock2.h>
#include <windows.h>
#include "../../include/debug/debugfunction.h"
#include "general.h"

//BoundaryVolume *g_debug_bv = NULL;
// Uint32	g_debug_sum = 0;
// Uint32	g_debug_average = 0;
// s32		g_debug_cnt = 0;
// Uint32	g_debug_start = 0;

u32	g_debug_sum = 0;
u32	g_debug_average = 0;
s32	g_debug_cnt = 0;
u32	g_debug_start = 0;



void DispBit(char *str, u8 *ucp, size_t len)
{
	u8 work, i; 

	PRINTF("DispBit:%s [", str); 
	//printf("DispBit:%s [", str); 

	for(i = 0; i < (len * 8); i++) { 
		work = 0x80 >> (i % 8); 
		PRINTF("%c", ((ucp[i / 8] & work) ? '1' : '0')); 
		//printf("%c", ((ucp[i / 8] & work) ? '1' : '0')); 
		if(!(i / 4)) { 
			PRINTF(" ");
			//printf(" "); 
		} 
	} 
	PRINTF("]\n"); 
	//printf("]\n"); 
} 


void _DebugPrintf(const char* fmt, ...)
{
#ifndef _DEBUG
    va_list argPtr;

    va_start(argPtr, fmt);
    vprintf(fmt, argPtr);
    va_end(argPtr);
#else
	char debugOutBuff[512]	= { 0 };
	
	va_list argPtr;
	va_start( argPtr, fmt );
	
	if ( !vsprintf_s( debugOutBuff, sizeof(debugOutBuff), fmt, argPtr ) ) {
	   OutputDebugStringA( "dprintf error." );
	   return;
	}

	OutputDebugStringA( debugOutBuff );

    va_end( argPtr );

#endif
}