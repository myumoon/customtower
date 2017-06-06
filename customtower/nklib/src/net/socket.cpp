//=============================================================================
/*!	@file	socket.h

	@brief	�\�P�b�g

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/net/socket.h"

#if defined(_WIN32)
#include <ws2tcpip.h>
#endif

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "../../include/general.h"

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
Socket::Socket()
{
	//m_copyCounter	= 0;
	_Init();
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	id		�\�P�b�g�ԍ�
*/
//===========================================================================
Socket::Socket( SocketID id, SOCKET_TYPE type )
{
	_Init();
	
	m_id			= id;
	m_type			= type;
	m_initialized	= true;
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Socket::~Socket()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Socket::_Init( void )
{
	m_initialized	= false;
	m_type			= SOCKET_TYPE_UNKNOWN;
	m_blocking		= true;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Socket::_Term( void )
{
	
}

	
//===========================================================================
/*!	@brief		�\�P�b�g����
	@param		type	TCP/UDP
	@return		true.����	false.���s
*/
//===========================================================================
bool Socket::_CreateSocket( SOCKET_TYPE type )
{
	if( type == SOCKET_TYPE_TCP ) {
		m_id	= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		//m_id	= socket( AF_INET, SOCK_STREAM, 0 );
	}
	else {
		m_id	= socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
		//m_id	= socket( AF_INET, SOCK_DGRAM, 0 );
	}

	PRINTF("Created socket : id = %u\n", m_id);
		
	return (0 <= m_id);
}

//===========================================================================
/*!	@brief		IP�E�|�[�g�ݒ�
	@param		ipAddress	IP�A�h���X(NULL��INADDR_ANY�w��)
	@param		port		�|�[�g
	@return		----
*/
//===========================================================================
void Socket::_SetAddress( const char* ipAddress, s32 port )
{
	memset( &m_addr, 0, sizeof(m_addr) );
	
	m_addr.sin_family		= AF_INET;
	m_addr.sin_addr.s_addr	= ipAddress ? inet_addr( ipAddress ) : htonl( INADDR_ANY );
	m_addr.sin_port			= port == 0 ? 0 : htons( port );
	
}

	
//===========================================================================
/*!	@brief		����
	@param		ipAddress	IP�A�h���X
	@param		port		�|�[�g
	@param		blocking	�u���b�L���O�ݒ�(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateTCP( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_TCP;
	
	bool	result	= true;
	result	&= _CreateSocket( SOCKET_TYPE_TCP );

	_SetAddress( ipAddress, port );

	_Bind();

	_SetBlocking( blocking );

	//s32		connectResult	= connect( m_id, (struct sockaddr *)&m_addr, sizeof(m_addr) );
	//result	&= (0 <= connectResult);
	
	m_initialized	= result;

	
	return m_initialized;
}



//===========================================================================
/*!	@brief		����
	@param		ipAddress	IP�A�h���X
	@param		port		�|�[�g
	@param		blocking	�u���b�L���O�ݒ�(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateUDP( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_UDP;
	
	bool	result	= true;
	result	&= _CreateSocket( SOCKET_TYPE_UDP );

	_SetAddress( ipAddress, port );

	_Bind();

	_SetBlocking( blocking );

	m_initialized	= result;

	
	return m_initialized;
}



//===========================================================================
/*!	@brief		����
	@param		ipAddress	IP�A�h���X
	@param		port		�|�[�g
	@param		blocking	�u���b�L���O�ݒ�(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateUDP_Broadcast( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_UDP_BROADCAST;
	
	bool	result	= true;
	result	&= _CreateSocket( SOCKET_TYPE_UDP_BROADCAST );

	//_SetAddress( "255.255.255.255", port );
	_SetAddress( ipAddress, port );

	///_Bind();

	int	yes	= 1;	// �I�v�V�����p
	result	&= (0 == setsockopt( m_id, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes) ));

	_SetBlocking( blocking );

	m_initialized	= result;

	
	return m_initialized;
}



//===========================================================================
/*!	@brief		����
	@param		ipAddress	IP�A�h���X
	@param		port		�|�[�g
	@param		blocking	�u���b�L���O�ݒ�(=true)
	@return		----
*/
//===========================================================================
bool Socket::CreateUDP_Multicast( const char* ipAddress, s32 port, bool blocking )
{
	m_type	= SOCKET_TYPE_UDP_MULTICAST;
	
	bool	result	= true;
	
	result	&= _CreateSocket( SOCKET_TYPE_UDP_MULTICAST );

	_SetAddress( ipAddress, port );

	/* �}���`�L���X�g�p */
	sockaddr_in		addrLocal;
	ip_mreq			stMreq;	
	
	addrLocal.sin_family			= AF_INET;
	addrLocal.sin_addr.s_addr		= htonl(INADDR_ANY);
	addrLocal.sin_port				= 0;
	
	bind( m_id, (struct sockaddr*)&addrLocal, sizeof(addrLocal) );
	
	stMreq.imr_multiaddr.s_addr		= m_addr.sin_addr.s_addr;
	stMreq.imr_interface.s_addr		= INADDR_ANY;

	int	ttl	= 32;
	
	setsockopt( m_id, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&stMreq, sizeof(stMreq)	);	// �����o�V�b�v
	setsockopt( m_id, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl)			);	// TTL

	_SetBlocking( blocking );

	m_initialized	= result;

	
	return m_initialized;
}


//===========================================================================
/*!	@brief		����
	@param		----
	@return		----
*/
//===========================================================================
void Socket::Close( void )
{
	if( m_initialized ) {
		PRINTF("Closed socket : %u\n", m_id);
		closesocket( m_id );
	}
	
}


//===========================================================================
/*!	@brief		�\�P�b�gID�擾
	@param		----
*/
//===========================================================================
SocketID Socket::GetID( void ) const
{
	
	return m_id;
}



//===========================================================================
/*!	@brief		�p�P�b�g���M
	@param		packet		���M�p�P�b�g
	@param		packetSize	�p�P�b�g�T�C�Y
	@return		----
*/
//===========================================================================
bool Socket::Send( void* packet, u32 packetSize )
{
	s32	result;
	if( m_type == SOCKET_TYPE_TCP ) {
		result	= send( m_id, (char*)packet, packetSize, 0 );
	}
	else {
		result	= sendto( m_id, (char*)packet, packetSize, 0, (sockaddr*)&m_addr, sizeof(m_addr) );
	}

	return (0 <= result);
}

//===========================================================================
/*!	@brief		�p�P�b�g��M
	@param[out]	packet		��M�p�P�b�g
	@param[in]	packetSize	�p�P�b�g�T�C�Y
	@param[out]	fromAddress	���M�ҏ��(=NULL)
	@return		----
*/
//===========================================================================
SOCKET_RESULT Socket::Receive( void* packet, u32 packetSize, Address* fromAddress )
{
	int	result	= -1;

	
	if( m_type == SOCKET_TYPE_TCP ) {
		if( packet ) {
			result	= recv( GetID(), (char*)packet, packetSize, 0 );
		}
	}
	else {
		if( packet ) {
			sockaddr_in 	fromInfo;
			SocketLength 	fromInfoLen	= sizeof(fromInfo);
			memset( &fromInfo, 0, sizeof(fromInfo) );
			result	= recvfrom( GetID(), (char*)packet, packetSize, 0, (struct sockaddr*)&fromInfo, &fromInfoLen );
			//result	= recvfrom( GetID(), (char*)packet, packetSize, 0, NULL, NULL );

			if( fromAddress ) {
				const char*	addrStr	= inet_ntoa( fromInfo.sin_addr );
				const s32	port	= fromInfo.sin_port;
				fromAddress->SetIpAddress( addrStr, port );
			}
			
		}
	}

	// �G���[
	if( result < 0 ) {
		SOCKET_RESULT	result	= GetLastResult();
		return result;
		//printf("error : Socket::Receive() error code = %d\n", WSAGetLastError() );
		//return false;
	}

	return SOCKET_RESULT_OK;
}

//===========================================================================
/*!	@brief		�o�C���h
	@param		----
	@return		----
*/
//===========================================================================
void Socket::Bind( void )
{
	_Bind();
}


//===========================================================================
/*!	@brief		���X��
	@param		backlog		�o�b�N���O��
	@return		----
*/
//===========================================================================
void Socket::Listen( s32 backlog )
{
	_Listen( backlog );
}


//===========================================================================
/*!	@brief		�ڑ��v��
	@param		----
	@return		----
*/
//===========================================================================
bool Socket::Connect( void )
{
	const bool	result	= _Connect();
	
	return result;
}


//===========================================================================
/*!	@brief		�o�C���h
	@param		----
	@return		----
*/
//===========================================================================
void Socket::_Bind( void )
{

	bind( m_id, (sockaddr*)&m_addr, sizeof(m_addr) );
	
}

//===========================================================================
/*!	@brief		���X��
	@param		backlog		�o�b�N���O�L���[
	@return		----
*/
//===========================================================================
void Socket::_Listen( s32 backlog )
{

	listen( m_id, backlog );
	
}

//===========================================================================
/*!	@brief		�ڑ�
	@param		----
	@return		----
*/
//===========================================================================
bool Socket::_Connect( void )
{
	s32	result	= connect( m_id, (struct sockaddr*)&m_addr, sizeof(m_addr) );

	return (0 <= result);
}


//===========================================================================
/*!	@brief		�u���b�L���O�ݒ�
	@param		block	true.�u���b�N	false.�m���u���b�N
	@return		----
*/
//===========================================================================
void Socket::SetBlocking( bool block )
{
	_SetBlocking( block );
	
}



//===========================================================================
/*!	@brief		�u���b�L���O�ݒ�
	@param		block	true.�u���b�N	false.�m���u���b�N
	@return		----
*/
//===========================================================================
void Socket::_SetBlocking( bool block )
{
	m_blocking	= block;
	
#if defined(_WIN32)
	u_long		val	= block ? 0 : 1;
	ioctlsocket( GetID(), FIONBIO, &val );

#else
	int		val	= block ? 0 : 1;
	ioctl( GetID(), FIONBIO, &val );
	
#endif
	
}


//===========================================================================
/*!	@brief		�u���b�L���O�ݒ�擾
	@param		----
	@return		----
*/
//===========================================================================
bool Socket::IsBlocking( void ) const
{
	
	return m_blocking;
}


}	// namespace net
	
}	// namespace nk
