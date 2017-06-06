//=============================================================================
/*!	@file	textParserUTF8.h
	@brief	UTF-8パーサー

	@author	ryunosuke ide
	@date	2013.12.11
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../include/utility/textParserUTF8.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------


//--------------------------------static関数--------------------------------


//---------------------------------関数定義---------------------------------


namespace nk {


//-------------------------------- データバッファ --------------------------------

//===========================================================================
/*!	@brief		バッファリング
	@param		data	追加データ
	@return		true.成功
*/
//===========================================================================
bool TextParserUTF8::UTF8DataBuffer::AddBuffer( u8 data )
{
	m_characterBuf[m_addIndex]	= data;
	++m_addIndex;

	// BOMは除外
	{
		const u8	BOM[]	= { 0xEF, 0xBB, 0xBF };

		if( m_addIndex == ARRAY_SIZE(BOM) ) {
			u32	i = 0;
			for( i = 0; i < ARRAY_SIZE(BOM); ++i ) {
				if( m_characterBuf[i] != BOM[i] ) {
					break;
				}
			}
			if( i == ARRAY_SIZE(BOM) ) {
				Clear();
			}
		}
	}
	
	return true;
}


//===========================================================================
/*!	@brief		バッファデータ取得可能ならtrueを返す
	@param		----
	@return		true.利用可能
*/
//===========================================================================
bool TextParserUTF8::UTF8DataBuffer::IsAvailable( void ) const
{
	switch( m_addIndex ) {
		// 1バイト
		case 1 : {
			if( _IsIncludedTopByte( 0x00, 0x7F ) ) {
				return true;
			}
		} break;

		// 2バイト
		case 2 : {
			if( _IsIncludedTopByte( 0xC0, 0xDF ) ) {
				return true;
			}
		} break;

		// 3バイト
		case 3 : {
			if( _IsIncludedTopByte( 0xE0, 0xEF ) ) {
				return true;
			}
		} break;

		// 4バイト
		case 4 : {
			if( _IsIncludedTopByte( 0xF0, 0xF7 ) ) {
				return true;
			}
		} break;

		// 5バイト
		case 5 : {
			if( _IsIncludedTopByte( 0xF8, 0xFB ) ) {
				return true;
			}
		} break;

		// 6バイト
		case 6 : {
			if( _IsIncludedTopByte( 0xFC, 0xFD ) ) {
				return true;
			}
		} break;
	}
	
	return false;
}


//===========================================================================
/*!	@brief		バッファデータを取得
	@param		----
	@return		バッファ
*/
//===========================================================================
const u8* TextParserUTF8::UTF8DataBuffer::GetBufferData( void ) const
{
	
	return m_characterBuf;
}

	
//===========================================================================
/*!	@brief		バッファデータサイズを取得
	@param		----
	@return		データサイズ
*/
//===========================================================================
u32 TextParserUTF8::UTF8DataBuffer::GetBufferDataSize( void ) const
{
	
	return m_addIndex;
}

//===========================================================================
/*!	@brief		クリア
	@param		----
	@return		----
*/
//===========================================================================
void TextParserUTF8::UTF8DataBuffer::Clear( void )
{
	memset( m_characterBuf, 0, sizeof(m_characterBuf) );
	m_addIndex	= 0;
}
	

//-------------------------------- UTF-8パーサー --------------------------------

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
TextParserUTF8::TextParserUTF8( void )
{
	_Init();
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
TextParserUTF8::TextParserUTF8( TextParser::CharacterGetListener* listener ) : TextParser( listener )
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
TextParserUTF8::~TextParserUTF8( void )
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void TextParserUTF8::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void TextParserUTF8::_Term( void )
{

}

	
}	// namespace nk