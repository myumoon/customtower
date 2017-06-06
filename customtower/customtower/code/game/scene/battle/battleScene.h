//=============================================================================
/*!	@file	battleScene.h

	@brief	バトルシーン基底

	@author	ryunosuke ide
	@date	2013.06.24
*/
//=============================================================================

#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "game/scene/sceneInterface.h"
#include "game/battle/generator.h"
#include "game/battle/battleInfo.h"
#include "game/battle/battleExecutor.h"
#include "game/battle/battleEventSender.h"
#include "game/battle/battleExecutorSetupThread.h"

// ジェネレーター
#include "game/battle/stage/stageGenerator.h"
#include "game/battle/force/forceGenerator.h"
#include "game/battle/character/characterGenerator.h"



namespace game {

//=============================================================================
/*!
								通常バトル
*/
//=============================================================================
class BattleScene : public SceneInterface {
public:
	//-----------------------型定義--------------------------
//	typedef std::vector<battle::Generator*>		VecGenerator;	//!< ジェネレーター

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	virtual void	InitializeScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		終了
	*/
	//===========================================================================
	virtual void	TerminateScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	virtual void	RenderLocal( void );

protected:
	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual s32		ExecuteLocal( s32 parentMessage );

	//===========================================================================
	/*!	@brief		ジェネレーター登録
	*/
	//===========================================================================
//	void			RegisterGenerator( battle::Generator* generator );

	//===========================================================================
	/*!	@brief		ジェネレーーセットアップ
	*/
	//===========================================================================
	void			SetupGenerator( const battle::BattleInfo& info );

	//===========================================================================
	/*!	@brief		ジェネレーターで生成したインスタンスを削除
	*/
	//===========================================================================
	void			CallGeneratorDelete( void );
	
protected:
	//-----------------------メソッド------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------メンバ変数-----------------------
	battle::BattleExecutorSetupThread*	m_battleExecutorSetupThread;	//!< 対戦セットアップスレッド
	battle::BattleExecutor*				m_battleExecutor;				//!< 対戦処理
	battle::StageGenerator				m_stageGenerator;				//!< ステージジェネレーター
	battle::ForceGenerator				m_forceGenerator;				//!< 軍ジェネレーター
	battle::BattleEventSender			m_battleEventSender;			//!< バトルイベント送信者
	nk::graphics::Layout				m_layout;						//!< レイアウト
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			BattleScene();
	virtual~BattleScene();
};


	
}	// namespace game





#endif  // __BATTLE_SCENE_H__

