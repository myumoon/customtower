//=============================================================================
/*!	@file	force.h

	@brief	�R

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "force.h"
#include "gameDef.h"
#include "../battleExecutor.h"

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
Force::Force()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Force::~Force()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Force::_Init( void )
{
	m_battle	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Force::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		battle		�o�g���Ǘ�
	@return		----
*/
//===========================================================================
void Force::Initialize( BattleExecutor* battle )
{
	m_battle	= battle;

	m_characterEmitter.Setup( battle, &m_characterGenerator, &m_characterManager );
	m_characterManager.Initialize();
	m_characterGenerator.Setup( *battle->GetBattleInfo() );

	// �d�͏����o�^
	m_earthOvjectManager.RegisterEarthObject( &m_characterManager );
}


//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		----
*/
//===========================================================================
void Force::Terminate( void )
{
	m_characterManager.Terminate();

	m_earthOvjectManager.Clear();

}


//===========================================================================
/*!	@brief		�ړ��t�F�C�Y
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_Move( const OpponentForce& opponent )
{
	const OperateInfo&	nowFrameInfo	= GetNowFrameOperateInfo();

	// �O��ʒu�L��
	m_characterManager.PushPrevPos();

	// �d�͏���
	m_earthOvjectManager.AcceptProjection();
	
	// �L�����N�^�[�ړ�
	m_characterManager.UpdateMove();
}


//===========================================================================
/*!	@brief		�ړ���ʒu�C���t�F�C�Y
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_MoveFix( const OpponentForce& opponent )
{

}


//===========================================================================
/*!	@brief		�U���t�F�C�Y
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_Attack( const OpponentForce& opponent )
{

}


//===========================================================================
/*!	@brief		�q�b�g��t�F�C�Y
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_AfterHit( const OpponentForce& opponent )
{
	//m_characterManager.Remove( &m_characterGenerator );
}


//===========================================================================
/*!	@brief		���͏��push
	@param		info	���͏��
	@return		----
*/
//===========================================================================
void Force::PushOperateInfo( const OperateInfo& info )
{
	m_operateInfo.push( info );
	
}


//===========================================================================
/*!	@brief		�t���[���J�n����
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_FrameInitialize( void )
{
	
}
	
//===========================================================================
/*!	@brief		�t���[���I������
	@param		----
	@return		----
*/
//===========================================================================
void Force::UpdatePhase_FrameTerminate( void )
{
	m_characterManager.RemoveReservedCharacters();
	
}

//===========================================================================
/*!	@brief		���͏��擾
	@param		----
	@return		----
*/
//===========================================================================
void Force::PopOperateInfo( void )
{
	const u64	nowFrame	= m_battle->GetFrame();
	
	// �w��t���[���҂�����Ɏ擾�J�n
	if( BATTLE_INPUT_DELAY_FRAME <= nowFrame ) {

		// �󂾂������̏������Ă���
		if( m_operateInfo.empty() ) {
			m_nowFrameOperateInfo	= OperateInfo();
		}
		else {
			do {
				m_nowFrameOperateInfo	= m_operateInfo.front();
				m_operateInfo.pop();
			} while( m_nowFrameOperateInfo.frame < nowFrame - BATTLE_INPUT_DELAY_FRAME );
		}
	}

}

//===========================================================================
/*!	@brief		���̓R�}���h�擾
	@param		----
	@return		----
*/
//===========================================================================
const Force::OperateInfo& Force::GetNowFrameOperateInfo( void ) const
{
	
	return m_nowFrameOperateInfo;
}


}	// namespace battle
	
}	// namespace game