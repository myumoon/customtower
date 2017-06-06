//=============================================================================
/*!	@file	renderModel.h

	@brief	�`�惂�f�����N���X

	@author	��� ���V��
	@date	2012/03/03
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __RENDERMODEL_H__
#define __RENDERMODEL_H__

//-------------------------------�C���N���[�h-------------------------------
#include "drawPacketManager.h"
#include "../resource/resourcemanager.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"
#include "../graphics/attitude.h"


namespace nk {
namespace graphics {

//=============================================================================
/*!
								�`����N���X
*/
//=============================================================================
class RenderModel {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	static system::CameraManager*			m_cameraMng;		//!< �J�����Ǘ�
	static resource::ResourceManager*		m_resourceMng;		//!< ���\�[�X�Ǘ��N���X
	static graphics::DrawPacketManager*		m_drawPacketMng;	//!< �`��p�P�b�g�Ǘ�
	
	
	//-----------------------���\�b�h------------------------

	//! �`��
	virtual void	Draw( const math::Vector& pos )	{};
	
	//! ��]�ʂ��Z�b�g
	virtual void	SetRotate( f32 amount, const math::Vector& axis );
	virtual void	AddRotate( f32 amount, const math::Vector& axis );

	//! �X�P�[�����Z�b�g
	virtual void	SetScale( f32 scale );
	virtual void	AddScale( f32 scale );

	//! �F���Z�b�g
	virtual void	SetColor(Color color);

	//! �`��D��x��ݒ�
	virtual void	SetPriority( u32 pri );

	//! �`��X�N���[��
	virtual void	SetScreenId( s32 screenId );

	//! �\���E��\�����Z�b�g
	virtual void	SetVisible( bool visible );

	//! �\���E��\�����擾
	virtual bool	Visible( void ) const;
	
	//! ���\�[�X�Ǘ����Z�b�g
	static void	SetResourceManager( resource::ResourceManager* mng )	{ m_resourceMng = mng; }
	
	//! �J�����Ǘ����Z�b�g
	static void SetCameraManager( system::CameraManager* mng )			{ m_cameraMng = mng; }

	//! �`��p�P�b�g�Ǘ����Z�b�g
	static void	SetDrawPacketManager( graphics::DrawPacketManager* mng )	{ m_drawPacketMng = mng; }
	
protected:
	//----------------------�����o�ϐ�-----------------------
	Attitude		m_attitude;		//!< �p��
	Color			m_color;		//!< �F
	u32				m_priority;		//!< �`��D��x
	s32				m_screenId;		//!< �`��X�N���[��
	bool			m_visible;		//!< �\��
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 RenderModel();
	virtual ~RenderModel();
};


}	// namespace graphics
}	// namespace nk







#endif  // __RENDERMODEL_H__