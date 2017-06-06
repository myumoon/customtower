//=============================================================================
/*!	@file	animationModel.h

	@brief	アニメーションモデルクラス

	@author	井手 竜之介
	@date	2011/11/25
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __ANIMATIONMODEL_H__
#define __ANIMATIONMODEL_H__

//-------------------------------インクルード-------------------------------
#include "../file/xfile.h"
#include "../file/toyFile.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"
#include "../graphics/attitude.h"
#include "../render/renderModel.h"


namespace nk {
namespace graphics {

//=============================================================================
/*!
								アニメーションモデルクラス
*/
//=============================================================================
class AnimationModel : public RenderModel {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 初期化
	void		Init( std::string name );

	//! 更新
	void		Update();

	//! 描画
	void		Draw( const math::Vector& pos, graphics::ShaderData& data = graphics::ShaderData() );

	//! メッシュの描画
	void		DrawMesh( resource::ToyFile::_Mesh* drawMesh, resource::Material m, const math::Matrix44& parentMat, graphics::ShaderData& data );

	//! アニメーションをセット
	void		SetAnimation( std::string animName );

	//! アニメーションを開始
	void		StartAnimation();


private:
	//----------------------メンバ変数-----------------------
	const resource::ToyFile*				m_toyFile;		//!< ToyStudioファイル
	const resource::ToyFile::_Animation*	m_animation;	//!< アニメーション
	s32										m_animTime;		//!< アニメーションの時間
	Color									m_color;		//!< 色
	
	//-----------------------メソッド------------------------
	void	Draw(	const resource::XFile::_ModelObject&	obj,
					const resource::XFile::_Animation&		anim,
					const math::Matrix44&					trans,
					const graphics::ShaderData&				data
	);

	//! アニメーション行列を取得
	math::Matrix44	_GetAnimationMatrix( const resource::ToyFile::_AnimationItem* animItem );
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 AnimationModel();
	~AnimationModel();
};


}	// namespace graphics
}	// namespace nk



#endif  // __ANIMATIONMODEL_H__