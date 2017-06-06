//=============================================================================
/*!	@file	controlPlayerForce.h

	@brief	プレイヤー操作軍

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

#ifndef __CONTROL_PLAYER_FORCE_H__
#define __CONTROL_PLAYER_FORCE_H__

#include "../force.h"



namespace game {

namespace battle {

//=============================================================================
/*!
							プレイヤー操作軍
*/
//=============================================================================
class ControlPlayerForce : public Force {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	virtual void	Initialize( BattleExecutor* battleExec );

	//===========================================================================
	/*!	@brief		終了
	*/
	//===========================================================================
	virtual void	Terminate( void );

	//===========================================================================
	/*!	@brief		操作チェック
	*/
	//===========================================================================
	virtual void	UpdatePhase_Operate( const OpponentForce& opponent );

protected:

	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			ControlPlayerForce();
	virtual~ControlPlayerForce();
};


}	// namespace battle
	
}	// namespace game



#endif  // __CONTROL_PLAYER_FORCE_H__