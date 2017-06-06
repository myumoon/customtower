//=============================================================================
/*!	@file	color.h

	@brief	�F���

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __COLOR_H__
#define __COLOR_H__

#include "../typedef.h"
#include "../math/math.h"


namespace nk {


//=============================================================================
/*!
								�F
*/
//=============================================================================
struct Color {

	//! �F�̎��
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
	
	//----------------------�����o�ϐ�-----------------------
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
	
	//-----------------------���\�b�h------------------------
	
	//===========================================================================
	/*!	@brief		float�Ŏ擾
	*/
	//===========================================================================
	f32		Float( TYPE colorType ) const {
		return (U8( colorType ) / 255.0f);
	}

	//===========================================================================
	/*!	@brief		U8�Ŏ擾
	*/
	//===========================================================================
	u8		U8( TYPE colorType ) const {
		return rgba8x4.rgba[colorType];
	}
	
	
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	//! �R���X�g���N�^
	Color( void ) {
		this->rgba32	= 0xFFFFFFFF;	// ��
	}

	//! �R���X�g���N�^
	Color( f32 r, f32 g, f32 b, f32 a = 1.0f ) {
		this->rgba8x4	= FloatToRGBA( r, g, b, a );
	}

	//! �R���X�g���N�^
	Color( u32 rgba ) {
		//! @todo �G���f�B�A���l�����Ȃ��Ƃ����Ȃ�����
		this->rgba32	= rgba;
	}

	//! �R���X�g���N�^
	Color( u8 r, u8 g, u8 b, u8 a = 0xFF ) {
		this->r	= r;
		this->g	= g;
		this->b	= b;
		this->a	= a;
	}

	//! �f�X�g���N�^
	virtual~Color( void ) {
	}

protected:
	//===========================================================================
	/*!	@brief		float �� RGBA
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