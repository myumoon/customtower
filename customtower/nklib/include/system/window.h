//=============================================================================
/*!	@file	window.h

	@brief	ウインドウを管理するクラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __WINDOW_H__
#define __WINDOW_H__

//-------------------------------インクルード-------------------------------
#include <string>
#if defined(_WINDOWS)
#include <winsock2.h>
#include <windows.h>
#endif

#include "../typedef.h"
#include "../math/matrix.h"


namespace nk {


// ウインドウ更新時コールバック
typedef void (*WindowCallback)(void*);


//=============================================================================
/*!
                              ウインドウクラス
*/
//=============================================================================
class Window {
public:
	
	//-----------------------型定義--------------------------
	struct WindowInfo {
		s32			width;
		s32			height;
		f32			depth;
		bool		fullscreen;
	};
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 初期化
	//void				Initialize(f32 screenWidth, f32 screenHeight);
	bool				Create( s32 width, s32 height, f32 depth, bool fullscreen = false );
	bool				Create( const WindowInfo& info );

	//! ウインドウコールバックをセット
	void				SetWindowCallback( WindowCallback func, void* param );

	//! タイトルをつける
	void				SetTitle(const char* title);

	//! アイコンをセット
	void				SetIcon( const char* iconPath );

	//! プロジェクション変換行列(右手座標)
	void				SetMatrixPerspectiveFovRH();

	//! 幅・高さ・深度の習得
	math::Vector		GetScreenParam( void ) const;

	//! ウインドウハンドルを習得
	NK_WINDOW_HANDLE	GetWindowHandle( void ) const;

	//! ビューポート行列を習得
	math::Matrix44		GetViewPortMatrix( void ) const;
	
	//! ウインドウコールバック
	//static NK_RESULT NK_CALLBACK WndProc(  );
	//LRESULT CALLBACK WndProc( HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
	//static LRESULT CALLBACK WndProc(){}
	
private:
	//----------------------メンバ変数-----------------------
	f32							m_screenWidth;			//!< スクリーンの幅
	f32							m_screenHeight;			//!< スクリーンの高さ
	f32							m_screenDepth;			//!< スクリーン深度
	bool						m_fullScreen;			//!< フルスクリーンフラグ

	NK_WINDOW_HANDLE			m_windowHandle;			//!< ウインドウハンドル
	
#if defined(_WINDOWS)
	WNDCLASS					m_windowClass;			//!< ウインドウ winAPI
#endif
	
	//-----------------------メソッド------------------------
	void				_Initialize( void );
	void				_Finalize( void );
public:
	//-------------コンストラクタ・デストラクタ--------------
			 Window();
	virtual ~Window();
};

}







#endif  // __WINDOW_H__