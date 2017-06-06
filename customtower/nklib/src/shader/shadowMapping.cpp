//=============================================================================
/*!	@file	shadowMapping.h

	@brief	�V���h�E�}�b�v

	@author	��� ���V��
	@date	2012/02/24
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
//#include "project.h"
#include "../../include/shader/shadowMapping.h"

#if		defined(NK_USE_DIRECTX)

#elif	defined(NK_USE_SDLGL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_opengl.h>
#include <GL/glut.h>

#elif	defined(NK_USE_GL)
//#include <gl/glut.h>
#include <gl/gl.h>

#elif	defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#endif



#include "../../include/resource/texture.h"
#include "../../include/resource/material.h"
#include "../../include/resource/renderableTexture.h"


namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
ShadowMapping::ShadowMapping() : Shader()
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
ShadowMapping::~ShadowMapping()
{
	
}


//===========================================================================
/*!	@brief	������
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void ShadowMapping::Init()
{
	m_entWorldViewProj			= cgGetNamedEffectParameter( m_cgEffect, "WorldViewProj2"	);
	m_entWorldLightProj			= cgGetNamedEffectParameter( m_cgEffect, "WorldLightProj"	);
	m_entWorldLightTexProj		= cgGetNamedEffectParameter( m_cgEffect, "WorldLightTexProj");
	m_entWorld					= cgGetNamedEffectParameter( m_cgEffect, "World"			);
	m_entLightPos				= cgGetNamedEffectParameter( m_cgEffect, "LightPos"			);
	m_entShadowmapTex			= cgGetNamedEffectParameter( m_cgEffect, "ShadowMap"		);
	m_entDecalTex				= cgGetNamedEffectParameter( m_cgEffect, "DecalTex"			);
	
}


//===========================================================================
/*!	@brief	�p�����[�^�̃Z�b�g
	@param	material	: �}�e���A��
	@param	camera		: �J����
	@return	�Ȃ�
*/
//===========================================================================
void ShadowMapping::SetParam( nk::resource::Material *material, nk::system::Camera *camera )
{
	ShaderData& data = material->GetShaderData();

	/* �����o��ݒ� */
	m_mappingTex	= data.mappingTex;
	m_screenSize	= data.screenSize;
	m_mode			= data.mode;


	/* ���[���h���C�g�v���W�F�N�V���� */
	math::Matrix44 lightProj = math::CreatePerspectiveFieldOfView(
		50.0f,									// ���p
		data.screenSize.x / data.screenSize.y,	// �A�X�y�N�g��
		500.0f,									// �߂��Ƃ���
		2500.0f									// �����Ƃ���
	);
	math::Matrix44 WLP		= lightProj * data.light.GetCameraMatrix() * data.worldMat;
	WLP.Transpose();
	

	if( data.mode  == MODE_CREATE_SHADOWMAP ) {
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		//gluPerspective( 50.0, data.screenSize.x / data.screenSize.y, 500.0, 2500.0 );
		gluPerspective( 50.0, data.screenSize.x / data.screenSize.y, 1.0, 3000.0 );
		glViewport( 0, 0, data.mappingTex->GetWidth(), data.mappingTex->GetHeight() );

		// ���[���h���C�g�s���ݒ�
		math::Matrix44 worldLight = data.light.GetCameraMatrix() * data.worldMat;
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glLoadMatrixf( worldLight.GetMatrix().ary16 );

		/* ���[���h���C�g�v���W�F�N�V�����s�� */
		cgSetMatrixParameterfr(
			m_entWorldLightProj,
			WLP.GetMatrix().ary16
		);

	} else {

		/* GL����v���W�F�N�V�����s����擾 */
		f32 temp[16];
		glGetFloatv( GL_PROJECTION_MATRIX, temp );
		math::Matrix44 glProj;
		glProj.SetMatrix( temp );

		math::Matrix44 worldView	= camera->GetCameraMatrix() * data.worldMat;

		math::Matrix44 world		= data.worldMat;
		world.Transpose();

		math::Matrix44 WVP			= glProj * worldView;
		WVP.Transpose();

		math::Matrix44 WLTP			= WLP * math::CreatePerspectiveToTextureSpace( data.screenSize.x, data.screenSize.y );
		
		/* ���[���h�r���[�v���W�F�N�V���� */
		cgSetMatrixParameterfr(
			m_entWorldViewProj,
			WVP.GetMatrix().ary16
		);

		/* ���[���h���C�g�v���W�F�N�V�����s�� */
		cgSetMatrixParameterfr(
			m_entWorldLightProj,
			WLP.GetMatrix().ary16
		);

		/* ���[���h���C�g�e�N�X�`���v���W�F�N�V�����s�� */
		cgSetMatrixParameterfr(
			m_entWorldLightTexProj,
			WLTP.GetMatrix().ary16
		);

		/* ���C�g�ʒu */
		cgGLSetParameter3f( m_entLightPos, data.light.GetPos().x, data.light.GetPos().y, data.light.GetPos().z );

		/* �V���h�E�}�b�v�̃e�N�X�`��ID */
		cgGLSetTextureParameter( m_entShadowmapTex, data.mappingTex->GetID() );

		/* �I�u�W�F�N�g�̃e�N�X�`��ID */
		cgGLSetTextureParameter( m_entDecalTex, material->GetTexture()->GetID() );

		/* ���[���h�̃Z�b�g */
		// @@@@@ ������
		//math::Matrix44 mat = data.worldMat;
		//mat.Transpose();
		//mat.InverseMatrix();
		//mat.Transpose();
		//cgGLSetMatrixParameterfr( m_entWorld, mat.GetMatrix().ary16 );
		//SetIT( m_entWorld, mat );
		world.InverseMatrix();
		cgGLSetMatrixParameterfr( m_entWorld, world.GetMatrix().ary16 );

		/* �V���h�E�}�b�v�e�N�X�`����ݒ� */
		glBindTexture( GL_TEXTURE_2D, data.mappingTex->GetID() );
	}


}


//===========================================================================
/*!	@brief	�`��I����̏���
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void ShadowMapping::ProcAfterDrawing()
{
	/* �e�N�X�`���Ƀo�b�t�@�̏���`�� */
	if( m_mode == MODE_CREATE_SHADOWMAP ) {
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, m_mappingTex->GetID() );
		glCopyTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_mappingTex->GetWidth(), m_mappingTex->GetHeight() );
		glDisable( GL_TEXTURE_2D );
	}

}

}	// namespace graphics
}	// namespace nk



