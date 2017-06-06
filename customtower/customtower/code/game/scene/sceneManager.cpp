//=============================================================================
/*!	@file	sceneManager.h

	@brief	シーン管理

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "sceneManager.h"

// 生成するシーンをインクルード
#include "net/networkScene.h"
#include "net/hostRoom/hostRoomScene.h"
#include "net/searchHostRoomScene.h"
#include "title/titleScene.h"
#include "battle/normal/normalBattleScene.h"
#include "debug/debugMenu.h"
#include "debug/model/modelTestScene.h"
#include "debug/viewer/stageViewer.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace game {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
SceneManager::SceneManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
SceneManager::~SceneManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
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
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void SceneManager::_Term( void )
{
	DeleteScene();
}


//===========================================================================
/*!	@brief		全シーン生成
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
	
	// 一時テーブルに一旦格納後にm_scenesに入れる
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
/*!	@brief		全シーン削除
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
/*!	@brief		シーン取得
	@param		id		シーンID
	@return		----
*/
//===========================================================================
SceneInterface* SceneManager::GetScene( SCENE_ID id ) const
{
	
	return m_scenes.at( id );
}

//===========================================================================
/*!	@brief		アクティブなシーンを設定
	@param		scene	シーン
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
/*!	@brief		アクティブなシーンを設定
	@param		scene	シーン
	@return		----
*/
//===========================================================================
void SceneManager::SetNextActiveScene( SCENE_ID id )
{
	INDEX_ASSERT( id, SCENE_ID_MAX, "invalid id (%d)", id );
	
	m_nextSceneId	= id;
	
}

//===========================================================================
/*!	@brief		アクティブなシーンを取得
	@param		----
	@return		----
*/
//===========================================================================
SceneInterface* SceneManager::GetActiveScene( void ) const
{
	
	return m_activeScene;
}


//===========================================================================
/*!	@brief		更新
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
/*!	@brief		描画
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
