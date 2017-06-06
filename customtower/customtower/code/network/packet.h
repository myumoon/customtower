//=============================================================================
/*!	@file	packet.h

	@brief	�p�P�b�g

	@author	ryunosuke ide
	@date	2013.05.23
*/
//=============================================================================


#ifndef __PACKET_H__
#define __PACKET_H__


#include "net/socketUtility.h"

namespace network {


//=============================================================================
/*!
							�z�X�g�����p�P�b�g
*/
//=============================================================================
struct Packet_FindClientToHost {
	s32						port;			//!< �|�[�g
	char	str[128];
};

struct Packet_FindHostToClient {
	nk::net::IPAddress		ipAddress;		//!< IP
	char					hostName[64];	//!< �z�X�g��
	char					roomName[64];	//!< ������
};


}	// namespace network



#endif  // __PACKET_H__