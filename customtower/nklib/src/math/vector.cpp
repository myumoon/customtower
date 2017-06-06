//=============================================================================
/*!	@file	vector.cpp

	@brief	ベクトル関係

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/math/vector.h"

#include <math.h>
#include "../../include/math/math.h"



namespace nk {
namespace math {

//===========================================================================
/*!	@brief	コンストラクタ
*/
//===========================================================================
Vector::Vector(f32 vx, f32 vy, f32 vz, f32 vw)
{
	x = vx;
	y = vy;
	z = vz;
	w = vw;
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	vec:初期化するベクトル
*/
//===========================================================================
Vector::Vector(const Vector &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}




//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
Vector::~Vector()
{

}



//===========================================================================
/*!	@brief	0クリア
	@param	なし
	@return	なし
*/
//===========================================================================
void Vector::Clear()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;

}


//===========================================================================
/*!	@brief	値をセット
	@param	vx,vy,vz:セットする値
	@return	なし
*/
//===========================================================================
void Vector::SetVector(f32 vx, f32 vy, f32 vz, f32 vw)
{
	x = vx;
	y = vy;
	z = vz;
	w = vw;
}


//===========================================================================
/*!	@brief	ベクトルをセット
	@param	v:セットするベクトル
	@return	なし
*/
//===========================================================================
void Vector::SetVector(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}


//===========================================================================
/*!	@brief	正規化
	@param	なし
	@return	なし
*/
//===========================================================================
void Vector::Normalize()
{
	
	if( IsVectorZero() ) {
		return;
	}

	const f32	norm	= GetNorm();	// ベクトルの大きさを求める

	x /= norm;
	y /= norm;
	z /= norm;
	w = 0.0f;
}



//===========================================================================
/*!	@brief	したベクトルを取得
	@param	なし
	@return	なし
*/
//===========================================================================
Vector Vector::GetNormalizeVec( void ) const
{
	
	if( IsVectorZero() ) {
		return Vector();
	}

	Vector	calcVec	= *this;
	const f32	norm	= calcVec.GetNorm();

	calcVec.x /= norm;
	calcVec.y /= norm;
	calcVec.z /= norm;
	calcVec.w = 0.0f;

	return calcVec;
}


//===========================================================================
/*!	@brief	ノルムを取得
	@param	なし
	@return	ノルム
*/
//===========================================================================
f32 Vector::GetNorm() const
{

	return sqrt(x * x + y * y + z * z);
}


//===========================================================================
/*!	@brief	ノルムの2乗を取得
	@param	なし
	@return	ノルムの2乗
*/
//===========================================================================
f32 Vector::GetNorm2() const
{

	return x * x + y * y + z * z;
}



//===========================================================================
/*!	@brief	ベクトルの符号を逆にする
	@param	なし
	@return	なし
*/
//===========================================================================
void Vector::Inversion()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
	w *= -1.0f;
}


//===========================================================================
/*!	@brief	ゼロベクトルかどうかを判断
	@param	
	@return	
*/
//===========================================================================
bool Vector::IsVectorZero( void ) const
{
	const f32	errorRange	= 0.000000f;	// 誤差
	
	return	((-errorRange <= x) && (x <= errorRange)) &&
			((-errorRange <= y) && (y <= errorRange)) &&
			((-errorRange <= z) && (z <= errorRange)) &&
			((-errorRange <= w) && (w <= errorRange));
}


//===========================================================================
/*!	@brief	+演算子のオーバーロード
	@param	rhs		ベクトル
	@return	演算
*/
//===========================================================================
Exp<Vector, OpPlus, Vector> Vector::operator+( const Vector& rhs ) const
{
	return Exp<Vector, OpPlus, Vector>( *this, rhs );
}


//===========================================================================
/*!	@brief	-演算子のオーバーロード
	@param	rhs		ベクトル
	@return	演算
*/
//===========================================================================
Exp<Vector, OpMinus, Vector> Vector::operator-( const Vector& rhs ) const
{
	return Exp<Vector, OpMinus, Vector>( *this, rhs );
}


//===========================================================================
/*!	@brief	*演算子のオーバーロード
	@param	rhs		スカラー値
	@return	演算
*/
//===========================================================================
// Exp<Vector, OpMul, Vector> Vector::operator*( f32 rhs ) const
// {
// 	return Exp<Vector, OpMul, Vector>( *this, nk::math::Vector( rhs, rhs, rhs ) );
// }
	
//===========================================================================
/*!	@brief	+演算子のオーバーロード
	@param	vec:足すベクトル
	@return	足した結果
*/
//===========================================================================
//Vector Vector::operator +(const Vector &vec) const
//{
//	return Vector(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
//}



