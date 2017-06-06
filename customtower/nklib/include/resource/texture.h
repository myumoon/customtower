//=============================================================================
/*!	@file	texture.h

	@brief	�e�N�X�`���N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __TEXTURE_H__
#define __TEXTURE_H__


//-------------------------------�C���N���[�h-------------------------------
#include <stdio.h>
#include <string>
#include "../typedef.h"
#include "textureUtility.h"

namespace nk {
namespace resource {



//=============================================================================
/*!
								�e�N�X�`���N���X
*/
//=============================================================================
class Texture {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! �T�[�t�F�C�X�̓o�^
	void			Register( ImageSurface surface );

	//! �e�N�X�`����
	void			SetTexName( const char* name );
	void			SetTexName( std::string name );
	std::string		GetTexName() const;

	//! ID
	void			SetID(u32 id);
	u32				GetID() const;
	const u32*		GetIDPointer() const;

	//! �T�C�Y
	void			SetSize(s32 w, s32 h);
	s32				GetWidth() const;
	s32				GetHeight() const;

	
	
private:
	//----------------------�����o�ϐ�-----------------------
	std::string			m_texName;		//!< �e�N�X�`����
	u32					m_id;			//!< �e�N�X�`��ID
	s32					m_width;		//!< ��
	s32					m_height;		//!< ����
	ImageSurface		m_surface;		//!< �T�[�t�F�C�X
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 Texture();
	virtual ~Texture();

private:
	//! �f�X�g���N�^�Ńe�N�X�`�����J�����邽�߃R�s�[���֎~����
	Texture(const Texture& tex);			// �錾����
	void operator =(const Texture& tex);	// �錾����
};


	
//=============================================================================
/*!	@brief		�e�N�X�`���\��t��
	@param		�o�C���h����e�N�X�`��
*/
//=============================================================================
extern void			BindTexture( const Texture* tex );


//=============================================================================
/*!	@brief		�T�[�t�F�C�X����e�N�X�`���𐶐�
*/
//=============================================================================
extern Texture*		CreateTexture( ImageSurface src );
	

//=============================================================================
/*!	@brief		�t�@�C������e�N�X�`���𐶐�
	@attention	���C���X���b�h�ȊO�ŌĂԏꍇ�͂�CreateTexture(ImageSurface)���g�p���Ă��������B
*/
//=============================================================================
extern Texture*		CreateTexture( const char* filaname );


//=============================================================================
/*!	@brief		��̃e�N�X�`���𐶐�
	@param		width	��
	@param		height	����
	@attention	���C���X���b�h�ȊO�ŌĂԂ��Ƃ͂ł��܂���
*/
//=============================================================================
extern Texture*		CreateEmptyTexture( s32 width, s32 height );


	
#if 0
Texture*	CreateTexture(std::string fileName)
	
/*! �e�N�X�`�����g�p */


/*! ��̃e�N�X�`�����쐬 */
Texture*	CreateEmptyTexture(s32 width, s32 height);
#endif
}	// namespace resource
}	// namespace nk














#endif















































