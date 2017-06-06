//=============================================================================
/*!	@file	packetReceiveThread.h

	@brief	�p�P�b�g��M�X���b�h

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================

#ifndef __PACKET_RECEIVE_THREAD_H__
#define __PACKET_RECEIVE_THREAD_H__

#include <vector>
#include <map>
#include "../thread/thread.h"
#include "./socket.h"

namespace nk {
namespace net {

class PacketReceiver;

//=============================================================================
/*!
						�p�P�b�g��M�X���b�h
*/
//=============================================================================
class PacketReceiveThread : public Thread {
public:
	//-----------------------�^��`--------------------------
		

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		��M���R�[���o�b�N�ǉ�
	*/
	//===========================================================================
	void			Add( const Socket& socket, PacketReceiver* receiver );

	//===========================================================================
	/*!	@brief		�^�C���A�E�g�ݒ�
	*/
	//===========================================================================
	void			SetTimeout( s32 sec, s32 micSec );

protected:
	virtual void	ThreadFunc( void );

	//===========================================================================
	/*!	@brief		��M�`�F�b�N
	*/
	//===========================================================================
	bool			Receive( void );
	
private:
	//----------------------�����o�ϐ�-----------------------
	//std::map<Socket::SocketID, PacketReceiver*>	m_receivers;	//!< �p�P�b�g��M
	std::vector<SocketInfo>		m_vecSocketInfo;	//!< �\�P�b�g���
	fd_set						m_fd;				//!< ��M��ԊǗ�
	timeval						m_timeout;			//!< �^�C���A�C�g
	u32							m_maxID;			//!< �ő�ID

	CriticalSection				m_criticalSection;	//!< �~���[�e�b�N�X
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			PacketReceiveThread();
	virtual~PacketReceiveThread();
};

}	// namespace net
}	// namespace nk


#endif  // __PACKET_RECEIVE_THREAD_H__