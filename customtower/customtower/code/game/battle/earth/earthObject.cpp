//=============================================================================
/*!	@file	earthObject.h

	@brief	位置計算

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#define _USE_MATH_DEFINES	// M_PI
#include <math.h>

#include "gameDef.h"

#include "earthObject.h"
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
EarthObject::EarthObject()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
EarthObject::~EarthObject()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void EarthObject::_Init( void )
{
	m_airResistance				= 0.0f;
	m_gravityAcceleration		= 0.0f;
	m_firstVirticalVelocity		= 0.0f;
	m_firstHorizonalVelocity	= 0.0f;
	m_virticalVelocity			= 0.0f;
	m_horizonalVelocity			= 0.0f;
	m_globalRotation			= 0.0f;
	m_autoUpdate				= false;
	
	m_calcFunc		= &EarthObject::_UpdateWait;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void EarthObject::_Term( void )
{

}


//===========================================================================
/*!	@brief		セットアップ
	@param		gravityAcc		重力加速度
	@param		centerPos		中心位置
	@return		----
*/
//===========================================================================
void EarthObject::Setup(
	f32 					gravityAcc,
	const nk::math::Vector& centerPos
)
{
	m_gravityAcceleration		= gravityAcc;
	m_centerPos					= centerPos;
	m_airResistance				= 0.0f;
	m_frameCount				= 0;

	m_firstVirticalVelocity		= 0.0f;
	m_firstHorizonalVelocity	= 0.0f;
	m_virticalVelocity			= 0.0f;
	m_horizonalVelocity			= 0.0f;

	m_calcFunc					= &EarthObject::_UpdateWait;
}


//===========================================================================
/*!	@brief		空気抵抗設定
	@param		airResistance	空気抵抗値
	@return		----
	@note		設定した値分だけ毎フレーム減速する
*/
//===========================================================================
void EarthObject::SetAirResistance( f32 airResistance )
{
	m_airResistance	= airResistance;
}

//===========================================================================
/*!	@brief		開始
	@param		firstVelocity			初速度
	@param		true.現在の速度に加算	false.新しく計算
	@return		----
*/
//===========================================================================
void EarthObject::Start( const nk::math::Vector& firstVelocity, bool add )
{
	m_frameCount		= 0;
	m_calcFunc			= &EarthObject::_UpdatePosition;
	m_autoUpdate		= true;

	const nk::math::Vector	axis_z( 0.0f, 0.0f, 1.0f );

	nk::math::Vector	newFirstVelocity	= firstVelocity;
	if( add ) {
		newFirstVelocity	+= GetProjectionVelocity();
	}

	// 水平方向初速度計算
	{
		nk::math::Vector	localFirstVelocity_y	= m_objectPos - m_centerPos;
		nk::math::Vector	localFirstVelocity_x	= nk::math::CalcCrossProduct( localFirstVelocity_y, axis_z );
		localFirstVelocity_x.Normalize();

		// 右が正 左が負
		m_firstHorizonalVelocity					= nk::math::CalcDotProduct( localFirstVelocity_x, newFirstVelocity );
		m_horizonalVelocity							= m_firstHorizonalVelocity;
	}

	// 垂直方向初速度計算
	{
		nk::math::Vector	localFirstVelocity_y	= m_objectPos - m_centerPos;
		localFirstVelocity_y.Normalize();

		m_firstVirticalVelocity						= nk::math::CalcDotProduct( localFirstVelocity_y, newFirstVelocity );
		m_virticalVelocity							= m_firstVirticalVelocity;
	}
	
}

//===========================================================================
/*!	@brief		一時停止
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::Pause( void )
{
	m_calcFunc	= &EarthObject::_UpdateWait;
}

//===========================================================================
/*!	@brief		停止
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::Stop( void )
{
	m_frameCount	= 0;
	m_calcFunc		= &EarthObject::_UpdateWait;
	m_autoUpdate	= false;
}

//===========================================================================
/*!	@brief		投射速度を取得
	@param		----
	@return		----
*/
//===========================================================================
nk::math::Vector EarthObject::GetProjectionVelocity( void ) const
{
	const nk::math::Vector	axis_z( 0.0f, 0.0f, 1.0f );
	
	nk::math::Vector	verticalVelocity	= m_objectPos - m_centerPos;
	verticalVelocity.Normalize();
	
	nk::math::Vector	horizonalVelocity	= nk::math::CalcCrossProduct( verticalVelocity, axis_z );
	horizonalVelocity.Normalize();

	verticalVelocity	*= m_virticalVelocity;
	horizonalVelocity	*= m_horizonalVelocity;

#if defined(_DEBUG)
	nk::math::Vector	retVelocity	= verticalVelocity + horizonalVelocity;
	return retVelocity;
#else
	return verticalVelocity + horizonalVelocity;
#endif
}

