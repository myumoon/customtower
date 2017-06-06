//=============================================================================
/*!	@file	battleExecutor.h

	@brief	対戦処理実行
			対戦オブジェクトの動作部分を担当
			メニュー等はここから情報を引っ張る

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

#ifndef __BATTLE_EXECUTOR_H__
#define __BATTLE_EXECUTOR_H__

#include "graphics/layout.h"


//#include "game/battle/character/character.h"
//#include "game/battle/stage/stage.h"
#include "game/battle/stage/stageGenerator.h"
//#include "game/battle/force/force.h"
#include "game/battle/force/forceGenerator.h"
#include "game/battle/force/opponentForce.h"


namespace game {
namespace battle {


class Force;
class Stage;
class CollisionObjectManager;
	
//=============================================================================
/*!
								対戦実行者
*/
//=============================================================================
class BattleExecutor {
public:
	//-----------------------型定義--------------------------
	typedef std::vector<Force*>			VecForce;				//!< 軍リスト
	typedef std::vector<OpponentForce>	VecOpponentForce;		//!< 敵軍リスト
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	void	Initialize(
		const BattleInfo&		battleInfo,
		ForceGenerator*			forceGenerator,
		StageGenerator*			stageGenerator
	);

	//===========================================================================
	/*!	@brief		終了
	*/
	//===========================================================================
	void	Terminate( void );


	//===========================================================================
	/*!	@brief		実行
	*/
	//===========================================================================
	void	Update( void );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
  	void	Render( void );

	//===========================================================================
	/*!	@brief		現在フレーム取得
	*/
	//===========================================================================
	u64		GetFrame( void ) const;

	//===========================================================================
	/*!	@brief		対戦情報取得
	*/
	//===========================================================================
	const BattleInfo*	GetBattleInfo( void ) const;

	//===========================================================================
	/*!	@brief		ヒット管理取得
	*/
	//===========================================================================
	CollisionObjectManager*	GetCollisionObjectManager( void );

	//===========================================================================
	/*!	@brief		ステージ取得
	*/
	//===========================================================================
	const Stage*			GetStage( void ) const;

protected:
	//===========================================================================
	/*!	@brief		軍生成
	*/
	//===========================================================================
	void	GenerateForce( ForceGenerator* forceGenerator );

	//===========================================================================
	/*!	@brief		ステージ生成
	*/
	//===========================================================================
	void	GenerateStage( StageGenerator* stageGenerator );

	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
 	BattleInfo				m_battleInfo;				//!< 対戦情報
	u64						m_battleFrame;				//!< 対戦フレーム
	ForceList*				m_forceList;				//!< 軍リスト
	Stage*					m_stage;					//!< ステージ
	CollisionObjectManager*	m_collisionObjectManager;	//!< ヒット管理
	
	nk::graphics::Layout	m_layout;			//!< レイアウト
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			BattleExecutor();
	virtual~BattleExecutor();
};
	

}	// namespace battle

}	// namespace game




#endif  // __BATTLE_EXECUTOR_H__