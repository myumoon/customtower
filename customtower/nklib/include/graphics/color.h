//=============================================================================
/*!	@file	color.h

	@brief	色情報

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __COLOR_H__
#define __COLOR_H__

#include "../typedef.h"
#include "../math/math.h"


namespace nk {


//=============================================================================
/*!
								色
*/
//=============================================================================
struct Color {

	//! 色の種類
	enum TYPE {
		TYPE_R,
		TYPE_G,
		TYPE_B,
		TYPE_A,
		TYPE_MAX,
	};

	struct RGBA {
		u8	rgba[TYPE_MAX];
	};
	
	//----------------------メンバ変数-----------------------
	//! RGBA
	union {
		RGBA	rgba8x4;
		u32		rgba32;
		
		struct {
#if 1
			u8	r, g, b, a;
#else
			u8	a, b, g, r;
#endif
		};
	};
	
	//-----------------------メソッド------------------------
	
	//===========================================================================
	/*!	@brief		floatで取得
	*/
	//===========================================================================
	f32		Float( TYPE colorType ) const {
		return (U8( colorType ) / 255.0f);
	}

	//===========================================================================
	/*!	@brief		U8で取得
	*/
	//===========================================================================
	u8		U8( TYPE colorType ) const {
		return rgba8x4.rgba[colorType];
	}
	
	
	//-------------コンストラクタ・デストラクタ--------------
	//! コンストラクタ
	Color( void ) {
		this->rgba32	= 0xFFFFFFFF;	// 白
	}

	//! コンストラクタ
	Color( f32 r, f32 g, f32 b, f32 a = 1.0f ) {
		this->rgba8x4	= FloatToRGBA( r, g, b, a );
	}

	//! コンストラクタ
	Color( u32 rgba ) {
		//! @todo エンディアン考慮しないといけないかも
		this->rgba32	= rgba;
	}

	//! コンストラクタ
	Color( u8 r, u8 g, u8 b, u8 a = 0xFF ) {
		this->r	= r;
		this->g	= g;
		this->b	= b;
		this->a	= a;
	}

	//! デストラクタ
	virtual~Color( void ) {
	}

protected:
	//===========================================================================
	/*!	@brief		float → RGBA
	*/
	//===========================================================================
	RGBA		FloatToRGBA( f32 r, f32 g, f32 b, f32 a ) {
		RGBA		ret;
		ret.rgba[TYPE_R]	= static_cast<u8>(math::Clamp( r, 0.0f, 1.0f ) * 0xFF);
		ret.rgba[TYPE_G]	= static_cast<u8>(math::Clamp( g, 0.0f, 1.0f ) * 0xFF);
		ret.rgba[TYPE_B]	= static_cast<u8>(math::Clamp( b, 0.0f, 1.0f ) * 0xFF);
		ret.rgba[TYPE_A]	= static_cast<u8>(math::Clamp( a, 0.0f, 1.0f ) * 0xFF);

		return ret;
	}

};


}	// namespace nk



#endif  // __COLOR_H__