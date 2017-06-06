//=============================================================================
/*!	@file	earthObject.h

	@brief	�ʒu�v�Z

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#define _USE_MATH_DEFINES	// M_PI
#include <math.h>

#include "gameDef.h"

#include "earthObject.h"
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
EarthObject::EarthObject()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
EarthObject::~EarthObject()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
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
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void EarthObject::_Term( void )
{

}


//===========================================================================
/*!	@brief		�Z�b�g�A�b�v
	@param		gravityAcc		�d�͉����x
	@param		centerPos		���S�ʒu
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
/*!	@brief		��C��R�ݒ�
	@param		airResistance	��C��R�l
	@return		----
	@note		�ݒ肵���l���������t���[����������
*/
//===========================================================================
void EarthObject::SetAirResistance( f32 airResistance )
{
	m_airResistance	= airResistance;
}

//===========================================================================
/*!	@brief		�J�n
	@param		firstVelocity			�����x
	@param		true.���݂̑��x�ɉ��Z	false.�V�����v�Z
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

	// �������������x�v�Z
	{
		nk::math::Vector	localFirstVelocity_y	= m_objectPos - m_centerPos;
		nk::math::Vector	localFirstVelocity_x	= nk::math::CalcCrossProduct( localFirstVelocity_y, axis_z );
		localFirstVelocity_x.Normalize();

		// �E���� ������
		m_firstHorizonalVelocity					= nk::math::CalcDotProduct( localFirstVelocity_x, newFirstVelocity );
		m_horizonalVelocity							= m_firstHorizonalVelocity;
	}

	// �������������x�v�Z
	{
		nk::math::Vector	localFirstVelocity_y	= m_objectPos - m_centerPos;
		localFirstVelocity_y.Normalize();

		m_firstVirticalVelocity						= nk::math::CalcDotProduct( localFirstVelocity_y, newFirstVelocity );
		m_virticalVelocity							= m_firstVirticalVelocity;
	}
	
}

//===========================================================================
/*!	@brief		�ꎞ��~
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::Pause( void )
{
	m_calcFunc	= &EarthObject::_UpdateWait;
}

//===========================================================================
/*!	@brief		��~
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
/*!	@brief		���ˑ��x���擾
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
/*!	@brief		�X�V
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
/*!	@brief		�����ړ��x�N�g���擾
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
/*!	@brief		���s�ړ��x�N�g���擾
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
/*!	@brief		�������x�擾
	@param		----
	@return		----
*/
//===========================================================================
f32 EarthObject::GetVerticalVelocity( void ) const
{

	return m_virticalVelocity;
}

//===========================================================================
/*!	@brief		���s���x�擾
	@param		----
	@return		----
*/
//===========================================================================
f32 EarthObject::GetHrizonalVelocity( void ) const
{

	return m_horizonalVelocity;
}

//===========================================================================
/*!	@brief		�ʒu�ݒ�
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::SetPos( const nk::math::Vector& pos )
{
	m_objectPos	= pos;
}


//===========================================================================
/*!	@brief		�ʒu�擾
	@param		----
	@return		----
*/
//===========================================================================
nk::math::Vector EarthObject::GetPos( void ) const
{
	return m_objectPos;
}


//===========================================================================
/*!	@brief		�O���[�o����]�ʂ��v�Z
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
/*!	@brief		�O���[�o����]�ʂ����Z
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::AddGlobalRotation( f32 rotation )
{
	m_globalRotation	= rotation;
}


//===========================================================================
/*!	@brief		�O���[�o����]�ʂ��擾
	@param		----
	@return		----
*/
//===========================================================================
f32 EarthObject::GetGlobalRotation( void ) const
{
	
	return m_globalRotation;
}

//===========================================================================
/*!	@brief		�����X�V���Ȃ�true
	@param		----
	@return		----
*/
//===========================================================================
bool EarthObject::IsAutoUpdate( void ) const
{

	return m_autoUpdate;
}

//===========================================================================
/*!	@brief		�ړ�
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
/*!	@brief		���x�X�V
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::_UpdateVelocity( void )
{
	if( m_frameCount <= INT_MAX ) {
		++m_frameCount;
	}	

	// ���x�X�V
	m_virticalVelocity	= m_firstVirticalVelocity - m_gravityAcceleration * m_frameCount;
	m_horizonalVelocity	= m_firstHorizonalVelocity - m_airResistance * m_frameCount;
}


//===========================================================================
/*!	@brief		�҂�
	@param		----
	@return		----
*/
//===========================================================================
void EarthObject::_UpdateWait( void )
{

}
	
	
}	// namespace battle
	
}	// namespace game

