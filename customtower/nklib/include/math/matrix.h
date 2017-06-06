//=============================================================================
/*!	@file	matrix.h

	@brief	�s��֌W

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __MATRIX_H__
#define __MATRIX_H__

//#include <math.h>
#include "../typedef.h"

namespace nk {
namespace math {


const s32 MATRIX_ROW = 4;			// �s
const s32 MATRIX_COL = 4;			// ��
const s32 MATRIX_MAX = MATRIX_ROW * MATRIX_COL;

//---------------------------------�O���錾---------------------------------
class Vector;

//----------------------------------���p��----------------------------------
/*! �s����i�[����^ */
union MatrixAry {
	f32 ary16[16];
	f32 ary44[4][4];
};



//=============================================================================
/*!
                     4x4�s��N���X
*/
//=============================================================================
class Matrix44 {
public:

	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
	Matrix44();
	Matrix44(
		f32, f32, f32, f32, 
		f32, f32, f32, f32, 
		f32, f32, f32, f32, 
		f32, f32, f32, f32
	);
			Matrix44( f32* );							// 16�v�f������f32�z����R�s�[
			Matrix44( const Matrix44 & );				// �R�s�[�R���X�g���N�^
	virtual~Matrix44();								// �f�X�g���N�^


	//	�f�[�^�̃Z�b�g
	//---------------------------------------
	void Clear();				// 0�Ŗ��߂�
	void SetMatrix( f32 * );

	//	�v�f�̃Z�b�g
	//---------------------------------------
	void SetElement( s32 row, s32 col, f32 num );

	//	X���������擾
	//---------------------------------------
	Vector GetXAxis() const;

	//	Y���������擾
	//---------------------------------------
	Vector GetYAxis() const;

	//	Z���������擾
	//---------------------------------------
	Vector GetZAxis() const;

	//	���s�ړ��������擾
	//---------------------------------------
	Vector GetParallel() const;

	//	�ϊ�
	//---------------------------------------
	void	InitIdentityMatrix();			// �P�ʍs��
	void	InverseMatrix();				// �t�s��
	Vector	ApplyMatrixXYZ( const Matrix44& m1, const Vector& v );

	//	���s�ړ��������N���A
	//---------------------------------------
	void	ClearMoveComponent();

	//	�s�Ɨ�̓���ւ�
	//---------------------------------------
	void	Transpose();	


	//	GL�ɍs����Z�b�g
	//---------------------------------------
	void		SetGL( const Matrix44 *model );
	friend void SetGL( const Matrix44 *_view, const Matrix44 *_model );


	//	�f�[�^�̎擾	
	//---------------------------------------
	MatrixAry	GetMatrix() const { return matrix; }


	//	���Z�q�̃I�[�o�[���[�h	
	//---------------------------------------
	Matrix44	operator +	(const Matrix44 &	) const;	//!< �s��{�s��
	Vector		operator *	(const Vector &		) const;	//!< �s�񂘃x�N�g��
	Matrix44	operator *	(const Matrix44 &	) const;	//!< �s�񂘍s��
	void		operator *=	(const Matrix44 &	);			//!< �s�񂘍s��
	Matrix44&	operator =	(const Matrix44 &	);			//!< ���

	//	�\��
	//---------------------------------------
	void Disp();

private:
	MatrixAry		matrix;					// 4*4�s��
};







//-----------------------------------------------
//	�ϊ��s��
//-----------------------------------------------
/* ���s�ړ� */
Matrix44	Translation( f32 x, f32 y, f32 z );
Matrix44	Translation( const Vector& xyz );

/* �g�� */
Matrix44	Expansion( f32 x, f32 y, f32 z );

/* �ϓ��Ɋg�� */
Matrix44	Expansion( f32 rate );

/* X����] */
Matrix44	RotateX( f32 theta );

/* Y����] */
Matrix44	RotateY( f32 theta );

/* Z����] */
Matrix44	RotateZ( f32 theta );

/* �C�ӂ̎��ŉ�]����ϊ��s���Ԃ� */
Matrix44	RotateAxis( f32 theta, const Vector *axis );
Matrix44	RotateAxis( f32 theta, const Vector& axis );

/* GL�ɍs����Z�b�g */
void		SetGL( const Matrix44*, const Matrix44* );

/* �ˉe�s��𐶐� */
Matrix44	CreatePerspectiveFieldOfView( f64 field_of_vision, f64 aspect_ratio, f64 near, f64 far );
Matrix44	CreatePerspectiveFieldOfView();


/* �ˉe��Ԃ���e�N�X�`����Ԃɕϊ������s��𐶐� */
Matrix44	CreatePerspectiveToTextureSpace( f32 screenW, f32 screenH );

//! �s���z��(16�v�f��f32�z��)�ɃR�s�[
void		CopyMatrix44ToArray( f32*, const Matrix44& );
void		CopyMatrix44ToArray( f64*, const Matrix44& );

}	// namespace math
}	// namespace nk

#endif  // __MATRIX_H__
