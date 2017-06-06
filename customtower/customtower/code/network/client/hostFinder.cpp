//=============================================================================
/*!	@file	hostFinder.h

	@brief	�z�X�g����

	@author	ryunosuke ide
	@date	2013.05.23
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "net/socketReceiver.h"
#include "utility/utility.h"
#include "general.h"

#include "hostFinder.h"
#include "gameDef.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace network {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
HostFinder::HostFinder()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
HostFinder::~HostFinder()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void HostFinder::_Init( void )
{
	m_initialized	= false;
	m_finished		= false;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void HostFinder::_Term( void )
{
	if( m_initialized ) {
		Close();
	}
}

//===========================================================================
/*!	@brief		�Z�b�g�A�b�v
	@param		----
	@return		----
*/
//===========================================================================
void HostFinder::Setup( void )
{
	printf("HostFinder::Setup start\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	// ���M�\�P�b�g�쐬
	{
		m_findSockets.clear();
		
		// �u���[�h�L���X�g�A�h���X�擾
		nk::net::IPAddressStr	ipStr;
		bool					result		= true;
		s32						adapterNo	= 0;

		do {
			result = nk::net::GetBroadcastAddressStr( &ipStr, adapterNo );
			if( result ) {
				nk::net::Socket	addSocket;
				addSocket.CreateUDP_Broadcast( ipStr.ipAddress, PORT_FIND_HOST_CLIENT_TO_SERVER );

				m_findSockets.push_back( addSocket );
				
				++adapterNo;
			}
		} while( result );

		m_sendPacket.port	= PORT_FIND_HOST_SERVER_TO_CLIENT;
		memset( m_sendPacket.str, 0, 128 );
		strcpy_s( m_sendPacket.str, 128, "hello world" );
	}

	// ��M�\�P�b�g�쐬
	{
		m_receiveSocket.CreateUDP( NULL, PORT_FIND_HOST_SERVER_TO_CLIENT );
		m_receiver.Init();
		m_receiver.AddReceiveScoket( m_receiveSocket, this );
	}

	

	// �X���b�h�쐬
	Thread::Setup( THREAD_PRIORITY_NORMAL, 0, "HostFinder::Setup" );

	m_initialized	= true;

	printf("HostFinder::Setup end\n");
}

//===========================================================================
/*!	@brief		�N���[�Y
	@param		----
	@return		----
*/
//===========================================================================
void HostFinder::Close( void )
{
	printf("HostFinder::Close start\n");

	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	// �\�P�b�g�����
	for( u32 i = 0; i < m_findSockets.size(); ++i ) {
		m_findSockets[i].Close();
	}	
	m_receiveSocket.Close();
	m_receiver.Clear();

	m_result.results.clear();
	m_initialized	= false;

	printf("HostFinder::Close end\n");
}


//===========================================================================
/*!	@brief		��M���R�[���o�b�N�ǉ�
	@param		receiver	���V�[�o
	@return		----
*/
//===========================================================================
void HostFinder::AddReceiver( SearchResultReceiver* receiver )
{
	printf("HostFinder::AddReceiver start\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	m_receiveCallbacks.push_back( receiver );

	printf("HostFinder::AddReceiver end\n");
}



//===========================================================================
/*!	@brief		��M���R�[���o�b�N�폜
	@param		receiver	���V�[�o
	@return		----
*/
//===========================================================================
void HostFinder::RemoveReceiver( SearchResultReceiver* receiver )
{
	printf("HostFinder::RemoveReceiver start\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );

	std::vector<SearchResultReceiver*>::iterator	itr	= m_receiveCallbacks.begin();
	for( ; itr != m_receiveCallbacks.end(); ) {
		if( (*itr) == receiver ) {
			itr	= m_receiveCallbacks.erase( itr );
		}
		else {
			++itr;
		}
	}

	printf("HostFinder::RemoveReceiver end\n");
}


//===========================================================================
/*!	@brief		�X���b�h����
	@param		----
	@return		----
*/
//===========================================================================
void HostFinder::ThreadFunc( void )
{
	printf("HostFinder::ThreadFunc start\n");
	bool	result		= false;
	u64		startTime	= nk::GetTimeMillSec();

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );
		m_result.Clear();
	}
	
	while( 1 ) {

		// �z�X�g����̃��b�Z�[�W����M
		{
			SCOPE_CRITICAL_SECTION( m_criticalSection );
			result	= _ReceiveMessageFromHost();
			//_ReceiveMessageFromHost();
		}

		if( DEFAULT_TIMEOUT_MILLISEC < nk::GetTimeMillSec() - startTime ) {
			break;
		}
		
		nk::SleepThread( 1 );
	}

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );
		
// 		if( 0 < m_result.GetResultNum() ) {

		// ��M���R�[���o�b�N
		for( u32 i = 0; i < m_receiveCallbacks.size(); ++i ) {
			m_receiveCallbacks[i]->CallbackReceivedResult( m_result );
		}
// 		}
// 		else {
// 			printf("not found.\n");
// 		}

		Close();
	
		m_finished	= true;
	}

	printf("HostFinder::ThreadFunc end\n");
}

