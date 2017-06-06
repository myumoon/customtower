//=============================================================================
/*!	@file	screen.h

	@brief	スクリーン

	@author	ryunosuke ide
	@date	2012.06.23
*/
//=============================================================================

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "../resource/renderableTexture.h"
#include "../resource/texture.h"

namespace nk {

//=============================================================================
/*!
						描画スクリーン
*/
//=============================================================================
class ScreenManager {
private:
	struct ScreenTexId {
		s32					screenId;
		RenderTexId			texId;
		u32					width;
		u32					height;
		resource::Texture*	texture;
	};
	typedef std::vector<ScreenTexId>	VecScreenId;

public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//!	描画スクリーン生成
	void			CreateScreen( u32 width, u32 height, s32 screenId );

	
	//!	スクリーンIDからテクスチャIDを取得
	RenderTexId		GetTextureId( s32 screenId ) const;


	//! テクスチャを習得
	resource::Texture*	GetTexture( s32 screenId ) const;


	//!	指定したスクリーンをウインドウに貼り付ける
	void			BindWindow( s32 screenId );


	//!	指定したスクリーンの内容をクリア
	void			ClearScreen( s32 screenId );
	

	//!	スクリーンの内容を描画
	void			Draw( s32 screenId );
	
	
protected:
	//----------------------メンバ変数-----------------------
	VecScreenId		m_vecScreenId;			//!< スクリーンID
	
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			ScreenManager();
	virtual~ScreenManager();
};


}	// namespace nk

#endif  // __SCREEN_H__