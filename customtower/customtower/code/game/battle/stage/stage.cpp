//=============================================================================
/*!	@file	ステージ

	@brief	ステージ

	@author	ryunosuke ide
	@date	2013.05.27
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "stage.h"

#include "game/gameMain.h"
#include "game/battle/collision/collisionObjectManager.h"
#include "game/battle/character/character.h"
#include "game/battle/battleExecutor.h"

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
Stage::Stage()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Stage::~Stage()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Stage::_Init( void )
{
	m_stageModel	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Stage::_Term( void )
{

}


//===========================================================================
/*!	@brief		バトル生成時初期化
	@param		battle	バトル
	@return		----
*/
//===========================================================================
void Stage::InitializeForBattle( BattleExecutor* battleExec )
{
	BattleObject::InitializeForBattle( battleExec );
	
	RegisterToRenderManager();

	m_bvSphere.Init();
	m_bvSphere.SetRadius( GetInfo().radius );
	m_battleExec->GetCollisionObjectManager()->AddCollisionObject( &m_bvSphere, this );

}



//===========================================================================
/*!	@brief		バトル終了時
	@param		----
	@return		----
*/
//===========================================================================
void Stage::TerminateForBattle( void )
{
	RemoveFromRenderManager();

	m_battleExec->GetCollisionObjectManager()->RemoveCollisionObject( &m_bvSphere );

}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
bool Stage::Execute( void )
{
	bool	result	= true;
	
	result	= ExecuteLocal();

	return result;
}


//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void Stage::Render( void )
{
}


//===========================================================================
/*!	@brief		ステージ基本情報取得
	@param		----
	@return		----
*/
//===========================================================================
const Stage::StageInfo& Stage::GetInfo( void ) const
{
	
	return m_stageInfo;
}


}	// namespace battle

}	// namespace game
