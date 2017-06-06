//=============================================================================
/*!	@file	quaternion.cpp

	@brief	�N�H�[�^�j�I��

	@author	��� ���V��
	@date	2011/12/14
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "../typedef.h"


//-------------------------------�C���N���[�h-------------------------------


namespace nk {
namespace math {

class	Matrix44;
class	Vector;

//=============================================================================
/*!
								�N�H�[�^�j�I��
*/
//=============================================================================
class Quaternion {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//! �P�ʌ�
	void			Identity();

	//! X����]
	void			RotateX( f32 theta );

	//! Y����]
	void			RotateY( f32 theta );

	//! Z����]
	void			RotateZ( f32 theta );

	//! Yaw Pitch Roll(Y,X,Z)
	void			RotateYawPitchRoll( f32 yaw, f32 pitch, f32 roll );

	//! �C�ӎ���]
	void			RotateAxis( f32 theta, const math::Vector& axis );

	//! ���K��
	void			Normalize();

	//! �|���Z
	Quaternion		operator *( const Quaternion& qua ) const;

	//! ��]�s����擾
	friend Matrix44	GetQuaternionToMatrix( const Quaternion& q );

	//! �|���Z
	friend f32		DotProduct( const Quaternion &q0, const Quaternion &q1 );

	//! ���ʐ��`���
	friend			Quaternion Slerp( const Quaternion &q0, const Quaternion &q1, f32 t );

private:
	//----------------------�����o�ϐ�-----------------------
	f32			t;				//!< ����
	f32			x, y, z;		//!< ����(i,j,k)
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 Quaternion();
	~Quaternion();
};

//! �N�H�[�^�j�I������s����擾
Matrix44	GetQuaternionToMatrix( const Quaternion& q );

//! ����
f32			DotProduct( const Quaternion& q0, const Quaternion& q1 );

//! ���ʐ��`���(Spherical Linear intERPolation)
Quaternion	Slerp( const Quaternion& q0, const Quaternion& q1, f32 t );

}	// namespace math
}	// namespace nk


#if 0
class CQuaternion {
public:
	//�ʏ킱���̒l�𒼐ڑ��삷��K�v�͂Ȃ��B
	//�������A������public�ɂ��Ă����B
	//���ڃA�N�Z�X�֎~�ɂ��Ă����Ƃ������̑��삪�ώG�ɂȂ邽�߂ł���B
	f32 x, y, z, w;

	//	�P���l�����ɂ���
	//---------------------------------------
	void Identity() {w = 1.0f; x = y = z = 0.0f;}

	//	�l���������̊p�x�ɃZ�b�g�A�b�v����
	//---------------------------------------
	void SetToRotateAboutX(f32 theta);
	void SetToRotateAboutY(f32 theta);
	void SetToRotateAboutZ(f32 theta);
	void SetToRotateAboutAxis(math::Vector &axis, f32 theta);
	void SetToYawPitchRoll(f32 Yaw, f32 Pitch, f32 Roll);

	//	�O��
	//---------------------------------------
	CQuaternion operator *(const CQuaternion &a) const;

	//	����𔺂���Z
	//---------------------------------------
	CQuaternion operator *=(const CQuaternion &a);

	//	���K��
	//---------------------------------------
	void Normalize();

	//	��]�p�Ɗp�x�����o��
	//---------------------------------------
	f32   GetRotationAngle() const;
	math::Vector GetRotationAxis()  const;
};

//�P���l�����p�̃O���[�o���ϐ�
extern const CQuaternion kQuaternionIdentity;

//�l�����̓���
extern f32 DotProduct(const CQuaternion &a, const CQuaternion &b);

//�l�����̋��ʐ��`���
extern CQuaternion Slerp(const CQuaternion &q0, const CQuaternion &q1, f32 t);

//�l�����̋���
extern CQuaternion Conjugate(const CQuaternion &q);

//�N�H�[�^�j�I�������]�s����쐬����
extern CMatrix44 GetQuaternionToMatrix( const CQuaternion &q );
#endif

#endif	// QUATERNION