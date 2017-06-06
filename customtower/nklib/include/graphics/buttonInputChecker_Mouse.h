//=============================================================================
/*!	@file	buttonInputChecker_Mouse.h

	@brief	ボタン用マウス入力チェック

	@author	ryunosuke ide
	@date	2013.06.08
*/
//=============================================================================

#ifndef __BUTTON_INPUT_CHECKER_MOUSE_H__
#define __BUTTON_INPUT_CHECKER_MOUSE_H__

#include "button.h"
#include "../input/input.h"

namespace nk {

namespace graphics {

//=============================================================================
/*!
							ボタン用マウス入力チェック
*/
//=============================================================================
class ButtonInputChecker_Mouse : public Button::EventChecker {
public:
	//-----------------------型定義--------------------------
	static const	s32	INPUT_CHECK_BUTTON	= input::Mouse::CLICK_LEFT;
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	virtual void	Initialize( const input::Mouse* mouse );

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
// 	virtual void	Update( void );

	//===========================================================================
	/*!	@brief		アクティブ？
	*/
	//===========================================================================
	virtual bool	IsActive( const CheckInfo& info ) const;


	//===========================================================================
	/*!	@brief		押されている？
	*/
	//===========================================================================
	virtual bool	IsPress( void ) const;
	
	
private:
	//-----------------------メソッド------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------メンバ変数-----------------------
	const input::Mouse*		m_mouse;		//! マウス

public:
	//-------------コンストラクタ・デストラクタ--------------
			ButtonInputChecker_Mouse( const input::Mouse* mouse );
			ButtonInputChecker_Mouse();
	virtual~ButtonInputChecker_Mouse();
};


// void						InitializeDefaultButtonInputChecker_Mouse( const input::Mouse* mouse );
// void						TerminateDefaultButtonInputChecker_Mouse( void );
// ButtonInputChecker_Mouse*	GetDefaultButtonInputChecker_Mouse( void );
	
}	// namespace graphics
	
}	// namespace nk





#endif  // __BUTTON_INPUT_CHECKER_MOUSE_H__