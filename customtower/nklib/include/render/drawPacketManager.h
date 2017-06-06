//=============================================================================
/*!	@file	drawPacketManager.h

	@brief	�`��p�P�b�g�Ǘ�

	@author	ryunosuke ide
	@date	2013.06.22
	
	@note	drawPacket�̐������s����Vertex��Face�̐����Ɏ��Ԃ�������̂�
			�Q�[�����������Ɉ�C�ɏ��������Ă����B
*/
//=============================================================================

#ifndef __DRAW_PACKET_MANAGER_H__
#define __DRAW_PACKET_MANAGER_H__

#include "../typedef.h"
#include "drawPacket.h"

//#define __DRAWPACKETMANAGER_USE_VECTOR	// ������`����Ɣz��ł͂Ȃ�vector�ŊǗ�

namespace nk {

namespace graphics {

class renderManager;

//=============================================================================
/*!
						�`��p�P�b�g�Ǘ�
*/
//=============================================================================
class DrawPacketManager {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	static const u32	DEFAULT_MAX_PACKET	= 2048;		//!< �f�t�H���g�ő�p�P�b�g��
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	void			Initialize( u32 maxPacket = DEFAULT_MAX_PACKET );

	//===========================================================================
	/*!	@brief		�I��
	*/
	//===========================================================================
	void			Terminate( void );

	//===========================================================================
	/*!	@brief		�g�p�\�p�P�b�g�ԍ���������
	*/
	//===========================================================================
	void			ChangeStateDisuseAllPacket( void );

	//===========================================================================
	/*!	@brief		�g�p�\�p�P�b�g���擾
	*/
	//===========================================================================
	DrawPacket&		PopDrawPacket( void );

	//===========================================================================
	/*!	@brief		�`��}�l�[�W���[�ɑ��M
	*/
	//===========================================================================
	void			SendToDrawManager( const DrawPacket& packet );

	//===========================================================================
	/*!	@brief		�`��}�l�[�W���[�ݒ�
	*/
	//===========================================================================
	void			SetRenderManager( RenderManager* renderManager ) { m_renderManager = renderManager; }
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
#if defined(__DRAWPACKETMANAGER_USE_VECTOR)
 	std::vector<DrawPacket>			m_packets;			//!< �`��p�P�b�g
#else
	DrawPacket*						m_packets;			//!< �`��p�P�b�g
#endif
	u32								m_packetsSize;		//!< �T�C�Y
	u32								m_usablePacket;		//!< �g�p�\�p�P�b�g�ԍ�
	RenderManager*					m_renderManager;	//!< �`��}�l�[�W���[
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			DrawPacketManager();
	virtual~DrawPacketManager();
};


}	// namespace graphics
}	// namespace nk





#endif  // __DRAW_PACKET_MANAGER_H__