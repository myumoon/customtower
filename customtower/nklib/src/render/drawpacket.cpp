//=============================================================================
/*!	@file	drawpacket.cpp

	@brief	�`��p�P�b�g�N���X

	@author	��� ���V��
	@date	2011/11/16
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/render/drawpacket.h"
#include "../../include/render/renderManager.h"



namespace nk {
namespace graphics {

//------------------------------�ÓI�����o��`------------------------------
RenderManager*	DrawPacket::m_drawManager			= NULL;
const u32	DrawPacket::DEFAULT_PRIORITY		= 0x00010000;
const u32	DrawPacket::DEFAULT_SPRITE_PRIORITY	= 0x00100000;
const u32	DrawPacket::DEFAULT_LINE_PRIORITY	= 0x01000000;



//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
DrawPacket::DrawPacket( void ) : 
	m_material(), 
	m_type(0),
	m_priority(DEFAULT_PRIORITY),
	m_isClearBuffer(false)
{
}

#if 0
//===========================================================================
/*!	@brief	�R�s�[�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
DrawPacket::DrawPacket(const DrawPacket& pack) : 
	//m_texture(pack.m_texture),
	m_material(pack.m_material),
	m_vertex(pack.m_vertex),
	m_face(pack.m_face),
	m_normal(pack.m_normal),
	m_worldViewTransform(pack.m_worldViewTransform),
	m_type(pack.m_type),
	m_priority(pack.m_priority),
	m_isClearBuffer(pack.m_isClearBuffer),
	m_screenId(pack.m_screenId)
{
	
}
#endif


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
DrawPacket::~DrawPacket()
{
	
}


//===========================================================================
/*!	@brief	�e�N�X�`�����Z�b�g
	@param	tex	: �e�N�X�`��
	@return	�Ȃ�
*/
//===========================================================================
//void DrawPacket::SetTexture(const resource::Texture* tex)
//{
//	m_texture = tex;
//}


//===========================================================================
/*!	@brief	�e�N�X�`�����擾
	@param	�Ȃ�
	@return	�e�N�X�`��
*/
//===========================================================================
//const resource::Texture* DrawPacket::GetTexture( void ) const
//{
//	return m_texture;
//}


//===========================================================================
/*!	@brief	�}�e���A�����Z�b�g
	@param	tex	: �}�e���A��
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetMaterial(const resource::Material& mat)
{
	m_material = mat;
}


//===========================================================================
/*!	@brief	�}�e���A�����擾
	@param	�Ȃ�
	@return	�}�e���A��
*/
//===========================================================================
resource::Material DrawPacket::GetMaterial( void ) const
{
	return m_material;
}


//===========================================================================
/*!	@brief	���_���Z�b�g
	@param	v	: ���_
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetVertex(const resource::Vertex& v)
{
	m_vertex.Clear();
	
	for( u32 i = 0; i < v.GetSize(); ++i ) {
		m_vertex.Add( v.GetVertex( i ) );
	}
	
}



//===========================================================================
/*!	@brief	���_���Z�b�g
	@param	v	: ���_
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::AddVertex( const math::Vector& v )
{
	m_vertex.Add( v );
}


//===========================================================================
/*!	@brief	���_���Z�b�g
	@param	v	: ���_
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::AddVertex( f32 x, f32 y, f32 z )
{
	m_vertex.Add( x, y, z );
}


//===========================================================================
/*!	@brief	���_���擾
	@param	�Ȃ�
	@return	���_
*/
//===========================================================================
resource::Vertex& DrawPacket::GetVertex( void )
{
	return m_vertex;
}



//===========================================================================
/*!	@brief	���_���擾
	@param	�Ȃ�
	@return	���_
*/
//===========================================================================
const resource::Vertex& DrawPacket::GetVertex( void ) const
{
	return m_vertex;
}


//===========================================================================
/*!	@brief	�ʂ��Z�b�g
	@param	face	: ���_
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetFace(const resource::Face& face)
{
	m_face = face;
}


//===========================================================================
/*!	@brief	�ʂ��Z�b�g
	@param	face	: ���_
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::AddFace( u32 index, const math::Vector& uv )
{
	m_face.AddFaceUV( index, uv );
}


//===========================================================================
/*!	@brief	�ʂ��Z�b�g
	@param	face	: ���_
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::AddFace( u32 index, f32 u, f32 v )
{
	m_face.AddFaceUV( index, u, v );
}


//===========================================================================
/*!	@brief	�ʂ��擾
	@param	�Ȃ�
	@return	���_
*/
//===========================================================================
resource::Face& DrawPacket::GetFace( void )
{
	return m_face;
}



