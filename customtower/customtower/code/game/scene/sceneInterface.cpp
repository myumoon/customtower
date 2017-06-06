//=============================================================================
/*!	@file	sceneInterface.h

	@brief	�V�[���C���^�[�t�F�[�X

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "sceneInterface.h"



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
SceneInterface::SceneInterface()
{
	SceneInterface::_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
SceneInterface::~SceneInterface()
{
	SceneInterface::_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void SceneInterface::_Init( void )
{
	m_children.reserve( MAX_TREE_NUM );

	m_id			= -1;
	m_active		= false;
	m_sceneManager	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void SceneInterface::_Term( void )
{
	// @todo �����폜����H�H
}

//===========================================================================
/*!	@brief		�c���[�폜
	@param		----
	@return		----
*/
//===========================================================================
void SceneInterface::DeleteTree( SceneInterface* parent )
{
	std::vector<SceneInterface*>::iterator	itr	= m_children.begin();
	for( ; itr != m_children.end(); ++itr ) {
		(*itr)->DeleteTree( parent );
	}
	m_children.clear();

	TerminateScene( parent );
}


//===========================================================================
/*!	@brief		�Q�[���I�u�W�F�N�g���폜
	@param		----
	@return		----
*/
//===========================================================================
//void SceneInterface::DeleteGameObjects( void )
//{
//	m_gameObjectMng.DeleteGameObjects();
//	
//}


//===========================================================================
/*!	@brief		�X�V
	@param		message		�e����̃��b�Z�[�W
	@return		false�ō폜
*/
//===========================================================================
void SceneInterface::Execute( s32 parentMessage )
{
	s32	sendChildMessage	= 0;
	
	sendChildMessage	= ExecuteLocal( parentMessage );

//	result	&= m_gameObjectMng.Execute();

	std::vector<SceneInterface*>::iterator	itr	= m_children.begin();
	for( ; itr != m_children.end(); ++itr ) {
		(*itr)->Execute( sendChildMessage );
	}
	
}

//===========================================================================
/*!	@brief		ID�ݒ�
	@param		id		SceneManager::SCENE_ID
	@return		----
*/
//===========================================================================
void SceneInterface::SetID( s32 id )
{
	m_id	= id;
	
}

//===========================================================================
/*!	@brief		ID�擾
	@param		----
	@return		SceneManager::SCENE_ID
*/
//===========================================================================
s32 SceneInterface::GetID( void ) const
{
	
	return m_id;
}


//===========================================================================
/*!	@brief		�q����ǉ�
	@param		child	�q��
	@return		----
*/
//===========================================================================
void SceneInterface::ConnectChild( SceneInterface* child )
{
	m_children.push_back( child );
	child->SetActive( IsActive() );
	
}


//===========================================================================
/*!	@brief		�q����ǉ�
	@param		child	�q��
	@return		----
*/
//===========================================================================
void SceneInterface::DisconnectChild( SceneInterface* child )
{
	std::vector<SceneInterface*>::iterator	itr	= m_children.begin();
	for( ; itr != m_children.end(); ) {
		if( child == *itr ) {
			(*itr)->TerminateScene( this );
			(*itr)->SetActive( false );
			itr	= m_children.erase( itr );
		}
		else {
			++itr;
		}
	}

	
}


//===========================================================================
/*!	@brief		�X�V�I�u�W�F�N�g��ǉ�
	@param		----
	@return		----
*/
//===========================================================================
//void SceneInterface::AddGameObject( GameObject* gameObj )
//{
//	m_gameObjectMng.AddGameObject( gameObj );
//	
//}


//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void SceneInterface::Render( void )
{
	if( IsActive() ) {
		RenderLocal();
	}
	
	std::vector<SceneInterface*>::iterator	itr	= m_children.begin();
	for( ; itr != m_children.end(); ++itr ) {
		(*itr)->Render();
	}
}

	

//===========================================================================
/*!	@brief		�A�N�e�B�u�Ȃ�true��Ԃ�
	@param		----
	@return		----
*/
//===========================================================================
bool SceneInterface::IsActive( void ) const
{

	return m_active;
}

//===========================================================================
/*!	@brief		�A�N�e�B�u��Ԃ�ݒ�
	@param		----
	@return		----
*/
//===========================================================================
void SceneInterface::SetActive( bool state )
{
	m_active	= state;

	for( u32 i = 0; i < m_children.size(); ++i ) {
		m_children[i]->SetActive( state );
	}
	
}


//===========================================================================
/*!	@brief		�V�[���Ǘ���R�t��
	@param		sceneManager	�V�[���Ǘ�
	@return		----
*/
//===========================================================================
void SceneInterface::SetSceneManager( SceneManager* sceneManager )
{
	m_sceneManager	= sceneManager;
	
}



//===========================================================================
/*!	@brief		�V�[���Ǘ����擾
	@param		----
	@return		�V�[���Ǘ�
*/
//===========================================================================
SceneManager* SceneInterface::GetSceneManager( void ) const
{
	
	return m_sceneManager;
}

}	// namespace game
