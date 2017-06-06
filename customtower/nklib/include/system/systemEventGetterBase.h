//=============================================================================
/*!	@file	systemEventGetterBase.h

	@brief	システムイベント取得インターフェース

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================


#ifndef __SYSTEM_EVENT_GETTER_BASE_H__
#define __SYSTEM_EVENT_GETTER_BASE_H__

#include "eventGetterBase.h"
#include "systemEvent.h"



namespace nk {
namespace system {

//=============================================================================
/*!
					システムイベント取得インターフェース
*/
//=============================================================================
class SystemEventGetterBase : public EventGetterBase {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		イベント取得
	*/
	//===========================================================================
	bool	IsOn( u32 eventType ) const { return false; }
	
private:
	//-----------------------メソッド------------------------

	
	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			SystemEventGetterBase() : EventGetterBase() {}
	virtual~SystemEventGetterBase() {}
};
	
}	// namespace system
}	// namespace nk



#endif  // __SYSTEM_EVENT_GETTER_BASE_H__