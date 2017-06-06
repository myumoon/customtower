//=============================================================================
/*!	@file	listTask

	@brief	リストタスク

	@author	ryunosuke ide
	@date	2013.03.17
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/system/listTask.h"
#include "../../include/general.h"


//--------------------------------define定義--------------------------------
#define DISCONNECT(child)	{ SafeDelete(child);	}
//#define DISCONNECT(child)	{ child	= NULL;	}


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
ListTask::ListTask()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
ListTask::~ListTask()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void ListTask::_Init()
{
	m_child		= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void ListTask::_Term()
{
	if( m_child ) {
		m_child->DisconnectAllChild();
		SafeDelete( m_child );
	}
	
}



//===========================================================================
/*!	@brief		更新
	@param		parentParam		ユーザーパラメーター
	@return		----
*/
//===========================================================================
void ListTask::UpdateChild( void* parentParam )
{

	if( m_child ) {
		m_child->Execute( parentParam );
		m_child->UpdateChild( parentParam );
	}
	
}


//===========================================================================
/*!	@brief		子供を追加
	@param		task	子供
	@return		----
	@note		既に子供が設定されていた場合はその子供と取り替えます
*/
//===========================================================================
void ListTask::ConnectChild( Task* task )
{
	if( m_child ) {
		DisconnectChild( m_child );
	}

	m_child	= task;
	
}

//===========================================================================
/*!	@brief		子供を切り離す
	@param		task	子供
	@return		----
*/
//===========================================================================
void ListTask::DisconnectChild( Task* task )
{
	if( m_child && (m_child == task) ) {
		DisconnectAllChild();
	}
}



//===========================================================================
/*!	@brief		子供を切り離す
	@param		----
	@return		----
*/
//===========================================================================
void ListTask::DisconnectAllChild( void )
{
	if( m_child ) {
		m_child->DisconnectAllChild();

		DISCONNECT( m_child );
	}
	
}


}	// namaespace system
}	// namespace nk



