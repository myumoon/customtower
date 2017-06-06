//=============================================================================
/*!	@file	line.h

	@brief	線

	@author	井手 竜之介
	@date	2013/02/11
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __LINE_H__
#define __LINE_H__


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
								ラインクラス
*/
//=============================================================================
class Line : public RenderModel {
public:
	//-----------------------型定義--------------------------
	enum RENDER_MODE {
		RENDER_MODE_2D,
		RENDER_MODE_3D,
	};
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 描画
	virtual void		Draw( const math::Vector& pos = math::Vector() );

	//! 点を追加
	void				AddPoint( const math::Vector& pos );
	void				ClearPoints( void );

	//! 色をセット
	void				SetColor( const Color& color );

	//! アルファ値を設定
	void				SetAlpha( f32 alpha );
	void				AddAlpha( f32 alpha );

	//! 2D, 3D 設定
	void				SetRenderMode( RENDER_MODE mode );


private:
	//----------------------メンバ変数-----------------------
	Color						m_color;	//!< 色
	resource::Vertex			m_points;	//!< 描画点
	RENDER_MODE					m_mode;		//!< レンダリングモード
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 Line();
	~Line();
};

}	// namespace graphics
}	// namespace nk




#endif	// __LINE_H__
