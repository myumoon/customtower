//=============================================================================
/*!	@file	searchHostScene.h

	@brief	ホスト検索シーン

	@author	ryunosuke ide
	@date	2013.05.26
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "searchHostRoomScene.h"

#include "general.h"
#include "game/gameMain.h"
#include "network/client/hostFinder.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace game {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
SearchHostRoomScene::SearchHostRoomScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
SearchHostRoomScene::~SearchHostRoomScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void SearchHostRoomScene::_Init( void )
{
	
 	m_hostFinder			= new network::HostFinder();
 	m_hostFinder->AddReceiver( this );
	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void SearchHostRoomScene::_Term( void )
{
	
}


//===========================================================================
/*!	@brief		初期化
	@param		parent	親
	@return		----
*/
//===========================================================================
void SearchHostRoomScene::InitializeScene( SceneInterface* parent )
{
	RegisterToRenderManager();
}


//===========================================================================
/*!	@brief		終了
	@param		parent	親
	@return		----
*/
//===========================================================================
void SearchHostRoomScene::TerminateScene( SceneInterface* parent )
{
	RemoveFromRenderManager();
}

//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
s32 SearchHostRoomScene::ExecuteLocal( s32 parentMessage )
{

	return MESSAGE_NONE;
}

//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void SearchHostRoomScene::RenderLocal( void )
{

	const s32	lineHeight	= 30;
	const s32	offsetX		= 400;
	const s32	offsetY		= 70;
	const s32	hostInfoNum	= 3;
	
	SystemPrint( offsetX, offsetY, "================= Room Info =================" );
	
	u32 i	= 0;
	for( i = 0; i < m_hostInfos.size(); ++i ) {
		SystemPrint( offsetX, offsetY + (i * hostInfoNum + 1) * lineHeight, "IP Address : %s", m_hostInfos[i].ipAddressStr.ipAddress	);
		SystemPrint( offsetX, offsetY + (i * hostInfoNum + 2) * lineHeight, "Host name  : %s", m_hostInfos[i].hostName					);
		SystemPrint( offsetX, offsetY + (i * hostInfoNum + 3) * lineHeight, "Room name  : %s", m_hostInfos[i].roomName					);
	}
	SystemPrint( offsetX, offsetY + (i * hostInfoNum + 1) * lineHeight, "=============================================" );

	
}

//===========================================================================
/*!	@brief		検索
	@param		----
	@return		----
*/
//===========================================================================
void SearchHostRoomScene::Search( void )
{
	GetGameManager()->StartLoadingIcon();

	bool b = m_hostFinder->Find();
	if( b ) {
		printf("SearchHostRoomScene::ExecuteLocal m_hostFinder->Find() true\n");
	}
	else {
		printf("SearchHostRoomScene::ExecuteLocal m_hostFinder->Find() false\n");
	}
}

//===========================================================================
/*!	@brief		ホスト情報受信時コールバック
	@param		----
	@return		----
*/
//===========================================================================
void SearchHostRoomScene::CallbackReceivedResult( network::HostFinder::SearchResult& result )
{
	GetGameManager()->StopLoadingIcon();
	
	m_hostInfos.clear();
	
	for( u32 i = 0; i < result.GetResultNum(); ++i ) {
		const network::HostFinder::HostInfo*	hostInfo	= result.GetResult( i );

		m_hostInfos.push_back( *hostInfo );
	}

}

	
}	// namespace game
