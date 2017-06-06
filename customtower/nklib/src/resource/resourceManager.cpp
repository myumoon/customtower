//=============================================================================
/*!	@file	resourcemanager.h

	@brief	���\�[�X�Ǘ��N���X

	@author	��� ���V��
	@date	2011/11/18
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include "../../include/resource/resourceManager.h"
#include "../../include/general.h"


namespace nk {
namespace resource {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
ResourceManager::ResourceManager()
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
ResourceManager::~ResourceManager()
{
	_DeleteTexture();
	_DeleteXFile();
	_DeleteToyFile();
	_DeleteMqoFile();
}


//===========================================================================
/*!	@brief	�t�@�C���̈ꊇ���[�h
	@param	�ꊇ���[�h���s���t�@�C����(txt)
	@return	�Ȃ�
*/
//===========================================================================
void ResourceManager::LoadAllFile(std::string loadpath)
{
	std::ifstream ifs(loadpath.c_str());

	ASSERT( ifs.fail() == false, "file list open error." );
	if( ifs.fail() ) {
		return;
	}

	while( !ifs.eof() ) {
		std::string line;
		ifs >> line;
		PRINTF( "%s\n", line.c_str() );

		/* �e�N�X�`���ǂݍ��� */
		if( strstr( line.c_str(), ".png" ) || 
			strstr( line.c_str(), ".jpg" ) ||
			strstr( line.c_str(), ".jpeg") ||
			strstr( line.c_str(), ".bmp" ) ) {
			

			Texture* tex = CreateTexture( line.c_str() );

			tex->SetTexName( line.c_str() );

			m_textureAry.push_back( tex );
		}

		/* ���f���ǂݍ��� */
		else if( strstr(line.c_str(), ".mqo") ) {
			MqoFile* mqo = new MqoFile( LoadMqoFile(line) );
			m_mqofileAry.push_back( mqo );
		}

		/* ToyStudio�Ő��삵���A�j���[�V�����̓ǂݍ��� */
		else if( strstr(line.c_str(), ".toy") ) {
			ToyFile* toy = new ToyFile(LoadToyFile(line.c_str()));
			m_toyfileAry.push_back(toy);
		}

		/* X�t�@�C���̓Ǎ��� */
		else if( strstr(line.c_str(), ".x") ) {
			m_xfileAry.push_back(CreateXFile(line.c_str()));
		}

		else if( strstr(line.c_str(), ".cgfx") ) {
			ASSERT( false, "cgfx" );
		}

		/* csv */
		else if( strstr(line.c_str(), ".csv") ) {
			//#error
		}
		
	}

}



//===========================================================================
/*!	@brief	�t�@�C���̃��[�h(�t�@�C������)
	@param	loadFilePath	�t�@�C���p�X
	@return	�Ȃ�
*/
//===========================================================================
void ResourceManager::LoadFile( std::string loadFilePath )
{
	/* �e�N�X�`���ǂݍ��� */
	if( strstr( loadFilePath.c_str(), ".png" ) || 
		strstr( loadFilePath.c_str(), ".jpg" ) ||
		strstr( loadFilePath.c_str(), ".bmp" ) ) {

		Texture* tex = CreateTexture( loadFilePath.c_str() );
		tex->SetTexName( loadFilePath );
		m_textureAry.push_back( tex );
	}

	/* ���f���ǂݍ��� */
	if( strstr( loadFilePath.c_str(), ".mqo" ) ) {
		MqoFile* mqo = new MqoFile( LoadMqoFile( loadFilePath ) );
		m_mqofileAry.push_back( mqo );
	}

	/* ToyStudio�Ő��삵���A�j���[�V�����̓ǂݍ��� */
	if( strstr( loadFilePath.c_str(), ".toy" ) ) {
		ToyFile* toy = new ToyFile( LoadToyFile( loadFilePath.c_str() ) );
		m_toyfileAry.push_back( toy );
	}

	/* X�t�@�C���̓Ǎ��� */
	if( strstr( loadFilePath.c_str(), ".x" ) ) {
		m_xfileAry.push_back( CreateXFile( loadFilePath.c_str() ) );
	}

	/* �V�F�[�_�[ */
	if( strstr( loadFilePath.c_str(), ".cgfx" ) ) {
	}

}


//===========================================================================
/*!	@brief	�e�N�X�`���̒ǉ�
	@param	----
	@return	----
*/
//===========================================================================
void ResourceManager::Register( Texture* tex )
{
	m_textureAry.push_back( tex );
}




