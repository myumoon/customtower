//=============================================================================
/*!	@file	drawModel.cpp

	@brief	描画モデル基底クラス

	@author	井手 竜之介
	@date	2012/03/03
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/render/renderModel.h"
#include "../../include/resource/resourcemanager.h"
#include "../../include/render/drawpacket.h"


namespace nk {
namespace graphics {

resource::ResourceManager*		RenderModel::m_resourceMng		= NULL;	// リソース管理
system::CameraManager*			RenderModel::m_cameraMng		= NULL;	// カメラ管理
graphics::DrawPacketManager*	RenderModel::m_drawPacketMng	= NULL;	// 描画パケット管理
	
//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
RenderModel::RenderModel()
{
	m_priority	= 0;
	m_screenId	= 0;
	m_visible	= true;
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
RenderModel::~RenderModel()
{
	
}


//===========================================================================
/*!	@brief	回転量をセット
	@param	amount	: 回転量
	@param	axis	: 回転軸
	@return	
*/
//===========================================================================
void RenderModel::SetRotate(f32 amount, const nk::math::Vector &axis)
{
	m_attitude.SetRotate(amount, axis);
}


//===========================================================================
/*!	@brief	回転量を追加
	@param	amount	: 回転量
	@param	axis	: 回転軸
	@return	
*/
//===========================================================================
void RenderModel::AddRotate(f32 amount, const nk::math::Vector &axis)
{
	m_attitude.AddRotate(amount, axis);
}


//===========================================================================
/*!	@brief	拡縮
	@param	scale	: 拡大量
	@return	
*/
//===========================================================================
void RenderModel::SetScale(f32 scale)
{
	m_attitude.SetScale(scale);
}


//===========================================================================
/*!	@brief	拡縮
	@param	scale	: 拡大量
	@return	
*/
//===========================================================================
void RenderModel::AddScale(f32 scale)
{
	m_attitude.AddScale(scale);
}


//===========================================================================
/*!	@brief	色のセット
	@param	color	: 色
	@return	なし
*/
//===========================================================================
void RenderModel::SetColor(nk::Color color)
{
	m_color = color;
}


//===========================================================================
/*!	@brief	描画優先度を設定
	@param	pri	: 優先度
	@return	なし
*/
//===========================================================================
void RenderModel::SetPriority(u32 pri)
{
	m_priority = pri;
}


//===========================================================================
/*!	@brief	スクリーンIDを設定
	@param	screenId	: セットするスクリーンID
	@return	なし
*/
//===========================================================================
void RenderModel::SetScreenId( s32 screenId )
{
	m_screenId = screenId;
}

//===========================================================================
/*!	@brief	表示非表示を設定
	@param	visible	: 表示非表示
	@return	なし
*/
//===========================================================================
void RenderModel::SetVisible( bool visible )
{
	m_visible = visible;
}

//===========================================================================
/*!	@brief	表示非表示を取得
	@param	----
	@return	----
*/
//===========================================================================
bool RenderModel::Visible( void ) const
{
	return m_visible;
}


}	// namespace graphics
}	// namespace nk