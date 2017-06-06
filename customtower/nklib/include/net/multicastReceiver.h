//=============================================================================
/*!	@file	multicastReceiver.h

	@brief	�\�P�b�g

	@author	ryunosuke ide
	@date	2013.05.11
*/
//=============================================================================

#ifndef __MULTICAST_RECEIVER_H__
#define __MULTICAST_RECEIVER_H__

#include "../../include/net/socket.h"



namespace nk {

namespace net {

//=============================================================================
/*!
						�}���`�L���X�g���V�[�o�[
*/
//=============================================================================
class MulticastReceiver : public Socket {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	virtual bool			Create( const char* ipAddress, s32 port );

	//===========================================================================
	/*!	@brief		��M
	*/
	//===========================================================================
	bool					Receive( void );
	
private:
	//----------------------�����o�ϐ�-----------------------
	
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			MulticastReceiver();
	virtual~MulticastReceiver();
};
	
}	// namespace net
	
}	// namespace nk

#endif  // __MULTICAST_RECEIVER_H__