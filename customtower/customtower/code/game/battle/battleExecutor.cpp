//=============================================================================
/*!	@file	battleExecutor.h

	@brief	�ΐ폈�����s
			�ΐ�I�u�W�F�N�g�̓��암����S��
			���j���[���͂������������������

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "battleExecutor.h"
#include "game/battle/force/force.h"
#include "game/battle/force/opponentForce.h"
#include "game/battle/stage/stage.h"
#include "game/battle/stage/stage01/stage01.h"
#include "game/battle/collision/collisionObjectManager.h"


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
BattleExecutor::BattleExecutor()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
BattleExecutor::~BattleExecutor()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutor::_Init( void )
{
	m_forceList	= NULL;
// 	m_forceList.reserve( 16 );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void BattleExecutor::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		forceGenerator		�R
	@param		stageGenerator		�X�e�[�W
	@return		----
*/
//===========================================================================
void BattleExecutor::Initialize(
	const BattleInfo&		battleInfo,
	ForceGenerator*			forceGenerator,
	StageGenerator*			stageGenerator
)
{
	m_battleInfo				= battleInfo;
	m_battleFrame				= 0;
	
	m_collisionObjectManager	= new CollisionObjectManager();
	
	// �o�g���I�u�W�F�N�g�𐶐�
	{
		GenerateStage( stageGenerator );		
		GenerateForce( forceGenerator );
	}


	// �o�g���I�u�G�W�F�N�g��������
	{
		for( u32 i = 0; i < m_forceList->forces.size(); ++i ) {
			m_forceList->forces[i]->Initialize( this );
		}
		
		if( m_stage ) {
			m_stage->InitializeForBattle( this );
		}
	}
}


//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		----
*/
//===========================================================================
void BattleExecutor::Terminate( void )
{
	m_collisionObjectManager->RemoveCollisionObjects();

	for( u32 i = 0; i < m_forceList->forces.size(); ++i ) {
		m_forceList->forces[i]->Terminate();
	}
	if( m_stage ) {
		m_stage->TerminateForBattle();
	}

	nk::SafeDelete( m_collisionObjectManager );
}

//===========================================================================
/*!	@brief		�Q����
	@param		forceGenerator	�W�F�l���[�^�[
	@return		----
*/
//===========================================================================
void BattleExecutor::GenerateForce( ForceGenerator* forceGenerator )
{
// 	forceGenerator.Setup( m_battleInfo );
	m_forceList	= forceGenerator->Generate();

}

//===========================================================================
/*!	@brief		�X�e�[�W����
	@param		stageGenerator	�W�F�l���[�^�[
	@return		----
*/
//===========================================================================
void BattleExecutor::GenerateStage( StageGenerator* stageGenerator )
{
// 	stageGenerator.Setup( m_battleInfo );
	m_stage	= stageGenerator->Generate();
	
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void BattleExecutor::Update( void )
{
	// �G�R���X�g����
	VecOpponentForce	opponents;
	opponents.resize( m_forceList->forces.size() );
	for( u32 insertForce = 0; insertForce < m_forceList->forces.size(); ++insertForce ) {
		for( u32 opponentForce = 0; opponentForce < m_forceList->forces.size(); ++opponentForce ) {
			if( insertForce != opponentForce ) {
				opponents[insertForce].AppendForce( m_forceList->forces[opponentForce] );
			}
		}
	}

	// �I������
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_FrameInitialize();
	}

	// ���̓R�}���h
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_Operate( opponents[updateForce] );
		m_forceList->forces[updateForce]->PopOperateInfo();
	}

	// ���ۂ̈ړ�
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_Move( opponents[updateForce] );
	}

	// �ړ���ʒu�C��
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_MoveFix( opponents[updateForce] );
	}

	// �U��
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_Attack( opponents[updateForce] );
	}

	// �q�b�g����
	{
		m_collisionObjectManager->SortByPriority();
		m_collisionObjectManager->CheckHit();
	}


	// �q�b�g��
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_AfterHit( opponents[updateForce] );
	}

	// �I������
	for( u32 updateForce = 0; updateForce < m_forceList->forces.size(); ++updateForce ) {
		m_forceList->forces[updateForce]->UpdatePhase_FrameTerminate();
	}

	++m_battleFrame;
}


//===========================================================================
/*!	@brief		���݃t���[���擾
	@param		----
	@return		----
*/
//===========================================================================
u64 BattleExecutor::GetFrame( void ) const
{
	
	return m_battleFrame;
}


//===========================================================================
/*!	@brief		�ΐ���擾
	@param		----
	@return		----
*/
//===========================================================================
const BattleInfo* BattleExecutor::GetBattleInfo( void ) const
{

	return &m_battleInfo;
}



//===========================================================================
/*!	@brief		�q�b�g�Ǘ��擾
	@param		----
	@return		----
*/
//===========================================================================
CollisionObjectManager*	BattleExecutor::GetCollisionObjectManager( void )
{

	return m_collisionObjectManager;
}


//===========================================================================
/*!	@brief		�X�e�[�W�擾
	@param		----
	@return		----
*/
//===========================================================================
const Stage* BattleExecutor::GetStage( void ) const
{

	return m_stage;
}

//===========================================================================
/*!	@brief		�`��v�b�V���o�b�N
	@param		offset	�`��ʒu�I�t�Z�b�g
	@return		----
*/
//===========================================================================
// void BattleExecutor::RenderPushBack( const nk::math::Vector& offset )
// {
// 	if( m_stage ) {
// 		m_stage->RenderPushBack( offset );
// 	}
// 	
// 	for( u32 i = 0; i < m_forceList.size(); ++i ) {
// 		m_forceList[i]->RenderPushBack( offset );
// 	}
// 	
// }


}	// namespace battle

	
}	// namespace game