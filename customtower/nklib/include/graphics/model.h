//=============================================================================
/*!	@file	model.h

	@brief	���f���N���X

	@author	��� ���V��
	@date	2012/02/22
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __MODEL_H__
#define __MODEL_H__

//-------------------------------�C���N���[�h-------------------------------
#include "../file/mqoFile.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"
#include "./attitude.h"
#include "../render/renderModel.h"


namespace nk {
namespace graphics {


//=============================================================================
/*!
								���f���N���X
*/
//=============================================================================
class Model : public RenderModel {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//! ������
	void		Init( std::string filename );

	//! �`��
	void		Draw( graphics::ShaderData& data = graphics::ShaderData() );
	void		Draw( const math::Vector& pos, graphics::ShaderData& data = graphics::ShaderData() );

private:
	//----------------------�����o�ϐ�-----------------------
	const resource::MqoFile*				m_file;			//!< mqo�t�@�C��
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 Model();
	virtual ~Model();
};


}	// namespace graphics
}	// namespace nk



#endif  // __MODEL_H__