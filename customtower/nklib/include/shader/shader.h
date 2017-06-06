//=============================================================================
/*!	@file	shader.h

	@brief	�V�F�[�_�[���N���X�ƊǗ��N���X

	@author	��� ���V��
	@date	2012/02/23
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================
#ifndef __SHADER_H__
#define __SHADER_H__

//-------------------------------�C���N���[�h-------------------------------
#include <vector>
#include <string>
#include <map>
#include <list>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include "../math/matrix.h"
#include "../math/vector.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"

namespace nk {

namespace resource {
	class Material;
	class Texture;
}
namespace system {
	class Camera;
}

namespace graphics {


//----------------------------------�\����----------------------------------
//! �V�F�[�_�[�Ŏg�p����f�[�^
struct ShaderData {
	std::string			shaderName;		//!< �g�p����V�F�[�_�[��
	u32					useTechnique;	//!< �g�p����e�N�j�b�N(�f�t�H���g��0)
	math::Matrix44		worldMat;		//!< ���[���h�s��
	system::Light		light;			//!< ���C�g���
	math::Vector		screenSize;		//!< �X�N���[���T�C�Y
	u32					useTexId;		//!< �V���h�E�}�b�v���Ɏg�p����e�N�X�`��ID
	resource::Texture*	mappingTex;		//!< �}�b�s���O�p�̃e�N�X�`��ID
	u32			mode;			//!< ���[�h

	ShaderData() {
		useTechnique	= 0;
		mappingTex		= NULL;
		mode			= 0;
		useTexId		= 0;
	}

	void SetupPhongShader( const system::Light& light )
	{
		this->shaderName	= "PhongShader";
		this->light			= light;
	}
};

//=============================================================================
/*!
								�V�F�[�_�[���N���X
*/
//=============================================================================
class Shader {
public:
	friend	class	ShaderManager;

	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//! ���[�h
	//bool Load(const char *file_name);
	
	//! �V�F�[�_�[�`��J�n
	void Begin( nk::resource::Material* material, u32 teq, nk::system::Camera* camera );

	//! �V�F�[�_�[�`��I��
	void End();

protected:

	//! ������
	virtual void	Init() = 0;

	//! �l�̃Z�b�g
	virtual void	SetParam( nk::resource::Material* material, nk::system::Camera* camera ) = 0;

	//! �`��I���㏈��
	virtual	void	ProcAfterDrawing()	{}

	//! Matrix�l���t�]�u�s��ɕϊ����� val�Ɋ֘A�t����ꂽ�V�F�[�_�[�p�����[�^�ɃZ�b�g
	void SetIT( CGparameter val, math::Matrix44 &m )
	{
		math::Matrix44 mat_IT( m );
		//mat_IT.InverseMatrix();	// phong:�R�����g���Ă����Ȃ��Ă��ς��Ȃ�
		//mat_IT.Transpose();

		f32 *p = mat_IT.GetMatrix().ary16;
		cgGLSetMatrixParameterfc( val, p );
	}		

	//----------------------�����o�ϐ�-----------------------
	std::string					m_fileName;			// �t�@�C����
	CGprogram					m_vertexShader;		// �V�F�[�_�[�v���O����
	CGeffect					m_cgEffect;			// �G�t�F�N�g
	CGpass						m_cgPass;			// �p�X
	std::vector<CGtechnique>	m_cgTechnique;		// Cg�̃V�F�[�_�[�e�N�j�b�N��
	ShaderManager*				m_shaderMng;		// �V�F�[�_�[�Ǘ�
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 Shader();
	~Shader();
};


//=============================================================================
/*!
								�V�F�[�_�[�Ǘ��N���X
*/
//=============================================================================
class ShaderManager {
public:
	//-----------------------�^��`--------------------------
	typedef std::map<std::string, Shader *> ShaderMap;
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ������
	bool		Initialize( void );

	//! �G���[�`�F�b�N
	bool		CheckCgError(const char *situation);
	
	//! Cg�R���e�L�X�g���擾
	CGcontext	GetCgContext() { return m_cgContext; }

	//! vp�v���t�@�C�����擾
	CGprofile	GetVPProfile() { return m_vpProfile; }
	
	//! fp�v���t�@�C�����擾
	CGprofile	GetFPProfile() { return m_fpProfile; }

	//! �V�F�[�_�[�̓Ǎ���
	void ShaderManager::LoadShader(Shader* shader, std::string file, std::string name);

	//! �V�F�[�_�[�̎擾
	Shader*	GetShader(std::string name) const;

	//! �S�V�F�[�_�[�̍폜
	void		DeleteAll();

	//! �V�F�[�_�[�g�p�\���H
	bool		Ready( void ) const	{ return m_ready;	}
	
	
private:
	//----------------------�����o�ϐ�-----------------------
	bool								m_ready;		// �V�F�[�_�[�����p�\��
	CGcontext							m_cgContext;	// Cg�R���e�L�X�g
	CGprofile							m_vpProfile;	// vp�v���t�@�C��
	CGprofile							m_fpProfile;	// fp�v���t�@�C��
	CGeffect							m_cgEffect;		// �G�t�F�N�g
	std::map<std::string, Shader *>	m_shaderMap;	// �e�V�F�[�_�[�ւ̃|�C���^
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 ShaderManager();
	~ShaderManager();
};



}	// namespace graphics
}	// namespace nk




#endif  // __SHADER_H__