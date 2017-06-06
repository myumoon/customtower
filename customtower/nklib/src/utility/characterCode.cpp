//=============================================================================
/*!	@file	characterCode.h
	@brief	文字コード

	@author	ryunosuke ide
	@date	2013.12.12

	@note	http://shnya.jp/moin/nmh
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../private/nmh.h"
#include "../include/general.h"
#include "../include/utility/characterCode.h"


//--------------------------------define定義--------------------------------


//--------------------------------static変数--------------------------------


//--------------------------------static関数--------------------------------


//---------------------------------関数定義---------------------------------

namespace nk {

	
//===========================================================================
/*!	@brief		文字コード判別
	@param		text	テキストデータ
	@param		size	テキストデータサイズ
	@return		文字コード(判別出来なかった場合は CHARACTER_CODE_UNKOWN が返ります)
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
