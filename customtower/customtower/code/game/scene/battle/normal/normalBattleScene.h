//=============================================================================
/*!	@file	normalBattleScene.h

	@brief	�ʏ�o�g��

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __NORMALL_BATTLE_SCENE_H__
#define __NORMALL_BATTLE_SCENE_H__

#include "../battleScene.h"

#include "game/scene/sceneInterface.h"
#include "game/battle/generator.h"
#include "game/battle/battleInfo.h"
#include "game/battle/battleExecutor.h"

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
class NormalBattleScene : public BattleScene {
public:
	//-----------------------�^��`--------------------------

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

private:
	//-----------------------���\�b�h------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------�����o�ϐ�-----------------------
	battle::BattleExecutor*			m_battleExecutor;		//!< �ΐ폈��
	battle::StageGenerator			m_stageGenerator;		//!< �X�e�[�W�W�F�l���[�^�[
	battle::ForceGenerator			m_forceGenerator;		//!< �R�W�F�l���[�^�[
	battle::CharacterGenerator		m_characterGenerator;	//!< �L�����W�F�l���[�^�[
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			NormalBattleScene();
	virtual~NormalBattleScene();
};
	
}	// namespace game



#endif  // __NORMALL_BATTLE_SCENE_H__