//=============================================================================
/*!	@file	quaternion.cpp

	@brief	�N�H�[�^�j�I��

	@author	��� ���V��
	@date	2011/12/14
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================



//-------------------------------�C���N���[�h-------------------------------
#include <math.h>
#include "../../include/math/quaternion.h"
#include "../../include/math/vector.h"
#include "../../include/math/matrix.h"
#include "../../include/general.h"


namespace nk {
namespace math {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), t(0.0f)
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Quaternion::~Quaternion()
{
	
}


//===========================================================================
/*!	@brief	�P�ʌ���
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Quaternion::Identity()
{
	t = 1.0f;
	x = y = z = 0.0f;
}


//===========================================================================
/*!	@brief	���K��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void Quaternion::Normalize()
{
	/* �l�����̑傫�����v�Z���� */
	f32 mag = sqrtf(t * t + x * x + y * y + z * z);

	/* �[�����Z�`�F�b�N */
	if(mag > 0.0f) {
		f32 oneOvermag = 1.0f / mag;
		t *= oneOvermag;
		x *= oneOvermag;
		y *= oneOvermag;
		z *= oneOvermag;
	} else {
		PRINTF("Quaternion::normalize()�[�����Z�G���[\n");
		
		/* �ЂƂ܂������� */
		Identity();
	}
}

//===========================================================================
/*!	@brief	X����]
	@param	theta	: ��]��
	@return	�Ȃ�
*/
//===========================================================================
void Quaternion::RotateX(f32 theta)
{
	/* �����̊p�x���v�Z���� */
	f32 halfTheta = theta * 0.5f;

	/* �l��ݒ肷�� */
	t = cosf(halfTheta);
	x = sinf(halfTheta);
	y = 0.0f;
	z = 0.0f;
}


//===========================================================================
/*!	@brief	Y����]
	@param	theta	: ��]��
	@return	�Ȃ�
*/
//===========================================================================
void Quaternion::RotateY(f32 theta)
{
	/* �����̊p�x���v�Z���� */
	f32 halfTheta = theta * 0.5f;

	/* �l��ݒ肷�� */
	t = cosf(halfTheta);
	x = 0.0f;
	y = sinf(halfTheta);
	z = 0.0f;
}



//===========================================================================
/*!	@brief	Z����]
	@param	theta	: ��]��
	@return	�Ȃ�
*/
//===========================================================================
void Quaternion::RotateZ(f32 theta)
{
	/* �����̊p�x���v�Z���� */
	f32 halfTheta = theta * 0.5f;

	/* �l��ݒ肷�� */
	t = cosf(halfTheta);
	x = 0.0f;
	y = 0.0f;
	z = sinf(halfTheta);
}


//===========================================================================
/*!	@brief	�C�ӎ���]
	@param	theta	: ��]��
	@param	axis	: ��]��
	@return	�Ȃ�
*/
//===========================================================================
void Quaternion::RotateAxis(f32 theta, const math::Vector &axis)
{
	/* ��]���͐��K������Ă���K�v������ */
	f32 len = axis.GetNorm();
	
	if( fabs(len - 1.0f) > 0.01f ) {
		PRINTF( "Quaternion::SetToRotateAboutAxis �s�����x�N�g���ŉ�]���悤�Ƃ��܂���\n" );
		
		return;
	}

	/* �����̊p�Ƃ��� sin ���v�Z���� */
	f32 halfTheta = theta * 0.5f;
	f32 halfSin   = sinf( halfTheta );

	/* �l��ݒ肷�� */
	t = cosf(halfTheta);
	x = axis.x * halfSin;
	y = axis.y * halfSin;
	z = axis.z * halfSin;
}

