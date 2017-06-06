//=============================================================================
/*!	@file	debugItemChunk.h

	@brief	デバッグ項目のまとまり

	@author	ryunosuke ide
	@date	2013.06.15
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <string.h>
#include <stdlib.h>
#include "../../include/debug/debugItemChunk.h"
#include "../../include/debug/debugItem.h"

#include "../../include/utility/utility.h"
#include "../../include/general.h"
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
DebugItemChunk::DebugItemChunk()
{
	_Init();
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	title		タイトル
	@param	listener	イベントリスナー
*/
//===========================================================================
DebugItemChunk::DebugItemChunk( const char* title, DebugEventListener* listener )
{
	_Init();

	SetTitle( title );
	//SetEventListener( listener );
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	title		タイトル
*/
//===========================================================================
DebugItemChunk::DebugItemChunk( const char* title )
{
	_Init();

	SetTitle( title );
}



//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
DebugItemChunk::~DebugItemChunk()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
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
/*!	@brief	終了処理
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
/*!	@brief		タイトル設定
	@param		title	タイトル
	@return		----
*/
//===========================================================================
void DebugItemChunk::SetTitle( const char* title )
{
	strcpy_s( m_title, TITLE_SIZE, title );
	
}

//===========================================================================
/*!	@brief		タイトル取得
	@param		----
	@return		----
*/
//===========================================================================
const char* DebugItemChunk::GetTitle( void ) const
{

	return m_title;
}



//===========================================================================
/*!	@brief		アイテムの追加
	@param		セットアイテム
	@return		----
*/
//===========================================================================
void DebugItemChunk::AddItem( DebugItemInterface* item )
{
	_AddItem( item );
}



//===========================================================================
/*!	@brief		アイテムのセット
	@param		items		アイテム配列
	@param		arysize		サイズ
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
/*!	@brief		アイテムの削除
	@param		obj		削除オブジェクト
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
/*!	@brief		アイテムの追加
	@param		item			項目
	@return		----
*/
//===========================================================================
void DebugItemChunk::_AddItem( DebugItemInterface* item )
{
	if( item ) {
	 	m_items.push_back( item );

		// 最大文字長取得
		m_maxItemTitleStrLength	= math::Max( static_cast<size_t>(m_maxItemTitleStrLength), strlen( item->GetItemName() ) );

		m_titleSelector.SetMaxSelectNo( m_items.size() );
	}
}


//===========================================================================
/*!	@brief		更新
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
/*!	@brief		項目セレクトコールバック
	@param		----
	@return		----
*/
//===========================================================================
void DebugItemChunk::_ItemSelectCallback( s32 selectNo )
{
	ASSERT( selectNo != SELECT_VALUE_NOT_SELECT, "error" );

	// 左
	if( selectNo == SELECT_VALUE_PUSH_LEFT ) {
		DebugItemInterface* item	= m_items[m_nowLine];
		item->CallDebugFunc( m_nowLine, CALL_EVENT_MUNUS );
	}
	// 右
	else if( selectNo == SELECT_VALUE_PUSH_RIGHT ) {
		DebugItemInterface* item	= m_items[m_nowLine];
		item->CallDebugFunc( m_nowLine, CALL_EVENT_PLUS );
	}
	
}



//===========================================================================
/*!	@brief		項目決定コールバック
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
/*!	@brief		描画
	@param		pos		表示オフセット
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

		// スペースを埋める
		memset( space, ' ', m_maxItemTitleStrLength - titleLength + 1 );
		space[m_maxItemTitleStrLength - titleLength + 1 + 1]	= '\0';
		
		SystemPrint( offset.x, offset.y + lineHeight * i, "%s%s%s: %s", selectStr, m_items[i]->GetItemName(), space, m_items[i]->GetDispValue().c_str() );
	}
}


}	// namespace debug
}	// namespace nk