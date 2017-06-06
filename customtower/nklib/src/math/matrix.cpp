//=============================================================================
/*!	@file	matrix.cpp

	@brief	行列関係

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <math.h>
#include "../../include/math/math.h"
#include "../../include/math/vector.h"
#include "../../include/math/matrix.h"

namespace nk {
namespace math {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	
*/
//===========================================================================
Matrix44::Matrix44()
{

	// 0クリア
// 	Clear();

	// 単位行列
	InitIdentityMatrix();

}







//===========================================================================
/*!	@brief	コンストラクタ
	@param	m1～m16	: セットする値
*/
//===========================================================================
Matrix44::Matrix44(f32 m1, f32 m2, f32 m3, f32 m4, 
				 f32 m5, f32 m6, f32 m7, f32 m8, 
				 f32 m9, f32 m10, f32 m11, f32 m12, 
				 f32 m13, f32 m14, f32 m15, f32 m16)
{
	matrix.ary16[0] = m1;
	matrix.ary16[1] = m2;
	matrix.ary16[2] = m3;
	matrix.ary16[3] = m4;
	matrix.ary16[4] = m5;
	matrix.ary16[5] = m6;
	matrix.ary16[6] = m7;
	matrix.ary16[7] = m8;
	matrix.ary16[8] = m9;
	matrix.ary16[9] = m10;
	matrix.ary16[10] = m11;
	matrix.ary16[11] = m12;
	matrix.ary16[12] = m13;
	matrix.ary16[13] = m14;
	matrix.ary16[14] = m15;
	matrix.ary16[15] = m16;
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	m	: 16個要素のあるf32配列の先頭アドレス
*/
//===========================================================================
Matrix44::Matrix44(f32* m)
{
	matrix.ary16[0] = m[0];
	matrix.ary16[1] = m[1];
	matrix.ary16[2] = m[2];
	matrix.ary16[3] = m[3];
	matrix.ary16[4] = m[4];
	matrix.ary16[5] = m[5];
	matrix.ary16[6] = m[6];
	matrix.ary16[7] = m[7];
	matrix.ary16[8] = m[8];
	matrix.ary16[9] = m[9];
	matrix.ary16[10] = m[10];
	matrix.ary16[11] = m[11];
	matrix.ary16[12] = m[12];
	matrix.ary16[13] = m[13];
	matrix.ary16[14] = m[14];
	matrix.ary16[15] = m[15];
}

//===========================================================================
/*!	@brief	コピーコンストラクタ
	@param	data	: コピーを行う行列
*/
//===========================================================================
Matrix44::Matrix44(const Matrix44 &data)
{
	for(s32 i = 0; i < 16; i++) {
		matrix.ary16[i] = data.GetMatrix().ary16[i];
	}
				
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
Matrix44::~Matrix44()
{

}



//===========================================================================
/*!	@brief	行列をセット
	@param	mat	: セットする行列へのポインタ
	@return	なし
*/
//===========================================================================
void Matrix44::SetMatrix(f32 *mat)
{

	/* 入れ替え */
	for(s32 i = 0; i < MATRIX_MAX; i++) {
		matrix.ary16[i] = mat[i];
	}

}



//===========================================================================
/*!	@brief	要素をセット
	@param	row	: 行数
	@param	col	: 列数
	@param	num	: セットする値
	@return	なし
*/
//===========================================================================
void Matrix44::SetElement(s32 row, s32 col, f32 num)
{

	matrix.ary44[row][col] = num;

}


//===========================================================================
/*!	@brief	0クリア
	@param	なし
	@return	なし
*/
//===========================================================================
void Matrix44::Clear()
{

	for(s32 i = 0; i < MATRIX_MAX; i++) {
		matrix.ary16[i] = 0;
	}

}


//===========================================================================
/*!	@brief	単位行列に変換
	@param	なし
	@return	なし
*/
//===========================================================================
void Matrix44::InitIdentityMatrix()
{
	for(s32 i = 0; i < MATRIX_COL; i++) {
		for(s32 j = 0; j < MATRIX_ROW; j++) {
			if(i == j)	{ matrix.ary44[i][j] = 1.0f; }
			else		{ matrix.ary44[i][j] = 0.0f; }
		}
	}
}


//===========================================================================
/*!	@brief	
	@param	
	@return	
	\note	[検索]あとで編集する　誰かのソースに書いてあったからとりあえず書いただけ
*/
//===========================================================================
Vector Matrix44::ApplyMatrixXYZ(const Matrix44& m1, const Vector& v)
{
	Vector ans;

	#define M1_MAT m1.matrix.ary44
		ans.x =	M1_MAT[0][0] * v.x + M1_MAT[1][0] * v.y + M1_MAT[2][0] * v.z + M1_MAT[3][0];
		ans.y =	M1_MAT[0][1] * v.x + M1_MAT[1][1] * v.y + M1_MAT[2][1] * v.z + M1_MAT[3][1];
		ans.z =	M1_MAT[0][2] * v.x + M1_MAT[1][2] * v.y + M1_MAT[2][2] * v.z + M1_MAT[3][2];
	#undef M1_MAT

	return ans;
}


//===========================================================================
/*!	@brief	逆行列に変換
	@param	なし
	@return	なし
*/
//===========================================================================
void Matrix44::InverseMatrix()
{
#if 0
	Matrix44 ans;

	Matrix44 mTemp(*this);

	Vector vTemp;
	vTemp.SetVector(mTemp.matrix.ary44[3][0], mTemp.matrix.ary44[3][1], mTemp.matrix.ary44[3][2]);

	mTemp.SetElement(3, 0, 1.0f);
	mTemp.SetElement(3, 1, 1.0f);
	mTemp.SetElement(3, 2, 1.0f);
	
	ans = mTemp;
	ans.Transpose();
	
	mTemp.ApplyMatrixXYZ(*this, vTemp);
#else

	const s32 defaultRowCol = 4;	// 行列の初期行数と列数
	f32 mat[16];					// 途中式
	const f32 *m = matrix.ary16;	// 変数名の省略


	f32 inv_a[16];	//ここに逆行列が入る
	f32 buf;			//一時的なデータを蓄える
	s32 i, j, k;		//カウンタ
	s32 n = 4;			//配列の次数


	//	配列のコピー
	//---------------------------------------
	for(s32 i = 0; i < 16; i++) {
		mat[i] = m[i];
	}


	//	単位行列に変換
	//---------------------------------------
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			inv_a[i * 4 + j] = (i == j) ? 1.0f : 0.0f;
		}
	}


	//	掃き出し法
	//---------------------------------------
	for(i = 0; i < n; i++) {
		buf = 1.0f / mat[i * 4 + i];
		for(j = 0; j < n; j++) {
			mat[i * 4 + j] *= buf;
			inv_a[i * 4 + j] *= buf;
		}
		for(j = 0; j < n; j++) {
			if(i != j){
				buf = mat[j * 4 + i];
				for(k = 0; k < n; k++) {
					mat[j * 4 + k] -= mat[i * 4 + k] * buf;
					inv_a[j * 4 + k] -= inv_a[i * 4 + k] * buf;
				}
			}
		}
	}
	SetMatrix(inv_a);
#endif


}


