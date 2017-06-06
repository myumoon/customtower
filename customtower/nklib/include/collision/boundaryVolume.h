
/*-------------------------------------------------------------------------
	説　明：境界ボリューム
	作成日：2010/10/26
	更新日：2010/10/26
--------------------------------------------------------------------------*/

#ifndef __BOUNDARYVOLUME_H__
#define __BOUNDARYVOLUME_H__

#include <math.h>
#include <assert.h>
#include "../math/vector.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"

namespace nk {

class CameraManager;
class BVSphere;
class BVPolygon;
class BVRay;
class BVInfiniteFace;
class HitListener;


enum BV_TYPE {
	BV_NONE,
	BV_SPHERE,
	BV_RAY,
	BV_POLYGON,
	BV_INFINITYFACE,
};


//=============================================================================
/*!
								境界ボリューム基底クラス

		ダブルディスパッチで衝突判定を行う
*/
//=============================================================================
class BoundaryVolume {
public:
	
public:

	//!	境界タイプを取得
	BV_TYPE				GetType() const { return m_type; }

	//! 衝突判定
	virtual	bool		IsHit( const BoundaryVolume* bv ) const = 0;

	//!	描画
	virtual void		Draw() {}

	//---------------ヒットチェック関数(ダブルディスパッチ)---------------
	//! 球
	virtual	bool		Check( const BVSphere* sphere		) const { return false; }

	//! 線分
	virtual	bool		Check( const BVRay* ray				) const { return false; }

	//! 三角ポリゴン
	virtual	bool		Check( const BVPolygon* poly		) const { return false; }

	//* 無限平面
	virtual	bool		Check( const BVInfiniteFace* face	) const { return false; }

	
	//----- debug
	static	void		SetCameraManager( system::CameraManager* mng ) { m_cameraMng = mng; }
protected:
	static system::CameraManager*		m_cameraMng;
	//----- debug
	
protected:

	//---------------メンバ変数---------------
	BV_TYPE								m_type;				//!< 自身のタイプ

private:
	//! 初期化・終了
	void	_Init( void );
	void	_Term( void );
	
public:

	//	コンストラクタ・デストラクタ
	//---------------------------------------
			BoundaryVolume();
	virtual~BoundaryVolume();
};



//=============================================================================
/*!
								球体クラス
*/
//=============================================================================
class BVSphere : public BoundaryVolume {
public:
	//!	初期化
	void			Init();
	void			Init( const math::Vector& pos, f32 r );

	//!	位置のセット
	void			SetPos( const math::Vector& p ) { m_pos = p; }

	//! 位置の習得
	math::Vector	GetPos() const		{ return m_pos; }
	
	//!	半径のセット
	void			SetRadius( f32 r )	{ m_radius = r; }

	//! 半径の習得
	f32				GetRadius() const	{ return m_radius; }

	//!	描画
	void Draw();

	//! 衝突判定
	bool			IsHit( const BoundaryVolume* bv ) const;
	
	//! 球
	bool			Check( const BVSphere* sphere ) const;

	//! 線分
	bool			Check( const BVRay* ray ) const;

	//* 無限平面
	bool			Check( const BVInfiniteFace* face ) const;

private:
	//	データ
	//---------------------------------------
	f32				m_radius;			//!< 半径
	math::Vector	m_pos;				//!< 位置

public:
	//!	コンストラクタ・デストラクタ
	 BVSphere();
	~BVSphere();
};






//=============================================================================
/*!
								線分クラス
*/
//=============================================================================
class BVRay : public BoundaryVolume {
public:
	//!	初期化
	void			Init();

	//! 初期化
	void			Init( const math::Vector& o, const math::Vector &e );

	//!	始点のセット
	void			SetOrigin( const math::Vector& p ) { m_origin = p; }

	//! 視点の習得
	math::Vector	GetOrigin() const { return m_origin; }
	
	//!	終点のセット
	void			SetEnd( const math::Vector& p) { m_end = p; }

	//! 終点の習得
	math::Vector	GetEnd() const { return m_end; }

	//!	始点から終点までのベクトルを計算
	math::Vector	GetLengthFromOriginToEnd() const { return m_end - m_origin; }

	//! 衝突判定
	bool			IsHit( const BoundaryVolume* bv ) const;

	//! 球との交差判定
	bool			Check( const BVSphere* sphere ) const;

	//! 三角ポリゴンとの交差判定
	bool			Check( const BVPolygon* poly ) const;

