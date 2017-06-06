//=============================================================================
/*!	@file	debugMenu.h

	@brief	デバッグメニュー

	@author	ryunosuke ide
	@date	2013.06.15
*/
//=============================================================================


#ifndef __DEBUG_MENU_H__
#define __DEBUG_MENU_H__

#include <vector>
#include "./debugItemChunk.h"
#include "./debugEventListener.h"

namespace nk {

namespace input {
class Keyboard;
}

namespace debug {

class DebugItemChunk;
class DebugEventListener;

//=============================================================================
/*!
								
*/
//=============================================================================
class DebugMenu {
public:
	//-----------------------型定義--------------------------
	typedef std::vector<DebugItemChunk*>	VecItemChunk;	//!< 項目まとまり

	//----------------------静的メンバ-----------------------
	static const s32	DISP_TITLE_SLIDE_NUM	= 2;
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		項目まとまり追加
	*/
	//===========================================================================
	void	AddItemChunk( u32 lineNo, const char* title );
	void	AddItemChunk( u32 lineNo, DebugItemChunk* itemChunk );

	//===========================================================================
	/*!	@brief		アイテム削除
	*/
	//===========================================================================
	void	DeleteItemChunk( u32 lineNo );
	void	DeleteItemChunkAll( void );
	
	//===========================================================================
	/*!	@brief		項目追加
	*/
	//===========================================================================
	void	AddItem( u32 addLineNo, DebugItemInterface* addItem );

	//===========================================================================
	/*!	@brief		ライン削除
	*/
	//===========================================================================
//	void	DeleteItem( void* callobj );

	//===========================================================================
	/*!	@brief		アイテム削除
	*/
	//===========================================================================
//	void	DeleteItems( void );

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	void	Update( void );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	void	Draw( void );

	//===========================================================================
	/*!	@brief		描画位置設定
	*/
	//===========================================================================
	void	SetPos( s32 x, s32 y );

	//===========================================================================
	/*!	@brief		最大表示数設定
	*/
	//===========================================================================
	void	SetMaxDispNum( s32 maxDispNum );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//===========================================================================
	/*!	@brief		アイテム追加
	*/
	//===========================================================================
	void	_AddItemChunk( u32 lineNo, DebugItemChunk* itemChunk );

	//===========================================================================
	/*!	@brief		ダミーならtrueを返す
	*/
	//===========================================================================
	bool	_IsDummy( const DebugItemChunk* item ) const;

	//===========================================================================
	/*!	@brief		選択時コールバック
	*/
	//===========================================================================
	void	_ItemChunkSelectCallback( s32 selectNo );

	//===========================================================================
	/*!	@brief		決定時コールバック
	*/
	//===========================================================================
	void	_ItemChunkDecideCallback( s32 selectNo );

	//===========================================================================
	/*!	@brief		最大タイトル長を取得
	*/
	//===========================================================================
	s32		_GetMaxTitleLength( void );

	//----------------------メンバ変数-----------------------
	VecItemChunk					m_items;			//!< 項目まとまり
	DebugItemChunk					m_dummy;			//!< ダミー表示用
	input::Keyboard*				m_keyboard;			//!< キーボード	
	s32								m_nowLine;			//!< 現在表示項目
	s32								m_dispStartLine;	//!< 表示開始位置
	s32								m_dispMax;			//!< 表示項目数
	Selector<DebugMenu>				m_itemSelector;		//!< アイテムセレクタ
	DebugItemChunk*					m_activeItemChunk;	//!< アクティブアイテム
	math::Vector					m_pos;				//!< 表示位置
	bool							m_dispAll;			//!< 全部表示ならtrue

public:
	//-------------コンストラクタ・デストラクタ--------------
			DebugMenu();
	virtual~DebugMenu();
};
	
}	// namespace debug
}	// namespace nk

#endif  // __DEBUG_MENU_H__