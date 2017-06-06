//=============================================================================
/*!	@file	taskManager.cpp

	@brief	タスク管理

	@author	ryunosuke ide
	@date	2012.06.07
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/system/taskManager.h"

#include "../../include/general.h"
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
	@param	
*/
//===========================================================================
TaskManager::TaskManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
TaskManager::~TaskManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void TaskManager::_Init()
{
	m_vecTaskRoot.reserve( DEFAULT_MAX_TASK );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void TaskManager::_Term()
{
	Clear();
}


//===========================================================================
/*!	@brief	ルートタスクを追加
	@param	root	: ルートタスク
	@return	----
*/
//===========================================================================
void TaskManager::AddRoot( Task* root, s32 taskId )
{
	TaskData	data;
	data.task	= root;
	data.id		= taskId;

	m_vecTaskRoot.push_back( data );

}



//===========================================================================
/*!	@brief	ルートタスクを習得
	@param	タスクID(デフォルトで0)
	@return	ルートタスク
*/
//===========================================================================
Task* TaskManager::GetRoot( s32 taskId )
{
	Task*	retTask	= NULL;
	s32		size	= m_vecTaskRoot.size();

	ASSERT( taskId < size, "taskId : %d", taskId );
	if( size <= taskId ) {
		return NULL;
	}

	for( s32 i = 0; i < size; ++i ) {
		if( m_vecTaskRoot[i].id == taskId ) {
			retTask	= m_vecTaskRoot[i].task;
		}
	}

	return retTask;
}



//===========================================================================
/*!	@brief	更新
	@param	----
	@return	----
*/
//===========================================================================
bool TaskManager::Update()
{
	bool ret	= true;
	std::vector<TaskData>::iterator	itr	= m_vecTaskRoot.begin();
	std::vector<TaskData>::iterator	end	= m_vecTaskRoot.end();

	for( ; itr != end; ++itr ) {
		(*itr).task->UpdateChild( NULL );
	}

	return ret;
}



//===========================================================================
/*!	@brief		削除
	@param		taskId	削除するタスク
	@return		----
*/
//===========================================================================
void TaskManager::Remove( s32 taskId )
{
	std::vector<TaskData>::iterator	itr	= m_vecTaskRoot.begin();

	for( ; itr != m_vecTaskRoot.end(); ) {
		if( (*itr).id == taskId ) {
			(*itr).task->DisconnectAllChild();
			SafeDelete( (*itr).task );
			itr = m_vecTaskRoot.erase( itr );
		}
		else {
			++itr;
		}
	}

}



//===========================================================================
/*!	@brief		削除
	@param		task	削除するタスクへのポインタ
	@return		----
*/
//===========================================================================
void TaskManager::Remove( Task* task )
{
	std::vector<TaskData>::iterator	itr	= m_vecTaskRoot.begin();

	for( ; itr != m_vecTaskRoot.end(); ) {
		if( (*itr).task == task ) {
			task->DisconnectAllChild();
			SafeDelete( (*itr).task );
			itr = m_vecTaskRoot.erase( itr );
		}
		else {
			++itr;
		}
	}

}




//===========================================================================
/*!	@brief		削除
	@param		----
	@return		----
*/
//===========================================================================
void TaskManager::Clear( void )
{
	std::vector<TaskData>::iterator	itr	= m_vecTaskRoot.begin();
	std::vector<TaskData>::iterator	end	= m_vecTaskRoot.end();

	for( ; itr != end; ++itr ) {
		(*itr).task->DisconnectAllChild();
		SafeDelete( (*itr).task );
	}
	m_vecTaskRoot.clear();

}



//===========================================================================
/*!	@brief		イテレーター取得
	@param		task	タスク
	@return		失敗	m_vecTaskRoot.end()
*/
//===========================================================================
std::vector<TaskManager::TaskData>::iterator TaskManager::_GetTaskIterator( Task* task )
{
	std::vector<TaskData>::iterator	itr	= m_vecTaskRoot.begin();
	std::vector<TaskData>::iterator	end	= m_vecTaskRoot.end();

	for( ; itr != end; ++itr ) {
		if( (*itr).task == task ) {
			return itr;
		}
	}

	return m_vecTaskRoot.end();
}


//===========================================================================
/*!	@brief		イテレーター取得
	@param		id		タスクID
	@return		失敗	m_vecTaskRoot.end()
*/
//===========================================================================
std::vector<TaskManager::TaskData>::iterator TaskManager::_GetTaskIterator( s32 id )
{
	std::vector<TaskData>::iterator	itr	= m_vecTaskRoot.begin();
	std::vector<TaskData>::iterator	end	= m_vecTaskRoot.end();

	for( ; itr != end; ++itr ) {
		if( (*itr).id == id ) {
			return itr;
		}
	}

	return m_vecTaskRoot.end();
}


#if 0
//===========================================================================
/*!	@brief	ソート
	@param		descending		true:降順	false:昇順
	@return	----
*/
//===========================================================================
bool TaskManager::SortByPriority( bool descending )
{
	std::vector<TaskData>::iterator	itr	= m_vecTaskRoot.begin();
	std::vector<TaskData>::iterator	end	= m_vecTaskRoot.end();

	for( ; itr != end; ++itr ) {
		(*itr).task->UpdateChild( NULL );
	}

	return ret;
}

#endif


}	// namespace system
}	// namespace nk