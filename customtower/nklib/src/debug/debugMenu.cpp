//=============================================================================
/*!	@file	debugMenu.cpp

	@brief	�f�o�b�O���j���[

	@author	ryunosuke ide
	@date	2013.06.15
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/debug/debugMenu.h"
#include "../../include/general.h"
#include "../../include/input/keyboard.h"
#include "../../include/math/math.h"
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
DebugMenu::DebugMenu()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
DebugMenu::~DebugMenu()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void DebugMenu::_Init( void )
{
	m_activeItemChunk	= NULL;
	
	// �s�ݒ�
	m_nowLine			= 0;
	m_dispStartLine		= 0;
	m_dispMax			= 1;
	m_dispAll			= true;

	m_items.reserve( 128 );
	
	// �L�[�{�[�h�ݒ�
	m_keyboard			= NULL;
	m_keyboard			= new input::Keyboard();

	// �Z���N�^�ݒ�
	m_itemSelector.Setup<UpdateRepeat>(
		0,
		m_keyboard,
		input::Keyboard::KEY_UP,
		input::Keyboard::KEY_DOWN,
		input::Keyboard::KEY_ENTER
	);
	m_itemSelector.SetCallbackReceiver( this );
	m_itemSelector.SetOnSelectCallback( &DebugMenu::_ItemChunkSelectCallback );
	m_itemSelector.SetDecideCallback( &DebugMenu::_ItemChunkDecideCallback );

	// �_�~�[�ݒ�
	m_dummy.SetTitle("----");
	
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void DebugMenu::_Term( void )
{
	SafeDelete( m_keyboard );
	DeleteItemChunkAll();
}

//===========================================================================
/*!	@brief		���ڂ܂Ƃ܂�ǉ�
	@param		lineNo		�ǉ��s
	@param		title		�\���^�C�g��
	@return		----
*/
//===========================================================================
void DebugMenu::AddItemChunk( u32 lineNo, const char* title )
{
	_AddItemChunk( lineNo, new DebugItemChunk( title ) );
}


//===========================================================================
/*!	@brief		���ڂ܂Ƃ܂�ǉ�
	@param		lineNo		�ǉ��s
	@param		itemChunk	�܂Ƃ܂�
	@return		----
*/
//===========================================================================
void DebugMenu::AddItemChunk( u32 lineNo, DebugItemChunk* itemChunk )
{
	_AddItemChunk( lineNo, itemChunk );
}


//===========================================================================
/*!	@brief		���ڂ܂Ƃ܂�ǉ�
	@param		lineNo		�ǉ��s
	@param		itemChunk	�܂Ƃ܂�
	@return		----
*/
//===========================================================================
void DebugMenu::_AddItemChunk( u32 lineNo, DebugItemChunk* itemChunk )
{
	if( m_items.size() <= lineNo ) {

		u32	prevItemTail	= m_items.size();
		m_items.resize( lineNo + 1 );

		// NULL���������Ă���
		for( u32 i = prevItemTail; i < m_items.size(); ++i ) {
			m_items[i]	= NULL;
		}
	}
	
	ASSERT( m_items[lineNo] == NULL, "already created." );
	if( m_items[lineNo] == NULL ) {
		m_items[lineNo]	= itemChunk;
	}

	m_itemSelector.SetMaxSelectNo( m_items.size() );
}

//===========================================================================
/*!	@brief		���ڂ܂Ƃ܂�폜
	@param		lineNo	�폜�s
	@return		----
*/
//===========================================================================
void DebugMenu::DeleteItemChunk( u32 lineNo )
{
	INDEX_ASSERT( lineNo, m_items.size(), "index error" );
	
	SafeDelete( m_items[lineNo] );
	m_items.erase( m_items.begin() + lineNo );
}


//===========================================================================
/*!	@brief		���ڂ܂Ƃ܂�폜
	@param		----
	@return		----
*/
//===========================================================================
void DebugMenu::DeleteItemChunkAll( void )
{
	for( u32 i = 0; i < m_items.size(); ++i ) {
		SafeDelete( m_items[i] );
	}
}


//===========================================================================
/*!	@brief		�A�C�e���ǉ�
	@param		addLineNo	�ǉ��s
	@param		addItem		�ǉ��A�C�e��
	@return		----
*/
//===========================================================================
void DebugMenu::AddItem( u32 addLineNo, DebugItemInterface* addItem )
{
	ASSERT( addLineNo < m_items.size(), "error" );
	if( addLineNo < m_items.size() ) {
		m_items[addLineNo]->AddItem( addItem );
	}
}




//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void DebugMenu::Update( void )
{
	m_keyboard->Update();
	
	if( m_keyboard->IsPress(input::Keyboard::KEY_BACKSPACE) ) {
		m_activeItemChunk	= NULL;
	}

	// �I������Ă�����I�����ڂ𑀍�
	if( m_activeItemChunk ) {
		m_activeItemChunk->Update();
	}
	// �I������Ă��Ȃ������烁�j���[����
	else {
		m_itemSelector.Update();
	}
	
	
}


