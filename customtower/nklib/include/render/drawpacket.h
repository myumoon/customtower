//=============================================================================
/*!	@file	drawpacket.h

	@brief	�`��p�P�b�g�N���X

	@author	��� ���V��
	@date	2011/11/16
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __DRAWPACKET_H__
#define __DRAWPACKET_H__

//-------------------------------�C���N���[�h-------------------------------
#include "../resource/material.h"
#include "../resource/vertex.h"
#include "../resource/texture.h"
#include "../math/matrix.h"
#include "../resource/face.h"
#include "../general.h"



namespace nk {
namespace graphics {


class RenderManager;

//=============================================================================
/*!
								�`��p�P�b�g�N���X
*/
//=============================================================================
class DrawPacket {
public:
	friend	RenderManager;
	
	//-----------------------�^��`--------------------------
	enum {
		SPRITE_BILLBOARD	= BIT_SHIFT_LEFT(0),	//!< �r���{�[�h
		LINE3D				= BIT_SHIFT_LEFT(1),	//!< ��(3D)
		SPRITE				= BIT_SHIFT_LEFT(2),	//!< �X�v���C�g
		MODEL				= BIT_SHIFT_LEFT(3),	//!< ���f��
		MODEL_ANIMATION		= BIT_SHIFT_LEFT(4),	//!< �A�j���[�V�������f��
		LINE2D				= BIT_SHIFT_LEFT(5),	//!< ��(2D)
		
		DEAPTH_ON			= BIT_SHIFT_LEFT(5),	//!< �f�v�X�L��
		Z_BUFFER			= BIT_SHIFT_LEFT(6),	//!< Z�o�b�t�@
		SRC_ALPHA			= BIT_SHIFT_LEFT(7),	//!< ���Z����
	};
	typedef u32 DRAW_TYPE;

	//----------------------�ÓI�����o-----------------------
	static const u32	DEFAULT_PRIORITY;			//!< �f�t�H���g�`��D��x
	static const u32	DEFAULT_SPRITE_PRIORITY;	//!< �f�t�H���g�X�v���C�g�D��x
	static const u32	DEFAULT_LINE_PRIORITY;		//!< �f�t�H���g���D��x
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�N���A
	*/
	//===========================================================================
	void				Clear( void );
	
	/*! �e�N�X�`�����Z�b�g */
	//void				SetTexture(const resource::Texture* tex);

	/*! �e�N�X�`�����擾 */
	//const resource::Texture*	GetTexture( void ) const;

	//! �V�F�[�_�[�f�[�^���Z�b�g
	void				SetShaderData( const ShaderData& data );

	/*! �}�e���A�����Z�b�g */
	void				SetMaterial( const resource::Material& m );

	/*! �}�e���A�����擾 */
	resource::Material	GetMaterial( void ) const;

	/*! ���_���Z�b�g */
	void				SetVertex( const resource::Vertex& v );
	void				AddVertex( const math::Vector& v );
	void				AddVertex( f32 x, f32 y, f32 z );

	/*! ���_���擾 */
	resource::Vertex&		GetVertex( void );
	const resource::Vertex&	GetVertex( void ) const;

	/*! �ʂ��Z�b�g */
	void				SetFace( const resource::Face& face );
	void				AddFace( u32 index, const math::Vector& uv );
	void				AddFace( u32 index, f32 u, f32 v );

	/*! �ʂ��擾 */
	resource::Face&			GetFace( void );
	const resource::Face&	GetFace( void ) const;
	

	/*! ���_�@�����Z�b�g */
	void				SetNormalVertex( const resource::Vertex& n );

	/*! ���_�@�����K�� */
	resource::Vertex&	GetNormalVertex( void );
	
	/*! ���[���h�r���[�ϊ��s����Z�b�g */
	void				SetWorldViewTransform(const math::Matrix44& mat);

	/*! ���[���h�r���[�ϊ��s����擾 */
	const math::Matrix44&	GetWorldViewTransform( void ) const;
	math::Matrix44&			GetWorldViewTransform( void );

	/*! �`��^�C�v��ݒ� */
	void				SetDrawType( DRAW_TYPE type );

	/*! �`��p�P�b�g���}�l�[�W���ɑ��� */
// 	void				SendToDrawManager( void );

	//! �e�N�X�`���`�惊�X�g�ɓ]��
	//void				SendToDrawTextureList( void );

	//! �`��D��x��ݒ�
	void				SetPriority( u32 num );

	//! �`��D��x���K��
	u32					GetPriority( void ) const;

	//! �o�b�t�@�N���A�I�u�W�F�N�g��}��
// 	void				AddListForBufferClear( void );
// 
// 	bool				IsBufferClear( void ) const;

	//! �X�N���[��Id
	void				SetScreenId( s32 screenId )					{ m_screenId = screenId; 	}
	s32					GetScreenId( void ) const					{ return m_screenId;		}
	
	//! ���[���h�s��
	void				SetWorldMatrix( const math::Matrix44& m )	{ m_world = m;				}
	math::Matrix44		GetWorldMatrix( void ) const				{ return m_world;			}

private:
	//----------------------�����o�ϐ�-----------------------
	u32							m_priority;				//!< �`��D�揇��
	resource::Material			m_material;				//!< �}�e���A��
	resource::Vertex			m_vertex;				//!< ���_
	resource::Face				m_face;					//!< ��
	resource::Vertex			m_normal;				//!< ���_�@��
	math::Matrix44				m_worldViewTransform;	//!< ���[���h�ϊ��s��
	math::Matrix44				m_world;				//!< ���[���h�s��
	DRAW_TYPE					m_type;					//!< �`��^�C�v
	s32							m_screenId;				//!< �`��X�N���[��ID
	bool						m_isClearBuffer;		//!< �o�b�t�@�N���A�t���O

	static RenderManager*		m_drawManager;			//!< �`��}�l�[�W��

	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 DrawPacket( void );
	 //DrawPacket( const DrawPacket& pack );
	~DrawPacket( void );
};


}	// namespace draw
}	// namespace nk







#endif  // __DRAWPACKET_H__
