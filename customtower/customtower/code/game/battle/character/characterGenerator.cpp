//=============================================================================
/*!	@file	characterGenerator.h

	@brief	キャラクタジェネレーター

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "characterGenerator.h"
#include "character01/character01.h"


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
CharacterGenerator::CharacterGenerator()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
CharacterGenerator::~CharacterGenerator()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void CharacterGenerator::_Init( void )
{
#if 0
	m_characterManager	= NULL;
	
	m_characters.resize( MAX_CHARACTER_NUM );
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i].index	= i;
	}
	m_unusedHeadIndex	= 0;
#endif
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void CharacterGenerator::_Term( void )
{
#if 0
	Terminate();
#endif
}

#if 0
//===========================================================================
/*!	@brief		初期化
	@param		----
	@return		----
*/
//===========================================================================
void CharacterGenerator::Initialize( const CharacterManager* mng )
{
	m_characterManager	= mng;
}


//===========================================================================
/*!	@brief		終了
	@param		----
	@return		----
*/
//===========================================================================
void CharacterGenerator::Terminate( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i].DeleteCharacter();
	}
}
#endif

//===========================================================================
/*!	@brief		生成情報設定
	@param		info	生成情報
	@return		----
*/
//===========================================================================
void CharacterGenerator::SetGenerateInfo( const GenerateInfo& info )
{

}

	
//===========================================================================
/*!	@brief		キャラクタ生成
	@param		info	生成情報
	@return		----
*/
//===========================================================================
Character* CharacterGenerator::Generate( void )
{
	{
		Character*	createdCharacter	= new Character01();
// 		AddCharacterToContainer( createdCharacter );
// 
// 		createdCharacter->SetCharacterManager( m_characterManager );
// 		createdCharacter->InitializeForBattle();
		
		return createdCharacter;
	}
	
	return NULL;
}
#if 0
//===========================================================================
/*!	@brief		キャラクタ削除
	@param		character	削除キャラクタ
	@return		----
*/
//===========================================================================
void CharacterGenerator::Delete( Character* character )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		if( m_characters[i].character == character ) {
			m_characters[i].character->TerminateForBattle();
			m_characters[i].DeleteCharacter();

			if( i < m_unusedHeadIndex ) {
				m_unusedHeadIndex	= i;
			}
			break;
		}
	}
	
}

//===========================================================================
/*!	@brief		キャラクタ削除
	@param		----
	@return		----
*/
//===========================================================================
void CharacterGenerator::Delete( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i].DeleteCharacter();
	}
	m_unusedHeadIndex	= 0;
}


//===========================================================================
/*!	@brief		未使用のコンテナを取得
	@param		----
	@return		----
*/
//===========================================================================
CharacterGenerator::CharacterContainer* CharacterGenerator::GetUnusedContainer( void )
{
	// 検索時間短縮のために未使用インデックスを参照
	if( m_unusedHeadIndex != m_characters.size() ) {
		return &m_characters[m_unusedHeadIndex];
	}

	// 配列数が足りていなかったら仕方なく増やして再帰呼び出し
	{
		const u32	prevSize	= m_characters.size();
		m_characters.resize( prevSize + MAX_CHARACTER_NUM );
		for( u32 i = prevSize; i < m_characters.size(); ++i ) {
			m_characters[i].index	= i;
		}
	}

	return GetUnusedContainer();
}

//===========================================================================
/*!	@brief		コンテナにキャラクタを格納
	@param		character	追加キャラ
	@return		----
*/
//===========================================================================
void CharacterGenerator::AddCharacterToContainer( Character* character )
{
	CharacterContainer*	container	= GetUnusedContainer();
	
	container->SetCharacter( character );

	// 次の生成時間短縮のために未使用コンテナを検索
	do {
		++m_unusedHeadIndex;
	} while( m_characters[m_unusedHeadIndex].Using() );
	
}
#endif

}	// namespace battle

	
}	// namespace game