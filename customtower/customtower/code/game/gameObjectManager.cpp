//=============================================================================
/*!	@file	gameObjectManager.h

	@brief	ゲームオブジェクト管理

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <algorithm>
#include "gameObjectManager.h"


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
GameObjectManager::GameObjectManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
GameObjectManager::~GameObjectManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void GameObjectManager::_Init( void )
{
	m_gameObjects.reserve( 1024 );

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void GameObjectManager::_Term( void )
{

}

//===========================================================================
/*!	@brief		ゲームオブジェクトを追加
	@param		gameObj		ゲームオブジェクト
	@return		----
*/
//===========================================================================
void GameObjectManager::AddGameObject( GameObject* gameObj )
{
	m_gameObjects.push_back( gameObj );
	
}


//===========================================================================
/*!	@brief		ゲームオブジェクトを除外
	@param		gameObj		ゲームオブジェクト
	@return		----
*/
//===========================================================================
void GameObjectManager::RemoveGameObject( GameObject* gameObj )
{
	std::remove( m_gameObjects.begin(), m_gameObjects.end(), gameObj );
	
}


//===========================================================================
/*!	@brief		ゲームオブジェクトを削除
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
/*!	@brief		システムイベントコールバック
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
