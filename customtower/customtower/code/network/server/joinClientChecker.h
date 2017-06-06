//=============================================================================
/*!	@file	joinClientChecker.h

	@brief	�N���C�A���g�ǉ��m�F

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================


#ifndef __JOIN_CLIENT_CHECKER_H__
#define __JOIN_CLIENT_CHECKER_H__

#include <vector>
#include "net/socket.h"
#include "net/socketReceiver.h"
#include "net/packetReceiver.h"
#include "thread/thread.h"

#include "../packet.h"

namespace network {



//=============================================================================
/*!
							�N���C�A���g�ǉ��m�F
*/
//=============================================================================
class JoinClientChecker : public nk::net::PacketReceiver, public nk::Thread {
public:
	//-----------------------�^��`--------------------------

	//! �p�P�b�g���M�X���b�h
	class PacketSendThread : public nk::Thread {
	public:
		static const s32	DEFAULT_SEND_NUM				= 10;	//!< �f�t�H���g���M��
		static const s32	DEFAULT_SEND_INTERVAL_MILLISEC	= 100;	//!< ���M�Ԋu

		//! ���M���
		struct SendInfo {
			nk::net::Socket				sendSocket;			//!< ���M�\�P�b�g
			Packet_FindHostToClient		sendPacket;			//!< ���M�p�P�b�g
			s32							sendCount;			//!< ���M�J�n����
		};
		typedef std::vector<SendInfo>	VecSendInfo;
		
	public:
		//! �R���X�g���N�^�E�f�X�g���N�^
				 PacketSendThread();
		virtual ~PacketSendThread();

		//! �ݒ�
		void		AddSendSocket(
			nk::net::IPAddress				ipAddress,
			u32								port,
			const Packet_FindHostToClient&	packet
		);
		
		//! �ݒ�
		void		SetOption( s32 sendNum, s32 intervalMilliSec );

		//! �X���b�h����
		void		ThreadFunc( void );
		
	private:
		//! ������
		void		_Init( void );
		void		_Term( void );

		//! �\�P�b�g�폜
		void		_DeleteSockets( void );
		
	private:
		nk::CriticalSection				m_criticalSection;	//!< �N���e�B�J���Z�N�V����
		VecSendInfo						m_sendInfos;		//!< ���M���
		s32								m_sendNum;			//!< ���M��
		s32								m_sendInterval;		//!< ���M�Ԋu
	};

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�Z�b�g�A�b�v
	*/
	//===========================================================================
	bool	Setup( void );

	//===========================================================================
	/*!	@brief		�N���[�Y
	*/
	//===========================================================================
	void	Close( void );	
		
	//===========================================================================
	/*!	@brief		��M�`�F�b�N
		@note		�f�[�^����M����܂Ńu���b�N���܂�
	*/
	//===========================================================================
	bool	CheckReceive( void );
	
	//===========================================================================
	/*!	@brief		�o�b�t�@�擾
	*/
	//===========================================================================
	virtual void*	GetBuffer( void )			{ return &m_receivePacket; }
	virtual u32		GetBufferSize( void ) const	{ return sizeof(m_receivePacket); }

	//===========================================================================
	/*!	@brief		��M
	*/
	//===========================================================================
	virtual void	Receive( void* packet, u32 packetSize );

	void	(*m_callbackReceive)( nk::net::IPAddress );

protected:
	//===========================================================================
	/*!	@brief		�X���b�h����
	*/
	//===========================================================================
	virtual void	ThreadFunc( void );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

	//----------------------�����o�ϐ�-----------------------
	nk::net::Socket					m_receiveCheckSocket;	//!< �u���[�h�L���X�g��M�\�P�b�g
	nk::net::SocketReceiver			m_receiver;				//!< ���V�[�o
	Packet_FindClientToHost			m_receivePacket;		//!< ��M�p�P�b�g
	PacketSendThread				m_sendThread;			//!< ���M�X���b�h
	nk::CriticalSection				m_criticalSection;	//!< �N���e�B�J���Z�N�V����
	//nk::net::Socket					m_sendSocket;			//!< �ʒm�\�P�b�g
	
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			JoinClientChecker();
	virtual~JoinClientChecker();
};
	
}	// namespace network




#endif  // __JOIN_CLIENT_CHECKER_H__