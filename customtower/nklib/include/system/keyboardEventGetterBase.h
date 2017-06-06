//=============================================================================
/*!	@file	keyboardEventGetterBase.h

	@brief	キーボードイベント取得インターフェース

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

#ifndef __KEYBOARD_EVENT_GETTER_BASE_H__
#define __KEYBOARD_EVENT_GETTER_BASE_H__

#include "eventGetterBase.h"
#include "keyboardEvent.h"

namespace nk {
namespace system {


//=============================================================================
/*!
					キーボードイベント取得インターフェ－ス
*/
//=============================================================================
class KeyboardEventGetterBase : public EventGetterBase {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		イベント取得
		@param		KeyboardEvent定数
	*/
	//===========================================================================
	virtual bool	IsOn( u32 key ) const { return false; }
	
private:
	//-----------------------メソッド------------------------

	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			KeyboardEventGetterBase() : EventGetterBase() {}
	virtual~KeyboardEventGetterBase() {}
};
	
}	// namespace system
}	// namespace nk






#endif  // __KEYBOARD_EVENT_GETTER_BASE_H__