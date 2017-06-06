//=============================================================================
/*!	@file	treeTask

	@brief	ツリータスク

	@author	ryunosuke ide
	@date	2013.03.17
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/system/treeTask.h"
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
TreeTask::TreeTask()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
TreeTask::~TreeTask()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void TreeTask::_Init()
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void TreeTask::_Term()
{
	DisconnectAllChild();
	
}



//===========================================================================
/*!	@brief		更新
	@param		parentParam		ユーザーパラメーター
	@return		----
*/
//===========================================================================
void TreeTask::UpdateChild( void* parentParam )
{
	std::list<Task*>::iterator	itr	= m_childList.begin();
	std::list<Task*>::iterator	end	= m_childList.end();

	for( ; itr != end; ++itr ) {
		if( *itr ) {
			(*itr)->Execute( parentParam );
			(*itr)->UpdateChild( parentParam );
		}
	}
	
}



//===========================================================================
/*!	@brief		子供を追加
	@param		task	子供
	@return		----
*/
//===========================================================================
void TreeTask::ConnectChild( Task* task )
{
	
	m_childList.push_back( task );
	
}

//===========================================================================
/*!	@brief		子供を切り離す
	@param		task	子供
	@return		----
*/
//===========================================================================
void TreeTask::DisconnectChild( Task* task )
{
	std::list<Task*>::iterator	itr	= m_childList.begin();
	std::list<Task*>::iterator	end	= m_childList.end();

	for( ; itr != end; ++itr ) {
		if( (*itr) && (*itr == task) ) {
			(*itr)->DisconnectAllChild();

			DISCONNECT( *itr );
			itr	= m_childList.erase( itr );
			
			break;
		}
	}
	
}



//===========================================================================
/*!	@brief		子供を切り離す
	@param		----
	@return		----
*/
//===========================================================================
void TreeTask::DisconnectAllChild( void )
{
	std::list<Task*>::iterator	itr	= m_childList.begin();
	std::list<Task*>::iterator	end	= m_childList.end();

	for( ; itr != end; ++itr ) {
		if( *itr ) {
			(*itr)->DisconnectAllChild();

			DISCONNECT( *itr );
		}
	}
	m_childList.clear();
	
}
	
}	// namaespace system	
}	// namespace nk



