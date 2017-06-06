//=============================================================================
/*!	@file	treeTask

	@brief	�c���[�^�X�N

	@author	ryunosuke ide
	@date	2013.03.17
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/system/treeTask.h"
#include "../../include/general.h"


//--------------------------------define��`--------------------------------
#define DISCONNECT(child)	{ SafeDelete(child);	}
//#define DISCONNECT(child)	{ child	= NULL;	}


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
	@param	----
*/
//===========================================================================
TreeTask::TreeTask()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
TreeTask::~TreeTask()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void TreeTask::_Init()
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void TreeTask::_Term()
{
	DisconnectAllChild();
	
}



//===========================================================================
/*!	@brief		�X�V
	@param		parentParam		���[�U�[�p�����[�^�[
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
/*!	@brief		�q����ǉ�
	@param		task	�q��
	@return		----
*/
//===========================================================================
void TreeTask::ConnectChild( Task* task )
{
	
	m_childList.push_back( task );
	
}

//===========================================================================
/*!	@brief		�q����؂藣��
	@param		task	�q��
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
/*!	@brief		�q����؂藣��
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



