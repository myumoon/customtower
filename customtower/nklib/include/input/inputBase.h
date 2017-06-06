//=============================================================================
/*!	@file	inputBase.h

	@brief	入力基底クラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __INPUTBASE_H__
#define __INPUTBASE_H__


//-------------------------------インクルード-------------------------------
#include <assert.h>

#include "../typedef.h"


namespace nk {
namespace input {

/* 入力デバイスの種類 */
typedef u32 INPUT_KIND;



//=============================================================================
/*!
                              入力基底クラス
*/
//=============================================================================
class Input {
public:
	//-----------------------型定義--------------------------
	enum ButtonPress {
		NONE		= 0,
		PRESS		= 1<<0,		//!< 押している
		RELEASE		= 1<<1,		//!< 離している
		PRESSED		= 1<<2,		//!< 押した
		RELEASED	= 1<<3,		//!< 離した

		USER_SHIFT	= 4,		//!< ユーザー使用
	};
	typedef u32 ButtonState;	// ボタンの状態


	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	//! 入力種類をセット
	void			SetKind( INPUT_KIND kind ) { m_kind = kind; }
	
	//! 入力種類を取得
	INPUT_KIND		GetKind() const { return m_kind; }

	//!	更新
	virtual void	Update() = 0;

	//! 押されているかどうかの判定
	virtual bool	IsPress( s32 i ) const = 0;

	//! 前回のフレームでは離されていて今のフレームでは押されているかどうかの判定
	virtual bool	IsPressed( s32 i ) const = 0;

	//! 離しているかどうかの判定
	virtual bool	IsRelease( s32 i ) const = 0;

	//! 前のフレームで押していて今のフレームで離されたかどうかの判定
	virtual bool	IsReleased( s32 i ) const = 0;

private:
	//----------------------メンバ変数-----------------------
	INPUT_KIND				m_kind;					// デバイスの種類
	
	
	//-----------------------メソッド------------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			 Input();
	virtual ~Input();
};



}	// namespace input
}	// namespace nk



#endif  // __INPUTBASE_H__