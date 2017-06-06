//=============================================================================
/*!	@file	battleExecutor.h

	@brief	対戦処理実行
			対戦オブジェクトの動作部分を担当
			メニュー等はここから情報を引っ張る

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "battleExecutor.h"
#include "game/battle/force/force.h"
#include "game/battle/force/opponentForce.h"
#include "game/battle/stage/stage.h"
#include "game/battle/stage/stage01/stage01.h"
#include "game/battle/collision/collisionObjectManager.h"


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
BattleExecutor::BattleExecutor()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
BattleExecutor::~BattleExecutor()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutor::_Init( void )
{
	m_forceList	= NULL;
// 	m_forceList.reserve( 16 );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutor::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		forceGenerator		軍
	@param		stageGenerator		ステージ
	@return		----
*/
//===========================================================================
void BattleExecutor::Initialize(
	const BattleInfo&		battleInfo,
	ForceGenerator*			forceGenerator,
	StageGenerator*			stageGenerator
)
{
	m_battleInfo				= battleInfo;
	m_battleFrame				= 0;
	
	m_collisionObjectManager	= new CollisionObjectManager();
	
	// バトルオブジェクトを生成
	{
		GenerateStage( stageGenerator );		
		GenerateForce( forceGenerator );
	}


	// バトルオブエジェクトを初期化
	{
		for( u32 i = 0; i < m_forceList->forces.size(); ++i ) {
			m_forceList->forces[i]->Initialize( this );
		}
		
		if( m_stage ) {
			m_stage->InitializeForBattle( this );
		}
	}
}


//===========================================================================
/*!	@brief		終了
	@param		----
	@return		----
*/
//===========================================================================
void BattleExecutor::Terminate( void )
{
	m_collisionObjectManager->RemoveCollisionObjects();

	for( u32 i = 0; i < m_forceList->forces.size(); ++i ) {
		m_forceList->forces[i]->Terminate();
	}
	if( m_stage ) {
		m_stage->TerminateForBattle();
	}

	nk::SafeDelete( m_collisionObjectManager );
}

//===========================================================================
/*!	@brief		群生成
	@param		forceGenerator	ジェネレーター
	@return		----
*/
//===========================================================================
void BattleExecutor::GenerateForce( ForceGenerator* forceGenerator )
{
// 	forceGenerator.Setup( m_battleInfo );
	m_forceList	= forceGenerator->Generate();

}

//===========================================================================
/*!	@brief		ステージ生成
	@param		stageGenerator	ジェネレーター
	@return		----
*/
//===========================================================================
void BattleExecutor::GenerateStage( StageGenerator* stageGenerator )
{
// 	stageGenerator.Setup( m_battleInfo );
	m_stage	= stageGenerator->Generate();
	
}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void BattleExecutor::Update( void )
{
	// 敵軍リスト生成
	VecOpponentForce	opponents;
	opponents.resize( m_forceList->forces.size() );
	for( u32 insertForce = 0; insertForce < m_forceList->forces.size(); ++insertForce ) {
		for( u32 opponentForce = 0; opponentForce < m_forceList->forces.size(); ++opponentForce ) {
			if( insertForce != opponentForce ) {
				opponents[insertForce].AppendForce( m_forceList->forces[opponentForce] );
			}
		}
	}

	// 終了処理
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_FrameInitialize();
	}

	// 入力コマンド
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_Operate( opponents[updateForce] );
		m_forceList->forces[updateForce]->PopOperateInfo();
	}

	// 実際の移動
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_Move( opponents[updateForce] );
	}

	// 移動後位置修正
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_MoveFix( opponents[updateForce] );
	}

	// 攻撃
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_Attack( opponents[updateForce] );
	}

	// ヒット判定
	{
		m_collisionObjectManager->SortByPriority();
		m_collisionObjectManager->CheckHit();
	}


	// ヒット後
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_AfterHit( opponents[updateForce] );
	}

	// 終了処理
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_FrameTerminate();
	}

	++m_battleFrame;
}


//===========================================================================
/*!	@brief		現在フレーム取得
	@param		----
	@return		----
*/
//===========================================================================
u64 BattleExecutor::GetFrame( void ) const
{
	
	return m_battleFrame;
}


//===========================================================================
/*!	@brief		対戦情報取得
	@param		----
	@return		----
*/
//===========================================================================
const BattleInfo* BattleExecutor::GetBattleInfo( void ) const
{

	return &m_battleInfo;
}



//===========================================================================
/*!	@brief		ヒット管理取得
	@param		----
	@return		----
*/
//===========================================================================
CollisionObjectManager*	BattleExecutor::GetCollisionObjectManager( void )
{

	return m_collisionObjectManager;
}


//===========================================================================
/*!	@brief		ステージ取得
	@param		----
	@return		----
*/
//===========================================================================
const Stage* BattleExecutor::GetStage( void ) const
{

	return m_stage;
}

//===========================================================================
/*!	@brief		描画プッシュバック
	@param		offset	描画位置オフセット
	@return		----
*/
//===========================================================================
// void BattleExecutor::RenderPushBack( const nk::math::Vector& offset )
// {
// 	if( m_stage ) {
// 		m_stage->RenderPushBack( offset );
// 	}
// 	
// 	for( u32 i = 0; i < m_forceList.size(); ++i ) {
// 		m_forceList[i]->RenderPushBack( offset );
// 	}
// 	
// }


}	// namespace battle

	
}	// namespace game