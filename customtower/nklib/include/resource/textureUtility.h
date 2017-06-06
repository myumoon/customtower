//=============================================================================
/*!	@file	textureUtility.h

	@brief	�e�N�X�`�����[�e�B���e�B�[

	@author	ryunosuke ide
	@date	2013.03.05
*/
//=============================================================================



#ifndef __TEXTURE_UTILITY_H__
#define __TEXTURE_UTILITY_H__

#include <stdio.h>
#if defined(_WIN32)
#include <winsock2.h>	// �����̒�`���Ē�`�����̂�
#include <windows.h>	// GL�̑O�ɃC���N���[�h���Ă����Ȃ���"APIENTRY���Ē�`�����"
#endif

#if defined(NK_USE_GL)
#include <GL/glpng.h>
#include <GL/GL.h>
#endif
#include "project.h"
#include "../general.h"


struct	SDL_Surface;

namespace nk {

namespace resource {

#if defined(NK_USE_GL)	
struct GlPngSurface {
	pngInfo		info;
	GLuint		texId;
};
#endif


//=============================================================================
/*!
								�摜�T�[�t�F�C�X
*/
//=============================================================================
struct ImageSurface {
	
#if defined(NK_USE_SDL)
	SDL_Surface*	image;		//!< �摜�T�[�t�F�C�X
#else
	GlPngSurface*	image;		//!< �摜�T�[�t�F�C�X
#endif
	
	bool			created;	//!< �����ς݂Ȃ�true

	ImageSurface() {
		this->image		= NULL;
		this->created	= false;
	}

#if defined(NK_USE_SDL)
	void Register( SDL_Surface* image )
#elif defined(NK_USE_GL)
	void Register( GlPngSurface* image )
#else
	#error �֐�����`
#endif
	{
		this->image	= image;
		if( this->image ) {
			this->created	= true;
		}
	}

	//! ���K��
	u32	GetWidth( void ) const;

	//! �����K��
	u32	GetHeight( void ) const;

	
};


	
//=============================================================================
/*!	@brief	�摜�t�@�C���̓Ǎ���
	@param	dst		�o�� : �摜�T�[�t�F�C�X
	@param	path	���� : �摜�p�X
	@return	true.�ǂݍ��ݐ���	false.�ǂݍ��ݎ��s
*/
//=============================================================================
extern bool 	LoadImageSurface( ImageSurface* dst, const char* path );


//=============================================================================
/*!	@brief	�J���T�[�t�F�X�̍쐬
	@param	width	��
	@param	height	����
	@param	depth	�f�v�X
	@return	true.����	false.���s
*/
//=============================================================================
extern bool 	CreateEmptySurface( ImageSurface* dst, u32 width, u32 height, u32 depth );

	
//=============================================================================
/*!	@brief	�摜�t�@�C���̊J��
	@param	�J������摜
*/
//=============================================================================
extern void		ReleaseImageSurface( ImageSurface* img );




}	// namespace resource
	
	
}	// namespace nk








#endif  // __TEXTURE_UTILITY_H__