//===========================================================================
/*!	@brief	�ʂ��擾
	@param	�Ȃ�
	@return	���_
*/
//===========================================================================
const resource::Face& DrawPacket::GetFace( void ) const
{
	return m_face;
}


//===========================================================================
/*!	@brief	���_�@�����Z�b�g
	@param	n	: ���_�@��
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetNormalVertex(const resource::Vertex& n)
{
	m_normal = n;
}


//===========================================================================
/*!	@brief	���_�@�����擾
	@param	�Ȃ�
	@return	���_�@��
*/
//===========================================================================
resource::Vertex& DrawPacket::GetNormalVertex( void )
{
	return m_normal;
}


//===========================================================================
/*!	@brief	���[���h�r���[�ϊ��s����Z�b�g
	@param	mat	: �ϊ��s��
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetWorldViewTransform(const math::Matrix44& mat)
{
	m_worldViewTransform = mat;
}


//===========================================================================
/*!	@brief	���[���h�ϊ��s����擾
	@param	�Ȃ�
	@return	���[���h�ϊ��s��
*/
//===========================================================================
const math::Matrix44& DrawPacket::GetWorldViewTransform( void ) const
{
	return m_worldViewTransform;
}


//===========================================================================
/*!	@brief	���[���h�ϊ��s����擾
	@param	�Ȃ�
	@return	���[���h�ϊ��s��
*/
//===========================================================================
math::Matrix44& DrawPacket::GetWorldViewTransform( void )
{
	return m_worldViewTransform;
}


//===========================================================================
/*!	@brief	�`��^�C�v��ݒ�
	@param	type	: �`��^�C�v
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetDrawType(DRAW_TYPE type)
{
	m_type |= type;
}


//===========================================================================
/*!	@brief	�}�l�[�W���ɓ]��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
// void DrawPacket::SendToDrawManager( void )
// {
// 	m_drawManager->Add(*this);
// }


//===========================================================================
/*!	@brief	�`��O�������X�g�ɓ]��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
//void DrawPacket::SendToDrawTextureList( void )
//{
//	m_drawManager->AddDrawTextureList(*this);
//}


//===========================================================================
/*!	@brief	�V�F�[�_�[�f�[�^���Z�b�g
	@param	data	: �V�F�[�_�[�f�[�^
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetShaderData(const nk::graphics::ShaderData &data)
{
	m_material.SetShaderData(data);
}


//===========================================================================
/*!	@brief	�`��D��x��ݒ�
	@param	num		: �D��x
	@return	�Ȃ�
*/
//===========================================================================
void DrawPacket::SetPriority(u32 num)
{
	m_priority = num;
}


//===========================================================================
/*!	@brief	�`��D��x���K��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
u32 DrawPacket::GetPriority( void ) const
{
	return m_priority;
}


//===========================================================================
/*!	@brief	�o�b�t�@�N���A�I�u�W�F�N�g��}��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
// void DrawPacket::AddListForBufferClear( void )
// {
// 	m_isClearBuffer = true;
// 	SendToDrawManager();
// }


//===========================================================================
/*!	@brief	�o�b�t�@�N���A�t���O���K��
	@param	�Ȃ�
	@return	true	: �o�b�t�@���N���A
	@return	false	: �N���A���Ȃ�
*/
//===========================================================================
// bool DrawPacket::IsBufferClear( void ) const
// {
// 	return m_isClearBuffer;
// }


//===========================================================================
/*!	@brief		��ɂ���
	@param		----
	@return		----
*/
//===========================================================================
void DrawPacket::Clear( void )
{

	m_type				= 0;
	m_priority			= DEFAULT_PRIORITY;
	m_isClearBuffer		= false;

	m_material.Clear();
	m_vertex.Clear();
	m_face.Clear();
	m_normal.Clear();
	m_worldViewTransform.InitIdentityMatrix();	// �P�ʍs��
	m_world.InitIdentityMatrix();				// �P�ʍs��
	
}

}	// namespace graphics
}	// namespace nk