//===========================================================================
/*!	@brief	YawPitchRoll��](YXZ��])
	@param	yaw		: Y����]��
	@param	pitch	: X����]��
	@param	roll	: Z����]��
	@return	�Ȃ�
*/
//===========================================================================
void Quaternion::RotateYawPitchRoll(f32 yaw, f32 pitch, f32 roll)
{
	/* �����̊p��sin cos���v�Z���� */
	f32 sp, sr, sy;
	f32 cp, cr, cy;
	sp = sinf(pitch * 0.5f); cp = cosf(pitch * 0.5f);
	sr = sinf(roll  * 0.5f); cr = cosf(roll  * 0.5f);
	sy = sinf(yaw   * 0.5f); cy = cosf(yaw   * 0.5f);

	t = cy * cp * cr + sy * sp * sr;
	x = cy * sp * cr + sy * cp * sr;
	y =-cy * sp * sr + sy * cp * cp;
	z =-sy * sp * cr + cy * cp * sr;
}

//===========================================================================
/*!	@brief	�N�H�[�^�j�I�����m�̊|���Z
	@param	q1	: 
	@return	
*/
//===========================================================================
Quaternion Quaternion::operator *(const Quaternion &qua) const
{
	Quaternion retQua;

	retQua.t = t * qua.t - x * qua.x - y * qua.y - z * qua.z;
	retQua.x = t * qua.x + x * qua.t + y * qua.z - z * qua.y;
	retQua.y = t * qua.y + y * qua.t + z * qua.x - z * qua.z;
	retQua.z = t * qua.z + z * qua.t + x * qua.y - z * qua.x;

	return retQua;
}


//===========================================================================
/*!	@brief	�N�H�[�^�j�I���̓���
	@param	q0, q1	: �v�Z����N�H�[�^�j�I��
	@return	����
*/
//===========================================================================
f32 DotProduct(const Quaternion &q0, const Quaternion &q1)
{
	return q0.t * q1.t + q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;
}




//===========================================================================
/*!	@brief	���ʐ��`���
	@param	q0	: �J�n���̎p��
	@param	q1	: �I�����̎p��
	@param	t	: 0.0�`1.0�̊Ԃŕ�Ԃ���
	@return	��Ԃ����N�H�[�^�j�I��
	\memo	Spherical Linear intERPolation�̗�
*/
//===========================================================================
Quaternion Slerp(const Quaternion &q0, const Quaternion &q1, f32 t)
{
	/* �͈͊O�̃p�����[�^���`�F�b�N���A���̏ꍇ�͒[�_��Ԃ� */
	if(t <= 0.0f) {
		return q0;
	}
	if(t >= 1.0f) {
		return q1;
	}

	/* ���ς�p���Ďl�����Ԃ̊p�x��cos���v�Z���� */
	f32 cosOmega = DotProduct(q0, q1);

	/*
		���̓��ς̏ꍇ�A-q1��p����
		�Q�̎l����q��-q�͓�����]��\�����A�قȂ鋅�ʐ��`��Ԃ𐶐�����ꍇ������
		���m�Ȋp�x��p���ĉ�]���邽�߂�q��-q����I������
	*/
	f32 q1t = q1.t;
	f32 q1x = q1.x;
	f32 q1y = q1.y;
	f32 q1z = q1.z;
	if( cosOmega < 0.0f ) {
		q1t			= -q1t;
		q1x			= -q1x;
		q1y			= -q1y;
		q1z			= -q1z;
		cosOmega	= -cosOmega;
	}

	/*
		��ԗp�̃t���N�V�������v�Z����
		�Q�̎l�������قƂ�ǑS�������ł��邩�`�F�b�N����
	*/
	f32 k0, k1;
	if( cosOmega > 0.9999f ) {
		/* ���ɋ߂� --- �P���ɐ��`��Ԃ�p����i�[�����Z��h���j */
		k0 = 1.0f - t;
		k1 = t;
	} else {
		/*
			�O�p�@�̓���sin^2(Omega) + cos^2(Omega) = 1��p����
			���̊p�x��sin���v�Z����
		*/
		f32 sinOmega = sqrtf(1.0f - cosOmega * cosOmega);

		/* ����sin �� cos ����p�x���v�Z���� */
		f32 omega = atan2f( sinOmega, cosOmega );

		/* ���Z��1��ōςނ悤�ɁA����̋t�����v�Z���� */
		f32 oneOverSinOmega = 1.0f / sinOmega;

		/* ��ԃp�����[�^���v�Z���� */
		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sin(t * omega) * oneOverSinOmega;
	}

	/* ��Ԃ��� */
	Quaternion result;
	result.x = k0 * q0.x + k1 * q1x;
	result.y = k0 * q0.y + k1 * q1y;
	result.z = k0 * q0.z + k1 * q1z;
	result.t = k0 * q0.t + k1 * q1t;

	return result;
}



