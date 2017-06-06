//=============================================================================
/*!	@file	battleExecutorSetupThread.h

	@brief	バトルセットアップスレッド

	@author	ryunosuke ide
	@date	2013.06.26
*/
//=============================================================================


#ifndef __BATTLE_EXECUTOR_SETUP_THREAD_H__
#define __BATTLE_EXECUTOR_SETUP_THREAD_H__


#include "thread/thread.h"
#include "battleInfo.h"


namespace game {
	
namespace battle {

	
class BattleExecutor;
class StageGenerator;
class ForceGenerator;
class BattleEventSender;

	
//=============================================================================
/*!
						バトルセットアップスレッド
*/
//=============================================================================
class BattleExecutorSetupThread : public nk::Thread {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		バトル設定
	*/
	//===========================================================================
	void			Setup(
		BattleExecutor*		battleExecutor,
		const BattleInfo&	battleInfo,
		StageGenerator*		stageGenerator,
		ForceGenerator*		forceGenerator,
		BattleEventSender*	eventSender
	);

	//===========================================================================
	/*!	@brief		セットアップ終了したらtrueを返す
	*/
	//===========================================================================
	bool			IsSetupEnd( void ) const;
	
protected:
	
	//===========================================================================
	/*!	@brief		スレッド処理
	*/
	//===========================================================================
	virtual void	ThreadFunc( void );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	BattleExecutor*		m_battleExecutor;		//!< バトル
	BattleInfo			m_battleInfo;			//!< 対戦情報
	StageGenerator*		m_stageGenerator;		//!< ステージ生成
	ForceGenerator*		m_forceGenerator;		//!< 軍生成
	BattleEventSender*	m_eventSender;			//!< イベント生成

public:
	//-------------コンストラクタ・デストラクタ--------------
			BattleExecutorSetupThread();
	virtual~BattleExecutorSetupThread();
};
	
}	// namespace battle
	
}	// namespace game


#endif  // __BATTLE_EXECUTOR_SETUP_THREAD_H__