//=============================================================================
/*!	@file	line.h

	@brief	ライン

	@author	井手 竜之介
	@date	2013/02/11
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/graphics/line.h"
#include "../../include/render/drawpacket.h"



namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Line::Line() : RenderModel()
{
	m_priority	= DrawPacket::DEFAULT_LINE_PRIORITY;
	m_mode		= RENDER_MODE_3D;
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
Line::~Line()
{
	
}


//===========================================================================
/*!	@brief	色を設定
	@param	color	: 色
	@return	なし
*/
//===========================================================================
void Line::SetColor(const Color& color)
{
	m_color = color;
}


//===========================================================================
/*!	@brief	アルファ値を設定
	@param	alpha	: セットするアルファ値
	@return	なし
*/
//===========================================================================
void Line::SetAlpha(f32 alpha)
{
	m_color.a = static_cast<u8>(math::Clamp( alpha, 0.0f, 1.0f ) * 0xFF);
}


//===========================================================================
/*!	@brief	アルファ値を加算
	@param	alpha	: 加えるアルファ値
	@return	なし
*/
//===========================================================================
void Line::AddAlpha(f32 alpha)
{
	// 溢れないように一旦s32に変換
	s32	a	= static_cast<s32>(m_color.a);
	a		+= static_cast<s32>(alpha * 0xFF);
	
	if( a < 0 )			{ a = 0;	}
	else if( a > 0xFF )	{ a = 0xFF;	}

	m_color.a = a;
}



//===========================================================================
/*!	@brief	描画点を追加
	@param	pos		描画点
	@return	なし
*/
//===========================================================================
void Line::AddPoint( const math::Vector& pos )
{

	m_points.Add( pos );
	
}



//===========================================================================
/*!	@brief	描画点をクリア
	@param	----
	@return	----
*/
//===========================================================================
void Line::ClearPoints( void )
{

	m_points.Clear();
	
}



//===========================================================================
/*!	@brief	描画
	@param	描画位置
	@return	なし
*/
//===========================================================================
void Line::Draw( const nk::math::Vector &pos )
{
// 	DrawPacket packet;
	graphics::DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();

	// 優先度
	packet.SetPriority( m_priority );

	// マテリアルを生成
	resource::Material material;

	// 色
	material.SetColor( m_color );
	packet.SetMaterial( material );

	// 描画点
	packet.SetVertex( m_points );

	// 描画モード
	if( m_mode == RENDER_MODE_3D ) {
		packet.SetDrawType( DrawPacket::LINE3D );
	}
	else /*if( m_mode == RENDER_MODE_2D )*/ {
		packet.SetDrawType( DrawPacket::LINE2D );
	}
	
	/* 行列を計算 */
	math::Matrix44& view		= m_cameraMng->GetUseCameraMatrix();
	math::Matrix44&	world		= m_attitude.GetAttitudeMatrix();
	math::Matrix44	worldView	= view * world;
	//math::Matrix44	worldView	= view * world;

	
	// ワールド変換行列
	//math::Matrix44 worldView;
	
	//worldView = math::Translation( pos );
// 	worldView = 
// 		math::Translation( pos )
// 		* math::Translation( math::Vector(WIDTH, HEIGHT, 0.0f) )
// 		* math::Expansion( m_scale.x, m_scale.y, m_scale.z )
// 		* math::RotateZ( m_rotate );

	if( m_mode == RENDER_MODE_3D ) {
// 		packet.SetWorldViewTransform( worldView );
	}
	else {
		worldView =	math::Translation( pos );
// 					* math::Translation( math::Vector(WIDTH, HEIGHT, 0.0f) )
// 					* math::Expansion( m_scale.x, m_scale.y, m_scale.z )
// 					* math::RotateZ( m_rotate );
	}
	packet.SetWorldViewTransform( worldView );
	
	packet.SetScreenId( m_screenId );

	// 描画マネージャに登録
// 	packet.SendToDrawManager();
	m_drawPacketMng->SendToDrawManager( packet );
}


//===========================================================================
/*!	@brief		レンダリングモード設定
	@param		mode	レンダリングモード
	@return		----
*/
//===========================================================================
void Line::SetRenderMode( RENDER_MODE mode )
{
	m_mode	= mode;
	
}

}	// namespace graphics
}	// namespace nk






