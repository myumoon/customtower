//=============================================================================
/*!	@file	textParserUTF8.h
	@brief	UTF-8�p�[�T�[

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
								UTF�p�[�T�[
*/
//=============================================================================
class TextParserUTF8 : public TextParser {
public:
	//-----------------------�^��`--------------------------

	//! �f�[�^�o�b�t�@
	struct UTF8DataBuffer : public TextParser::DataBuffer {
		u8		m_characterBuf[18];			//!< ������o�b�t�@
		u32		m_addIndex;					//!< �ǉ��C���f�b�N�X

		UTF8DataBuffer( void ) {
			std::memset( m_characterBuf, 0, sizeof(m_characterBuf) );
			m_addIndex			= 0;
		}
		virtual ~UTF8DataBuffer( void ) {
		}

		//! �o�b�t�@�����O
		virtual bool		AddBuffer( u8 data );
		
		//! �o�b�t�@�f�[�^�擾�\�Ȃ�true��Ԃ�
		virtual bool		IsAvailable( void ) const;

		//! �o�b�t�@�f�[�^���擾
		virtual const u8*	GetBufferData( void ) const;

		//! �o�b�t�@�f�[�^�T�C�Y���擾
		virtual u32			GetBufferDataSize( void ) const;

		//! �o�b�t�@�N���A
		virtual void		Clear( void );

	private:
		bool				_IsIncludedTopByte( u8 min, u8 max ) const {
			ASSERT( 0 < m_addIndex, "m_addIndex == 0" );
			return (min <= m_characterBuf[0]) && (m_characterBuf[0] <= max);
		}
	};

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

protected:
	//===========================================================================
	/*!	@brief		�o�b�t�@���擾
	*/
	//===========================================================================
	virtual TextParser::DataBuffer*		GetBuffer( void ) { return &m_buffer; }
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	UTF8DataBuffer		m_buffer;		//!< ������i�[�o�b�t�@

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			TextParserUTF8( void );
			TextParserUTF8( TextParser::CharacterGetListener* listener );
	virtual~TextParserUTF8( void );
};
	
}	// namespace nk







#endif  // __TEXT_PARSER_UTF8_H__