//=============================================================================
/*!	@file	system.h

	@brief	メインクラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __SYSTEM_H__
#define __SYSTEM_H__


#include <new.h>
#include <new>
#include <string>
#include <iostream>
#include <list>
#include <vector>

#include "./typedef.h"

#include "./general.h"
#include "./utility/utility.h"

#include "./debug/debugfunction.h"
#include "./debug/layoutChanger.h"


#include "./project.h"

#include "./system/window.h"
#include "./system/camera.h"
#include "./system/cameraManager.h"
#include "./system/task.h"
#include "./system/treeTask.h"
#include "./system/listTask.h"
#include "./system/taskManager.h"
#include "./system/framerateCalclator.h"

#include "./font/font.h"
#include "./font/fontRenderer.h"

#include "./math/math.h"
#include "./math/vector.h"
#include "./math/matrix.h"

#include "./graphics/attitude.h"

#include "./collision/boundaryVolume.h"

#include "./input/keyboard.h"
#include "./input/mouse.h"
#include "./system/eventGetter.h"
#include "./system/mouseEventGetter.h"
#include "./system/keyboardEventGetter.h"
#include "./system/systemEventGetter.h"

#include "./graphics/graphics.h"
#include "./resource/material.h"
#include "./resource/texture.h"
#include "./resource/resourceLoader.h"
#include "./render/renderManager.h"
#include "./resource/resourcemanager.h"
#include "./shader/shader.h"
#include "./shader/phongShader.h"
#include "./shader/shadowMapping.h"
#include "./render/screenManager.h"
#include "./render/drawPacketManager.h"
#include "./sound/soundManager.h"

#include "./resource/renderableTexture.h"

#include "./thread/thread.h"

#include "./net/socketUtility.h"
#include "./net/socket.h"
#include "./net/socketManager.h"
#include "./net/packetReceiver.h"
#include "./net/socketReceiver.h"


#pragma warning(disable:4996)
#pragma warning(disable:4985)


#if 1
	#define	nekolibPrintf		printf
#else
	#define	nekolibPrintf(...)	((void)0)
#endif

//! デバッグ描画
#if defined(_DEBUG)
	#define DISP_PRINT			SystemPrint
#else
	//#define DISP_PRINT(...)		(void)0
	#define DISP_PRINT(...)		SystemPrint
#endif



#define DISP_DRAW_TIME_CONSOLE

namespace nk {
//namespace system {

//----------------------------------構造体----------------------------------
/*! 初期化パラメータ */
struct InitParam {
	s32			argc;					//!<	プログラム引数
	char**		argv;					//!<	プログラム引数
	f32			screenWidth;			//!<	スクリーン横幅
	f32			screenHeight;			//!<	スクリーン縦幅
	u32			frameRate;				//!<	フレームレート
	bool		fullScreen;				//!<	フルスクリーン
	char		strApplicationName[50];	//!<	アプリケーション名

	InitParam( s32 param1, char** param2, f32 screenWidth, f32 screenHeight, u32 frameRate, bool fullScreen, const char* appName )
	{
		this->argc				= param1;
		this->argv				= param2;
		this->screenWidth		= screenWidth;
		this->screenHeight		= screenHeight;
		this->frameRate			= frameRate;
		this->fullScreen		= fullScreen;
		strcpy( this->strApplicationName, appName );
	}

};





//=============================================================================
/*!
							  システムクラス
*/
//=============================================================================
class Main {
public:
	//-----------------------型定義--------------------------
	
	
	//----------------------静的メンバ-----------------------
	static const f32	DEFAULT_SCREEN_WIDTH;			//!< 初期スクリーン幅(1024)
	static const f32	DEFAULT_SCREEN_HEIGHT;			//!< 初期スクリーン高さ(768)
	static const s32	DEFAULT_FRAME_RATE;				//!< デフォルトフレームレート(30FPS)
	static const s32	DEBUG_SCREEN_ID			= 0xFF;	//!< デバッグスクリーン
	static const s32	SYSTEM_FONT_SIZE;				//!< フォントサイズ
	
	enum eSCREEN_ID {
		eSCREEN_ID_DEFAULT,			//!< デフォルトスクリーン
		eSCREEN_ID_USER,			//!< 使用者はスクリーンIDをこれ以降に設定する
	};

	enum SYSTEM_EVENT {
		SYSTEM_EVENT_EXIT,		//!< 終了
	};

	//-----------------------メソッド------------------------
	
	//-------------コンストラクタ・デストラクタ--------------
	Main( s32 argc = 0, char** argv = NULL, f32 screenWidth = DEFAULT_SCREEN_HEIGHT, f32 screenHeight = DEFAULT_SCREEN_HEIGHT, u32 frameRate = DEFAULT_FRAME_RATE, bool fullScreen = false, const char* appName = "" );
	virtual ~Main();

	
	//! 実行
	virtual void				Run( void );

	//! フレームコールバック
	void						UpdateCallback( void );

	//! 終了
	void						Exit( void );

	//! システムイベントコールバック
	virtual void				CallbackEvent( SYSTEM_EVENT event ) {}
	

	//! スクリーンの幅を取得
	f32							GetScreenWidth( void ) const;

	//! スクリーンの高さを取得
	f32							GetScreenHeight( void ) const;

	//! スクリーンデプスを取得
	f32							GetScreenDepth( void ) const;
	
	//! 軸を描画
	void						DrawAxis( void );

	//! 2Dモードに変更
	void						ChangeMode2D( void );

