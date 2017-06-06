//=============================================================================
/*!	@file	xfile.h

	@brief	X�t�@�C��������

	@author	��� ���V��
	@date	2011/11/23
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


#ifndef __XFILE_H__
#define __XFILE_H__

//-------------------------------�C���N���[�h-------------------------------
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../math/matrix.h"
#include "../resource/vertex.h"
#include "../resource/face.h"
#include "../resource/material.h"


namespace nk {
namespace resource {

//---------------------------------�O���錾---------------------------------
class ResourceManager;

//=============================================================================
/*!
								X�t�@�C���N���X
*/
//=============================================================================
class XFile {
private:
public:
	//-----------------------�^��`--------------------------
	struct _ObjAnimation;
	typedef std::vector<_ObjAnimation> ObjAnimAry;	// �I�u�W�F�N�g�A�j���[�V�����z��^
	
	// ���f���I�u�W�F�N�g
	struct _ModelObject {
		std::string			name;			// �I�u�W�F�N�g��
		resource::Vertex	vertex;			// ���_
		resource::Face		face;			// ��
		resource::Vertex	normalVertex;	// �ʖ@��
		resource::Face		normalFace;		// �ʖ@���̃C���f�b�N�X
		resource::Material	material;		// �}�e���A��
	};

	// �A�j���[�V����
	struct _Animation {
		std::string					objName;	// �Ή�����I�u�W�F�N�g��
		std::vector<math::Matrix44>	matrix;		// �A�j���[�V�����s��
	};

	// ���f���A�j���[�V����
	struct _ObjAnimation {
		_ModelObject	object;		// �I�u�W�F�N�g
		_Animation		animation;	// �A�j���[�V����
	};
	
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! �I�u�W�F�N�g�A�j���[�V������ǉ�
	void		AddObjectAnimation( const _ObjAnimation& obj );

	//! �A�j���[�V������ǉ�
	void		AddAnimation( const _Animation& anim, std::string name );

	//! �t�@�C�������擾
	std::string	GetName() const;

	//! ���[�v�񐔂��擾
	u32		GetSize() const;

	//! �I�u�W�F�N�g�\���̂��擾
	const _ModelObject&	GetModelObject( u32 index ) const;

	//! �A�j���[�V�����\���̂��擾
	const _Animation&	GetAnimation( u32 index ) const;


	//! ���\�[�X�Ǘ��N���X��o�^
	static void	SetResourceManager( ResourceManager* mng );
	
	// ��������Ƃ��̓����o�����J����
	friend XFile* CreateXFile( std::string path );
	
private:
	//----------------------�����o�ϐ�-----------------------
	ObjAnimAry		m_objAnimAry;	//!< �I�u�W�F�N�g�A�j���[�V�����z��
	std::string		m_name;			//!< �t�@�C����
	
	static ResourceManager*	m_resourceMng;	//!< ���\�[�X�Ǘ�
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 XFile();
	~XFile();
};


//! X�t�@�C�������[�h
XFile* CreateXFile( std::string path );

//! �����񂩂璸�_���擾
math::Vector GetVertexFromString();

}	// namespace resource
}	// namespace nk



#endif  // __XFILE_H__