//===========================================================================
/*!	@brief	��]�s����擾
	@param	q		: �s����擾�������N�H�[�^�j�I��
	@return	�������ꂽ�s��
*/
//===========================================================================
Matrix44 GetQuaternionToMatrix(const Quaternion& q)
{
	f32 m11, m12, m13;	//�s��̉�]����
	f32 m21, m22, m23;
	f32 m31, m32, m33;

	/* ���ʂ��ėp���镛�������Ɍv�Z���Ă��� */
	f32 t = 2.0f * q.t;
	f32 x = 2.0f * q.x;
	f32 y = 2.0f * q.y;
	f32 z = 2.0f * q.z;

	/* �s��̗v�f��ݒ肷�� */
	
	/* x������ */
	m11 = 1.0f - y * q.y - z * q.z;
	m21 = x * q.y + t * q.z;
	m31 = x * q.z - t * q.y; 
	
	/* y������ */
	m12 = x * q.y - t * q.z;
	m22 = 1.0f - x * q.x - z * q.z;
	m32 = y * q.z + t * q.x;
	
	/* z������ */
	m13 = x * q.z + t * q.y;
	m23 = y * q.z - t * q.x; 
	m33 = 1.0f - x * q.x - y * q.y;

	Matrix44 retMat(	m11,	m21,	m31,	0.0f,
						m12,	m22,	m32,	0.0f,
						m13,	m23,	m33,	0.0f,
						0.0f,	0.0f,	0.0f,	1.0f);

	return retMat;
}


}	// namespace math
}	// namespace nk




#if 0
//�O���[�o���ȍP���l����
//CQuaternion�N���X�ɂ̓R���X�g���N�^���Ȃ����Ƃɒ���
//�����͂܂������K�v�Ȃ�����ł���
const CQuaternion kQuaternionIdentity = {
1.0f, 0.0f, 0.0f, 0.0f
};


//========================================================================
//	�N���X�FCQuaternion
//	���@�e�FX����]
//	���@���F��]�p�x
//	�߂�l�F��]��̃N�H�[�^�j�I��
//	 memo �F
//========================================================================
void CQuaternion::SetToRotateAboutX(f32 theta)
{
/* �����̊p�x���v�Z���� */
f32 halftheta = theta * 0.5f;

/* �l��ݒ肷�� */
w = cosf( halftheta );
x = sinf( halftheta );
y = 0.0f;
z = 0.0f;
}

//========================================================================
//	�N���X�FCQuaternion
//	���@�e�FY����]
//	���@���F��]�p�x
//	�߂�l�F��]��̃N�H�[�^�j�I��
//	 memo �F
//========================================================================
void CQuaternion::SetToRotateAboutY(f32 theta)
{
/* �����̊p�x���v�Z���� */
f32 halftheta = theta * 0.5f;

/* �l��ݒ肷�� */
w = cosf( halftheta );
x = 0.0f;
y = sinf( halftheta );
z = 0.0f;
}

//========================================================================
//	�N���X�FCQuaternion
//	���@�e�FZ����]
//	���@���F��]�p�x
//	�߂�l�F��]��̃N�H�[�^�j�I��
//	 memo �F
//========================================================================
void CQuaternion::SetToRotateAboutZ(f32 theta)
{
/* �����̊p�x���v�Z���� */
f32 halftheta = theta * 0.5f;

/* �l��ݒ肷�� */
w = cosf( halftheta );
x = 0.0f;
y = 0.0f;
z = sinf( halftheta );
}

