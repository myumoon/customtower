//=============================================================================
/*!	@file	line.h

	@brief	���C��

	@author	��� ���V��
	@date	2013/02/11
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/graphics/line.h"
#include "../../include/render/drawpacket.h"



namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Line::Line() : RenderModel()
{
	m_priority	= DrawPacket::DEFAULT_LINE_PRIORITY;
	m_mode		= RENDER_MODE_3D;
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Line::~Line()
{
	
}


//===========================================================================
/*!	@brief	�F��ݒ�
	@param	color	: �F
	@return	�Ȃ�
*/
//===========================================================================
void Line::SetColor(const Color& color)
{
	m_color = color;
}


//===========================================================================
/*!	@brief	�A���t�@�l��ݒ�
	@param	alpha	: �Z�b�g����A���t�@�l
	@return	�Ȃ�
*/
//===========================================================================
void Line::SetAlpha(f32 alpha)
{
	m_color.a = static_cast<u8>(math::Clamp( alpha, 0.0f, 1.0f ) * 0xFF);
}


//===========================================================================
/*!	@brief	�A���t�@�l�����Z
	@param	alpha	: ������A���t�@�l
	@return	�Ȃ�
*/
//===========================================================================
void Line::AddAlpha(f32 alpha)
{
	// ���Ȃ��悤�Ɉ�Us32�ɕϊ�
	s32	a	= static_cast<s32>(m_color.a);
	a		+= static_cast<s32>(alpha * 0xFF);
	
	if( a < 0 )			{ a = 0;	}
	else if( a > 0xFF )	{ a = 0xFF;	}

	m_color.a = a;
}



//===========================================================================
/*!	@brief	�`��_��ǉ�
	@param	pos		�`��_
	@return	�Ȃ�
*/
//===========================================================================
void Line::AddPoint( const math::Vector& pos )
{

	m_points.Add( pos );
	
}



//===========================================================================
/*!	@brief	�`��_���N���A
	@param	----
	@return	----
*/
//===========================================================================
void Line::ClearPoints( void )
{

	m_points.Clear();
	
}



//===========================================================================
/*!	@brief	�`��
	@param	�`��ʒu
	@return	�Ȃ�
*/
//===========================================================================
void Line::Draw( const nk::math::Vector &pos )
{
// 	DrawPacket packet;
	graphics::DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();

	// �D��x
	packet.SetPriority( m_priority );

	// �}�e���A���𐶐�
	resource::Material material;

	// �F
	material.SetColor( m_color );
	packet.SetMaterial( material );

	// �`��_
	packet.SetVertex( m_points );

	// �`�惂�[�h
	if( m_mode == RENDER_MODE_3D ) {
		packet.SetDrawType( DrawPacket::LINE3D );
	}
	else /*if( m_mode == RENDER_MODE_2D )*/ {
		packet.SetDrawType( DrawPacket::LINE2D );
	}
	
	/* �s����v�Z */
	math::Matrix44& view		= m_cameraMng->GetUseCameraMatrix();
	math::Matrix44&	world		= m_attitude.GetAttitudeMatrix();
	math::Matrix44	worldView	= view * world;
	//math::Matrix44	worldView	= view * world;

	
	// ���[���h�ϊ��s��
	//math::Matrix44 worldView;
	
	//worldView = math::Translation( pos );
// 	worldView = 
// 		math::Translation( pos )
// 		* math::Translation( math::Vector(WIDTH, HEIGHT, 0.0f) )
// 		* math::Expansion( m_scale.x, m_scale.y, m_scale.z )
// 		* math::RotateZ( m_rotate );

	if( m_mode == RENDER_MODE_3D ) {
// 		packet.SetWorldViewTransform( worldView );
	}
	else {
		worldView =	math::Translation( pos );
// 					* math::Translation( math::Vector(WIDTH, HEIGHT, 0.0f) )
// 					* math::Expansion( m_scale.x, m_scale.y, m_scale.z )
// 					* math::RotateZ( m_rotate );
	}
	packet.SetWorldViewTransform( worldView );
	
	packet.SetScreenId( m_screenId );

	// �`��}�l�[�W���ɓo�^
// 	packet.SendToDrawManager();
	m_drawPacketMng->SendToDrawManager( packet );
}


//===========================================================================
/*!	@brief		�����_�����O���[�h�ݒ�
	@param		mode	�����_�����O���[�h
	@return		----
*/
//===========================================================================
void Line::SetRenderMode( RENDER_MODE mode )
{
	m_mode	= mode;
	
}

}	// namespace graphics
}	// namespace nk