#if 0


//========================================================================
//	クラス：Matrix44
//	内　容：カメラ行列に変換
//	引　数：camera : カメラクラス
//	戻り値：
//	 memo ：
//========================================================================
//void Matrix44::TransformCameraMatrix(CCamera camera)
//{
//	Vector F = camera.GetLook() - camera.GetPos();
//	F.Normalize();
//	
//	Vector camUp(camera.GetTop());
//	camUp.Normalize();
//
//	Vector S = CalcCrossProduct(&F, &camUp);
//	S.Normalize();
//
//	Vector U = CalcCrossProduct(&S, &F);
//	U.Normalize();
//
//	Matrix44 ret(
//		S.x, S.y, S.z, 0.0f,
//		U.x, U.y, U.z, 0.0f,
//		-F.x,-F.y,-F.z, 0.0f,
//		0, 0, 0, 1.0f);
//
//	Matrix44 trans(
//		1, 0, 0, -camera.GetPos().x,
//		0, 1, 0, -camera.GetPos().y,
//		0, 0, 1, -camera.GetPos().z,
//		0, 0, 0, 1);
//
//
//	ret = ret * trans;
//
//
//	SetMatrix(ret.GetMatrix());
//}



//========================================================================
//	クラス：Matrix44
//	内　容：カメラ行列に変換
//	引　数：pos		: 位置
//			look	: 向き
//			top		: 上方向
//	戻り値：
//	 memo ：
//========================================================================
void Matrix44::TransformCameraMatrix(const Vector &pos, const Vector &look, const Vector &top)
{
	Vector F(look - pos);
	F.Normalize();
	
	Vector camUp(top);
	camUp.Normalize();

	Vector S = CalcCrossProduct(&F, &camUp);
	S.Normalize();

	Vector U = CalcCrossProduct(&S, &F);
	U.Normalize();

	Matrix44 ret(
		S.x, S.y, S.z, 0.0f,
		U.x, U.y, U.z, 0.0f,
		-F.x,-F.y,-F.z, 0.0f,
		0, 0, 0, 1.0f);

	Matrix44 trans(
		1, 0, 0, -pos.x,
		0, 1, 0, -pos.y,
		0, 0, 1, -pos.z,
		0, 0, 0, 1);


	ret = ret * trans;


	SetMatrix(ret.GetMatrix().ary16);
}
#endif