//========================================================================
//	�N���X�FCQuaternion
//	���@�e�F�C�ӎ���]
//	���@���F��]��
//			��]�p�x
//	�߂�l�F��]��̃N�H�[�^�j�I��
//	 memo �F
//========================================================================
void CQuaternion::SetToRotateAboutAxis(math::Vector &axis, f32 theta)
{
/* ��]���͐��K������Ă���K�v������ */
f32 len = axis.GetNorm();

if( fabs(len - 1.0f) > 0.01f ) {
#ifndef NODEBUG
printf( "Quaternion::SetToRotateAboutAxis �s�����x�N�g���ŉ�]���悤�Ƃ��܂���\n" );
#endif
return;
}

/* �����̊p�Ƃ��� sin ���v�Z���� */
f32 halftheta = theta * 0.5f;
f32 halfsin   = sinf( halftheta );

/* �l��ݒ肷�� */
w = cosf( halftheta );
x = axis.x * halfsin;
y = axis.y * halfsin;
z = axis.z * halfsin;
}

//========================================================================
//	�N���X�FCQuaternion
//	���@�e�FXYZ��]
//	���@���FY��]��
//			X��]��
//			Z��]��
//	�߂�l�F��]��̃N�H�[�^�j�I��
//	 memo �F
//========================================================================
void CQuaternion::SetToYawPitchRoll(f32 Yaw, f32 Pitch, f32 Roll)
{
/* �����̊p��sin cos���v�Z���� */
f32 sp, sr, sy;
f32 cp, cr, cy;
sp = sinf(Pitch * 0.5f); cp = cosf(Pitch * 0.5f);
sr = sinf(Roll  * 0.5f); cr = cosf(Roll  * 0.5f);
sy = sinf(Yaw   * 0.5f); cy = cosf(Yaw   * 0.5f);

w = cy * cp * cr + sy * sp * sr;
x = cy * sp * cr + sy * cp * sr;
y =-cy * sp * sr + sy * cp * cp;
z =-sy * sp * cr + cy * cp * sr;
}

//========================================================================
//	�N���X�FCQuaternion
//	���@�e�F*���Z�q�̃I�[�o�[���[�h
//	���@���F�N�H�[�^�j�I��
//	�߂�l�F
//	 memo �F�l�����̊O��
//	
//	�u����Ŋw�ԃQ�[���RD���w�v�ł͒�`����O��
//	��Z�̏����́u������E�ɂ����鏇���v
//	�i���Z���������₷�����邽�߁j�ł��邪�A
//	���̎����͒�`�ʂ�
//	��Z�̏����́u�E���獶�ɂ����鏇���v�Ƃ���B
//	����ɂ��AOpenGL�̍s�񉉎Z�Ɠ����l�����ɂł���
//========================================================================
CQuaternion CQuaternion::operator *(const CQuaternion &a) const
{
CQuaternion result;

result.w = w * a.w - x * a.x - y * a.y - z * a.z;
result.x = w * a.x + x * a.w + y * a.z - z * a.y;
result.y = w * a.y + y * a.w + z * a.x - z * a.z;
result.z = w * a.z + z * a.w + x * a.y - z * a.x;

return result;
}



//========================================================================
//	�N���X�FCQuaternion
//	���@�e�F*=���Z�q�̃I�[�o�[���[�h
//	���@���F�N�H�[�^�j�I��
//	�߂�l�F
//	 memo �F
//
//�O�ςƑ���̑g�ݍ��킹
// �����͎��H�ɂ��Q�[���RD���w�Ɠ��������ɂ��Ă���
// q *= p �� q = q * p �̏����ł���B(q �� p * q)
//========================================================================
CQuaternion CQuaternion::operator *=(const CQuaternion &a)
{
*this = (*this) * a;

/* ���Ӓl�ւ̎Q�Ƃ�Ԃ� */
return *this;
}


