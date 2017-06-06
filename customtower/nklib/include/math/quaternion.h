//=============================================================================
/*!	@file	quaternion.cpp

	@brief	クォータニオン

	@author	井手 竜之介
	@date	2011/12/14
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "../typedef.h"


//-------------------------------インクルード-------------------------------


namespace nk {
namespace math {

class	Matrix44;
class	Vector;

//=============================================================================
/*!
								クォータニオン
*/
//=============================================================================
class Quaternion {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//! 単位元
	void			Identity();

	//! X軸回転
	void			RotateX( f32 theta );

	//! Y軸回転
	void			RotateY( f32 theta );

	//! Z軸回転
	void			RotateZ( f32 theta );

	//! Yaw Pitch Roll(Y,X,Z)
	void			RotateYawPitchRoll( f32 yaw, f32 pitch, f32 roll );

	//! 任意軸回転
	void			RotateAxis( f32 theta, const math::Vector& axis );

	//! 正規化
	void			Normalize();

	//! 掛け算
	Quaternion		operator *( const Quaternion& qua ) const;

	//! 回転行列を取得
	friend Matrix44	GetQuaternionToMatrix( const Quaternion& q );

	//! 掛け算
	friend f32		DotProduct( const Quaternion &q0, const Quaternion &q1 );

	//! 球面線形補間
	friend			Quaternion Slerp( const Quaternion &q0, const Quaternion &q1, f32 t );

private:
	//----------------------メンバ変数-----------------------
	f32			t;				//!< 実部
	f32			x, y, z;		//!< 虚部(i,j,k)
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 Quaternion();
	~Quaternion();
};

//! クォータニオンから行列を取得
Matrix44	GetQuaternionToMatrix( const Quaternion& q );

//! 内積
f32			DotProduct( const Quaternion& q0, const Quaternion& q1 );

//! 球面線形補間(Spherical Linear intERPolation)
Quaternion	Slerp( const Quaternion& q0, const Quaternion& q1, f32 t );

}	// namespace math
}	// namespace nk


#if 0
class CQuaternion {
public:
	//通常これらの値を直接操作する必要はない。
	//しかし、これらはpublicにしておく。
	//直接アクセス禁止にしておくといくつかの操作が煩雑になるためである。
	f32 x, y, z, w;

	//	恒等四元数にする
	//---------------------------------------
	void Identity() {w = 1.0f; x = y = z = 0.0f;}

	//	四元数を特定の角度にセットアップする
	//---------------------------------------
	void SetToRotateAboutX(f32 theta);
	void SetToRotateAboutY(f32 theta);
	void SetToRotateAboutZ(f32 theta);
	void SetToRotateAboutAxis(math::Vector &axis, f32 theta);
	void SetToYawPitchRoll(f32 Yaw, f32 Pitch, f32 Roll);

	//	外積
	//---------------------------------------
	CQuaternion operator *(const CQuaternion &a) const;

	//	代入を伴う乗算
	//---------------------------------------
	CQuaternion operator *=(const CQuaternion &a);

	//	正規化
	//---------------------------------------
	void Normalize();

	//	回転角と角度を取り出す
	//---------------------------------------
	f32   GetRotationAngle() const;
	math::Vector GetRotationAxis()  const;
};

//恒等四元数用のグローバル変数
extern const CQuaternion kQuaternionIdentity;

//四元数の内積
extern f32 DotProduct(const CQuaternion &a, const CQuaternion &b);

//四元数の球面線形補間
extern CQuaternion Slerp(const CQuaternion &q0, const CQuaternion &q1, f32 t);

//四元数の共役
extern CQuaternion Conjugate(const CQuaternion &q);

//クォータニオンから回転行列を作成する
extern CMatrix44 GetQuaternionToMatrix( const CQuaternion &q );
#endif

#endif	// QUATERNION