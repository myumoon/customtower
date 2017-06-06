//=============================================================================
/*!	@file	hostRoomScene.h
	@brief	�ڑ��ҋ@����

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

#ifndef __HOST_ROOM_SCENE_H__
#define __HOST_ROOM_SCENE_H__

#include "net/socket.h"
#include "thread/thread.h"
#include "utility/selector.h"

#include "game/scene/sceneInterface.h"

namespace network {
class JoinClientChecker;
}

namespace game {


//=============================================================================
/*!
								�z�X�g����
*/
//=============================================================================
class HostRoomScene : public SceneInterface {
public:
	//-----------------------�^��`--------------------------
	//! ���j���[
	enum {
		MENU_ID_CREATE_ROOM,	//!< �����쐬
		MENU_ID_DELETE_ROOM,	//!< �����폜
		MENU_ID_RETURN,			//!< �߂�
		MENU_ID_MAX,
	};

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
	/*!	@brief		���j���[���莞�R�[���o�b�N
	*/
	//===========================================================================
	virtual void	CallbackMenuDecide( s32 menuIndex );
	
	//===========================================================================
	/*!	@brief		�����쐬
	*/
	//===========================================================================
	virtual void	InitializeCreateRoom( void );

	//===========================================================================
	/*!	@brief		�����쐬
	*/
	//===========================================================================
	virtual void	InitializeDeleteRoom( void );	

	//===========================================================================
	/*!	@brief		�߂�
	*/
	//===========================================================================
	virtual void	InitializeReturn( void );

	static HostRoomScene*	_hostRoomScene;
	static void		CallbackClientAccess( nk::net::IPAddress ip )
	{
		_hostRoomScene->CallbackAccess( ip );
	}
	void CallbackAccess( nk::net::IPAddress ip )
	{
		m_accessIPAddress.push_back( ip );
	}
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();


	//----------------------�����o�ϐ�-----------------------
	nk::Selector<HostRoomScene>*	m_menuSelector;			//!< �Z���N�^
	network::JoinClientChecker*		m_joinClientChecker;	//!< �ڑ��v���m�F

	std::vector<nk::net::IPAddress>	m_accessIPAddress;		//!< ��MIP�A�h���X

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			HostRoomScene();
	virtual~HostRoomScene();
};
	
}	// namespace game



#endif  // __HOST_ROOM_SCENE_H__
