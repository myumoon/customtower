//=============================================================================
/*!	@file	attitude.cpp

	@brief	�p���s�񐶐��N���X

	@author	��� ���V��
	@date	2011/11/25
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/graphics/attitude.h"



namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Attitude::Attitude() : 
	//m_rotFlag(FLAG_NONE),
	//m_rotate(0),
	//m_rotAxis(),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pos(0.0f, 0.0f, 0.0f)
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
Attitude::~Attitude()
{
	
}


//===========================================================================
/*!	@brief	�p���s����擾
	@param	�Ȃ�
	@return	�p���s��
*/
//===========================================================================
math::Matrix44 Attitude::GetAttitudeMatrix() const
{
	math::Matrix44& moveMat		= math::Translation( m_pos );
	math::Matrix44& scaleMat	= math::Expansion( m_scale.x, m_scale.y, m_scale.z );
	//math::Matrix44& rotMat		= math::RotateAxis(m_rotate, m_rotAxis);

	return  moveMat * scaleMat * m_rotate;
}


//===========================================================================
/*!	@brief	�ʒu���Z�b�g
	@param	pos	: �ʒu
	@return	�Ȃ�
*/
//===========================================================================
void Attitude::SetPos( const nk::math::Vector &pos )
{
	m_pos = pos;
}



//===========================================================================
/*!	@brief	�ʒu��ǉ�
	@param	pos	: �ǉ�����ʒu
	@return	�Ȃ�
*/
//===========================================================================
void Attitude::AddPos( const math::Vector& pos )
{
	m_pos += pos;
}


//===========================================================================
/*!	@brief	�X�P�[�����Z�b�g
	@param	scale	: �X�P�[��
	@return	�Ȃ�
*/
//===========================================================================
void Attitude::SetScale( const math::Vector& scale )
{
	m_scale = scale;
}


//===========================================================================
/*!	@brief	�X�P�[�����Z�b�g
	@param	scale	: �X�P�[��
	@return	�Ȃ�
*/
//===========================================================================
void Attitude::SetScale( f32 scale )
{
	if( scale < 0 ) {
		scale = 0;
	}
	m_scale.x = m_scale.y = m_scale.z = scale;
}


//===========================================================================
/*!	@brief	�X�P�[����ǉ�
	@param	scale	: �ǉ�����X�P�[��
	@return	�Ȃ�
*/
//===========================================================================
void Attitude::AddScale( f32 scale )
{
	m_scale.x += scale;
	if( m_scale.x < 0.0f ) {
		m_scale.x = 0.0f;
	}
	m_scale.y += scale;
	if( m_scale.y < 0.0f ) {
		m_scale.y = 0.0f;
	}
	m_scale.z += scale;
	if( m_scale.z < 0.0f ) {
		m_scale.z = 0.0f;
	}
}


//===========================================================================
/*!	@brief	��]�ʂ��Z�b�g
	@param	amount	: ��]��
	@param	axis	: ��]��
	@return	�Ȃ�
*/
//===========================================================================
void Attitude::SetRotate( f32 amount, const nk::math::Vector &axis )
{
	//m_rotate = amount;
	//m_rotAxis = axis;
	m_rotate = math::RotateAxis( amount, axis );
}


//===========================================================================
/*!	@brief	��]�ʂ�ǉ�
	@param	amount	: ��]��
	@param	axis	: ��]��
	@return	�Ȃ�
*/
//===========================================================================
void Attitude::AddRotate( f32 amount, const nk::math::Vector &axis )
{
	m_rotate *= math::RotateAxis( amount, axis );
}

}	// namespace graphics
}	// namespace nk