//=============================================================================
/*!	\file	renderManager.h

	\brief	�`��Ǘ��N���X

	\author	��� ���V��
	\date	2011/11/17
	\todo	�Ȃ�
	\bug	�Ȃ�
*/
//=============================================================================


#ifndef __RENDERMANAGER_H__
#define __RENDERMANAGER_H__


//-------------------------------�C���N���[�h-------------------------------
#include <list>
#include "./drawpacket.h"
#include "../shader/shader.h"



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
class DrawManager {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! �`��I�u�W�F�N�g��ǉ�
	void	Add( const DrawPacket& packet );

	//! �`��O������ǉ�(�V���h�E�}�b�v�����Ȃ�)
	//void	AddDrawTextureList(const DrawPacket& pacet);

	//! �`��
	void	Draw( Main* mainclass );

	//! �V�F�[�_�[�����[�h
	void	LoadShader( Shader* shader, std::string file, std::string name );

	// �V�F�[�_�[���폜
	void	DeleteShader();

private:

	//! �I�u�W�F�N�g�ʂ̕`��
	void	Draw( Main* mainclass, const DrawPacket& packet );


private:
	//----------------------�����o�ϐ�-----------------------
	std::list<DrawPacket>		m_drawPacketList;		//!< �`��p�P�b�g���X�g
	//std::list<DrawPacket>		m_drawTextureList;		//!< �e�N�X�`���`�惊�X�g
	ShaderManager*				m_shaderMng;			//!< �V�F�[�_�[�Ǘ�
	Extension*					m_extension;			//!< �g���@�\
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 DrawManager();
	~DrawManager();
};



}	// namespace graphics
}	// namespace nk



#endif  // __RENDERMANAGER_H__