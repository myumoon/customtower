//=============================================================================
/*!	@file	hitListener.h

	@brief	ヒット結果リスナー

	@author	ryunosuke ide
	@date	2013.05.29
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "./hitListener.h"


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
HitListener::HitListener()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
HitListener::~HitListener()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void HitListener::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void HitListener::_Term( void )
{

}



}	// namespace battle

	
}	// namespace game
