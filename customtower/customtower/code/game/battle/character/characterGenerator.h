//=============================================================================
/*!	@file	characterGenerator.h

	@brief	キャラクタジェネレーター

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __CHARACTER_GENERATOR_H__
#define __CHARACTER_GENERATOR_H__

#include <vector>
#include "character.h"
#include "game/battle/generator.h"


namespace game {

namespace battle {

//=============================================================================
/*!
						キャラクタジェネレーター
*/
//=============================================================================
class CharacterGenerator : public Generator<Character> {
public:
	//-----------------------型定義--------------------------

	//! 生成情報
	struct GenerateInfo {
		s32			base;		//!< ベース
	};

	//! キャラクタコンテナ
	struct CharacterContainer {
		s32				index;			//!< インデックス
		Character*		character;		//!< キャラ
		bool			use;			//!< 使用

		//! コンストラクタ
		CharacterContainer() {
			this->character		= NULL;
			this->use			= false;
		}

		//! キャラクターをセット
		void SetCharacter( Character* character ) {
			this->character	= character;
			this->use		= true;
		}

		//! キャラクターを削除
		void DeleteCharacter( void ) {
			if( this->use ) {
				nk::SafeDelete( this->character );
				this->use	= false;
			}
		}

		//! 使用中ならtrueを返す
		bool Using( void ) const {
			return this->use;
		}
	};

	typedef std::vector<CharacterContainer>	VecCharacter;		//!< キャクタコンテナ

	
	//----------------------静的メンバ-----------------------
	static const s32	MAX_CHARACTER_NUM	= 128;	//!< キャラクター生成最大数
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		キャラクターパラメーターセット登録
	*/
	//===========================================================================
	//u32				RegisterParameter( const CharacterParameter& param );

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
// 	void			Initialize( const CharacterManager* mng );

	//===========================================================================
	/*!	@brief		終了
	*/
	//===========================================================================
// 	void			Terminate( void );

	//===========================================================================
	/*!	@brief		生成情報セット
	*/
	//===========================================================================
	void			SetGenerateInfo( const GenerateInfo& info );

	//===========================================================================
	/*!	@brief		生成
	*/
	//===========================================================================
	virtual Character*		Generate( void );

	//===========================================================================
	/*!	@brief		キャラクタ削除
	*/
	//===========================================================================
// 	void			Delete( Character* character );
	
	//===========================================================================
	/*!	@brief		削除
	*/
	//===========================================================================
// 	virtual void	Delete( void );

protected:

	//===========================================================================
	/*!	@brief		未使用のキャラクタ格納場所を取得
	*/
	//===========================================================================
// 	CharacterContainer*	GetUnusedContainer( void );

	//===========================================================================
	/*!	@brief		コンテナにキャラクタを格納
	*/
	//===========================================================================
// 	void				AddCharacterToContainer( Character* character );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
// 	const CharacterManager*		m_characterManager;		//!< キャラクターマネージャー
// 	VecCharacter				m_characters;			//!< キャラクタ
// 	u32							m_unusedHeadIndex;		//!< 未使用インデックス

public:
	//-------------コンストラクタ・デストラクタ--------------
			CharacterGenerator();
	virtual~CharacterGenerator();
};


}	// namespace battle
	
}	// namespace game



#endif  // __CHARACTER_GENERATOR_H__