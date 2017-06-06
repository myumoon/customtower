//=============================================================================
/*!	@file	drawModel.cpp

	@brief	�`�惂�f�����N���X

	@author	��� ���V��
	@date	2012/03/03
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/render/renderModel.h"
#include "../../include/resource/resourcemanager.h"
#include "../../include/render/drawpacket.h"


namespace nk {
namespace graphics {

resource::ResourceManager*		RenderModel::m_resourceMng		= NULL;	// ���\�[�X�Ǘ�
system::CameraManager*			RenderModel::m_cameraMng		= NULL;	// �J�����Ǘ�
graphics::DrawPacketManager*	RenderModel::m_drawPacketMng	= NULL;	// �`��p�P�b�g�Ǘ�
	
//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
RenderModel::RenderModel()
{
	m_priority	= 0;
	m_screenId	= 0;
	m_visible	= true;
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
RenderModel::~RenderModel()
{
	
}


//===========================================================================
/*!	@brief	��]�ʂ��Z�b�g
	@param	amount	: ��]��
	@param	axis	: ��]��
	@return	
*/
//===========================================================================
void RenderModel::SetRotate(f32 amount, const nk::math::Vector &axis)
{
	m_attitude.SetRotate(amount, axis);
}


//===========================================================================
/*!	@brief	��]�ʂ�ǉ�
	@param	amount	: ��]��
	@param	axis	: ��]��
	@return	
*/
//===========================================================================
void RenderModel::AddRotate(f32 amount, const nk::math::Vector &axis)
{
	m_attitude.AddRotate(amount, axis);
}


//===========================================================================
/*!	@brief	�g�k
	@param	scale	: �g���
	@return	
*/
//===========================================================================
void RenderModel::SetScale(f32 scale)
{
	m_attitude.SetScale(scale);
}


//===========================================================================
/*!	@brief	�g�k
	@param	scale	: �g���
	@return	
*/
//===========================================================================
void RenderModel::AddScale(f32 scale)
{
	m_attitude.AddScale(scale);
}


//===========================================================================
/*!	@brief	�F�̃Z�b�g
	@param	color	: �F
	@return	�Ȃ�
*/
//===========================================================================
void RenderModel::SetColor(nk::Color color)
{
	m_color = color;
}


//===========================================================================
/*!	@brief	�`��D��x��ݒ�
	@param	pri	: �D��x
	@return	�Ȃ�
*/
//===========================================================================
void RenderModel::SetPriority(u32 pri)
{
	m_priority = pri;
}


//===========================================================================
/*!	@brief	�X�N���[��ID��ݒ�
	@param	screenId	: �Z�b�g����X�N���[��ID
	@return	�Ȃ�
*/
//===========================================================================
void RenderModel::SetScreenId( s32 screenId )
{
	m_screenId = screenId;
}

//===========================================================================
/*!	@brief	�\����\����ݒ�
	@param	visible	: �\����\��
	@return	�Ȃ�
*/
//===========================================================================
void RenderModel::SetVisible( bool visible )
{
	m_visible = visible;
}

//===========================================================================
/*!	@brief	�\����\�����擾
	@param	----
	@return	----
*/
//===========================================================================
bool RenderModel::Visible( void ) const
{
	return m_visible;
}


}	// namespace graphics
}	// namespace nk