//=============================================================================
/*!	@file	font.h

	@brief	�t�H���g

	@author	ryunosuke ide
	@date	2013.03.23
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/font/font.h"

#if defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

#include "../../include/resource/textureUtility.h"
#include "../../include/resource/texture.h"
#include "../../include/graphics/geometry.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

s32		s_asciiOffset	= 32;	// ' '
	

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {


}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace nk {

namespace font {

using namespace resource;

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
Font::Font()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Font::~Font()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Font::_Init()
{
	m_fontTexture	= NULL;
	m_fontWidth		= -1;
	m_fontHeight	= -1;
	m_initialized	= false;

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Font::_Term()
{
	SafeDelete( m_fontTexture );
	
	//_DestroyFontTable();
}


//===========================================================================
/*!	@brief		�摜�o�^
	@param		image		�t�H���g�摜
	@param		fontWidth	������
	@param		fontHeigjt	��������
	@param		xCharaNum	�������̕�����
	@return		----
*/
//===========================================================================
// void Font::RegisterImage( ImageSurface image, u32 fontWidth, u32 fontHeight, u32 xCharNum )
// {
// 	m_fontImage		= image;
// 	m_fontWidth		= fontWidth;
// 	m_fontHeight	= fontHeight;
// 	m_xCharNum		= xCharNum;
// 
// 	m_fontTexture->Register( image );;
// 
// 	m_initialized	= true;
// 	//m_initialized	= _CreateFontTable();
// 
// }


//===========================================================================
/*!	@brief		�摜�o�^
	@param		imgPath		�t�H���g�摜
	@param		fontWidth	������
	@param		fontHeigjt	��������
	@param		xCharaNum	�������̕�����
	@return		----
*/
//===========================================================================
bool Font::RegisterImage( const char* imgPath, u32 fontWidth, u32 fontHeight, u32 xCharNum )
{
	
	m_fontTexture	= resource::CreateTexture( imgPath );
	m_fontWidth		= fontWidth;
	m_fontHeight	= fontHeight;
	m_xCharNum		= xCharNum;

	return m_fontTexture != NULL;
}

//===========================================================================
/*!	@brief		�����T�[�t�F�X�擾
	@param		ascii����(' '�`'~')
	@return		�T�[�t�F�X(����͈ӎ����Ȃ��đ��v�ł�)
*/
//===========================================================================
// resource::ImageSurface	Font::GetCharacter( char asciiCode ) const
// {
// 	
// 	return m_vecImage[ _GetCharacterIndex(asciiCode) ];
// }

//===========================================================================
/*!	@brief		�����T�[�t�F�X�擾
	@param		ascii����(' '�`'~')
*/
//===========================================================================
graphics::Rect2D Font::GetCharacterRect( char asciiCode ) const
{
	const	s32	imgIndex	= _GetCharacterIndex( asciiCode );
	graphics::Rect2D	rect;
	
	rect.x	= static_cast<f32>((imgIndex % m_xCharNum) * m_fontWidth);
	rect.y	= static_cast<f32>((imgIndex / m_xCharNum) * m_fontHeight);
	rect.w	= static_cast<f32>(m_fontWidth);
	rect.h	= static_cast<f32>(m_fontHeight);

	return rect;
}


//===========================================================================
/*!	@brief		�����T�[�t�F�X�擾
	@param		ascii����(' '�`'~')
*/
//===========================================================================
graphics::Rect2D Font::GetCharacterRectUV( char asciiCode ) const
{
	graphics::Rect2D	rect	= GetCharacterRect( asciiCode );

	rect.x	= rect.x / m_fontTexture->GetWidth();
	rect.y	= rect.y / m_fontTexture->GetHeight();
	rect.w	= rect.w / m_fontTexture->GetWidth();
	rect.h	= rect.h / m_fontTexture->GetHeight();

	return rect;
}


//===========================================================================
/*!	@brief		�e�N�X�`���擾
	@param		----
	@return		----
*/
//===========================================================================
const resource::Texture* Font::GetTexture( void ) const
{
	
	return m_fontTexture;
}

//===========================================================================
/*!	@brief		�t�H���g�e�[�u������
	@param		----
	@return		----
*/
//===========================================================================
// bool Font::_CreateFontTable( void )
// {
// 	if( m_fontImage.created == false ) {
// 		return false;
// 	}
// 
// 	_DestroyFontTable();
// 	
// 	m_vecImage.resize( 128 );
// 	
// #if defined(NK_USE_SDL)
// 	for( s32 c = 0; c < s_asciiOffset; ++c ) {
// 		const s32	xNum	= c % m_xCharNum;
// 		const s32	yNum	= c / m_xCharNum;
// 		SDL_Rect	src	= { xNum * m_fontWidth, yNum * m_fontHeight, m_fontWidth, m_fontHeight };
// 		SDL_Rect	dst	= { m_fontWidth, m_fontHeight, m_fontWidth, m_fontHeight };
// 		ImageSurface	surface;
// 		CreateEmptySurface( &m_vecImage[c], m_fontWidth, m_fontHeight, 32 );
// 		SDL_BlitSurface( m_fontImage.image, &src, m_vecImage[c].image, &dst );
// 
// 		m_vecImage[c].created	= true;
// 	}
// #else
// #endif
// 
// 	return true;
// }



//===========================================================================
/*!	@brief		�t�H���g�e�[�u���폜
	@param		----
	@return		----
*/
//===========================================================================
// void Font::_DestroyFontTable( void )
// {
// 	std::vector<ImageSurface>::iterator	itr	= m_vecImage.begin();
// 
// 	for( ; itr != m_vecImage.end(); ++itr ) {
// 		if( (*itr).created ) {
// 			ReleaseImageSurface( &(*itr) );
// 		}
// 	}
// 	
// }


//===========================================================================
/*!	@brief		�����C���f�b�N�X���擾
	@param		c		����
	@return		----
*/
//===========================================================================
s32 Font::_GetCharacterIndex( char c ) const
{
	ASSERT( (' ' <= c) && (c <= '~'), "ascii index error : %d", c );
	if( c < ' ' ) {
		return ' ' - s_asciiOffset;
	}
	if( '~' < c ) {
		return ' ' - s_asciiOffset;
	}

	const s32	retIdx	= c - s_asciiOffset;
	

	
	return c - s_asciiOffset;
}

	
}	// namespace font

}	// namespace nk