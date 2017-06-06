//=============================================================================
/*!	@file	gameObject.h

	@brief	ゲームオブジェクト

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "system.h"

#include "system/updateObject.h"
#include "system/renderObject.h"

namespace game {

class GameMain;
class GameObjectManager;
	
//=============================================================================
/*!
					ゲームオブジェクトインターフェース
*/
//=============================================================================
class GameObject /*: public UpdateObject,*//* public RenderObject*/ {
private:
	friend class GameMain;
	
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------

	
	//-----------------------メソッド------------------------
	
	//===========================================================================
	/*!	@brief		システムコールバック
		@param		event	イベント
	*/
	//===========================================================================
	virtual void		CallbackSystemEvent( nk::Main::SYSTEM_EVENT event ) {}
	
	
	//===========================================================================
	/*!	@brief		ゲーム管理
	*/
	//===========================================================================
	static GameMain*	GetGameManager( void )				{ return m_gameManager;		}
	
private:
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

	//----------------------メンバ変数-----------------------

	static	GameObjectManager*	m_gameObjectManager;	//!< ゲームオブジェクト管理
	static	GameMain*			m_gameManager;			//!< ゲーム管理
public:
	//-------------コンストラクタ・デストラクタ--------------
			GameObject();
	virtual~GameObject();
};

}	// namespace game





#endif  // __GAME_OBJECT_H__