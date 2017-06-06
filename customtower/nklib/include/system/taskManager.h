//=============================================================================
/*!	@file	taskManager.h

	@brief	�^�X�N�Ǘ�

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
								�^�X�N�Ǘ�
*/
//=============================================================================
class TaskManager {
private:

	//----------------------�ÓI�����o-----------------------
	static const s32	DEFAULT_MAX_TASK	= 256;		//!< �^�X�N�ő�

	//-----------------------�^��`--------------------------
	struct TaskData {
		Task*		task;
		s32			id;
	};
	
public:
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	bool	Update( void );

	//===========================================================================
	/*!	@brief		���[�g�^�X�N��ǉ�
	*/
	//===========================================================================
	void	AddRoot( Task* root, s32 taskId = 0 );

	//===========================================================================
	/*!	@brief		���[�g�^�X�N���擾
	*/
	//===========================================================================
	Task*	GetRoot( s32 taskId = 0 );

	//===========================================================================
	/*!	@brief		�^�X�N���폜
		@note		�w��^�X�N�ȏ�ɂ���^�X�N�͊J������܂�
	*/
	//===========================================================================
	void	Remove( s32 taskId = 0 );
	void	Remove( Task* root );

	//===========================================================================
	/*!	@brief		�S�^�X�N���폜
		@note		�^�X�N�͊J������܂�
	*/
	//===========================================================================
	void	Clear( void );

	//===========================================================================
	/*!	@brief		���ёւ�
	*/
	//===========================================================================
	template<typename T1, typename T2>
	void	Swap( T1 task1, T2 task2 );

	//===========================================================================
	/*!	@brief		�\�[�g
		@param		descending		true:�~��	false:����
	*/
	//===========================================================================
	//void	SortByPriority( bool descending = true );
	
private:
	//===========================================================================
	/*!	@brief		�C�e���[�^�[�擾
	*/
	//===========================================================================
	std::vector<TaskData>::iterator	_GetTaskIterator( Task* task );
	std::vector<TaskData>::iterator	_GetTaskIterator( s32 id );
	
private:
	//----------------------�����o�ϐ�-----------------------
	std::vector<TaskData>			m_vecTaskRoot;
	
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			TaskManager();
	virtual~TaskManager();
};



//===========================================================================
/*!	@brief		���ёւ�
	@param		task1, task2	����ւ���^�X�N
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