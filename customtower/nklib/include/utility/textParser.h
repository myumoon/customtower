//=============================================================================
/*!	@file	textParser.h
	@brief	文字パーサー

	@author	ryunosuke ide
	@date	2013.12.11
*/
//=============================================================================

#ifndef __TEXT_PARSER_H__
#define __TEXT_PARSER_H__



namespace nk {

//=============================================================================
/*!
							テキストパーサー
*/
//=============================================================================
class TextParser {
public:
	//-----------------------型定義--------------------------

	//! 文字取得リスナー
	class CharacterGetListener {
	public:
		virtual void	GetCharacter( const u8* character, u32 characterSize ) = 0;
	};

	//! データバッファ
	class DataBuffer {
	public:
		//! バッファリング
		virtual bool		AddBuffer( u8 data ) = 0;
		
		//! バッファデータ取得可能ならtrueを返す
		virtual bool		IsAvailable( void ) const = 0;

		//! バッファデータを取得
		virtual const u8*	GetBufferData( void ) const = 0;

		//! バッファデータサイズを取得
		virtual u32			GetBufferDataSize( void ) const = 0;

		//! バッファデータクリア
		virtual void		Clear( void ) = 0;
	};
	
	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//===========================================================================
	/*!	@brief		リスナー設定
	*/
	//===========================================================================
	void	SetListener( CharacterGetListener* listener )
	{
		m_listener	= listener;
	}

	//===========================================================================
	/*!	@brief		文字取得
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
	/*!	@brief		バッファを取得
	*/
	//===========================================================================
	virtual DataBuffer*	GetBuffer( void ) = 0;
	
protected:
	//----------------------メンバ変数-----------------------
	CharacterGetListener*	m_listener;

public:
	//-------------コンストラクタ・デストラクタ--------------
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