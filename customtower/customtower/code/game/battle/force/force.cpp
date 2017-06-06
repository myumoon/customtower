//=============================================================================
/*!	@file	force.h

	@brief	軍

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "force.h"
#include "gameDef.h"
#include "../battleExecutor.h"

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
Force::Force()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Force::~Force()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Force::_Init( void )
{
	m_battle	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Force::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		battle		バトル管理
	@return		----
*/
//===========================================================================
void Force::Initialize( BattleExecutor* battle )
{
	m_battle	= battle;

	m_characterEmitter.Setup( battle, &m_characterGenerator, &m_characterManager );
	m_characterManager.Initialize();
	m_characterGenerator.Setup( *battle->GetBattleInfo() );

	// 重力処理登録
	m_earthOvjectManager.RegisterEarthObject( &m_characterManager );
}


//===========================================================================
/*!	@brief		終了
	@param		----
	@return		----
*/
//===========================================================================
void Force::Terminate( void )
{
	m_characterManager.Terminate();

	m_earthOvjectManager.Clear();

}


//===========================================================================
/*!	@brief		移動フェイズ
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_Move( const OpponentForce& opponent )
{
	const OperateInfo&	nowFrameInfo	= GetNowFrameOperateInfo();

	// 前回位置記憶
	m_characterManager.PushPrevPos();

	// 重力処理
	m_earthOvjectManager.AcceptProjection();
	
	// キャラクター移動
	m_characterManager.UpdateMove();
}


//===========================================================================
/*!	@brief		移動後位置修正フェイズ
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_MoveFix( const OpponentForce& opponent )
{

}


//===========================================================================
/*!	@brief		攻撃フェイズ
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_Attack( const OpponentForce& opponent )
{

}


//===========================================================================
/*!	@brief		ヒット後フェイズ
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_AfterHit( const OpponentForce& opponent )
{
	//m_characterManager.Remove( &m_characterGenerator );
}


//===========================================================================
/*!	@brief		入力情報push
	@param		info	入力情報
	@return		----
*/
//===========================================================================
void Force::PushOperateInfo( const OperateInfo& info )
{
	m_operateInfo.push( info );
	
}


//===========================================================================
/*!	@brief		フレーム開始処理
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_FrameInitialize( void )
{
	
}
	
//===========================================================================
/*!	@brief		フレーム終了処理
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_FrameTerminate( void )
{
	m_characterManager.RemoveReservedCharacters();
	
}

//===========================================================================
/*!	@brief		入力情報取得
	@param		----
	@return		----
*/
//===========================================================================
void Force::PopOperateInfo( void )
{
	const u64	nowFrame	= m_battle->GetFrame();
	
	// 指定フレーム待った後に取得開始
	if( BATTLE_INPUT_DELAY_FRAME <= nowFrame ) {

		// 空だったら空の情報を入れておく
		if( m_operateInfo.empty() ) {
			m_nowFrameOperateInfo	= OperateInfo();
		}
		else {
			do {
				m_nowFrameOperateInfo	= m_operateInfo.front();
				m_operateInfo.pop();
			} while( m_nowFrameOperateInfo.frame < nowFrame - BATTLE_INPUT_DELAY_FRAME );
		}
	}

}

//===========================================================================
/*!	@brief		入力コマンド取得
	@param		----
	@return		----
*/
//===========================================================================
const Force::OperateInfo& Force::GetNowFrameOperateInfo( void ) const
{
	
	return m_nowFrameOperateInfo;
}


}	// namespace battle
	
}	// namespace game