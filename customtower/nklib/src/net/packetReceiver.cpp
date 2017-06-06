//=============================================================================
/*!	@file	packetReceiver.h

	@brief	�p�P�b�g���V�[�o

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/net/packetReceiver.h"
#include "../../include/net/socket.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace nk {

namespace net {


//===========================================================================
/*!	@brief		�R���X�g���N�^
*/
//===========================================================================
PacketReceiver::PacketReceiver( void )
{
	m_received		= false;
	m_ipAddress		= 0;
	m_ipAddressStr	= "";
	
}

//===========================================================================
/*!	@brief		�f�X�g���N�^
*/
//===========================================================================
PacketReceiver::~PacketReceiver( void )
{
	
}


//===========================================================================
/*!	@brief		��M���R�[���o�b�N
	@param		receiveSocket	��M�\�P�b�g
	@param		packet			��M�p�P�b�g
	@param		packetSize		�p�P�b�g�T�C�Y
	@param		
	@return		----
*/
//===========================================================================
void PacketReceiver::ReceiveCallback( Socket receiveSocket, void* packet, u32 packetSize, Address senderAddr )
{
	// ��M�m�F�p�P�b�g���M
	{
		//ReceiveCheckPacket	returnPacket;
		//receiveSocket.Send( &returnPacket, sizeof(returnPacket) );
	}
	
	// ��M�R�[���o�b�N
	{
		m_ipAddressStr	= senderAddr.ipAddress;
		IPAddressStrToIPAddress( &m_ipAddress, m_ipAddressStr );
		m_received	= true;
		
		Receive( packet, packetSize );		
	}
}	


//===========================================================================
/*!	@brief		���M��IP�A�h���X���擾
	@param		----
	@return		----
*/
//===========================================================================
IPAddress PacketReceiver::GetIPAddress( void ) const
{

	return m_ipAddress;
}


//===========================================================================
/*!	@brief		���M��IP�A�h���X���擾
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
/*!	@brief		��M�����Ȃ�true��Ԃ�
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

