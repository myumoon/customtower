//=============================================================================
/*!	@file	packet.h

	@brief	パケット

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
							ホスト検索パケット
*/
//=============================================================================
struct Packet_FindClientToHost {
	s32						port;			//!< ポート
	char	str[128];
};

struct Packet_FindHostToClient {
	nk::net::IPAddress		ipAddress;		//!< IP
	char					hostName[64];	//!< ホスト名
	char					roomName[64];	//!< 部屋名
};


}	// namespace network



#endif  // __PACKET_H__