//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void DebugMenu::Draw( void )
{
	const s32	offsetX		= static_cast<s32>(m_pos.x);
	const s32	offsetY		= static_cast<s32>(m_pos.y);
	const s32	lineHeight	= 16;

// 	AUTO_TIME( DebugMenu );
	
	{
		const s32	loopNum			= math::Min( m_dispMax, static_cast<s32>(m_items.size()) );
		s32			dispOffsetCount	= 0;
		for( s32 i = m_dispStartLine; i < m_dispStartLine + loopNum; ++i ) {
			if( m_items[i] ) {
				const char*		selectStr	= (m_nowLine == i) ? ">" : " ";
				SystemPrint( offsetX, offsetY + lineHeight * dispOffsetCount, "%s%s", selectStr, m_items[i]->GetTitle() );
			}
			++dispOffsetCount;
		}
	}
  	

	if( m_activeItemChunk ) {
		const s32	maxTitleLength	= _GetMaxTitleLength();
		m_activeItemChunk->Draw( math::Vector( offsetX + maxTitleLength * 11, offsetY, 0 ) );
	}
}


//===========================================================================
/*!	@brief		�`��ʒu�ݒ�
	@param		x, y	���W
	@return		----
*/
//===========================================================================
void DebugMenu::SetPos( s32 x, s32 y )
{
	m_pos.SetVector( static_cast<f32>(x), static_cast<f32>(y), 0.0f );
	
}


//===========================================================================
/*!	@brief		�ő�\�����ݒ�
	@param		dispNum		�\����
	@return		----
*/
//===========================================================================
void DebugMenu::SetMaxDispNum( s32 maxDispNum )
{
	m_dispMax	= maxDispNum;
	m_dispAll	= false;
}

//===========================================================================
/*!	@brief		�_�~�[�A�C�e���Ȃ�true��Ԃ�
	@param		item		�`�F�b�N�A�C�e��
	@return		----
*/
//===========================================================================
bool DebugMenu::_IsDummy( const DebugItemChunk* item ) const
{
	return item == &m_dummy;
}

//===========================================================================
/*!	@brief		�I�����R�[���o�b�N
	@param		selectNo	�I��ԍ�
	@return		----
*/
//===========================================================================
void DebugMenu::_ItemChunkSelectCallback( s32 selectNo )
{
	printf("DebugMenu::_ItemChunkSelectCallback %d\n", selectNo);
	const bool	isLoop	= math::Abs( m_nowLine - selectNo ) == m_items.size() - 1;
	const s32	itemNum	= static_cast<s32>(m_items.size());

	if( m_nowLine < selectNo ) {
		m_nowLine	= selectNo;

		// ��ԉ��ɍs���O�Ƀ��X�g���X���C�h������
		if( m_dispMax < itemNum ) {
			if( itemNum - DISP_TITLE_SLIDE_NUM <= m_nowLine ) {
			}
			else if( m_dispStartLine + m_dispMax <= m_nowLine + DISP_TITLE_SLIDE_NUM ) {
				m_dispStartLine	= (m_nowLine + DISP_TITLE_SLIDE_NUM) - (m_dispMax - 1);
			}
		}
	}
	else {
		m_nowLine	= selectNo;

		// ��ԏ�ɍs���O�Ƀ��X�g���X���C�h������
		if( m_dispMax < itemNum ) {
			if( m_nowLine < DISP_TITLE_SLIDE_NUM ) {
			}
			else if( m_nowLine - DISP_TITLE_SLIDE_NUM < m_dispStartLine ) {
				m_dispStartLine	= m_nowLine - DISP_TITLE_SLIDE_NUM;
			}
		}
	}

	if( isLoop ) {
		m_nowLine	= selectNo;
		if( selectNo == 0 ) {
			m_dispStartLine	= 0;
		}
		else {
			m_dispStartLine	= m_items.size() - m_dispMax;
		}
	}
	
}



//===========================================================================
/*!	@brief		���莞�R�[���o�b�N
	@param		selectNo	�I��ԍ�
	@return		----
*/
//===========================================================================
void DebugMenu::_ItemChunkDecideCallback( s32 selectNo )
{
	m_activeItemChunk	= m_items[selectNo];
}


//===========================================================================
/*!	@brief		�ő�^�C�g�������擾
	@param		----
	@return		----
*/
//===========================================================================
s32 DebugMenu::_GetMaxTitleLength( void )
{
	const s32	loopNum		= math::Min( m_dispMax, static_cast<s32>(m_items.size()) );
	s32			maxLength	= 0;
	s32			length		= 0;
	
	for( s32 i = m_dispStartLine; i < m_dispStartLine + loopNum; ++i ) {
		if( m_items[i] ) {
			length		= strlen( m_items[i]->GetTitle() );
			maxLength	= math::Max( length, maxLength );
		}
	}

	return maxLength;
}
	
}	// namespace debug
}	// namespace nk