//===========================================================================
/*!	@brief	平行移動成分をクリア
	@param	なし
	@return	なし
*/
//===========================================================================
void Matrix44::ClearMoveComponent()
{

	matrix.ary16[12] = matrix.ary16[13] = matrix.ary16[14] = 0.0f;

}



//===========================================================================
/*!	@brief	行と列を入れ替える
	@param	なし
	@return	なし
*/
//===========================================================================
void Matrix44::Transpose()
{
	f32 swap[MATRIX_MAX];


	for(s32 i = 0; i < MATRIX_COL; i++) {
		for(s32 j = 0; j < MATRIX_ROW; j++) {
			swap[j * MATRIX_COL + i] = matrix.ary16[i * MATRIX_COL + j];
		}
	}

	SetMatrix(swap);
}


#if 0

//========================================================================
//	クラス：Matrix44
//	内　容：GLに行列をセット
//	引　数：model : キャラのモデル変換行列
//	戻り値：
//	 memo ：
//========================================================================
void Matrix44::SetGL(const Matrix44 *model)
{
	Matrix44 model_view;




	glMatrixMode(GL_MODELVIEW);


	/* モデルビュー変換 */
	model_view = (*this) * (*model);
	

	/* 行と列を入れ替え */
	//model_view.Transpose();



	glLoadMatrixf(model_view.GetMatrix().ary16);

}



//========================================================================
//	クラス：Matrix44
//	内　容：GLに行列をセット
//	引　数：view  : ビュー変換行列
//			model : キャラのモデル変換行列
//	戻り値：
//	 memo ：
//========================================================================
void SetGL(const Matrix44 *_view, const Matrix44 *_model)
{
	Matrix44 view;
	Matrix44 model;
	Matrix44 model_view;


	view.SetMatrix(_view->GetMatrix().ary16);
	model.SetMatrix(_model->GetMatrix().ary16);

	glMatrixMode(GL_MODELVIEW);



	/* モデルビュー変換 */
	model_view = view * model;
	

	/* 行と列を入れ替え */
	//model_view.Transpose();	@@@


	glLoadMatrixf(model_view.GetMatrix().ary16);
}


#endif


//===========================================================================
/*!	@brief	演算子のオーバーロード
	@param	mat:足す行列
	@return	結果
*/
//===========================================================================
Matrix44 Matrix44::operator +(const Matrix44 &mat) const
{

	/* 計算結果を格納 */
	MatrixAry sum;


	/* 計算 */
	for(s32 i = 0; i < MATRIX_COL; i++) {
		for(s32 j = 0; j < MATRIX_ROW; j++) {
			sum.ary44[i][j] = matrix.ary44[i][j] + mat.GetMatrix().ary44[i][j];
		}
	}

	Matrix44 ans;
	ans.SetMatrix(sum.ary16);


	return ans;
}




//===========================================================================
/*!	@brief	*演算子のオーバーロード
	@param	vec	: 掛ける行列
	@return	結果
*/
//===========================================================================
Vector Matrix44::operator *(const Vector &vector) const
{
	f32 ans[4] = { 0 };

	ans[0]	=	matrix.ary44[0][0] * vector.x + matrix.ary44[1][0] * vector.y + matrix.ary44[2][0] * vector.z;// + matrix.ary44[3][0] * vector.w;
	ans[1]	=	matrix.ary44[0][1] * vector.x + matrix.ary44[1][1] * vector.y + matrix.ary44[2][1] * vector.z;// + matrix.ary44[3][1] * vector.w;
	ans[2]	=	matrix.ary44[0][2] * vector.x + matrix.ary44[1][2] * vector.y + matrix.ary44[2][2] * vector.z;// + matrix.ary44[3][2] * vector.w;
	ans[3]	=	matrix.ary44[0][3] * vector.x + matrix.ary44[1][3] * vector.y + matrix.ary44[2][3] * vector.z;// + matrix.ary44[3][3] * vector.w;


	return Vector(ans[0], ans[1], ans[2], ans[3]);
}





