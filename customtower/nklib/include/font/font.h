//=============================================================================
/*!	@file	font.h

	@brief	フォント

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
								フォント
*/
//=============================================================================
class Font {
private:
	typedef std::vector<resource::ImageSurface>	VecSurface;
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		画像登録
		@note		配置は左詰め・等幅でなければならない
	*/
	//===========================================================================
	//void			RegisterImage( resource::ImageSurface image, u32 fontWidth, u32 fontHeight, u32 xCharNum );
	bool			RegisterImage( const char* imgPath, u32 fontWidth, u32 fontHeight, u32 xCharNum );

	//===========================================================================
	/*!	@brief		フォント画像習得
	*/
	//===========================================================================
	//resource::ImageSurface	GetCharacter( char asciiCode ) const;

	//===========================================================================
	/*!	@brief		クロップ情報取得
	*/
	//===========================================================================
	graphics::Rect2D		GetCharacterRect( char asciiCode ) const;
	graphics::Rect2D		GetCharacterRectUV( char asciiCode ) const;

	//===========================================================================
	/*!	@brief		フォントテクスチャ
	*/
	//===========================================================================
	const resource::Texture*	GetTexture( void ) const;
	
protected:
	//===========================================================================
	/*!	@brief		画像マップ生成
		@note		m_fontImageがセットされていなければならない
	*/
	//===========================================================================
	bool	_CreateFontTable( void );


	//===========================================================================
	/*!	@brief		フォントテーブル削除
	*/
	//===========================================================================
	void	_DestroyFontTable( void );

	//===========================================================================
	/*!	@brief		文字インデックスを取得
	*/
	//===========================================================================
	s32		_GetCharacterIndex( char c ) const;
	
private:
	//----------------------メンバ変数-----------------------
	//resource::ImageSurface	m_fontImage;		//!< フォント画像(等幅でなければならない)	
	resource::Texture*		m_fontTexture;		//!< テクスチャ
	s32						m_fontWidth;		//!< フォント幅
	s32						m_fontHeight;		//!< フォント高さ
	s32						m_xCharNum;			//!< 横方向の文字数
	bool					m_initialized;		//!< 初期化済みならtrue

	//VecSurface				m_vecImage;			//!< フォント画像
	
	
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			Font();
	virtual~Font();
};


}	// namespace font

}	// namespace nk

#endif  // __FONT_H__
