//=============================================================================
/*!	@file	character01.h

	@brief	キャラクタ01

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "gameDef.h"

#include "character01.h"
#include "game/battle/battleExecutor.h"
#include "game/battle/stage/stage.h"

#include "out/data_list.h"
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
Character01::Character01( void )
{
	_Init();
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Character01::Character01( const CharacterManager* mng ) : Character( mng )
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Character01::~Character01( void )
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Character01::_Init( void )
{
	m_model.Init( DATA_CHARACTER_TESTCHARACTER_TESTCHARACTER_MODEL );
	m_model.SetPriority( RENDER_PRIORITY_CHARACTER );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Character01::_Term( void )
{

}


//===========================================================================
/*!	@brief		移動
	@param		----
	@return		----
*/
//===========================================================================
void Character01::Move( void )
{
	Character::Move();

	nk::math::Vector	up = GetPos() - m_battleExec->GetStage()->GetPos();
	up.Normalize();
	m_bvSphere.SetPos( GetPos() + up * 5.0f );
}


//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void Character01::Render( void )
{
	Character::Render();
	m_model.SetRotate( GetGlobalRotation(), GAME_AXIS_Z );
	m_model.Draw( GetPos() );
}


}	// namespace battle
	
	
}	// namespace game