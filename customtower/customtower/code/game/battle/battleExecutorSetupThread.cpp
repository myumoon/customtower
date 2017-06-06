//=============================================================================
/*!	@file	battleExecutorSetupThread.h

	@brief	バトルセットアップスレッド

	@author	ryunosuke ide
	@date	2013.06.26
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "battleExecutorSetupThread.h"

#include "battleExecutor.h"
#include "battleEventSender.h"
#include "stage/stageGenerator.h"
#include "force/forceGenerator.h"

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
BattleExecutorSetupThread::BattleExecutorSetupThread()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
BattleExecutorSetupThread::~BattleExecutorSetupThread()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutorSetupThread::_Init( void )
{
	m_battleExecutor	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutorSetupThread::_Term( void )
{

}


//===========================================================================
/*!	@brief		セットアップ
	@param		battle				バトル
    @param		stageGenerator		ステージ生成
	@param		forceGenerator		軍生成
	@param		eventSender			イベント通知
	@return		----
*/
//===========================================================================
void BattleExecutorSetupThread::Setup(
	BattleExecutor*		battleExecutor,
	const BattleInfo&	battleInfo,
	StageGenerator*		stageGenerator,
	ForceGenerator*		forceGenerator,
	BattleEventSender*	eventSender
)
{
	m_battleExecutor	= battleExecutor;
	m_battleInfo		= battleInfo;
    m_stageGenerator	= stageGenerator;
    m_forceGenerator	= forceGenerator;
	m_eventSender		= eventSender;

	Thread::Setup( THREAD_PRIORITY_NORMAL, 0, "BattleExecutorSetupThread" );
}

//===========================================================================
/*!	@brief		スレッド処理
	@param		----
	@return		----
*/
//===========================================================================
void BattleExecutorSetupThread::ThreadFunc( void )
{
	if( m_battleExecutor ) {
		m_battleExecutor->Initialize( m_battleInfo, m_forceGenerator, m_stageGenerator );
	}
}

//===========================================================================
/*!	@brief		セットアップ終了ならtrueを返す
	@param		----
	@return		true.セットアップ完了	false.完了していない
*/
//===========================================================================
bool BattleExecutorSetupThread::IsSetupEnd( void ) const
{
	
	return GetStatus() == Thread::STATUS_EXIT;
}

	
}	// namespace battle
	
}	// namespace game