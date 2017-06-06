//=============================================================================
/*!	@file	force.h

	@brief	�R

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __FORCE_H__
#define __FORCE_H__

#include <queue>
#include "../battleObject.h"
#include "game/battle/character/characterGenerator.h"
#include "game/battle/character/characterManager.h"
#include "game/battle/character/characterEmitter.h"
#include "game/battle/earth/earthObjectManager.h"
#include "opponentForce.h"

namespace game {

namespace battle {


//=============================================================================
/*!
								�R
*/
//=============================================================================
class Force {
public:
	//-----------------------�^��`--------------------------

	//! ���̓R�}���h
	enum OPERATE_COMMAND {
		OPERATE_COMMAND_NONE,
	};
	
	//! ������
	struct OperateInfo {
		u64					frame;		//!< ���̓t���[��
		OPERATE_COMMAND		command;	//!< ���̓R�}���h

		//! �R���X�g���N�^
		OperateInfo( void ) {
			this->frame		= 0;
			this->command	= OPERATE_COMMAND_NONE;
		}
	};
	typedef std::queue<OperateInfo>	QueueOperateInfo;		//!< ���̓R�}���h
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	virtual void	Initialize( BattleExecutor* battle );

	//===========================================================================
	/*!	@brief		�I��
	*/
	//===========================================================================
	virtual void	Terminate( void );

	//===========================================================================
	/*!	@brief		����`�F�b�N
	*/
	//===========================================================================
	virtual void	UpdatePhase_Operate( const OpponentForce& opponent ) {}

	//===========================================================================
	/*!	@brief		�ړ��t�F�C�Y
	*/
	//===========================================================================
	virtual void	UpdatePhase_Move( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		�ړ���ʒu�C���t�F�C�Y
	*/
	//===========================================================================
	virtual void	UpdatePhase_MoveFix( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		�U���t�F�C�Y
	*/
	//===========================================================================
	virtual void	UpdatePhase_Attack( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		�q�b�g��t�F�C�Y
	*/
	//===========================================================================
	virtual void	UpdatePhase_AfterHit( const OpponentForce& opponent );

	//===========================================================================
	/*!	@brief		�t���[���J�n
	*/
	//===========================================================================
	virtual void	UpdatePhase_FrameInitialize( void );
	
	//===========================================================================
	/*!	@brief		�t���[���I��
	*/
	//===========================================================================
	virtual void	UpdatePhase_FrameTerminate( void );

	//===========================================================================
	/*!	@brief		���̓R�}���h�ǉ�
	*/
	//===========================================================================
	void					PushOperateInfo( const OperateInfo& info );

	//===========================================================================
	/*!	@brief		���̓R�}���h�擾
	*/
	//===========================================================================
	void					PopOperateInfo( void );
	const OperateInfo&		GetNowFrameOperateInfo( void ) const;

	
protected:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

protected:
	//----------------------�����o�ϐ�-----------------------
	const BattleExecutor* 		m_battle;					//!< �o�g��

	EarthObjectManager			m_earthOvjectManager;		//!< �n����̃I�u�W�F�N�g�Ǘ�

	QueueOperateInfo			m_operateInfo;				//!< ���̓R�}���h
	OperateInfo					m_nowFrameOperateInfo;		//!< ���݃t���[�����͏��
	
	CharacterGenerator			m_characterGenerator;		//!< �L�����N�^�[�W�F�l���[�^�[
	CharacterManager			m_characterManager;			//!< �L�����N�^�[�Ǘ�
	CharacterEmitter			m_characterEmitter;			//!< �L�����N�^�[�G�~�b�^�[
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Force();
	virtual~Force();
};


}	// namespace battle

	
}	// namespace game







#endif  // __FORCE_H__