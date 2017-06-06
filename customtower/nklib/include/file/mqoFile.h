//=============================================================================
/*!	@file	mqoModel.h

	@brief	mqo���f���N���X

	@author	��� ���V��
	@date	2012/02/21
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __MQOFILE_H__
#define __MQOFILE_H__


//-------------------------------�C���N���[�h-------------------------------
#include <string.h>
#include "../resource/vertex.h"
#include "../resource/material.h"
#include "../resource/face.h"
#include "../graphics/color.h"


namespace nk {
namespace resource {

class ResourceManager;
class LoadMqoFile;

//=============================================================================
/*!
								mqo�t�@�C���N���X
*/
//=============================================================================
class MqoFile {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! �t�@�C�������Z�b�g
	void			SetFileName(std::string name);

	//! �t�@�C�������K��
	std::string		GetFileName() const;

	//! ���_�f�[�^�̒ǉ�
	void			AddVertex(const math::Vector& pos);

	//! ���_�f�[�^�̏K��
	const Vertex&	GetVertex() const;

	//! �ʃf�[�^�̒ǉ�
	void			AddFace(u32 index, const math::Vector& uv);

	//! �ʃf�[�^�̏K��
	const Face&		GetFace() const;

	//! �@���f�[�^�̏K��
	const Vertex&	GetNormalVertex() const;

	//! �}�e���A���̃Z�b�g
	void			SetMaterial(const Material& material);

	//! �}�e���A���̏K��
	Material		GetMaterial() const;
	
	
private:
	//----------------------�����o�ϐ�-----------------------
	std::string			m_name;		//!< �t�@�C����
	Vertex				m_vertex;	//!< ���_�f�[�^
	Face				m_face;		//!< �ʃf�[�^
	Material			m_material;	//!< �}�e���A��
	Vertex				m_normal;	//!< �@���f�[�^
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 MqoFile(const LoadMqoFile& file);
			 MqoFile();
	virtual ~MqoFile();
};


//=============================================================================
/*!
								mqo���[�h�N���X
*/
//=============================================================================
class LoadMqoFile {
public:
	friend class MqoFile;
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	static void	SetResourceManager(ResourceManager* mng) { m_resourceMng = mng; }
	
	
private:
	//----------------------�����o�ϐ�-----------------------
	static	resource::ResourceManager*	m_resourceMng;	//!< ���\�[�X�Ǘ�
	Vertex								m_vertex;		//!< ���_�f�[�^
	Material							m_material;		//!< �}�e���A��
	Face								m_face;			//!< �ʃf�[�^
	std::string							m_path;			//!< �t�@�C���p�X
	Vertex								m_normal;		//!< �@���f�[�^
	
	//-----------------------���\�b�h------------------------
	 LoadMqoFile() { }	// ���̃R���X�g���N�^�͎g�p�s�ɂ���
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 LoadMqoFile(std::string path);
	~LoadMqoFile();
};


}	// namespace resource
}	// namespace nk


#endif	// __MQOFILE_H__