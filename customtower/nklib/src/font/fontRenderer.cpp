//=============================================================================
/*!	@file	�t�H���g�`��

	@brief	�t�H���g�����_��

	@author	ryunosuke ide
	@date	2013.03.24
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/font/fontRenderer.h"
#include "../../include/utility/autoTime.h"
#include <cstdarg>

#if		defined(NK_USE_DIRECTX)

#elif	defined(NK_USE_SDL) && defined(NK_USE_GL)
#include <SDL/SDL_opengl.h>
#include <gl/glut.h>

#elif	defined(NK_USE_GL)
#include <gl/gl.h>

#elif	defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#endif

#include "../../include/resource/texture.h"
#include "../../include/font/font.h"
#include "../../include/graphics/sprite.h"
#include "../../include/utility/autoTime.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace nk {

namespace font {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
FontRenderer::FontRenderer()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
FontRenderer::~FontRenderer()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void FontRenderer::_Init()
{
	m_font			= NULL;
	m_sprite		= new graphics::Sprite();
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void FontRenderer::_Term()
{

}


//===========================================================================
/*!	@brief		�t�H���g�o�^
	@param		font	�o�^�t�H���g
	@return		----
*/
//===========================================================================
void FontRenderer::Register( const Font* font )
{
	
	m_font		= font;
	
}


//===========================================================================
/*!	@brief		�`��
	@param		x, y		�`��ʒu
	@param		fmt			�`�敶��
	@return		----
*/
//===========================================================================
void FontRenderer::Render( s32 screenId, s32 x, s32 y, s32 size, const char* fmt, ... )
{
	const Color	color			= Color( 0.2f, 0.2f, 0.2f, 1.0f );	// �\���F(�D�F)
	char		outBuff[512]	= { 0 };
	
	va_list		argPtr;
	va_start( argPtr, fmt );

	if ( !vsprintf_s( outBuff, sizeof(outBuff), fmt, argPtr ) ) {
	   return;
	}
	Render( screenId, x, y, size, color, fmt, argPtr );

	va_end( argPtr );
}


//===========================================================================
/*!	@brief		�`��
	@param		x, y		�`��ʒu
	@param		color		�F
	@param		fmt			�`�敶��
	@return		----
*/
//===========================================================================
void FontRenderer::Render( s32 screenId, s32 x, s32 y, s32 size, const Color& color, const char* fmt, ... )
{
	char outBuff[512]	= { 0 };
	
	va_list argPtr;
	va_start( argPtr, fmt );
	
	if ( !vsprintf_s( outBuff, sizeof(outBuff), fmt, argPtr ) ) {
	   return;
	}

	
	const resource::Texture*	rendTex		= m_font->GetTexture();
	s32							fontWidth	= 0;
	s32							rendX, rendY;
	f32							scale;
	graphics::Rect2D			fontSize;
	graphics::Rect2D			texUV;

	m_sprite->SetTexture( const_cast<resource::Texture*>(rendTex) );
	m_sprite->SetColor( color );
	m_sprite->SetScreenId( screenId );


	s32	count	= 0;
	for( s32 i = 0; i < ARRAY_SIZE( outBuff ); ++i ) {
		if( outBuff[i] ) {
			fontSize	= m_font->GetCharacterRect( outBuff[i] );
			texUV		= m_font->GetCharacterRectUV( outBuff[i] );
			scale		= static_cast<f32>(size) / fontSize.w;
			rendX		= static_cast<s32>(x + (fontSize.w * scale) * i);
			rendY		= y;

			m_sprite->SetScale( scale );
			m_sprite->SetUVWH( texUV.x, texUV.y, texUV.w, texUV.h );
			m_sprite->Draw( math::Vector( rendX, rendY, 0 ) );

			count++;
		}
		else {
			break;
		}
	}
	
    va_end( argPtr );
}


//===========================================================================
/*!	@brief		�X�N���[��ID
	@param		screenId	ID
	@return		----
*/
//===========================================================================
// void FontRenderer::SetScreenId( s32 screenId )
// {
// 	
// 	m_sprite->SetScreenId( screenId );
// 	
// }
	
}	// namespace font
}	// namespace nk
