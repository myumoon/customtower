//=============================================================================
/*!	@file	debugItemChunk.h

	@brief	�f�o�b�O���ڂ̂܂Ƃ܂�

	@author	ryunosuke ide
	@date	2013.06.15
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <string.h>
#include <stdlib.h>
#include "../../include/debug/debugItemChunk.h"
#include "../../include/debug/debugItem.h"

#include "../../include/utility/utility.h"
#include "../../include/general.h"
#include "../../include/system.h"

#include "../../include/utility/autoTime.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {
namespace debug {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
DebugItemChunk::DebugItemChunk()
{
	_Init();
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	title		�^�C�g��
	@param	listener	�C�x���g���X�i�[
*/
//===========================================================================
DebugItemChunk::DebugItemChunk( const char* title, DebugEventListener* listener )
{
	_Init();

	SetTitle( title );
	//SetEventListener( listener );
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	title		�^�C�g��
*/
//===========================================================================
DebugItemChunk::DebugItemChunk( const char* title )
{
	_Init();

	SetTitle( title );
}



//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
DebugItemChunk::~DebugItemChunk()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void DebugItemChunk::_Init( void )
{
	m_keyboard				= NULL;
	m_nowLine				= 0;
	m_maxItemTitleStrLength	= 0;

	m_items.reserve( 128 );

	memset( m_title, 0, TITLE_SIZE );

	m_keyboard				= new input::Keyboard();

	m_titleSelector.Setup<UpdateRepeat>(
		0,
		m_keyboard,
		input::Keyboard::KEY_UP,
		input::Keyboard::KEY_DOWN,
		input::Keyboard::KEY_ENTER
	);

	m_valueSelector.Setup<UpdateRepeat>(
		SELECT_VALUE_MAX,
		m_keyboard,
		input::Keyboard::KEY_LEFT,
		input::Keyboard::KEY_RIGHT,
		input::Keyboard::KEY_ENTER,
		true,
		SELECT_VALUE_NOT_SELECT
	);
	m_valueSelector.SetCallbackReceiver( this );
	m_valueSelector.SetOnSelectCallback( &DebugItemChunk::_ItemSelectCallback );
	m_valueSelector.SetDecideCallback( &DebugItemChunk::_ItemDecideCallback );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void DebugItemChunk::_Term( void )
{
	for( u32 i = 0; i < m_items.size(); ++i ) {
		SafeDelete( m_items[i] );
	}
	SafeDelete( m_keyboard );
}


//===========================================================================
/*!	@brief		�^�C�g���ݒ�
	@param		title	�^�C�g��
	@return		----
*/
//===========================================================================
void DebugItemChunk::SetTitle( const char* title )
{
	strcpy_s( m_title, TITLE_SIZE, title );
	
}

//===========================================================================
/*!	@brief		�^�C�g���擾
	@param		----
	@return		----
*/
//===========================================================================
const char* DebugItemChunk::GetTitle( void ) const
{

	return m_title;
}



//===========================================================================
/*!	@brief		�A�C�e���̒ǉ�
	@param		�Z�b�g�A�C�e��
	@return		----
*/
//===========================================================================
void DebugItemChunk::AddItem( DebugItemInterface* item )
{
	_AddItem( item );
}



//===========================================================================
/*!	@brief		�A�C�e���̃Z�b�g
	@param		items		�A�C�e���z��
	@param		arysize		�T�C�Y
	@return		----
*/
//===========================================================================
//void DebugItemChunk::SetItem( const DebugItem* items[], u32 arysize )
//{
//	for( u32 itemNo = 0; itemNo < arysize; ++itemNo ) {
//		_AddItem( items[itemNo], items[itemNo]->itemName, items[itemNo].variableStr, items[itemNo].nowNo );
//	}
//}


//===========================================================================
/*!	@brief		�A�C�e���̍폜
	@param		obj		�폜�I�u�W�F�N�g
	@return		----
*/
//===========================================================================
void DebugItemChunk::DeleteItem( void* callobj )
{
	VecItem::iterator	itr	= m_items.begin();
	for( ; itr != m_items.end(); ) {
		if( (*itr)->IsEqualObject( callobj ) ) {
			SafeDelete( *itr );
			itr	= m_items.erase( itr );
		}
		else {
			++itr;
		}
	}
	
}


//===========================================================================
/*!	@brief		�A�C�e���̒ǉ�
	@param		item			����
	@return		----
*/
//===========================================================================
void DebugItemChunk::_AddItem( DebugItemInterface* item )
{
	if( item ) {
	 	m_items.push_back( item );

		// �ő啶�����擾
		m_maxItemTitleStrLength	= math::Max( static_cast<size_t>(m_maxItemTitleStrLength), strlen( item->GetItemName() ) );

		m_titleSelector.SetMaxSelectNo( m_items.size() );
	}
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void DebugItemChunk::Update( void )
{
	m_keyboard->Update();
	m_titleSelector.Update();
	m_nowLine	= m_titleSelector.GetSelectNo();
	m_valueSelector.Update();
	m_valueSelector.SetNowSelectNo( SELECT_VALUE_NOT_SELECT );

}


//===========================================================================
/*!	@brief		���ڃZ���N�g�R�[���o�b�N
	@param		----
	@return		----
*/
//===========================================================================
void DebugItemChunk::_ItemSelectCallback( s32 selectNo )
{
	ASSERT( selectNo != SELECT_VALUE_NOT_SELECT, "error" );

	// ��
	if( selectNo == SELECT_VALUE_PUSH_LEFT ) {
		DebugItemInterface* item	= m_items[m_nowLine];
		item->CallDebugFunc( m_nowLine, CALL_EVENT_MUNUS );
	}
	// �E
	else if( selectNo == SELECT_VALUE_PUSH_RIGHT ) {
		DebugItemInterface* item	= m_items[m_nowLine];
		item->CallDebugFunc( m_nowLine, CALL_EVENT_PLUS );
	}
	
}



//===========================================================================
/*!	@brief		���ڌ���R�[���o�b�N
	@param		----
	@return		----
*/
//===========================================================================
void DebugItemChunk::_ItemDecideCallback( s32 selectNo )
{
	ASSERT( selectNo == SELECT_VALUE_NOT_SELECT, "error" );

	DebugItemInterface* item	= m_items[m_nowLine];
	item->CallDebugFunc( m_nowLine, CALL_EVENT_DECIDE );
	
}


//===========================================================================
/*!	@brief		�`��
	@param		pos		�\���I�t�Z�b�g
	@return		----
*/
//===========================================================================
void DebugItemChunk::Draw( const math::Vector& offset )
{
// 	AUTO_TIME( DebugItemChunk );
	
	const s32	lineHeight	= 16;
	const s32	nowSelectNo	= m_titleSelector.GetSelectNo();
	
	char		space[128]	= { 0 };
	s32			titleLength	= 0;
	s32			spaceIdx	= 0;
	
	for( u32 i = 0; i < m_items.size(); ++i ) {
		titleLength	= strlen( m_items[i]->GetItemName() );
		const char*	selectStr	= (nowSelectNo == i) ? ">" : " ";

		// �X�y�[�X�𖄂߂�
		memset( space, ' ', m_maxItemTitleStrLength - titleLength + 1 );
		space[m_maxItemTitleStrLength - titleLength + 1 + 1]	= '\0';
		
		SystemPrint( offset.x, offset.y + lineHeight * i, "%s%s%s: %s", selectStr, m_items[i]->GetItemName(), space, m_items[i]->GetDispValue().c_str() );
	}
}


}	// namespace debug
}	// namespace nk