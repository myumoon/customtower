//=============================================================================
/*!	@file	sprite.h

	@brief	�X�v���C�g

	@author	��� ���V��
	@date	2011/11/18
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/graphics/sprite.h"
#include "../../include/render/drawpacket.h"
#include "../../include/utility/autoTime.h"

namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Sprite::Sprite() :
	RenderModel(),
	m_texture(),
	m_uv(),
	m_wh(1.0f, 1.0f, 0.0f),
	m_scale(1.0f, 1.0f, 1.0f),
	m_rotate(0.0f),
	m_color(),
	m_drawMode(0)
{
	m_priority = DrawPacket::DEFAULT_SPRITE_PRIORITY;
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Sprite::~Sprite()
{
	
}


//===========================================================================
/*!	@brief	������
	@param	name	: �\������e�N�X�`����
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::Init(const std::string& name)
{			
	m_texture 	= m_resourceMng->GetTexture(name);
	m_screenId	= 0;
}


//===========================================================================
/*!	@brief	�N���b�v�ݒ�
	@param	u,v,w,h	: �؂蔲�����s��UV���W�Ƃ��̕�(0.0�`1.0)
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetUVWH(f32 u, f32 v, f32 w, f32 h)
{
	m_uv.x = u;
	m_uv.y = v;
	m_wh.x = w;
	m_wh.y = h;
}


//===========================================================================
/*!	@brief	�X�P�[����ݒ�
	@param	scale	: �X�P�[��(0.0�`)
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetScale(const nk::math::Vector &scale)
{
	m_scale = scale;
	m_scale.z = 1.0f;
}


//===========================================================================
/*!	@brief	�X�P�[����ݒ�
	@param	x,y	: �c���ɑ΂��ẴX�P�[����
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetScale(f32 x, f32 y)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = 1.0f;
}


//===========================================================================
/*!	@brief	�X�P�[����ݒ�
	@param	scale	: �c���ɑ΂��ẴX�P�[����
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetScale(f32 scale)
{
	SetScale(math::Vector(scale, scale, 1.0f));
}


//===========================================================================
/*!	@brief	�F��ݒ�
	@param	color	: �F
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetColor(const Color& color)
{
	m_color = color;
}


//===========================================================================
/*!	@brief	�A���t�@�l��ݒ�
	@param	alpha	: �Z�b�g����A���t�@�l
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetAlpha(f32 alpha)
{
	m_color.a = static_cast<u8>(math::Clamp( alpha, 0.0f, 1.0f ) * 0xFF);
}


//===========================================================================
/*!	@brief	�A���t�@�l�����Z
	@param	alpha	: ������A���t�@�l
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::AddAlpha(f32 alpha)
{
	// ���Ȃ��悤�Ɉ�Us32�ɕϊ�
	s32	a	= static_cast<s32>(m_color.a);
	a		+= static_cast<s32>(alpha * 0xFF);
	a		= math::Clamp( a, 0x00, 0xFF);

	m_color.a = static_cast<u8>(a);
}


//===========================================================================
/*!	@brief	�`��ݒ�
	@param	mode	: �ݒ肷��`�惂�[�h
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetDrawMode(nk::graphics::Sprite::DRAW_MODE mode)
{
	m_drawMode |= mode;
}


//===========================================================================
/*!	@brief	�`��ݒ�
	@param	mode	: ��������`�惂�[�h
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::RemoveDrawMode(nk::graphics::Sprite::DRAW_MODE mode)
{
	m_drawMode &= ~mode;
}


//===========================================================================
/*!	@brief	��]�ʂ�ݒ�
	@param	rotate	: ��]��
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetRotate(f32 rotate)
{
	m_rotate = rotate;
}



//===========================================================================
/*!	@brief	�`��
	@param	�`��ʒu
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::Draw(const nk::math::Vector &pos)
{
	if( Visible() ) {
		_Draw( pos );
	}
}

//===========================================================================
/*!	@brief	�`��
	@param	�`��ʒu
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::_Draw(const nk::math::Vector &pos)
{
//  	AUTO_TIME( _Draw );
	DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();

	// �D��x
	packet.SetPriority(m_priority);

	// �}�e���A���𐶐�
	resource::Material material;

	// �e�N�X�`��
	material.SetTexture(m_texture);
	packet.SetMaterial(material);

	// �F
	material.SetColor(m_color);
	packet.SetMaterial(material);

	// ���_
	if( m_texture == NULL ) {
		return;
	}

	
	const f32 TEX_W = static_cast<f32>(m_texture->GetWidth());
	const f32 TEX_H = static_cast<f32>(m_texture->GetHeight());
	const f32 WIDTH	= (TEX_W * (m_uv.x + m_wh.x) - TEX_W * m_uv.x) / 2.0f;
	const f32 HEIGHT	= (TEX_H * (m_uv.y + m_wh.y) - TEX_H * m_uv.y) / 2.0f;
	
	// ���_
	{
		if( m_drawMode & BILLBOARD ) {
			packet.AddVertex( -WIDTH,  HEIGHT, 0.0f );
			packet.AddVertex( -WIDTH, -HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH, -HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH,  HEIGHT, 0.0f );
		} else {
			packet.AddVertex( -WIDTH, -HEIGHT, 0.0f );
			packet.AddVertex( -WIDTH,  HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH,  HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH, -HEIGHT, 0.0f );
		}
	}

	// ��
	{
		const math::Vector uvwh = m_uv + m_wh;
		packet.AddFace( 0, m_uv.x, m_uv.y );
		packet.AddFace( 1, m_uv.x, uvwh.y );
		packet.AddFace( 2, uvwh.x, uvwh.y );
		packet.AddFace( 0, m_uv.x, m_uv.y );
		packet.AddFace( 2, uvwh.x, uvwh.y );
		packet.AddFace( 3, uvwh.x, m_uv.y );
	}


	// ���[���h�ϊ��s��
	math::Matrix44& worldView	= packet.GetWorldViewTransform();
	if( m_drawMode & BILLBOARD ) {
		packet.SetDrawType(DrawPacket::SPRITE_BILLBOARD);	// �`��^�C�v:�r���{�[�h

		//---------------�r���{�[�h�ϊ�---------------
		math::Matrix44 billbord = m_cameraMng->GetUseCameraMatrix();
		billbord.ClearMoveComponent();		// ���s�ړ�����������
		billbord.Transpose();				// �]�u

		math::Matrix44	trans = math::Translation(pos) * math::Expansion(m_scale.x, m_scale.y, m_scale.z) * math::RotateZ(m_rotate);
		const f32* transAry = trans.GetMatrix().ary16;				// �ϊ��s��̏ȗ��`
		math::Vector	move(transAry[12], transAry[13], transAry[14]);	// ���f���̕��s�ړ�������ۑ�
	
		trans.ClearMoveComponent();				// ���s�ړ�����������

		math::Matrix44 a = billbord * trans;	// 
		a.SetElement(3, 0, move.x);
		a.SetElement(3, 1, move.y);
		a.SetElement(3, 2, move.z);

		worldView = m_cameraMng->GetUseCameraMatrix() * a;

	} else {
		packet.SetDrawType(DrawPacket::SPRITE);				// �`��^�C�v:�X�v���C�g
		worldView = 
			math::Translation( pos )
			* math::Translation( math::Vector(WIDTH, HEIGHT, 0.0f) )
			* math::Expansion( m_scale.x, m_scale.y, m_scale.z )
			* math::RotateZ( m_rotate );
	}
	packet.SetScreenId( m_screenId );
	
// 	u64 _start = GetTimeMillSec();

	// �`��}�l�[�W���ɓo�^
	m_drawPacketMng->SendToDrawManager( packet );
// 	PRINTF("_Draw : %ld\n", GetTimeMillSec() - _start);
}


//===========================================================================
/*!	@brief	�e�N�X�`�����Z�b�g
	@param	tex	: �e�N�X�`��
	@return	�Ȃ�
*/
//===========================================================================
void Sprite::SetTexture(nk::resource::Texture* tex)
{
	m_texture = tex;
}



//===========================================================================
/*!	@brief	�e�N�X�`�����擾
	@param	----
	@return	----
*/
//===========================================================================
const resource::Texture* Sprite::GetTexture( void ) const
{
	return m_texture;
}

	
}	// namespace graphics
}	// namespace nk






