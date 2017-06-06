//=============================================================================
/*!	@file	modelTestScene.h

	@brief	���f���`��e�X�g

	@author	ryunosuke ide
	@date	2013.05.25
*/
//=============================================================================

#ifndef __MODEL_TEST_SCENE_H__
#define __MODEL_TEST_SCENE_H__

#include "utility/selector.h"
#include "system.h"

#include "game/scene/sceneInterface.h"



namespace game {


//=============================================================================
/*!
								�^�C�g��
*/
//=============================================================================
class ModelTestScene : public SceneInterface {
public: 
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		���[�J���X�V
	*/
	//===========================================================================
	virtual s32		ExecuteLocal( s32 parentMessage );

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	virtual void	RenderLocal( void );
	
	//===========================================================================
	/*!	@brief		�c���[����
	*/
	//===========================================================================
	virtual void	CreateTree( void ) {}

	//===========================================================================
	/*!	@brief		���\�[�X����
	*/
	//===========================================================================
	virtual void	InitializeScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		���\�[�X�폜
	*/
	//===========================================================================
	virtual void	TerminateScene( SceneInterface* parent );

	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );


	//----------------------�����o�ϐ�-----------------------
	f32									m_sphereRot;		// 
	FILE*								m_fpOut;			// �t�@�C��
	nk::graphics::Model					m_floor;			// �n��
	nk::graphics::Model					m_sphere;			// ����
	nk::graphics::AnimationModel		m_animModel;		// �@�B���f��
	nk::math::Vector					m_pos;				// �@�B���f���̈ʒu
	nk::BVRay							m_hitRay;			// �����q�b�g
	nk::BVSphere						m_hitSphere;		// ���q�b�g
	nk::BVInfiniteFace					m_infinitie;		// ��������
	nk::graphics::Sprite				m_shadowMapSprite;	// �V���h�E�}�b�v�X�v���C�g
	nk::graphics::Sprite				m_loadIcon;			// ���[�h�A�C�R��
	nk::graphics::Line					m_line;				// ��
	nk::resource::ResourceLoader*		m_resourceLoader;	// ���\�[�X���[�h
	bool								m_modelInit;		// ���f��������

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			ModelTestScene();
	virtual~ModelTestScene();
};
	
}	// namespace game




#endif  // __MODEL_TEST_SCENE_H__