//=============================================================================
/*!	@file	textParserUTF8.h
	@brief	UTF-8�p�[�T�[

	@author	ryunosuke ide
	@date	2013.12.11
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../include/utility/textParserUTF8.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------


//--------------------------------static�֐�--------------------------------


//---------------------------------�֐���`---------------------------------


namespace nk {


//-------------------------------- �f�[�^�o�b�t�@ --------------------------------

//===========================================================================
/*!	@brief		�o�b�t�@�����O
	@param		data	�ǉ��f�[�^
	@return		true.����
*/
//===========================================================================
bool TextParserUTF8::UTF8DataBuffer::AddBuffer( u8 data )
{
	m_characterBuf[m_addIndex]	= data;
	++m_addIndex;

	// BOM�͏��O
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
/*!	@brief		�o�b�t�@�f�[�^�擾�\�Ȃ�true��Ԃ�
	@param		----
	@return		true.���p�\
*/
//===========================================================================
bool TextParserUTF8::UTF8DataBuffer::IsAvailable( void ) const
{
	switch( m_addIndex ) {
		// 1�o�C�g
		case 1 : {
			if( _IsIncludedTopByte( 0x00, 0x7F ) ) {
				return true;
			}
		} break;

		// 2�o�C�g
		case 2 : {
			if( _IsIncludedTopByte( 0xC0, 0xDF ) ) {
				return true;
			}
		} break;

		// 3�o�C�g
		case 3 : {
			if( _IsIncludedTopByte( 0xE0, 0xEF ) ) {
				return true;
			}
		} break;

		// 4�o�C�g
		case 4 : {
			if( _IsIncludedTopByte( 0xF0, 0xF7 ) ) {
				return true;
			}
		} break;

		// 5�o�C�g
		case 5 : {
			if( _IsIncludedTopByte( 0xF8, 0xFB ) ) {
				return true;
			}
		} break;

		// 6�o�C�g
		case 6 : {
			if( _IsIncludedTopByte( 0xFC, 0xFD ) ) {
				return true;
			}
		} break;
	}
	
	return false;
}


//===========================================================================
/*!	@brief		�o�b�t�@�f�[�^���擾
	@param		----
	@return		�o�b�t�@
*/
//===========================================================================
const u8* TextParserUTF8::UTF8DataBuffer::GetBufferData( void ) const
{
	
	return m_characterBuf;
}

	
//===========================================================================
/*!	@brief		�o�b�t�@�f�[�^�T�C�Y���擾
	@param		----
	@return		�f�[�^�T�C�Y
*/
//===========================================================================
u32 TextParserUTF8::UTF8DataBuffer::GetBufferDataSize( void ) const
{
	
	return m_addIndex;
}

//===========================================================================
/*!	@brief		�N���A
	@param		----
	@return		----
*/
//===========================================================================
void TextParserUTF8::UTF8DataBuffer::Clear( void )
{
	memset( m_characterBuf, 0, sizeof(m_characterBuf) );
	m_addIndex	= 0;
}
	

//-------------------------------- UTF-8�p�[�T�[ --------------------------------

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
TextParserUTF8::TextParserUTF8( void )
{
	_Init();
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
TextParserUTF8::TextParserUTF8( TextParser::CharacterGetListener* listener ) : TextParser( listener )
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
TextParserUTF8::~TextParserUTF8( void )
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void TextParserUTF8::_Init( void )
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void TextParserUTF8::_Term( void )
{

}

	
}	// namespace nk