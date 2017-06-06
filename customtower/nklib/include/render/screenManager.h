//=============================================================================
/*!	@file	screen.h

	@brief	�X�N���[��

	@author	ryunosuke ide
	@date	2012.06.23
*/
//=============================================================================

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "../resource/renderableTexture.h"
#include "../resource/texture.h"

namespace nk {

//=============================================================================
/*!
						�`��X�N���[��
*/
//=============================================================================
class ScreenManager {
private:
	struct ScreenTexId {
		s32					screenId;
		RenderTexId			texId;
		u32					width;
		u32					height;
		resource::Texture*	texture;
	};
	typedef std::vector<ScreenTexId>	VecScreenId;

public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//!	�`��X�N���[������
	void			CreateScreen( u32 width, u32 height, s32 screenId );

	
	//!	�X�N���[��ID����e�N�X�`��ID���擾
	RenderTexId		GetTextureId( s32 screenId ) const;


	//! �e�N�X�`�����K��
	resource::Texture*	GetTexture( s32 screenId ) const;


	//!	�w�肵���X�N���[�����E�C���h�E�ɓ\��t����
	void			BindWindow( s32 screenId );


	//!	�w�肵���X�N���[���̓��e���N���A
	void			ClearScreen( s32 screenId );
	

	//!	�X�N���[���̓��e��`��
	void			Draw( s32 screenId );
	
	
protected:
	//----------------------�����o�ϐ�-----------------------
	VecScreenId		m_vecScreenId;			//!< �X�N���[��ID
	
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			ScreenManager();
	virtual~ScreenManager();
};


}	// namespace nk

#endif  // __SCREEN_H__