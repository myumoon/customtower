//=============================================================================
/*!	@file	taskManager.h

	@brief	タスク管理

	@author	ryunosuke ide
	@date	2012.06.07
*/
//=============================================================================

#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include <vector>
#include <typeinfo>
#include "../typedef.h"

namespace nk {

namespace system {

class Task;

//=============================================================================
/*!
								タスク管理
*/
//=============================================================================
class TaskManager {
private:

	//----------------------静的メンバ-----------------------
	static const s32	DEFAULT_MAX_TASK	= 256;		//!< タスク最大

	//-----------------------型定義--------------------------
	struct TaskData {
		Task*		task;
		s32			id;
	};
	
public:
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	bool	Update( void );

	//===========================================================================
	/*!	@brief		ルートタスクを追加
	*/
	//===========================================================================
	void	AddRoot( Task* root, s32 taskId = 0 );

	//===========================================================================
	/*!	@brief		ルートタスクを取得
	*/
	//===========================================================================
	Task*	GetRoot( s32 taskId = 0 );

	//===========================================================================
	/*!	@brief		タスクを削除
		@note		指定タスク以上にあるタスクは開放されます
	*/
	//===========================================================================
	void	Remove( s32 taskId = 0 );
	void	Remove( Task* root );

	//===========================================================================
	/*!	@brief		全タスクを削除
		@note		タスクは開放されます
	*/
	//===========================================================================
	void	Clear( void );

	//===========================================================================
	/*!	@brief		並び替え
	*/
	//===========================================================================
	template<typename T1, typename T2>
	void	Swap( T1 task1, T2 task2 );

	//===========================================================================
	/*!	@brief		ソート
		@param		descending		true:降順	false:昇順
	*/
	//===========================================================================
	//void	SortByPriority( bool descending = true );
	
private:
	//===========================================================================
	/*!	@brief		イテレーター取得
	*/
	//===========================================================================
	std::vector<TaskData>::iterator	_GetTaskIterator( Task* task );
	std::vector<TaskData>::iterator	_GetTaskIterator( s32 id );
	
private:
	//----------------------メンバ変数-----------------------
	std::vector<TaskData>			m_vecTaskRoot;
	
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			TaskManager();
	virtual~TaskManager();
};



//===========================================================================
/*!	@brief		並び替え
	@param		task1, task2	入れ替えるタスク
	@return		----
*/
//===========================================================================
template<typename T1, typename T2>
void TaskManager::Swap( T1 task1, T2 task2 )
{
	bool	result	= true;
	result	&= (typeid(task1) == typeid(s32)) || (typeid(task1) == typeid(u32)) || (typeid(task1) == typeid(Task*));
	result	&= (typeid(task2) == typeid(s32)) || (typeid(task2) == typeid(u32)) || (typeid(task2) == typeid(Task*));

	if( result ) {
		std::vector<TaskData>::iterator	itr1	= _GetTaskIterator( task1 );
		std::vector<TaskData>::iterator	itr2	= _GetTaskIterator( task2 );
		TaskData	temp	= *itr1;
		*itr1	= *itr2;
		*itr2	= temp;
	}
	
}

}	// namespace system

}	// namespace nk





#endif  // __TASKMANAGER_H__