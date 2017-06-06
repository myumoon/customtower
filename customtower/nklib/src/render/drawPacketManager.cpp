//=============================================================================
/*!	@file	drawPacketManager.h

	@brief	�`��p�P�b�g�Ǘ�

	@author	ryunosuke ide
	@date	2013.06.22
	
	@note	drawPacket�̐������s����Vertex��Face�̐����Ɏ��Ԃ�������̂�
			�Q�[�����������Ɉ�C�ɏ��������Ă����B
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/render/drawPacketManager.h"
#include "../../include/render/renderManager.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {
namespace graphics {

	
//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
DrawPacketManager::DrawPacketManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
DrawPacketManager::~DrawPacketManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void DrawPacketManager::_Init( void )
{
	m_renderManager	= NULL;
	m_usablePacket	= 0;
	m_packetsSize	= 0;
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
#else
	m_packets	= NULL;
#endif
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void DrawPacketManager::_Term( void )
{
	Terminate();
}


//===========================================================================
/*!	@brief		������
	@param		maxPacket	�ő�p�P�b�g��
	@return		----
*/
//===========================================================================
void DrawPacketManager::Initialize( u32 maxPacket )
{	
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	m_packets.resize( maxPacket );
	m_packetsSize	= m_packets.size();
#else
	if( m_packets == NULL ) {
		m_packets		= new DrawPacket[maxPacket];
		m_packetsSize	= maxPacket;
	}
#if defined(_DEBUG)
	else {
		PRINTF("DrawPacketManager::Initialize : already initialized.\n");
	}
#endif	// #if defined(_DEBUG)
#endif	// #if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	
}

//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		----
*/
//===========================================================================
void DrawPacketManager::Terminate( void )
{
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	m_packets.clear();
#else
	SafeDeleteArray( m_packets );
#endif
}


//===========================================================================
/*!	@brief		�g�p�\�p�P�b�g�ԍ���������
	@param		----
	@return		----
*/
//===========================================================================
void DrawPacketManager::ChangeStateDisuseAllPacket( void )
{
	// ���o���ꏊ��ς��邾��
	m_usablePacket	= 0;
}


//===========================================================================
/*!	@brief		�g�p�\�p�P�b�g���擾
	@param		----
	@return		----
*/
//===========================================================================
DrawPacket& DrawPacketManager::PopDrawPacket( void )
{
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	if( m_packets.size() <= m_usablePacket ) {
		m_packets.resize( m_packets.size() * 2 );
	}
	
	DrawPacket&	retPacket	= m_packets.at( m_usablePacket );
#else
	if( m_packetsSize <= m_usablePacket ) {
		ASSERT( false, "packet buffer over." );
	}
	
	DrawPacket&	retPacket	= m_packets[m_usablePacket];
#endif
	
	retPacket.Clear();
	
	++m_usablePacket;
	
	return retPacket;
}


//===========================================================================
/*!	@brief		�`��}�l�[�W���[�ɑ��M
	@param		packet	���M�p�P�b�g
	@return		----
*/
//===========================================================================
void DrawPacketManager::SendToDrawManager( const DrawPacket& packet )
{
	const DrawPacket*	sendPacket	= NULL;

#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
	{
		// Pop���ꂽ�p�P�b�g�Ȃ�A�h���X�𑗂�
		for( u32 i = 0; i < m_packets.size(); ++i ) {
			if( &packet == &m_packets[i] ) {
				sendPacket	= &m_packets[i];
				break;
			}
		}
	}
#else
	{
		// �z��͈͓�
		if( (&m_packets[0] <= &packet) && (&packet <= &m_packets[m_packetsSize - 1]) ) {
// 			sendPacket	= const_cast<DrawPacket*>(&packet);
			sendPacket	= &packet;
		}
	}
#endif

	// ���o�^�̃p�P�b�g�Ȃ�o�^
	if( sendPacket == NULL ) {
		DrawPacket&	popPacket	= PopDrawPacket();
		popPacket				= packet;
		sendPacket				= &popPacket;
	}

	// ���M
	m_renderManager->Add( sendPacket );
}

}	// namespace graphics
}	// namespace nk