//=============================================================================
/*!	@file	resourcemanager.h

	@brief	���\�[�X�Ǘ��N���X

	@author	��� ���V��
	@date	2011/11/18
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __RESOUREMANAGER_H__
#define __RESOUREMANAGER_H__

//-------------------------------�C���N���[�h-------------------------------
#include <string>
#include <vector>
#include <map>
#include "./texture.h"
#include "./material.h"
#include "./vertex.h"
#include "./face.h"
#include "../file/xfile.h"
#include "../file/toyFile.h"
#include "../file/mqoFile.h"
//#include "../file/csv.h"

namespace nk {
namespace resource {

//=============================================================================
/*!
								���\�[�X�Ǘ��N���X
*/
//=============================================================================
class ResourceManager {
private:
	//-----------------------�^��`--------------------------
	typedef std::map<std::string, Vertex>		VertexMap;		//!< ���_�Ɩ��O
	typedef std::map<std::string, Face>			FaceMap;		//!< �ʂƖ��O
	typedef std::map<std::string, Material>		MaterialMap;	//!< �}�e���A���Ɩ��O
	typedef std::vector<const Texture*>			TextureAry;		//!< �e�N�X�`���z��
	typedef std::vector<const XFile*>			XFileAry;		//!< X�t�@�C���z��
	typedef std::vector<const ToyFile*>			ToyFileAry;		//!< ToyStudio�t�@�C���z��
	typedef std::vector<const MqoFile*>			MqoFileAry;		//!< mqo�t�@�C���z��
	//typedef std::vector<const Csv::DataTable*>	CsvAry;			//!< csv
public:

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//! �t�@�C���̈ꊇ���[�h(txt�`��)
	void			LoadAllFile( std::string loadPath );

	//! �t�@�C���̃��[�h(�t�@�C������)
	void			LoadFile( std::string loadFilePath );

	//! �e�N�X�`���ǉ�
	void			Register( Texture* tex );
	
	//! ���_���擾
	//Vertex			GetVertex(std::string name);

	//! �ʂ��擾
	//Face			GetFace(std::string name);

	//! �}�e���A�����擾
	//Material		GetMaterial(std::string name);

	//! �e�N�X�`�����擾
	const Texture*	GetTexture(std::string name);

	//! X�t�@�C�����擾
	const XFile*	GetXFile(std::string name);

	//! ToyFile���擾
	const ToyFile*	GetToyFile(std::string name);

	//! mqo�t�@�C�����K��
	const MqoFile*	GetMqoFile(std::string name);

	//! csv�t�@�C�����擾
	//const Csv*		GetCsv( std::string name );
	
private:
	//----------------------�����o�ϐ�-----------------------
	VertexMap		m_vertexAry;	//!< ���_�Ǘ��z��
	FaceMap			m_faceAry;		//!< �ʊǗ��z��
	MaterialMap		m_materialAry;	//!< �}�e���A���Ǘ��z��
	TextureAry		m_textureAry;	//!< �e�N�X�`���Ǘ��z��
	XFileAry		m_xfileAry;		//!< X�t�@�C���Ǘ��z��
	ToyFileAry		m_toyfileAry;	//!< ToyStudio�Ǘ��z��
	MqoFileAry		m_mqofileAry;	//!< mqo�t�@�C���Ǘ��z��
	//CsvAry			m_csvAry;		//!< csv

	

	//-----------------------���\�b�h------------------------
	//! �e�N�X�`�����J��
	void	_DeleteTexture();

	//! X�t�@�C�������
	void	_DeleteXFile();

	//! ToyStudio�t�@�C�����J��
	void	_DeleteToyFile();

	//! mqo�t�@�C�����J��
	void	_DeleteMqoFile();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 ResourceManager();
	~ResourceManager();
};


}	// namespace resource
}	// namespace nk







#endif  // __RESOUREMANAGER_H__