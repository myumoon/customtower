//=============================================================================
/*!	@file	geometry.h

	@brief	}Œ`

	@author	ryunosuke ide
	@date	2013.03.24
*/
//=============================================================================


#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "../typedef.h"

namespace nk {

namespace graphics {


struct Rect2D {
	f32		x;
	f32		y;
	f32		w;
	f32		h;

	Rect2D() {
		this->x	= 0;
		this->y	= 0;
		this->w	= 0;
		this->h	= 0;
	}
};

}	// namespace graphics
}	// namespace nk







#endif  // __GEOMETRY_H__