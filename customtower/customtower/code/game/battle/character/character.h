//=============================================================================
/*!	@file	character.h

	@brief	キャラクター

	@author	ryunosuke ide
	@date	2013.05.31
*/
//=============================================================================

#ifndef __CHARACTER_H__
#define __CHARACTER_H__


#include "graphics/model.h"
#include "graphics/animationModel.h"
#include "collision/boundaryVolume.h"

#include "system/renderObject.h"
#include "game/battle/battleObject.h"
//#include "game/gameObject.h"
#include "game/battle/collision/hitListener.h"


namespace game {

namespace battle {

class CharacterManager;
class Stage;

//=============================================================================
/*!
								キャラクター
*/
//=============================================================================
class Character : public BattleObject, public HitListener {
public:
	//-----------------------型定義--------------------------
	

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
	/*!	@brief		移動
	*/
	//===========================================================================
	virtual void		Move( void );

	//===========================================================================
	/*!	@brief		攻撃
	*/
	//===========================================================================
	virtual void		Attack( void ) {}
	
	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	virtual void		Render( void ) {}

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
	virtual void		Hit( const Stage* target );
	virtual void		Hit( const Character* target );

	//===========================================================================
	/*!	@brief		キャラクターマネージャーセット
	*/
	//===========================================================================
	void				SetCharacterManager( const CharacterManager* mng );

	//===========================================================================
	/*!	@brief		移動速度設定
	*/
	//===========================================================================
	void				SetMoveSpeed( f32 speed );
	
protected:

	//===========================================================================
	/*!	@brief		右移動
	*/
	//===========================================================================
	virtual void			MoveRight( void );

	//===========================================================================
	/*!	@brief		左移動
	*/
	//===========================================================================
	virtual void			MoveLeft( void );
	
	//===========================================================================
	/*!	@brief		キャラクターマネージャー取得
	*/
	//===========================================================================
	const CharacterManager*	GetCharacterManager( void ) const;

protected:
	//----------------------メンバ変数-----------------------
	const CharacterManager*		m_characterManager;		//!< キャラクターマネージャー
	nk::BVSphere				m_bvSphere;				//!< 当たり

	f32							m_moveSpeed;			//!< 移動速度
	f32							m_moveRotation;			//!< 移動回転量
// 	nk::math::Quaternion		m_moveRotation;			//!< 移動回転量
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );


public:
	//-------------コンストラクタ・デストラクタ--------------
			Character( void );
			Character( const CharacterManager* mng );
	virtual~Character( void );
};


}	// namespace battle
	
}	// namespace game



#endif  // __CHARACTER_H__