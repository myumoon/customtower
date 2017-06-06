//=============================================================================
/*!	@file	�X�e�[�W

	@brief	�X�e�[�W

	@author	ryunosuke ide
	@date	2013.05.27
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "stage.h"

#include "game/gameMain.h"
#include "game/battle/collision/collisionObjectManager.h"
#include "game/battle/character/character.h"
#include "game/battle/battleExecutor.h"

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
Stage::Stage()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Stage::~Stage()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Stage::_Init( void )
{
	m_stageModel	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Stage::_Term( void )
{

}


//===========================================================================
/*!	@brief		�o�g��������������
	@param		battle	�o�g��
	@return		----
*/
//===========================================================================
void Stage::InitializeForBattle( BattleExecutor* battleExec )
{
	BattleObject::InitializeForBattle( battleExec );
	
	RegisterToRenderManager();

	m_bvSphere.Init();
	m_bvSphere.SetRadius( GetInfo().radius );
	m_battleExec->GetCollisionObjectManager()->AddCollisionObject( &m_bvSphere, this );

}



//===========================================================================
/*!	@brief		�o�g���I����
	@param		----
	@return		----
*/
//===========================================================================
void Stage::TerminateForBattle( void )
{
	RemoveFromRenderManager();

	m_battleExec->GetCollisionObjectManager()->RemoveCollisionObject( &m_bvSphere );

}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
bool Stage::Execute( void )
{
	bool	result	= true;
	
	result	= ExecuteLocal();

	return result;
}


//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void Stage::Render( void )
{
}


//===========================================================================
/*!	@brief		�X�e�[�W��{���擾
	@param		----
	@return		----
*/
//===========================================================================
const Stage::StageInfo& Stage::GetInfo( void ) const
{
	
	return m_stageInfo;
}


}	// namespace battle

}	// namespace game
