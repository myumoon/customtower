
/*-------------------------------------------------------------------------
	���@���F���E�{�����[��
	�쐬���F2010/10/26
	�X�V���F2010/10/26
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
								���E�{�����[�����N���X

		�_�u���f�B�X�p�b�`�ŏՓ˔�����s��
*/
//=============================================================================
class BoundaryVolume {
public:
	
public:

	//!	���E�^�C�v���擾
	BV_TYPE				GetType() const { return m_type; }

	//! �Փ˔���
	virtual	bool		IsHit( const BoundaryVolume* bv ) const = 0;

	//!	�`��
	virtual void		Draw() {}

	//---------------�q�b�g�`�F�b�N�֐�(�_�u���f�B�X�p�b�`)---------------
	//! ��
	virtual	bool		Check( const BVSphere* sphere		) const { return false; }

	//! ����
	virtual	bool		Check( const BVRay* ray				) const { return false; }

	//! �O�p�|���S��
	virtual	bool		Check( const BVPolygon* poly		) const { return false; }

	//* ��������
	virtual	bool		Check( const BVInfiniteFace* face	) const { return false; }

	
	//----- debug
	static	void		SetCameraManager( system::CameraManager* mng ) { m_cameraMng = mng; }
protected:
	static system::CameraManager*		m_cameraMng;
	//----- debug
	
protected:

	//---------------�����o�ϐ�---------------
	BV_TYPE								m_type;				//!< ���g�̃^�C�v

private:
	//! �������E�I��
	void	_Init( void );
	void	_Term( void );
	
public:

	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
			BoundaryVolume();
	virtual~BoundaryVolume();
};



//=============================================================================
/*!
								���̃N���X
*/
//=============================================================================
class BVSphere : public BoundaryVolume {
public:
	//!	������
	void			Init();
	void			Init( const math::Vector& pos, f32 r );

	//!	�ʒu�̃Z�b�g
	void			SetPos( const math::Vector& p ) { m_pos = p; }

	//! �ʒu�̏K��
	math::Vector	GetPos() const		{ return m_pos; }
	
	//!	���a�̃Z�b�g
	void			SetRadius( f32 r )	{ m_radius = r; }

	//! ���a�̏K��
	f32				GetRadius() const	{ return m_radius; }

	//!	�`��
	void Draw();

	//! �Փ˔���
	bool			IsHit( const BoundaryVolume* bv ) const;
	
	//! ��
	bool			Check( const BVSphere* sphere ) const;

	//! ����
	bool			Check( const BVRay* ray ) const;

	//* ��������
	bool			Check( const BVInfiniteFace* face ) const;

private:
	//	�f�[�^
	//---------------------------------------
	f32				m_radius;			//!< ���a
	math::Vector	m_pos;				//!< �ʒu

public:
	//!	�R���X�g���N�^�E�f�X�g���N�^
	 BVSphere();
	~BVSphere();
};






//=============================================================================
/*!
								�����N���X
*/
//=============================================================================
class BVRay : public BoundaryVolume {
public:
	//!	������
	void			Init();

	//! ������
	void			Init( const math::Vector& o, const math::Vector &e );

	//!	�n�_�̃Z�b�g
	void			SetOrigin( const math::Vector& p ) { m_origin = p; }

	//! ���_�̏K��
	math::Vector	GetOrigin() const { return m_origin; }
	
	//!	�I�_�̃Z�b�g
	void			SetEnd( const math::Vector& p) { m_end = p; }

	//! �I�_�̏K��
	math::Vector	GetEnd() const { return m_end; }

	//!	�n�_����I�_�܂ł̃x�N�g�����v�Z
	math::Vector	GetLengthFromOriginToEnd() const { return m_end - m_origin; }

	//! �Փ˔���
	bool			IsHit( const BoundaryVolume* bv ) const;

	//! ���Ƃ̌�������
	bool			Check( const BVSphere* sphere ) const;

	//! �O�p�|���S���Ƃ̌�������
	bool			Check( const BVPolygon* poly ) const;

	//! �������ʂƂ̌�������
	bool			Check( const BVInfiniteFace* face ) const;

private:
	//	�f�[�^
	//---------------------------------------
	math::Vector	m_origin;		//!< �n�_
	math::Vector	m_end;			//!< �I�_

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
	 BVRay();
	~BVRay();

};





