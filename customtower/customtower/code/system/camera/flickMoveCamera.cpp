//=============================================================================
/*!	@file	flickMoveCamera.h

	@brief	フリック移動カメラ

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "flickMoveCamera.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

const f32	FlickMoveCamera::FLICK_DECELERATION				= 0.50f;
const f32	FlickMoveCamera::FLICK_SPEED					= 0.30f;
const f32	FlickMoveCamera::DEFAULT_ZOOM_SPEED				= 5.00f;
const f32	FlickMoveCamera::DEFAULT_FIELD_OF_VISION		= 30.0f;
const f32	FlickMoveCamera::DEFAULT_MAX_FIELD_OF_VISION	= 60.0f;
const f32	FlickMoveCamera::DEFAULT_MIN_FIELD_OF_VISION	= 10.0f;

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
FlickMoveCamera::FlickMoveCamera()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
FlickMoveCamera::~FlickMoveCamera()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
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
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void FlickMoveCamera::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		mouse	監視マウス
	@param		button	フリック開始ボタン
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
/*!	@brief		更新
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

	// フリック
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

	// ズーム
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
/*!	@brief		ズーム速度設定
	@param		speed	速度
	@return		----
*/
//===========================================================================
void FlickMoveCamera::SetZoomSpeed( f32 speed )
{
	m_zoomSpeed	= speed;
	
}


//===========================================================================
/*!	@brief		ズーム速度
	@param		----
	@return		----
*/
//===========================================================================
f32 FlickMoveCamera::GetZoomSpeed( void ) const
{
	
	return m_zoomSpeed;	
}


