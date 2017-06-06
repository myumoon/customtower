//=============================================================================
/*!	@file	battleExecutorSetupThread.h

	@brief	�o�g���Z�b�g�A�b�v�X���b�h

	@author	ryunosuke ide
	@date	2013.06.26
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "battleExecutorSetupThread.h"

#include "battleExecutor.h"
#include "battleEventSender.h"
#include "stage/stageGenerator.h"
#include "force/forceGenerator.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace game {

namespace battle {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
BattleExecutorSetupThread::BattleExecutorSetupThread()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
BattleExecutorSetupThread::~BattleExecutorSetupThread()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutorSetupThread::_Init( void )
{
	m_battleExecutor	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutorSetupThread::_Term( void )
{

}


//===========================================================================
/*!	@brief		�Z�b�g�A�b�v
	@param		battle				�o�g��
    @param		stageGenerator		�X�e�[�W����
	@param		forceGenerator		�R����
	@param		eventSender			�C�x���g�ʒm
	@return		----
*/
//===========================================================================
void BattleExecutorSetupThread::Setup(
	BattleExecutor*		battleExecutor,
	const BattleInfo&	battleInfo,
	StageGenerator*		stageGenerator,
	ForceGenerator*		forceGenerator,
	BattleEventSender*	eventSender
)
{
	m_battleExecutor	= battleExecutor;
	m_battleInfo		= battleInfo;
    m_stageGenerator	= stageGenerator;
    m_forceGenerator	= forceGenerator;
	m_eventSender		= eventSender;

	Thread::Setup( THREAD_PRIORITY_NORMAL, 0, "BattleExecutorSetupThread" );
}

//===========================================================================
/*!	@brief		�X���b�h����
	@param		----
	@return		----
*/
//===========================================================================
void BattleExecutorSetupThread::ThreadFunc( void )
{
	if( m_battleExecutor ) {
		m_battleExecutor->Initialize( m_battleInfo, m_forceGenerator, m_stageGenerator );
	}
}

//===========================================================================
/*!	@brief		�Z�b�g�A�b�v�I���Ȃ�true��Ԃ�
	@param		----
	@return		true.�Z�b�g�A�b�v����	false.�������Ă��Ȃ�
*/
//===========================================================================
bool BattleExecutorSetupThread::IsSetupEnd( void ) const
{
	
	return GetStatus() == Thread::STATUS_EXIT;
}

	
}	// namespace battle
	
}	// namespace game