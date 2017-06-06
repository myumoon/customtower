//=============================================================================
/*!	@file	animationModel.cpp

	@brief	�A�j���[�V�������f���N���X

	@author	��� ���V��
	@date	2011/11/25
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/graphics/animationModel.h"
#include "../../include/resource/resourcemanager.h"
#include "../../include/render/drawpacket.h"
#include "../../include/math/quaternion.h"
#include "../../include/math/math.h"

namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
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
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
AnimationModel::~AnimationModel()
{
	
}


//===========================================================================
/*!	@brief	������
	@param	name	: �I�u�W�F�N�g��
	@return	�Ȃ�
*/
//===========================================================================
void AnimationModel::Init(std::string name)
{
	m_toyFile = m_resourceMng->GetToyFile(name);
}


//===========================================================================
/*!	@brief	�A�j���[�V�������Z�b�g
	@param	�A�j���[�V������
	@return	�Ȃ�
*/
//===========================================================================
void AnimationModel::SetAnimation(std::string animName)
{
	m_animation	= m_toyFile->GetAnimation(animName);
	m_animTime	= 1;
}


//===========================================================================
/*!	@brief	�A�j���[�V�����̍X�V
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void AnimationModel::Update()
{
	/* �A�j���[�V�����t���[�����X�V */
	if( m_animation ) {
		if( ++m_animTime > m_animation->lastFrame ) {
			m_animTime = 1;
		}
	}

}


//===========================================================================
/*!	@brief	�`��
	@param	pos		: �ʒu
	@param	data	: �V�F�[�_�[�Ɏg�p����l(�����Ă��ǂ�)
	@return	�Ȃ�
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
/*!	@brief	���b�V���̕`��
	@param	drawMesh	: �`�悷�郁�b�V��
	@param	m			: �}�e���A��
	@param	parentMat	: �e�̃��[���h�s��
	@param	data		: �V�F�[�_�[�f�[�^
	@return	�Ȃ�
*/
//===========================================================================
void AnimationModel::DrawMesh(resource::ToyFile::_Mesh *drawMesh, resource::Material m, const math::Matrix44 &parentMat, graphics::ShaderData& data)
{
	using namespace resource;

	if( !drawMesh ) {
		return;
	}

	/* �p�P�b�g����ݒ� */
	graphics::DrawPacket& packet	= m_drawPacketMng->PopDrawPacket();

	math::Quaternion animStart, animEnd;
	
	// m_animTime����t������o���Čv�Z
	// drawMesh->name������Ƃ͌���Ȃ�
	// �A�j���[�V�����Ɋ֌W�̂Ȃ����b�V���͓����Ȃ����Ƃ��l����
	math::Matrix44		animMat;
	if( m_animation ) {
		const resource::ToyFile::_AnimationItem* animItem = m_animation->GetAnimationItem(drawMesh->name);

		if( animItem ) {
			animMat = _GetAnimationMatrix(animItem);
		}
	}
	math::Matrix44		world	= parentMat * animMat;

	data.worldMat = world;	// �V�F�[�_�[�̒l��ݒ�

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
// 	packet.SendToDrawManager();		// �`��Ǘ��ɑ��M
	
	/* �c���[���`�� */
	u32 meshSize = drawMesh->mesh.size();
	for(u32 i = 0; i < meshSize; ++i) {
		DrawMesh(drawMesh->mesh[i], m, world, data);
	}

}


//===========================================================================
/*!	@brief	�A�j���[�V�����s����擾
	@param	animItem	: �擾�������A�j���[�V�����A�C�e��
	@return	�ϊ��s��
*/
//===========================================================================
math::Matrix44 AnimationModel::_GetAnimationMatrix(const nk::resource::ToyFile::_AnimationItem* animItem)
{
	using namespace resource;

	math::Matrix44 retMat;


	/* Attitude�̃^�C�v */
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
		attitude�z���XYZ��]��XYZ�ړ����i�[���A
		��������ϊ��s������߂�B
	*/
	const ToyFile::_Attitude* nextAttitude[ATT_MAX]	= { 0 };
	const ToyFile::_Attitude* prevAttitude[ATT_MAX]	= { 0 };

	for(s32 i = 0; i < ToyFile::_AnimationItem::ITEM_TYPE_MAX; ++i) {
		const ToyFile::_Transformation& trans = animItem->transform[i];
		nextAttitude[i]	= &trans.attitude[0];		// �p���͕K��1�ȏ゠��̂łƂ肠����0�Ԗڂ����Ă���
		prevAttitude[i]	= nextAttitude[i];

		for(s32 j = 1; j < trans.keyNum; ++j) {
			if( m_animTime < trans.attitude[j].frame ) {
				nextAttitude[i] = &trans.attitude[j];
				break;
			}
			prevAttitude[i] = &trans.attitude[j];
		}
	}

	/* ��]�N�H�[�^�j�I���𐶐� */
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

	/* ���݂̃t���[������t�����߂� */
	s32 divNum = nextAttitude[ATT_ROTATE_X]->frame - prevAttitude[ATT_ROTATE_X]->frame;
	if( divNum == 0 ) {
		divNum = 1;
	}
	f32 t = static_cast<f32>(m_animTime - prevAttitude[ATT_ROTATE_X]->frame) / divNum;

	/* ��]�ʂ����ʐ��`��� */
	math::Quaternion rot = math::Slerp(prevRot, nextRot, t);

	/* ���s�ړ����������߂� */
	f32 transX = prevAttitude[ATT_TRANSLATE_X]->trans + (nextAttitude[ATT_TRANSLATE_X]->trans - prevAttitude[ATT_TRANSLATE_X]->trans) * t;
	f32 transY = prevAttitude[ATT_TRANSLATE_Y]->trans + (nextAttitude[ATT_TRANSLATE_Y]->trans - prevAttitude[ATT_TRANSLATE_Y]->trans) * t;
	f32 transZ = prevAttitude[ATT_TRANSLATE_Z]->trans + (nextAttitude[ATT_TRANSLATE_Z]->trans - prevAttitude[ATT_TRANSLATE_Z]->trans) * t;

	/* �ŏI�I�ȍs�� */
	retMat = math::Translation(transX, transY, transZ) * math::GetQuaternionToMatrix(rot);


	return retMat;
}

}	// namespace graphics
}	// namespace nk