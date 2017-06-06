//=============================================================================
/*!	@file	characterCode.h
	@brief	文字コード

	@author	ryunosuke ide
	@date	2013.12.12
*/
//=============================================================================

#ifndef __CHARACTER_CODE_H__
#define __CHARACTER_CODE_H__

#include "../typedef.h"

namespace nk {

//! 文字コード
enum CHARACTER_CODE {
    CHARACTER_CODE_JIS,			//!< JIS
    CHARACTER_CODE_UTF8,		//!< UTF-8
    CHARACTER_CODE_UTF8N,		//!< UTF-8
	CHARACTER_CODE_UTF16BE,		//!< UTF-16 (BigEndian)
    CHARACTER_CODE_UTF16LE,		//!< UTF-16 (LittleEndian)
    CHARACTER_CODE_UTF32BE,		//!< UTF-32 (BigEndian)
    CHARACTER_CODE_UTF32LE,		//!< UTF-32 (LittleEndian)
    CHARACTER_CODE_SJIS,		//!< Shift-JIS
    CHARACTER_CODE_EUC,			//!< EUC
    CHARACTER_CODE_ASCII,		//!< ASCII
	
	CHARACTER_CODE_UNKOWN,		//!< 不明
};

//===========================================================================
/*!	@brief		JISならtrueを返す
*/
//===========================================================================
//bool			IsCharacterCodeJis( const u8* text, u32 size );
	
//===========================================================================
/*!	@brief		UTF8ならtrueを返す
*/
//===========================================================================
//bool			IsCharacterCodeUtf8( const u8* text, u32 size );

//===========================================================================
/*!	@brief		Shift-JISならtrueを返す
*/
//===========================================================================
//bool			IsCharacterCodeShiftJis( const u8* text, u32 size );

//===========================================================================
/*!	@brief		テキストデータから文字コードを判別
*/
//===========================================================================
CHARACTER_CODE	ParseCharacterCode( const u8* text, u32 size );
	
}	// namespace nk






#endif  // __CHARACTER_CODE_H__