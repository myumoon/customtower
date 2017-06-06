//=============================================================================
/*!	@file	animationModel.cpp

	@brief	アニメーションモデルクラス

	@author	井手 竜之介
	@date	2011/11/25
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/graphics/animationModel.h"
#include "../../include/resource/resourcemanager.h"
#include "../../include/render/drawpacket.h"
#include "../../include/math/quaternion.h"
#include "../../include/math/math.h"

namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
AnimationModel::AnimationModel() : 
	RenderModel(),
	m_toyFile(NULL),
	m_animation(NULL),
	m_animTime(1)
{
	m_priority = DrawPacket::DEFAULT_PRIORITY;
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
AnimationModel::~AnimationModel()
{
	
}


//===========================================================================
/*!	@brief	初期化
	@param	name	: オブジェクト名
	@return	なし
*/
//===========================================================================
void AnimationModel::Init(std::string name)
{
	m_toyFile = m_resourceMng->GetToyFile(name);
}


//===========================================================================
/*!	@brief	アニメーションをセット
	@param	アニメーション名
	@return	なし
*/
//===========================================================================
void AnimationModel::SetAnimation(std::string animName)
{
	m_animation	= m_toyFile->GetAnimation(animName);
	m_animTime	= 1;
}


//===========================================================================
/*!	@brief	アニメーションの更新
	@param	なし
	@return	なし
*/
//===========================================================================
void AnimationModel::Update()
{
	/* アニメーションフレームを更新 */
	if( m_animation ) {
		if( ++m_animTime > m_animation->lastFrame ) {
			m_animTime = 1;
		}
	}

}


//===========================================================================
/*!	@brief	描画
	@param	pos		: 位置
	@param	data	: シェーダーに使用する値(無くても良い)
	@return	なし
*/
//===========================================================================
void AnimationModel::Draw(const nk::math::Vector &pos, graphics::ShaderData& data)
{
	m_attitude.SetPos(pos);

	const math::Matrix44&			trans		= m_attitude.GetAttitudeMatrix();
	resource::ToyFile::_Mesh*		rootMesh	= m_toyFile->GetRootMesh();
	resource::Material				material	= m_toyFile->GetMaterial();

	material.SetColor(m_color);
	DrawMesh(rootMesh, material, trans, data);
	
}



//===========================================================================
/*!	@brief	メッシュの描画
	@param	drawMesh	: 描画するメッシュ
	@param	m			: マテリアル
	@param	parentMat	: 親のワールド行列
	@param	data		: シェーダーデータ
	@return	なし
*/
//===========================================================================
void AnimationModel::DrawMesh(resource::ToyFile::_Mesh *drawMesh, resource::Material m, const math::Matrix44 &parentMat, graphics::ShaderData& data)
{
	using namespace resource;

	if( !drawMesh ) {
		return;
	}

	/* パケット情報を設定 */
	graphics::DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();

	math::Quaternion animStart, animEnd;
	
	// m_animTimeからtを割り出して計算
	// drawMesh->nameがあるとは限らない
	// アニメーションに関係のないメッシュは動かないことも考える
	math::Matrix44		animMat;
	if( m_animation ) {
		const resource::ToyFile::_AnimationItem* animItem = m_animation->GetAnimationItem(drawMesh->name);

		if( animItem ) {
			animMat = _GetAnimationMatrix(animItem);
		}
	}
	math::Matrix44		world	= parentMat * animMat;

	data.worldMat = world;	// シェーダーの値を設定

	math::Matrix44 worldView;
	worldView = m_cameraMng->GetUseCameraMatrix() * world;
	
	packet.SetMaterial(m);
	packet.SetVertex(drawMesh->vertex);
	packet.SetFace(drawMesh->face);
	packet.SetNormalVertex(drawMesh->normal);
	packet.SetDrawType(graphics::DrawPacket::MODEL_ANIMATION);
	packet.SetWorldViewTransform(worldView);
	packet.SetShaderData(data);
	packet.SetPriority(m_priority);
	packet.SetScreenId(m_screenId);
	packet.SetWorldMatrix(world);

	m_drawPacketMng->SendToDrawManager( packet );
// 	packet.SendToDrawManager();		// 描画管理に送信
	
	/* ツリー先を描画 */
	u32 meshSize = drawMesh->mesh.size();
	for(u32 i = 0; i < meshSize; ++i) {
		DrawMesh(drawMesh->mesh[i], m, world, data);
	}

}


