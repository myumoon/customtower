//=============================================================================
/*!	@file	sprite.h

	@brief	スプライト

	@author	井手 竜之介
	@date	2011/11/18
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/graphics/sprite.h"
#include "../../include/render/drawpacket.h"
#include "../../include/utility/autoTime.h"

namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Sprite::Sprite() :
	RenderModel(),
	m_texture(),
	m_uv(),
	m_wh(1.0f, 1.0f, 0.0f),
	m_scale(1.0f, 1.0f, 1.0f),
	m_rotate(0.0f),
	m_color(),
	m_drawMode(0)
{
	m_priority = DrawPacket::DEFAULT_SPRITE_PRIORITY;
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
Sprite::~Sprite()
{
	
}


//===========================================================================
/*!	@brief	初期化
	@param	name	: 表示するテクスチャ名
	@return	なし
*/
//===========================================================================
void Sprite::Init(const std::string& name)
{			
	m_texture 	= m_resourceMng->GetTexture(name);
	m_screenId	= 0;
}


//===========================================================================
/*!	@brief	クロップ設定
	@param	u,v,w,h	: 切り抜きを行うUV座標とその幅(0.0～1.0)
	@return	なし
*/
//===========================================================================
void Sprite::SetUVWH(f32 u, f32 v, f32 w, f32 h)
{
	m_uv.x = u;
	m_uv.y = v;
	m_wh.x = w;
	m_wh.y = h;
}


//===========================================================================
/*!	@brief	スケールを設定
	@param	scale	: スケール(0.0～)
	@return	なし
*/
//===========================================================================
void Sprite::SetScale(const nk::math::Vector &scale)
{
	m_scale = scale;
	m_scale.z = 1.0f;
}


//===========================================================================
/*!	@brief	スケールを設定
	@param	x,y	: 縦横に対してのスケール量
	@return	なし
*/
//===========================================================================
void Sprite::SetScale(f32 x, f32 y)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = 1.0f;
}


//===========================================================================
/*!	@brief	スケールを設定
	@param	scale	: 縦横に対してのスケール量
	@return	なし
*/
//===========================================================================
void Sprite::SetScale(f32 scale)
{
	SetScale(math::Vector(scale, scale, 1.0f));
}


//===========================================================================
/*!	@brief	色を設定
	@param	color	: 色
	@return	なし
*/
//===========================================================================
void Sprite::SetColor(const Color& color)
{
	m_color = color;
}


//===========================================================================
/*!	@brief	アルファ値を設定
	@param	alpha	: セットするアルファ値
	@return	なし
*/
//===========================================================================
void Sprite::SetAlpha(f32 alpha)
{
	m_color.a = static_cast<u8>(math::Clamp( alpha, 0.0f, 1.0f ) * 0xFF);
}


//===========================================================================
/*!	@brief	アルファ値を加算
	@param	alpha	: 加えるアルファ値
	@return	なし
*/
//===========================================================================
void Sprite::AddAlpha(f32 alpha)
{
	// 溢れないように一旦s32に変換
	s32	a	= static_cast<s32>(m_color.a);
	a		+= static_cast<s32>(alpha * 0xFF);
	a		= math::Clamp( a, 0x00, 0xFF);

	m_color.a = static_cast<u8>(a);
}


//===========================================================================
/*!	@brief	描画設定
	@param	mode	: 設定する描画モード
	@return	なし
*/
//===========================================================================
void Sprite::SetDrawMode(nk::graphics::Sprite::DRAW_MODE mode)
{
	m_drawMode |= mode;
}


//===========================================================================
/*!	@brief	描画設定
	@param	mode	: 解除する描画モード
	@return	なし
*/
//===========================================================================
void Sprite::RemoveDrawMode(nk::graphics::Sprite::DRAW_MODE mode)
{
	m_drawMode &= ~mode;
}


//===========================================================================
/*!	@brief	回転量を設定
	@param	rotate	: 回転量
	@return	なし
*/
//===========================================================================
void Sprite::SetRotate(f32 rotate)
{
	m_rotate = rotate;
}



//===========================================================================
/*!	@brief	描画
	@param	描画位置
	@return	なし
*/
//===========================================================================
void Sprite::Draw(const nk::math::Vector &pos)
{
	if( Visible() ) {
		_Draw( pos );
	}
}

