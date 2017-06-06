//=============================================================================
/*!	@file	characterCode.h
	@brief	�����R�[�h

	@author	ryunosuke ide
	@date	2013.12.12
*/
//=============================================================================

#ifndef __CHARACTER_CODE_H__
#define __CHARACTER_CODE_H__

#include "../typedef.h"

namespace nk {

//! �����R�[�h
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
	
	CHARACTER_CODE_UNKOWN,		//!< �s��
};

//===========================================================================
/*!	@brief		JIS�Ȃ�true��Ԃ�
*/
//===========================================================================
//bool			IsCharacterCodeJis( const u8* text, u32 size );
	
//===========================================================================
/*!	@brief		UTF8�Ȃ�true��Ԃ�
*/
//===========================================================================
//bool			IsCharacterCodeUtf8( const u8* text, u32 size );

//===========================================================================
/*!	@brief		Shift-JIS�Ȃ�true��Ԃ�
*/
//===========================================================================
//bool			IsCharacterCodeShiftJis( const u8* text, u32 size );

//===========================================================================
/*!	@brief		�e�L�X�g�f�[�^���當���R�[�h�𔻕�
*/
//===========================================================================
CHARACTER_CODE	ParseCharacterCode( const u8* text, u32 size );
	
}	// namespace nk






#endif  // __CHARACTER_CODE_H__