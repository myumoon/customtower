//=============================================================================
/*!	@file	layout.h

	@brief	レイアウト

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "layoutEventListener.h"
#include "layoutParts.h"
#include "layoutPartsBox.h"
#include "spriteAnimation.h"
#include "button.h"



namespace nk {

namespace input {
class Mouse;
class Keyboard;
}

namespace graphics {

//=============================================================================
/*!
								レイアウト
*/
//=============================================================================
class Layout {
public:
	//-----------------------型定義--------------------------

	//! パーツ情報
	struct PartsInfo {
		LayoutParts*	parts;		//!< パーツ
		s32				depth;		//!< 深さ

		//! コンストラクタ
		PartsInfo() {
			this->parts	= NULL;
			this->depth	= 0;
		}

		//! 比較
		bool operator ==( const PartsInfo& rhs ) const {
			return this->parts == rhs.parts;
		}

		//! 比較
		bool operator ==( const LayoutParts* rhs ) const {
			return this->parts == rhs;
		}

		bool operator <( const PartsInfo& rhs ) const {
			return this->depth < rhs.depth;
		}
	};

	//! パーツ
	typedef std::vector<PartsInfo>	VecParts;

	//----------------------静的メンバ-----------------------
	static const	s32		KEYBOARD_MOVE_AMOUNT		= 5;		//!< キーボードでの移動量
	static const	s32		CTRL_KEYBOARD_MOVE_AMOUNT	= 1;		//!< ctrl+キーボードでの移動量
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	void			Initialize( const input::Mouse* mouse, const input::Keyboard* keyboard );

	//===========================================================================
	/*!	@brief		セットアップ
	*/
	//===========================================================================
	bool			Setup( const char* layoutFilePath, LayoutEventListener* listener = NULL );

	//===========================================================================
	/*!	@brief		セーブ
	*/
	//===========================================================================
	bool			SaveToFile( const char* outputPath );

	//===========================================================================
	/*!	@brief		ルート取得
	*/
	//===========================================================================
	LayoutPartsBox*	GetRoot( void );

	//===========================================================================
	/*!	@brief		パーツの削除
		@note		deleteします
	*/
	//===========================================================================
	void			DeleteParts( void );

	//===========================================================================
	/*!	@brief		パーツの更新
	*/
	//===========================================================================
	void			UpdateParts( void );

	//===========================================================================
	/*!	@brief		パーツの描画
	*/
	//===========================================================================
	void			DrawParts( void );

	//===========================================================================
	/*!	@brief		パーツの検索
		@attention	同名パーツが合った場合は親のパーツが優先されます。
	*/
	//===========================================================================
	LayoutParts*	FindParts( const char* partsname );

	//===========================================================================
	/*!	@brief		ボックスパーツの検索
	*/
	//===========================================================================
	LayoutPartsBox*	FindPartsBox( const char* partsboxname );


	//===========================================================================
	/*!	@brief		レイアウト変更更新
	*/
	//===========================================================================
	virtual void	UpdateLayoutChange( void );


	//===========================================================================
	/*!	@brief		アクティブパーツの枠を描画
	*/
	//===========================================================================
	void			DrawActivePartsFrame( void );

	//===========================================================================
	/*!	@brief		変更があった場合truyeを返す
	*/
	//===========================================================================
	bool			Changed( void ) const	{ return false; }
	
private:

	//! イベント取得
	//! Layoutには中身を公開
	class EventObserver : public ButtonEventListener {
	private:
		friend class Layout;

		virtual void	OnCursorOver( nk::graphics::Button* eventButton );
		virtual void	OnCursorOut( nk::graphics::Button* eventButton );
		virtual void	OnCursorDownStart( nk::graphics::Button* eventButton );
		virtual void	OnCursorDownEnd( nk::graphics::Button* eventButton );
		virtual void	OnCursorUpStart( nk::graphics::Button* eventButton );
		virtual void	OnCursorUpEnd( nk::graphics::Button* eventButton );
		virtual void	OnHold( nk::graphics::Button* eventButton );

		LayoutEventListener*	m_eventListener;
	};
	
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//===========================================================================
	/*!	@brief		アクティブパーツ追加
	*/
	//===========================================================================
	void			_AddActiveParts( LayoutParts* parts, s32 depth );

	//===========================================================================
	/*!	@brief		アクティブパーツ除外
	*/
	//===========================================================================
	void			_RemoveActiveParts( LayoutParts* parts );

	//===========================================================================
	/*!	@brief		アクティブパーツリセット
	*/
	//===========================================================================
	void			_ClearActiveParts( void );

	//----------------------メンバ変数-----------------------
	LayoutPartsBox			m_root;				//!< ルート
	const input::Mouse*		m_mouse;			//!< マウス
	const input::Keyboard*	m_keyboard;			//!< キーボード
	EventObserver			m_eventObserver;	//!< イベント通知

	math::Vector			m_prevMousePos;		//!< 前回マウス座標
	VecParts				m_activeParts;		//!< 選択中パーツ
	bool					m_moveable;			//!< 移動可能
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			Layout();
			Layout( const nk::input::Mouse* mouse );
	virtual~Layout();
};
	
}	// namespace graphics	
}	// namespace nk



#endif  // __LAYOUT_H__
