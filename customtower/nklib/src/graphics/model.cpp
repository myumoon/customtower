//=============================================================================
/*!	@file	model.cpp

	@brief	���f���N���X

	@author	��� ���V��
	@date	2012/02/22
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/graphics/model.h"
#include "../../include/resource/resourcemanager.h"
#include "../../include/render/drawpacket.h"


namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Model::Model() : 
	RenderModel(),
	m_file(NULL)
{
	m_priority = DrawPacket::DEFAULT_PRIORITY;
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
Model::~Model()
{
	
}


//===========================================================================
/*!	@brief	������
	@param	filename	: �I�u�W�F�N�g��
	@return	�Ȃ�
*/
//===========================================================================
void Model::Init(std::string filename)
{
	m_file = m_resourceMng->GetMqoFile(filename);
	m_color = m_file->GetMaterial().GetColor();
}



//===========================================================================
/*!	@brief	�`��
	@param	data	: �V�F�[�_�[�f�[�^
	@return	�Ȃ�
*/
//===========================================================================
void Model::Draw(graphics::ShaderData& data)
{
	
	/* �s����v�Z */
	math::Matrix44& view		= m_cameraMng->GetUseCameraMatrix();
	math::Matrix44&	world		= m_attitude.GetAttitudeMatrix();
	math::Matrix44	worldView	= view * world;
	
	/* �V�F�[�_�[�ݒ� */
	data.worldMat = world;
	
	/* �}�e���A�� */
	resource::Material material = m_file->GetMaterial();
	material.SetColor(m_color);

	/* �p�P�b�g����ݒ� */
	graphics::DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();
	packet.SetMaterial(material);
	packet.SetVertex(m_file->GetVertex());
	packet.SetFace(m_file->GetFace());
	packet.SetNormalVertex(m_file->GetNormalVertex());
	packet.SetDrawType(graphics::DrawPacket::MODEL);
	packet.SetWorldViewTransform(worldView);
	packet.SetShaderData(data);
	packet.SetPriority(m_priority);
	packet.SetScreenId(m_screenId);
	packet.SetWorldMatrix(world);

	/* �`��Ǘ��ɑ��M */
	m_drawPacketMng->SendToDrawManager( packet );

}


//===========================================================================
/*!	@brief	�`��
	@param	pos	: �`��ʒu
	@return	�Ȃ�
*/
//===========================================================================
void Model::Draw(const nk::math::Vector &pos, graphics::ShaderData& data)
{
	
	/* �s����v�Z */
	m_attitude.SetPos(pos);
	Draw(data);

}





}	// namespace graphics
}	// namespace nk