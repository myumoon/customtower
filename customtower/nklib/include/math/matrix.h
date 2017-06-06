//=============================================================================
/*!	@file	matrix.h

	@brief	行列関係

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __MATRIX_H__
#define __MATRIX_H__

//#include <math.h>
#include "../typedef.h"

namespace nk {
namespace math {


const s32 MATRIX_ROW = 4;			// 行
const s32 MATRIX_COL = 4;			// 列
const s32 MATRIX_MAX = MATRIX_ROW * MATRIX_COL;

//---------------------------------前方宣言---------------------------------
class Vector;

//----------------------------------共用体----------------------------------
/*! 行列を格納する型 */
union MatrixAry {
	f32 ary16[16];
	f32 ary44[4][4];
};



//=============================================================================
/*!
                     4x4行列クラス
*/
//=============================================================================
class Matrix44 {
public:

	//	コンストラクタ・デストラクタ
	//---------------------------------------
	Matrix44();
	Matrix44(
		f32, f32, f32, f32, 
		f32, f32, f32, f32, 
		f32, f32, f32, f32, 
		f32, f32, f32, f32
	);
			Matrix44( f32* );							// 16個要素があるf32配列をコピー
			Matrix44( const Matrix44 & );				// コピーコンストラクタ
	virtual~Matrix44();								// デストラクタ


	//	データのセット
	//---------------------------------------
	void Clear();				// 0で埋める
	void SetMatrix( f32 * );

	//	要素のセット
	//---------------------------------------
	void SetElement( s32 row, s32 col, f32 num );

	//	X軸成分を取得
	//---------------------------------------
	Vector GetXAxis() const;

	//	Y軸成分を取得
	//---------------------------------------
	Vector GetYAxis() const;

	//	Z軸成分を取得
	//---------------------------------------
	Vector GetZAxis() const;

	//	平行移動成分を取得
	//---------------------------------------
	Vector GetParallel() const;

	//	変換
	//---------------------------------------
	void	InitIdentityMatrix();			// 単位行列
	void	InverseMatrix();				// 逆行列
	Vector	ApplyMatrixXYZ( const Matrix44& m1, const Vector& v );

	//	平行移動成分をクリア
	//---------------------------------------
	void	ClearMoveComponent();

	//	行と列の入れ替え
	//---------------------------------------
	void	Transpose();	


	//	GLに行列をセット
	//---------------------------------------
	void		SetGL( const Matrix44 *model );
	friend void SetGL( const Matrix44 *_view, const Matrix44 *_model );


	//	データの取得	
	//---------------------------------------
	MatrixAry	GetMatrix() const { return matrix; }


	//	演算子のオーバーロード	
	//---------------------------------------
	Matrix44	operator +	(const Matrix44 &	) const;	//!< 行列＋行列
	Vector		operator *	(const Vector &		) const;	//!< 行列ｘベクトル
	Matrix44	operator *	(const Matrix44 &	) const;	//!< 行列ｘ行列
	void		operator *=	(const Matrix44 &	);			//!< 行列ｘ行列
	Matrix44&	operator =	(const Matrix44 &	);			//!< 代入

	//	表示
	//---------------------------------------
	void Disp();

private:
	MatrixAry		matrix;					// 4*4行列
};







//-----------------------------------------------
//	変換行列
//-----------------------------------------------
/* 平行移動 */
Matrix44	Translation( f32 x, f32 y, f32 z );
Matrix44	Translation( const Vector& xyz );

/* 拡大 */
Matrix44	Expansion( f32 x, f32 y, f32 z );

/* 均等に拡大 */
Matrix44	Expansion( f32 rate );

/* X軸回転 */
Matrix44	RotateX( f32 theta );

/* Y軸回転 */
Matrix44	RotateY( f32 theta );

/* Z軸回転 */
Matrix44	RotateZ( f32 theta );

/* 任意の軸で回転する変換行列を返す */
Matrix44	RotateAxis( f32 theta, const Vector *axis );
Matrix44	RotateAxis( f32 theta, const Vector& axis );

/* GLに行列をセット */
void		SetGL( const Matrix44*, const Matrix44* );

/* 射影行列を生成 */
Matrix44	CreatePerspectiveFieldOfView( f64 field_of_vision, f64 aspect_ratio, f64 near, f64 far );
Matrix44	CreatePerspectiveFieldOfView();


/* 射影空間からテクスチャ空間に変換した行列を生成 */
Matrix44	CreatePerspectiveToTextureSpace( f32 screenW, f32 screenH );

//! 行列を配列(16要素のf32配列)にコピー
void		CopyMatrix44ToArray( f32*, const Matrix44& );
void		CopyMatrix44ToArray( f64*, const Matrix44& );

}	// namespace math
}	// namespace nk

#endif  // __MATRIX_H__
