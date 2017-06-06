//=============================================================================
/*!	@file	earthObjectManager.h

	@brief	�n���I�u�W�F�N�g�Ǘ�

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <algorithm>
#include "earthObjectManager.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace game {
namespace battle {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
EarthObjectManager::EarthObjectManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
EarthObjectManager::~EarthObjectManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void EarthObjectManager::_Init( void )
{
	m_earthObjects.resize( MAX_REGISTER_OBJECTS_NUM );
	
	Clear();
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void EarthObjectManager::_Term( void )
{
	
}


//===========================================================================
/*!	@brief		�o�^�I�u�W�F�N�g�S�폜
	@param		----
	@return		----
*/
//===========================================================================
void EarthObjectManager::Clear( void )
{
	for( u32 i = 0; i < m_earthObjects.size(); ++i ) {
		m_earthObjects[i]	= NULL;
	}
}

//===========================================================================
/*!	@brief		�d�̓I�u�W�F�N�g�o�^
	@param		obj		�o�^�I�u�W�F�N�g
	@return		----
*/
//===========================================================================
bool EarthObjectManager::RegisterEarthObject( EarthObject* obj )
{
	bool	registered	= false;
	for( u32 i = 0; i < m_earthObjects.size(); ++i ) {
		if( m_earthObjects[i] == NULL ) {
			m_earthObjects[i]	= obj;
			registered	= true;
			break;
		}
	}

	return registered;
}

//===========================================================================
/*!	@brief		�d�̓I�u�W�F�N�g���O
	@param		obj		�폜�I�u�W�F�N�g
	@return		----
*/
//===========================================================================
void EarthObjectManager::RemoveEarthObject( EarthObject* obj )
{
	
	m_earthObjects.erase(
		std::remove( m_earthObjects.begin(), m_earthObjects.end(), obj ),
		m_earthObjects.end()
	);

}

//===========================================================================
/*!	@brief		�d�͓K�p
	@param		----
	@return		----
*/
//===========================================================================
void EarthObjectManager::AcceptProjection( void )
{
	for( u32 i = 0; i < m_earthObjects.size(); ++i ) {
		if( m_earthObjects[i] ) {
			m_earthObjects[i]->UpdatePosition();
		}
	}
	
}

	
}	// namespace battle
}	// namespace game
