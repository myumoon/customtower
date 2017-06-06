//=============================================================================
/*!	@file	forceGenerator.h

	@brief	軍生成

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "forceGenerator.h"

#include "general.h"

#include "force.h"
#include "game/battle/battleInfo.h"
#include "controlPlayerForce/controlPlayerForce.h"

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
ForceGenerator::ForceGenerator()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
ForceGenerator::~ForceGenerator()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void ForceGenerator::_Init( void )
{
	m_forceList	= new ForceList();
	m_forceList->forces.reserve( BattleInfo::MAX_CONTROLLER_NUM );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void ForceGenerator::_Term( void )
{
	Delete();
	nk::SafeDelete( m_forceList );

}


//===========================================================================
/*!	@brief		生成
	@param		m_battleInfo	生成情報
	@return		----
*/
//===========================================================================
// const std::vector<Force*>& ForceGenerator::Generate( void )
ForceList* ForceGenerator::Generate( void )
{
	Delete();

	Force*	createForce	= NULL;

	for( s32 forceNo = 0; forceNo < m_battleInfo.contorollerNum; ++forceNo ) {
		createForce	= NULL;
		
		switch( m_battleInfo.contorollerTypes[forceNo] ) {
			
			case BattleInfo::CONTOROLLER_TYPE_USER : {
				createForce	= new ControlPlayerForce();
			} break;

			default : {
				// @@@@@
				createForce	= new ControlPlayerForce();
			} break;
		}

		if( createForce ) {
			m_forceList->forces.push_back( createForce );
		}
	}

	return m_forceList;
}



//===========================================================================
/*!	@brief		削除
	@param		----
	@return		----
*/
//===========================================================================
void ForceGenerator::Delete( void )
{
	NULL_ASSERT( m_forceList );

	for( u32 i = 0; i < m_forceList->forces.size(); ++i ) {
		nk::SafeDelete( m_forceList->forces[i] );
	}
	m_forceList->forces.clear();
	
// 	for( u32 i = 0; i < m_forces.size(); ++i ) {
// 		nk::SafeDelete( m_forces[i] );
// 	}
// 	m_forces.clear();

}


}	// namespace battle


	
}	// namespace game