//===========================================================================
/*!	@brief	*演算子のオーバーロード
	@param	mat	: 掛ける行列
	@return	結果
*/
//===========================================================================
Matrix44 Matrix44::operator *(const Matrix44 &mat) const
{
	Matrix44 ans;
	ans.Clear();


	#define MAT1 this->matrix.ary44
	#define MAT2 mat.matrix.ary44

	ans.matrix.ary44[0][0]	=	MAT1[0][0] * MAT2[0][0] + MAT1[1][0] * MAT2[0][1] + MAT1[2][0] * MAT2[0][2] + MAT1[3][0] * MAT2[0][3];
	ans.matrix.ary44[0][1]	=	MAT1[0][1] * MAT2[0][0] + MAT1[1][1] * MAT2[0][1] + MAT1[2][1] * MAT2[0][2] + MAT1[3][1] * MAT2[0][3];
	ans.matrix.ary44[0][2]	=	MAT1[0][2] * MAT2[0][0] + MAT1[1][2] * MAT2[0][1] + MAT1[2][2] * MAT2[0][2] + MAT1[3][2] * MAT2[0][3];
	ans.matrix.ary44[0][3]	=	MAT1[0][3] * MAT2[0][0] + MAT1[1][3] * MAT2[0][1] + MAT1[2][3] * MAT2[0][2] + MAT1[3][3] * MAT2[0][3];

	ans.matrix.ary44[1][0]	=	MAT1[0][0] * MAT2[1][0] + MAT1[1][0] * MAT2[1][1] + MAT1[2][0] * MAT2[1][2] + MAT1[3][0] * MAT2[1][3];
	ans.matrix.ary44[1][1]	=	MAT1[0][1] * MAT2[1][0] + MAT1[1][1] * MAT2[1][1] + MAT1[2][1] * MAT2[1][2] + MAT1[3][1] * MAT2[1][3];
	ans.matrix.ary44[1][2]	=	MAT1[0][2] * MAT2[1][0] + MAT1[1][2] * MAT2[1][1] + MAT1[2][2] * MAT2[1][2] + MAT1[3][2] * MAT2[1][3];
	ans.matrix.ary44[1][3]	=	MAT1[0][3] * MAT2[1][0] + MAT1[1][3] * MAT2[1][1] + MAT1[2][3] * MAT2[1][2] + MAT1[3][3] * MAT2[1][3];
																									 
	ans.matrix.ary44[2][0]	=	MAT1[0][0] * MAT2[2][0] + MAT1[1][0] * MAT2[2][1] + MAT1[2][0] * MAT2[2][2] + MAT1[3][0] * MAT2[2][3];
	ans.matrix.ary44[2][1]	=	MAT1[0][1] * MAT2[2][0] + MAT1[1][1] * MAT2[2][1] + MAT1[2][1] * MAT2[2][2] + MAT1[3][1] * MAT2[2][3];
	ans.matrix.ary44[2][2]	=	MAT1[0][2] * MAT2[2][0] + MAT1[1][2] * MAT2[2][1] + MAT1[2][2] * MAT2[2][2] + MAT1[3][2] * MAT2[2][3];
	ans.matrix.ary44[2][3]	=	MAT1[0][3] * MAT2[2][0] + MAT1[1][3] * MAT2[2][1] + MAT1[2][3] * MAT2[2][2] + MAT1[3][3] * MAT2[2][3];
																									 
	ans.matrix.ary44[3][0]	=	MAT1[0][0] * MAT2[3][0] + MAT1[1][0] * MAT2[3][1] + MAT1[2][0] * MAT2[3][2] + MAT1[3][0] * MAT2[3][3];
	ans.matrix.ary44[3][1]	=	MAT1[0][1] * MAT2[3][0] + MAT1[1][1] * MAT2[3][1] + MAT1[2][1] * MAT2[3][2] + MAT1[3][1] * MAT2[3][3];
	ans.matrix.ary44[3][2]	=	MAT1[0][2] * MAT2[3][0] + MAT1[1][2] * MAT2[3][1] + MAT1[2][2] * MAT2[3][2] + MAT1[3][2] * MAT2[3][3];
	ans.matrix.ary44[3][3]	=	MAT1[0][3] * MAT2[3][0] + MAT1[1][3] * MAT2[3][1] + MAT1[2][3] * MAT2[3][2] + MAT1[3][3] * MAT2[3][3];

	#undef MAT1
	#undef MAT2

	return ans;
}



