//=============================================================================
/*!	@file	phongShader.h

	@brief	Phong�V�F�[�_�[�Ǘ��N���X

	@author	��� ���V��
	@date	2012/02/23
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __PHONGSHADER_H__
#define __PHONGSHADER_H__

//-------------------------------�C���N���[�h-------------------------------
#include "./shader.h"


namespace nk {
namespace graphics {

//=============================================================================
/*!
								Phong�V�F�[�_�[�N���X
			lightVec, worldMat ���g�p
*/
//=============================================================================
class PhongShader : public Shader {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ������
	void	Init();
	
	//! �p�����[�^�[�̐ݒ�
	void	SetParam( nk::resource::Material* material, nk::system::Camera* camera );
	

	
private:
	//----------------------�����o�ϐ�-----------------------
	/* Cg�����̃G���g���[�|�C���g */
	CGparameter 	m_entWorldIT;			//!< ���[���h�ϊ��̋t�]�u�s��
	CGparameter 	m_entLightVec;			//!< ���C�g�x�N�g��
	CGparameter 	m_entCamPos;			//!< �J�����x�N�g��
	CGparameter		m_entDecalTex;			//!< �e�N�X�`��
	CGparameter		m_entWorldViewProj;		//!< ���[���h�r���[�v���W�F�N�V�����s��
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 PhongShader();
	~PhongShader();
};

}	// namespace graphics
}	// namespace nk




#endif  // __PHONGSHADER_H__