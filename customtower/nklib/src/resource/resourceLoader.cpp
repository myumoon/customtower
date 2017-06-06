//=============================================================================
/*!	@file	resourceLoader.h

	@brief	���\�[�X���[�h

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/resource/resourceLoader.h"


#include <iostream>
#include <string>
#include "../../include/general.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace nk {

namespace resource {


ResourceManager*	ResourceLoader::m_resourceMng	= NULL;

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
ResourceLoader::ResourceLoader()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
ResourceLoader::~ResourceLoader()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void ResourceLoader::_Init()
{
	m_texLoadThread		= new TextureLoadThread();

	m_loadTexComplete	= false;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void ResourceLoader::_Term()
{
	m_texLoadThread->Cancel();
	m_texLoadThread->Join();
	
	SafeDelete( m_texLoadThread );
}


//===========================================================================
/*!	@brief	���[�h�J�n
	@param	loadListPath	���[�h�t�@�C�����X�g
	@return	----
*/
//===========================================================================
void ResourceLoader::Load( const char* loadListPath )
{
	printf("ResourceLoader::Load 1\n");
	std::ifstream ifs( loadListPath );
	printf("ResourceLoader::Load 2\n");

	ASSERT( ifs.fail() == false, "file list open error." );
	if( ifs.fail() ) {
		return;
	}
	printf("ResourceLoader::Load 3\n");

	while( !ifs.eof() ) {
		std::string line;
		ifs >> line;
		printf( "%s\n", line.c_str() );

		_FileInfo	info;

		// �e�N�X�`���ǂݍ���
		if( strstr( line.c_str(), ".png" ) || 
			strstr( line.c_str(), ".jpg" ) ||
			strstr( line.c_str(), ".jpeg") ||
			strstr( line.c_str(), ".bmp" ) ) {

			m_texLoadThread->Add( line.c_str() );
			info.isImage	= true;
		}
		else {
			info.isImage	= false;
		}
		
		info.fileName.assign( line.c_str() );
		m_vecLoadFiles.push_back( info );
		
	}

	m_texLoadThread->Setup();
	m_texLoadThread->Start();

	Setup();
}


//===========================================================================
/*!	@brief	�X�V
	@param	----
	@return	----
*/
//===========================================================================
bool ResourceLoader::Update( void )
{
	if( m_loadTexComplete ) {
		return GetStatus() == STATUS_EXIT;
	}
	
	NULL_ASSERT( m_texLoadThread );
	if( m_texLoadThread && m_texLoadThread->IsComplete() ) {

		for( u32 i = 0; i < m_vecLoadFiles.size(); ++i ) {
			if( m_vecLoadFiles[i].isImage ) {
				Texture*	tex	= m_texLoadThread->PopTexture( m_vecLoadFiles[i].fileName.c_str() );
				m_resourceMng->Register( tex );
			}
		}
		m_loadTexComplete	= true;
		Start();	// �X���b�h�J�n

	}

	return false;
}


//===========================================================================
/*!	@brief	�X���b�h����
	@param	----
	@return	----
*/
//===========================================================================
void ResourceLoader::ThreadFunc( void )
{
	for( u32 i = 0; i < m_vecLoadFiles.size(); ++i ) {
		if( m_vecLoadFiles[i].isImage == false ) {
			m_resourceMng->LoadFile( m_vecLoadFiles[i].fileName );
		}
	}

}
	
}	// namespace resource
}	// namespace nk
