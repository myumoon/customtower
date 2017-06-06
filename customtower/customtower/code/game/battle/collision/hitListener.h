//=============================================================================
/*!	@file	hitListener.h

	@brief	ヒット結果リスナー

	@author	ryunosuke ide
	@date	2013.05.29
*/
//=============================================================================


#ifndef __HIT_LISTENER_H__
#define __HIT_LISTENER_H__

#include "collision/boundaryVolume.h"

namespace game {
namespace battle {


class Stage;
class Character;

//=============================================================================
/*!
								ヒットリスナー
*/
//=============================================================================
class HitListener {
private:
public:
	//-----------------------型定義--------------------------

	//! イベントタイプ
	enum EVENT_TYPE {
		EVENT_TYPE_TARGET_CHECK,		//!< ターゲットチェック
		EVENT_TYPE_HIT_RESULT,			//!< ヒット結果
	};
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		イベントチェック
	*/
	//===========================================================================
	virtual bool	AcceptEvent( HitListener* target, EVENT_TYPE event ) { return true; }


	//===========================================================================
	/*!	@brief		ヒットターゲットチェック
	*/
	//===========================================================================
	virtual bool	IsHitTarget( const Stage* target ) const { return true; }
	virtual bool	IsHitTarget( const Character* target ) const { return true; }

	//===========================================================================
	/*!	@brief		ヒット時コールバック
	*/
	//===========================================================================
	virtual void	Hit( const Stage* target ) {}
	virtual void	Hit( const Character* target ) {}

	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			HitListener();
	virtual~HitListener();
};

}	// namespace battle

	
}	// namespace game






#endif  // __HIT_LISTENER_H__