//=============================================================================
/*!
								�O�p�|���S���N���X
		�����v��肪�\
*/
//=============================================================================
class BVPolygon : public BoundaryVolume {
public:
	//!	�Z�b�g
	void			Init(const math::Vector&, const math::Vector&, const math::Vector&);	

	//!	���_���擾
	math::Vector	GetPoint(s32 i) const;

	//! �@�����K��
	math::Vector	GetNormal() const;

	//! �Փ˔���
	bool			IsHit(const BoundaryVolume* bv) const;

	//! �����Ƃ̏Փ˔���
	bool			Check(const BVRay* ray) const;

private:
	//	�f�[�^
	//---------------------------------------
	math::Vector	m_pos[3];	//!< ���_
	math::Vector	m_normal;	//!< �@��

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
	 BVPolygon();
	 BVPolygon(const math::Vector&, const math::Vector&, const math::Vector&);
	~BVPolygon();

};




//=============================================================================
/*!
								�������ʃN���X
		
		�f�t�H���g�Ŗ@��(0,1,0)��XZ����
*/
//=============================================================================
class BVInfiniteFace : public BoundaryVolume {
public:
	//!	�Z�b�g
	void			Init(const nk::math::Vector& pos, const math::Vector& n);

	//!	�@�����擾
	math::Vector	GetNormal() const { return m_normal; }

	//! ��_���K��
	math::Vector	GetPos() const { return m_pos; }

	//! �Փ˔���
	bool			IsHit(const BoundaryVolume* bv) const;

	//! ���Ƃ̏Փ˔���
	bool			Check(const BVSphere* sphere) const;

	//! �����Ƃ̌�������
	bool			Check(const BVRay* ray) const;

private:
	//	�f�[�^
	//---------------------------------------
	math::Vector	m_normal;		//!< ���K���ς݂̖@��
	math::Vector	m_pos;			//!< �ʒu

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
	 BVInfiniteFace();
	 BVInfiniteFace(const nk::math::Vector& pos, const math::Vector& n);
	~BVInfiniteFace();
};
#if 0
class BVInfiniteFace : public BoundaryVolume {
public:
	//!	�Z�b�g
	void Init(const math::Vector& norm, f32 move);	
	
	//!	�@�����擾
	math::Vector GetNormal() const { return m_normal; }

	//! ���_����̈ړ��ʂ��K��
	f32 GetMoveAmount() const { return m_d; }
	
private:
	//	�f�[�^
	//---------------------------------------
	math::Vector		m_normal;		//!< �m�[�}���C�Y�ς݂̖@��
	f32				m_d;			//!< ���_����@�������ւ̈ړ���

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
	 BVInfiniteFace();
	 BVInfiniteFace(const math::Vector& norm, f32 move);
	~BVInfiniteFace();
};
#endif


//! ���Ƌ��̃q�b�g����
bool	IsHitSphereSphere( const BVSphere* s1, const BVSphere* s2 );

//! ���Ɛ����̃q�b�g����
bool	IsHitSphereRay( const BVSphere* s, const BVRay* r );

//! �����ƎO�p�|���S��
bool	IsHitRayPolygon( const BVRay* ray, const BVPolygon* poly );

//! �����Ɩ�������
bool	IsHitRayInfFace( const BVRay* ray, const BVInfiniteFace* face );

//! ���Ɩ�������
bool	IsHitSphereInfFace( const BVSphere* s, const BVInfiniteFace* face );

//! �O�p�`�̓��O����
bool	IsPointInTriangle( const BVPolygon* face, const math::Vector& point );


//! �_���畽�ʂ܂ł̋��������߂�
f32		CalcDistanceFromPointToFace( const math::Vector& point, const BVInfiniteFace* face );

//! �����Ƌ��̌�_���v�Z
s32		CalcIntersectionPoint( nk::math::Vector* out, const BVSphere* sphere, const BVRay* ray );
// s32		CalcIntersectionPoint( nk::math::Vector* out1, nk::math::Vector* out2, const BVSphere* sphere, const BVRay* ray );
	
#if 0
/* �����Ă��鋅�Ɩ������� */
bool IsHit(const BVSphere* s, const math::Vector& move, const BVInfiniteFace* face);
#endif

/* �����Ă鋅�ƎO�p�|���S�� */

/* �O�p�`�̍ŋߐږ� */

}	// namespace nk


#endif  // __BOUNDARYVOLUME_H__