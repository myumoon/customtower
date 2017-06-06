//=============================================================================
/*!	@file	shader.h

	@brief	�V�F�[�_�[���N���X�ƊǗ��N���X

	@author	��� ���V��
	@date	2012/02/23
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#include "../../include/shader/shader.h"
#include "../../include/general.h"
#include "../../include/resource/material.h"
#include "../../include/system/camera.h"

namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Shader::Shader() : m_fileName(""), m_shaderMng(NULL)
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
Shader::~Shader()
{
	m_cgTechnique.clear();
	cgDestroyEffect( m_cgEffect );
}


//===========================================================================
/*!	@brief	�V�F�[�_�[�����J�n
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Shader::Begin( nk::resource::Material* material, u32 teq, nk::system::Camera* camera )
{
	// �V�F�[�_�[�p�����[�^���Z�b�g
	SetParam( material, camera );

	// ���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[��
	// �v���t�@�C����L���ɂ���B
	cgGLEnableProfile( m_shaderMng->GetVPProfile() );
	cgGLEnableProfile( m_shaderMng->GetFPProfile() );

	// �`��p�X���Z�b�g����
	m_cgPass = cgGetFirstPass( m_cgTechnique[teq] );
	cgSetPassState( m_cgPass );

}


//===========================================================================
/*!	@brief	�V�F�[�_�[�����I��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Shader::End()
{

	cgGLUnbindProgram( m_shaderMng->GetVPProfile() );
	cgGLUnbindProgram( m_shaderMng->GetFPProfile() );
	cgGLDisableProfile( m_shaderMng->GetVPProfile() );
	cgGLDisableProfile( m_shaderMng->GetFPProfile() );

	ProcAfterDrawing();

}













//========================================================================
//	�N���X�FShaderManager
//	���@�e�F�R���X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F
//	 memo �F
//========================================================================
ShaderManager::ShaderManager()
{
	m_ready		= false; 
	m_vpProfile	= CG_PROFILE_UNKNOWN;
	m_fpProfile	= CG_PROFILE_UNKNOWN;

#if 0
	//	�V�F�[�_�[�T�|�[�g�𒲂ׂ�
	//---------------------------------------

	// ARBvp1 ����� ARBfp1�̃T�|�[�g�𒲂ׂ�
	if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) ) {
		m_vpProfile = CG_PROFILE_ARBVP1;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) ) {
		m_fpProfile = CG_PROFILE_ARBFP1;
	}

	// VP20, FP20�����ׂ�
	if( cgGLIsProfileSupported(CG_PROFILE_VP20) ) {
		m_vpProfile = CG_PROFILE_VP20;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP20) ) {
		m_fpProfile = CG_PROFILE_FP20;
	}

	// VP30, FP30�����ׂ�
	if( cgGLIsProfileSupported(CG_PROFILE_VP30) ) {
		m_vpProfile = CG_PROFILE_VP30;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP30) ) {
		m_fpProfile = CG_PROFILE_FP30;
	}

	// �V�F�[�_�[���T�|�[�g���͏I��	
	if( m_vpProfile == CG_PROFILE_UNKNOWN || m_fpProfile == CG_PROFILE_UNKNOWN ) {
		RELEASE_PRINTF("Shader is not Supported. Application Terminated.\n");
	}
	else {
		// Cg�R���e�L�X�g�̍쐬
		m_cgContext = cgCreateContext();
		cgGLRegisterStates( m_cgContext );
		cgGLSetManageTextureParameters( m_cgContext, CG_TRUE );

		m_ready = CheckCgError("[Shader init]");
	}

#endif
	
}



//========================================================================
//	�N���X�FShaderManager
//	���@�e�F�f�X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F
//	 memo �F
//========================================================================
ShaderManager::~ShaderManager()
{
	// �R���e�L�X�g�̉��
	cgDestroyContext( m_cgContext );

}





//===========================================================================
/*!	@brief	������
	@param	�Ȃ�
*/
//===========================================================================
bool ShaderManager::Initialize( void )
{

	//	�V�F�[�_�[�T�|�[�g�𒲂ׂ�
	//---------------------------------------

	// ARBvp1 ����� ARBfp1�̃T�|�[�g�𒲂ׂ�
	if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) ) {
		m_vpProfile = CG_PROFILE_ARBVP1;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) ) {
		m_fpProfile = CG_PROFILE_ARBFP1;
	}

	// VP20, FP20�����ׂ�
	if( cgGLIsProfileSupported(CG_PROFILE_VP20) ) {
		m_vpProfile = CG_PROFILE_VP20;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP20) ) {
		m_fpProfile = CG_PROFILE_FP20;
	}

	// VP30, FP30�����ׂ�
	if( cgGLIsProfileSupported(CG_PROFILE_VP30) ) {
		m_vpProfile = CG_PROFILE_VP30;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP30) ) {
		m_fpProfile = CG_PROFILE_FP30;
	}

	// �V�F�[�_�[���T�|�[�g���͏I��	
	if( m_vpProfile == CG_PROFILE_UNKNOWN || m_fpProfile == CG_PROFILE_UNKNOWN ) {
		RELEASE_PRINTF("Shader is not Supported. Application Terminated.\n");
	}
	else {
		// Cg�R���e�L�X�g�̍쐬
		m_cgContext = cgCreateContext();
		cgGLRegisterStates( m_cgContext );
		cgGLSetManageTextureParameters( m_cgContext, CG_TRUE );

		m_ready = CheckCgError("[Shader init]");
	}

	return m_ready;
}




