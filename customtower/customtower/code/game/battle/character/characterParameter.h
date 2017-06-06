//=============================================================================
/*!	@file	characterParameter.h

	@brief	�p�����[�^�[�ݒ�

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
								�p�����[�^�[
*/
//=============================================================================
struct CharacterParameter {

	//! �p�[�c
	enum PARTS {
		PARTS_NONE,		//!< ����
		
		PARTS_MAX,		//!< �p�[�c��
	};
	
	//! �p�[�c
	struct PartsParam {
		static const u32	CHILDREN_SIZE	= 32;
		PARTS			type;
		PartsParam*		children[CHILDREN_SIZE];

		//! �R���X�g���N�^
		PartsParam( void ) {
			for( u32 i = 0; i < CHILDREN_SIZE; ++i ) {
				children[i]	= NULL;
			}
		}

		//! �f�X�g���N�^
		~PartsParam( void ) {
			for( u32 i = 0; i < CHILDREN_SIZE; ++i ) {
				nk::SafeDelete( children[i] );
			}
		}

		//! �ǉ�
		void AppendParts( PARTS type ) {
			for( u32 i = 0; i < CHILDREN_SIZE; ++i ) {
				if( children[i] == NULL ) {
					children[i]	= new PartsParam();
					children[i]->type	= type;
				}
			}
		}
	};
	
	
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
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