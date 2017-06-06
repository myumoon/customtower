//=============================================================================
/*!	@file	battleExecutorSetupThread.h

	@brief	�o�g���Z�b�g�A�b�v�X���b�h

	@author	ryunosuke ide
	@date	2013.06.26
*/
//=============================================================================


#ifndef __BATTLE_EXECUTOR_SETUP_THREAD_H__
#define __BATTLE_EXECUTOR_SETUP_THREAD_H__


#include "thread/thread.h"
#include "battleInfo.h"


namespace game {
	
namespace battle {

	
class BattleExecutor;
class StageGenerator;
class ForceGenerator;
class BattleEventSender;

	
//=============================================================================
/*!
						�o�g���Z�b�g�A�b�v�X���b�h
*/
//=============================================================================
class BattleExecutorSetupThread : public nk::Thread {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�o�g���ݒ�
	*/
	//===========================================================================
	void			Setup(
		BattleExecutor*		battleExecutor,
		const BattleInfo&	battleInfo,
		StageGenerator*		stageGenerator,
		ForceGenerator*		forceGenerator,
		BattleEventSender*	eventSender
	);

	//===========================================================================
	/*!	@brief		�Z�b�g�A�b�v�I��������true��Ԃ�
	*/
	//===========================================================================
	bool			IsSetupEnd( void ) const;
	
protected:
	
	//===========================================================================
	/*!	@brief		�X���b�h����
	*/
	//===========================================================================
	virtual void	ThreadFunc( void );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	BattleExecutor*		m_battleExecutor;		//!< �o�g��
	BattleInfo			m_battleInfo;			//!< �ΐ���
	StageGenerator*		m_stageGenerator;		//!< �X�e�[�W����
	ForceGenerator*		m_forceGenerator;		//!< �R����
	BattleEventSender*	m_eventSender;			//!< �C�x���g����

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			BattleExecutorSetupThread();
	virtual~BattleExecutorSetupThread();
};
	
}	// namespace battle
	
}	// namespace game


#endif  // __BATTLE_EXECUTOR_SETUP_THREAD_H__