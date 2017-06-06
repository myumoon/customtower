//=============================================================================
/*!	@file	gameDef.h

	@brief	ゲーム定義

	@author	ryunosuke ide
	@date	2013.05.23
*/
//=============================================================================


#ifndef __GAME_DEF_H__
#define __GAME_DEF_H__

#include "math/vector.h"


//! ホスト検索用ポート(ホスト→サーバー)
const u32				PORT_FIND_HOST_CLIENT_TO_SERVER	= 50001;

//! ホスト検索用ポート(サーバー→ホスト)
const u32				PORT_FIND_HOST_SERVER_TO_CLIENT	= 50002;

//! ゲーム通信用ポート
const u32				GAME_PORT						= 50003;		

//! 対戦時入力遅延フレーム
const u32				BATTLE_INPUT_DELAY_FRAME		= 5;

//! 軸
const nk::math::Vector	GAME_AXIS_X						= nk::math::Vector( 1.0f, 0.0f, 0.0f );
const nk::math::Vector	GAME_AXIS_Y						= nk::math::Vector( 0.0f, 1.0f, 0.0f );
const nk::math::Vector	GAME_AXIS_Z						= nk::math::Vector( 0.0f, 0.0f, 1.0f );


//! 描画優先度
enum RENDER_PRIORITY {
	RENDER_PRIORITY_BATTLE_BASE		= 0x001000,
	RENDER_PRIORITY_STAGE			= RENDER_PRIORITY_BATTLE_BASE + 0x000100,
	RENDER_PRIORITY_CHARACTER		= RENDER_PRIORITY_BATTLE_BASE + 0x000200,
	RENDER_PRIORITY_BULLET			= RENDER_PRIORITY_BATTLE_BASE + 0x000300,
	RENDER_PRIORITY_EFFECT_			= RENDER_PRIORITY_BATTLE_BASE + 0x000400,
	RENDER_PRIORITY_,
};

#endif  // __GAME_DEF_H__
