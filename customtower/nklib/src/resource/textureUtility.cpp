//=============================================================================
/*!	@file	textureUtility.h

	@brief	�e�N�X�`�����[�e�B���e�B�[

	@author	ryunosuke ide
	@date	2013.03.05
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/resource/textureUtility.h"
#include "../../include/utility/stringfunction.h"
#include "../../include/file/file.h"

#if defined(NK_USE_DIRECTX)
#elif	defined(NK_USE_SDLGL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#elif		defined(NK_USE_GL)
#include <gl/gl.h>
#include <gl/glpng.h>
#elif	defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

#include "../../include/general.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------





namespace nk {

namespace resource {

// ���擾
u32 ImageSurface::GetWidth( void ) const
{
#if defined(NK_USE_SDL)
	NULL_ASSERT( this->image );
	return this->image->w;
#elif defined(NK_USE_GL)
	NULL_ASSERT( this->image );
	return this->image->info.Width;
#endif
}

//! �����K��
u32	ImageSurface::GetHeight( void ) const
{
#if defined(NK_USE_SDL)
	NULL_ASSERT( this->image );
	return this->image->h;
#elif defined(NK_USE_GL)
	NULL_ASSERT( this->image );
	return this->image->info.Height;
#endif
}


//===========================================================================
/*!	@brief	�摜�Ǎ���
	@param	dst		�o�� : �摜
	@param	path	���� : �t�@�C���p�X
	@return	true.�ǂݍ��ݐ���	false.���s
*/
//===========================================================================
bool LoadImageSurface( ImageSurface* dst, const char* path )
{
	if( dst == NULL ) {
		return false;
	}
	
#if defined(NK_USE_SDL)
	{
		SDL_Surface *image;
		SDL_Surface *temp_image;

		PRINTF( "IMG_Load %s\n", path );

		//	�摜�̓ǂݍ���
		//---------------------------------------
		image = IMG_Load( path );

		if( !image ) {
			PRINTF( "�e�N�X�`���摜�Ǎ��ݎ��s : %s\n", path );
			return false;
		}

		// �t�H�[�}�b�g�ϊ��p�ɋ��SDL�C���[�W���
		temp_image= SDL_CreateRGBSurface(
			SDL_SWSURFACE, 
			0, 
			0, 
			32,
			0x000000ff,
			0x0000ff00,
			0x00ff0000,
			0xff000000 );


		// Image��tempImage�̃t�H�[�}�b�g�ɕϊ�����
		image = SDL_ConvertSurface( image, temp_image->format, SDL_SWSURFACE );
		SDL_FreeSurface( temp_image );


		Uint32 alpFlg;
		Uint8  alpGet;

		//�A���t�@�擾
		alpFlg = image->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
		alpGet = image->format->alpha;

		if( (alpFlg & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha( image, 0, 0 );
		}

		
		// �o�^
		dst->image		= image;
		dst->created	= true;
	}
#elif defined(NK_USE_GL)
	{
		// png�ȊO�̓G���[�ɂ��Ă���
		{
			const char*	ext	= GetExtension( path );
			ASSERT( Compare( ext, "png" ), "png only. %s", path );
			if( Compare( ext, "png" ) == false ) {
				return NULL;
			}
		}
		
		pngInfo info;
		GLuint	texId	= pngBind( path, PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST );
		ASSERT( texId != 0, "fileName : %s\n", path );
		if( texId == 0 ) {
			PRINTF( "texture load error : %s\n", path );
			return NULL;
		}

		dst->image			= new GlPngSurface();
		
		dst->image->info	= info;
		dst->image->texId	= texId;
		dst->created		= true;
	}
#endif

	return true;
}


//===========================================================================
/*!	@brief	�摜�Ǎ���
	@param	dst		�o�� : �摜
	@param	width	��
	@param	height	����
	@param	depth	�f�v�X
	@return	true.����	false.���s
*/
//===========================================================================
bool CreateEmptySurface( ImageSurface* dst, u32 width, u32 height, u32 depth )
{
	if( dst == NULL ) {
		return false;
	}
	
#if defined(NK_USE_SDL)
	Uint32 rMask, gMask, bMask, aMask;
	
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rMask = 0xff000000;
    gMask = 0x00ff0000;
    bMask = 0x0000ff00;
    aMask = 0x000000ff;
	
#else
    rMask = 0x000000ff;
    gMask = 0x0000ff00;
    bMask = 0x00ff0000;
    aMask = 0xff000000;
	
#endif	// SDL_BYTEORDER == SDL_BIG_ENDIAN
	
	dst->image	= SDL_CreateRGBSurface(
		SDL_SWSURFACE,
		width,
		height,
		32,
		rMask,
		gMask,
		bMask,
		aMask
	);
	
    if( dst->image == NULL) {
    	dst->created	= false;
    	return false;
    }
	else {
		dst->created	= true;
	}

	
#endif	// defined(NK_USE_SDL)

	return true;
}

//=============================================================================
/*!	@brief	�摜�t�@�C���̊J��
	@param	�J������摜
*/
//=============================================================================
void ReleaseImageSurface( ImageSurface* img )
{
	if( img && img->created ) {
#if defined(NK_USE_SDL)
		SDL_FreeSurface( img->image );
		img->image			= NULL;
		img->created		= false;
#elif defined(NK_USE_GL)
		SafeDelete( img->image );
#endif
	}
	
}
	
}	// namespace resource
	
	
}	// namespace nk
