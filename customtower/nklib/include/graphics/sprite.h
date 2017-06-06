//=============================================================================
/*!	@file	sprite.h

	@brief	�X�v���C�g

	@author	��� ���V��
	@date	2011/11/18
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __SPRITE_H__
#define __SPRITE_H__


//-------------------------------�C���N���[�h-------------------------------
#include <string>
#include <list>
#include "../general.h"
#include "../resource/texture.h"
#include "../math/vector.h"
#include "./color.h"
#include "../resource/resourcemanager.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"
#include "../render/renderModel.h"

namespace nk {
namespace graphics {

//=============================================================================
/*!
								�X�v���C�g�N���X
*/
//=============================================================================
class Sprite : public RenderModel {
public:
	//-----------------------�^��`--------------------------
	enum {
		BILLBOARD	= BIT_SHIFT_LEFT(0),	//!< �r���{�[�h
		VIEW		= BIT_SHIFT_LEFT(1),	//!< �`��
		DEAPTH_ON	= BIT_SHIFT_LEFT(2),	//!< �f�v�X�L��
		Z_BUFFER	= BIT_SHIFT_LEFT(3),	//!< Z�o�b�t�@
		SRC_ALPHA	= BIT_SHIFT_LEFT(4),	//!< ���Z����
	};
	typedef u32 DRAW_MODE;
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ������
	void			Init( const std::string& name );

	//! �`��
	virtual void	Draw( const math::Vector& pos );

	//! �N���b�v�ݒ�(0.0�`1.0)
	void			SetUVWH( f32 u, f32 v, f32 w, f32 h );

	//! �X�P�[����ݒ�
	void			SetScale( const math::Vector& scale );
	void			SetScale( f32 x, f32 y );
	void			SetScale( f32 scale );


	//! ��]�ʂ�ݒ�
	void			SetRotate( f32 rotate );

	//! �F���Z�b�g
	void			SetColor( const Color& color );

	//! �A���t�@�l��ݒ�
	void			SetAlpha( f32 alpha );
	void			AddAlpha( f32 alpha );

	//! �`��ݒ�
	void			SetDrawMode( DRAW_MODE mode );		//!< �ݒ�
	void			RemoveDrawMode( DRAW_MODE mode );		//!< ����

	//! �e�N�X�`����ݒ�
	void			SetTexture( resource::Texture* tex );

	//! �e�N�X�`���擾
	const resource::Texture*	GetTexture( void ) const;
protected:
	//! �`��
	void			_Draw( const math::Vector& pos );
	
protected:
	//----------------------�����o�ϐ�-----------------------
	const resource::Texture*	m_texture;	//!< �e�N�X�`��
	math::Vector				m_uv;		//!< UV
	math::Vector				m_wh;		//!< WH
	math::Vector				m_scale;	//!< �X�P�[��
	Color						m_color;	//!< �F
	f32							m_rotate;	//!< ��]��
	DRAW_MODE					m_drawMode;	//!< �`�惂�[�h
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 Sprite();
	~Sprite();
};

}	// namespace graphics
}	// namespace nk




#endif	// __SPRITE_H__
