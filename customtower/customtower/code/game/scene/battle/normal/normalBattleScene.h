//=============================================================================
/*!	@file	normalBattleScene.h

	@brief	通常バトル

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __NORMALL_BATTLE_SCENE_H__
#define __NORMALL_BATTLE_SCENE_H__

#include "../battleScene.h"

#include "game/scene/sceneInterface.h"
#include "game/battle/generator.h"
#include "game/battle/battleInfo.h"
#include "game/battle/battleExecutor.h"

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
class NormalBattleScene : public BattleScene {
public:
	//-----------------------型定義--------------------------

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

private:
	//-----------------------メソッド------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------メンバ変数-----------------------
	battle::BattleExecutor*			m_battleExecutor;		//!< 対戦処理
	battle::StageGenerator			m_stageGenerator;		//!< ステージジェネレーター
	battle::ForceGenerator			m_forceGenerator;		//!< 軍ジェネレーター
	battle::CharacterGenerator		m_characterGenerator;	//!< キャラジェネレーター
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			NormalBattleScene();
	virtual~NormalBattleScene();
};
	
}	// namespace game



#endif  // __NORMALL_BATTLE_SCENE_H__