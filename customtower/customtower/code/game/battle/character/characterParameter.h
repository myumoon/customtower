//=============================================================================
/*!	@file	characterParameter.h

	@brief	パラメーター設定

	@author	ryunosuke ide
	@date	2013.07.06
*/
//=============================================================================


#ifndef __CHARACTER_PARAMETER_H__
#define __CHARACTER_PARAMETER_H__

#include <vector>

namespace game {
namespace battle {


//=============================================================================
/*!
								パラメーター
*/
//=============================================================================
struct CharacterParameter {

	//! パーツ
	enum PARTS {
		PARTS_NONE,		//!< 無し
		
		PARTS_MAX,		//!< パーツ数
	};
	
	//! パーツ
	struct PartsParam {
		static const u32	CHILDREN_SIZE	= 32;
		PARTS			type;
		PartsParam*		children[CHILDREN_SIZE];

		//! コンストラクタ
		PartsParam( void ) {
			for( u32 i = 0; i < CHILDREN_SIZE; ++i ) {
				children[i]	= NULL;
			}
		}

		//! デストラクタ
		~PartsParam( void ) {
			for( u32 i = 0; i < CHILDREN_SIZE; ++i ) {
				nk::SafeDelete( children[i] );
			}
		}

		//! 追加
		void AppendParts( PARTS type ) {
			for( u32 i = 0; i < CHILDREN_SIZE; ++i ) {
				if( children[i] == NULL ) {
					children[i]	= new PartsParam();
					children[i]->type	= type;
				}
			}
		}
	};
	
	
	//-------------コンストラクタ・デストラクタ--------------
	CharacterParameter()
	{
	}
	virtual~CharacterParameter()
	{
	}
};
	
}	// namespace battle
}	// namespace game






#endif  // __CHARACTER_PARAMETER_H__