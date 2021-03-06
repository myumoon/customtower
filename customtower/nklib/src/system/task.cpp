//=============================================================================
/*!	@file	task.h

	@brief	タスクベース

	@author	ryunosuke ide
	@date	2012.06.07
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/system/task.h"


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
Task::Task()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Task::~Task()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Task::_Init()
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Task::_Term()
{

}


}	// namespace system
}	// namespace nk
