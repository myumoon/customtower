//=============================================================================
/*!	@file	titleScene.h

	@brief	�^�C�g���V�[��

	@author	ryunosuke ide
	@date	2013.05.25
*/
//=============================================================================

#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "utility/selector.h"
#include "graphics/graphics.h"


#include "game/scene/sceneInterface.h"

#include "debug/debug.h"
#include "graphics/buttonInputChecker_Mouse.h"

namespace game {


//=============================================================================
/*!
								�^�C�g��
*/
//=============================================================================
class TitleScene : public SceneInterface, public nk::graphics::ButtonEventListener {
public: 
	//-----------------------�^��`--------------------------
	
	//! ���j���[
	enum MENU_ID {
		MENU_ID_NORMAL_BATTLE,		//!< �ʏ�o�g��
		MENU_ID_NETWORK_BATTLE,		//!< �l�b�g���[�N�o�g��
		MENU_ID_MODEL_VIEWER,		//!< ���f���r���[�A�[
		MENU_ID_STAGE_VIEWER,		//!< �X�e�[�W�r���[�A�[
		MENU_ID_MAX,				//!< �ő�
	};

	enum {
		_DEBUG_1,
		_DEBUG_2,
		_DEBUG_3,
	};


	class _DebugListener : public nk::debug::DebugEventListener {
	public:
		virtual void		InputEvent_Left( s32 lineNo, s32& nowNo, char* dispStr, u32 dispStrSize )
		{
			sprintf_s( dispStr, dispStrSize, "lineNo(%d), nowNo(%d)", lineNo, nowNo );
		}
		virtual void		InputEvent_Right( s32 lineNo, s32& nowNo, char* dispStr, u32 dispStrSize )
		{
			sprintf_s( dispStr, dispStrSize, "lineNo(%d), nowNo(%d)", lineNo, nowNo );
		}
		virtual void		InputEvent_Decision( s32 lineNo, s32& nowNo, char* dispStr, u32 dispStrSize )
		{
			sprintf_s( dispStr, dispStrSize, "*lineNo(%d), nowNo(%d)", lineNo, nowNo );
		}
	};
	_DebugListener				m_lisntener;


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
	/*!	@brief		������
	*/
	//===========================================================================
	virtual void	InitializeScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		�I��
	*/
	//===========================================================================
	virtual void	TerminateScene( SceneInterface* parent );
	
protected:
	
	//===========================================================================
	/*!	@brief		�l�b�g�ΐ�
	*/
	//===========================================================================
	virtual void	InitializeNetwork( void );

	//===========================================================================
	/*!	@brief		���j���[���莞�R�[���o�b�N
	*/
	//===========================================================================
	virtual void	CallbackMenuDecide( s32 menuIndex );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	nk::Selector<TitleScene>*		m_menuSelector;		//!< ���j���[�Z���N�^

	// @@@
	nk::graphics::Layout					m_layout;
	nk::graphics::ButtonInputChecker_Mouse*	m_eventChecker;
	//===========================================================================
	/*!	@brief		���ꎞ
	*/
	//===========================================================================
	virtual void	OnCursorOver( nk::graphics::Button* eventButton )
	{
		printf("OnCursorOver\n");
	}

	//===========================================================================
	/*!	@brief		�ޏꎞ
	*/
	//===========================================================================
	virtual void	OnCursorOut( nk::graphics::Button* eventButton )
	{
		printf("OnCursorOut\n");
	}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����J�n��)
	*/
	//===========================================================================
	virtual void	OnCursorDownStart( nk::graphics::Button* eventButton )
	{
		printf("OnCursorDownStart\n");
	}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����I����)
	*/
	//===========================================================================
	virtual void	OnCursorDownEnd( nk::graphics::Button* eventButton )
	{
		printf("OnCursorDownEnd\n");
	}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����J�n��)
	*/
	//===========================================================================
	virtual void	OnCursorUpStart( nk::graphics::Button* eventButton )
	{
		printf("OnCursorUpStart\n");
	}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����I����)
	*/
	//===========================================================================
	virtual void	OnCursorUpEnd( nk::graphics::Button* eventButton )
	{
		printf("OnCursorUpEnd\n");
	}

	//===========================================================================
	/*!	@brief		�z�[���h��
	*/
	//===========================================================================
	virtual void	OnHold( nk::graphics::Button* eventButton )
	{
		printf("OnHold\n");
	}

	// @@@
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			TitleScene();
	virtual~TitleScene();
};
	
}	// namespace game




#endif  // __TITLE_SCENE_H__