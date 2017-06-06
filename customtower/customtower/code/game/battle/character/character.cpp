//=============================================================================
/*!	@file	キャラクター

	@brief	キャラクター

	@author	ryunosuke ide
	@date	2013.05.27
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <math.h>

#include "math/math.h"

#include "character.h"

#include "game/gameMain.h"
#include "game/battle/collision/collisionObjectManager.h"
#include "game/battle/battleExecutor.h"

#include "game/battle/stage/stage.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace game {
namespace battle {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Character::Character()
{
	_Init();
}



//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Character::Character( const CharacterManager* mng )
{
	_Init();
	SetCharacterManager( mng );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Character::~Character()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Character::_Init( void )
{
	m_moveSpeed	= 0.0f;	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Character::_Term( void )
{

}

//===========================================================================
/*!	@brief		バトル生成時初期化
	@param		battle	バトル
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
/*!	@brief		バトル終了時
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
/*!	@brief		移動
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
/*!	@brief		キャラクターマネージャーセット
	@param		mng		キャラクターマネージャー
	@return		----
*/
//===========================================================================
void Character::SetCharacterManager( const CharacterManager* mng )
{
	m_characterManager	= mng;
}

//===========================================================================
/*!	@brief		移動速度設定
	@param		speed	速度
	@return		----
*/
//===========================================================================
void Character::SetMoveSpeed( f32 speed )
{
	m_moveSpeed	= speed;
	
}


//===========================================================================
/*!	@brief		右移動
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
	
	// (移動距離(speed) / 円周) * 360(2*pi) が移動角度
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
/*!	@brief		左移動
	@param		----
	@return		----
*/
//===========================================================================
void Character::MoveLeft( void )
{
	
}


//===========================================================================
/*!	@brief		キャラクターマネージャー取得
	@param		----
	@return		----
*/
//===========================================================================
const CharacterManager* Character::GetCharacterManager( void ) const
{
	return m_characterManager;
}

//===========================================================================
/*!	@brief		ヒット反応
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
/*!	@brief		ヒット反応
	@return		----
*/
//===========================================================================
void Character::Hit( const Character* target )
{
}

}	// namespace battle

}	// namespace game
