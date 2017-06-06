//=============================================================================
/*!	@file	textParserUTF8.h
	@brief	UTF-8パーサー

	@author	ryunosuke ide
	@date	2013.12.11
*/
//=============================================================================

#ifndef __TEXT_PARSER_UTF8_H__
#define __TEXT_PARSER_UTF8_H__

#include <iostream>
#include "../general.h"
#include "./textParser.h"

namespace nk {

//=============================================================================
/*!
								UTFパーサー
*/
//=============================================================================
class TextParserUTF8 : public TextParser {
public:
	//-----------------------型定義--------------------------

	//! データバッファ
	struct UTF8DataBuffer : public TextParser::DataBuffer {
		u8		m_characterBuf[18];			//!< 文字列バッファ
		u32		m_addIndex;					//!< 追加インデックス

		UTF8DataBuffer( void ) {
			std::memset( m_characterBuf, 0, sizeof(m_characterBuf) );
			m_addIndex			= 0;
		}
		virtual ~UTF8DataBuffer( void ) {
		}

		//! バッファリング
		virtual bool		AddBuffer( u8 data );
		
		//! バッファデータ取得可能ならtrueを返す
		virtual bool		IsAvailable( void ) const;

		//! バッファデータを取得
		virtual const u8*	GetBufferData( void ) const;

		//! バッファデータサイズを取得
		virtual u32			GetBufferDataSize( void ) const;

		//! バッファクリア
		virtual void		Clear( void );

	private:
		bool				_IsIncludedTopByte( u8 min, u8 max ) const {
			ASSERT( 0 < m_addIndex, "m_addIndex == 0" );
			return (min <= m_characterBuf[0]) && (m_characterBuf[0] <= max);
		}
	};

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

protected:
	//===========================================================================
	/*!	@brief		バッファを取得
	*/
	//===========================================================================
	virtual TextParser::DataBuffer*		GetBuffer( void ) { return &m_buffer; }
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	UTF8DataBuffer		m_buffer;		//!< 文字列格納バッファ

public:
	//-------------コンストラクタ・デストラクタ--------------
			TextParserUTF8( void );
			TextParserUTF8( TextParser::CharacterGetListener* listener );
	virtual~TextParserUTF8( void );
};
	
}	// namespace nk







#endif  // __TEXT_PARSER_UTF8_H__