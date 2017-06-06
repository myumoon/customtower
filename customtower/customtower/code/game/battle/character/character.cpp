//=============================================================================
/*!	@file	�L�����N�^�[

	@brief	�L�����N�^�[

	@author	ryunosuke ide
	@date	2013.05.27
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <math.h>

#include "math/math.h"

#include "character.h"

#include "game/gameMain.h"
#include "game/battle/collision/collisionObjectManager.h"
#include "game/battle/battleExecutor.h"

#include "game/battle/stage/stage.h"

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
Character::Character()
{
	_Init();
}



//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
Character::Character( const CharacterManager* mng )
{
	_Init();
	SetCharacterManager( mng );
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Character::~Character()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Character::_Init( void )
{
	m_moveSpeed	= 0.0f;	
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Character::_Term( void )
{

}

//===========================================================================
/*!	@brief		�o�g��������������
	@param		battle	�o�g��
	@return		----
*/
//===========================================================================
void Character::InitializeForBattle( BattleExecutor* battleExec )
{
	BattleObject::InitializeForBattle( battleExec );

	RegisterToRenderManager();

	EarthObject::Setup( 2.5f, battleExec->GetStage()->GetPos() );

	m_bvSphere.Init();
	m_bvSphere.SetRadius( 10.0f );
	battleExec->GetCollisionObjectManager()->AddCollisionObject( &m_bvSphere, this );
	
}



//===========================================================================
/*!	@brief		�o�g���I����
	@param		----
	@return		----
*/
//===========================================================================
void Character::TerminateForBattle( void )
{
	RemoveFromRenderManager();

	m_battleExec->GetCollisionObjectManager()->RemoveCollisionObject( &m_bvSphere );

}


//===========================================================================
/*!	@brief		�ړ�
	@param		----
	@return		----
*/
//===========================================================================
void Character::Move( void )
{
	if( IsAutoUpdate() == false ) {
		MoveRight();
	}
}

//===========================================================================
/*!	@brief		�L�����N�^�[�}�l�[�W���[�Z�b�g
	@param		mng		�L�����N�^�[�}�l�[�W���[
	@return		----
*/
//===========================================================================
void Character::SetCharacterManager( const CharacterManager* mng )
{
	m_characterManager	= mng;
}

//===========================================================================
/*!	@brief		�ړ����x�ݒ�
	@param		speed	���x
	@return		----
*/
//===========================================================================
void Character::SetMoveSpeed( f32 speed )
{
	m_moveSpeed	= speed;
	
}


//===========================================================================
/*!	@brief		�E�ړ�
	@param		----
	@return		----
*/
//===========================================================================
void Character::MoveRight( void )
{
	const Stage::StageInfo&	stageInfo	= m_battleExec->GetStage()->GetInfo();
	const nk::math::Vector	centerToPos	= GetPos() - stageInfo.centerPos;
	const nk::math::Vector	top			= centerToPos.GetNormalizeVec();

	const f32				radius		= centerToPos.GetNorm();
	
	// (�ړ�����(speed) / �~��) * 360(2*pi) ���ړ��p�x
	// rotation = (m_speed / (radius * 2 * M_PI)) * 2 * M_PI
	const f32				rotation	= -m_moveSpeed / radius;
	
// 	AddGlobalRotation( rotation );


// 	nk::math::Quaternion	rotationQua;
// 	rotationQua.RotateZ( nk::math::Rad(GetGlobalRotation()) + rotation );
// 	nk::math::Vector		rotatePos	= nk::math::GetQuaternionToMatrix( rotationQua ) * centerToPos;
	const f32				globalRotation	= GetGlobalRotation();
	const f32				rotateValue	= globalRotation + rotation;
	nk::math::Matrix44		rotateMat	= nk::math::RotateZ( rotation );
	nk::math::Vector		rotatePos	= rotateMat * centerToPos;
	
	SetPos( stageInfo.centerPos + rotatePos );

	CalcGlobalRotation();
	
// 	if( m_globalRotation < 0.0f ) {
// 	}
	
// 	m_moveRotation.RotateZ( rotation );
// 	m_moveRotation.GetQuaternionToMatrix();
	
// 	nk::math::Vector		right		= nk::math::CalcCrossProduct( top, GAME_AXIS_Z );
// 	right.Normalize();
// 	right	*= m_moveSpeed;
	
}


//===========================================================================
/*!	@brief		���ړ�
	@param		----
	@return		----
*/
//===========================================================================
void Character::MoveLeft( void )
{
	
}


//===========================================================================
/*!	@brief		�L�����N�^�[�}�l�[�W���[�擾
	@param		----
	@return		----
*/
//===========================================================================
const CharacterManager* Character::GetCharacterManager( void ) const
{
	return m_characterManager;
}

//===========================================================================
/*!	@brief		�q�b�g����
	@return		----
*/
//===========================================================================
void Character::Hit( const Stage* target )
{
	nk::math::Vector		surfaceDirec	= GetPos();
	surfaceDirec.Normalize();
	
	const nk::math::Vector&	stagePos		= target->GetPos();
	const Stage::StageInfo&	stageInfo		= target->GetInfo();
	const f32				stageRadius		= stageInfo.radius;
	const nk::math::Vector	newPos			= stagePos + surfaceDirec * stageRadius;

	{
		nk::BVRay			ray;
		ray.Init( GetPrevPos(), GetPos() );

		nk::BVSphere		earth;
		earth.Init( target->GetPos(), stageRadius );

		nk::math::Vector	surfacePos;
		nk::CalcIntersectionPoint( &surfacePos, &earth, &ray );

		SetPos( surfacePos );
	}
	
 	SetPos( newPos );
	EarthObject::Stop();

	EarthObject::CalcGlobalRotation();
}

//===========================================================================
/*!	@brief		�q�b�g����
	@return		----
*/
//===========================================================================
void Character::Hit( const Character* target )
{
}

}	// namespace battle

}	// namespace game