//========================================================================
//	�N���X�FCQuaternion
//	���@�e�F���K��
//	���@���F
//	�߂�l�F
//	 memo �F�l�����𐳋K������B
//
// ���ӂ��ׂ��_�́A�ʏ�l�����͏��(���l���x�͈͓̔���)���K������Ă��邱�Ƃł���B
// 
// ���̊֐��͎�ɁA���������_�̌덷�̐N����h�����߂Ɏg����B
// �덷�̐N���͂�������̘A�������l�������Z���K�p���ꂽ�������邱�Ƃ�����B
//========================================================================
void CQuaternion::Normalize()
{
/* �l�����̑傫�����v�Z���� */
f32 mag = sqrtf( w * w + x * x + y * y + z * z );

/* �[�����Z�`�F�b�N */
if(mag > 0.0f) {
f32 oneOvermag = 1.0f / mag;
w *= oneOvermag;
x *= oneOvermag;
y *= oneOvermag;
z *= oneOvermag;
} else {
printf("Quaternion::normalize()�[�����Z�G���[\n");

/* �ЂƂ܂������� */
Identity();
}
}



//========================================================================
//	�N���X�FCQuaternion
//	���@�e�F��]�p�Ƃ�Ԃ�
//	���@���F
//	�߂�l�F��]�p(���W�A��)
//	 memo �F
//========================================================================
f32 CQuaternion::GetRotationAngle() const
{
/* �i�[����Ă���͔̂����̊p�ł��邱�Ƃɒ��� */
f32 theta = acosf( w );

/* ��]�p�x��Ԃ� */
return theta * 2.0f;
}


//========================================================================
//	�N���X�FCQuaternion
//	���@�e�F��]����Ԃ�
//	���@���F
//	�߂�l�F��]��
//	 memo �F
//========================================================================
math::Vector CQuaternion::GetRotationAxis() const
{
/*
sin^2(theta/2)���v�Z����
w = cos(theta/2), sin^2(x) + cos^2(x) = 1�ł��邱�Ƃɒ���
*/

f32 sinThetaOver2Sq = 1.0f -w * w;

/* ���l�̕s�m���������� */
if( sinThetaOver2Sq <= 0.0f ) {
/* �P���l�������A�s���Ȏl�����Ȃ̂œK���ɕԂ� */
return math::Vector(1.0f, 0.0f, 0.0f);
}

f32 oneOverThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

/* ��]����Ԃ� */
return math::Vector(
	x * oneOverThetaOver2,
	y * oneOverThetaOver2,
	z * oneOverThetaOver2
);
}


//========================================================================
//	���@�e�F�l�����̓���
//	���@���F
//	�߂�l�F����
//	 memo �F
//
// �񃁃��o�֐���p����̂ŁA�t�@���L�[�ȍ\����p�����Ɏl�����\����
// ���Z���Ƃ��ēn�����Ƃ��ł���
//========================================================================
f32 DotProduct( const CQuaternion &a, const CQuaternion &b)
{
return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}


