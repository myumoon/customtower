/*-------------------------------------------------------------------------
	���@���F���E�{�����[��
	�쐬���F2010/10/26
	�X�V���F2010/10/26
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
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
BoundaryVolume::BoundaryVolume()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
BoundaryVolume::~BoundaryVolume()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void BoundaryVolume::_Init( void )
{
	m_type			= BV_NONE;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void BoundaryVolume::_Term( void )
{

}


//--------------------------------Sphere--------------------------------



//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
	@return	
*/
//===========================================================================
BVSphere::BVSphere()
{

	Init();

}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
	@return	
*/
//===========================================================================
BVSphere::~BVSphere()
{

	Init();

}


//===========================================================================
/*!	@brief	������
	@param	�Ȃ�
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
/*!	@brief	������
	@param	pos	: �ʒu
	@param	r	: ���a
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
/*!	@brief	�Փ˔���
	@param	bv		: �`�F�b�N���s�����E�{�����[��
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVSphere::IsHit(const nk::BoundaryVolume *bv) const
{
	return bv->Check(this);
}


//===========================================================================
/*!	@brief	���Ƃ̏Փ˔���
	@param	sphere	: �`�F�b�N���鋅
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVSphere::Check(const BVSphere* sphere) const
{
	return IsHitSphereSphere(this, sphere);
}


//===========================================================================
/*!	@brief	�����Ƃ̏Փ˔���
	@param	ray		: �`�F�b�N�������
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVSphere::Check(const BVRay* ray) const
{
	return IsHitSphereRay(this, ray);
}


//===========================================================================
/*!	@brief	�������ʂƂ̏Փ˔���
	@param	face	: �`�F�b�N���镽��
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVSphere::Check(const BVInfiniteFace* face) const
{
	return IsHitSphereInfFace(this, face);
}

//===========================================================================
/*!	@brief	�`��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void BVSphere::Draw()
{
#if defined( USE_OPENGL ) || defined( USE_SDL_OPENGL )
	static const s32 SLICES = 8;	// ������
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


// ����
//------------------------------------------------------------------------------------------


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
	@return	
*/
//===========================================================================
BVRay::BVRay()
{

	Init();

}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
	@return	
*/
//===========================================================================
BVRay::~BVRay()
{


}


//===========================================================================
/*!	@brief	������
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void BVRay::Init()
{
	m_type = BV_RAY;

}


//===========================================================================
/*!	@brief	������
	@param	o	: �n�_
	@param	e	: �I�_
	@return	�Ȃ�
*/
//===========================================================================
void BVRay::Init(const math::Vector& o, const math::Vector& e)
{
	m_type = BV_RAY;
	SetOrigin(o);
	SetEnd(e);

}


//===========================================================================
/*!	@brief	�Փ˔���
	@param	bv		: �`�F�b�N���s�����E�{�����[��
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVRay::IsHit(const BoundaryVolume* bv) const
{
	return bv->Check(this);
}


//===========================================================================
/*!	@brief	���Ƃ̌�������
	@param	sphere	: �`�F�b�N���s����
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVRay::Check(const nk::BVSphere *sphere) const
{
	return IsHitSphereRay(sphere, this);
}


//===========================================================================
/*!	@brief	�|���S���Ƃ̌�������
	@param	poly	: �`�F�b�N���s���|���S��
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVRay::Check(const nk::BVPolygon *poly) const
{
	return IsHitRayPolygon(this, poly);
}


//===========================================================================
/*!	@brief	�������ʂƂ̌�������
	@param	face	: �`�F�b�N���s����������
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVRay::Check(const nk::BVInfiniteFace *face) const
{
	return IsHitRayInfFace(this, face);
}




// �|���S��
//------------------------------------------------------------------------------------------





//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
	@return	
*/
//===========================================================================
BVPolygon::BVPolygon()
{
	Init(math::Vector(), math::Vector(), math::Vector());

}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
	@return	
*/
//===========================================================================
BVPolygon::~BVPolygon()
{


}


//===========================================================================
/*!	@brief	������
	@param	p1, p2, p3	: ���_
	@return	�Ȃ�
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
/*!	@brief	���_���K��
	@param	i	: ���_�ԍ�
	@return	���_���W
*/
//===========================================================================
math::Vector BVPolygon::GetPoint(s32 i) const
{
	assert(0 <= i && i < 3);
	return m_pos[i];
}


//===========================================================================
/*!	@brief	�@�����K��
	@param	�Ȃ�
	@return	�@��
*/
//===========================================================================
math::Vector BVPolygon::GetNormal() const
{
	return m_normal;
}



//===========================================================================
/*!	@brief	�Փ˔���
	@param	bv		: �`�F�b�N���s�����E�{�����[��
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVPolygon::IsHit(const BoundaryVolume* bv) const
{
	return bv->Check(this);
}


//===========================================================================
/*!	@brief	�����Ƃ̏Փ˔���
	@param	bv		: �`�F�b�N���s������
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVPolygon::Check(const nk::BVRay *ray) const
{
	return IsHitRayPolygon(ray, this);
}



// ��������
//------------------------------------------------------------------------------------------


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
	@return	
*/
//===========================================================================
BVInfiniteFace::BVInfiniteFace() :
	m_normal(0.0f, 1.0f, 0.0f),
	m_pos(0.0f, 0.0f, 0.0f)
{

}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	pos		: ��ꏊ
	@param	n		: �@��
	@return	�Ȃ�
