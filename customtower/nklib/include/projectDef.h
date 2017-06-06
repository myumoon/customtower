//=============================================================================
/*!	@file	projectDef.h

	@brief	プロジェクトタイプ定数群

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __PROJECTDEF_H__
#define	__PROJECTDEF_H__


//===========================================================================
/*!
	プロジェクトタイプ

	各種プロジェクトタイプの設定に応じてコードが変化する。
	タイプ専用処理は必ずプロジェクトタイプで判定する事
*/
//===========================================================================
enum
{
	PROJECT_TYPE_WIN32,		//!<	32bitウィンドウズ
	PROJECT_TYPE_WIN64,		//!<	64bitウィンドウズ
	PROJECT_TYPE_PS2,		//!<	PlayStation2
	PROJECT_TYPE_PS3,		//!<	PlayStation3
	PROJECT_TYPE_PSP,		//!<	PlayStationPortable
	PROJECT_TYPE_DS,		//!<	NintendoDS
	PROJECT_TYPE_WII,		//!<	NintendoWii
	PROJECT_TYPE_XBOX,		//!<	XBOX
	PROJECT_TYPE_XBOX360,	//!<	XBOX360
};



//===========================================================================
/*!
	スレッドタイプ

	アプリケーションのスレッドタイプ
*/
//===========================================================================
enum
{
	THREAD_TYPE_SINGLE,		//!<	シングルスレッド
	THREAD_TYPE_MULTI,		//!<	マルチスレッド
};


//===========================================================================
/*!
	グラフィックタイプ

	PS2等のコンシューマではプロジェクトタイプでほぼいけるが、
 	OpenGLとDirectXの様なライブラリ違いがあった時の為に分けておく
*/
//===========================================================================
#define	GRAPHICS_TYPE_OPENGL		0	//!<	OpenGL
#define	GRAPHICS_TYPE_DIRECTX9		1	//!<	DirectX
#define GRAPHICS_TYPE_SDL			2	//!<	SDL
#define GRAPHICS_TYPE_SDL_OPENGL	3	//!<	SDL+OpenGL
#define	GRAPHICS_TYPE_PS2			4	//!<	PlayStation2
#define	GRAPHICS_TYPE_PS3			5	//!<	PlayStation3
#define	GRAPHICS_TYPE_PSP			6	//!<	PlayStationPortable
#define	GRAPHICS_TYPE_DS			7	//!<	NintendoDS
#define	GRAPHICS_TYPE_WII			8	//!<	NintendoWii
#define	GRAPHICS_TYPE_XBOX			9	//!<	XBOX
#define	GRAPHICS_TYPE_XBOX360		10	//!<	XBOX360



//===========================================================================
/*!
	ライセンスエリア

	ターゲットとなる国によって設定が異なる部分があるので、
	ここを変えるだけでシステムが適応するようにする
	主にパッド操作周りか？
*/
//===========================================================================
enum
{
	LICENSE_AREA_JAPAN,	//<!	日本

	LICENSE_AREA_USA,	//<!	アメリカ
	LICENSE_AREA_EURO,	//<!	欧州

	LICENSE_AREA_USEU,	//<!	北米・欧州
};


//===========================================================================
/*
	フレームレート

	基本フレームレート値
*/
//===========================================================================
#define	FRAME_FULL	1	//!<	フルフレーム
#define	FRAME_60	60	//!<	60フレーム
#define	FRAME_30	30	//!<	30フレーム
#define	FRAME_15	15	//!<	15フレーム




#endif	//	__PROJECTDEF_H__