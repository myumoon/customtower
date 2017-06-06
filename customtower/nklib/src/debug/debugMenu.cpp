//=============================================================================
/*!	@file	debugMenu.cpp

	@brief	デバッグメニュー

	@author	ryunosuke ide
	@date	2013.06.15
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/debug/debugMenu.h"
#include "../../include/general.h"
#include "../../include/input/keyboard.h"
#include "../../include/math/math.h"
#include "../../include/system.h"
#include "../../include/utility/autoTime.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {
namespace debug {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
DebugMenu::DebugMenu()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
DebugMenu::~DebugMenu()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void DebugMenu::_Init( void )
{
	m_activeItemChunk	= NULL;
	
	// 行設定
	m_nowLine			= 0;
	m_dispStartLine		= 0;
	m_dispMax			= 1;
	m_dispAll			= true;

	m_items.reserve( 128 );
	
	// キーボード設定
	m_keyboard			= NULL;
	m_keyboard			= new input::Keyboard();

	// セレクタ設定
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

	// ダミー設定
	m_dummy.SetTitle("----");
	
}


//===========================================================================
/*!	@brief	終了処理
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
/*!	@brief		項目まとまり追加
	@param		lineNo		追加行
	@param		title		表示タイトル
	@return		----
*/
//===========================================================================
void DebugMenu::AddItemChunk( u32 lineNo, const char* title )
{
	_AddItemChunk( lineNo, new DebugItemChunk( title ) );
}


//===========================================================================
/*!	@brief		項目まとまり追加
	@param		lineNo		追加行
	@param		itemChunk	まとまり
	@return		----
*/
//===========================================================================
void DebugMenu::AddItemChunk( u32 lineNo, DebugItemChunk* itemChunk )
{
	_AddItemChunk( lineNo, itemChunk );
}


//===========================================================================
/*!	@brief		項目まとまり追加
	@param		lineNo		追加行
	@param		itemChunk	まとまり
	@return		----
*/
//===========================================================================
void DebugMenu::_AddItemChunk( u32 lineNo, DebugItemChunk* itemChunk )
{
	if( m_items.size() <= lineNo ) {

		u32	prevItemTail	= m_items.size();
		m_items.resize( lineNo + 1 );

		// NULL初期化しておく
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
/*!	@brief		項目まとまり削除
	@param		lineNo	削除行
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
/*!	@brief		項目まとまり削除
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
/*!	@brief		アイテム追加
	@param		addLineNo	追加行
	@param		addItem		追加アイテム
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
/*!	@brief		更新
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

	// 選択されていたら選択項目を操作
	if( m_activeItemChunk ) {
		m_activeItemChunk->Update();
	}
	// 選択されていなかったらメニュー操作
	else {
		m_itemSelector.Update();
	}
	
	
}


//===========================================================================
/*!	@brief		描画
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
/*!	@brief		描画位置設定
	@param		x, y	座標
	@return		----
*/
//===========================================================================
void DebugMenu::SetPos( s32 x, s32 y )
{
	m_pos.SetVector( static_cast<f32>(x), static_cast<f32>(y), 0.0f );
	
}


//===========================================================================
/*!	@brief		最大表示数設定
	@param		dispNum		表示数
	@return		----
*/
//===========================================================================
void DebugMenu::SetMaxDispNum( s32 maxDispNum )
{
	m_dispMax	= maxDispNum;
	m_dispAll	= false;
}

//===========================================================================
/*!	@brief		ダミーアイテムならtrueを返す
	@param		item		チェックアイテム
	@return		----
*/
//===========================================================================
bool DebugMenu::_IsDummy( const DebugItemChunk* item ) const
{
	return item == &m_dummy;
}

//===========================================================================
/*!	@brief		選択時コールバック
	@param		selectNo	選択番号
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

		// 一番下に行く前にリストをスライドさせる
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

		// 一番上に行く前にリストをスライドさせる
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
/*!	@brief		決定時コールバック
	@param		selectNo	選択番号
	@return		----
*/
//===========================================================================
void DebugMenu::_ItemChunkDecideCallback( s32 selectNo )
{
	m_activeItemChunk	= m_items[selectNo];
}


//===========================================================================
/*!	@brief		最大タイトル長を取得
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
