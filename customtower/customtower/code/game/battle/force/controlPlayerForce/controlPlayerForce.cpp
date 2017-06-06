//=============================================================================
/*!	@file	controlPlayerForce.h

	@brief	プレイヤー操作軍

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "controlPlayerForce.h"


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
ControlPlayerForce::ControlPlayerForce()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
ControlPlayerForce::~ControlPlayerForce()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void ControlPlayerForce::_Init( void )
{
	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void ControlPlayerForce::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		----
	@return		----
*/
//===========================================================================
void ControlPlayerForce::Initialize( BattleExecutor* battleExec )
{
	Force::Initialize( battleExec );
	
	m_characterEmitter.SetPos( nk::math::Vector( 0.0f, 100.0f, 0.0f ) );
	m_characterEmitter.SetDirection( nk::math::Vector( -1.0f, 1.0f, 0.0f ), 10 );
	m_characterEmitter.SetVelocity( 30.0f );
	m_characterEmitter.SetRotation( nk::math::Vector(0.0f, 0.0f, 5.0f) );
 	m_characterEmitter.SetEmitInterval( 30 );
	m_characterEmitter.SetLife( 30 * 60 );
  	m_characterEmitter.Emit();
}


//===========================================================================
/*!	@brief		終了
	@param		----
	@return		----
*/
//===========================================================================
void ControlPlayerForce::Terminate( void )
{
	Force::Terminate();
}

//===========================================================================
/*!	@brief		操作チェック
	@param		----
	@return		----
*/
//===========================================================================
void ControlPlayerForce::UpdatePhase_Operate( const OpponentForce& opponent )
{
// 	m_characterEmitter.Update();
}



}	// namespace battle

	
}	// namespace game