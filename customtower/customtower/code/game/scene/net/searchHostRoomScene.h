//=============================================================================
/*!	@file	searchHostScene.h

	@brief	�z�X�g�����V�[��

	@author	ryunosuke ide
	@date	2013.05.26
*/
//=============================================================================

#ifndef __SEARCH_HOST_SCENE_H__
#define __SEARCH_HOST_SCENE_H__





#include "net/socket.h"
#include "thread/thread.h"
#include "utility/selector.h"

#include "game/scene/sceneInterface.h"
#include "network/client/hostFinder.h"

namespace network {
class HostFinder;
}

namespace game {


//=============================================================================
/*!
								�z�X�g����
*/
//=============================================================================
class SearchHostRoomScene : public SceneInterface, public network::HostFinder::SearchResultReceiver {
public:
	//-----------------------�^��`--------------------------
	//! ���j���[
	enum {
		MENU_ID_MAX,
	};
	typedef std::vector<network::HostFinder::HostInfo>	VecHostInfo;	//!< �z�X�g���

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

	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	void			Search( void );

	//===========================================================================
	/*!	@brief		��~
	*/
	//===========================================================================
	void			StopSearch( void )
	{
		m_hostFinder->Close();
	}


protected:
	
	//===========================================================================
	/*!	@brief		�������ʎ擾�R�[���o�b�N
	*/
	//===========================================================================
 	void			CallbackReceivedResult( network::HostFinder::SearchResult& result );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();


	//----------------------�����o�ϐ�-----------------------
	//nk::Selector<SearchHostRoomScene>*	m_menuSelector;			//!< �Z���N�^
 	network::HostFinder*			m_hostFinder;			//!< �z�X�g����
	VecHostInfo						m_hostInfos;			//!< �z�X�g���

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			SearchHostRoomScene();
	virtual~SearchHostRoomScene();
};
	
}	// namespace game






#endif  // __SEARCH_HOST_SCENE_H__