//=============================================================================
/*!	@file	interpolation.h

	@brief	補間

	@author	ryunosuke ide
	@date	2013.07.20
*/
//=============================================================================


#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__

#include "vector.h"

namespace nk {
namespace math {


//===========================================================================
/*!	@brief		CatmullRomスプライン曲線
	@param		t	0.0～1.0
*/
//===========================================================================
f32		InterpolationCatmullRom( f32 prev, f32 x0, f32 x1, f32 next, f32 t );


//===========================================================================
/*!	@brief		CatmullRomスプライン曲線
	@param		t	0.0～1.0
*/
//===========================================================================
Vector	InterpolationCatmullRom(
	const nk::math::Vector&	prev,
	const nk::math::Vector&	x0,
	const nk::math::Vector&	x1,
	const nk::math::Vector&	next,
	f32						t
);
	
}	// namespace math
}	// namespace nk






#endif  // __INTERPOLATION_H__