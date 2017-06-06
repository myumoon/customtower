//=============================================================================
/*!	@file	flickMoveCamera.h

	@brief	�t���b�N�ړ��J����

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "flickMoveCamera.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

const f32	FlickMoveCamera::FLICK_DECELERATION				= 0.50f;
const f32	FlickMoveCamera::FLICK_SPEED					= 0.30f;
const f32	FlickMoveCamera::DEFAULT_ZOOM_SPEED				= 5.00f;
const f32	FlickMoveCamera::DEFAULT_FIELD_OF_VISION		= 30.0f;
const f32	FlickMoveCamera::DEFAULT_MAX_FIELD_OF_VISION	= 60.0f;
const f32	FlickMoveCamera::DEFAULT_MIN_FIELD_OF_VISION	= 10.0f;

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
FlickMoveCamera::FlickMoveCamera()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
FlickMoveCamera::~FlickMoveCamera()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void FlickMoveCamera::_Init( void )
{
	m_mouse			= NULL;
	m_checkButton	= nk::input::Mouse::CLICK_LEFT;
	m_zoomSpeed		= DEFAULT_ZOOM_SPEED;
// 	m_checkButton.reserve( 32 );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void FlickMoveCamera::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		mouse	�Ď��}�E�X
	@param		button	�t���b�N�J�n�{�^��
	@return		----
*/
//===========================================================================
void FlickMoveCamera::Initialize( const nk::input::Mouse* mouse, nk::input::Mouse::MOUSE_NUM button )
{
	m_mouse			= mouse;
	m_checkButton	= button;
	m_flick.Initialize( m_mouse );
	m_flick.SetDeceleration( FLICK_DECELERATION );
	
	SetFieldOfVision( DEFAULT_FIELD_OF_VISION );
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void FlickMoveCamera::Update( void )
{
	if( m_mouse == NULL ) {
		return;
	}

	m_flick.Update();

	// �t���b�N
	if( m_flick.IsStopping( m_checkButton ) == false ) {
		const nk::math::Vector	flickVec	= m_flick.GetFlickVec( m_checkButton ) * FLICK_SPEED;
		const nk::math::Vector	toCamera	= GetPos() - GetLook();
		nk::math::Vector		localX		= nk::math::CalcCrossProduct( GetTop(), toCamera );
		nk::math::Vector		localY		= nk::math::CalcCrossProduct( toCamera, localX );

		localX.Normalize();
		localY.Normalize();

		const nk::math::Vector	moveVec		= localX * -flickVec.x + localY * flickVec.y;
		SetPos( GetPos() + moveVec );
		SetLook( GetLook() + moveVec );
	}

	// �Y�[��
	{
		f32	zoomSpeed	= 0.0f;
		if( m_mouse->IsPress( nk::input::Mouse::WHEEL_UP ) ) {
			zoomSpeed	= -GetZoomSpeed();
		}
		else if( m_mouse->IsPress( nk::input::Mouse::WHEEL_DOWN ) ) {
			zoomSpeed	= GetZoomSpeed();
		}

		{
			const f32	maxFieldOfVision	= DEFAULT_MAX_FIELD_OF_VISION;
			const f32	minFieldOfVision	= DEFAULT_MIN_FIELD_OF_VISION;
			const f32	nextFieldOfVision	= GetFieldOfVision() + zoomSpeed;
			const f32	setFieldOfVision	= nk::math::Clamp( nextFieldOfVision, minFieldOfVision, maxFieldOfVision );
			SetFieldOfVision( setFieldOfVision );
		}
// 		{
// 			const f32	minNear				= 0.1f;
// 			const f32	maxFar				= 1000.0f;
// 			const f32	near				= GetNearDistance() + zoomSpeed;
// 			const f32	setNear				= nk::math::Clamp( near, minNear, maxFar - 1.0f );
// 			
// 			SetNearDistance( setNear );
// 		}
	}
	
}

//===========================================================================
/*!	@brief		�Y�[�����x�ݒ�
	@param		speed	���x
	@return		----
*/
//===========================================================================
void FlickMoveCamera::SetZoomSpeed( f32 speed )
{
	m_zoomSpeed	= speed;
	
}


//===========================================================================
/*!	@brief		�Y�[�����x
	@param		----
	@return		----
*/
//===========================================================================
f32 FlickMoveCamera::GetZoomSpeed( void ) const
{
	
	return m_zoomSpeed;	
}


