//=============================================================================
/*!	@file	characterManager.h

	@brief	キャラクターマネージャー

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "characterManager.h"

#include "characterGenerator.h"

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
CharacterManager::CharacterManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
CharacterManager::~CharacterManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void CharacterManager::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void CharacterManager::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::Initialize( void )
{
	
}


//===========================================================================
/*!	@brief		終了
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::Terminate( void )
{
	DeleteAll();
}


//===========================================================================
/*!	@brief		キャラクター追加
	@param		character	追加キャラクター
	@return		----
*/
//===========================================================================
void CharacterManager::Add( Character* character )
{
	character->RegisterToRenderManager();
	m_characters.push_back( character );
}



//===========================================================================
/*!	@brief		削除キャラクター追加
	@param		character	削除キャラクター
	@return		----
*/
//===========================================================================
void CharacterManager::Remove( Character* character )
{
	character->RemoveFromRenderManager();
	m_removeCharacters.push_back( character );
	
}


//===========================================================================
/*!	@brief		全削除
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::DeleteAll( void )
{
	std::vector<Character*>::iterator	itr	= m_characters.begin();
	for( ; itr != m_characters.end(); ++itr ) {
		(*itr)->TerminateForBattle();
		nk::SafeDelete( *itr );
	}
	m_characters.clear();
	m_removeCharacters.clear();
}


//===========================================================================
/*!	@brief		削除
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::RemoveReservedCharacters( void )
{
	std::vector<Character*>::iterator	itrDead	= m_removeCharacters.begin();
	std::vector<Character*>::iterator	itrLive	= m_characters.begin();
	
	for( ; itrDead != m_removeCharacters.end(); ++itrDead ) {
		for( itrLive = m_characters.begin(); itrLive != m_characters.end(); ++itrLive ) {
			if( *itrDead == *itrLive ) {
				(*itrLive)->TerminateForBattle();
				nk::SafeDelete( *itrLive );
				m_characters.erase( itrLive );
				break;
			}
		}
	}
	m_removeCharacters.clear();
	
		
}


//===========================================================================
/*!	@brief		前回位置記憶
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::PushPrevPos( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i]->SetPrevPos( m_characters[i]->GetPos() );
	}
}


//===========================================================================
/*!	@brief		位置更新
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::UpdatePosition( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i]->UpdatePosition();
	}
}

//===========================================================================
/*!	@brief		移動
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::UpdateMove( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i]->Move();
	}
	
}


}	// namespace battle
	
}	// namespace game