//===========================================================================
/*!	@brief	描画
	@param	描画位置
	@return	なし
*/
//===========================================================================
void Sprite::_Draw(const nk::math::Vector &pos)
{
//  	AUTO_TIME( _Draw );
	DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();

	// 優先度
	packet.SetPriority(m_priority);

	// マテリアルを生成
	resource::Material material;

	// テクスチャ
	material.SetTexture(m_texture);
	packet.SetMaterial(material);

	// 色
	material.SetColor(m_color);
	packet.SetMaterial(material);

	// 頂点
	if( m_texture == NULL ) {
		return;
	}

	
	const f32 TEX_W = static_cast<f32>(m_texture->GetWidth());
	const f32 TEX_H = static_cast<f32>(m_texture->GetHeight());
	const f32 WIDTH	= (TEX_W * (m_uv.x + m_wh.x) - TEX_W * m_uv.x) / 2.0f;
	const f32 HEIGHT	= (TEX_H * (m_uv.y + m_wh.y) - TEX_H * m_uv.y) / 2.0f;
	
	// 頂点
	{
		if( m_drawMode & BILLBOARD ) {
			packet.AddVertex( -WIDTH,  HEIGHT, 0.0f );
			packet.AddVertex( -WIDTH, -HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH, -HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH,  HEIGHT, 0.0f );
		} else {
			packet.AddVertex( -WIDTH, -HEIGHT, 0.0f );
			packet.AddVertex( -WIDTH,  HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH,  HEIGHT, 0.0f );
			packet.AddVertex(  WIDTH, -HEIGHT, 0.0f );
		}
	}

	// 面
	{
		const math::Vector uvwh = m_uv + m_wh;
		packet.AddFace( 0, m_uv.x, m_uv.y );
		packet.AddFace( 1, m_uv.x, uvwh.y );
		packet.AddFace( 2, uvwh.x, uvwh.y );
		packet.AddFace( 0, m_uv.x, m_uv.y );
		packet.AddFace( 2, uvwh.x, uvwh.y );
		packet.AddFace( 3, uvwh.x, m_uv.y );
	}


	// ワールド変換行列
	math::Matrix44& worldView	= packet.GetWorldViewTransform();
	if( m_drawMode & BILLBOARD ) {
		packet.SetDrawType(DrawPacket::SPRITE_BILLBOARD);	// 描画タイプ:ビルボード

		//---------------ビルボード変換---------------
		math::Matrix44 billbord = m_cameraMng->GetUseCameraMatrix();
		billbord.ClearMoveComponent();		// 平行移動成分を消す
		billbord.Transpose();				// 転置

		math::Matrix44	trans = math::Translation(pos) * math::Expansion(m_scale.x, m_scale.y, m_scale.z) * math::RotateZ(m_rotate);
		const f32* transAry = trans.GetMatrix().ary16;				// 変換行列の省略形
		math::Vector	move(transAry[12], transAry[13], transAry[14]);	// モデルの平行移動成分を保存
	
		trans.ClearMoveComponent();				// 平行移動成分を消す

		math::Matrix44 a = billbord * trans;	// 
		a.SetElement(3, 0, move.x);
		a.SetElement(3, 1, move.y);
		a.SetElement(3, 2, move.z);

		worldView = m_cameraMng->GetUseCameraMatrix() * a;

	} else {
		packet.SetDrawType(DrawPacket::SPRITE);				// 描画タイプ:スプライト
		worldView = 
			math::Translation( pos )
			* math::Translation( math::Vector(WIDTH, HEIGHT, 0.0f) )
			* math::Expansion( m_scale.x, m_scale.y, m_scale.z )
			* math::RotateZ( m_rotate );
	}
	packet.SetScreenId( m_screenId );
	
// 	u64 _start = GetTimeMillSec();

	// 描画マネージャに登録
	m_drawPacketMng->SendToDrawManager( packet );
// 	PRINTF("_Draw : %ld\n", GetTimeMillSec() - _start);
}


//===========================================================================
/*!	@brief	テクスチャをセット
	@param	tex	: テクスチャ
	@return	なし
*/
//===========================================================================
void Sprite::SetTexture(nk::resource::Texture* tex)
{
	m_texture = tex;
}



//===========================================================================
/*!	@brief	テクスチャを取得
	@param	----
	@return	----
*/
//===========================================================================
const resource::Texture* Sprite::GetTexture( void ) const
{
	return m_texture;
}

	
}	// namespace graphics
}	// namespace nk