//========================================================================
//	���@�e�F���ʐ��`���
//	���@���F
//	�߂�l�F��Ԍ�̎l����
//	 memo �Fq0 �` q1������t�ŕ�Ԃ����l������Ԃ�(t=0�̂Ƃ�q0, t=1�̂Ƃ�q1) 
//========================================================================
CQuaternion Slerp( const CQuaternion &q0, const CQuaternion &q1, f32 t)
{
/* �͈͊O�̃p�����[�^���`�F�b�N���A���̏ꍇ�͒[�_��Ԃ� */
if(t <= 0.0f) return q0;
if(t >= 1.0f) return q1;

/* ���ς�p���Ďl�����Ԃ̊p�x��cos���v�Z���� */
f32 cosOmega = DotProduct(q0, q1);

/*
���̓��ς̏ꍇ�A-q1��p����
�Q�̎l����q��-q�͓�����]��\�����A�قȂ鋅�ʐ��`��Ԃ𐶐�����ꍇ������
���m�Ȋp�x��p���ĉ�]���邽�߂�q��-q����I������
*/
f32 q1w = q1.w;
f32 q1x = q1.x;
f32 q1y = q1.y;
f32 q1z = q1.z;
if( cosOmega < 0.0f ) {
q1w = -q1w;
q1x = -q1x;
q1y = -q1y;
q1z = -q1z;
cosOmega = -cosOmega;
}

/*
��ԗp�̃t���N�V�������v�Z����
�Q�̎l�������قƂ�ǑS�������ł��邩�`�F�b�N����
*/

f32 k0, k1;
if( cosOmega > 0.9999f ) {
/* ���ɋ߂� --- �P���ɐ��`��Ԃ�p����i�[�����Z��h���j */
k0 = 1.0f - t;
k1 = t;
} else {
/*
�O�p�@�̓���sin^2(Omega) + cos^2(Omega) = 1��p����
���̊p�x��sin���v�Z����
*/
f32 sinOmega = sqrtf(1.0f - cosOmega * cosOmega);

/* ����sin �� cos ����p�x���v�Z���� */
f32 omega = atan2f( sinOmega, cosOmega );

/* ���Z��1��ōςނ悤�ɁA����̋t�����v�Z���� */
f32 oneOverSinOmega = 1.0f / sinOmega;

/* ��ԃp�����[�^���v�Z���� */
k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
k1 = sin(t * omega) * oneOverSinOmega;
}

/* ��Ԃ��� */
CQuaternion result;
result.x = k0 * q0.x + k1 * q1x;
result.y = k0 * q0.y + k1 * q1y;
result.z = k0 * q0.z + k1 * q1z;
result.w = k0 * q0.w + k1 * q1w;

return result;
}


//========================================================================
//	���@�e�F�l�����̋������v�Z����
//	���@���F����������l����
//	�߂�l�F�����̎l�����̔��΂̉�]�����l����
//	 memo �F
//========================================================================
CQuaternion Conjugate( const CQuaternion &q )
{
CQuaternion result;
/* ������]�� */
result.w = q.w;

/* ���΂̉�]�� */
result.x = -q.x;
result.y = -q.y;
result.z = -q.z;

return result;
}



//========================================================================
//	���@�e�F�l��������s����쐬����
//	���@���F�ϊ�����l����
//	�߂�l�F��]�s��
//	 memo �F���s�ړ������̓[���ł���
//========================================================================
CMatrix44 GetQuaternionToMatrix( const CQuaternion &q )
{
f32 m11, m12, m13;	//�s��̉�]����
f32 m21, m22, m23;
f32 m31, m32, m33;

/* ���ʂ��ėp���镛�������Ɍv�Z���Ă��� */
f32 ww = 2.0f * q.w;
f32 xx = 2.0f * q.x;
f32 yy = 2.0f * q.y;
f32 zz = 2.0f * q.z;

/* �s��̗v�f��ݒ肷�� */

/* x������ */
m11 = 1.0f - yy * q.y - zz * q.z;
m21 = xx * q.y + ww * q.z;
m31 = xx * q.z - ww * q.y; 

/* y������ */
m12 = xx * q.y - ww * q.z;
m22 = 1.0f - xx * q.x - zz * q.z;
m32 = yy * q.z + ww * q.x;

/* z������ */
m13 = xx * q.z + ww * q.y;
m23 = yy * q.z - ww * q.x; 
m33 = 1.0f - xx * q.x - yy * q.y;

//CMatrix44 result( m11, m12, m13, 0.0f,
//	           m21, m22, m23, 0.0f,
//			   m31, m32, m33, 0.0f,
//			   0.0f,0.0f,0.0f, 1.0f);
CMatrix44 result(	m11,	m21,	m31,	0.0f,
				m12,	m22,	m32,	0.0f,
				m13,	m23,	m33,	0.0f,
				0.0f,	0.0f,	0.0f,	1.0f);

return result;
}

#endif
