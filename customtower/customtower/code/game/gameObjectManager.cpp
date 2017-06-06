//=============================================================================
/*!	@file	gameObjectManager.h

	@brief	�Q�[���I�u�W�F�N�g�Ǘ�

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <algorithm>
#include "gameObjectManager.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace game {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
GameObjectManager::GameObjectManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
GameObjectManager::~GameObjectManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void GameObjectManager::_Init( void )
{
	m_gameObjects.reserve( 1024 );

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void GameObjectManager::_Term( void )
{

}

//===========================================================================
/*!	@brief		�Q�[���I�u�W�F�N�g��ǉ�
	@param		gameObj		�Q�[���I�u�W�F�N�g
	@return		----
*/
//===========================================================================
void GameObjectManager::AddGameObject( GameObject* gameObj )
{
	m_gameObjects.push_back( gameObj );
	
}


//===========================================================================
/*!	@brief		�Q�[���I�u�W�F�N�g�����O
	@param		gameObj		�Q�[���I�u�W�F�N�g
	@return		----
*/
//===========================================================================
void GameObjectManager::RemoveGameObject( GameObject* gameObj )
{
	std::remove( m_gameObjects.begin(), m_gameObjects.end(), gameObj );
	
}


//===========================================================================
/*!	@brief		�Q�[���I�u�W�F�N�g���폜
	@param		----
	@return		----
*/
//===========================================================================
void GameObjectManager::DeleteGameObjects( void )
{
	std::vector<GameObject*>::iterator	itr	= m_gameObjects.begin();
	for( ; itr != m_gameObjects.end(); ++itr ) {
		nk::SafeDelete( *itr );
	}

	m_gameObjects.clear();

}


//===========================================================================
/*!	@brief		�V�X�e���C�x���g�R�[���o�b�N
	@param		----
	@return		----
*/
//===========================================================================
void GameObjectManager::CallbackSystemEvent( nk::Main::SYSTEM_EVENT event )
{
	std::vector<GameObject*>::iterator	itr	= m_gameObjects.begin();
	for( ; itr != m_gameObjects.end(); ++itr ) {
		(*itr)->CallbackSystemEvent( event );
	}
	
}
	
}	// namespace game
