//=============================================================================
/*!	@file	shadowMapping.h

	@brief	シャドウマップ

	@author	井手 竜之介
	@date	2012/02/24
	@todo	なし
	@bug	なし
*/
//=============================================================================
#ifndef __SHADOWMAPPING_H__
#define __SHADOWMAPPING_H__

//-------------------------------インクルード-------------------------------
#include "./shader.h"

namespace nk {
namespace graphics {

//=============================================================================
/*!
								シャドウマッピングクラス
	シャドウマップ生成時に必要:
		shaderName, mappingTex, mode(MODE_CREATE_SHADOWMAP)
	
	影描画時に必要:
		shaderName, mappingTex, mode(MODE_DRAW_SHADOWMAP), light
*/
//=============================================================================
class ShadowMapping : public Shader {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	//! ShaderData.modeに入れる
	enum {
		MODE_CREATE_SHADOWMAP	= 0,	// シャドウマップ生成モード
		MODE_DRAW_SHADOWMAP		= 1		// シャドウマップ使用モード
	};
	
	
	//-----------------------メソッド------------------------
	//! 初期化
	void	Init();
	
	//! パラメーターの設定
	void	SetParam( nk::resource::Material* material, nk::system::Camera* camera );
	
	//! 描画終了後の処理
	void	ProcAfterDrawing();
	
private:
	//----------------------メンバ変数-----------------------

	/* Cg引数のエントリーポイント */
	CGparameter 		m_entWorldViewProj;			// ワールドビュープロジェクション
	CGparameter 		m_entWorldLightProj;		// ワールドライトプロジェクション
	CGparameter 		m_entWorldLightTexProj;		// ワールドライトテクスチャプロジェクション
	CGparameter 		m_entWorld;					// ワールド
	CGparameter 		m_entLightPos;				// ライト位置
	CGparameter 		m_entShadowmapTex;			// シャドウマップテクスチャ
	CGparameter 		m_entDecalTex;				// オブジェクトテクスチャ
	
	/* その他 */
	resource::Texture*	m_mappingTex;				//!< シャドウマップ
	math::Vector		m_screenSize;				//!< スクリーンサイズ
	u32					m_mode;						//!< モード

	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 ShadowMapping();
	~ShadowMapping();
};

}	// namespace graphics
}	// namespace nk


#endif  // __SHADOWMAPPING_H__