	//! 無限平面との交差判定
	bool			Check( const BVInfiniteFace* face ) const;

private:
	//	データ
	//---------------------------------------
	math::Vector	m_origin;		//!< 始点
	math::Vector	m_end;			//!< 終点

public:
	//	コンストラクタ・デストラクタ
	//---------------------------------------
	 BVRay();
	~BVRay();

};





//=============================================================================
/*!
								三角ポリゴンクラス
		反時計回りが表
*/
//=============================================================================
class BVPolygon : public BoundaryVolume {
public:
	//!	セット
	void			Init(const math::Vector&, const math::Vector&, const math::Vector&);	

	//!	頂点を取得
	math::Vector	GetPoint(s32 i) const;

	//! 法線を習得
	math::Vector	GetNormal() const;

	//! 衝突判定
	bool			IsHit(const BoundaryVolume* bv) const;

	//! 線分との衝突判定
	bool			Check(const BVRay* ray) const;

private:
	//	データ
	//---------------------------------------
	math::Vector	m_pos[3];	//!< 頂点
	math::Vector	m_normal;	//!< 法線

public:
	//	コンストラクタ・デストラクタ
	//---------------------------------------
	 BVPolygon();
	 BVPolygon(const math::Vector&, const math::Vector&, const math::Vector&);
	~BVPolygon();

};




//=============================================================================
/*!
								無限平面クラス
		
		デフォルトで法線(0,1,0)のXZ平面
*/
//=============================================================================
class BVInfiniteFace : public BoundaryVolume {
public:
	//!	セット
	void			Init(const nk::math::Vector& pos, const math::Vector& n);

	//!	法線を取得
	math::Vector	GetNormal() const { return m_normal; }

	//! 基準点を習得
	math::Vector	GetPos() const { return m_pos; }

	//! 衝突判定
	bool			IsHit(const BoundaryVolume* bv) const;

	//! 球との衝突判定
	bool			Check(const BVSphere* sphere) const;

	//! 線分との交差判定
	bool			Check(const BVRay* ray) const;

private:
	//	データ
	//---------------------------------------
	math::Vector	m_normal;		//!< 正規化済みの法線
	math::Vector	m_pos;			//!< 位置

public:
	//	コンストラクタ・デストラクタ
	//---------------------------------------
	 BVInfiniteFace();
	 BVInfiniteFace(const nk::math::Vector& pos, const math::Vector& n);
	~BVInfiniteFace();
};
#if 0
class BVInfiniteFace : public BoundaryVolume {
public:
	//!	セット
	void Init(const math::Vector& norm, f32 move);	
	
	//!	法線を取得
	math::Vector GetNormal() const { return m_normal; }

	//! 原点からの移動量を習得
	f32 GetMoveAmount() const { return m_d; }
	
private:
	//	データ
	//---------------------------------------
	math::Vector		m_normal;		//!< ノーマライズ済みの法線
	f32				m_d;			//!< 原点から法線方向への移動量

public:
	//	コンストラクタ・デストラクタ
	//---------------------------------------
	 BVInfiniteFace();
	 BVInfiniteFace(const math::Vector& norm, f32 move);
	~BVInfiniteFace();
};
#endif


//! 球と球のヒット判定
bool	IsHitSphereSphere( const BVSphere* s1, const BVSphere* s2 );

//! 球と線分のヒット判定
bool	IsHitSphereRay( const BVSphere* s, const BVRay* r );

//! 線分と三角ポリゴン
bool	IsHitRayPolygon( const BVRay* ray, const BVPolygon* poly );

//! 線分と無限平面
bool	IsHitRayInfFace( const BVRay* ray, const BVInfiniteFace* face );

//! 球と無限平面
bool	IsHitSphereInfFace( const BVSphere* s, const BVInfiniteFace* face );

//! 三角形の内外判定
bool	IsPointInTriangle( const BVPolygon* face, const math::Vector& point );


//! 点から平面までの距離を求める
f32		CalcDistanceFromPointToFace( const math::Vector& point, const BVInfiniteFace* face );

//! 線分と球の交点を計算
s32		CalcIntersectionPoint( nk::math::Vector* out, const BVSphere* sphere, const BVRay* ray );
// s32		CalcIntersectionPoint( nk::math::Vector* out1, nk::math::Vector* out2, const BVSphere* sphere, const BVRay* ray );
	
#if 0
/* 動いている球と無限平面 */
bool IsHit(const BVSphere* s, const math::Vector& move, const BVInfiniteFace* face);
#endif

/* 動いてる球と三角ポリゴン */

/* 三角形の最近接面 */

}	// namespace nk


#endif  // __BOUNDARYVOLUME_H__