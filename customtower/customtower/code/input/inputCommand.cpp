//=============================================================================
/*!	@file	inputCommand.h

	@brief	入力コマンド定数群

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================
//#ifndef __INPUTCOMMAND_H__
//#define __INPUTCOMMAND_H__

//-------------------------------インクルード-------------------------------

#include "input/buttonConstant.h"
#include "input/keyboard.h"

namespace {

using namespace nk::input;

/* これを入力確認時の命令として使用する */
enum Command {
	COMMAND_SHIELD,			// シールド
	COMMAND_SHOT1,			// ショット
	COMMAND_MINE,			// 地雷
	COMMAND_SLASH,			// 斬撃
	COMMAND_RUSH,			// 突進
	COMMAND_LOCKON,			// ロックオン
	COMMAND_DECISION,		// 決定
	COMMAND_CANCEL,			// キャンセル
	COMMAND_PAUSE,			// ポーズ

	COMMAND_EDIT_OUTPUT,	// 掃き出し
	COMMAND_EDIT_LOAD,		// 読込み
	COMMAND_EDIT_SET,		// 設置
	COMMAND_EDIT_ANDO,		// アンドゥ
	COMMAND_EDIT_SIZE_UP,	// エディット画面でのサイズアップ
	COMMAND_EDIT_SIZE_DOWN,	// エディット画面でのサイズダウン

	COMMAND_LV_UP,
	COMMAND_LV_DOWN,
	COMMAND_ID_UP,
	COMMAND_ID_DOWN,
	COMMAND_WAIT_UP,
	COMMAND_WAIT_DOWN,
	COMMAND_CREATE,
	COMMAND_ANDO,

	COMMAND_FPS_UP,
	COMMAND_FPS_DOWN,

	COMMAND_EXIT,			// 終了

	COMMAND_MAX,
};



//===============================================
//	ボタン対応表
//===============================================
struct TCommandCorrespondence {
	Command				command;
	PAD_NUM				pad_num;
	Keyboard::KEY_NUM	key_num;
};

const TCommandCorrespondence CC[] = {

	{COMMAND_SHIELD,			PAD_R1,		Keyboard::KEY_Z		},
	{COMMAND_SHOT1,				PAD_RD,		Keyboard::KEY_X		},
	{COMMAND_SLASH,				PAD_RR,		Keyboard::KEY_C		},
	{COMMAND_DECISION,			PAD_RR,		Keyboard::KEY_C		},
	{COMMAND_RUSH,				PAD_RU,		Keyboard::KEY_LCTRL	},
	{COMMAND_MINE,				PAD_RL,		Keyboard::KEY_V		},
	{COMMAND_LOCKON,			PAD_L1,		Keyboard::KEY_SPACE	},
	{COMMAND_PAUSE,				PAD_START,	Keyboard::KEY_ESC	},
	{COMMAND_EXIT,				PAD_SELECT,	Keyboard::KEY_ESC	},

	{COMMAND_FPS_UP,			PAD_LU,		Keyboard::KEY_2		},
	{COMMAND_FPS_DOWN,			PAD_LD,		Keyboard::KEY_1		},

	{COMMAND_EDIT_OUTPUT,		PAD_START,	Keyboard::KEY_ENTER	},
	{COMMAND_EDIT_LOAD,			PAD_SELECT,	Keyboard::KEY_SPACE	},
	{COMMAND_EDIT_SIZE_UP,		PAD_R1,		Keyboard::KEY_X		},
	{COMMAND_EDIT_SIZE_DOWN,	PAD_L1,		Keyboard::KEY_Z		},
	{COMMAND_EDIT_SET,			PAD_RR,		Keyboard::KEY_C		},
	{COMMAND_EDIT_ANDO,			PAD_RD,		Keyboard::KEY_V		},

	{COMMAND_LV_UP,				PAD_L1,		Keyboard::KEY_1		},
	{COMMAND_LV_DOWN,			PAD_L2,		Keyboard::KEY_2		},
	{COMMAND_ID_UP,				PAD_R1,		Keyboard::KEY_3		},
	{COMMAND_ID_DOWN,			PAD_R2,		Keyboard::KEY_4		},
	{COMMAND_WAIT_UP,			PAD_RU,		Keyboard::KEY_5		},
	{COMMAND_WAIT_DOWN,			PAD_RL,		Keyboard::KEY_6		},
	{COMMAND_CREATE,			PAD_RR,		Keyboard::KEY_7		},
	{COMMAND_ANDO,				PAD_RD,		Keyboard::KEY_8		}
};

}	// unnamed

/* 1つのブロックあたりに何個の設定がされているか */
#define CC_SIZE (sizeof(CC) / sizeof(CC[0]))

//#endif  // __INPUTCOMMAND_H__
