//=============================================================================
/*!	@file	model.h

	@brief	モデルクラス

	@author	井手 竜之介
	@date	2012/02/22
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __MODEL_H__
#define __MODEL_H__

//-------------------------------インクルード-------------------------------
#include "../file/mqoFile.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"
#include "./attitude.h"
#include "../render/renderModel.h"


namespace nk {
namespace graphics {


//=============================================================================
/*!
								モデルクラス
*/
//=============================================================================
class Model : public RenderModel {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//! 初期化
	void		Init( std::string filename );

	//! 描画
	void		Draw( graphics::ShaderData& data = graphics::ShaderData() );
	void		Draw( const math::Vector& pos, graphics::ShaderData& data = graphics::ShaderData() );

private:
	//----------------------メンバ変数-----------------------
	const resource::MqoFile*				m_file;			//!< mqoファイル
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			 Model();
	virtual ~Model();
};


}	// namespace graphics
}	// namespace nk



#endif  // __MODEL_H__