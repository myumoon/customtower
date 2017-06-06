//=============================================================================
/*!	@file	earthObjectManager.h

	@brief	地球オブジェクト管理

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <algorithm>
#include "earthObjectManager.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace game {
namespace battle {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
EarthObjectManager::EarthObjectManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
EarthObjectManager::~EarthObjectManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
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
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void EarthObjectManager::_Term( void )
{
	
}


//===========================================================================
/*!	@brief		登録オブジェクト全削除
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
/*!	@brief		重力オブジェクト登録
	@param		obj		登録オブジェクト
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
/*!	@brief		重力オブジェクト除外
	@param		obj		削除オブジェクト
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
/*!	@brief		重力適用
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
