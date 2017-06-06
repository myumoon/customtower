//=============================================================================
/*!	@file	characterCode.h
	@brief	�����R�[�h

	@author	ryunosuke ide
	@date	2013.12.12

	@note	http://shnya.jp/moin/nmh
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../private/nmh.h"
#include "../include/general.h"
#include "../include/utility/characterCode.h"


//--------------------------------define��`--------------------------------


//--------------------------------static�ϐ�--------------------------------


//--------------------------------static�֐�--------------------------------


//---------------------------------�֐���`---------------------------------

namespace nk {

	
//===========================================================================
/*!	@brief		�����R�[�h����
	@param		text	�e�L�X�g�f�[�^
	@param		size	�e�L�X�g�f�[�^�T�C�Y
	@return		�����R�[�h(���ʏo���Ȃ������ꍇ�� CHARACTER_CODE_UNKOWN ���Ԃ�܂�)
*/
//===========================================================================
CHARACTER_CODE ParseCharacterCode( const u8* text, u32 size )
{
	struct CharCodeMap {
		NMH_CHAR_CODE	mnhCode;
		CHARACTER_CODE	nkCode;
	};
	const CharCodeMap	codeMap[]	= {
		{ NMH_CHAR_CODE_JIS,			CHARACTER_CODE_JIS		},
		{ NMH_CHAR_CODE_UTF8,			CHARACTER_CODE_UTF8		},
		{ NMH_CHAR_CODE_UTF8N,			CHARACTER_CODE_UTF8N	},
		{ NMH_CHAR_CODE_UTF16BE,		CHARACTER_CODE_UTF16BE	},
		{ NMH_CHAR_CODE_UTF16LE,		CHARACTER_CODE_UTF16LE	},
		{ NMH_CHAR_CODE_UTF32BE,		CHARACTER_CODE_UTF32BE	},
		{ NMH_CHAR_CODE_UTF32LE,		CHARACTER_CODE_UTF32LE	},
		{ NMH_CHAR_CODE_SJIS,			CHARACTER_CODE_SJIS		},
		{ NMH_CHAR_CODE_EUC,			CHARACTER_CODE_EUC		},
		{ NMH_CHAR_CODE_ASCII,			CHARACTER_CODE_ASCII	},
		{ NMH_CHAR_CODE_UNKNOWN,		CHARACTER_CODE_UNKOWN	},
	};
	
	const NMH_CHAR_CODE	code	= nmh_code_detect( reinterpret_cast<const char*>(text), size );
	
	for( u32 i = 0; i < ARRAY_SIZE(codeMap); ++i ) {
		if( codeMap[i].mnhCode == code ) {
			return codeMap[i].nkCode;
		}
	}
	
	return CHARACTER_CODE_UNKOWN;
}
	
}	// namespace nk
