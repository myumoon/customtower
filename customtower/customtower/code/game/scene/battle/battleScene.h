//=============================================================================
/*!	@file	battleScene.h

	@brief	�o�g���V�[�����

	@author	ryunosuke ide
	@date	2013.06.24
*/
//=============================================================================

#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "game/scene/sceneInterface.h"
#include "game/battle/generator.h"
#include "game/battle/battleInfo.h"
#include "game/battle/battleExecutor.h"
#include "game/battle/battleEventSender.h"
#include "game/battle/battleExecutorSetupThread.h"

// �W�F�l���[�^�[
#include "game/battle/stage/stageGenerator.h"
#include "game/battle/force/forceGenerator.h"
#include "game/battle/character/characterGenerator.h"



namespace game {

//=============================================================================
/*!
								�ʏ�o�g��
*/
//=============================================================================
class BattleScene : public SceneInterface {
public:
	//-----------------------�^��`--------------------------
//	typedef std::vector<battle::Generator*>		VecGenerator;	//!< �W�F�l���[�^�[

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	virtual void	InitializeScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		�I��
	*/
	//===========================================================================
	virtual void	TerminateScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	virtual void	RenderLocal( void );

protected:
	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual s32		ExecuteLocal( s32 parentMessage );

	//===========================================================================
	/*!	@brief		�W�F�l���[�^�[�o�^
	*/
	//===========================================================================
//	void			RegisterGenerator( battle::Generator* generator );

	//===========================================================================
	/*!	@brief		�W�F�l���[�[�Z�b�g�A�b�v
	*/
	//===========================================================================
	void			SetupGenerator( const battle::BattleInfo& info );

	//===========================================================================
	/*!	@brief		�W�F�l���[�^�[�Ő��������C���X�^���X���폜
	*/
	//===========================================================================
	void			CallGeneratorDelete( void );
	
protected:
	//-----------------------���\�b�h------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------�����o�ϐ�-----------------------
	battle::BattleExecutorSetupThread*	m_battleExecutorSetupThread;	//!< �ΐ�Z�b�g�A�b�v�X���b�h
	battle::BattleExecutor*				m_battleExecutor;				//!< �ΐ폈��
	battle::StageGenerator				m_stageGenerator;				//!< �X�e�[�W�W�F�l���[�^�[
	battle::ForceGenerator				m_forceGenerator;				//!< �R�W�F�l���[�^�[
	battle::BattleEventSender			m_battleEventSender;			//!< �o�g���C�x���g���M��
	nk::graphics::Layout				m_layout;						//!< ���C�A�E�g
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			BattleScene();
	virtual~BattleScene();
};


	
}	// namespace game





#endif  // __BATTLE_SCENE_H__

