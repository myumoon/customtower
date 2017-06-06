//=============================================================================
/*!	@file	drawPacketManager.h

	@brief	描画パケット管理

	@author	ryunosuke ide
	@date	2013.06.22
	
	@note	drawPacketの生成を行うとVertexやFaceの生成に時間がかかるので
			ゲーム初期化時に一気に初期化しておく。
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/render/drawPacketManager.h"
#include "../../include/render/renderManager.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {
namespace graphics {

	
//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
DrawPacketManager::DrawPacketManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
DrawPacketManager::~DrawPacketManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void DrawPacketManager::_Init( void )
{
	m_renderManager	= NULL;
	m_usablePacket	= 0;
	m_packetsSize	= 0;
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
#else
	m_packets	= NULL;
#endif
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void DrawPacketManager::_Term( void )
{
	Terminate();
}


//===========================================================================
/*!	@brief		初期化
	@param		maxPacket	最大パケット数
	@return		----
*/
//===========================================================================
void DrawPacketManager::Initialize( u32 maxPacket )
{	
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	m_packets.resize( maxPacket );
	m_packetsSize	= m_packets.size();
#else
	if( m_packets == NULL ) {
		m_packets		= new DrawPacket[maxPacket];
		m_packetsSize	= maxPacket;
	}
#if defined(_DEBUG)
	else {
		PRINTF("DrawPacketManager::Initialize : already initialized.\n");
	}
#endif	// #if defined(_DEBUG)
#endif	// #if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	
}

//===========================================================================
/*!	@brief		終了
	@param		----
	@return		----
*/
//===========================================================================
void DrawPacketManager::Terminate( void )
{
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	m_packets.clear();
#else
	SafeDeleteArray( m_packets );
#endif
}


//===========================================================================
/*!	@brief		使用可能パケット番号を初期化
	@param		----
	@return		----
*/
//===========================================================================
void DrawPacketManager::ChangeStateDisuseAllPacket( void )
{
	// 取り出す場所を変えるだけ
	m_usablePacket	= 0;
}


//===========================================================================
/*!	@brief		使用可能パケットを取得
	@param		----
	@return		----
*/
//===========================================================================
DrawPacket& DrawPacketManager::PopDrawPacket( void )
{
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	if( m_packets.size() <= m_usablePacket ) {
		m_packets.resize( m_packets.size() * 2 );
	}
	
	DrawPacket&	retPacket	= m_packets.at( m_usablePacket );
#else
	if( m_packetsSize <= m_usablePacket ) {
		ASSERT( false, "packet buffer over." );
	}
	
	DrawPacket&	retPacket	= m_packets[m_usablePacket];
#endif
	
	retPacket.Clear();
	
	++m_usablePacket;
	
	return retPacket;
}


//===========================================================================
/*!	@brief		描画マネージャーに送信
	@param		packet	送信パケット
	@return		----
*/
//===========================================================================
void DrawPacketManager::SendToDrawManager( const DrawPacket& packet )
{
	const DrawPacket*	sendPacket	= NULL;

#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	{
		// Popされたパケットならアドレスを送る
		for( u32 i = 0; i < m_packets.size(); ++i ) {
			if( &packet == &m_packets[i] ) {
				sendPacket	= &m_packets[i];
				break;
			}
		}
	}
#else
	{
		// 配列範囲内
		if( (&m_packets[0] <= &packet) && (&packet <= &m_packets[m_packetsSize - 1]) ) {
// 			sendPacket	= const_cast<DrawPacket*>(&packet);
			sendPacket	= &packet;
		}
	}
#endif

	// 未登録のパケットなら登録
	if( sendPacket == NULL ) {
		DrawPacket&	popPacket	= PopDrawPacket();
		popPacket				= packet;
		sendPacket				= &popPacket;
	}

	// 送信
	m_renderManager->Add( sendPacket );
}

}	// namespace graphics
}	// namespace nk