//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::UpdatePosition( void )
{
	if( m_calcFunc ) {
		(this->*m_calcFunc)();
	}
	
}

//===========================================================================
/*!	@brief		垂直移動ベクトル取得
	@param		----
	@return		----
*/
//===========================================================================
nk::math::Vector EarthObject::GetVerticalVelocityVec( void ) const
{
	nk::math::Vector	velocity	= m_centerPos - m_objectPos;
	velocity.Normalize();
	velocity *= m_virticalVelocity;
	
	return velocity;
}


//===========================================================================
/*!	@brief		平行移動ベクトル取得
	@param		----
	@return		----
*/
//===========================================================================
nk::math::Vector EarthObject::GetHorizonalVelocityVec( void ) const
{
	nk::math::Vector	velocity	= m_centerPos - m_objectPos;
	velocity.Normalize();
	velocity *= m_horizonalVelocity;
	
	return velocity;
}

//===========================================================================
/*!	@brief		垂直速度取得
	@param		----
	@return		----
*/
//===========================================================================
f32 EarthObject::GetVerticalVelocity( void ) const
{

	return m_virticalVelocity;
}

//===========================================================================
/*!	@brief		平行速度取得
	@param		----
	@return		----
*/
//===========================================================================
f32 EarthObject::GetHrizonalVelocity( void ) const
{

	return m_horizonalVelocity;
}

//===========================================================================
/*!	@brief		位置設定
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::SetPos( const nk::math::Vector& pos )
{
	m_objectPos	= pos;
}


//===========================================================================
/*!	@brief		位置取得
	@param		----
	@return		----
*/
//===========================================================================
nk::math::Vector EarthObject::GetPos( void ) const
{
	return m_objectPos;
}


//===========================================================================
/*!	@brief		グローバル回転量を計算
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::CalcGlobalRotation( void )
{
	m_globalRotation	= nk::math::CalcVectorAngle( GetPos(), GAME_AXIS_Y );
	
	while( m_globalRotation < 0.0f ) {
		m_globalRotation += 2.0f * M_PI;
	}
	while( 2.0f * M_PI < m_globalRotation ) {
		m_globalRotation -= 2.0f * M_PI;
	}
	
	if( m_centerPos.x < GetPos().x ) {
		m_globalRotation = 2.0 * M_PI - m_globalRotation;
	}
	
}


//===========================================================================
/*!	@brief		グローバル回転量を加算
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::AddGlobalRotation( f32 rotation )
{
	m_globalRotation	= rotation;
}


//===========================================================================
/*!	@brief		グローバル回転量を取得
	@param		----
	@return		----
*/
//===========================================================================
f32 EarthObject::GetGlobalRotation( void ) const
{
	
	return m_globalRotation;
}

//===========================================================================
/*!	@brief		自動更新中ならtrue
	@param		----
	@return		----
*/
//===========================================================================
bool EarthObject::IsAutoUpdate( void ) const
{

	return m_autoUpdate;
}

//===========================================================================
/*!	@brief		移動
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::_UpdatePosition( void )
{
	_UpdateVelocity();

	SetPos( GetPos() + GetProjectionVelocity() );

	CalcGlobalRotation();
}

//===========================================================================
/*!	@brief		速度更新
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::_UpdateVelocity( void )
{
	if( m_frameCount <= INT_MAX ) {
		++m_frameCount;
	}	

	// 速度更新
	m_virticalVelocity	= m_firstVirticalVelocity - m_gravityAcceleration * m_frameCount;
	m_horizonalVelocity	= m_firstHorizonalVelocity - m_airResistance * m_frameCount;
}


//===========================================================================
/*!	@brief		待ち
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::_UpdateWait( void )
{

}
	
	
}	// namespace battle
	
}	// namespace game

