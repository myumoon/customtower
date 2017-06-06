//=============================================================================
/*!	@file	phongShader.cpp

	@brief	Phongシェーダー管理クラス

	@author	井手 竜之介
	@date	2012/02/23
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/shader/phongShader.h"
#include "../../include/resource/material.h"
#include "../../include/system/camera.h"


namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	
*/
//===========================================================================
PhongShader::PhongShader() : Shader()
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
PhongShader::~PhongShader()
{
	
}

//===========================================================================
/*!	@brief	初期化
	@param	なし
	@return	なし
*/
//===========================================================================
void PhongShader::Init()
{
	m_entWorldIT			= cgGetNamedEffectParameter( m_cgEffect, "World"		);
	m_entLightVec			= cgGetNamedEffectParameter( m_cgEffect, "LightVec"		);
	m_entCamPos				= cgGetNamedEffectParameter( m_cgEffect, "CameraPos"	);
	m_entDecalTex			= cgGetNamedEffectParameter( m_cgEffect, "DecalTex"		);
	m_entWorldViewProj		= cgGetNamedEffectParameter( m_cgEffect, "WorldViewProj");	// ワールドビュープロジェクション行列を設定

}


//===========================================================================
/*!	@brief	パラメーターの設定
	@param	material	: マテリアルへのポインタ
	@return	なし
*/
//===========================================================================
void PhongShader::SetParam( nk::resource::Material *material, nk::system::Camera* camera )
{
	const graphics::ShaderData&	shaderData	= material->GetShaderData();
	math::Vector				lightVec	= shaderData.light.GetLook() - shaderData.light.GetPos();
	lightVec.Normalize();

	/* ワールドビュープロジェクション行列 */
	cgGLSetStateMatrixParameter( 
		m_entWorldViewProj,
		CG_GL_MODELVIEW_PROJECTION_MATRIX,
		CG_GL_MATRIX_IDENTITY );

	/* ライトベクトル */
	cgGLSetParameter3f( m_entLightVec, lightVec.x, lightVec.y, lightVec.z );

	/* 視線ベクトル */
	math::Vector cam = camera->GetPos();
	cgGLSetParameter3f( m_entCamPos, cam.x, cam.y, cam.z );

	/* 逆転値行列 */
	math::Matrix44 world = shaderData.worldMat;
	// @@@@@
	world.InverseMatrix();
	SetIT( m_entWorldIT, world );

	/* テクスチャID */
	cgGLSetTextureParameter( m_entDecalTex, material->GetTexture()->GetID() );

}

}	// namespace graphics
}	// namespace nk