	//! 3Dモードに変更
	void						ChangeMode3D( void );

	//! 更新ミリ秒を習得
	u32							GetUpdateIntervalMillSec( void ) const;

	//! 視野角を変更(初期値は45度)
	//void						ChangeFieldOfVision( f32 deg );

	//! ビューポート行列を習得
	//math::Matrix44				GetViewPortMatrix( void ) const;

	//! シェーダーを読込み
	void						LoadShader( graphics::Shader* shader, std::string path, std::string name );

	//! カメラマネージャを習得
	system::CameraManager*		GetCameraManager( void ) const;

	//! リソース管理を習得
	resource::ResourceManager*	GetResourceManager( void ) const;

	//! スクリーンを習得
	ScreenManager*				GetScreen( void ) const;

	//! プロセスインスタンスを習得
	static NK_PROCESS_INSTANCE	GetProcessInstance( void );

	//! スクリーン座標変換行列を習得
	math::Matrix44				GetPerspectiveFieldOfView( void ) const;

	//! ウインドウハンドルを習得
	NK_WINDOW_HANDLE			GetWindowHandle( void ) const;

	//! ウインドウの習得
	Window*						GetWindow( void ) const;

	//! タスクマネージャー
	system::TaskManager*		GetTaskManager( void ) const;

	//! システムフォントレンダラ
	font::FontRenderer*			GetFontRenderer( void ) const;

	//! キーボード取得
	input::Keyboard*			GetKeyboard( void ) const;

	//! マウス取得
	input::Mouse*				GetMouse( void ) const;

protected:		
	//-----------------------メソッド------------------------

	//! 初期化
	virtual bool				Initialize( void );

	//! 更新
	virtual bool				Update( void ) { return true; }

	//! 終了処理
	virtual void				Terminate( void );

	/**		描画前処理
	
		@param	----
		@retval	----
		\note	描画前後に呼ばれる。
				デフォルトでは画面クリアが呼ばれる
	*/
	virtual	void				DrawInitialize( void );


	/**		描画後処理
	
		@param	----
		@retval	----
		\note	デフォルトでは軸描画が呼ばれる
	*/
	virtual void				DrawTerminate( void );


	//! イベント習得
	virtual bool				ObtainEvent( void );

	//! 終了ならtrue
	bool						IsExit( void ) const;
	
	
	//----------------------メンバ変数-----------------------
	//nk::math::Matrix44			m_PFOVmatrix;		//!< スクリーン変換行列
	nk::input::Keyboard*		m_keyboard;				//!< キーボード
	nk::input::Mouse*			m_mouse;				//!< マウス
	resource::ResourceManager*	m_resourceMng;			//!< リソース管理
	system::CameraManager*		m_cameraMng;			//!< カメラ管理
	graphics::RenderManager*	m_drawMng;				//!< 描画管理
	ScreenManager*				m_screenMng;			//!< スクリーン
	Window*						m_window;				//!< ウインドウ
	system::TaskManager*		m_taskMng;				//!< タスクマネージャー
	net::SocketManager*			m_socketMng;			//!< ソケット管理
	graphics::DrawPacketManager*m_drawPacketMng;		//!< 描画パケット管理

	font::Font					m_systemFont;			//!< システムフォント
	font::FontRenderer*			m_fontRenderer;			//!< フォントレンダラ
	system::MouseEventGetter	m_mouseEventGetter;		//!< マウスイベント取得
	system::KeyboardEventGetter	m_keyboardEventGetter;	//!< マウスイベント取得
	system::SystemEventGetter	m_systemEventGetter;	//!< マウスイベント取得
	graphics::Line				m_line;					//!< 線描画
	
private:		
	//-----------------------メソッド------------------------

	//! 初期化
	bool	_Init( void );

	//! 終了処理
	void	_Term( void );

	//! フレームウェイト
	void	_FrameWait( void );

	//! システムの初期化
	bool	_InitSystem( void );

	//! ウインドウの初期化
	bool	_InitWindow( void );

	//! オーディオの初期化
	bool	_InitAudio( void );

	//! プログラムパラメーターをセット
	bool	_InitApplicationParameter( void );

	//! ループ
	void	_Loop( void );

	//! ループ内更新
	bool	_UpdateFrame( void );

	//! 更新フレームならtrue
	bool	_Updateable( void ) const;

	//! SDLのイベントを取得
	bool	_ObtainSDLEvent( void );



	//! GLの初期化
	bool	_InitWinGL( void );

	//! 描画バッファ入れ替え
	void	_SwapBuffers( void );

	//----------------------メンバ変数-----------------------
	nk::InitParam			m_initParam;			//!< 初期化パラメータ
	u32						m_prevTime;				//!< 前回の時間(フレームウェイトに使用)
	FramerateCalclator		m_framerateCalclator;	//!< フレームレート計測
	bool					m_exit;					//!< 終了フラグ

#ifdef _WIN32
	HDC						m_hDC;				//!< 
	HGLRC					m_hRC;				//!< 
	HDC						m_hOldDC;			//!< 
	HGLRC					m_hOldRC;			//!< 
#endif
	

};


//! 描画リストにバッファクリア処理を挿入
// void				AddListForBufferClear( u32 priority );

//! システム文字列描画
void				SystemPrint( s32 x, s32 y, 				const char* fmt, ... );
void				SystemPrint( s32 x, s32 y, Color color, const char* fmt, ... );


//}	// namespace system
}	// namespace nk





#endif  // __SYSTEM_H__