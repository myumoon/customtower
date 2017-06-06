//=============================================================================
/*!	@file	BattleScene.h

	@brief	通常バトル

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "battleScene.h"
#include "game/battle/battleInfo.h"


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
BattleScene::BattleScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
BattleScene::~BattleScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void BattleScene::_Init( void )
{
	m_battleExecutor				= NULL;
	m_battleExecutorSetupThread		= NULL;
	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void BattleScene::_Term( void )
{
	nk::SafeDelete( m_battleExecutorSetupThread );
	nk::SafeDelete( m_battleExecutor );
}


//===========================================================================
/*!	@brief		初期化
	@param		parent	親
	@return		----
*/
//===========================================================================
void BattleScene::InitializeScene( SceneInterface* parent )
{
	m_battleExecutorSetupThread		= new battle::BattleExecutorSetupThread();
	m_battleExecutor				= new battle::BattleExecutor();

	// @@@@@
	{
		battle::BattleInfo	_info;
		_info.SetStage( battle::BattleInfo::STAGE_TYPE_STAGE01 );
		_info.AddControler( battle::BattleInfo::CONTOROLLER_TYPE_USER );

		SetupGenerator( _info );
	}

	battle::BattleInfo	battleInfo;

	// バトル初期化
	m_battleExecutorSetupThread->Setup(
		m_battleExecutor,
		battleInfo,
		&m_stageGenerator,
		&m_forceGenerator,
		&m_battleEventSender
	);

	RegisterToRenderManager();

	m_battleExecutorSetupThread->Start();
}


//===========================================================================
/*!	@brief		終了
	@param		parent	親
	@return		----
*/
//===========================================================================
void BattleScene::TerminateScene( SceneInterface* parent )
{
	if( m_battleExecutor ) {
		m_battleExecutor->Terminate();
	}
	
	nk::SafeDelete( m_battleExecutor );
	CallGeneratorDelete();


	RemoveFromRenderManager();
}


//===========================================================================
/*!	@brief		更新
	@param		parentMessage	親からのメッセージ
	@return		子に通知するメッセージ
*/
//===========================================================================
s32 BattleScene::ExecuteLocal( s32 parentMessage )
{
	if( m_battleExecutorSetupThread->IsSetupEnd() ) {
		m_battleExecutor->Update();
	}

	
	return MESSAGE_NONE;
}


//===========================================================================
/*!	@brief		レンダリング
	@param		----
	@return		----
*/
//===========================================================================
void BattleScene::RenderLocal( void )
{
	nk::SystemPrint( 0, 0, "Normal Battle" );

	if( m_battleExecutorSetupThread->IsSetupEnd() ) {
		//m_battleExecutor->Render( message );
	}
	
}



//===========================================================================
/*!	@brief		ジェネレーターセットアップ
	@param		info	対戦情報
	@return		----
*/
//===========================================================================
void BattleScene::SetupGenerator( const battle::BattleInfo& info )
{
	m_stageGenerator.Setup( info );
	m_forceGenerator.Setup( info );
	
}


//===========================================================================
/*!	@brief		ジェネレーター内のインスタンス削除
	@param		----
	@return		----
*/
//===========================================================================
void BattleScene::CallGeneratorDelete( void )
{
	m_stageGenerator.Delete();
	m_forceGenerator.Delete();
	
}
	
}	// namespace game