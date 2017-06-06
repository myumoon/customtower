//=============================================================================
/*!	@file	font.h

	@brief	フォント

	@author	ryunosuke ide
	@date	2013.03.23
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/font/font.h"

#if defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

#include "../../include/resource/textureUtility.h"
#include "../../include/resource/texture.h"
#include "../../include/graphics/geometry.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

s32		s_asciiOffset	= 32;	// ' '
	

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {


}	// unnamed

//---------------------------------関数定義---------------------------------

namespace nk {

namespace font {

using namespace resource;

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Font::Font()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Font::~Font()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
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
/*!	@brief	終了処理
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
/*!	@brief		画像登録
	@param		image		フォント画像
	@param		fontWidth	文字幅
	@param		fontHeigjt	文字高さ
	@param		xCharaNum	横方向の文字数
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
/*!	@brief		画像登録
	@param		imgPath		フォント画像
	@param		fontWidth	文字幅
	@param		fontHeigjt	文字高さ
	@param		xCharaNum	横方向の文字数
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
/*!	@brief		文字サーフェス取得
	@param		ascii文字(' '～'~')
	@return		サーフェス(解放は意識しなくて大丈夫です)
*/
//===========================================================================
// resource::ImageSurface	Font::GetCharacter( char asciiCode ) const
// {
// 	
// 	return m_vecImage[ _GetCharacterIndex(asciiCode) ];
// }

//===========================================================================
/*!	@brief		文字サーフェス取得
	@param		ascii文字(' '～'~')
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
/*!	@brief		文字サーフェス取得
	@param		ascii文字(' '～'~')
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
/*!	@brief		テクスチャ取得
	@param		----
	@return		----
*/
//===========================================================================
const resource::Texture* Font::GetTexture( void ) const
{
	
	return m_fontTexture;
}

//===========================================================================
/*!	@brief		フォントテーブル生成
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
/*!	@brief		フォントテーブル削除
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
/*!	@brief		文字インデックスを取得
	@param		c		文字
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