//===========================================================================
/*!	@brief		����
	@param		timeoutMilliSec	�^�C���A�E�g�~���b
	@return		----
*/
//===========================================================================
bool HostFinder::Find( s32 timeoutMilliSec )
{
	if( Running() ) {
		return false;
	}

	printf("SCOPE_CRITICAL_SECTION\n");
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	printf("_Find\n");
	return _Find( timeoutMilliSec );
}


//===========================================================================
/*!	@brief		����
	@param		timeoutMilliSec	�^�C���A�E�g�~���b
	@return		----
*/
//===========================================================================
bool HostFinder::_Find( s32 timeoutMilliSec )
{
	printf("HostFinder::_Find start\n");
	
	HostFinder::Setup();
	
	if( m_initialized == false ) {
		printf("HostFinder::_Find false\n");
		return false;
	}
	
	bool	result	= false;

	// �������̏��𑗐M
	do {
		// ���炩���ߎ�M�ҋ@���Ă���
		Thread::Start();
		
		// �z�X�g����
		result	= _SendMessage();
		if( result == false ) {
			break;
		}

	} while( 0 );


	printf("HostFinder::_Find end\n");

	return result;
}

//===========================================================================
/*!	@brief		������̏����u���[�h�L���X�g�ő��M
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::_SendMessage( void )
{
	PRINTF("HostFinder::_SendMessage start\n");
	bool	result = true;

	for( u32 i = 0; i < m_findSockets.size(); ++i ) {
		result	&= m_findSockets[i].Send( &m_sendPacket, sizeof(m_sendPacket) );
		nk::SleepThread( 1 );
	}

	PRINTF("HostFinder::_SendMessage end\n");
	
	return result;
}

//===========================================================================
/*!	@brief		�z�X�g����̃��b�Z�[�W����M
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::_ReceiveMessageFromHost( void )
{
	printf("HostFinder::_ReceiveMessageFromHost start\n");
	bool	result = false;

	m_receiver.SetTimeout( 0, DEFAULT_TIMEOUT_MILLISEC * 1000 );
	result	= m_receiver.ReceiveWait();

	printf("HostFinder::_ReceiveMessageFromHost end\n");
	
	return result;
}


//===========================================================================
/*!	@brief		��M���R�[���o�b�N
	@param		packet		��M�p�P�b�g
	@param		packetSize	�p�P�b�g�T�C�Y
	@return		----
*/
//===========================================================================
void HostFinder::Receive( void* packet, u32 packetSize )
{
	printf("HostFinder::Receive start\n");
	Packet_FindHostToClient*	hostInfo	= static_cast<Packet_FindHostToClient*>(packet);

	HostInfo	addInfo;
	nk::net::IPAddressToIPAddressStr( &addInfo.ipAddressStr, hostInfo->ipAddress );
	strcpy_s( addInfo.hostName, sizeof(hostInfo->hostName), hostInfo->hostName );
	strcpy_s( addInfo.roomName, sizeof(hostInfo->roomName), hostInfo->roomName );

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );

		// �����z�X�g�̏��͒e��
		if( _Registered( addInfo ) == false ) {
			m_result.results.push_back( addInfo );
		}
	}

	printf("HostFinder::Receive end\n");
}


//===========================================================================
/*!	@brief		�I���H
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::IsEnd( void ) const
{
	nk::CriticalSection	criticalSectiom	= m_criticalSection;
	SCOPE_CRITICAL_SECTION( criticalSectiom );
	
	return m_finished;
}


//===========================================================================
/*!	@brief		�o�b�t�@�擾
	@param		buffer		�擾�o�b�t�@
	@param		bufferSize	�o�b�t�@�T�C�Y
	@return		----
*/
//===========================================================================
void* HostFinder::GetBuffer( void )
{
	
	return static_cast<void*>(&m_receivePacket);
}

//===========================================================================
/*!	@brief		�o�b�t�@�T�C�Y�擾
	@param		----
	@return		----
*/
//===========================================================================
u32 HostFinder::GetBufferSize( void ) const
{
	
	return sizeof(m_receivePacket);
}


//===========================================================================
/*!	@brief		������񂪓o�^����Ă���Ȃ�true��Ԃ�
	@param		----
	@return		----
*/
//===========================================================================
bool HostFinder::_Registered( const HostInfo& info )
{
	printf("HostFinder::_Registered start\n");
	
	for( u32 i = 0; i < m_result.GetResultNum(); ++i ) {
		if( m_result.GetResult(i)->IsSameInfo( info ) ) {
			printf("HostFinder::_Registered true\n");
			return true;
		}
	}

	printf("HostFinder::_Registered end\n");

	return false;
}


	
}	// namespace network
