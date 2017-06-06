//=============================================================================
/*!	@file	attitude.h

	@brief	�p���s�񐶐��N���X

	@author	��� ���V��
	@date	2011/11/25
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __ATTITUDE_H__
#define __ATTITUDE_H__

//-------------------------------�C���N���[�h-------------------------------
#include "../math/matrix.h"
#include "../math/vector.h"



namespace nk {
namespace graphics {


//=============================================================================
/*!
								�p���N���X
*/
//=============================================================================
class Attitude {
public:
	//-----------------------�^��`--------------------------
	//enum ROTATE_FLAG {
	//	FLAG_NONE,			// ����
	//	FLAG_ROTATE_XYZ,	// XYZ������ɉ�]
	//	FLAG_ROTATE_AXIS,	// �����S�ŉ�]
	//};
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! �p���s����擾
	math::Matrix44	GetAttitudeMatrix() const;

	//! �ʒu���Z�b�g
	void			SetPos( const math::Vector& pos );
	void			AddPos( const math::Vector& pos );

	//! �X�P�[�����Z�b�g
	void			SetScale( const math::Vector& scale );
	void			SetScale( f32 scale );
	void			AddScale( f32 scale );
 
	//! ��]�ʂ��Z�b�g
	//void			SetRotate(const math::Vector& rot);
	void			SetRotate( f32 amount, const math::Vector& axis );
	void			AddRotate( f32 amount, const math::Vector& axis );
	
private:
	//----------------------�����o�ϐ�-----------------------
	//f32			m_rotate;		//!< ��]��
	//math::Vector	m_rotAxis;		//!< ��]��
	math::Matrix44	m_rotate;		//!< ��]
	math::Vector	m_scale;		//!< �X�P�[��
	math::Vector	m_pos;			//!< �ʒu
	//ROTATE_FLAG		m_rotFlag;		//!< ��]���@�t���O
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 Attitude();
	~Attitude();
};

}	// namespace graphics
}	// namespace nk



#endif  // __ATTITUDE_H__