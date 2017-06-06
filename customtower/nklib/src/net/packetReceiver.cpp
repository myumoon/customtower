//=============================================================================
/*!	@file	packetReceiver.h

	@brief	パケットレシーバ

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/net/packetReceiver.h"
#include "../../include/net/socket.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace nk {

namespace net {


//===========================================================================
/*!	@brief		コンストラクタ
*/
//===========================================================================
PacketReceiver::PacketReceiver( void )
{
	m_received		= false;
	m_ipAddress		= 0;
	m_ipAddressStr	= "";
	
}

//===========================================================================
/*!	@brief		デストラクタ
*/
//===========================================================================
PacketReceiver::~PacketReceiver( void )
{
	
}


//===========================================================================
/*!	@brief		受信時コールバック
	@param		receiveSocket	受信ソケット
	@param		packet			受信パケット
	@param		packetSize		パケットサイズ
	@param		
	@return		----
*/
//===========================================================================
void PacketReceiver::ReceiveCallback( Socket receiveSocket, void* packet, u32 packetSize, Address senderAddr )
{
	// 受信確認パケット送信
	{
		//ReceiveCheckPacket	returnPacket;
		//receiveSocket.Send( &returnPacket, sizeof(returnPacket) );
	}
	
	// 受信コールバック
	{
		m_ipAddressStr	= senderAddr.ipAddress;
		IPAddressStrToIPAddress( &m_ipAddress, m_ipAddressStr );
		m_received	= true;
		
		Receive( packet, packetSize );		
	}
}	


//===========================================================================
/*!	@brief		送信者IPアドレスを取得
	@param		----
	@return		----
*/
//===========================================================================
IPAddress PacketReceiver::GetIPAddress( void ) const
{

	return m_ipAddress;
}


//===========================================================================
/*!	@brief		送信者IPアドレスを取得
	@param		----
	@return		----
*/
//===========================================================================
void PacketReceiver::GetIPAddressStr( IPAddressStr* outIpAddress ) const
{
	//memset( *outIpAddress, 0, sizeof(m_ipAddressStr) );
	//strncpy( *outIpAddress, m_ipAddressStr, sizeof(m_ipAddressStr) );
	*outIpAddress	= m_ipAddressStr;
	
}

//===========================================================================
/*!	@brief		受信したならtrueを返す
	@param		----
	@return		----
*/
//===========================================================================
bool PacketReceiver::IsReceived( void ) const
{

	return m_received;
}


}	// namespace net
	
}	// namespace nk