//===========================================================================
/*!	@brief	*=演算子のオーバーロード
	@param	mat	: 掛け合わせる行列
	@return	
*/
//===========================================================================
void Matrix44::operator *=(const Matrix44 &mat)
{
	Matrix44 temp(*this);

	this->matrix.ary44[0][0]	=	temp.matrix.ary44[0][0] * mat.matrix.ary44[0][0] + temp.matrix.ary44[1][0] * mat.matrix.ary44[0][1] + temp.matrix.ary44[2][0] * mat.matrix.ary44[0][2] + temp.matrix.ary44[3][0] * mat.matrix.ary44[0][3];
	this->matrix.ary44[0][1]	=	temp.matrix.ary44[0][1] * mat.matrix.ary44[0][0] + temp.matrix.ary44[1][1] * mat.matrix.ary44[0][1] + temp.matrix.ary44[2][1] * mat.matrix.ary44[0][2] + temp.matrix.ary44[3][1] * mat.matrix.ary44[0][3];
	this->matrix.ary44[0][2]	=	temp.matrix.ary44[0][2] * mat.matrix.ary44[0][0] + temp.matrix.ary44[1][2] * mat.matrix.ary44[0][1] + temp.matrix.ary44[2][2] * mat.matrix.ary44[0][2] + temp.matrix.ary44[3][2] * mat.matrix.ary44[0][3];
	this->matrix.ary44[0][3]	=	temp.matrix.ary44[0][3] * mat.matrix.ary44[0][0] + temp.matrix.ary44[1][3] * mat.matrix.ary44[0][1] + temp.matrix.ary44[2][3] * mat.matrix.ary44[0][2] + temp.matrix.ary44[3][3] * mat.matrix.ary44[0][3];

	this->matrix.ary44[1][0]	=	temp.matrix.ary44[0][0] * mat.matrix.ary44[1][0] + temp.matrix.ary44[1][0] * mat.matrix.ary44[1][1] + temp.matrix.ary44[2][0] * mat.matrix.ary44[1][2] + temp.matrix.ary44[3][0] * mat.matrix.ary44[1][3];
	this->matrix.ary44[1][1]	=	temp.matrix.ary44[0][1] * mat.matrix.ary44[1][0] + temp.matrix.ary44[1][1] * mat.matrix.ary44[1][1] + temp.matrix.ary44[2][1] * mat.matrix.ary44[1][2] + temp.matrix.ary44[3][1] * mat.matrix.ary44[1][3];
	this->matrix.ary44[1][2]	=	temp.matrix.ary44[0][2] * mat.matrix.ary44[1][0] + temp.matrix.ary44[1][2] * mat.matrix.ary44[1][1] + temp.matrix.ary44[2][2] * mat.matrix.ary44[1][2] + temp.matrix.ary44[3][2] * mat.matrix.ary44[1][3];
	this->matrix.ary44[1][3]	=	temp.matrix.ary44[0][3] * mat.matrix.ary44[1][0] + temp.matrix.ary44[1][3] * mat.matrix.ary44[1][1] + temp.matrix.ary44[2][3] * mat.matrix.ary44[1][2] + temp.matrix.ary44[3][3] * mat.matrix.ary44[1][3];
																									 
	this->matrix.ary44[2][0]	=	temp.matrix.ary44[0][0] * mat.matrix.ary44[2][0] + temp.matrix.ary44[1][0] * mat.matrix.ary44[2][1] + temp.matrix.ary44[2][0] * mat.matrix.ary44[2][2] + temp.matrix.ary44[3][0] * mat.matrix.ary44[2][3];
	this->matrix.ary44[2][1]	=	temp.matrix.ary44[0][1] * mat.matrix.ary44[2][0] + temp.matrix.ary44[1][1] * mat.matrix.ary44[2][1] + temp.matrix.ary44[2][1] * mat.matrix.ary44[2][2] + temp.matrix.ary44[3][1] * mat.matrix.ary44[2][3];
	this->matrix.ary44[2][2]	=	temp.matrix.ary44[0][2] * mat.matrix.ary44[2][0] + temp.matrix.ary44[1][2] * mat.matrix.ary44[2][1] + temp.matrix.ary44[2][2] * mat.matrix.ary44[2][2] + temp.matrix.ary44[3][2] * mat.matrix.ary44[2][3];
	this->matrix.ary44[2][3]	=	temp.matrix.ary44[0][3] * mat.matrix.ary44[2][0] + temp.matrix.ary44[1][3] * mat.matrix.ary44[2][1] + temp.matrix.ary44[2][3] * mat.matrix.ary44[2][2] + temp.matrix.ary44[3][3] * mat.matrix.ary44[2][3];
																									 
	this->matrix.ary44[3][0]	=	temp.matrix.ary44[0][0] * mat.matrix.ary44[3][0] + temp.matrix.ary44[1][0] * mat.matrix.ary44[3][1] + temp.matrix.ary44[2][0] * mat.matrix.ary44[3][2] + temp.matrix.ary44[3][0] * mat.matrix.ary44[3][3];
	this->matrix.ary44[3][1]	=	temp.matrix.ary44[0][1] * mat.matrix.ary44[3][0] + temp.matrix.ary44[1][1] * mat.matrix.ary44[3][1] + temp.matrix.ary44[2][1] * mat.matrix.ary44[3][2] + temp.matrix.ary44[3][1] * mat.matrix.ary44[3][3];
	this->matrix.ary44[3][2]	=	temp.matrix.ary44[0][2] * mat.matrix.ary44[3][0] + temp.matrix.ary44[1][2] * mat.matrix.ary44[3][1] + temp.matrix.ary44[2][2] * mat.matrix.ary44[3][2] + temp.matrix.ary44[3][2] * mat.matrix.ary44[3][3];
	this->matrix.ary44[3][3]	=	temp.matrix.ary44[0][3] * mat.matrix.ary44[3][0] + temp.matrix.ary44[1][3] * mat.matrix.ary44[3][1] + temp.matrix.ary44[2][3] * mat.matrix.ary44[3][2] + temp.matrix.ary44[3][3] * mat.matrix.ary44[3][3];

}




