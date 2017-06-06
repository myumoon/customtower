//=============================================================================
/*!	@file	flick.cpp

	@brief	フリック入力

	@author	ryunosuke ide
	@date	2013.06.27
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/input/flick.h"
#include "../../include/input/mouse.h"
#include "../../include/general.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

namespace nk {
namespace input {
	
const f32	Flick::DEFAULT_DECELERATION		= 0.85f;	// デフォルト減衰率
	
}	// namespace input
}	// namespace nk

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {

namespace input {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Flick::Flick()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Flick::~Flick()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Flick::_Init( void )
{
	m_mouse			= NULL;
	m_deceleration	= DEFAULT_DECELERATION;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Flick::_Term( void )
{

}


//===========================================================================
/*!	@brief		マウス設定
	@param		mouse	マウス
	@return		----
*/
//===========================================================================
void Flick::Initialize( const Mouse* mouse )
{
	m_mouse	= mouse;
}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void Flick::Update( void )
{
	if( m_mouse == NULL ) {
		return;
	}

	for( s32 button = 0; button < Mouse::MOUSE_MAX; ++button ) {
		// 押された瞬間は何もしない
		if( m_mouse->IsPressed( button ) ) {
			m_prevPos[button]	= m_mouse->GetPos();
			m_flickVec[button].Clear();
		}
		// 押しっぱなしでマウスについていく
		else if( m_mouse->IsPress( button ) ) {
			m_flickVec[button]	= m_mouse->GetPos() - m_prevPos[button];
			m_prevPos[button]	= m_mouse->GetPos();
		}
		// 入力がなかったら減速
		else {
			m_flickVec[button] *= m_deceleration;
			if( m_flickVec[button].GetNorm2() <= 1.0f ) {
				m_flickVec[button].Clear();
			}
		}
	}
	
}

//===========================================================================
/*!	@brief		減速率設定
	@param		deceleration	減速率
	@return		----
*/
//===========================================================================
void Flick::SetDeceleration( f32 deceleration )
{
	m_deceleration	= deceleration;
	
}

//===========================================================================
/*!	@brief		フリック量取得
	@param		----
	@return		----
*/
//===========================================================================
math::Vector Flick::GetFlickVec( s32 button ) const
{
	INDEX_ASSERT( button, Mouse::MOUSE_MAX, "index error" );
	if( (0 <= button) && button < Mouse::MOUSE_MAX ) {
		return m_flickVec[button];
	}
	return math::Vector();
}
	
//===========================================================================
/*!	@brief		停止時にtrueを返す
	@param		----
	@return		----
*/
//===========================================================================
bool Flick::IsStopping( s32 button ) const
{
	INDEX_ASSERT( button, Mouse::MOUSE_MAX, "index error" );
	if( (0 <= button) && button < Mouse::MOUSE_MAX ) {
		if( m_flickVec[button].GetNorm2() < 1.0f ) {
			return true;
		}
	}
	
	return false;
}
	
}	// namespace input
	
}	// namespace nk