*/
//===========================================================================
BVInfiniteFace::BVInfiniteFace(const nk::math::Vector& pos, const math::Vector& n)
{
	Init(pos, n);
}



//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
	@return	
*/
//===========================================================================
BVInfiniteFace::~BVInfiniteFace()
{


}


//===========================================================================
/*!	@brief	������
	@param	pos		: ��_
	@param	n		: �@��
	@return	�Ȃ�
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
/*!	@brief	�Փ˔���
	@param	bv		: �`�F�b�N���s�����E�{�����[��
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVInfiniteFace::IsHit(const BoundaryVolume* bv) const
{
	return bv->Check(this);
}



//===========================================================================
/*!	@brief	���Ƃ̏Փ˔���
	@param	sphere	: �`�F�b�N���s����
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVInfiniteFace::Check(const BVSphere* sphere) const
{
	return IsHitSphereInfFace(sphere, this);
}


//===========================================================================
/*!	@brief	�����Ƃ̌�������
	@param	ray		: �`�F�b�N���s������
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool BVInfiniteFace::Check(const BVRay* ray) const
{
	return IsHitRayInfFace(ray, this);
}





// �q�b�g����
//------------------------------------------------------------------------------------------



//===========================================================================
/*!	@brief	���Ƌ��̃q�b�g����
	@param	s1, s2	: ������s����
	@return	true	: �q�b�g
	@return	false	: �q�b�g���Ă��Ȃ�
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
/*!	@brief	���Ɛ����̃q�b�g����
	@param	s		: ��
	@param	r		: ����
	@return	true	: �q�b�g
	@return false	: �q�b�g���Ă��Ȃ�
*/
//===========================================================================
bool IsHitSphereRay(const BVSphere* s, const BVRay* r)
{
	/* ���� */
	f32 denominator = r->GetLengthFromOriginToEnd().GetNorm2();
	
	const math::Vector vec1 = s->GetPos() - r->GetOrigin();
	const math::Vector vec2 = r->GetEnd() - r->GetOrigin();
	
	/* ���q */
	f32 numerator = math::CalcDotProduct(vec1, vec2);

	//	�_�Ƌ��̃q�b�g����
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
/*!	@brief	�O�p�`�̓��O����
	@param	face	: �O�p�`
	@param	point	: �_
	@return	true	: ����
	@return	false	: �O��
*/
//===========================================================================
bool IsPointInTriangle(const BVPolygon* face, const math::Vector& point)
{

	// �_���璸�_�܂ł̃x�N�g�������߂�
	const math::Vector p0 = face->GetPoint(0) - point;
	const math::Vector p1 = face->GetPoint(1) - point;
	const math::Vector p2 = face->GetPoint(2) - point;

	// �O�ςŌ����𒲂ׂ�
	const math::Vector v0 = CalcCrossProduct(&p0, &p1);
	const math::Vector v1 = CalcCrossProduct(&p1, &p2);
	const math::Vector v2 = CalcCrossProduct(&p2, &p0);

	// �����̌��������������������
	if( IsSameDirection(v0, v1) && IsSameDirection(v1, v2) && IsSameDirection(v2, v0) ) {
		return true;
	}

	return false;
}



//===========================================================================
/*!	@brief	�����Ɩ������ʂ̌�������
	@param	ray		: ����
	@param	norm	: �������ʂ̖@���x�N�g��
	@return	true	: �������Ă���
	@return false	: �������Ă��Ȃ�
*/
//===========================================================================
bool IsHitRayInfFace(const BVRay* ray, const BVInfiniteFace* face)
{
	const f32 near = math::CalcDotProduct(face->GetNormal(), math::Vector()) / face->GetNormal().GetNorm();

	f32 cosThetaS = math::CalcDotProduct(face->GetNormal(), ray->GetOrigin()) + near;
	f32 cosThetaE = math::CalcDotProduct(face->GetNormal(), ray->GetEnd()) + near;


	//	���ʂ��܂����ł��邩
	//---------------------------------------
	if( (cosThetaS >= 0) && (cosThetaE < 0) ) {
		return true;
	}

	return false;
}




//===========================================================================
/*!	@brief	�Î~���Ɩ������ʂ̃q�b�g����
	@param	s		: ��
	@param	face	: ��������
	@return	true	: �������Ă���
	@return false	: �������Ă��Ȃ�
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
/*!	@brief	�����ƃ|���S���̌�������
	@param	ray		: ����
	@param	poly	: �|���S��
	@return	true	: �������Ă���
	@return false	: �������Ă��Ȃ�
*/
//===========================================================================
bool IsHitRayPolygon(const BVRay* ray, const BVPolygon* poly)
{
	math::Vector&	poly0	= poly->GetPoint(0);	// �|���S���̓_
	math::Vector&	poly1	= poly->GetPoint(1);
	math::Vector&	poly2	= poly->GetPoint(2);
	math::Vector	normal	= poly->GetNormal();

	BVInfiniteFace face;
	face.Init(poly0, normal);

	if( !IsHitRayInfFace(ray, &face) ) {
		return false;
	}

	// �n�_�ƏI�_�̕��ʂ܂ł̋��������߂�
	f32			disStart	= CalcDistanceFromPointToFace(ray->GetOrigin(), &face);
	f32			disEnd		= CalcDistanceFromPointToFace(ray->GetEnd(), &face);
	

	// ���ʏ�̂ǂ̈ʒu�ɐ��������邩���v�Z
	if( disStart + disEnd == 0.0f ) {
		return false;
	}
	f32			a				= disStart / (disStart + disEnd);
	math::Vector	piercingPoint	= ray->GetOrigin() + (ray->GetLengthFromOriginToEnd() * a);	// �ђʓ_


	// �ђʓ_���|���S�����ɓ����Ă��邩�ǂ����𔻒�
	math::Vector norm0 = math::CalcCrossProduct(poly1 - poly0, piercingPoint - poly1);
	math::Vector norm1 = math::CalcCrossProduct(poly2 - poly1, piercingPoint - poly2);
	math::Vector norm2 = math::CalcCrossProduct(poly0 - poly2, piercingPoint - poly0);

	// ���_�Ɗђʓ_�̖@�����ʂ̖@���Ɠ��������Ȃ����
	norm0.Normalize();
	norm1.Normalize();
	norm2.Normalize();
	if( (normal == norm0) && (normal == norm1) && (normal == norm2) ) {
		return true;
	}

	return false;
}


//===========================================================================
/*!	@brief	�_���畽�ʂ܂ł̋��������߂�
	@param	point	: �_�̍��W
	@param	face	: ��
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
/*!	@brief		�����Ƌ��̌�_���v�Z
	@param[out]	out				��_
	@param[in]	sphere			��
	@param		ray				��
	@return		��_�̐�
*/
//===========================================================================
s32 CalcIntersectionPoint( nk::math::Vector* out, const BVSphere* sphere, const BVRay* ray )
{
	NULL_ASSERT( out );
	if( out == NULL ) {
		return 0;
	}

	// �q�b�g���Ă��Ȃ��������_�͖���
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
	
	// ��_2�ӏ�
	return 1;
}
	
#if 0
//===========================================================================
/*!	@brief		�����Ƌ��̌�_���v�Z
	@param[out]	out1, out2		��_
	@param[in]	sphere			��
	@param		ray				��
	@return		��_�̐�
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

	// �q�b�g���Ă��Ȃ��������_�͖���
	if( IsHitSphereRay( sphere, ray ) == false ) {
		return 0;
	}
	
	const nk::math::Vector	start	= ray->GetOrigin();
	const nk::math::Vector	direc	= ray->GetLengthFromOriginToEnd();
	//const nk::math::Vector	direc	= ray->GetLengthFromOriginToEnd().GetNormalizeVec();

	// (direc * t0), (direc * t1) ����_�̍��W
	f32	t0	= 0.0f;
	f32	t1	= 0.0f;

	// (-b �} ��(b^2 - 4ac)) / (2a)
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

	// ��(b^2 - 4ac)
	const f64	rootB2minus4AC	= sqrt( b * b - 4 * a * c );
	const f32	plusT			= (-b + rootB2minus4AC) / (2 * a);
	const f32	minusT			= (-b - rootB2minus4AC) / (2 * a);

	// ��_1
	if( (-0.00001 <= rootB2minus4AC) && (rootB2minus4AC <= 0.00001) ) {
		*out1	= start * plusT;
		return 1;
	}

	*out1	= start + direc * plusT;
	*out2	= start + direc * minusT;

	// ��_2�ӏ�
	return 2;
}
#endif
#if 0

//===========================================================================
/*!	@brief	�����Ă��鋅�Ɩ�������
	@param	s		: ��(���݈ʒu)
	@param	move	: ���̈ړ��ʃx�N�g��
	@param	face	: ��������
	@return	true	: ���݂܂��͍���q�b�g����
	@return	false	: �q�b�g���Ȃ�
*/
//===========================================================================
bool IsHit(const BVSphere* s, const math::Vector& move, const BVInfiniteFace* face) const
{
	/* ���q */
	const f32 t_molecular   = s->GetRadius() - math::CalcDotProduct(s->GetPos(), face->GetNormal()) - face->GetMoveAmount();

	/* ���� */
	const f32 t_denominator = math::CalcDotProduct(move, face->GetNormal());

	const f32 t = t_molecular / t_denominator;


	/* �Փ˓_�����߂� */
	//const math::Vector P = move * t + s.GetPos() - s.GetRadius() * face.GetNormal();


	return false;
}
#endif


}	// namespace nk
