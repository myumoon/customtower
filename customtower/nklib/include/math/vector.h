//=============================================================================
/*!	@file	vector.h

	@brief	�x�N�g���֌W

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __VECTOR_H__
#define __VECTOR_H__

//-------------------------------�C���N���[�h-------------------------------
#include <stdio.h>
#include <iostream>
#include "../typedef.h"
#include "../general.h"
#include "./expOperator.h"


namespace nk {
namespace math {

//-----------------------------------------------
//	�O���錾
//-----------------------------------------------
class Matrix44;


//=============================================================================
/*!
                              �x�N�g���N���X
*/
//=============================================================================
//template<class T = f32>
class Vector {
public:
	//----------------------�����o�ϐ�-----------------------
	union {
		f32	v[4];

		struct {
			f32	x, y, z, w;
		};
	};


	//-----------------------���\�b�h------------------------

	//!	�l�̃Z�b�g
	void SetVector( f32 x, f32 y, f32 z = 0.0f, f32 w = 0.0f );
	void SetVector( const Vector& );	

	//! 0�N���A
	void Clear();

	//! ���K��
	void Normalize();

	//! ���K�������x�N�g�����擾
	Vector GetNormalizeVec( void ) const;

	//! �x�N�g�����t�ɂ���
	void Inversion();

	//! �m�������擾
	f32 GetNorm() const;

	//! �m�����̓����擾
	f32 GetNorm2() const;

	//! �[���x�N�g�����ǂ����`�F�b�N
	bool IsVectorZero( void ) const;

	//! �\��
	void Disp() const { PRINTF("x = %f, y = %f, z = %f, w = %f, norm = %f\n", x, y, z, w, GetNorm()); }

	//! �A�N�Z�X
	f32	operator[]( std::size_t i ) const {
		ASSERT( i < 4, "error" );
		return v[i];
	}

	//! ���Z�q
	template<class T>
	Vector&							operator =	( const T& rhs )
	{
		for( std::size_t i = 0; i < 4; ++i ) {
			v[i]	= rhs[i];
		}
		return *this;
	}
	
	Exp<Vector, OpPlus, Vector>		operator +	( const Vector& rhs ) const;
	Exp<Vector, OpMinus, Vector>	operator -	( const Vector& rhs ) const;
	//Exp<Vector, OpMul, Vector>		operator *	( f32 &rhs ) const;
	//Exp<Vector, OpDiv, Vector>		operator /	( f32 &rha ) const;

	//Vector  						operator +	( const Vector &vec ) const;
	Vector&							operator +=	( const Vector &vec );
	Vector& 						operator +=	( f32 a				);
	Vector  						operator -	(					) const;
	//Vector  						operator -	( const Vector &vec ) const;
	Vector& 						operator -=	( const Vector &vec );
	Vector& 						operator -=	( f32 a				);
	Vector  						operator *	( f32 scalar		) const;
	Vector& 						operator *=	( f32 scalar		);
	Vector  						operator *	( const Matrix44 &	) const;
	Vector  						operator /	( f32 scalar		) const;
	Vector&							operator /=	( f32 scalar		);
	bool							operator ==	( const Vector &vec ) const;
	bool							operator !=	( const Vector &vec ) const;
	
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	Vector( f32 x = 0.0f, f32 y = 0.0f, f32 z = 0.0f, f32 w = 0.0f );	//!< �R���X�g���N�^
	Vector( const Vector & );											//!< �R�s�[�R���X�g���N�^
	
	template<class T>
	Vector( const T& rhs )
	{
		(*this).operator=( rhs );
	}
	virtual~Vector();															//!< �f�X�g���N�^
};


/* �x�N�g���̂Ȃ��p */
f32		CalcVectorAngle( const Vector*, const Vector* );
f32		CalcVectorAngle( const Vector&, const Vector& );

/* �x�N�g���̓��� */
f32		CalcDotProduct( const Vector*, const Vector* );
f32		CalcDotProduct( const Vector&, const Vector& );

/* �x�N�g���̊O�� */
Vector	CalcCrossProduct( const Vector*, const Vector* );
Vector	CalcCrossProduct( const Vector&, const Vector& );

/* �������S����v���邩 */
bool	IsSameDirection( const Vector&, const Vector& );

}	// namespace math
}	// namespace nk


#endif  // __VECTOR_H__