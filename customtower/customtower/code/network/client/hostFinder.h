//=============================================================================
/*!	@file	hostFinder.h

	@brief	�z�X�g����

	@author	ryunosuke ide
	@date	2013.05.23
*/
//=============================================================================

#ifndef __HOST_FINDER_H__
#define __HOST_FINDER_H__

#include "net/socket.h"
#include "net/socketReceiver.h"
#include "net/packetReceiver.h"
#include "thread/thread.h"

#include "../packet.h"

namespace network {


//=============================================================================
/*!
								�z�X�g����
*/
//=============================================================================
class HostFinder : public nk::net::PacketReceiver, public nk::Thread {
public:
	//-----------------------�^��`--------------------------
	static const s32	DEFAULT_TIMEOUT_MILLISEC	= 1000;	//!< �f�t�H���g�^�C���A�E�g����

	//! �z�X�g���
	struct HostInfo {
		nk::net::IPAddressStr	ipAddressStr;
		char					hostName[64];
		char					roomName[64];

		//! �����H
		bool	IsSameInfo( const HostInfo& rhs )
		{
			if( strcmp( ipAddressStr.ipAddress, rhs.ipAddressStr.ipAddress ) != 0 ) {
				return false;
			}
			if( strcmp( hostName, rhs.hostName ) != 0 )  {
				return false;
			}
			if( strcmp( roomName, rhs.roomName ) != 0 )  {
				return false;
			}

			return true;
		}
	};
	//typedef std::vector<HostInfo>	VecHostInfo;

	//! �������ʊi�[�p
	struct SearchResult {
		std::vector<HostInfo>		results;	//!< ��������

		SearchResult()
		{
			results.reserve( 32 );
		}
		
		//! �q�b�g���擾
		u32			GetResultNum( void )
		{
			return results.size();
		}

		//! �z�X�g���擾
		HostInfo*	GetResult( u32 index )
		{
			if( (0 <= index) && (index < GetResultNum()) ) {
				return &results[index];
			}
			
			return NULL;
		}

		//! �N���A
		void		Clear( void )
		{
			results.clear();
		}
	};

	//! �������ʃ��V�[�o�[
	class SearchResultReceiver {
	public:
		//! @brief		�擾���R�[���o�b�N
		//! @caution	result�͂��̊֐����ł̂ݗL���ł��B
		virtual void	CallbackReceivedResult( SearchResult& result )	= 0;
	};


	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		��M���R�[���o�b�N�ǉ�
	*/
	//===========================================================================
	void				AddReceiver( SearchResultReceiver* receiver );

	//===========================================================================
	/*!	@brief		��M���R�[���o�b�N�ǉ�
	*/
	//===========================================================================
	void				RemoveReceiver( SearchResultReceiver* receiver );

	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	bool				Find( s32 timeoutMilliSec = DEFAULT_TIMEOUT_MILLISEC );

	//===========================================================================
	/*!	@brief		�I���H
	*/
	//===========================================================================
	bool				IsEnd( void ) const;
	
	//===========================================================================
	/*!	@brief		�o�b�t�@�擾
	*/
	//===========================================================================
	virtual void*		GetBuffer( void );
	virtual u32			GetBufferSize( void ) const;
	
	//===========================================================================
	/*!	@brief		�N���[�Y
	*/
	//===========================================================================
	void				Close( void );

	
protected:
	//===========================================================================
	/*!	@brief		�Z�b�g�A�b�v
	*/
	//===========================================================================
	void				Setup( void );

	
	//===========================================================================
	/*!	@brief		��M
	*/
	//===========================================================================
	virtual void		Receive( void* packet, u32 packetSize );

	//===========================================================================
	/*!	@brief		�X���b�h
	*/
	//===========================================================================
	virtual void		ThreadFunc( void );
	

private:
	//-----------------------���\�b�h------------------------
	void		_Init( void );
	void		_Term( void );

	//! ����
	bool		_Find( s32 timeoutMilliSec );

	//! �u���[�h�L���X�g�ő��M
	bool		_SendMessage( void );

	//! �z�X�g����̃��b�Z�[�W����M
	bool		_ReceiveMessageFromHost( void );

	//! ���ɓo�^����Ă�����true��Ԃ�
	bool 		_Registered( const HostInfo& info );

	//----------------------�����o�ϐ�-----------------------
	bool								m_initialized;			//!< ������
	std::vector<nk::net::Socket>		m_findSockets;			//!< �����\�P�b�g
	//nk::net::Socket						m_findSocket;			//!< �����\�P�b�g
	nk::net::Socket						m_receiveSocket;		//!< ��M�p�\�P�b�g
	nk::net::SocketReceiver				m_receiver;				//!< ���V�[�o
	nk::net::IPAddress					m_broadcastAddress;		//!< �u���[�h�L���X�g�A�h���X
	Packet_FindClientToHost				m_sendPacket;			//!< ���M�p�P�b�g
	Packet_FindHostToClient				m_receivePacket;		//!< ��M�p�P�b�g
	
	nk::CriticalSection					m_criticalSection;		//!< �N���e�B�J���Z�N�V����
	bool								m_finished;				//!< �I��

	SearchResult						m_result;				//!< �z�X�g��񑗐M�p
	std::vector<SearchResultReceiver*>	m_receiveCallbacks;		//!< ���ʎ�M���R�[���o�b�N
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			HostFinder();
	virtual~HostFinder();
};


}	// namespace network

#endif  // __HOST_FINDER_H__