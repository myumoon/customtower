//=============================================================================
/*!	@file	hostRoomScene.h
	@brief	�ڑ��ҋ@����

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "hostRoomScene.h"

#include "general.h"
#include "game/gameMain.h"
#include "network/server/joinClientChecker.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

namespace game {

HostRoomScene*	HostRoomScene::_hostRoomScene	= NULL;
}

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace game {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
HostRoomScene::HostRoomScene()
{
	_hostRoomScene	= this;
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
HostRoomScene::~HostRoomScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void HostRoomScene::_Init( void )
{

	m_menuSelector	= new nk::Selector<HostRoomScene>( this );
	m_menuSelector->Setup<nk::UpdateRepeat>(
		MENU_ID_MAX,
		GetGameManager()->GetKeyboard(),
		nk::input::Keyboard::KEY_UP,
		nk::input::Keyboard::KEY_DOWN,
		nk::input::Keyboard::KEY_ENTER
	);
	m_menuSelector->SetDecideCallback( &game::HostRoomScene::CallbackMenuDecide );
	

	m_joinClientChecker		= new network::JoinClientChecker();
	m_joinClientChecker->m_callbackReceive	= CallbackClientAccess;
	
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void HostRoomScene::_Term( void )
{
	nk::SafeDelete( m_menuSelector );
	
}


//===========================================================================
/*!	@brief		������
	@param		parent	�e
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeScene( SceneInterface* parent )
{
	m_accessIPAddress.clear();
	m_accessIPAddress.reserve( 128 );

	RegisterToRenderManager();
}


//===========================================================================
/*!	@brief		�I��
	@param		parent	�e
	@return		----
*/
//===========================================================================
void HostRoomScene::TerminateScene( SceneInterface* parent )
{
	RemoveFromRenderManager();
}

//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
s32 HostRoomScene::ExecuteLocal( s32 parentMessage )
{
	m_menuSelector->Update();


	return MESSAGE_NONE;
}

//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void HostRoomScene::RenderLocal( void )
{
	SystemPrint( 0, 0, "HostRoom" );

	
	const char*	menuTbl[]	= {
		"Create Room",
		"Delete Room",
		"Return",
	};

	{
		const s32	offsetX		= 200;
		const s32	offsetY		= 300;
		const s32	lineHeight	= 30;
		for( s32 i = 0; i < MENU_ID_MAX; ++i ) {
			SystemPrint( offsetX, offsetY + i * lineHeight, "%s", menuTbl[i] );
		}
		SystemPrint( offsetX - 20, offsetY + m_menuSelector->GetSelectNo() * lineHeight, ">" );
	}

	{
		const s32	lineHeight	= 30;
		const s32	offsetX		= 400;
		const s32	offsetY		= 70;
		const s32	hostInfoNum	= 1;
		
		SystemPrint( offsetX, offsetY, "================= Access IP =================" );

		nk::net::IPAddressStr	str;
		u32 i	= 0;
		for( i = 0; i < m_accessIPAddress.size(); ++i ) {
			nk::net::IPAddressToIPAddressStr( &str, m_accessIPAddress[i] );
			SystemPrint( offsetX, offsetY + (i + 1) * lineHeight, "IP Address : %s", str.ipAddress	);
		}
		SystemPrint( offsetX, offsetY + lineHeight * (m_accessIPAddress.size() + hostInfoNum) + lineHeight * 1, "=============================================" );
	}

}



//===========================================================================
/*!	@brief		���j���[���莞�R�[���o�b�N
	@param		menuIndex	���j���[�C���f�b�N�X
	@return		----
*/
//===========================================================================
void HostRoomScene::CallbackMenuDecide( s32 menuIndex )
{
	if( menuIndex == MENU_ID_CREATE_ROOM ) {
		InitializeCreateRoom();
	}
	else if( menuIndex == MENU_ID_DELETE_ROOM ) {
		InitializeDeleteRoom();
	}
	else if( menuIndex == MENU_ID_RETURN ) {
		InitializeReturn();
	}
}

//===========================================================================
/*!	@brief		�����쐬
	@param		----
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeCreateRoom( void )
{
	bool b = m_joinClientChecker->Setup();
	if( b ) {
		GetGameManager()->StartLoadingIcon();
		printf("HostRoomScene::ExecuteLocal m_joinClientChecker->CheckReceive() true\n");
	}
	else {
		printf("HostRoomScene::ExecuteLocal m_joinClientChecker->CheckReceive() false\n");
	}
}


//===========================================================================
/*!	@brief		�����폜
	@param		----
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeDeleteRoom( void )
{
	GetGameManager()->StopLoadingIcon();
	
	m_joinClientChecker->Close();
}


//===========================================================================
/*!	@brief		�߂�
	@param		----
	@return		----
*/
//===========================================================================
void HostRoomScene::InitializeReturn( void )
{
	GetGameManager()->StopLoadingIcon();
	
	m_joinClientChecker->Close();
	GetGameManager()->SetNextScene( SceneManager::SCENE_ID_NETWORK );
}

	
}	// namespace game
