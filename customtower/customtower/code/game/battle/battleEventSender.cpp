//=============================================================================
/*!	@file	battleEventSender.cpp

	@brief	バトルにイベント通知

	@author	ryunosuke ide
	@date	2013.06.24
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "battleEventSender.h"
#include "utility/stringfunction.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace game {

namespace battle {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
BattleEventSender::BattleEventSender()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
BattleEventSender::~BattleEventSender()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void BattleEventSender::_Init( void )
{
	m_battleExecutor	= NULL;
	m_keyboard			= NULL;
	m_mouse				= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void BattleEventSender::_Term( void )
{

}


//===========================================================================
/*!	@brief		バトル設定
	@param		battle	バトル
	@return		----
*/
//===========================================================================
void BattleEventSender::SetBattleExecutor( BattleExecutor* battle )
{
	m_battleExecutor	= battle;
}


//===========================================================================
/*!	@brief		キーボード設定
	@param		keyboard	キーボード
	@return		----
*/
//===========================================================================
void BattleEventSender::SetKeyboard( const nk::input::Keyboard* keyboard )
{
	m_keyboard	= keyboard;
}


//===========================================================================
/*!	@brief		マウス設定
	@param		mouse	マウス
	@return		----
*/
//===========================================================================
void BattleEventSender::SetMouse( const nk::input::Mouse* mouse )
{
	m_mouse	= mouse;
}


//--------------------------------ボタンイベントコールバック--------------------------------


//===========================================================================
/*!	@brief		押された瞬間(アニメーション開始時)
*/
//===========================================================================
void BattleEventSender::OnCursorDownStart( nk::graphics::Button* eventButton )
{
	if( nk::Compare( eventButton->GetName(), "" ) ) {
	}
}
	
}	// namespace battle
	
}	// namespace game