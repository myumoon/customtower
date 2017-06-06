//=============================================================================
/*!	@file	inputCommand.h

	@brief	���̓R�}���h�萔�Q

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================
//#ifndef __INPUTCOMMAND_H__
//#define __INPUTCOMMAND_H__

//-------------------------------�C���N���[�h-------------------------------

#include "input/buttonConstant.h"
#include "input/keyboard.h"

namespace {

using namespace nk::input;

/* �������͊m�F���̖��߂Ƃ��Ďg�p���� */
enum Command {
	COMMAND_SHIELD,			// �V�[���h
	COMMAND_SHOT1,			// �V���b�g
	COMMAND_MINE,			// �n��
	COMMAND_SLASH,			// �a��
	COMMAND_RUSH,			// �ːi
	COMMAND_LOCKON,			// ���b�N�I��
	COMMAND_DECISION,		// ����
	COMMAND_CANCEL,			// �L�����Z��
	COMMAND_PAUSE,			// �|�[�Y

	COMMAND_EDIT_OUTPUT,	// �|���o��
	COMMAND_EDIT_LOAD,		// �Ǎ���
	COMMAND_EDIT_SET,		// �ݒu
	COMMAND_EDIT_ANDO,		// �A���h�D
	COMMAND_EDIT_SIZE_UP,	// �G�f�B�b�g��ʂł̃T�C�Y�A�b�v
	COMMAND_EDIT_SIZE_DOWN,	// �G�f�B�b�g��ʂł̃T�C�Y�_�E��

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

	COMMAND_EXIT,			// �I��

	COMMAND_MAX,
};



//===============================================
//	�{�^���Ή��\
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

/* 1�̃u���b�N������ɉ��̐ݒ肪����Ă��邩 */
#define CC_SIZE (sizeof(CC) / sizeof(CC[0]))

//#endif  // __INPUTCOMMAND_H__
