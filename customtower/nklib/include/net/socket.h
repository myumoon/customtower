//=============================================================================
/*!	@file	socket.h

	@brief	�\�P�b�g

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================


#ifndef __SOCKET_H__
#define __SOCKET_H__

#if defined(_WIN32)
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif	// defined(_WIN32)

#include "./socketUtility.h"

namespace nk {

namespace net {
	
//=============================================================================
/*!
								�\�P�b�g
*/
//=============================================================================
class Socket {
public:
	//-----------------------�^��`--------------------------
	enum SOCKET_TYPE {
		SOCKET_TYPE_UNKNOWN,		//!< �s��
		SOCKET_TYPE_TCP,			//!< TCP
		SOCKET_TYPE_UDP,			//!< UDP
		SOCKET_TYPE_UDP_BROADCAST,	//!< UDP �u���[�h�L���X�g
		SOCKET_TYPE_UDP_MULTICAST,	//!< UDP �}���`�L���X�g
		
		SOCKET_TYPE_USER,			//!< ���[�U�[��`
	};


	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	//virtual bool			Create( const char* ipAddress, s32 port ) = 0;
	
	bool			CreateTCP			( const char* ipAddress, s32 port, bool blocking = true );	//!< TCP
	bool			CreateUDP			( const char* ipAddress, s32 port, bool blocking = true );	//!< UDP
	bool			CreateUDP_Broadcast	( const char* ipAddress, s32 port, bool blocking = true );	//!< UDP �u���[�h�L���X�g
	bool			CreateUDP_Multicast	( const char* ipAddress, s32 port, bool blocking = true );	//!< UDP �}���`�L���X�g


	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	void				Close( void );


	//===========================================================================
	/*!	@brief		���M
	*/
	//===========================================================================
	virtual bool		Send( void* packet, u32 packetSize );


	//===========================================================================
	/*!	@brief		��M
	*/
	//===========================================================================
	virtual SOCKET_RESULT		Receive( void* packet, u32 packetSize, Address* senderAddr = NULL );


	//===========================================================================
	/*!	@brief		�o�C���h
	*/
	//===========================================================================
	virtual void		Bind( void );


	//===========================================================================
	/*!	@brief		���X��
	*/
	//===========================================================================
	virtual void		Listen( s32 backlog );


	//===========================================================================
	/*!	@brief		�ڑ��v��
	*/
	//===========================================================================
	virtual bool		Connect( void );
	

	//===========================================================================
	/*!	@brief		�\�P�b�g�ԍ��擾
	*/
	//===========================================================================
	virtual SocketID	GetID( void ) const;

	//===========================================================================
	/*!	@brief		�u���b�L���O�ݒ�
	*/
	//===========================================================================
	void				SetBlocking( bool block = true );

	//===========================================================================
	/*!	@brief		�u���b�L���O�ݒ�擾
	*/
	//===========================================================================
	bool				IsBlocking( void ) const;


protected:
	// �\�P�b�g����
	bool			_CreateSocket( SOCKET_TYPE type );

	// IP�E�|�[�g�ݒ�
	void			_SetAddress( const char* ipAddress, s32 port );

	// �o�C���h
	void			_Bind( void );

	// ���X��
	void			_Listen( s32 backlog );
	
	// �ڑ�
	bool			_Connect( void );

	// �u���b�L���O�ݒ�
	void			_SetBlocking( bool block );
	
protected:
	//----------------------�����o�ϐ�-----------------------
	SocketID		m_id;			//!< �\�P�b�g���ʎq
	sockaddr_in		m_addr;			//!< �A�h���X
	SOCKET_TYPE		m_type;			//!< �ʐM�^�C�v
	bool			m_initialized;	//!< �������ς݂Ȃ�true
	bool			m_blocking;		//!< �u���b�L���O�Ȃ�true
	//s32				m_copyCounter;	//!< �R�s�[�J�E���^
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Socket();
			Socket( SocketID id, SOCKET_TYPE type );
	virtual~Socket();
};


	
}	// namespace net
	
}	// namespace nk







#endif  // __SOCKET_H__