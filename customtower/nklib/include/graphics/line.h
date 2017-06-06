//=============================================================================
/*!	@file	line.h

	@brief	��

	@author	��� ���V��
	@date	2013/02/11
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __LINE_H__
#define __LINE_H__


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
								���C���N���X
*/
//=============================================================================
class Line : public RenderModel {
public:
	//-----------------------�^��`--------------------------
	enum RENDER_MODE {
		RENDER_MODE_2D,
		RENDER_MODE_3D,
	};
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! �`��
	virtual void		Draw( const math::Vector& pos = math::Vector() );

	//! �_��ǉ�
	void				AddPoint( const math::Vector& pos );
	void				ClearPoints( void );

	//! �F���Z�b�g
	void				SetColor( const Color& color );

	//! �A���t�@�l��ݒ�
	void				SetAlpha( f32 alpha );
	void				AddAlpha( f32 alpha );

	//! 2D, 3D �ݒ�
	void				SetRenderMode( RENDER_MODE mode );


private:
	//----------------------�����o�ϐ�-----------------------
	Color						m_color;	//!< �F
	resource::Vertex			m_points;	//!< �`��_
	RENDER_MODE					m_mode;		//!< �����_�����O���[�h
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 Line();
	~Line();
};

}	// namespace graphics
}	// namespace nk




#endif	// __LINE_H__
