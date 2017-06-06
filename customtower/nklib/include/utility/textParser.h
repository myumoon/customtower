//=============================================================================
/*!	@file	textParser.h
	@brief	�����p�[�T�[

	@author	ryunosuke ide
	@date	2013.12.11
*/
//=============================================================================

#ifndef __TEXT_PARSER_H__
#define __TEXT_PARSER_H__



namespace nk {

//=============================================================================
/*!
							�e�L�X�g�p�[�T�[
*/
//=============================================================================
class TextParser {
public:
	//-----------------------�^��`--------------------------

	//! �����擾���X�i�[
	class CharacterGetListener {
	public:
		virtual void	GetCharacter( const u8* character, u32 characterSize ) = 0;
	};

	//! �f�[�^�o�b�t�@
	class DataBuffer {
	public:
		//! �o�b�t�@�����O
		virtual bool		AddBuffer( u8 data ) = 0;
		
		//! �o�b�t�@�f�[�^�擾�\�Ȃ�true��Ԃ�
		virtual bool		IsAvailable( void ) const = 0;

		//! �o�b�t�@�f�[�^���擾
		virtual const u8*	GetBufferData( void ) const = 0;

		//! �o�b�t�@�f�[�^�T�C�Y���擾
		virtual u32			GetBufferDataSize( void ) const = 0;

		//! �o�b�t�@�f�[�^�N���A
		virtual void		Clear( void ) = 0;
	};
	
	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//===========================================================================
	/*!	@brief		���X�i�[�ݒ�
	*/
	//===========================================================================
	void	SetListener( CharacterGetListener* listener )
	{
		m_listener	= listener;
	}

	//===========================================================================
	/*!	@brief		�����擾
	*/
	//===========================================================================
	bool	Parse( const u8* data, u32 dataSize )
	{
		if( data == NULL ) {
			return false;
		}
		if( m_listener == NULL ) {
			return false;
		}

		bool	result	= true;
		for( u32 parseIndex = 0; parseIndex < dataSize; ++parseIndex ) {
			
			result	= GetBuffer()->AddBuffer( data[parseIndex] );
			
			if( result == false ) {
				break;
			}
			
			if( GetBuffer()->IsAvailable() ) {
				m_listener->GetCharacter( GetBuffer()->GetBufferData(), GetBuffer()->GetBufferDataSize() );
				GetBuffer()->Clear();
			}
		}
		return true;
	}

protected:
	//===========================================================================
	/*!	@brief		�o�b�t�@���擾
	*/
	//===========================================================================
	virtual DataBuffer*	GetBuffer( void ) = 0;
	
protected:
	//----------------------�����o�ϐ�-----------------------
	CharacterGetListener*	m_listener;

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	TextParser( void )
	{
		m_listener	= NULL;
	}
	TextParser( CharacterGetListener* listener ) : m_listener( listener )
	{		
	}
	virtual~TextParser( void )
	{
	}
};
	
}	// namespace nk





#endif  // __TEXT_PARSER_H__