//===========================================================================
/*!	@brief	アニメーション行列を取得
	@param	animItem	: 取得したいアニメーションアイテム
	@return	変換行列
*/
//===========================================================================
math::Matrix44 AnimationModel::_GetAnimationMatrix(const nk::resource::ToyFile::_AnimationItem* animItem)
{
	using namespace resource;

	math::Matrix44 retMat;


	/* Attitudeのタイプ */
	enum {
		ATT_ROTATE_X		= ToyFile::_AnimationItem::RotateX,
		ATT_ROTATE_Y		= ToyFile::_AnimationItem::RotateY,
		ATT_ROTATE_Z		= ToyFile::_AnimationItem::RotateZ,
		ATT_TRANSLATE_X		= ToyFile::_AnimationItem::TranslateX,
		ATT_TRANSLATE_Y		= ToyFile::_AnimationItem::TranslateY,
		ATT_TRANSLATE_Z		= ToyFile::_AnimationItem::TranslateZ,
		ATT_MAX				= ToyFile::_AnimationItem::ITEM_TYPE_MAX
	};

	/*
		attitude配列にXYZ回転とXYZ移動を格納し、
		そこから変換行列を求める。
	*/
	const ToyFile::_Attitude* nextAttitude[ATT_MAX]	= { 0 };
	const ToyFile::_Attitude* prevAttitude[ATT_MAX]	= { 0 };

	for(s32 i = 0; i < ToyFile::_AnimationItem::ITEM_TYPE_MAX; ++i) {
		const ToyFile::_Transformation& trans = animItem->transform[i];
		nextAttitude[i]	= &trans.attitude[0];		// 姿勢は必ず1個以上あるのでとりあえず0番目を入れておく
		prevAttitude[i]	= nextAttitude[i];

		for(s32 j = 1; j < trans.keyNum; ++j) {
			if( m_animTime < trans.attitude[j].frame ) {
				nextAttitude[i] = &trans.attitude[j];
				break;
			}
			prevAttitude[i] = &trans.attitude[j];
		}
	}

	/* 回転クォータニオンを生成 */
	math::Quaternion prevRot, nextRot;


	{
		struct RotateAmount {
			f32 prevYaw;
			f32 prevPitch;
			f32 prevRoll;
			f32 nextYaw;
			f32 nextPitch;
			f32 nextRoll;
		};
		RotateAmount amount = {
			math::Rad(prevAttitude[ATT_ROTATE_Y]->trans),
			math::Rad(prevAttitude[ATT_ROTATE_X]->trans),
			math::Rad(prevAttitude[ATT_ROTATE_Z]->trans),
			math::Rad(nextAttitude[ATT_ROTATE_Y]->trans),
			math::Rad(nextAttitude[ATT_ROTATE_X]->trans),
			math::Rad(nextAttitude[ATT_ROTATE_Z]->trans)
		};
		prevRot.RotateYawPitchRoll(amount.prevYaw, amount.prevPitch, amount.prevRoll);
		nextRot.RotateYawPitchRoll(amount.nextYaw, amount.nextPitch, amount.nextRoll);
	}

	/* 現在のフレームからtを求める */
	s32 divNum = nextAttitude[ATT_ROTATE_X]->frame - prevAttitude[ATT_ROTATE_X]->frame;
	if( divNum == 0 ) {
		divNum = 1;
	}
	f32 t = static_cast<f32>(m_animTime - prevAttitude[ATT_ROTATE_X]->frame) / divNum;

	/* 回転量を球面線形補間 */
	math::Quaternion rot = math::Slerp(prevRot, nextRot, t);

	/* 平行移動成分を求める */
	f32 transX = prevAttitude[ATT_TRANSLATE_X]->trans + (nextAttitude[ATT_TRANSLATE_X]->trans - prevAttitude[ATT_TRANSLATE_X]->trans) * t;
	f32 transY = prevAttitude[ATT_TRANSLATE_Y]->trans + (nextAttitude[ATT_TRANSLATE_Y]->trans - prevAttitude[ATT_TRANSLATE_Y]->trans) * t;
	f32 transZ = prevAttitude[ATT_TRANSLATE_Z]->trans + (nextAttitude[ATT_TRANSLATE_Z]->trans - prevAttitude[ATT_TRANSLATE_Z]->trans) * t;

	/* 最終的な行列 */
	retMat = math::Translation(transX, transY, transZ) * math::GetQuaternionToMatrix(rot);


	return retMat;
}

}	// namespace graphics
}	// namespace nk