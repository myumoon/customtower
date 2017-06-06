//=============================================================================
/*!	@file	model.cpp

	@brief	モデルクラス

	@author	井手 竜之介
	@date	2012/02/22
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/graphics/model.h"
#include "../../include/resource/resourcemanager.h"
#include "../../include/render/drawpacket.h"


namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Model::Model() : 
	RenderModel(),
	m_file(NULL)
{
	m_priority = DrawPacket::DEFAULT_PRIORITY;
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
Model::~Model()
{
	
}


//===========================================================================
/*!	@brief	初期化
	@param	filename	: オブジェクト名
	@return	なし
*/
//===========================================================================
void Model::Init(std::string filename)
{
	m_file = m_resourceMng->GetMqoFile(filename);
	m_color = m_file->GetMaterial().GetColor();
}



//===========================================================================
/*!	@brief	描画
	@param	data	: シェーダーデータ
	@return	なし
*/
//===========================================================================
void Model::Draw(graphics::ShaderData& data)
{
	
	/* 行列を計算 */
	math::Matrix44& view		= m_cameraMng->GetUseCameraMatrix();
	math::Matrix44&	world		= m_attitude.GetAttitudeMatrix();
	math::Matrix44	worldView	= view * world;
	
	/* シェーダー設定 */
	data.worldMat = world;
	
	/* マテリアル */
	resource::Material material = m_file->GetMaterial();
	material.SetColor(m_color);

	/* パケット情報を設定 */
	graphics::DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();
	packet.SetMaterial(material);
	packet.SetVertex(m_file->GetVertex());
	packet.SetFace(m_file->GetFace());
	packet.SetNormalVertex(m_file->GetNormalVertex());
	packet.SetDrawType(graphics::DrawPacket::MODEL);
	packet.SetWorldViewTransform(worldView);
	packet.SetShaderData(data);
	packet.SetPriority(m_priority);
	packet.SetScreenId(m_screenId);
	packet.SetWorldMatrix(world);

	/* 描画管理に送信 */
	m_drawPacketMng->SendToDrawManager( packet );

}


//===========================================================================
/*!	@brief	描画
	@param	pos	: 描画位置
	@return	なし
*/
//===========================================================================
void Model::Draw(const nk::math::Vector &pos, graphics::ShaderData& data)
{
	
	/* 行列を計算 */
	m_attitude.SetPos(pos);
	Draw(data);

}





}	// namespace graphics
}	// namespace nk