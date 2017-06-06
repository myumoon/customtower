//=============================================================================
/*!	@file	force.h

	@brief	軍

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __FORCE_H__
#define __FORCE_H__

#include <queue>
#include "../battleObject.h"
#include "game/battle/character/characterGenerator.h"
#include "game/battle/character/characterManager.h"
#include "game/battle/character/characterEmitter.h"
#include "game/battle/earth/earthObjectManager.h"
#include "opponentForce.h"

namespace game {

namespace battle {


//=============================================================================
/*!
								軍
*/
//=============================================================================
class Force {
public:
	//-----------------------型定義--------------------------

	//! 入力コマンド
	enum OPERATE_COMMAND {
		OPERATE_COMMAND_NONE,
	};
	
	//! 操作情報
	struct OperateInfo {
		u64					frame;		//!< 入力フレーム
		OPERATE_COMMAND		command;	//!< 入力コマンド

		//! コンストラクタ
		OperateInfo( void ) {
			this->frame		= 0;
			this->command	= OPERATE_COMMAND_NONE;
		}
	};
	typedef std::queue<OperateInfo>	QueueOperateInfo;		//!< 入力コマンド
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	virtual void	Initialize( BattleExecutor* battle );

	//===========================================================================
	/*!	@brief		終了
	*/
	//===========================================================================
	virtual void	Terminate( void );

	//===========================================================================
	/*!	@brief		操作チェック
	*/
	//===========================================================================
	virtual void	UpdatePhase_Operate( const OpponentForce& opponent ) {}

	//===========================================================================
	/*!	@brief		移動フェイズ
	*/
	//===========================================================================
	virtual void	UpdatePhase_Move( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		移動後位置修正フェイズ
	*/
	//===========================================================================
	virtual void	UpdatePhase_MoveFix( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		攻撃フェイズ
	*/
	//===========================================================================
	virtual void	UpdatePhase_Attack( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		ヒット後フェイズ
	*/
	//===========================================================================
	virtual void	UpdatePhase_AfterHit( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		フレーム開始
	*/
	//===========================================================================
	virtual void	UpdatePhase_FrameInitialize( void );
	
	//===========================================================================
	/*!	@brief		フレーム終了
	*/
	//===========================================================================
	virtual void	UpdatePhase_FrameTerminate( void );

	//===========================================================================
	/*!	@brief		入力コマンド追加
	*/
	//===========================================================================
	void					PushOperateInfo( const OperateInfo& info );

	//===========================================================================
	/*!	@brief		入力コマンド取得
	*/
	//===========================================================================
	void					PopOperateInfo( void );
	const OperateInfo&		GetNowFrameOperateInfo( void ) const;

	
protected:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

protected:
	//----------------------メンバ変数-----------------------
	const BattleExecutor* 		m_battle;					//!< バトル

	EarthObjectManager			m_earthOvjectManager;		//!< 地球上のオブジェクト管理

	QueueOperateInfo			m_operateInfo;				//!< 入力コマンド
	OperateInfo					m_nowFrameOperateInfo;		//!< 現在フレーム入力情報
	
	CharacterGenerator			m_characterGenerator;		//!< キャラクタージェネレーター
	CharacterManager			m_characterManager;			//!< キャラクター管理
	CharacterEmitter			m_characterEmitter;			//!< キャラクターエミッター
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			Force();
	virtual~Force();
};


}	// namespace battle

	
}	// namespace game







#endif  // __FORCE_H__