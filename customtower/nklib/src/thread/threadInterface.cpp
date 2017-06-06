//=============================================================================
/*!	@file	threadInterface.h

	@brief	�X���b�h�N���X

	@author	ryunosuke ide
	@date	2013.03.06
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/thread/threadInterface.h"
#include "../../include/utility/utility.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {


}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {

// �X���b�h�R�[���o�b�N
u32 Thread::_ThreadCallback( void* param )
{
	nk::Thread*	thread	= reinterpret_cast<nk::Thread*>(param);
	thread->ThreadCallback();
	//thread->ThreadFunc();

	return 0;
}

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
Thread::Thread()
{
	_Init();
}



//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Thread::~Thread()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Thread::_Init()
{
	m_status	= STATUS_NOT_INITIALIZED;
	m_created	= false;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Thread::_Term()
{
	if( m_created ) {
// 		Pause();
		Cancel();
		Join();
	}
}

//===========================================================================
/*!	@brief	�X���b�h�R�[���o�b�N
	@param	----
*/
//===========================================================================
void Thread::ThreadCallback( void )
{

	this->ThreadFunc();
	m_status	= STATUS_EXIT;
	m_created	= false;

	printf("Thread::ThreadCallback end\n");
}

//===========================================================================
/*!	@brief	�Z�b�g�A�b�v
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Setup( u32 priority, u32 stackSize, const char* name )
{
	if( m_created == false ) {
		m_handle	= nk::CreateThread( _ThreadCallback, this, priority, stackSize, name );
		m_created	= true;
		m_status	= Thread::STATUS_NOT_INITIALIZED;
	}

}

//===========================================================================
/*!	@brief	�J�n
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Start( void )
{
	bool	startableStatus	= (GetStatus() == Thread::STATUS_NOT_INITIALIZED) || (GetStatus() == Thread::STATUS_PAUSE);
	if( m_created && startableStatus ) {
		const u32	tempStatus	= m_status;
		m_status	= STATUS_RUN;
		
		if( tempStatus == STATUS_PAUSE ) {
			ResumeThread( m_handle );
		}
		else {
			StartThread( m_handle );
		}
	}
	
	
}



//===========================================================================
/*!	@brief	��~
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Pause( void )
{
	if( m_created && (m_status == Thread::STATUS_RUN) ) {
		m_status	= STATUS_PAUSE;
		SuspendThread( m_handle );
	}
}



//===========================================================================
/*!	@brief	�I��
	@param	----
	@return	----
*/
//===========================================================================
void Thread::Cancel( void )
{
	if( m_created && (m_status == Thread::STATUS_RUN) ) {
		m_status	= STATUS_CANCEL;
		//DestroyThread( m_handle );
	}
	//m_created	= false;
	
}



//===========================================================================
/*!	@brief	�X�e�[�^�X�̎擾
	@param	----
	@return	�X�e�[�^�X
*/
//===========================================================================
u32 Thread::GetStatus( void ) const
{

	return m_status;
}

//===========================================================================
/*!	@brief	���s���Ȃ�true��Ԃ�
	@param	----
*/
//===========================================================================
bool Thread::Running( void ) const
{

	return (GetStatus() == STATUS_RUN);
}


//===========================================================================
/*!	@brief		�ҋ@
	@param		----
	@return		----
*/
//===========================================================================
void Thread::Join( void )
{
	JoinThread( m_handle );
}


//===========================================================================
/*!	@brief		�L�����Z���Ȃ�true��Ԃ�
	@param		----
	@return		----
*/
//===========================================================================
bool Thread::IsCancel( void ) const
{
	
	return m_status == STATUS_CANCEL;
}
	
}	// namespace nk