//===========================================================================
/*!	@brief	=演算子オーバーロード
	@param	mat	: 代入を行う行列
	@return	*this
*/
//===========================================================================
Matrix44& Matrix44::operator =(const Matrix44& mat)
{
	for(s32 i = 0; i < MATRIX_MAX; i++) {
		matrix.ary16[i] = mat.GetMatrix().ary16[i];
	}

	return *this;
}



//===========================================================================
/*!	@brief	行列をコンソールに表示
	@param	なし
	@return	なし
*/
//===========================================================================
void Matrix44::Disp()
{
	PRINTF("Matrix44 ( %p )\n", this);

	for(s32 i = 0; i < MATRIX_COL; i++) {
		for(s32 j = 0; j < MATRIX_ROW; j++) {
			PRINTF("%f\t", matrix.ary44[i][j]);
		}
		PRINTF("\n");
	}

}




//===========================================================================
/*!	@brief	X軸成分を取得
	@param	なし
	@return	X軸成分
*/
//===========================================================================
Vector Matrix44::GetXAxis() const
{

	return Vector(matrix.ary16[0], matrix.ary16[1], matrix.ary16[2]);
}




//===========================================================================
/*!	@brief	Y軸成分を取得
	@param	なし
	@return	Y軸成分
*/
//===========================================================================
Vector Matrix44::GetYAxis() const
{

	return Vector(matrix.ary16[4], matrix.ary16[5], matrix.ary16[6]);
}




//===========================================================================
/*!	@brief	Z軸成分を取得
	@param	なし
	@return	Z軸成分
*/
//===========================================================================
Vector Matrix44::GetZAxis() const
{

	return Vector(matrix.ary16[8], matrix.ary16[9], matrix.ary16[10]);	
}



//===========================================================================
/*!	@brief	平行移動成分を取得
	@param	なし
	@return	平行移動成分
*/
//===========================================================================
Vector Matrix44::GetParallel() const
{

	return Vector(matrix.ary16[12], matrix.ary16[13], matrix.ary16[14]);
}


//===========================================================================
/*!	@brief	拡大行列を生成
	@param	x,y,z:各軸に対しての拡大率
	@return	生成した行列
*/
//===========================================================================
Matrix44 Expansion(f32 x, f32 y, f32 z)
{
	Matrix44 trans(
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1);

	return trans;
}


//===========================================================================
/*!	@brief	拡大行列を生成
	@param	rate	: 拡大率
	@return	生成した行列
*/
//===========================================================================
Matrix44 Expansion(f32 rate)
{

	return Expansion(rate, rate, rate);
}



//===========================================================================
/*!	@brief	X軸回転行列を生成
	@param	theta	: 回転角度(ラジアン角)
	@return	生成した行列
*/
//===========================================================================
Matrix44 RotateX(f32 theta)
{
	f32 cos_theta = cos(theta);
	f32 sin_theta = sin(theta);
	
	Matrix44 trans(
		1,	0,			0,			0,
		0,	cos_theta,	sin_theta,	0,
		0,	-sin_theta,	cos_theta,	0,
		0,	0,			0,			1);


	return trans;
}



//===========================================================================
/*!	@brief	Y軸回転行列を生成
	@param	theta	: 回転角度(ラジアン角)
	@return	生成した行列
*/
//===========================================================================
Matrix44 RotateY(f32 theta)
{
	f32 cos_theta = cos(theta);
	f32 sin_theta = sin(theta);

	Matrix44 trans(
		cos_theta,	0,		-sin_theta,	0,
		0,			1,		0,			0,
		sin_theta,	0,		cos_theta,	0,
		0,			0,		0,			1);


	return trans;
}


//===========================================================================
/*!	@brief	Z軸回転行列を生成
	@param	theta	: 回転角度(ラジアン角)
	@return	生成した行列
*/
//===========================================================================
Matrix44 RotateZ(f32 theta)
{
	f32 cos_theta = cos(theta);
	f32 sin_theta = sin(theta);

	Matrix44 trans(
		cos_theta,	sin_theta,	0,		0,
		-sin_theta,	cos_theta,	0,		0,
		0,			0,			1,		0,
		0,			0,			0,		1);

	return trans;
}


