//=============================================================================
/*!	@file	drawpacket.cpp

	@brief	描画パケットクラス

	@author	井手 竜之介
	@date	2011/11/16
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/render/drawpacket.h"
#include "../../include/render/renderManager.h"



namespace nk {
namespace graphics {

//------------------------------静的メンバ定義------------------------------
RenderManager*	DrawPacket::m_drawManager			= NULL;
const u32	DrawPacket::DEFAULT_PRIORITY		= 0x00010000;
const u32	DrawPacket::DEFAULT_SPRITE_PRIORITY	= 0x00100000;
const u32	DrawPacket::DEFAULT_LINE_PRIORITY	= 0x01000000;



//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
DrawPacket::DrawPacket( void ) : 
	m_material(), 
	m_type(0),
	m_priority(DEFAULT_PRIORITY),
	m_isClearBuffer(false)
{
}

#if 0
//===========================================================================
/*!	@brief	コピーコンストラクタ
	@param	なし
*/
//===========================================================================
DrawPacket::DrawPacket(const DrawPacket& pack) : 
	//m_texture(pack.m_texture),
	m_material(pack.m_material),
	m_vertex(pack.m_vertex),
	m_face(pack.m_face),
	m_normal(pack.m_normal),
	m_worldViewTransform(pack.m_worldViewTransform),
	m_type(pack.m_type),
	m_priority(pack.m_priority),
	m_isClearBuffer(pack.m_isClearBuffer),
	m_screenId(pack.m_screenId)
{
	
}
#endif


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
DrawPacket::~DrawPacket()
{
	
}


//===========================================================================
/*!	@brief	テクスチャをセット
	@param	tex	: テクスチャ
	@return	なし
*/
//===========================================================================
//void DrawPacket::SetTexture(const resource::Texture* tex)
//{
//	m_texture = tex;
//}


//===========================================================================
/*!	@brief	テクスチャを取得
	@param	なし
	@return	テクスチャ
*/
//===========================================================================
//const resource::Texture* DrawPacket::GetTexture( void ) const
//{
//	return m_texture;
//}


//===========================================================================
/*!	@brief	マテリアルをセット
	@param	tex	: マテリアル
	@return	なし
*/
//===========================================================================
void DrawPacket::SetMaterial(const resource::Material& mat)
{
	m_material = mat;
}


//===========================================================================
/*!	@brief	マテリアルを取得
	@param	なし
	@return	マテリアル
*/
//===========================================================================
resource::Material DrawPacket::GetMaterial( void ) const
{
	return m_material;
}


//===========================================================================
/*!	@brief	頂点をセット
	@param	v	: 頂点
	@return	なし
*/
//===========================================================================
void DrawPacket::SetVertex(const resource::Vertex& v)
{
	m_vertex.Clear();
	
	for( u32 i = 0; i < v.GetSize(); ++i ) {
		m_vertex.Add( v.GetVertex( i ) );
	}
	
}



//===========================================================================
/*!	@brief	頂点をセット
	@param	v	: 頂点
	@return	なし
*/
//===========================================================================
void DrawPacket::AddVertex( const math::Vector& v )
{
	m_vertex.Add( v );
}


//===========================================================================
/*!	@brief	頂点をセット
	@param	v	: 頂点
	@return	なし
*/
//===========================================================================
void DrawPacket::AddVertex( f32 x, f32 y, f32 z )
{
	m_vertex.Add( x, y, z );
}


//===========================================================================
/*!	@brief	頂点を取得
	@param	なし
	@return	頂点
*/
//===========================================================================
resource::Vertex& DrawPacket::GetVertex( void )
{
	return m_vertex;
}



//===========================================================================
/*!	@brief	頂点を取得
	@param	なし
	@return	頂点
*/
//===========================================================================
const resource::Vertex& DrawPacket::GetVertex( void ) const
{
	return m_vertex;
}


//===========================================================================
/*!	@brief	面をセット
	@param	face	: 頂点
	@return	なし
*/
//===========================================================================
void DrawPacket::SetFace(const resource::Face& face)
{
	m_face = face;
}


//===========================================================================
/*!	@brief	面をセット
	@param	face	: 頂点
	@return	なし
*/
//===========================================================================
void DrawPacket::AddFace( u32 index, const math::Vector& uv )
{
	m_face.AddFaceUV( index, uv );
}


