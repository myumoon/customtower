//=============================================================================
/*!	@file	debugItemChunk.h

	@brief	�f�o�b�O���ڂ̂܂Ƃ܂�

	@author	ryunosuke ide
	@date	2013.06.15
*/
//=============================================================================

#ifndef __DEBUG_ITEM_CHUNK_H__
#define __DEBUG_ITEM_CHUNK_H__

#include <string>
#include <vector>
#include "../math/vector.h"
#include "../utility/selector.h"
#include "debugEventListener.h"
#include "debugItem.h"




namespace nk {

namespace input {
class Keyboard;
}
	
namespace debug {


class DebugItemInterface;

//=============================================================================
/*!
								�f�o�b�O����
*/
//=============================================================================
class DebugItemChunk {
public:
	//-----------------------�^��`--------------------------
	static const s32	TITLE_SIZE				= 128;					//!< �^�C�g�����

	//! �f�o�b�O���ڃZ���N�^
	enum {
		SELECT_VALUE_PUSH_LEFT,			//!< �l����
		SELECT_VALUE_NOT_SELECT,		//!< �����l
		SELECT_VALUE_PUSH_RIGHT,		//!< �l�㏸
		
		SELECT_VALUE_MAX,
	};

	typedef std::vector<DebugItemInterface*>	VecItem;
	
	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�^�C�g���ݒ�
	*/
	//===========================================================================
	void			SetTitle( const char* title );

	//===========================================================================
	/*!	@brief		�^�C�g���擾
	*/
	//===========================================================================
	const char*		GetTitle( void ) const;

	//===========================================================================
	/*!	@brief		���ڒǉ�
	*/
	//===========================================================================
//	void			AddItem( s32 itemNo, const char* itemName, const std::string& defaultStr, s32 defaultNo = 0 );
//	void			AddItem( s32 itemNo, const char* itemName, const char*		  defaultStr, s32 defaultNo = 0 );
	void			AddItem( DebugItemInterface* item );
//	void			SetItem( const DebugItem* items[], u32 arysize );

	//===========================================================================
	/*!	@brief		���ڍ폜
	*/
	//===========================================================================
	void			DeleteItem( void* callobj );

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	void			Update( void );

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	void			Draw( const math::Vector& offset );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//===========================================================================
	/*!	@brief		�A�C�e���ǉ�
	*/
	//===========================================================================
	void			_AddItem( DebugItemInterface* item );

	//===========================================================================
	/*!	@brief		���ڃZ���N�g�R�[���o�b�N
	*/
	//===========================================================================
	void			_ItemSelectCallback( s32 selectNo );

	//===========================================================================
	/*!	@brief		����R�[���o�b�N
	*/
	//===========================================================================
	void			_ItemDecideCallback( s32 selectNo );

	//----------------------�����o�ϐ�-----------------------
	char						m_title[TITLE_SIZE];		//!< �^�C�g��
	input::Keyboard*			m_keyboard;					//!< �L�[�{�[�h
	Selector<>					m_titleSelector;			//!< �Z���N�^(�^�C�g��)
	Selector<DebugItemChunk>	m_valueSelector;			//!< �f�o�b�O�ϐ��Z���N�^

	VecItem						m_items;					//!< �\������
 	s32							m_nowLine;					//!< ���썀��
	s32							m_maxItemTitleStrLength;	//!< �Œ��^�C�g��

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			DebugItemChunk( const char* title, DebugEventListener* listener );
			DebugItemChunk( const char* title );
			DebugItemChunk();
	virtual~DebugItemChunk();
};
	
}	// namespace debug
}	// namespace nk



#endif  // __DEBUG_ITEM_CHUNK_H__