//===========================================================================
/*!	@brief	任意の軸に対する回転行列を生成
	@param	theta	: 回転角度(ラジアン角)
	@param	vector	: 回転軸
	@return	生成した行列
*/
//===========================================================================
Matrix44 RotateAxis(f32 theta, const Vector *axis)
{
	f32 cos_theta = cos(theta), sin_theta = sin(theta);

	f32 cos1 = 1.0f - cos_theta;		// (1 - cosθ)
	f32 px = axis->x;
	f32 py = axis->y;
	f32 pz = axis->z;

	Matrix44 trans(
		cos1 * px * px + cos_theta,		 cos1 * px * py + pz * sin_theta, cos1 * pz * px - py * sin_theta, 0,
		cos1 * px * py - pz * sin_theta, cos1 * py * py + cos_theta,	  cos1 * py * pz + px * sin_theta, 0,
		cos1 * pz * px + py * sin_theta, cos1 * py * pz - px * sin_theta, cos1 * pz * pz + cos_theta,	   0,
		0,								 0,								  0,							   1);


	return trans;
}


//===========================================================================
/*!	@brief	任意の軸に対する回転行列を生成
	@param	theta	: 回転角度(ラジアン角)
	@param	vector	: 回転軸
	@return	生成した行列
*/
//===========================================================================
Matrix44 RotateAxis(f32 theta, const Vector& axis)
{
	f32 cos_theta = cos(theta), sin_theta = sin(theta);

	f32 cos1 = 1.0f - cos_theta;		// (1 - cosθ)
	f32 px = axis.x;
	f32 py = axis.y;
	f32 pz = axis.z;


	Matrix44 trans(
		cos1 * px * px + cos_theta,		 cos1 * px * py + pz * sin_theta, cos1 * pz * px - py * sin_theta, 0,
		cos1 * px * py - pz * sin_theta, cos1 * py * py + cos_theta,	  cos1 * py * pz + px * sin_theta, 0,
		cos1 * pz * px + py * sin_theta, cos1 * py * pz - px * sin_theta, cos1 * pz * pz + cos_theta,	   0,
		0,								 0,								  0,							   1);

	return trans;
}




//===========================================================================
/*!	@brief	平行移動行列を生成
	@param	x,y,z:各軸に対する移動量
	@return	生成した行列
*/
//===========================================================================
Matrix44 Translation(f32 x, f32 y, f32 z)
{
	Matrix44 trans(
		1,	0,	0,	0,
		0,	1,	0,	0,
		0,	0,	1,	0,
		x,	y,	z,	1);


	return trans;
}



//===========================================================================
/*!	@brief	平行移動行列を生成
	@param	xyz:各軸に対する移動量ベクトル
	@return	生成した行列
*/
//===========================================================================
Matrix44 Translation(const Vector& xyz)
{
	Matrix44 result = Translation(xyz.x, xyz.y, xyz.z);

	return result;
}





