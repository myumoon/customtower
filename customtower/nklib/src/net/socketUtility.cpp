//=============================================================================
/*!	@file	socketUtility.h

	@brief	�\�P�b�g

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <winsock2.h>
#include <iphlpapi.h>
#include "../../include/net/socketUtility.h"
#include "../../include/general.h"

#pragma warning(disable:4996)	// strncpy�x��

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {


//===========================================================================
/*!	@brief		WSA�G���[����SOCKET_RESULT�ɕϊ�
	@param		wsaError	WSAE
	@return		SOCKET_RESULT
*/
//===========================================================================
nk::net::SOCKET_RESULT _WSAEToSocketResult( u32 wsaError )
{
	using namespace nk::net;

#if defined(_WIN32)
	switch( wsaError ) {
		case WSAEWOULDBLOCK	:	{ return SOCKET_RESULT_NONBLOCKING_WAIT;		} break;	// �m���u�b�L���O�҂�
		case WSAEINVAL		:	{ return SOCKET_RESULT_INVALID_ARGS;			} break;	// �����Ȉ���
		case WSAEALREADY 	:	{ return SOCKET_RESULT_ALREADY;					} break;	// ���ɏ�����
		
		default :				{ return SOCKET_RESULT_UNKNOW_ERROR;			} break;
	}
#else
	return SOCKET_RESULT_OK;
#endif
}
	
