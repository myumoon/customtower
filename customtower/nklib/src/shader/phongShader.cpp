//=============================================================================
/*!	@file	phongShader.cpp

	@brief	Phong�V�F�[�_�[�Ǘ��N���X

	@author	��� ���V��
	@date	2012/02/23
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/shader/phongShader.h"
#include "../../include/resource/material.h"
#include "../../include/system/camera.h"


namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	
*/
//===========================================================================
PhongShader::PhongShader() : Shader()
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
PhongShader::~PhongShader()
{
	
}

//===========================================================================
/*!	@brief	������
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void PhongShader::Init()
{
	m_entWorldIT			= cgGetNamedEffectParameter( m_cgEffect, "World"		);
	m_entLightVec			= cgGetNamedEffectParameter( m_cgEffect, "LightVec"		);
	m_entCamPos				= cgGetNamedEffectParameter( m_cgEffect, "CameraPos"	);
	m_entDecalTex			= cgGetNamedEffectParameter( m_cgEffect, "DecalTex"		);
	m_entWorldViewProj		= cgGetNamedEffectParameter( m_cgEffect, "WorldViewProj");	// ���[���h�r���[�v���W�F�N�V�����s���ݒ�

}


//===========================================================================
/*!	@brief	�p�����[�^�[�̐ݒ�
	@param	material	: �}�e���A���ւ̃|�C���^
	@return	�Ȃ�
*/
//===========================================================================
void PhongShader::SetParam( nk::resource::Material *material, nk::system::Camera* camera )
{
	const graphics::ShaderData&	shaderData	= material->GetShaderData();
	math::Vector				lightVec	= shaderData.light.GetLook() - shaderData.light.GetPos();
	lightVec.Normalize();

	/* ���[���h�r���[�v���W�F�N�V�����s�� */
	cgGLSetStateMatrixParameter( 
		m_entWorldViewProj,
		CG_GL_MODELVIEW_PROJECTION_MATRIX,
		CG_GL_MATRIX_IDENTITY );

	/* ���C�g�x�N�g�� */
	cgGLSetParameter3f( m_entLightVec, lightVec.x, lightVec.y, lightVec.z );

	/* �����x�N�g�� */
	math::Vector cam = camera->GetPos();
	cgGLSetParameter3f( m_entCamPos, cam.x, cam.y, cam.z );

	/* �t�]�l�s�� */
	math::Matrix44 world = shaderData.worldMat;
	// @@@@@
	world.InverseMatrix();
	SetIT( m_entWorldIT, world );

	/* �e�N�X�`��ID */
	cgGLSetTextureParameter( m_entDecalTex, material->GetTexture()->GetID() );

}

}	// namespace graphics
}	// namespace nk



