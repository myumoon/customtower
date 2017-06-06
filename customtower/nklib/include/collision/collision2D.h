//=============================================================================
/*!	@file	collision2D.h

	@brief	2Dヒット処理

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
						2Dヒット判定ユーティリティー
*/
//=============================================================================
class Collision2D {
public:
	//-----------------------型定義--------------------------

	//! 座標
	struct Point {
		s32		x;		//!< X座標
		s32		y;		//!< Y座標

		Point() {
			this->x	= 0;
			this->y	= 0;
		}

		Point( const math::Vector& rhs ) {
			this->x	= static_cast<s32>(rhs.x);
			this->y	= static_cast<s32>(rhs.y);
		}
	};
	
	//! 矩形
	struct Rect {
		Point	pos;	//!< 座標
		s32		w;		//!< 幅
		s32		h;		//!< 高さ

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

	//! 円
	struct Circle {
		Point	pos;	//!< 座標
		s32		r;		//!< 半径
	};

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		矩形同士
	*/
	//===========================================================================
	static bool		IsHit( const Rect& lhs, const Rect& rhs );

	//===========================================================================
	/*!	@brief		矩形と点
	*/
	//===========================================================================
	static bool		IsHit( const Rect& lhs, const Point& rhs );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			Collision2D();
	virtual~Collision2D();
};

	
}	// namespace nk



#endif  // __COLLISION2D_H__