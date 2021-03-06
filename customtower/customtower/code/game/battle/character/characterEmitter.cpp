//=============================================================================
/*!	@file	characterEmiter.h

	@brief	エミッター

	@author	ryunosuke ide
	@date	2013.07.06
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "./characterEmitter.h"
#include "./characterManager.h"


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
CharacterEmitter::CharacterEmitter()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
CharacterEmitter::~CharacterEmitter()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void CharacterEmitter::_Init( void )
{
	m_mouse		= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void CharacterEmitter::_Term( void )
{

}


//===========================================================================
/*!	@brief		マウス設定
	@param		mouse		マウス
	@return		----
*/
//===========================================================================
void CharacterEmitter::SetMouse( const nk::input::Mouse* mouse )
{
	m_mouse		= mouse;
}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void CharacterEmitter::Update( void )
{
	Emitter<Character>::Update();

	if( m_mouse ) {
	}
	
}


//===========================================================================
/*!	@brief		発射
	@param		----
	@return		----
*/
//===========================================================================
void CharacterEmitter::Emit( void )
{
	EmitObjectHandle<Character>	handle	= _Emit();
	
	Character*	character	= handle.GetRegisteredObject();
	character->SetCharacterManager( static_cast<const CharacterManager*>(m_manager) );
	character->SetMoveSpeed( 2.0f );
	
	m_emitObjcts.push_back( handle );
}

	
}	// namespace battle
}	// namespace game
