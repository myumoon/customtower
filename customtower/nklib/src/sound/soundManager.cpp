//=============================================================================
/*!	@file	sound.h

	@brief	�T�E���h

	@author	ryunosuke ide
	@date	2013.02.10
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/sound/soundManager.h"
#include "../../include/project.h"
#include "../../include/general.h"


#if defined(NK_USE_SDL)
#include <SDL/SDL_mixer.h>
#endif

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------




namespace nk {

namespace sound {



//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
bool SoundManager::Initialize( void )
{
#if defined(NK_USE_SDL)
	
	/* �I�[�f�B�I�̏����� */
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		RELEASE_PRINTF("failed in the initialization audio�F%s\n", SDL_GetError());
		
		return false;
	}

#endif
	
	return true;
}


//===========================================================================
/*!	@brief	�I������
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