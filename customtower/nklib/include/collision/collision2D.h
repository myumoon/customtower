//=============================================================================
/*!	@file	collision2D.h

	@brief	2D�q�b�g����

	@author	ryunosuke ide
	@date	2013.06.13
*/
//=============================================================================

#ifndef __COLLISION2D_H__
#define __COLLISION2D_H__

#include "../math/vector.h"



namespace nk {


//=============================================================================
/*!
						2D�q�b�g���胆�[�e�B���e�B�[
*/
//=============================================================================
class Collision2D {
public:
	//-----------------------�^��`--------------------------

	//! ���W
	struct Point {
		s32		x;		//!< X���W
		s32		y;		//!< Y���W

		Point() {
			this->x	= 0;
			this->y	= 0;
		}

		Point( const math::Vector& rhs ) {
			this->x	= static_cast<s32>(rhs.x);
			this->y	= static_cast<s32>(rhs.y);
		}
	};
	
	//! ��`
	struct Rect {
		Point	pos;	//!< ���W
		s32		w;		//!< ��
		s32		h;		//!< ����

		Rect() {
			this->w	= 0;
			this->h	= 0;
		}

		Rect( const Point& pos, s32 w, s32 h ) {
			this->pos	= pos;
			this->w		= w;
			this->h		= h;
		}

		Rect( const math::Vector& pos, const math::Vector& size ) {
			this->pos.x	= static_cast<s32>(pos.x);
			this->pos.y	= static_cast<s32>(pos.y);
			this->w		= static_cast<s32>(size.x);
			this->h		= static_cast<s32>(size.y);
		}
	};

	//! �~
	struct Circle {
		Point	pos;	//!< ���W
		s32		r;		//!< ���a
	};

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		��`���m
	*/
	//===========================================================================
	static bool		IsHit( const Rect& lhs, const Rect& rhs );

	//===========================================================================
	/*!	@brief		��`�Ɠ_
	*/
	//===========================================================================
	static bool		IsHit( const Rect& lhs, const Point& rhs );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Collision2D();
	virtual~Collision2D();
};

	
}	// namespace nk



#endif  // __COLLISION2D_H__