//===========================================================================
/*!	@brief		errno����SOCKET_RESULT�ɕϊ�
	@param		errNo	errNo�̒l
	@return		SOCKET_RESULT
*/
//===========================================================================
nk::net::SOCKET_RESULT _ErrorNumToSocketResult( u32 errNo )
{
	using namespace nk::net;
#if !defined(_WIN32)
	switch( errNo ) {
		case EAGAIN			:	{ return SOCKET_RESULT_NONBLOCKING_WAIT;		} break;	// �m���u�b�L���O�҂�
		case EINVAL			:	{ return SOCKET_RESULT_INVALID_ARGS;			} break;	// �����Ȉ���
		case EALREADY		:	{ return SOCKET_RESULT_ALREADY;					} break;	// ���ɏ�����
		
		default :				{ return SOCKET_RESULT_UNKNOW_ERROR;			} break;
	}

#else
	return SOCKET_RESULT_OK;
#endif

}

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {

namespace net {

//===========================================================================
/*!	@brief		�A�h���X������
	@param		----
	@return		----
*/
//===========================================================================
void Address::Init( void )
{
	this->port	= 0;
	//memset( this->ipAddress, 0, sizeof(this->ipAddress) );
}

//===========================================================================
/*!	@brief		�A�h���X�ݒ�
	@param		----
	@return		----
*/
//===========================================================================
void Address::SetIpAddress( const char* ipAddress, u32 port )
{
	Init();
	//strncpy( this->ipAddress, ipAddress, sizeof(this->ipAddress) );
	this->ipAddress	= ipAddress;
	this->port		= port;
}


//===========================================================================
/*!	@brief		�\�P�b�g�̐���
*/
//===========================================================================
s32 CreateSocket( SOCKET_TYPE type )
{
	s32	sock	= 0;
	
	if( type == SOCKET_TYPE_TCP ) {
		sock = socket( AF_INET, SOCK_STREAM, IPPROTO_IP );
	}
	else {
		sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_IP );
	}

	return sock;
}


//===========================================================================
/*!	@brief		�\�P�b�g�̃N���[�Y
*/
//===========================================================================
void CloseSocket( SocketID socket )
{
#if defined(_WIN32)
	closesocket( socket );
#else
	close( socket );
#endif
	
}


//===========================================================================
/*!	@brief		�ڑ�
	@param		socket		�\�P�b�g
	@param		addr		����A�h���X
	@param		addrSize	addr�̃T�C�Y
	@return		�ڑ�����
*/
//===========================================================================
s32 ConnectSocket( SocketID socket, struct sockaddr* addr, SocketLength addrSize )
{
	s32	result	= connect( socket, addr, addrSize );

	return result;
}


//===========================================================================
/*!	@brief		�z�X�gIP��"255.255.255.255"�`���Ŏ擾
	@param[out]	hostIP		IP�A�h���X������()
*/
//===========================================================================
void GetLocalHost( IPAddressStr* hostIP )
{
	//NULL_ASSERT( *hostIP );
	
	int socket = CreateSocket( SOCKET_TYPE_UDP );
	
	if( socket < 0 ) {
		return;
	}

	// �R�l�N�V�������m���i���悤�Ɓj���邽�߂̃_�~�[�� IP �A�h���X
	const char*	connectIP	= "192.0.2.4";	// �g�p����Ă��Ȃ�IP�A�h���X(�����l)
#if defined(_WIN32)
	struct sockaddr_in dummy;
	{
		dummy.sin_addr.s_addr = inet_addr( connectIP );	
		
		// �G���[
		if( dummy.sin_addr.s_addr == INADDR_NONE ) {
			return;
		}
	}
#else
	struct in_addr	dummy;
	{		
		int	result	= inet_aton( connectIP, &dummy );

		// �G���[
		if( result == 0 ) {
			return;
		}
	}
#endif

	struct sockaddr_in exaddr = { 0 };
	memset( &exaddr, 0, sizeof(exaddr) );
	exaddr.sin_family = AF_INET;
	memcpy( (char*)&exaddr.sin_addr, &dummy, sizeof(dummy) );

	s32	connectResult	= ConnectSocket( socket, (struct sockaddr*)&exaddr, sizeof(exaddr) );
	if( connectResult < 0 ) {
		CloseSocket( socket );
		
		return;
	}

	struct sockaddr_in	addr	= { 0 };
	s32					len		= sizeof(addr);
	s32					status	= getsockname( socket, (struct sockaddr*)&addr, &len );
	if( 0 <= status ) {
		const char*	ipStr = inet_ntoa( addr.sin_addr );
		//strncpy( *hostIP, ipStr, sizeof(IPAddressStr) );
		*hostIP	= ipStr;
	}
	
	CloseSocket( socket );
	
}

//===========================================================================
/*!	@brief		�A�_�v�^�����擾
*/
//===========================================================================
bool	GetAdapterInfo( AdapterInfo* outAdapterInfo, s32 adapterNo )
{
	bool	result	= false;
	
	if( outAdapterInfo == NULL ) {
		return false;
	}

#if defined(_WIN32)
    IP_ADAPTER_INFO		adapterInfo;
    PIP_ADAPTER_INFO	pAdapterInfo	= &adapterInfo;
    ULONG				ulOutBufLen		= sizeof(IP_ADAPTER_INFO);
    DWORD				dwRetVal;
	bool				isMalloc		= false;
	s32					idx				= 0;

    /* Make an initial call to GetAdaptersInfo to get
       The necessary size into the ulOutBufLen variable */
    if( (dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == ERROR_BUFFER_OVERFLOW ) {
    	isMalloc		= true;
		pAdapterInfo	= (PIP_ADAPTER_INFO)malloc( ulOutBufLen );
		dwRetVal		= GetAdaptersInfo( pAdapterInfo, &ulOutBufLen );
    }

    if( dwRetVal == NO_ERROR ) {
		PIP_ADAPTER_INFO	pAdapter;

		for( pAdapter = pAdapterInfo; pAdapter; pAdapter = pAdapter->Next ) {

			/* XXX take care of only the first IP address */
// 			printf("address: %s\n", pAdapter->IpAddressList.IpAddress.String);
// 			printf("netmask: %s\n", pAdapter->IpAddressList.IpMask.String);
// 			printf("adapter name: %s\n", pAdapter->AdapterName);
// 			printf("adapter description: %s\n", pAdapter->Description);
// 			
// 			{
// 				char *physic = (char*)malloc(3 * pAdapter->AddressLength);
// 				char *pt = physic;
// 				UINT i;
// 				sprintf(pt, "%02X", pAdapter->Address[0]);
// 				pt += 2;
// 				for (i = 1; i < pAdapter->AddressLength; i++) {
// 					sprintf(pt, "-%02X", pAdapter->Address[i]);
// 					pt += 3;
// 				}
// 				printf( "physical address: %s\n", physic );
// 				free( physic );
// 			}

			if( idx == adapterNo ) {
				result	= true;

				// �����A�h���X�擾
				const u32	physicAddressLength	= 3 * pAdapter->AddressLength;
				char*	physic	= new char[ physicAddressLength ];
				memset( physic, 0, physicAddressLength );
				{					
					char*	pt		= physic;
					
					sprintf( pt, "%02X", pAdapter->Address[0] );
					pt += 2;
					for( u32 i = 1; i < pAdapter->AddressLength; ++i ) {
						sprintf( pt, "-%02X", pAdapter->Address[i] );
						pt += 3;
					}
					
				}

				// IP, �T�u�l�b�g�}�X�N
				//strncpy( outAdapterInfo->ipAddress,		pAdapter->IpAddressList.IpAddress.String,	sizeof(IPAddressStr)	);
				//strncpy( outAdapterInfo->subnetMask,	pAdapter->IpAddressList.IpMask.String,		sizeof(IPAddressStr)	);
				outAdapterInfo->ipAddress	= pAdapter->IpAddressList.IpAddress.String;
				outAdapterInfo->subnetMask	= pAdapter->IpAddressList.IpMask.String;

				// �����A�h���X
				strncpy( outAdapterInfo->physicalAddress,	physic, ARRAY_SIZE(outAdapterInfo->physicalAddress)			);
				
				SafeDeleteArray( physic );
				
				break;
			}
			++idx;
		}
    }
	
	if( isMalloc ) {
		free( pAdapterInfo );
	}
	
#else
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	/* IPv4�̃l�b�g�}�X�N���擾������ */
	ifr.ifr_addr.sa_family = AF_INET;

	/* eth0�̃l�b�g�}�X�N���擾������ */
	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

	ioctl(fd, SIOCGIFNETMASK, &ifr);

	close(fd);

	/* ���ʂ�\�� */
	printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
#endif
	
	return result;
}
	

//===========================================================================
/*!	@brief		"255.255.255.255" -> FFFFFFFF
*/
//===========================================================================
void IPAddressStrToIPAddress( IPAddress* outIpAddress, IPAddressStr ipAddress )
{
	NULL_ASSERT( outIpAddress );
	if( outIpAddress == NULL ) {
		return;
	}
	u32		octet[4]	= { 0 };
	
	sscanf_s( ipAddress.ipAddress, "%d.%d.%d.%d", &octet[0], &octet[1], &octet[2], &octet[3] );

	u32		final	= (octet[0] << 24) | (octet[1] << 16) | (octet[2] << 8) | (octet[3] << 0);

	*outIpAddress	= final;
	
}

	
//===========================================================================
/*!	@brief		FFFFFFFF -> "255.255.255.255"
*/
//===========================================================================
void IPAddressToIPAddressStr( IPAddressStr* outIpAddress, IPAddress ipAddress )
{
	NULL_ASSERT( outIpAddress );
	if( outIpAddress == NULL ) {
		return;
	}
	
	//const char*	ip	= inet_ntoa( addr.sin_addr );

	//const u32	mask	= 0xFF;
	u32		octet[4]	= { 0 };
	octet[0]	= (ipAddress & 0xFF000000) >> 24;
	octet[1]	= (ipAddress & 0x00FF0000) >> 16;
	octet[2]	= (ipAddress & 0x0000FF00) >> 8;
	octet[3]	= (ipAddress & 0x000000FF) >> 0;

	sprintf_s( outIpAddress->ipAddress, sizeof(outIpAddress->ipAddress), "%d.%d.%d.%d", octet[0], octet[1], octet[2], octet[3] );
	
}

//===========================================================================
/*!	@brief		�u���[�h�L���X�g�A�h���X���擾
	@param[out]	outIpAddress	�u���[�h�L���X�g�A�h���X
	@param[in]	adapterNo		�A�_�v�^�ԍ�
*/
//===========================================================================
bool GetBroadcastAddressStr( IPAddressStr* outIpAddress, s32 adapterNo )
{
	NULL_ASSERT( outIpAddress );
	
	if( outIpAddress == NULL ) {
		return false;
	}

	AdapterInfo	adapterInfo;
	const bool	result	= GetAdapterInfo( &adapterInfo, adapterNo );
	if( result == false ) {
		return false;
	}

	IPAddress	ipAddress;
	IPAddressStrToIPAddress( &ipAddress, adapterInfo.ipAddress );
	
	IPAddress	subnetMask;	
	IPAddressStrToIPAddress( &subnetMask, adapterInfo.subnetMask );

	IPAddressToIPAddressStr( outIpAddress, ipAddress | ~subnetMask );
	
	return true;
}


//===========================================================================
/*!	@brief		���ʎ擾
	@param		----
	@return		SOCKET_RESULT ����
*/
//===========================================================================
SOCKET_RESULT GetLastResult( void )
{
	SOCKET_RESULT	retResult	= SOCKET_RESULT_OK;
	
#if defined(_WIN32)
	retResult	= _WSAEToSocketResult( WSAGetLastError() );
#else
	retResult	= _ErrorNumToSocketResult( errno );	// errno�̓O���[�o��
#endif
	
	return retResult;
}

	
}	// namespace net
	
}	// namespace nk


