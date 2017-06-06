//=============================================================================
/*!	@file	shadowMapping.h

	@brief	�V���h�E�}�b�v

	@author	��� ���V��
	@date	2012/02/24
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================
#ifndef __SHADOWMAPPING_H__
#define __SHADOWMAPPING_H__

//-------------------------------�C���N���[�h-------------------------------
#include "./shader.h"

namespace nk {
namespace graphics {

//=============================================================================
/*!
								�V���h�E�}�b�s���O�N���X
	�V���h�E�}�b�v�������ɕK�v:
		shaderName, mappingTex, mode(MODE_CREATE_SHADOWMAP)
	
	�e�`�掞�ɕK�v:
		shaderName, mappingTex, mode(MODE_DRAW_SHADOWMAP), light
*/
//=============================================================================
class ShadowMapping : public Shader {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	//! ShaderData.mode�ɓ����
	enum {
		MODE_CREATE_SHADOWMAP	= 0,	// �V���h�E�}�b�v�������[�h
		MODE_DRAW_SHADOWMAP		= 1		// �V���h�E�}�b�v�g�p���[�h
	};
	
	
	//-----------------------���\�b�h------------------------
	//! ������
	void	Init();
	
	//! �p�����[�^�[�̐ݒ�
	void	SetParam( nk::resource::Material* material, nk::system::Camera* camera );
	
	//! �`��I����̏���
	void	ProcAfterDrawing();
	
private:
	//----------------------�����o�ϐ�-----------------------

	/* Cg�����̃G���g���[�|�C���g */
	CGparameter 		m_entWorldViewProj;			// ���[���h�r���[�v���W�F�N�V����
	CGparameter 		m_entWorldLightProj;		// ���[���h���C�g�v���W�F�N�V����
	CGparameter 		m_entWorldLightTexProj;		// ���[���h���C�g�e�N�X�`���v���W�F�N�V����
	CGparameter 		m_entWorld;					// ���[���h
	CGparameter 		m_entLightPos;				// ���C�g�ʒu
	CGparameter 		m_entShadowmapTex;			// �V���h�E�}�b�v�e�N�X�`��
	CGparameter 		m_entDecalTex;				// �I�u�W�F�N�g�e�N�X�`��
	
	/* ���̑� */
	resource::Texture*	m_mappingTex;				//!< �V���h�E�}�b�v
	math::Vector		m_screenSize;				//!< �X�N���[���T�C�Y
	u32					m_mode;						//!< ���[�h

	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 ShadowMapping();
	~ShadowMapping();
};

}	// namespace graphics
}	// namespace nk


#endif  // __SHADOWMAPPING_H__

