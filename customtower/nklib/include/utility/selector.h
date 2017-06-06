//=============================================================================
/*!	@file	selector.h

	@brief	セレクタ

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include <stdio.h>
#include "selectorUpdater.h"

namespace nk {

namespace input {
class Input;
}


namespace {
class _Dummy {
public:
	 _Dummy() {}
	~_Dummy() {}
};
}

//=============================================================================
/*!
								セレクタ
*/
//=============================================================================
template<typename T = _Dummy>
class Selector {
public:
	//-----------------------型定義--------------------------

	//! イベントコールバック
	typedef void (T::*SelectEventCallback)( s32 selectNo );
	
	static const s32	NOT_SELECTED	= -2;		//!< 未選択


	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		セットアップ
	*/
	//===========================================================================
	template<class Updater>
	void Setup(
		s32					max,					// 選択最大値
		nk::input::Input*	inputChecker,			// 入力チェック
		s32					prevButton,				// 前に戻るボタン
		s32					nextButton,				// 次への入力ボタン	
		s32					decisionButton,			// 決定ボタン
		bool				loop			= true,	// 端ループ
		s32					defaultSelectNo	= 0		// 初期値(-1で未選択)
	)
	{
		m_nowSelectNo		= defaultSelectNo;
		m_maxSelectNo		= max;
		m_loop				= loop;
		m_inputChecker		= inputChecker;
		m_nextButton		= nextButton;
		m_prevButton		= prevButton;
		m_decisionButton	= decisionButton;
		m_cursorUpdater		= new Updater();
	}

	//===========================================================================
	/*!	@brief		更新
		@return		現在選択中の番号
	*/
	//===========================================================================
	bool	Update( void );

	//===========================================================================
	/*!	@brief		現在選択中の番号
	*/
	//===========================================================================
	s32		GetSelectNo( void ) const;

	//===========================================================================
	/*!	@brief		コールバック設定
	*/
	//===========================================================================
	void	SetCallbackReceiver( T* callbackReceiver );
	void	SetOnSelectCallback( SelectEventCallback callbackFunc );	//!< オンになったときコールバック
	void	SetOffSelectCallback( SelectEventCallback callbackFunc );	//!< オフになったときコールバック
	void	SetDecideCallback( SelectEventCallback callbackFunc );		//!< 決定時コールバック

	//===========================================================================
	/*!	@brief		最大番号設定
	*/
	//===========================================================================
	void	SetMaxSelectNo( s32 maxSelectNo );

	//===========================================================================
	/*!	@brief		現在番号設定
	*/
	//===========================================================================
	void	SetNowSelectNo( s32 nowSelectNo );

private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	s32					m_nowSelectNo;			//!< 現在
	s32					m_maxSelectNo;			//!< 最大
	bool				m_loop;					//!< ループ
	input::Input*		m_inputChecker;			//!< 入力チェック
	s32					m_prevButton;			//!< 前に戻るボタン番号
	s32					m_nextButton;			//!< 次に進むボタン番号	
	s32					m_decisionButton;		//!< 決定ボタン
	CursorUpdater*		m_cursorUpdater;		//!< カーソル更新

	//! イベントコールバック
	SelectEventCallback	m_callbackOnSelect;		//!< オン時
	SelectEventCallback	m_callbackOffSelect;	//!< オフ時
	SelectEventCallback	m_callbackDecideSelect;	//!< 決定時
	T*					m_callbackReceiver;		//!< コールバック取得

public:
	//-------------コンストラクタ・デストラクタ--------------
			Selector( T* callbackReceiver );
			Selector();
	virtual~Selector();
};


#include "../../src/utility/selector.cpp"

}	// namespace nk




#endif  // __SELECTOR_H__