/*-------------------------------------------------------------------------
	説　明：境界ボリューム
	作成日：2010/10/26
	更新日：2010/10/26
--------------------------------------------------------------------------*/
#include "../../include/collision/boundaryVolume.h"

#if defined( USE_OPENGL ) || defined( USE_SDL_OPENGL )
#include <GL/glut.h>
//#include <GL/glu.h>
//#include <GL/gl.h>
#endif



namespace nk {

system::CameraManager* BoundaryVolume::m_cameraMng	= NULL;


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
BoundaryVolume::BoundaryVolume()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
BoundaryVolume::~BoundaryVolume()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void BoundaryVolume::_Init( void )
{
	m_type			= BV_NONE;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void BoundaryVolume::_Term( void )
{

}


//--------------------------------Sphere--------------------------------



//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
	@return	
*/
//===========================================================================
BVSphere::BVSphere()
{

	Init();

}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
	@return	
*/
//===========================================================================
BVSphere::~BVSphere()
{

	Init();

}


//===========================================================================
/*!	@brief	初期化
	@param	なし
	@return	
*/
//===========================================================================
void BVSphere::Init()
{

	m_type = BV_SPHERE;
	m_radius = 0.0f;
	m_pos.SetVector(0.0f, 0.0f, 0.0f);

}


//===========================================================================
/*!	@brief	初期化
	@param	pos	: 位置
	@param	r	: 半径
	@return	
*/
//===========================================================================
void BVSphere::Init(const math::Vector& pos, f32 r)
{
	m_type = BV_SPHERE;
	SetPos(pos);
	SetRadius(r);

}


//===========================================================================
/*!	@brief	衝突判定
	@param	bv		: チェックを行う境界ボリューム
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVSphere::IsHit(const nk::BoundaryVolume *bv) const
{
	return bv->Check(this);
}


//===========================================================================
/*!	@brief	球との衝突判定
	@param	sphere	: チェックする球
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVSphere::Check(const BVSphere* sphere) const
{
	return IsHitSphereSphere(this, sphere);
}


//===========================================================================
/*!	@brief	線分との衝突判定
	@param	ray		: チェックする線分
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVSphere::Check(const BVRay* ray) const
{
	return IsHitSphereRay(this, ray);
}


//===========================================================================
/*!	@brief	無限平面との衝突判定
	@param	face	: チェックする平面
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVSphere::Check(const BVInfiniteFace* face) const
{
	return IsHitSphereInfFace(this, face);
}

//===========================================================================
/*!	@brief	描画
	@param	なし
	@return	なし
*/
//===========================================================================
void BVSphere::Draw()
{
#if defined( USE_OPENGL ) || defined( USE_SDL_OPENGL )
	static const s32 SLICES = 8;	// 分割数
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(m_cameraMng->GetUseCamera()->GetCameraMatrix().GetMatrix().ary16);
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	//glPolygonOffset(1.0f, 1.0f);
	glutWireSphere(m_radius, SLICES, SLICES);
	//glDisable(GL_POLYGON_OFFSET_FILL);
#endif
}


// 線分
//------------------------------------------------------------------------------------------


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
	@return	
*/
//===========================================================================
BVRay::BVRay()
{

	Init();

}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
	@return	
*/
//===========================================================================
BVRay::~BVRay()
{


}


//===========================================================================
/*!	@brief	初期化
	@param	なし
	@return	なし
*/
//===========================================================================
void BVRay::Init()
{
	m_type = BV_RAY;

}


//===========================================================================
/*!	@brief	初期化
	@param	o	: 始点
	@param	e	: 終点
	@return	なし
*/
//===========================================================================
void BVRay::Init(const math::Vector& o, const math::Vector& e)
{
	m_type = BV_RAY;
	SetOrigin(o);
	SetEnd(e);

}


//===========================================================================
/*!	@brief	衝突判定
	@param	bv		: チェックを行う境界ボリューム
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVRay::IsHit(const BoundaryVolume* bv) const
{
	return bv->Check(this);
}


//===========================================================================
/*!	@brief	球との交差判定
	@param	sphere	: チェックを行う球
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVRay::Check(const nk::BVSphere *sphere) const
{
	return IsHitSphereRay(sphere, this);
}


//===========================================================================
/*!	@brief	ポリゴンとの交差判定
	@param	poly	: チェックを行うポリゴン
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVRay::Check(const nk::BVPolygon *poly) const
{
	return IsHitRayPolygon(this, poly);
}


//===========================================================================
/*!	@brief	無限平面との交差判定
	@param	face	: チェックを行う無限平面
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVRay::Check(const nk::BVInfiniteFace *face) const
{
	return IsHitRayInfFace(this, face);
}




// ポリゴン
//------------------------------------------------------------------------------------------





//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
	@return	
*/
//===========================================================================
BVPolygon::BVPolygon()
{
	Init(math::Vector(), math::Vector(), math::Vector());

}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
	@return	
*/
//===========================================================================
BVPolygon::~BVPolygon()
{


}


//===========================================================================
/*!	@brief	初期化
	@param	p1, p2, p3	: 頂点
	@return	なし
*/
//===========================================================================
void BVPolygon::Init(const math::Vector& p1, const math::Vector& p2, const math::Vector& p3)
{
	m_type = BV_POLYGON;
	
	m_pos[0] = p1;
	m_pos[1] = p2;
	m_pos[2] = p3;

	m_normal = math::CalcCrossProduct(p2 - p1, p3 - p1);
	m_normal.Normalize();
}


//===========================================================================
/*!	@brief	頂点を習得
	@param	i	: 頂点番号
	@return	頂点座標
*/
//===========================================================================
math::Vector BVPolygon::GetPoint(s32 i) const
{
	assert(0 <= i && i < 3);
	return m_pos[i];
}


//===========================================================================
/*!	@brief	法線を習得
	@param	なし
	@return	法線
*/
//===========================================================================
math::Vector BVPolygon::GetNormal() const
{
	return m_normal;
}



//===========================================================================
/*!	@brief	衝突判定
	@param	bv		: チェックを行う境界ボリューム
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVPolygon::IsHit(const BoundaryVolume* bv) const
{
	return bv->Check(this);
}


//===========================================================================
/*!	@brief	線分との衝突判定
	@param	bv		: チェックを行う線分
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVPolygon::Check(const nk::BVRay *ray) const
{
	return IsHitRayPolygon(ray, this);
}



// 無限平面
//------------------------------------------------------------------------------------------


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
	@return	
*/
//===========================================================================
BVInfiniteFace::BVInfiniteFace() :
	m_normal(0.0f, 1.0f, 0.0f),
	m_pos(0.0f, 0.0f, 0.0f)
{

}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	pos		: 基準場所
	@param	n		: 法線
	@return	なし
*/
//===========================================================================
BVInfiniteFace::BVInfiniteFace(const nk::math::Vector& pos, const math::Vector& n)
{
	Init(pos, n);
}



//===========================================================================
/*!	@brief	デストラクタ
	@param	
	@return	
*/
//===========================================================================
BVInfiniteFace::~BVInfiniteFace()
{


}


//===========================================================================
/*!	@brief	初期化
	@param	pos		: 基準点
	@param	n		: 法線
	@return	なし
*/
//===========================================================================
void BVInfiniteFace::Init(const nk::math::Vector& pos, const math::Vector& n)
{
	m_type		= BV_INFINITYFACE;
	m_pos		= pos;
	m_normal	= n;
	m_normal.Normalize();


}


//===========================================================================
/*!	@brief	衝突判定
	@param	bv		: チェックを行う境界ボリューム
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVInfiniteFace::IsHit(const BoundaryVolume* bv) const
{
	return bv->Check(this);
}



//===========================================================================
/*!	@brief	球との衝突判定
	@param	sphere	: チェックを行う球
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVInfiniteFace::Check(const BVSphere* sphere) const
{
	return IsHitSphereInfFace(sphere, this);
}


//===========================================================================
/*!	@brief	線分との交差判定
	@param	ray		: チェックを行う線分
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool BVInfiniteFace::Check(const BVRay* ray) const
{
	return IsHitRayInfFace(ray, this);
}





// ヒット判定
//------------------------------------------------------------------------------------------



//===========================================================================
/*!	@brief	球と球のヒット判定
	@param	s1, s2	: 判定を行う球
	@return	true	: ヒット
	@return	false	: ヒットしていない
*/
//===========================================================================
bool IsHitSphereSphere(const BVSphere *s1, const BVSphere *s2)
{

	math::Vector vec = s2->GetPos() - s1->GetPos();
	f32 dot = CalcDotProduct(&vec, &vec);

	if( dot <= pow(s1->GetRadius() + s2->GetRadius(), 2) ) {
		return true;
	}

	return false;
}




//===========================================================================
/*!	@brief	球と線分のヒット判定
	@param	s		: 球
	@param	r		: 線分
	@return	true	: ヒット
	@return false	: ヒットしていない
*/
//===========================================================================
bool IsHitSphereRay(const BVSphere* s, const BVRay* r)
{
	/* 分母 */
	f32 denominator = r->GetLengthFromOriginToEnd().GetNorm2();
	
	const math::Vector vec1 = s->GetPos() - r->GetOrigin();
	const math::Vector vec2 = r->GetEnd() - r->GetOrigin();
	
	/* 分子 */
	f32 numerator = math::CalcDotProduct(vec1, vec2);

	//	点と球のヒット判定
	//---------------------------------------
	if( denominator == 0.0f ) {
		BVSphere c;
		c.Init(r->GetOrigin(), 1.0f);
		if( IsHitSphereSphere(s, &c) ) {
			return true;
		}
	}

	f32 t = numerator / denominator;

	if( 0.0f <= t && t <= 1.0f ) {
		const math::Vector	ray		= r->GetEnd() - r->GetOrigin();
		const math::Vector	point	= r->GetOrigin() + ray * t;
		const math::Vector	dist	= s->GetPos() - point;
		if( dist.GetNorm2() <= s->GetRadius() * s->GetRadius() ) {
			return true;
		}
	}

	else {
		{
			const math::Vector	dist	= s->GetPos() - r->GetOrigin();
			if( dist.GetNorm2() <= s->GetRadius() * s->GetRadius() ) {
				return true;
			}
		}
		{
			const math::Vector	dist	= s->GetPos() - r->GetEnd();
			if( dist.GetNorm2() <= s->GetRadius() * s->GetRadius() ) {
				return true;
			}
		}
	}

	return false;
}




//===========================================================================
/*!	@brief	三角形の内外判定
	@param	face	: 三角形
	@param	point	: 点
	@return	true	: 内側
	@return	false	: 外側
*/
//===========================================================================
bool IsPointInTriangle(const BVPolygon* face, const math::Vector& point)
{

	// 点から頂点までのベクトルを求める
	const math::Vector p0 = face->GetPoint(0) - point;
	const math::Vector p1 = face->GetPoint(1) - point;
	const math::Vector p2 = face->GetPoint(2) - point;

	// 外積で向きを調べる
	const math::Vector v0 = CalcCrossProduct(&p0, &p1);
	const math::Vector v1 = CalcCrossProduct(&p1, &p2);
	const math::Vector v2 = CalcCrossProduct(&p2, &p0);

	// 符号の向きが同じだったら内側
	if( IsSameDirection(v0, v1) && IsSameDirection(v1, v2) && IsSameDirection(v2, v0) ) {
		return true;
	}

	return false;
}



//===========================================================================
/*!	@brief	線分と無限平面の交差判定
	@param	ray		: 線分
	@param	norm	: 無限平面の法線ベクトル
	@return	true	: 交差している
	@return false	: 交差していない
*/
//===========================================================================
bool IsHitRayInfFace(const BVRay* ray, const BVInfiniteFace* face)
{
	const f32 near = math::CalcDotProduct(face->GetNormal(), math::Vector()) / face->GetNormal().GetNorm();

	f32 cosThetaS = math::CalcDotProduct(face->GetNormal(), ray->GetOrigin()) + near;
	f32 cosThetaE = math::CalcDotProduct(face->GetNormal(), ray->GetEnd()) + near;


	//	平面をまたいでいるか
	//---------------------------------------
	if( (cosThetaS >= 0) && (cosThetaE < 0) ) {
		return true;
	}

	return false;
}




//===========================================================================
/*!	@brief	静止球と無限平面のヒット判定
	@param	s		: 球
	@param	face	: 無限平面
	@return	true	: 当たっている
	@return false	: 当たっていない
*/
//===========================================================================
bool IsHitSphereInfFace(const BVSphere* s, const BVInfiniteFace* face)
{
	//const f32 dis = math::CalcDotProduct(s->GetPos(), face->GetNormal()) + face->GetMoveAmount();
	//const f32 near	= abs(math::CalcDotProduct(face->GetNormal(), math::Vector())) / face->GetNormal().GetNorm();
	const f32 near	= math::CalcDotProduct(face->GetNormal(), math::Vector()) / face->GetNormal().GetNorm();
	const f32 dis		= math::CalcDotProduct(s->GetPos(), face->GetNormal()) + near;

	if( abs(dis) <= s->GetRadius() ) {
		return true;
	}

	return false;
}



//===========================================================================
/*!	@brief	線分とポリゴンの交差判定
	@param	ray		: 線分
	@param	poly	: ポリゴン
	@return	true	: 当たっている
	@return false	: 当たっていない
*/
//===========================================================================
bool IsHitRayPolygon(const BVRay* ray, const BVPolygon* poly)
{
	math::Vector&	poly0	= poly->GetPoint(0);	// ポリゴンの点
	math::Vector&	poly1	= poly->GetPoint(1);
	math::Vector&	poly2	= poly->GetPoint(2);
	math::Vector	normal	= poly->GetNormal();

	BVInfiniteFace face;
	face.Init(poly0, normal);

	if( !IsHitRayInfFace(ray, &face) ) {
		return false;
	}

	// 始点と終点の平面までの距離を求める
	f32			disStart	= CalcDistanceFromPointToFace(ray->GetOrigin(), &face);
	f32			disEnd		= CalcDistanceFromPointToFace(ray->GetEnd(), &face);
	

	// 平面上のどの位置に線分が来るかを計算
	if( disStart + disEnd == 0.0f ) {
		return false;
	}
	f32			a				= disStart / (disStart + disEnd);
	math::Vector	piercingPoint	= ray->GetOrigin() + (ray->GetLengthFromOriginToEnd() * a);	// 貫通点


	// 貫通点がポリゴン内に入っているかどうかを判定
	math::Vector norm0 = math::CalcCrossProduct(poly1 - poly0, piercingPoint - poly1);
	math::Vector norm1 = math::CalcCrossProduct(poly2 - poly1, piercingPoint - poly2);
	math::Vector norm2 = math::CalcCrossProduct(poly0 - poly2, piercingPoint - poly0);

	// 頂点と貫通点の法線が面の法線と同じ向きなら交差
	norm0.Normalize();
	norm1.Normalize();
	norm2.Normalize();
	if( (normal == norm0) && (normal == norm1) && (normal == norm2) ) {
		return true;
	}

	return false;
}


//===========================================================================
/*!	@brief	点から平面までの距離を求める
	@param	point	: 点の座標
	@param	face	: 面
	@return	
*/
//===========================================================================
f32 CalcDistanceFromPointToFace(const math::Vector& point, const BVInfiniteFace* face)
{
	//d = |Dot(vn,v1)|/ |vn|
	math::Vector	v		= point - face->GetPos();
	math::Vector	n		= face->GetNormal();
	
	return abs(math::CalcDotProduct(n, v)) / n.GetNorm();
}
	
//===========================================================================
/*!	@brief		線分と球の交点を計算
	@param[out]	out				交点
	@param[in]	sphere			球
	@param		ray				線
	@return		交点の数
*/
//===========================================================================
s32 CalcIntersectionPoint( nk::math::Vector* out, const BVSphere* sphere, const BVRay* ray )
{
	NULL_ASSERT( out );
	if( out == NULL ) {
		return 0;
	}

	// ヒットしていなかったら交点は無し
	if( IsHitSphereRay( sphere, ray ) == false ) {
		return 0;
	}

	//     /                  \
	//    |                    |
	//    |         c-----r----|
	//    |         |          |
	// ----\--------p---------h------------a
	//      \                /
	const nk::math::Vector	a				= ray->GetOrigin();
	const nk::math::Vector	c				= sphere->GetPos();
	const nk::math::Vector	a2c				= c - a;
	const nk::math::Vector	a2pDirec		= ray->GetLengthFromOriginToEnd().GetNormalizeVec();
	const f64				a2pLength		= nk::math::CalcDotProduct( a2pDirec, a2c );
	const f64				a2c_2			= pow( static_cast<f64>(a2c.GetNorm()), 2.0 );
	const f64				a2p_2			= pow( static_cast<f64>(a2pLength), 2.0 );
	const f64				c2p_2			= a2c_2 - a2p_2;
	const f64				r_2				= pow( static_cast<f64>(sphere->GetRadius()), 2.0 );
	const f64				p2hLength		= sqrt( r_2 - c2p_2 );
	const f64				a2hLength		= a2pLength - p2hLength;
	const nk::math::Vector	a2h				= a + a2pDirec * a2hLength;

	*out	= a2h;
	
	// 交点2箇所
	return 1;
}
	
#if 0
//===========================================================================
/*!	@brief		線分と球の交点を計算
	@param[out]	out1, out2		交点
	@param[in]	sphere			球
	@param		ray				線
	@return		交点の数
*/
//===========================================================================
s32 CalcIntersectionPoint( nk::math::Vector* out1, nk::math::Vector* out2, const BVSphere* sphere, const BVRay* ray )
{
	NULL_ASSERT( out1 );
	NULL_ASSERT( out2 );
	if( out1 == NULL ) {
		return 0;
	}
	if( out2 == NULL ) {
		return 0;
	}

	// ヒットしていなかったら交点は無し
	if( IsHitSphereRay( sphere, ray ) == false ) {
		return 0;
	}
	
	const nk::math::Vector	start	= ray->GetOrigin();
	const nk::math::Vector	direc	= ray->GetLengthFromOriginToEnd();
	//const nk::math::Vector	direc	= ray->GetLengthFromOriginToEnd().GetNormalizeVec();

	// (direc * t0), (direc * t1) が交点の座標
	f32	t0	= 0.0f;
	f32	t1	= 0.0f;

	// (-b ± √(b^2 - 4ac)) / (2a)
	// ----
	// r^2 = (start.x^2 + 2 * start.x * direc.x * t + (direc.x * t)^2) +
	//       (start.y^2 + 2 * start.y * direc.y * t + (direc.y * t)^2) +
	//       (start.z^2 + 2 * start.z * direc.z * t + (direc.z * t)^2);
	// ----
	// 0 =   (direc.x * t)^2 + (direc.y * t)^2 + (direc.z * t)^2 +
	//       2 * start.x * direc.x * t + 2 * start.y * direc.y * t + 2 * start.z * direc.z * t
	//       (start.x^2 + start.y^2 + start.z^2) - r^2
	// ----
	// 0 =   (direc.x + direc.y + direc.z)t^2 +
	//       (2 * start.x * direc.x * t + 2 * start.y * direc.y * t + 2 * start.z * direc.z * t) +
	//       (start.x^2 + start.y^2 + start.z^2) - r^2

	// at^2 + bt + c = 0
	const f32	a	= direc.x + direc.y + direc.z;
	const f32	b	= 2.0f * start.x * direc.x + 2.0f * start.y * direc.y + 2.0f * start.z * direc.z;
	const f32	c	= (start.x * start.x) + (start.y * start.y) + (start.z * start.z) - (sphere->GetRadius() * sphere->GetRadius());

	// √(b^2 - 4ac)
	const f64	rootB2minus4AC	= sqrt( b * b - 4 * a * c );
	const f32	plusT			= (-b + rootB2minus4AC) / (2 * a);
	const f32	minusT			= (-b - rootB2minus4AC) / (2 * a);

	// 交点1
	if( (-0.00001 <= rootB2minus4AC) && (rootB2minus4AC <= 0.00001) ) {
		*out1	= start * plusT;
		return 1;
	}

	*out1	= start + direc * plusT;
	*out2	= start + direc * minusT;

	// 交点2箇所
	return 2;
}
#endif
#if 0

//===========================================================================
/*!	@brief	動いている球と無限平面
	@param	s		: 球(現在位置)
	@param	move	: 球の移動量ベクトル
	@param	face	: 無限平面
	@return	true	: 現在または今後ヒットする
	@return	false	: ヒットしない
*/
//===========================================================================
bool IsHit(const BVSphere* s, const math::Vector& move, const BVInfiniteFace* face) const
{
	/* 分子 */
	const f32 t_molecular   = s->GetRadius() - math::CalcDotProduct(s->GetPos(), face->GetNormal()) - face->GetMoveAmount();

	/* 分母 */
	const f32 t_denominator = math::CalcDotProduct(move, face->GetNormal());

	const f32 t = t_molecular / t_denominator;


	/* 衝突点を求める */
	//const math::Vector P = move * t + s.GetPos() - s.GetRadius() * face.GetNormal();


	return false;
}
#endif


}	// namespace nk