//===========================================================================
/*!	@brief	射影行列を生成
	@param	fieldOfVision	: 見える角度
	@param	aspectRatio		: ウインドウのアスペクト比(w/h)
	@param	nearDistance	: 最小可視距離
	@param	farDistance		: 最大可視距離
	@return	生成した行列
*/
//===========================================================================
Matrix44 CreatePerspectiveFieldOfView(f64 fieldOfVision, f64 aspectRatio, f64 nearDistance, f64 farDistance)
{
	Matrix44 result;
	result.Clear();
	f64 rad = Rad(fieldOfVision);
	f64 y_scale = 1.0 / tan(rad * 0.5);			// 1/tan(x) == cos(x)
	f64 x_scale = y_scale / aspectRatio;	

	result.SetElement(0, 0, static_cast<f32>(x_scale));
	result.SetElement(1, 1, static_cast<f32>(y_scale));
	
	result.SetElement(2, 2, static_cast<f32>(farDistance / (nearDistance - farDistance)));
	//result.SetElement(2, 2, static_cast<f32>(farDistance / (farDistance - nearDistance)));	// ASURA版

	// これを逆にするとウインドウの(0,0)が上と下で変わる
	result.SetElement(2, 3, -1.0f);	
	//result.SetElement(2, 3, 1.0f);	
	
	result.SetElement(3, 2, static_cast<f32>((nearDistance * farDistance) / (nearDistance - farDistance)));
	//result.SetElement(3, 2, static_cast<f32>((-nearDistance * farDistance) / (farDistance - nearDistance)));

//透視射影変換行列生成
// http://www.xxxxx13.com/gles2_ViewProjection.html
//
//void HelperFunc::MatrixPerspectiveFovLH(MATRIX2 *p, f32 radian, f32 aspect, f32 zmin, f32 zmax){
//f32 ys=cot(radian / 2);
//f32 xs=ys / aspect;
//
//f32 w22=zmax / (zmax - zmin);
//f32 w32=-zmin * zmax / (zmax - zmin);
//
//p->m[0][0] = xs; p->m[0][1] = 0.0f; p->m[0][2] = 0.0f; p->m[0][3] = 0.0f;
//p->m[1][0] = 0.0f; p->m[1][1] = ys; p->m[1][2] = 0.0f; p->m[1][3] = 0.0f;
//p->m[2][0] = 0.0f; p->m[2][1] = 0.0f; p->m[2][2] = w22; p->m[2][3] = 1.0f;
//p->m[3][0] = 0.0f; p->m[3][1] = 0.0f; p->m[3][2] = w32; p->m[3][3] = 0.0f;
//}
#if 0
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(field_of_vision, aspect_ratio, near_distance, far_distance);
	glViewport(0, 0, SYSTEM->GetScreenWidth(), SYSTEM->GetScreenHeight());

	f32 temp.matrix.ary44[16];
	glGetFloatv(GL_PROJECTION_MATRIX, temp.matrix.ary44);
	result.SetMatrix(temp.matrix.ary44);

	glLoadIdentity();
	gluPerspective(50.0, aspect_ratio, 0.1, 1000.0);
	glViewport(0, 0, SYSTEM->GetScreenWidth(), SYSTEM->GetScreenHeight());
	glMatrixMode(GL_MODELVIEW);
#endif

	return result;
}




#if 0

//========================================================================
//	内　容：射影空間からテクスチャ空間に変換した行列を生成
//	引　数：view_angle		: どれだけ見えるかのアングル
//	　　　：aspect_ratio	: ウインドウのアスペクト比(w/h)
//　　　　：near_distance	: 近くの距離
//　　　　：far_distance	: 遠くの距離
//	戻り値：射影行列
//	 memo ：
//========================================================================
Matrix44 CreatePerspectiveToTextureSpace()
{

	f32 offset_x = 0.5f + ( 0.5f / SYSTEM->GetScreenWidth() );
	f32 offset_y = 0.5f + ( 0.5f / SYSTEM->GetScreenHeight() );

	//Matrix44 scale_bias(		@@@
	//	0.5f,		0.0f,		0.0f,		0.0f,
	//	0.0f,		0.5f,		0.0f,		0.0f,
	//	0.0f,		0.0f,		1.0f,		0.0f,
	//	offset_x,	offset_y,	0.0f,		1.0f
	//	);

	//scale_bias.Transpose();	@@@

	Matrix44 scale_bias(
		0.5f,		0.0f,		0.0f,		offset_x,
		0.0f,		0.5f,		0.0f,		offset_y,
		0.0f,		0.0f,		1.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		1.0f
		);

	return scale_bias;
}
#endif

//===========================================================================
/*!	@brief	行列を配列にコピー
	@param	cpy		: コピーされる配列
	@param	origin	: 元となる行列
	@return	なし
*/
//===========================================================================
void CopyMatrix44ToArray(f32* cpy, const Matrix44& origin)
{
	for(s32 i = 0; i < MATRIX_MAX; ++i) {
		cpy[i] = origin.GetMatrix().ary16[i];
	}

}


//===========================================================================
/*!	@brief	行列を配列にコピー
	@param	cpy		: コピーされる配列
	@param	origin	: 元となる行列
	@return	なし
*/
//===========================================================================
void CopyMatrix44ToArray(f64* cpy, const Matrix44& origin)
{
	for(s32 i = 0; i < MATRIX_MAX; ++i) {
		cpy[i] = origin.GetMatrix().ary16[i];
	}

}


//===========================================================================
/*!	@brief	テクスチャ空間に直す行列を習得
	@param	screenW	: 幅
	@param	screenH	: 高さ
	@return	生成した行列
*/
//===========================================================================
Matrix44 CreatePerspectiveToTextureSpace(f32 screenW, f32 screenH)
{

	f32 offsetX = 0.5f + ( 0.5f / screenW );
	f32 offsetY = 0.5f + ( 0.5f / screenH );


	math::Matrix44 scaleBias(
		0.5f,		0.0f,		0.0f,		offsetX,
		0.0f,		0.5f,		0.0f,		offsetY,
		0.0f,		0.0f,		1.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		1.0f
		);

	return scaleBias;
}


}	// namespace math
}	// namespace nk

