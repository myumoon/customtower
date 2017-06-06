//=============================================================================
/*!	@file	sprite.h

	@brief	スプライト

	@author	井手 竜之介
	@date	2011/11/18
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __SPRITE_H__
#define __SPRITE_H__


//-------------------------------インクルード-------------------------------
#include <string>
#include <list>
#include "../general.h"
#include "../resource/texture.h"
#include "../math/vector.h"
#include "./color.h"
#include "../resource/resourcemanager.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"
#include "../render/renderModel.h"

namespace nk {
namespace graphics {

//=============================================================================
/*!
								スプライトクラス
*/
//=============================================================================
class Sprite : public RenderModel {
public:
	//-----------------------型定義--------------------------
	enum {
		BILLBOARD	= BIT_SHIFT_LEFT(0),	//!< ビルボード
		VIEW		= BIT_SHIFT_LEFT(1),	//!< 描画
		DEAPTH_ON	= BIT_SHIFT_LEFT(2),	//!< デプス有効
		Z_BUFFER	= BIT_SHIFT_LEFT(3),	//!< Zバッファ
		SRC_ALPHA	= BIT_SHIFT_LEFT(4),	//!< 加算合成
	};
	typedef u32 DRAW_MODE;
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 初期化
	void			Init( const std::string& name );

	//! 描画
	virtual void	Draw( const math::Vector& pos );

	//! クロップ設定(0.0～1.0)
	void			SetUVWH( f32 u, f32 v, f32 w, f32 h );

	//! スケールを設定
	void			SetScale( const math::Vector& scale );
	void			SetScale( f32 x, f32 y );
	void			SetScale( f32 scale );


	//! 回転量を設定
	void			SetRotate( f32 rotate );

	//! 色をセット
	void			SetColor( const Color& color );

	//! アルファ値を設定
	void			SetAlpha( f32 alpha );
	void			AddAlpha( f32 alpha );

	//! 描画設定
	void			SetDrawMode( DRAW_MODE mode );		//!< 設定
	void			RemoveDrawMode( DRAW_MODE mode );		//!< 解除

	//! テクスチャを設定
	void			SetTexture( resource::Texture* tex );

	//! テクスチャ取得
	const resource::Texture*	GetTexture( void ) const;
protected:
	//! 描画
	void			_Draw( const math::Vector& pos );
	
protected:
	//----------------------メンバ変数-----------------------
	const resource::Texture*	m_texture;	//!< テクスチャ
	math::Vector				m_uv;		//!< UV
	math::Vector				m_wh;		//!< WH
	math::Vector				m_scale;	//!< スケール
	Color						m_color;	//!< 色
	f32							m_rotate;	//!< 回転量
	DRAW_MODE					m_drawMode;	//!< 描画モード
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 Sprite();
	~Sprite();
};

}	// namespace graphics
}	// namespace nk




#endif	// __SPRITE_H__
