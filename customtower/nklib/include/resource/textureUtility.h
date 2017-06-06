//=============================================================================
/*!	@file	textureUtility.h

	@brief	テクスチャユーティリティー

	@author	ryunosuke ide
	@date	2013.03.05
*/
//=============================================================================



#ifndef __TEXTURE_UTILITY_H__
#define __TEXTURE_UTILITY_H__

#include <stdio.h>
#if defined(_WIN32)
#include <winsock2.h>	// 内部の定義が再定義されるので
#include <windows.h>	// GLの前にインクルードしておかないと"APIENTRYが再定義される"
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
								画像サーフェイス
*/
//=============================================================================
struct ImageSurface {
	
#if defined(NK_USE_SDL)
	SDL_Surface*	image;		//!< 画像サーフェイス
#else
	GlPngSurface*	image;		//!< 画像サーフェイス
#endif
	
	bool			created;	//!< 生成済みならtrue

	ImageSurface() {
		this->image		= NULL;
		this->created	= false;
	}

#if defined(NK_USE_SDL)
	void Register( SDL_Surface* image )
#elif defined(NK_USE_GL)
	void Register( GlPngSurface* image )
#else
	#error 関数未定義
#endif
	{
		this->image	= image;
		if( this->image ) {
			this->created	= true;
		}
	}

	//! 幅習得
	u32	GetWidth( void ) const;

	//! 高さ習得
	u32	GetHeight( void ) const;

	
};


	
//=============================================================================
/*!	@brief	画像ファイルの読込み
	@param	dst		出力 : 画像サーフェイス
	@param	path	入力 : 画像パス
	@return	true.読み込み成功	false.読み込み失敗
*/
//=============================================================================
extern bool 	LoadImageSurface( ImageSurface* dst, const char* path );


//=============================================================================
/*!	@brief	カラサーフェスの作成
	@param	width	幅
	@param	height	高さ
	@param	depth	デプス
	@return	true.成功	false.失敗
*/
//=============================================================================
extern bool 	CreateEmptySurface( ImageSurface* dst, u32 width, u32 height, u32 depth );

	
//=============================================================================
/*!	@brief	画像ファイルの開放
	@param	開放する画像
*/
//=============================================================================
extern void		ReleaseImageSurface( ImageSurface* img );




}	// namespace resource
	
	
}	// namespace nk








#endif  // __TEXTURE_UTILITY_H__