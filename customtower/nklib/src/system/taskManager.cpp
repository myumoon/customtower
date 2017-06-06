//=============================================================================
/*!	@file	taskManager.cpp

	@brief	�^�X�N�Ǘ�

	@author	ryunosuke ide
	@date	2012.06.07
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/system/taskManager.h"

#include "../../include/general.h"
#include "../../include/system/task.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace nk {

namespace system {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	
*/
//===========================================================================
TaskManager::TaskManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
TaskManager::~TaskManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void TaskManager::_Init()
{
	m_vecTaskRoot.reserve( DEFAULT_MAX_TASK );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void TaskManager::_Term()
{
	Clear();
}


//===========================================================================
/*!	@brief	���[�g�^�X�N��ǉ�
	@param	root	: ���[�g�^�X�N
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
/*!	@brief	���[�g�^�X�N���K��
	@param	�^�X�NID(�f�t�H���g��0)
	@return	���[�g�^�X�N
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
/*!	@brief	�X�V
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
/*!	@brief		�폜
	@param		taskId	�폜����^�X�N
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
/*!	@brief		�폜
	@param		task	�폜����^�X�N�ւ̃|�C���^
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
/*!	@brief		�폜
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
/*!	@brief		�C�e���[�^�[�擾
	@param		task	�^�X�N
	@return		���s	m_vecTaskRoot.end()
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
/*!	@brief		�C�e���[�^�[�擾
	@param		id		�^�X�NID
	@return		���s	m_vecTaskRoot.end()
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
/*!	@brief	�\�[�g
	@param		descending		true:�~��	false:����
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