//===========================================================================
/*!	@brief	面をセット
	@param	face	: 頂点
	@return	なし
*/
//===========================================================================
void DrawPacket::AddFace( u32 index, f32 u, f32 v )
{
	m_face.AddFaceUV( index, u, v );
}


//===========================================================================
/*!	@brief	面を取得
	@param	なし
	@return	頂点
*/
//===========================================================================
resource::Face& DrawPacket::GetFace( void )
{
	return m_face;
}



//===========================================================================
/*!	@brief	面を取得
	@param	なし
	@return	頂点
*/
//===========================================================================
const resource::Face& DrawPacket::GetFace( void ) const
{
	return m_face;
}


//===========================================================================
/*!	@brief	頂点法線をセット
	@param	n	: 頂点法線
	@return	なし
*/
//===========================================================================
void DrawPacket::SetNormalVertex(const resource::Vertex& n)
{
	m_normal = n;
}


//===========================================================================
/*!	@brief	頂点法線を取得
	@param	なし
	@return	頂点法線
*/
//===========================================================================
resource::Vertex& DrawPacket::GetNormalVertex( void )
{
	return m_normal;
}


//===========================================================================
/*!	@brief	ワールドビュー変換行列をセット
	@param	mat	: 変換行列
	@return	なし
*/
//===========================================================================
void DrawPacket::SetWorldViewTransform(const math::Matrix44& mat)
{
	m_worldViewTransform = mat;
}


//===========================================================================
/*!	@brief	ワールド変換行列を取得
	@param	なし
	@return	ワールド変換行列
*/
//===========================================================================
const math::Matrix44& DrawPacket::GetWorldViewTransform( void ) const
{
	return m_worldViewTransform;
}


//===========================================================================
/*!	@brief	ワールド変換行列を取得
	@param	なし
	@return	ワールド変換行列
*/
//===========================================================================
math::Matrix44& DrawPacket::GetWorldViewTransform( void )
{
	return m_worldViewTransform;
}


//===========================================================================
/*!	@brief	描画タイプを設定
	@param	type	: 描画タイプ
	@return	なし
*/
//===========================================================================
void DrawPacket::SetDrawType(DRAW_TYPE type)
{
	m_type |= type;
}


//===========================================================================
/*!	@brief	マネージャに転送
	@param	なし
	@return	なし
*/
//===========================================================================
// void DrawPacket::SendToDrawManager( void )
// {
// 	m_drawManager->Add(*this);
// }


//===========================================================================
/*!	@brief	描画前処理リストに転送
	@param	なし
	@return	なし
*/
//===========================================================================
//void DrawPacket::SendToDrawTextureList( void )
//{
//	m_drawManager->AddDrawTextureList(*this);
//}


//===========================================================================
/*!	@brief	シェーダーデータをセット
	@param	data	: シェーダーデータ
	@return	なし
*/
//===========================================================================
void DrawPacket::SetShaderData(const nk::graphics::ShaderData &data)
{
	m_material.SetShaderData(data);
}


//===========================================================================
/*!	@brief	描画優先度を設定
	@param	num		: 優先度
	@return	なし
*/
//===========================================================================
void DrawPacket::SetPriority(u32 num)
{
	m_priority = num;
}


//===========================================================================
/*!	@brief	描画優先度を習得
	@param	なし
	@return	なし
*/
//===========================================================================
u32 DrawPacket::GetPriority( void ) const
{
	return m_priority;
}


//===========================================================================
/*!	@brief	バッファクリアオブジェクトを挿入
	@param	なし
	@return	なし
*/
//===========================================================================
// void DrawPacket::AddListForBufferClear( void )
// {
// 	m_isClearBuffer = true;
// 	SendToDrawManager();
// }


//===========================================================================
/*!	@brief	バッファクリアフラグを習得
	@param	なし
	@return	true	: バッファをクリア
	@return	false	: クリアしない
*/
//===========================================================================
// bool DrawPacket::IsBufferClear( void ) const
// {
// 	return m_isClearBuffer;
// }


//===========================================================================
/*!	@brief		空にする
	@param		----
	@return		----
*/
//===========================================================================
void DrawPacket::Clear( void )
{

	m_type				= 0;
	m_priority			= DEFAULT_PRIORITY;
	m_isClearBuffer		= false;

	m_material.Clear();
	m_vertex.Clear();
	m_face.Clear();
	m_normal.Clear();
	m_worldViewTransform.InitIdentityMatrix();	// 単位行列
	m_world.InitIdentityMatrix();				// 単位行列
	
}

}	// namespace graphics
}	// namespace nk