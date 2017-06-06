//=============================================================================
/*!	@file	battleExecutor.h

	@brief	�ΐ폈�����s
			�ΐ�I�u�W�F�N�g�̓��암����S��
			���j���[���͂������������������

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

#ifndef __BATTLE_EXECUTOR_H__
#define __BATTLE_EXECUTOR_H__

#include "graphics/layout.h"


//#include "game/battle/character/character.h"
//#include "game/battle/stage/stage.h"
#include "game/battle/stage/stageGenerator.h"
//#include "game/battle/force/force.h"
#include "game/battle/force/forceGenerator.h"
#include "game/battle/force/opponentForce.h"


namespace game {
namespace battle {


class Force;
class Stage;
class CollisionObjectManager;
	
//=============================================================================
/*!
								�ΐ���s��
*/
//=============================================================================
class BattleExecutor {
public:
	//-----------------------�^��`--------------------------
	typedef std::vector<Force*>			VecForce;				//!< �R���X�g
	typedef std::vector<OpponentForce>	VecOpponentForce;		//!< �G�R���X�g
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	void	Initialize(
		const BattleInfo&		battleInfo,
		ForceGenerator*			forceGenerator,
		StageGenerator*			stageGenerator
	);

	//===========================================================================
	/*!	@brief		�I��
	*/
	//===========================================================================
	void	Terminate( void );


	//===========================================================================
	/*!	@brief		���s
	*/
	//===========================================================================
	void	Update( void );

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
  	void	Render( void );

	//===========================================================================
	/*!	@brief		���݃t���[���擾
	*/
	//===========================================================================
	u64		GetFrame( void ) const;

	//===========================================================================
	/*!	@brief		�ΐ���擾
	*/
	//===========================================================================
	const BattleInfo*	GetBattleInfo( void ) const;

	//===========================================================================
	/*!	@brief		�q�b�g�Ǘ��擾
	*/
	//===========================================================================
	CollisionObjectManager*	GetCollisionObjectManager( void );

	//===========================================================================
	/*!	@brief		�X�e�[�W�擾
	*/
	//===========================================================================
	const Stage*			GetStage( void ) const;

protected:
	//===========================================================================
	/*!	@brief		�R����
	*/
	//===========================================================================
	void	GenerateForce( ForceGenerator* forceGenerator );

	//===========================================================================
	/*!	@brief		�X�e�[�W����
	*/
	//===========================================================================
	void	GenerateStage( StageGenerator* stageGenerator );

	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
 	BattleInfo				m_battleInfo;				//!< �ΐ���
	u64						m_battleFrame;				//!< �ΐ�t���[��
	ForceList*				m_forceList;				//!< �R���X�g
	Stage*					m_stage;					//!< �X�e�[�W
	CollisionObjectManager*	m_collisionObjectManager;	//!< �q�b�g�Ǘ�
	
	nk::graphics::Layout	m_layout;			//!< ���C�A�E�g
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			BattleExecutor();
	virtual~BattleExecutor();
};
	

}	// namespace battle

}	// namespace game




#endif  // __BATTLE_EXECUTOR_H__