//=============================================================================
/*!	@file	drawmanager.h

	@brief	�`��Ǘ��N���X

	@author	��� ���V��
	@date	2011/11/17
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __DRAWMANAGER_H__
#define __DRAWMANAGER_H__


//-------------------------------�C���N���[�h-------------------------------
#include <list>
#include "./drawpacket.h"
#include "../shader/shader.h"
#include "../resource/renderableTexture.h"



namespace nk {

class Main;

namespace graphics {

//=============================================================================
/*!
								�`��g���@�\
*/
//=============================================================================
class Extension {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	virtual void		Proc();		//!< �X�V����
	
private:
	//----------------------�����o�ϐ�-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 Extension();
	virtual ~Extension();
};


//=============================================================================
/*!
								�`��Ǘ��N���X
*/
//=============================================================================
class RenderManager {
private:
#if 0
	struct ScreenTexId {
		s32				screenId;
		RenderTexId		texId;
	};
	typedef std::vector<ScreenTexId>	VecScreenId;

#endif

public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	//! ������
	bool	Initialize( void );

	//! �`��I�u�W�F�N�g��ǉ�
// 	void	Add( const DrawPacket& packet );
	void	Add( const DrawPacket* packet );

	//! �`��O������ǉ�(�V���h�E�}�b�v�����Ȃ�)
	//void	AddDrawTextureList(const DrawPacket& pacet);

	//! �`��
	void	Draw( Main* mainclass );

	//! �V�F�[�_�[�����[�h
	void	LoadShader( Shader* shader, std::string file, std::string name );

	//!	�V�F�[�_�[���폜
	void	DeleteShader();

#if 0
	//! �`��X�N���[������
	void	CreateRenderScreen( Main* mainclass, s32 screenId );

	//! �X�N���[��ID����e�N�X�`��ID���擾
	RenderTexId GetTextureId( s32 screenId );

#endif
private:

	//! �I�u�W�F�N�g�ʂ̕`��
	void	Draw( Main* mainclass, const DrawPacket* packet );


private:
	//----------------------�����o�ϐ�-----------------------
	std::list<const DrawPacket*>		m_drawPacketList;		//!< �`��p�P�b�g���X�g
	//std::list<DrawPacket>		m_drawTextureList;		//!< �e�N�X�`���`�惊�X�g
	ShaderManager*				m_shaderMng;			//!< �V�F�[�_�[�Ǘ�
	Extension*					m_extension;			//!< �g���@�\
	const resource::Texture*	m_prevUseTexture;		//!< �O��̕`��Ŏg�p�����e�N�X�`��
	
#if 0
	VecScreenId					m_vecScreenId;			//!< �X�N���[��ID

#endif
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 RenderManager();
	~RenderManager();
};



}	// namespace graphics
}	// namespace nk



#endif  // __DRAWMANAGER_H__