//===========================================================================
/*!	@brief	+=演算子のオーバーロード
	@param	vec:加えるベクトル
	@return	足した結果
*/
//===========================================================================
Vector& Vector::operator +=(const Vector &vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;

	return (*this);
}



//===========================================================================
/*!	@brief	+=演算子のオーバーロード
	@param	a:足す値
	@return	足した結果
*/
//===========================================================================
Vector& Vector::operator +=(f32 a)
{
	x += a;
	y += a;
	z += a;
	w += a;

	return *this;
}



//===========================================================================
/*!	@brief	単項-演算子のオーバーロード
	@param	なし
	@return	結果
*/
//===========================================================================
Vector Vector::operator -() const
{
	return Vector(-x, -y, -z, -w);


}

//===========================================================================
/*!	@brief	-演算子のオーバーロード
	@param	vec:引くベクトル
	@return	引いた結果
*/
//===========================================================================
// Vector Vector::operator -(const Vector &vec) const
// {
// 	return ( Vector(x - vec.x, y - vec.y, z - vec.z, w - vec.w) );
// }




//===========================================================================
/*!	@brief	-=演算子のオーバーロード
	@param	vec:引くベクトル
	@return	引いた結果
*/
//===========================================================================
Vector& Vector::operator -=(const Vector &vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;

	return (*this);
}



//===========================================================================
/*!	@brief	-=演算子のオーバーロード
	@param	a:引く値
	@return	引いた結果
*/
//===========================================================================
Vector& Vector::operator -=(f32 a)
{
	x -= a;
	y -= a;
	z -= a;
	w -= a;

	return *this;
}


//===========================================================================
/*!	@brief	*演算子のオーバーロード
	@param	num:掛ける値
	@return	掛けた結果
*/
//===========================================================================
Vector Vector::operator *(f32 num) const
{
	return Vector(x * num, y * num, z * num, w * num);
}


//===========================================================================
/*!	@brief	*=演算子のオーバーロード
	@param	num:掛ける値
	@return	掛けた結果
*/
//===========================================================================
Vector &Vector::operator *=(f32 num)
{
	x *= num;
	y *= num;
	z *= num;
	w *= num;

	return *this;
}


//===========================================================================
/*!	@brief	/演算子のオーバーロード
	@param	scalar:割る値
	@return	割った結果
*/
//===========================================================================
Vector Vector::operator /(f32 scalar) const
{

	return Vector(x / scalar, y / scalar, z / scalar, w / scalar);
}


//===========================================================================
/*!	@brief	/=演算子のオーバーロード
	@param	scalar:割る値
	@return	割った結果
*/
//===========================================================================
Vector &Vector::operator /=(f32 scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}


//===========================================================================
/*!	@brief	ベクトルの比較
	@param	vec:比較するベクトル
	@return	true:一致	false:不一致
	\note	0.001の誤差は一致とする
*/
//===========================================================================
bool Vector::operator ==(const Vector &vec) const
{

	return (x - 0.001 < vec.x && vec.x < x + 0.001) && (y - 0.001 < vec.y && vec.y < y + 0.001) && (z - 0.001 < vec.z && vec.z < z + 0.001);
}


//===========================================================================
/*!	@brief	ベクトルの比較
	@param	vec:比較するベクトル
	@return	true:一致	false:不一致
	\note	0.001の誤差は一致とする
*/
//===========================================================================
bool Vector::operator !=(const Vector &vec) const
{

	return !((x - 0.001 < vec.x && vec.x < x + 0.001) && (y - 0.001 < vec.y && vec.y < y + 0.001) && (z - 0.001 < vec.z && vec.z < z + 0.001));
}


//===========================================================================
/*!	@brief	内積を計算
	@param	vec1,vec2:ベクトル
	@return	結果
*/
//===========================================================================
f32 CalcDotProduct(const Vector *vec1, const Vector *vec2)
{

	return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}


//===========================================================================
/*!	@brief	内積を計算
	@param	vec1,vec2:ベクトル
	@return	結果
*/
//===========================================================================
f32 CalcDotProduct(const Vector& vec1, const Vector& vec2)
{

	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}



