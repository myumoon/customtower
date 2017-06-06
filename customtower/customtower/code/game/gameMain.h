//=============================================================================
/*!	@file	gameMain.h

	@brief	���C���֐�

	@author	ryunosuke ide
	@date	2011/11/15
*/
//=============================================================================

#ifndef __GAME_MAIN_H__
#define __GAME_MAIN_H__


#include "system.h"
#include "game/scene/sceneManager.h"
#include "system/renderObjectManager.h"
#include "debug/gameDebug.h"
#include "system/camera/flickMoveCamera.h"
//#include "debug/debugCaller.h"
//#include "gameObject.h"
//#include "renderObject.h"
//#include "renderObjectManager.h"


using namespace nk;

class RenderObjectManager;

namespace game {

class RenderObject;
class SceneManager;
	
//=============================================================================
/*!
								�Q�[�����C��
*/
//=============================================================================
class GameMain : public nk::Main {
public:
	//-----------------------�^��`--------------------------

	//! �X�N���[��
	enum eSCREEN_ID {
		eSCREEN_ID_1			= Main::eSCREEN_ID_USER,
		eSCREEN_ID_SHADOWMAP,
	};

	static const s32	SCREEN_WIDTH	= 1024;	//!< �X�N���[����
	static const s32	SCREEN_HEIGHT	= 768;	//!< �X�N���[������


	//----------------------�ÓI�����o-----------------------

	//! �V�[���ύX�f�o�b�O
	DEBUG_MENU_PROC_CALLBACK( DebugCallback_SceneChange );

	
	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	virtual bool		Initialize( void );

	//===========================================================================
	/*!	@brief		�I������
	*/
	//===========================================================================
	virtual void		Terminate( void );

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual bool		Update( void );

	//===========================================================================
	/*!	@brief		�`��O����
	*/
	//===========================================================================
	virtual void		DrawInitialize( void );

	//===========================================================================
	/*!	@brief		�`��㏈��
	*/
	//===========================================================================
	virtual void		DrawTerminate( void );

	//===========================================================================
	/*!	@brief		�V�[���؂�ւ�
	*/
	//===========================================================================
	void				SetNextScene( SceneManager::SCENE_ID id );

	//===========================================================================
	/*!	@brief		�V�[�P���X�Ǘ��擾
	*/
	//===========================================================================
	SceneManager*		GetSceneManager( void ) const;

	//===========================================================================
	/*!	@brief		���[�h�A�C�R���J�n
	*/
	//===========================================================================
	void				StartLoadingIcon( void );

	//===========================================================================
	/*!	@brief		���[�h�A�C�R����~
	*/
	//===========================================================================
	void				StopLoadingIcon( void );

	//===========================================================================
	/*!	@brief		�V�X�e���R�[���o�b�N
	*/
	//===========================================================================
	virtual void		CallbackEvent( nk::Main::SYSTEM_EVENT event );
protected:

private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	// �`��
	void	_Draw( void );


	//----------------------�����o�ϐ�-----------------------
	SceneManager*						m_sceneManager;				//!< �V�[�P���X�Ǘ�
	RenderObjectManager*				m_renderObjectManager;		//!< �����_�����O�I�u�G�W�F�N�g�Ǘ�

	//nk::graphics::Sprite				m_loadIcon;					//!< ���[�h�A�C�R��
	nk::resource::ResourceLoader*		m_resourceLoader;			//!< ���\�[�X���[�h
	nk::graphics::SpriteAnimation*		m_loadingIcon;				//!< ���[�f�B���O�A�C�R��
	
	GameObjectManager					m_gameObjectManager;		//!< �Q�[���I�u�W�F�N�g�Ǘ�

	FlickMoveCamera*					m_flickMoveCamera;			//!< �o�g���p�J����
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			GameMain();
			GameMain(s32 c, char** v);
	virtual~GameMain();
};


}	// namespace game

#endif  // __GAME_MAIN_H__


