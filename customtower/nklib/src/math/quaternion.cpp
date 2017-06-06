//=============================================================================
/*!	@file	quaternion.cpp

	@brief	クォータニオン

	@author	井手 竜之介
	@date	2011/12/14
	@todo	なし
	@bug	なし
*/
//=============================================================================



//-------------------------------インクルード-------------------------------
#include <math.h>
#include "../../include/math/quaternion.h"
#include "../../include/math/vector.h"
#include "../../include/math/matrix.h"
#include "../../include/general.h"


namespace nk {
namespace math {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), t(0.0f)
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
Quaternion::~Quaternion()
{
	
}


//===========================================================================
/*!	@brief	単位元化
	@param	なし
	@return	なし
*/
//===========================================================================
void Quaternion::Identity()
{
	t = 1.0f;
	x = y = z = 0.0f;
}


//===========================================================================
/*!	@brief	正規化
	@param	なし
	@return	なし
*/
//===========================================================================
void Quaternion::Normalize()
{
	/* 四元数の大きさを計算する */
	f32 mag = sqrtf(t * t + x * x + y * y + z * z);

	/* ゼロ除算チェック */
	if(mag > 0.0f) {
		f32 oneOvermag = 1.0f / mag;
		t *= oneOvermag;
		x *= oneOvermag;
		y *= oneOvermag;
		z *= oneOvermag;
	} else {
		PRINTF("Quaternion::normalize()ゼロ除算エラー\n");
		
		/* ひとまず初期化 */
		Identity();
	}
}

//===========================================================================
/*!	@brief	X軸回転
	@param	theta	: 回転量
	@return	なし
*/
//===========================================================================
void Quaternion::RotateX(f32 theta)
{
	/* 半分の角度を計算する */
	f32 halfTheta = theta * 0.5f;

	/* 値を設定する */
	t = cosf(halfTheta);
	x = sinf(halfTheta);
	y = 0.0f;
	z = 0.0f;
}


//===========================================================================
/*!	@brief	Y軸回転
	@param	theta	: 回転量
	@return	なし
*/
//===========================================================================
void Quaternion::RotateY(f32 theta)
{
	/* 半分の角度を計算する */
	f32 halfTheta = theta * 0.5f;

	/* 値を設定する */
	t = cosf(halfTheta);
	x = 0.0f;
	y = sinf(halfTheta);
	z = 0.0f;
}



//===========================================================================
/*!	@brief	Z軸回転
	@param	theta	: 回転量
	@return	なし
*/
//===========================================================================
void Quaternion::RotateZ(f32 theta)
{
	/* 半分の角度を計算する */
	f32 halfTheta = theta * 0.5f;

	/* 値を設定する */
	t = cosf(halfTheta);
	x = 0.0f;
	y = 0.0f;
	z = sinf(halfTheta);
}


//===========================================================================
/*!	@brief	任意軸回転
	@param	theta	: 回転量
	@param	axis	: 回転軸
	@return	なし
*/
//===========================================================================
void Quaternion::RotateAxis(f32 theta, const math::Vector &axis)
{
	/* 回転軸は正規化されている必要がある */
	f32 len = axis.GetNorm();
	
	if( fabs(len - 1.0f) > 0.01f ) {
		PRINTF( "Quaternion::SetToRotateAboutAxis 不正軸ベクトルで回転しようとしました\n" );
		
		return;
	}

	/* 半分の角とその sin を計算する */
	f32 halfTheta = theta * 0.5f;
	f32 halfSin   = sinf( halfTheta );

	/* 値を設定する */
	t = cosf(halfTheta);
	x = axis.x * halfSin;
	y = axis.y * halfSin;
	z = axis.z * halfSin;
}

//===========================================================================
/*!	@brief	YawPitchRoll回転(YXZ回転)
	@param	yaw		: Y軸回転量
	@param	pitch	: X軸回転量
	@param	roll	: Z軸回転量
	@return	なし
*/
//===========================================================================
void Quaternion::RotateYawPitchRoll(f32 yaw, f32 pitch, f32 roll)
{
	/* 半分の角のsin cosを計算する */
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
/*!	@brief	クォータニオン同士の掛け算
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
/*!	@brief	クォータニオンの内積
	@param	q0, q1	: 計算するクォータニオン
	@return	内積
*/
//===========================================================================
f32 DotProduct(const Quaternion &q0, const Quaternion &q1)
{
	return q0.t * q1.t + q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;
}




//===========================================================================
/*!	@brief	球面線形補間
	@param	q0	: 開始時の姿勢
	@param	q1	: 終了時の姿勢
	@param	t	: 0.0～1.0の間で補間する
	@return	補間したクォータニオン
	\memo	Spherical Linear intERPolationの略
*/
//===========================================================================
Quaternion Slerp(const Quaternion &q0, const Quaternion &q1, f32 t)
{
	/* 範囲外のパラメータをチェックし、その場合は端点を返す */
	if(t <= 0.0f) {
		return q0;
	}
	if(t >= 1.0f) {
		return q1;
	}

	/* 内積を用いて四元数間の角度のcosを計算する */
	f32 cosOmega = DotProduct(q0, q1);

	/*
		負の内積の場合、-q1を用いる
		２つの四元数qと-qは同じ回転を表すが、異なる球面線形補間を生成する場合がある
		正確な角度を用いて回転するためにqか-qかを選択する
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
		補間用のフラクションを計算する
		２つの四元数がほとんど全く同じであるかチェックする
	*/
	f32 k0, k1;
	if( cosOmega > 0.9999f ) {
		/* 非常に近い --- 単純に線形補間を用いる（ゼロ除算を防ぐ） */
		k0 = 1.0f - t;
		k1 = t;
	} else {
		/*
			三角法の等式sin^2(Omega) + cos^2(Omega) = 1を用いて
			この角度のsinを計算する
		*/
		f32 sinOmega = sqrtf(1.0f - cosOmega * cosOmega);

		/* このsin と cos から角度を計算する */
		f32 omega = atan2f( sinOmega, cosOmega );

		/* 除算が1回で済むように、分母の逆数を計算する */
		f32 oneOverSinOmega = 1.0f / sinOmega;

		/* 補間パラメータを計算する */
		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sin(t * omega) * oneOverSinOmega;
	}

	/* 補間する */
	Quaternion result;
	result.x = k0 * q0.x + k1 * q1x;
	result.y = k0 * q0.y + k1 * q1y;
	result.z = k0 * q0.z + k1 * q1z;
	result.t = k0 * q0.t + k1 * q1t;

	return result;
}



//===========================================================================
/*!	@brief	回転行列を取得
	@param	q		: 行列を取得したいクォータニオン
	@return	生成された行列
*/
//===========================================================================
Matrix44 GetQuaternionToMatrix(const Quaternion& q)
{
	f32 m11, m12, m13;	//行列の回転成分
	f32 m21, m22, m23;
	f32 m31, m32, m33;

	/* 共通して用いる副次式を先に計算しておく */
	f32 t = 2.0f * q.t;
	f32 x = 2.0f * q.x;
	f32 y = 2.0f * q.y;
	f32 z = 2.0f * q.z;

	/* 行列の要素を設定する */
	
	/* x軸成分 */
	m11 = 1.0f - y * q.y - z * q.z;
	m21 = x * q.y + t * q.z;
	m31 = x * q.z - t * q.y; 
	
	/* y軸成分 */
	m12 = x * q.y - t * q.z;
	m22 = 1.0f - x * q.x - z * q.z;
	m32 = y * q.z + t * q.x;
	
	/* z軸成分 */
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
//グローバルな恒等四元数
//CQuaternionクラスにはコンストラクタがないことに注意
//それらはまったく必要ないからである
const CQuaternion kQuaternionIdentity = {
1.0f, 0.0f, 0.0f, 0.0f
};


//========================================================================
//	クラス：CQuaternion
//	内　容：X軸回転
//	引　数：回転角度
//	戻り値：回転後のクォータニオン
//	 memo ：
//========================================================================
void CQuaternion::SetToRotateAboutX(f32 theta)
{
/* 半分の角度を計算する */
f32 halftheta = theta * 0.5f;

/* 値を設定する */
w = cosf( halftheta );
x = sinf( halftheta );
y = 0.0f;
z = 0.0f;
}

//========================================================================
//	クラス：CQuaternion
//	内　容：Y軸回転
//	引　数：回転角度
//	戻り値：回転後のクォータニオン
//	 memo ：
//========================================================================
void CQuaternion::SetToRotateAboutY(f32 theta)
{
/* 半分の角度を計算する */
f32 halftheta = theta * 0.5f;

/* 値を設定する */
w = cosf( halftheta );
x = 0.0f;
y = sinf( halftheta );
z = 0.0f;
}

//========================================================================
//	クラス：CQuaternion
//	内　容：Z軸回転
//	引　数：回転角度
//	戻り値：回転後のクォータニオン
//	 memo ：
//========================================================================
void CQuaternion::SetToRotateAboutZ(f32 theta)
{
/* 半分の角度を計算する */
f32 halftheta = theta * 0.5f;

/* 値を設定する */
w = cosf( halftheta );
x = 0.0f;
y = 0.0f;
z = sinf( halftheta );
}

//========================================================================
//	クラス：CQuaternion
//	内　容：任意軸回転
//	引　数：回転軸
//			回転角度
//	戻り値：回転後のクォータニオン
//	 memo ：
//========================================================================
void CQuaternion::SetToRotateAboutAxis(math::Vector &axis, f32 theta)
{
/* 回転軸は正規化されている必要がある */
f32 len = axis.GetNorm();

if( fabs(len - 1.0f) > 0.01f ) {
#ifndef NODEBUG
printf( "Quaternion::SetToRotateAboutAxis 不正軸ベクトルで回転しようとしました\n" );
#endif
return;
}

/* 半分の角とその sin を計算する */
f32 halftheta = theta * 0.5f;
f32 halfsin   = sinf( halftheta );

/* 値を設定する */
w = cosf( halftheta );
x = axis.x * halfsin;
y = axis.y * halfsin;
z = axis.z * halfsin;
}

//========================================================================
//	クラス：CQuaternion
//	内　容：XYZ回転
//	引　数：Y回転軸
//			X回転軸
//			Z回転軸
//	戻り値：回転後のクォータニオン
//	 memo ：
//========================================================================
void CQuaternion::SetToYawPitchRoll(f32 Yaw, f32 Pitch, f32 Roll)
{
/* 半分の角のsin cosを計算する */
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
//	クラス：CQuaternion
//	内　容：*演算子のオーバーロード
//	引　数：クォータニオン
//	戻り値：
//	 memo ：四元数の外積
//	
//	「実例で学ぶゲーム３D数学」では定義から外れ
//	乗算の順序は「左から右にかける順序」
//	（演算順序を見やすくするため）であるが、
//	この実装は定義通り
//	乗算の順序は「右から左にかける順序」とする。
//	これにより、OpenGLの行列演算と同じ考え方にできる
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
//	クラス：CQuaternion
//	内　容：*=演算子のオーバーロード
//	引　数：クォータニオン
//	戻り値：
//	 memo ：
//
//外積と代入の組み合わせ
// ここは実践によるゲーム３D数学と同じ順序にしてある
// q *= p は q = q * p の順序である。(q ≠ p * q)
//========================================================================
CQuaternion CQuaternion::operator *=(const CQuaternion &a)
{
*this = (*this) * a;

/* 左辺値への参照を返す */
return *this;
}


//========================================================================
//	クラス：CQuaternion
//	内　容：正規化
//	引　数：
//	戻り値：
//	 memo ：四元数を正規化する。
//
// 注意すべき点は、通常四元数は常に(数値精度の範囲内で)正規化されていることである。
// 
// この関数は主に、浮動小数点の誤差の侵入を防ぐために使われる。
// 誤差の侵入はたくさんの連続した四元数演算が適用された発生することがある。
//========================================================================
void CQuaternion::Normalize()
{
/* 四元数の大きさを計算する */
f32 mag = sqrtf( w * w + x * x + y * y + z * z );

/* ゼロ除算チェック */
if(mag > 0.0f) {
f32 oneOvermag = 1.0f / mag;
w *= oneOvermag;
x *= oneOvermag;
y *= oneOvermag;
z *= oneOvermag;
} else {
printf("Quaternion::normalize()ゼロ除算エラー\n");

/* ひとまず初期化 */
Identity();
}
}



//========================================================================
//	クラス：CQuaternion
//	内　容：回転角θを返す
//	引　数：
//	戻り値：回転角(ラジアン)
//	 memo ：
//========================================================================
f32 CQuaternion::GetRotationAngle() const
{
/* 格納されているのは半分の角であることに注意 */
f32 theta = acosf( w );

/* 回転角度を返す */
return theta * 2.0f;
}


//========================================================================
//	クラス：CQuaternion
//	内　容：回転軸を返す
//	引　数：
//	戻り値：回転軸
//	 memo ：
//========================================================================
math::Vector CQuaternion::GetRotationAxis() const
{
/*
sin^2(theta/2)を計算する
w = cos(theta/2), sin^2(x) + cos^2(x) = 1であることに注意
*/

f32 sinThetaOver2Sq = 1.0f -w * w;

/* 数値の不確かさから守る */
if( sinThetaOver2Sq <= 0.0f ) {
/* 恒等四元数か、不正な四元数なので適当に返す */
return math::Vector(1.0f, 0.0f, 0.0f);
}

f32 oneOverThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

/* 回転軸を返す */
return math::Vector(
	x * oneOverThetaOver2,
	y * oneOverThetaOver2,
	z * oneOverThetaOver2
);
}


//========================================================================
//	内　容：四元数の内積
//	引　数：
//	戻り値：内積
//	 memo ：
//
// 非メンバ関数を用いるので、ファンキーな構文を用いずに四元数表現を
// 演算数として渡すことができる
//========================================================================
f32 DotProduct( const CQuaternion &a, const CQuaternion &b)
{
return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}


//========================================================================
//	内　容：球面線形補間
//	引　数：
//	戻り値：補間後の四元数
//	 memo ：q0 ～ q1を引数tで補間した四元数を返す(t=0のときq0, t=1のときq1) 
//========================================================================
CQuaternion Slerp( const CQuaternion &q0, const CQuaternion &q1, f32 t)
{
/* 範囲外のパラメータをチェックし、その場合は端点を返す */
if(t <= 0.0f) return q0;
if(t >= 1.0f) return q1;

/* 内積を用いて四元数間の角度のcosを計算する */
f32 cosOmega = DotProduct(q0, q1);

/*
負の内積の場合、-q1を用いる
２つの四元数qと-qは同じ回転を表すが、異なる球面線形補間を生成する場合がある
正確な角度を用いて回転するためにqか-qかを選択する
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
補間用のフラクションを計算する
２つの四元数がほとんど全く同じであるかチェックする
*/

f32 k0, k1;
if( cosOmega > 0.9999f ) {
/* 非常に近い --- 単純に線形補間を用いる（ゼロ除算を防ぐ） */
k0 = 1.0f - t;
k1 = t;
} else {
/*
三角法の等式sin^2(Omega) + cos^2(Omega) = 1を用いて
この角度のsinを計算する
*/
f32 sinOmega = sqrtf(1.0f - cosOmega * cosOmega);

/* このsin と cos から角度を計算する */
f32 omega = atan2f( sinOmega, cosOmega );

/* 除算が1回で済むように、分母の逆数を計算する */
f32 oneOverSinOmega = 1.0f / sinOmega;

/* 補間パラメータを計算する */
k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
k1 = sin(t * omega) * oneOverSinOmega;
}

/* 補間する */
CQuaternion result;
result.x = k0 * q0.x + k1 * q1x;
result.y = k0 * q0.y + k1 * q1y;
result.z = k0 * q0.z + k1 * q1z;
result.w = k0 * q0.w + k1 * q1w;

return result;
}


//========================================================================
//	内　容：四元数の共役を計算する
//	引　数：共役をする四元数
//	戻り値：引数の四元数の反対の回転を持つ四元数
//	 memo ：
//========================================================================
CQuaternion Conjugate( const CQuaternion &q )
{
CQuaternion result;
/* 同じ回転量 */
result.w = q.w;

/* 反対の回転軸 */
result.x = -q.x;
result.y = -q.y;
result.z = -q.z;

return result;
}



//========================================================================
//	内　容：四元数から行列を作成する
//	引　数：変換する四元数
//	戻り値：回転行列
//	 memo ：平行移動成分はゼロである
//========================================================================
CMatrix44 GetQuaternionToMatrix( const CQuaternion &q )
{
f32 m11, m12, m13;	//行列の回転成分
f32 m21, m22, m23;
f32 m31, m32, m33;

/* 共通して用いる副次式を先に計算しておく */
f32 ww = 2.0f * q.w;
f32 xx = 2.0f * q.x;
f32 yy = 2.0f * q.y;
f32 zz = 2.0f * q.z;

/* 行列の要素を設定する */

/* x軸成分 */
m11 = 1.0f - yy * q.y - zz * q.z;
m21 = xx * q.y + ww * q.z;
m31 = xx * q.z - ww * q.y; 

/* y軸成分 */
m12 = xx * q.y - ww * q.z;
m22 = 1.0f - xx * q.x - zz * q.z;
m32 = yy * q.z + ww * q.x;

/* z軸成分 */
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
