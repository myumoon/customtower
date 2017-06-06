//=============================================================================
/*!	@file	sound.h

	@brief	サウンド

	@author	ryunosuke ide
	@date	2013.02.10
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/sound/soundManager.h"
#include "../../include/project.h"
#include "../../include/general.h"


#if defined(NK_USE_SDL)
#include <SDL/SDL_mixer.h>
#endif

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------




namespace nk {

namespace sound {



//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
bool SoundManager::Initialize( void )
{
#if defined(NK_USE_SDL)
	
	/* オーディオの初期化 */
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		RELEASE_PRINTF("failed in the initialization audio：%s\n", SDL_GetError());
		
		return false;
	}

#endif
	
	return true;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
bool SoundManager::Finalize( void )
{
	
	return true;
}

	
	
}	// namespace sound

	
}	// namespace nk