//===========================================================================
/*!	@brief	�V�F�[�_�[��Ǎ���
	@param	shader		: �V�F�[�_�[�N���X�ւ̃|�C���^
	@param	file		: �t�@�C���p�X
	@param	name		: �V�F�[�_�[��(�����Ɏg�p)
	@return	�Ȃ�
	\note	�V�F�[�_�[�̓}�l�[�W���[��delete����
*/
//===========================================================================
void ShaderManager::LoadShader( Shader* shader, std::string file, std::string name )
{
	if( m_ready ) {
		
		shader->m_cgEffect = cgCreateEffectFromFile( m_cgContext, file.c_str(), NULL );
		CheckCgError( "Shader Load-Compile" );

		// �V�F�[�_�[���G���[�Ȃ��ǂ߂����`�F�b�N
		if( shader->m_cgEffect == 0 ) {
			PRINTF( "\nShader Compile Error.\n" );
			SafeDelete( shader );
			return;
		}

		// �擪�e�N�j�b�N��ǂݍ���
		CGtechnique tech = cgGetFirstTechnique( shader->m_cgEffect );

		// �e�N�j�b�N�������������H
		while( tech ) {
			if( !tech ) {
				PRINTF( "%s: No valid technique\n", file.c_str() );
				SafeDelete( shader );
				return;
			}
			tech = cgGetNextTechnique( tech );
		}

		// �e�N�j�b�N��o�^
		tech = cgGetFirstTechnique( shader->m_cgEffect );

		while( tech ) {
			shader->m_cgTechnique.push_back( tech );
			tech = cgGetNextTechnique( tech );	
		}


		// �V�F�[�_�[�N���X���Z�b�g�A�b�v
		shader->m_shaderMng			= this;
		shader->m_fileName			= file;

		// �V�F�[�_�[�}�b�v�ɒǉ�
		m_shaderMap.insert( std::pair<std::string, Shader *>(name, shader) );

		// �V�F�[�_�[��������
		shader->Init();
	}

	return;	
}



//===========================================================================
/*!	@brief	�G���[�`�F�b�N
	@param	situation	: �`�F�b�N���ڕ�����
	@return	true		: �G���[����
	@return	false		: �G���[
*/
//===========================================================================
bool ShaderManager::CheckCgError( const char *situation )
{
	CGerror err = cgGetError();

	if( err != CG_NO_ERROR ) {
		RELEASE_PRINTF( "%s : %s\n", situation, cgGetErrorString(err) );

		if( err == CG_COMPILER_ERROR ) {
			RELEASE_PRINTF( "%s\n", cgGetLastListing(m_cgContext) );
			return false;
		}
	}

	return true;
}


//===========================================================================
/*!	@brief	�V�F�[�_�[�̏K��
	@param	������
	@return	�V�F�[�_�[
*/
//===========================================================================
Shader* ShaderManager::GetShader( std::string name ) const
{
	ASSERT( m_ready, "shader not initialized" );
	
	if( m_ready ) {
		ShaderMap::const_iterator itr = m_shaderMap.begin();
		ShaderMap::const_iterator end = m_shaderMap.end();

		for( ; itr != end; ++itr ) {
			if( (*itr).first == name ) {
				return (*itr).second;
			}
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief	�S�V�F�[�_�[���폜
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void ShaderManager::DeleteAll()
{
	ShaderMap::iterator itr = m_shaderMap.begin();
	ShaderMap::iterator end = m_shaderMap.end();

	//	�V�F�[�_�[�S�ẴC���X�^���X���폜
	//---------------------------------------
	for( ; itr != end; itr++) {
		SafeDelete( (*itr).second );
	}
	m_shaderMap.clear();

}


}	// namespace graphics
}	// namespace nk