//===========================================================================
/*!	@brief	ベクトルの外積を計算
	@param	vec1,vec2:ベクトル
	@return	２ベクトルに垂直でノルムが|vec1||vec2|sinθのベクトル
	\note	ノルムは計算しない
*/
//===========================================================================
Vector CalcCrossProduct(const Vector *vec1, const Vector *vec2)
{
	Vector vec1_cpy(*vec1);
	Vector vec2_cpy(*vec2);
	Vector closs_product;		// 外積


	/* 零ベクトルの場合 */
	if(vec1_cpy.IsVectorZero() || vec2_cpy.IsVectorZero()) {
		closs_product.SetVector(0.0, 0.0, 0.0);
		return closs_product;
	}



	//			外積の計算
	//	(y1*z2-z1y2, z1*x2-x1*z2, x1*y2-y1*x2)
	//	ノルムは |v1||v2|sinθ
	//	向きは座標系により異なる
	closs_product.x = vec1_cpy.y * vec2_cpy.z - vec1_cpy.z * vec2_cpy.y;
	closs_product.y = vec1_cpy.z * vec2_cpy.x - vec1_cpy.x * vec2_cpy.z;
	closs_product.z = vec1_cpy.x * vec2_cpy.y - vec1_cpy.y * vec2_cpy.x;

	//closs_product.CalcNorm();


	return closs_product;
}




//===========================================================================
/*!	@brief	ベクトルの外積を計算
	@param	vec1,vec2:ベクトル
	@return	２ベクトルに垂直でノルムが|vec1||vec2|sinθのベクトル
	\note	ノルムは計算しない
*/
//===========================================================================
Vector CalcCrossProduct(const Vector& vec1, const Vector& vec2)
{
	Vector vec1_cpy(vec1);
	Vector vec2_cpy(vec2);
	Vector closs_product;		// 外積


	/* 零ベクトルの場合 */
	if(vec1_cpy.IsVectorZero() || vec2_cpy.IsVectorZero()) {
		closs_product.SetVector(0.0, 0.0, 0.0);
		return closs_product;
	}



	//			外積の計算
	//	(y1*z2-z1y2, z1*x2-x1*z2, x1*y2-y1*x2)
	//	ノルムは |v1||v2|sinθ
	//	向きは座標系により異なる
	closs_product.x = vec1_cpy.y * vec2_cpy.z - vec1_cpy.z * vec2_cpy.y;
	closs_product.y = vec1_cpy.z * vec2_cpy.x - vec1_cpy.x * vec2_cpy.z;
	closs_product.z = vec1_cpy.x * vec2_cpy.y - vec1_cpy.y * vec2_cpy.x;

	//closs_product.CalcNorm();

	return closs_product;
}



//===========================================================================
/*!	@brief	なす角を計算
	@param	vec1,vec2:計算を行うベクトル
	@return	なす角
*/
//===========================================================================
f32 CalcVectorAngle(const Vector *vec1, const Vector *vec2)
{
	f32 angle;
	Vector vec1_cpy(*vec1);
	Vector vec2_cpy(*vec2);


	/* 零ベクトルの場合 */
	if(vec1_cpy.IsVectorZero() || vec2_cpy.IsVectorZero()) {
		return 0.0f;
	}


	vec1_cpy.Normalize();
	vec2_cpy.Normalize();

	//	cosθ = a・b / |a||b|
	//-----------------------------------------------
	angle = CalcDotProduct(&vec1_cpy, &vec2_cpy) / (vec1_cpy.GetNorm() * vec2_cpy.GetNorm());


	return acos(angle);
}




//===========================================================================
/*!	@brief	ベクトルのなす角を計算
	@param	vec1,vec2:計算するベクトル
	@return	なす角
*/
//===========================================================================
f32 CalcVectorAngle(const Vector& vec1, const Vector& vec2)
{
	f32 angle;
	Vector vec1_cpy(vec1);
	Vector vec2_cpy(vec2);


	/* 零ベクトルの場合 */
	if(vec1_cpy.IsVectorZero() || vec2_cpy.IsVectorZero()) {
		return 0.0f;
	}


	vec1_cpy.Normalize();
	vec2_cpy.Normalize();

	//	cosθ = a・b / |a||b|
	//-----------------------------------------------
	angle = CalcDotProduct(&vec1_cpy, &vec2_cpy) / 1.0f;

// 	if( 1.0f < angle ) {
// 		angle = 1.0f;
// 	}
// 	if( angle < -1.0f ) {
// 		angle = -1.0f;
// 	}

	return acos(angle);
}





//===========================================================================
/*!	@brief	ベクトルの符号が全部同じか
	@param	vec1,vec2:比較するベクトル
	@return	true:同じ	false:異なる
*/
//===========================================================================
bool IsSameDirection(const Vector& vec1, const Vector& vec2)
{

	if( Sign(vec1.x) != Sign(vec2.x) ) {
		return false;
	}
	if( Sign(vec1.y) != Sign(vec2.y) ) {
		return false;
	}
	if( Sign(vec1.z) != Sign(vec2.z) ) {
		return false;
	}

	return true;
}


}	// namespace math
}	// namespace nk

