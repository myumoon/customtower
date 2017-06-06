//=============================================================================
/*!	@file	animationModel.h

	@brief	�A�j���[�V�������f���N���X

	@author	��� ���V��
	@date	2011/11/25
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __ANIMATIONMODEL_H__
#define __ANIMATIONMODEL_H__

//-------------------------------�C���N���[�h-------------------------------
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
								�A�j���[�V�������f���N���X
*/
//=============================================================================
class AnimationModel : public RenderModel {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ������
	void		Init( std::string name );

	//! �X�V
	void		Update();

	//! �`��
	void		Draw( const math::Vector& pos, graphics::ShaderData& data = graphics::ShaderData() );

	//! ���b�V���̕`��
	void		DrawMesh( resource::ToyFile::_Mesh* drawMesh, resource::Material m, const math::Matrix44& parentMat, graphics::ShaderData& data );

	//! �A�j���[�V�������Z�b�g
	void		SetAnimation( std::string animName );

	//! �A�j���[�V�������J�n
	void		StartAnimation();


private:
	//----------------------�����o�ϐ�-----------------------
	const resource::ToyFile*				m_toyFile;		//!< ToyStudio�t�@�C��
	const resource::ToyFile::_Animation*	m_animation;	//!< �A�j���[�V����
	s32										m_animTime;		//!< �A�j���[�V�����̎���
	Color									m_color;		//!< �F
	
	//-----------------------���\�b�h------------------------
	void	Draw(	const resource::XFile::_ModelObject&	obj,
					const resource::XFile::_Animation&		anim,
					const math::Matrix44&					trans,
					const graphics::ShaderData&				data
	);

	//! �A�j���[�V�����s����擾
	math::Matrix44	_GetAnimationMatrix( const resource::ToyFile::_AnimationItem* animItem );
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 AnimationModel();
	~AnimationModel();
};


}	// namespace graphics
}	// namespace nk



#endif  // __ANIMATIONMODEL_H__