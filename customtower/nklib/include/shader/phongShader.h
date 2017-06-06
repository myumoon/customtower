//=============================================================================
/*!	@file	phongShader.h

	@brief	Phongシェーダー管理クラス

	@author	井手 竜之介
	@date	2012/02/23
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __PHONGSHADER_H__
#define __PHONGSHADER_H__

//-------------------------------インクルード-------------------------------
#include "./shader.h"


namespace nk {
namespace graphics {

//=============================================================================
/*!
								Phongシェーダークラス
			lightVec, worldMat を使用
*/
//=============================================================================
class PhongShader : public Shader {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 初期化
	void	Init();
	
	//! パラメーターの設定
	void	SetParam( nk::resource::Material* material, nk::system::Camera* camera );
	

	
private:
	//----------------------メンバ変数-----------------------
	/* Cg引数のエントリーポイント */
	CGparameter 	m_entWorldIT;			//!< ワールド変換の逆転置行列
	CGparameter 	m_entLightVec;			//!< ライトベクトル
	CGparameter 	m_entCamPos;			//!< カメラベクトル
	CGparameter		m_entDecalTex;			//!< テクスチャ
	CGparameter		m_entWorldViewProj;		//!< ワールドビュープロジェクション行列
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 PhongShader();
	~PhongShader();
};

}	// namespace graphics
}	// namespace nk




#endif  // __PHONGSHADER_H__