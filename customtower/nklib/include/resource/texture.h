//=============================================================================
/*!	@file	texture.h

	@brief	テクスチャクラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __TEXTURE_H__
#define __TEXTURE_H__


//-------------------------------インクルード-------------------------------
#include <stdio.h>
#include <string>
#include "../typedef.h"
#include "textureUtility.h"

namespace nk {
namespace resource {



//=============================================================================
/*!
								テクスチャクラス
*/
//=============================================================================
class Texture {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! サーフェイスの登録
	void			Register( ImageSurface surface );

	//! テクスチャ名
	void			SetTexName( const char* name );
	void			SetTexName( std::string name );
	std::string		GetTexName() const;

	//! ID
	void			SetID(u32 id);
	u32				GetID() const;
	const u32*		GetIDPointer() const;

	//! サイズ
	void			SetSize(s32 w, s32 h);
	s32				GetWidth() const;
	s32				GetHeight() const;

	
	
private:
	//----------------------メンバ変数-----------------------
	std::string			m_texName;		//!< テクスチャ名
	u32					m_id;			//!< テクスチャID
	s32					m_width;		//!< 幅
	s32					m_height;		//!< 高さ
	ImageSurface		m_surface;		//!< サーフェイス
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			 Texture();
	virtual ~Texture();

private:
	//! デストラクタでテクスチャを開放するためコピーを禁止する
	Texture(const Texture& tex);			// 宣言だけ
	void operator =(const Texture& tex);	// 宣言だけ
};


	
//=============================================================================
/*!	@brief		テクスチャ貼り付け
	@param		バインドするテクスチャ
*/
//=============================================================================
extern void			BindTexture( const Texture* tex );


//=============================================================================
/*!	@brief		サーフェイスからテクスチャを生成
*/
//=============================================================================
extern Texture*		CreateTexture( ImageSurface src );
	

//=============================================================================
/*!	@brief		ファイルからテクスチャを生成
	@attention	メインスレッド以外で呼ぶ場合はをCreateTexture(ImageSurface)を使用してください。
*/
//=============================================================================
extern Texture*		CreateTexture( const char* filaname );


//=============================================================================
/*!	@brief		空のテクスチャを生成
	@param		width	幅
	@param		height	高さ
	@attention	メインスレッド以外で呼ぶことはできません
*/
//=============================================================================
extern Texture*		CreateEmptyTexture( s32 width, s32 height );


	
#if 0
Texture*	CreateTexture(std::string fileName)
	
/*! テクスチャを使用 */


/*! 空のテクスチャを作成 */
Texture*	CreateEmptyTexture(s32 width, s32 height);
#endif
}	// namespace resource
}	// namespace nk














#endif















































