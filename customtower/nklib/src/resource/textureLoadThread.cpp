//=============================================================================
/*!	@file	textureLoadThread.h

	@brief	�e�N�X�`�����[�h�X���b�h

	@author	ryunosuke ide
	@date	2013.03.09
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/resource/textureLoadThread.h"
#include "../../include/utility/utility.h"
#include "../../include/resource/texture.h"
#include "../../include/general.h"
#include "../../include/utility/stringfunction.h"


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

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
TextureLoadThread::TextureLoadThread()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
TextureLoadThread::~TextureLoadThread()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void TextureLoadThread::_Init()
{
	m_vecSurface.reserve( 256 );

	m_completed			= false;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void TextureLoadThread::_Term()
{
	
}


//===========================================================================
/*!	@brief	���[�h���s���e�N�X�`����ǉ�
	@param	path	���[�h�e�N�X�`��
	@return	----
*/
//===========================================================================
void TextureLoadThread::Add( const char* path )
{
	_LoadSurface	addSurface;
	addSurface.path.assign( path );

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );
		
		m_vecSurface.push_back( addSurface );

		m_completed	= false;
	}

}


//===========================================================================
/*!	@brief	���[�h�����Ȃ�true��Ԃ�
	@param	----
	@return	----
*/
//===========================================================================
bool TextureLoadThread::IsComplete( void ) const
{
	
	return m_completed;
}


//===========================================================================
/*!	@brief	���[�h�����Ȃ�true��Ԃ�
	@param	----
	@return	----
*/
//===========================================================================
bool TextureLoadThread::IsComplete( const char* path ) const
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	for( u32 i = 0; i < m_vecSurface.size(); ++i ) {
		if( m_vecSurface[i].surface.created == false ) {
			if( m_vecSurface[i].path == path ) {
				return true;
			}
		}
	}

	return false;
}


//===========================================================================
/*!	@brief	�e�N�X�`�����擾
	@param	path		�擾����e�N�X�`���p�X
	@return	�e�N�X�`���ւ̃|�C���^
	
	@note	�擾�����e�N�X�`���̓��X�g����폜����܂�
			�e�N�X�`���̉���̓��[�U�[���s���Ă�������
*/
//===========================================================================
Texture* TextureLoadThread::PopTexture( const char* path )
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	for( u32 i = 0; i < m_vecSurface.size(); ++i ) {
		if( nk::Compare( m_vecSurface[i].path.c_str(), path ) ) {
			return _CreateTexture( m_vecSurface[i] );
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief	�X���b�h����
	@param	----
	@return	----
*/
//===========================================================================
void TextureLoadThread::ThreadFunc( void )
{
	while( 1 ) {
		{
			SCOPE_CRITICAL_SECTION( m_criticalSection );
			
			if( IsComplete() == false ) {
				for( u32 i = 0; i < m_vecSurface.size(); ++i ) {
					if( m_vecSurface[i].surface.created == false ) {
						ImageSurface	surface;
						LoadImageSurface( &surface, m_vecSurface[i].path.c_str() );
						m_vecSurface[i].surface.Register( surface.image );
					}
				}

				m_completed	= true;
			}
		}

		if( IsCancel() ) {
			printf("TextureLoadThread::ThreadFunc() cancel\n");
			break;
		}
		
		SleepThread( 1 );
	}

	printf("TextureLoadThread::ThreadFunc() end\n");
}

//===========================================================================
/*!	@brief	�T�[�t�F�X����e�N�X�`���𐶐�
	@param	surface		�\�[�X
	@return	�e�N�X�`��
*/
//===========================================================================
Texture* TextureLoadThread::_CreateTexture( const _LoadSurface& surface ) const
{
	Texture*	texture	= CreateTexture( surface.surface );

	NULL_ASSERT( texture );

	texture->SetTexName( surface.path.c_str() );
	

	return texture;
}
	
}	// namespace resource
	
}	// namespace nk