//===========================================================================
/*!	@brief	���_���擾
	@param	���_�̖��O
	@return	���_�N���X
*/
//===========================================================================
//Vertex ResourceManager::GetVertex(std::string name)
//{
//	return m_vertexAry[name];
	//typedef std::map<std::string, Vertex> Map;
	//
	//Map::iterator itr = m_vertexAry.begin();
	//Map::iterator end = m_vertexAry.end();

	//for( ; itr != end; ++itr) {
	//	if( (*itr).first == name ) {
	//		return (*itr).second;
	//	}
	//}
	//
	//return Vertex();
//}


//===========================================================================
/*!	@brief	�ʂ��擾
	@param	�ʂ̖��O
	@return	�ʃN���X
*/
//===========================================================================
//Face ResourceManager::GetFace(std::string name)
//{
//	return m_faceAry[name];
//}


//===========================================================================
/*!	@brief	�}�e���A�����擾
	@param	�}�e���A���̖��O
	@return	�}�e���A���N���X
*/
//===========================================================================
//Material ResourceManager::GetMaterial(std::string name)
//{
//	return m_materialAry[name];
//}


//===========================================================================
/*!	@brief	�e�N�X�`�����擾
	@param	�e�N�X�`���̖��O
	@return	�e�N�X�`���N���X	null:������Ȃ������ꍇ
*/
//===========================================================================
const Texture* ResourceManager::GetTexture(std::string name)
{
	TextureAry::iterator itr = m_textureAry.begin();
	TextureAry::iterator end = m_textureAry.end();
	for( ; itr != end; ++itr) {
		if( (*itr)->GetTexName() == name ) {
			return *itr;
		}
	}

	return NULL;		// ���O��������Ȃ������ꍇ
}


//===========================================================================
/*!	@brief	X�t�@�C�����擾
	@param	name	: �擾����X�t�@�C���̖��O
	@return	X�t�@�C��
*/
//===========================================================================
const XFile* ResourceManager::GetXFile(std::string name)
{
	XFileAry::iterator itr = m_xfileAry.begin();
	XFileAry::iterator end = m_xfileAry.end();
	for( ; itr != end; ++itr) {
		if( (*itr)->GetName() == name ) {
			return *itr;
		}
	}

	return NULL;		// ���O��������Ȃ������ꍇ
}


//===========================================================================
/*!	@brief	ToyFile���擾
	@param	name	: �擾����ToyFile�̖��O
	@return	X�t�@�C��
*/
//===========================================================================
const ToyFile* ResourceManager::GetToyFile(std::string name)
{
	ToyFileAry::iterator itr = m_toyfileAry.begin();
	ToyFileAry::iterator end = m_toyfileAry.end();

	for( ; itr != end; ++itr) {
		if( (*itr)->GetName() == name ) {
			return *itr;
		}
	}

	return NULL;		// ���O��������Ȃ������ꍇ
}


//===========================================================================
/*!	@brief	mqo�t�@�C�����K��
	@param	name	: �t�@�C����
	@return	mqo�t�@�C��
*/
//===========================================================================
const MqoFile* ResourceManager::GetMqoFile(std::string name)
{
	MqoFileAry::iterator itr = m_mqofileAry.begin();
	MqoFileAry::iterator end = m_mqofileAry.end();

	for( ; itr != end; ++itr) {
		if( (*itr)->GetFileName() == name ) {
			return *itr;
		}
	}

	return NULL;		// ���O��������Ȃ������ꍇ
}

//===========================================================================
/*!	@brief	�e�N�X�`�����J��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void ResourceManager::_DeleteTexture()
{
	TextureAry::iterator itr = m_textureAry.begin();
	TextureAry::iterator end = m_textureAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}
}


//===========================================================================
/*!	@brief	X�t�@�C�������
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void ResourceManager::_DeleteXFile()
{
	XFileAry::iterator itr = m_xfileAry.begin();
	XFileAry::iterator end = m_xfileAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}

}


//===========================================================================
/*!	@brief	ToyStudio�t�@�C�����J��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void ResourceManager::_DeleteToyFile()
{
	ToyFileAry::iterator itr = m_toyfileAry.begin();
	ToyFileAry::iterator end = m_toyfileAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}
}


//===========================================================================
/*!	@brief	ToyStudio�t�@�C�����J��
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void ResourceManager::_DeleteMqoFile()
{
	MqoFileAry::iterator itr = m_mqofileAry.begin();
	MqoFileAry::iterator end = m_mqofileAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}
}


}	// namespace resource
}	// namespace nk