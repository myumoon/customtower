//=============================================================================
/*!	@file	font.h

	@brief	�t�H���g

	@author	ryunosuke ide
	@date	2013.03.23
*/
//=============================================================================

#ifndef __FONT_H__
#define __FONT_H__


#include <stdio.h>
#include <vector>
#include "typedef.h"
#include "../resource/textureUtility.h"
#include "../graphics/geometry.h"


namespace nk {

namespace resource {
class Texture;
}

namespace font {

//=============================================================================
/*!
								�t�H���g
*/
//=============================================================================
class Font {
private:
	typedef std::vector<resource::ImageSurface>	VecSurface;
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�摜�o�^
		@note		�z�u�͍��l�߁E�����łȂ���΂Ȃ�Ȃ�
	*/
	//===========================================================================
	//void			RegisterImage( resource::ImageSurface image, u32 fontWidth, u32 fontHeight, u32 xCharNum );
	bool			RegisterImage( const char* imgPath, u32 fontWidth, u32 fontHeight, u32 xCharNum );

	//===========================================================================
	/*!	@brief		�t�H���g�摜�K��
	*/
	//===========================================================================
	//resource::ImageSurface	GetCharacter( char asciiCode ) const;

	//===========================================================================
	/*!	@brief		�N���b�v���擾
	*/
	//===========================================================================
	graphics::Rect2D		GetCharacterRect( char asciiCode ) const;
	graphics::Rect2D		GetCharacterRectUV( char asciiCode ) const;

	//===========================================================================
	/*!	@brief		�t�H���g�e�N�X�`��
	*/
	//===========================================================================
	const resource::Texture*	GetTexture( void ) const;
	
protected:
	//===========================================================================
	/*!	@brief		�摜�}�b�v����
		@note		m_fontImage���Z�b�g����Ă��Ȃ���΂Ȃ�Ȃ�
	*/
	//===========================================================================
	bool	_CreateFontTable( void );


	//===========================================================================
	/*!	@brief		�t�H���g�e�[�u���폜
	*/
	//===========================================================================
	void	_DestroyFontTable( void );

	//===========================================================================
	/*!	@brief		�����C���f�b�N�X���擾
	*/
	//===========================================================================
	s32		_GetCharacterIndex( char c ) const;
	
private:
	//----------------------�����o�ϐ�-----------------------
	//resource::ImageSurface	m_fontImage;		//!< �t�H���g�摜(�����łȂ���΂Ȃ�Ȃ�)	
	resource::Texture*		m_fontTexture;		//!< �e�N�X�`��
	s32						m_fontWidth;		//!< �t�H���g��
	s32						m_fontHeight;		//!< �t�H���g����
	s32						m_xCharNum;			//!< �������̕�����
	bool					m_initialized;		//!< �������ς݂Ȃ�true

	//VecSurface				m_vecImage;			//!< �t�H���g�摜
	
	
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Font();
	virtual~Font();
};


}	// namespace font

}	// namespace nk

#endif  // __FONT_H__
