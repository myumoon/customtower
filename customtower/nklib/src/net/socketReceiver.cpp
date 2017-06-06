//=============================================================================
/*!	@file	socketReceiver.h

	@brief	���V�[�o�[

	@author	ryunosuke ide
	@date	2013.05.17
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/net/socketReceiver.h"
#include "../../include/utility/utility.h"
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
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
SocketReceiver::SocketReceiver()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
SocketReceiver::~SocketReceiver()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void SocketReceiver::_Init( void )
{
	m_maxID	= 0;

	FD_ZERO( &m_fd );
	memset( &m_timeout, 0, sizeof(m_timeout) );

	m_vecSocketInfo.clear();
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void SocketReceiver::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		----
	@return		----
*/
//===========================================================================
void SocketReceiver::Init( void )
{
	_Init();
}


//===========================================================================
/*!	@brief		��M�m�F
	@param		----
	@return		----
*/
//===========================================================================
bool SocketReceiver::ReceiveWait( void )
{
	fd_set	fds;	// �`�F�b�N�p
	memcpy( &fds, &m_fd, sizeof(m_fd) );
	
	s32	lasttime = 0;
	{
		if( (m_timeout.tv_sec == 0) && (m_timeout.tv_usec == 0) ) {
			lasttime	= select( m_maxID + 1, &fds, NULL, NULL, NULL );
		}
		else {
			lasttime	= select( m_maxID + 1, &fds, NULL, NULL, &m_timeout );
		}
	}

	// �^�C���A�E�g
	if( lasttime == 0 ) {
		return false;
	}

	{		
		for( u32 i = 0; i < m_vecSocketInfo.size(); ++i ) {
			if( FD_ISSET( m_vecSocketInfo[i].socket.GetID(), &fds ) ) {
								
				void*	buffer		= m_vecSocketInfo[i].receiver->GetBuffer();
				u32		bufferSize	= m_vecSocketInfo[i].receiver->GetBufferSize();
				
				memset( buffer, 0, bufferSize );
				Address		senderAddr;
				const SOCKET_RESULT	result	= m_vecSocketInfo[i].socket.Receive( buffer, bufferSize, &senderAddr );
				if( (result != SOCKET_RESULT_OK) && (result != SOCKET_RESULT_NONBLOCKING_WAIT) ) {
					printf("error : %d\n", WSAGetLastError());
				}
				m_vecSocketInfo[i].receiver->ReceiveCallback( m_vecSocketInfo[i].socket, buffer, bufferSize, senderAddr );
			}
		}
	}

	return true;
}

//===========================================================================
/*!	@brief		�ǉ�
	@param		socket		�\�P�b�g
	@param		receiver	��M�N���X
	@return		----
*/
//===========================================================================
void SocketReceiver::AddReceiveScoket( const Socket& socket, PacketReceiver* receiver )
{
	
	FD_SET( socket.GetID(), &m_fd );

	m_vecSocketInfo.push_back( SocketInfo( socket, receiver) );
	//m_receivers.insert( std::pair<Socket::SocketID, PacketReceiver*>( socket.GetID(), receiver ) );

	if( m_maxID < socket.GetID() ) {
		m_maxID	= socket.GetID();
	}
}

//===========================================================================
/*!	@brief		�^�C���A�E�g�ݒ�
	@param		sec		�b 
	@param		micSec	�}�C�N���b
	@return		----
*/
//===========================================================================
void SocketReceiver::SetTimeout( s32 sec, s32 micSec )
{
	
	m_timeout.tv_sec	= sec;
	m_timeout.tv_usec	= micSec;

}


//===========================================================================
/*!	@brief		�N���A
	@param		----
	@return		----
*/
//===========================================================================
void SocketReceiver::Clear( void )
{
	_Init();
}

}	// namespace net
}	// namespace nk