//=============================================================================
/*!	@file	keyboardEventGetter.h

	@brief	キーボードイベント取得

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/system/keyboardEventGetter.h"
#include "../../include/system/eventGetter.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {
namespace system {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
KeyboardEventGetter::KeyboardEventGetter() : KeyboardEventGetterBase()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
KeyboardEventGetter::~KeyboardEventGetter()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void KeyboardEventGetter::_Init( void )
{
	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void KeyboardEventGetter::_Term( void )
{

}


//===========================================================================
/*!	@brief		押下チェック
	@param		button	ボタン番号
	@return		----
*/
//===========================================================================
bool KeyboardEventGetter::IsOn( u32 key ) const
{
	
	return m_event.IsOn( key );
}

//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void KeyboardEventGetter::Update( void )
{
	
	m_event	= EventGetter::GetInstance()->GetKeyboardEvent();
	
}
	
}	// namespace system
}	// namespace nk
