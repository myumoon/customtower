//=============================================================================
/*!	@file	BattleScene.h

	@brief	�ʏ�o�g��

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "battleScene.h"
#include "game/battle/battleInfo.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace game {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
BattleScene::BattleScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
BattleScene::~BattleScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void BattleScene::_Init( void )
{
	m_battleExecutor				= NULL;
	m_battleExecutorSetupThread		= NULL;
	
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void BattleScene::_Term( void )
{
	nk::SafeDelete( m_battleExecutorSetupThread );
	nk::SafeDelete( m_battleExecutor );
}


//===========================================================================
/*!	@brief		������
	@param		parent	�e
	@return		----
*/
//===========================================================================
void BattleScene::InitializeScene( SceneInterface* parent )
{
	m_battleExecutorSetupThread		= new battle::BattleExecutorSetupThread();
	m_battleExecutor				= new battle::BattleExecutor();

	// @@@@@
	{
		battle::BattleInfo	_info;
		_info.SetStage( battle::BattleInfo::STAGE_TYPE_STAGE01 );
		_info.AddControler( battle::BattleInfo::CONTOROLLER_TYPE_USER );

		SetupGenerator( _info );
	}

	battle::BattleInfo	battleInfo;

	// �o�g��������
	m_battleExecutorSetupThread->Setup(
		m_battleExecutor,
		battleInfo,
		&m_stageGenerator,
		&m_forceGenerator,
		&m_battleEventSender
	);

	RegisterToRenderManager();

	m_battleExecutorSetupThread->Start();
}


//===========================================================================
/*!	@brief		�I��
	@param		parent	�e
	@return		----
*/
//===========================================================================
void BattleScene::TerminateScene( SceneInterface* parent )
{
	if( m_battleExecutor ) {
		m_battleExecutor->Terminate();
	}
	
	nk::SafeDelete( m_battleExecutor );
	CallGeneratorDelete();


	RemoveFromRenderManager();
}


//===========================================================================
/*!	@brief		�X�V
	@param		parentMessage	�e����̃��b�Z�[�W
	@return		�q�ɒʒm���郁�b�Z�[�W
*/
//===========================================================================
s32 BattleScene::ExecuteLocal( s32 parentMessage )
{
	if( m_battleExecutorSetupThread->IsSetupEnd() ) {
		m_battleExecutor->Update();
	}

	
	return MESSAGE_NONE;
}


//===========================================================================
/*!	@brief		�����_�����O
	@param		----
	@return		----
*/
//===========================================================================
void BattleScene::RenderLocal( void )
{
	nk::SystemPrint( 0, 0, "Normal Battle" );

	if( m_battleExecutorSetupThread->IsSetupEnd() ) {
		//m_battleExecutor->Render( message );
	}
	
}



//===========================================================================
/*!	@brief		�W�F�l���[�^�[�Z�b�g�A�b�v
	@param		info	�ΐ���
	@return		----
*/
//===========================================================================
void BattleScene::SetupGenerator( const battle::BattleInfo& info )
{
	m_stageGenerator.Setup( info );
	m_forceGenerator.Setup( info );
	
}


//===========================================================================
/*!	@brief		�W�F�l���[�^�[���̃C���X�^���X�폜
	@param		----
	@return		----
*/
//===========================================================================
void BattleScene::CallGeneratorDelete( void )
{
	m_stageGenerator.Delete();
	m_forceGenerator.Delete();
	
}
	
}	// namespace game