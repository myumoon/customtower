//=============================================================================
/*!	@file	sceneManager.h

	@brief	�V�[���Ǘ�

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "sceneManager.h"

// ��������V�[�����C���N���[�h
#include "net/networkScene.h"
#include "net/hostRoom/hostRoomScene.h"
#include "net/searchHostRoomScene.h"
#include "title/titleScene.h"
#include "battle/normal/normalBattleScene.h"
#include "debug/debugMenu.h"
#include "debug/model/modelTestScene.h"
#include "debug/viewer/stageViewer.h"

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
SceneManager::SceneManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
SceneManager::~SceneManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void SceneManager::_Init( void )
{
	m_scenes.reserve( 1024 );
	m_activeScene	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void SceneManager::_Term( void )
{
	DeleteScene();
}


//===========================================================================
/*!	@brief		�S�V�[������
	@param		----
	@return		----
*/
//===========================================================================
void SceneManager::CreateScene( void )
{

	struct SceneInfo {
		SceneInterface*	instance;
		SCENE_ID		id;
	};
	
	// �ꎞ�e�[�u���Ɉ�U�i�[���m_scenes�ɓ����
	SceneInfo	sceenInfoTbl[]	= {
	#if defined SCENE_TBL
		#undef 	SCENE_TBL
	#endif
	#define	SCENE_TBL( enumName, className, title )	{ new className(), enumName },
		#include "sceneTbl.tbl"
	#undef SCENE_TBL
	};

	m_scenes.resize( SCENE_ID_MAX );
	for( s32 i = 0; i < SCENE_ID_MAX; ++i ) {
		m_scenes[i]	= sceenInfoTbl[i].instance;
		m_scenes[i]->SetID( sceenInfoTbl[i].id );
	}
	
}


//===========================================================================
/*!	@brief		�S�V�[���폜
	@param		----
	@return		----
*/
//===========================================================================
void SceneManager::DeleteScene( void )
{
	for( u32 i = 0; i < m_scenes.size(); ++i ) {
		m_scenes[i]->DeleteTree( NULL );
		nk::SafeDelete( m_scenes[i] );
	}

	m_scenes.clear();
	
}

//===========================================================================
/*!	@brief		�V�[���擾
	@param		id		�V�[��ID
	@return		----
*/
//===========================================================================
SceneInterface* SceneManager::GetScene( SCENE_ID id ) const
{
	
	return m_scenes.at( id );
}

//===========================================================================
/*!	@brief		�A�N�e�B�u�ȃV�[����ݒ�
	@param		scene	�V�[��
	@return		----
*/
//===========================================================================
void SceneManager::SetActiveScene( SCENE_ID id )
{
	if( m_activeScene ) {
		m_activeScene->SetActive( false );
	}
	
	m_activeScene	= GetScene( id );
	m_activeScene->SetActive( true );
	
}

	
//===========================================================================
/*!	@brief		�A�N�e�B�u�ȃV�[����ݒ�
	@param		scene	�V�[��
	@return		----
*/
//===========================================================================
void SceneManager::SetNextActiveScene( SCENE_ID id )
{
	INDEX_ASSERT( id, SCENE_ID_MAX, "invalid id (%d)", id );
	
	m_nextSceneId	= id;
	
}

//===========================================================================
/*!	@brief		�A�N�e�B�u�ȃV�[�����擾
	@param		----
	@return		----
*/
//===========================================================================
SceneInterface* SceneManager::GetActiveScene( void ) const
{
	
	return m_activeScene;
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
bool SceneManager::Execute( void )
{
	bool	result	= true;

	
	if( GetActiveScene() == NULL ) {
		if( m_nextSceneId != SCENE_ID_NONE ) {
			SetActiveScene( m_nextSceneId );
			GetActiveScene()->InitializeScene( NULL );
		}
	}
	
	if( GetActiveScene() ) {
		if( m_nextSceneId != GetActiveScene()->GetID() ) {
			GetActiveScene()->TerminateScene( NULL );
			SetActiveScene( m_nextSceneId );
			GetActiveScene()->InitializeScene( NULL );
		}
		
		GetActiveScene()->Execute( 0 );
	}
	
	return result;
}



//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void SceneManager::Render( void )
{
	//if( GetActiveScene() ) {
	//	GetActiveScene()->Render();
	//}
	
}
	
}	// namespace game
