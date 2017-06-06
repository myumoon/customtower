//=============================================================================
/*!	@file	debugItemChunk.h

	@brief	デバッグ項目のまとまり

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
								デバッグ項目
*/
//=============================================================================
class DebugItemChunk {
public:
	//-----------------------型定義--------------------------
	static const s32	TITLE_SIZE				= 128;					//!< タイトル上限

	//! デバッグ項目セレクタ
	enum {
		SELECT_VALUE_PUSH_LEFT,			//!< 値減少
		SELECT_VALUE_NOT_SELECT,		//!< 初期値
		SELECT_VALUE_PUSH_RIGHT,		//!< 値上昇
		
		SELECT_VALUE_MAX,
	};

	typedef std::vector<DebugItemInterface*>	VecItem;
	
	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		タイトル設定
	*/
	//===========================================================================
	void			SetTitle( const char* title );

	//===========================================================================
	/*!	@brief		タイトル取得
	*/
	//===========================================================================
	const char*		GetTitle( void ) const;

	//===========================================================================
	/*!	@brief		項目追加
	*/
	//===========================================================================
//	void			AddItem( s32 itemNo, const char* itemName, const std::string& defaultStr, s32 defaultNo = 0 );
//	void			AddItem( s32 itemNo, const char* itemName, const char*		  defaultStr, s32 defaultNo = 0 );
	void			AddItem( DebugItemInterface* item );
//	void			SetItem( const DebugItem* items[], u32 arysize );

	//===========================================================================
	/*!	@brief		項目削除
	*/
	//===========================================================================
	void			DeleteItem( void* callobj );

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	void			Update( void );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	void			Draw( const math::Vector& offset );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//===========================================================================
	/*!	@brief		アイテム追加
	*/
	//===========================================================================
	void			_AddItem( DebugItemInterface* item );

	//===========================================================================
	/*!	@brief		項目セレクトコールバック
	*/
	//===========================================================================
	void			_ItemSelectCallback( s32 selectNo );

	//===========================================================================
	/*!	@brief		決定コールバック
	*/
	//===========================================================================
	void			_ItemDecideCallback( s32 selectNo );

	//----------------------メンバ変数-----------------------
	char						m_title[TITLE_SIZE];		//!< タイトル
	input::Keyboard*			m_keyboard;					//!< キーボード
	Selector<>					m_titleSelector;			//!< セレクタ(タイトル)
	Selector<DebugItemChunk>	m_valueSelector;			//!< デバッグ変数セレクタ

	VecItem						m_items;					//!< 表示項目
 	s32							m_nowLine;					//!< 操作項目
	s32							m_maxItemTitleStrLength;	//!< 最長タイトル

public:
	//-------------コンストラクタ・デストラクタ--------------
			DebugItemChunk( const char* title, DebugEventListener* listener );
			DebugItemChunk( const char* title );
			DebugItemChunk();
	virtual~DebugItemChunk();
};
	
}	// namespace debug
}	// namespace nk



#endif  // __DEBUG_ITEM_CHUNK_H__