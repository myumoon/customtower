//=============================================================================
/*!	@file	packetReceiver.h

	@brief	�p�P�b�g���V�[�o

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================

#ifndef __PACKET_RECEIVER_H__
#define __PACKET_RECEIVER_H__

#include "./socket.h"

namespace nk {

namespace net {

//=============================================================================
/*!
					�p�P�b�g��M�C���^�[�t�F�[�X
*/
//=============================================================================
class PacketReceiver {
public:
	//! �R���X�g���N�^�E�f�X�g���N�^
			 PacketReceiver();
	virtual ~PacketReceiver();

	//===========================================================================
	/*!	@brief		��M
	*/
	//===========================================================================
	virtual void		Receive( void* packet, u32 packetSize ) = 0;

	//===========================================================================
	/*!	@brief		�o�b�t�@�擾
	*/
	//===========================================================================
	//virtual void		GetBuffer( void** buffer, u32* bufferSize ) = 0;
	virtual void*		GetBuffer( void ) = 0;
	virtual u32			GetBufferSize( void ) const = 0;

	//===========================================================================
	/*!	@brief		���M�ҏ����擾
	*/
	//===========================================================================
	void				GetIPAddressStr( IPAddressStr* outIpAddress ) const;
	IPAddress			GetIPAddress( void ) const;

	//===========================================================================
	/*!	@brief		��M�����Ȃ�true��Ԃ�
	*/
	//===========================================================================
	bool				IsReceived( void ) const;
	

	//===========================================================================
	/*!	@brief		��M���R�[���o�b�N
	*/
	//===========================================================================
	void				ReceiveCallback( Socket receiveSocket, void* packet, u32 packetSize, Address senderAddr );


private:
	IPAddressStr			m_ipAddressStr;		//!< ���M�ҏ��
	IPAddress				m_ipAddress;		//!< ���M�ҏ��
	bool					m_received;			//!< ��M�����Ȃ�true
};
	
}	// namespace net
	
}	// namespace nk







#endif  // __PACKET_RECEIVER_H__
