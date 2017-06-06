//=============================================================================
/*!	@file	socketUtility.h

	@brief	�\�P�b�g

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================

#ifndef __SOCKET_UTILITY_H__
#define __SOCKET_UTILITY_H__

#if defined(_WIN32)
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif	// defined(_WIN32)

#include <stdio.h>
#include <string.h>

namespace nk {

namespace net {
	

#if defined(_WIN32)
typedef SOCKET			SocketID;
typedef	int				SocketLength;
#else
typedef int				SocketID;
typedef	socklen_t		SocketLength;
#endif
//typedef char			IPAddressStr[32];	//!< "255.255.255.255"�`����IP�A�h���X�i�[�p
struct IPAddressStr {
	char	ipAddress[32];
	
	IPAddressStr() {
		memset( ipAddress, 0, sizeof(ipAddress) );
	}
	IPAddressStr( const char* str ) {
		strcpy_s( ipAddress, sizeof(ipAddress), str );
	}
	IPAddressStr operator=( const char* rhs ) {
		strcpy_s( ipAddress, sizeof(ipAddress), rhs );
		return *this;
	}
	IPAddressStr operator=( const IPAddressStr& rhs ) {
		strcpy_s( ipAddress, sizeof(ipAddress), rhs.ipAddress );
		return *this;
	}	
};

//typedef unsigned char	IPAddress[4];		//!< IP�A�h���X�i�[
typedef u32				IPAddress;			//!< IP�A�h���X�i�[


//! �\�P�b�g�̎��
enum SOCKET_TYPE {
	SOCKET_TYPE_TCP,
	SOCKET_TYPE_UDP,
};

//! �\�P�b�g��������
enum SOCKET_RESULT {
	// OK
	SOCKET_RESULT_OK,						//!< �G���[����

	// �ҋ@
	SOCKET_RESULT_NONBLOCKING_WAIT,			//!< �m���u���b�N��M�ҋ@��

	// �G���[
	SOCKET_RESULT_INVALID_ARGS,				//!< �����Ȉ���
	SOCKET_RESULT_ALREADY,					//!< ���ɏ�����

	// ����
	SOCKET_RESULT_UNKNOW_ERROR,				//!< �G���[
};

//=============================================================================
/*!
							����M�A�h���X
*/
//=============================================================================
struct Address {
	IPAddressStr	ipAddress;		//!< IP�A�h���X
	//IPAddress		ipAddress;		//!< IP�A�h���X
	u32				port;			//!< �|�[�g�ԍ�

	//! �R���X�g���N�^
	Address( void ) {
		Init();
	}

	//! ������
	void	Init( void );

	//! �ݒ�
	void	SetIpAddress( const char* ipAddress, u32 port );
	//void	SetIpAddress( IPAddress ipAddress, u32 port );
};



//=============================================================================
/*!
							�A�_�v�^���
*/
//=============================================================================
struct AdapterInfo {
	IPAddressStr	ipAddress;				//!< IP
	IPAddressStr	subnetMask;				//!< �T�u�l�b�g�}�X�N
	char			physicalAddress[256];	//!< �����A�h���X
};


//=============================================================================
/*!
							�p�P�b�g�w�b�_
*/
//=============================================================================
struct PacketHeader {
	u32			headerSize;		//!< ���̃f�[�^�T�C�Y
	u32			dataSize;		//!< �f�[�^�T�C�Y
	u64			packetNo;		//!< �p�P�b�g�ԍ�
};


//=============================================================================
/*!
							��M�m�F�p�P�b�g
*/
//=============================================================================
struct ReceiveCheckPacket {
	u64			packetNo;
};

//===========================================================================
/*!	@brief		�\�P�b�g�̐���
*/
//===========================================================================
s32		CreateSocket( SOCKET_TYPE type );


//===========================================================================
/*!	@brief		�\�P�b�g���N���[�Y
*/
//===========================================================================
void	CloseSocket( SocketID socket );

//===========================================================================
/*!	@brief		�ڑ�
*/
//===========================================================================
s32		ConnectSocket( SocketID socket, struct sockaddr* addr, SocketLength addrSize );


//===========================================================================
/*!	@brief		�A�_�v�^�����擾
*/
//===========================================================================
bool	GetAdapterInfo( AdapterInfo* outAdapterInfo, s32 adapterNo );
	

//===========================================================================
/*!	@brief		"255.255.255.255" -> FFFFFFFF
*/
//===========================================================================
void	IPAddressStrToIPAddress( IPAddress* outIpAddress, IPAddressStr ipAddress );


//===========================================================================
/*!	@brief		FFFFFFFF -> "255.255.255.255"
*/
//===========================================================================
void	IPAddressToIPAddressStr( IPAddressStr* outIpAddress, IPAddress ipAddress );


//===========================================================================
/*!	@brief		�u���[�h�L���X�g�A�h���X���擾
*/
//===========================================================================
bool	GetBroadcastAddressStr( IPAddressStr* outIpAddress, s32 adapterNo = 0 );

//===========================================================================
/*!	@brief		���ʎ擾
*/
//===========================================================================
SOCKET_RESULT GetLastResult( void );
	
}	// namespace net
	
}	// namespace nk







#endif  // __SOCKET_UTILITY_H__