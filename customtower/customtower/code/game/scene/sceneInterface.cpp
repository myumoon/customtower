//=============================================================================
/*!	@file	sceneInterface.h

	@brief	シーンインターフェース

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "sceneInterface.h"



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
SceneInterface::SceneInterface()
{
	SceneInterface::_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
SceneInterface::~SceneInterface()
{
	SceneInterface::_Term();
}


//===========================================================================
/*!	@brief	初期化
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
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void SceneInterface::_Term( void )
{
	// @todo 自動削除いる？？
}

//===========================================================================
/*!	@brief		ツリー削除
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
/*!	@brief		ゲームオブジェクトを削除
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
/*!	@brief		更新
	@param		message		親からのメッセージ
	@return		falseで削除
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
/*!	@brief		ID設定
	@param		id		SceneManager::SCENE_ID
	@return		----
*/
//===========================================================================
void SceneInterface::SetID( s32 id )
{
	m_id	= id;
	
}

//===========================================================================
/*!	@brief		ID取得
	@param		----
	@return		SceneManager::SCENE_ID
*/
//===========================================================================
s32 SceneInterface::GetID( void ) const
{
	
	return m_id;
}


//===========================================================================
/*!	@brief		子供を追加
	@param		child	子供
	@return		----
*/
//===========================================================================
void SceneInterface::ConnectChild( SceneInterface* child )
{
	m_children.push_back( child );
	child->SetActive( IsActive() );
	
}


//===========================================================================
/*!	@brief		子供を追加
	@param		child	子供
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
/*!	@brief		更新オブジェクトを追加
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
/*!	@brief		描画
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
/*!	@brief		アクティブならtrueを返す
	@param		----
	@return		----
*/
//===========================================================================
bool SceneInterface::IsActive( void ) const
{

	return m_active;
}

//===========================================================================
/*!	@brief		アクティブ状態を設定
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
/*!	@brief		シーン管理を紐付け
	@param		sceneManager	シーン管理
	@return		----
*/
//===========================================================================
void SceneInterface::SetSceneManager( SceneManager* sceneManager )
{
	m_sceneManager	= sceneManager;
	
}



//===========================================================================
/*!	@brief		シーン管理を取得
	@param		----
	@return		シーン管理
*/
//===========================================================================
SceneManager* SceneInterface::GetSceneManager( void ) const
{
	
	return m_sceneManager;
}

}	// namespace game
