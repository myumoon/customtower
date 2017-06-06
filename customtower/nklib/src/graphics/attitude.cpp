//=============================================================================
/*!	@file	attitude.cpp

	@brief	姿勢行列生成クラス

	@author	井手 竜之介
	@date	2011/11/25
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/graphics/attitude.h"



namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Attitude::Attitude() : 
	//m_rotFlag(FLAG_NONE),
	//m_rotate(0),
	//m_rotAxis(),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pos(0.0f, 0.0f, 0.0f)
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
Attitude::~Attitude()
{
	
}


//===========================================================================
/*!	@brief	姿勢行列を取得
	@param	なし
	@return	姿勢行列
*/
//===========================================================================
math::Matrix44 Attitude::GetAttitudeMatrix() const
{
	math::Matrix44& moveMat		= math::Translation( m_pos );
	math::Matrix44& scaleMat	= math::Expansion( m_scale.x, m_scale.y, m_scale.z );
	//math::Matrix44& rotMat		= math::RotateAxis(m_rotate, m_rotAxis);

	return  moveMat * scaleMat * m_rotate;
}


//===========================================================================
/*!	@brief	位置をセット
	@param	pos	: 位置
	@return	なし
*/
//===========================================================================
void Attitude::SetPos( const nk::math::Vector &pos )
{
	m_pos = pos;
}



//===========================================================================
/*!	@brief	位置を追加
	@param	pos	: 追加する位置
	@return	なし
*/
//===========================================================================
void Attitude::AddPos( const math::Vector& pos )
{
	m_pos += pos;
}


//===========================================================================
/*!	@brief	スケールをセット
	@param	scale	: スケール
	@return	なし
*/
//===========================================================================
void Attitude::SetScale( const math::Vector& scale )
{
	m_scale = scale;
}


//===========================================================================
/*!	@brief	スケールをセット
	@param	scale	: スケール
	@return	なし
*/
//===========================================================================
void Attitude::SetScale( f32 scale )
{
	if( scale < 0 ) {
		scale = 0;
	}
	m_scale.x = m_scale.y = m_scale.z = scale;
}


//===========================================================================
/*!	@brief	スケールを追加
	@param	scale	: 追加するスケール
	@return	なし
*/
//===========================================================================
void Attitude::AddScale( f32 scale )
{
	m_scale.x += scale;
	if( m_scale.x < 0.0f ) {
		m_scale.x = 0.0f;
	}
	m_scale.y += scale;
	if( m_scale.y < 0.0f ) {
		m_scale.y = 0.0f;
	}
	m_scale.z += scale;
	if( m_scale.z < 0.0f ) {
		m_scale.z = 0.0f;
	}
}


//===========================================================================
/*!	@brief	回転量をセット
	@param	amount	: 回転量
	@param	axis	: 回転軸
	@return	なし
*/
//===========================================================================
void Attitude::SetRotate( f32 amount, const nk::math::Vector &axis )
{
	//m_rotate = amount;
	//m_rotAxis = axis;
	m_rotate = math::RotateAxis( amount, axis );
}


//===========================================================================
/*!	@brief	回転量を追加
	@param	amount	: 回転量
	@param	axis	: 回転軸
	@return	なし
*/
//===========================================================================
void Attitude::AddRotate( f32 amount, const nk::math::Vector &axis )
{
	m_rotate *= math::RotateAxis( amount, axis );
}

}	// namespace graphics
}	// namespace nk