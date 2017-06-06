//=============================================================================
/*!	@file	interpolation.h

	@brief	���

	@author	ryunosuke ide
	@date	2013.07.20
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/math/interpolation.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {
namespace math {

//===========================================================================
/*!	@brief		CatmullROm�X�v���C���Ȑ��v�Z
	@param		prev	���O�ʒu
	@param		x0		�ʒu0
	@param		x1		�ʒu1
	@param		next	���̈ʒu
	@param		t		��Ԉʒu(0.0�`1.0)
	@return		----
*/
//===========================================================================
f32 InterpolationCatmullRom( f32 prev, f32 x0, f32 x1, f32 next, f32 t )
{
	const f32	vec0	= (x1 - prev) / 2.0f;
	const f32	vec1	= (next - x0) / 2.0f;
	const f32	t2		= t * t;
	const f32	t3		= t2 * t;
	const f32	x		= (2 * x0 - 2 * x1 + vec0 + vec1) * t3 + (-3 * x0 + 3 * x1 - 2 * vec0 - vec1) * t2 + (vec0) * t + x0;
	
	return x;
}


//===========================================================================
/*!	@brief		CatmullROm�X�v���C���Ȑ��v�Z
	@param		prev	���O�ʒu
	@param		x0		�ʒu0
	@param		x1		�ʒu1
	@param		next	���̈ʒu
	@param		t		��Ԉʒu(0.0�`1.0)
	@return		----
*/
//===========================================================================
Vector InterpolationCatmullRom(
	const nk::math::Vector&	prev,
	const nk::math::Vector&	x0,
	const nk::math::Vector&	x1,
	const nk::math::Vector&	next,
	f32						t
)
{
	Vector	pos;

	pos.x	= InterpolationCatmullRom( prev.x, x0.x, x1.x, next.x, t );
	pos.y	= InterpolationCatmullRom( prev.y, x0.y, x1.y, next.y, t );
	
	return pos;
}
	
}	// namespace math
}	// namespace nk