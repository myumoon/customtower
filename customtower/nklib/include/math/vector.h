//=============================================================================
/*!	@file	vector.h

	@brief	ベクトル関係

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __VECTOR_H__
#define __VECTOR_H__

//-------------------------------インクルード-------------------------------
#include <stdio.h>
#include <iostream>
#include "../typedef.h"
#include "../general.h"
#include "./expOperator.h"


namespace nk {
namespace math {

//-----------------------------------------------
//	前方宣言
//-----------------------------------------------
class Matrix44;


//=============================================================================
/*!
                              ベクトルクラス
*/
//=============================================================================
//template<class T = f32>
class Vector {
public:
	//----------------------メンバ変数-----------------------
	union {
		f32	v[4];

		struct {
			f32	x, y, z, w;
		};
	};


	//-----------------------メソッド------------------------

	//!	値のセット
	void SetVector( f32 x, f32 y, f32 z = 0.0f, f32 w = 0.0f );
	void SetVector( const Vector& );	

	//! 0クリア
	void Clear();

	//! 正規化
	void Normalize();

	//! 正規化したベクトルを取得
	Vector GetNormalizeVec( void ) const;

	//! ベクトルを逆にする
	void Inversion();

	//! ノルムを取得
	f32 GetNorm() const;

	//! ノルムの二乗を取得
	f32 GetNorm2() const;

	//! ゼロベクトルかどうかチェック
	bool IsVectorZero( void ) const;

	//! 表示
	void Disp() const { PRINTF("x = %f, y = %f, z = %f, w = %f, norm = %f\n", x, y, z, w, GetNorm()); }

	//! アクセス
	f32	operator[]( std::size_t i ) const {
		ASSERT( i < 4, "error" );
		return v[i];
	}

	//! 演算子
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
	
	//-------------コンストラクタ・デストラクタ--------------
	Vector( f32 x = 0.0f, f32 y = 0.0f, f32 z = 0.0f, f32 w = 0.0f );	//!< コンストラクタ
	Vector( const Vector & );											//!< コピーコンストラクタ
	
	template<class T>
	Vector( const T& rhs )
	{
		(*this).operator=( rhs );
	}
	virtual~Vector();															//!< デストラクタ
};


/* ベクトルのなす角 */
f32		CalcVectorAngle( const Vector*, const Vector* );
f32		CalcVectorAngle( const Vector&, const Vector& );

/* ベクトルの内積 */
f32		CalcDotProduct( const Vector*, const Vector* );
f32		CalcDotProduct( const Vector&, const Vector& );

/* ベクトルの外積 */
Vector	CalcCrossProduct( const Vector*, const Vector* );
Vector	CalcCrossProduct( const Vector&, const Vector& );

/* 符号が全部一致するか */
bool	IsSameDirection( const Vector&, const Vector& );

}	// namespace math
}	// namespace nk


#endif  // __VECTOR_H__