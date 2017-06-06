//=============================================================================
/*!	@file	battleObject.h

	@brief	対戦オブジェクト

	@author	ryunosuke ide
	@date	2013.06.04
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "battleObject.h"


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
BattleObject::BattleObject()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
BattleObject::~BattleObject()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void BattleObject::_Init( void )
{
	m_battleExec	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void BattleObject::_Term( void )
{

}

#if 0
//===========================================================================
/*!	@brief		重力落下
	@param		----
	@return		----
*/
//===========================================================================
void BattleObject::FreeFall( void )
{
	nk::math::Vector&	fallVec	= GetFallVelocityVec( GetPos() );		// 落下ベクトル
	
 	SetPos( GetPos() + fallVec );
}
#endif
//===========================================================================
/*!	@brief		位置設定
	@param		pos		位置
	@return		----
*/
//===========================================================================
// void BattleObject::SetPos( const nk::math::Vector& pos )
// {
// 	m_nowPos	= pos;
// }

//===========================================================================
/*!	@brief		位置取得
	@param		----
	@return		----
*/
//===========================================================================
// const nk::math::Vector& BattleObject::GetPos( void ) const
// {
// 	
// 	return m_nowPos;
// }


//===========================================================================
/*!	@brief		前回位置設定
	@param		pos		位置
	@return		----
*/
//===========================================================================
void BattleObject::SetPrevPos( const nk::math::Vector& pos )
{
	m_prevPos	= pos;
}

	
//===========================================================================
/*!	@brief		位置取得
	@param		----
	@return		----
*/
//===========================================================================
const nk::math::Vector& BattleObject::GetPrevPos( void ) const
{
	
	return m_prevPos;
}


}	// namespace battle
	
}	// namespace game