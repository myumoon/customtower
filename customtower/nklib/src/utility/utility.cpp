//=============================================================================
/*!	@file	utility.h

	@brief	���ʊ֐�

	@author	ryunosuke ide
	@date	2013.02.14
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/utility/utility.h"

#include <time.h>

#if defined(NK_USE_SDL)
#include <SDL/SDL.h>
#elif defined(_WINDOWS)
#include <winsock2.h>
#include <windows.h>
#endif


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

u64	startedApplicationTimeMillSec	= 0;

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {



//===========================================================================
/*!	@brief	�^�C�}�[�̏�����
	@param	----
	@return	----
*/
//===========================================================================
void InitializeTimer( void )
{
#if defined(NK_USE_SDL)
	startedApplicationTimeMillSec	= SDL_GetTicks();
	
#elif defined(_WINDOWS)
	SYSTEMTIME	time_val;
	GetLocalTime( &time_val );
	startedApplicationTimeMillSec	= GetTimeMillSec();
#endif

}


//===========================================================================
/*!	@brief	�N��������̌o�ߎ��Ԃ��~���b�ŏK��
	@param	----
	@return	----
*/
//===========================================================================
u64 GetTimeMillSec( void )
{
#if defined(NK_USE_SDL)
	const u64	nowTime	= SDL_GetTicks();
	
#elif defined(_WINDOWS)
	SYSTEMTIME	time_val;
	//GetLocalTime( &time_val );
	GetSystemTime( &time_val );
	//const u64	year	= time_val.wYear * 1000 * 60 * 60 * 24 * 365;
	const u64	day		= time_val.wDay * 1000 * 60 * 60 * 24;
	const u64	hour	= time_val.wHour * 1000 * 60 * 60;
	const u64	minute	= time_val.wMinute * 1000 * 60;
	const u64	second	= time_val.wSecond * 1000;
	const u64	millsec	= time_val.wMilliseconds;

	const u64	nowTime	= (day + hour + minute + second + millsec) - startedApplicationTimeMillSec;
#endif
	
	return nowTime;
}




//===========================================================================
/*!	@brief	���~���b�X���[�v
	@param	millsec		�X���[�v���s���b��(�~���b)
	@return	----
*/
//===========================================================================
void SleepThread( u64 millsec )
{
#if defined(NK_USE_SDL)
	SDL_Delay( static_cast<Uint32>(millsec) );
	
#elif defined(_WINDOWS)
	Sleep( static_cast<DWORD>(millsec) );
#endif


}


}	// namespace nk