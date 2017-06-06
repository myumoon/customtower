//=============================================================================
/*!	@file	ステージ

	@brief	ステージ

	@author	ryunosuke ide
	@date	2013.05.27
*/
//=============================================================================

#ifndef __STAGE_H__
#define __STAGE_H__

#include "graphics/model.h"
#include "graphics/animationModel.h"
#include "collision/boundaryVolume.h"

#include "game/gameObject.h"
#include "game/battle/collision/hitListener.h"

#include "game/battle/battleObject.h"

namespace game {

namespace battle {

class Character;

//=============================================================================
/*!
								ステージ
*/
//=============================================================================
class Stage : public BattleObject, public HitListener {
public:
	//-----------------------型定義--------------------------

	//! ステージ情報
	struct StageInfo {
		f32					radius;			//!< 半径
		nk::math::Vector	centerPos;		//!< 中心位置
		f32					gravity;		//!< 重力
		f32					airResistance;	//!< 空気抵抗
	};

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		バトル生成時初期化
	*/
	//===========================================================================
	void				InitializeForBattle( BattleExecutor* battleExec );

	//===========================================================================
	/*!	@brief		バトル消滅時終了処理
	*/
	//===========================================================================
	void				TerminateForBattle( void );
	
	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual bool		Execute( void );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	virtual void		Render( void );

	//===========================================================================
	/*!	@brief		ターゲットチェック
	*/
	//===========================================================================
	virtual bool		AcceptEvent( HitListener* target, EVENT_TYPE event )
	{
		switch( event ) {
			case EVENT_TYPE_TARGET_CHECK : {
				return target->IsHitTarget( this );
			} break;
			
			case EVENT_TYPE_HIT_RESULT : {
				target->Hit( this );
			} break;
		}
		
		return false;
	}

	//===========================================================================
	/*!	@brief		対象チェック
	*/
	//===========================================================================
	virtual bool		IsHitTarget( const Stage* target ) const { return true; }
	virtual bool		IsHitTarget( const Character* target ) const { return true; }

	//===========================================================================
	/*!	@brief		ヒット反応
	*/
	//===========================================================================
	virtual void		Hit( const Stage* target ) {}
	virtual void		Hit( const Character* target ) {}


	//===========================================================================
	/*!	@brief		基本情報取得
	*/
	//===========================================================================
	const StageInfo&	GetInfo( void ) const;
	
protected:
	//===========================================================================
	/*!	@brief		ローカル更新
	*/
	//===========================================================================
	virtual bool		ExecuteLocal( void ) { return true; }

protected:
	//----------------------メンバ変数-----------------------
	nk::BVSphere				m_bvSphere;
	StageInfo					m_stageInfo;		//!< ステージ情報
	nk::graphics::Model*		m_stageModel;		//!< モデル
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			Stage();
	virtual~Stage();
};


}	// namespace battle
	
}	// namespace game






#endif  // __STAGE_H__