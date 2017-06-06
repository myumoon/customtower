//=============================================================================
/*!	@file	characterGenerator.h

	@brief	�L�����N�^�W�F�l���[�^�[

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
						�L�����N�^�W�F�l���[�^�[
*/
//=============================================================================
class CharacterGenerator : public Generator<Character> {
public:
	//-----------------------�^��`--------------------------

	//! �������
	struct GenerateInfo {
		s32			base;		//!< �x�[�X
	};

	//! �L�����N�^�R���e�i
	struct CharacterContainer {
		s32				index;			//!< �C���f�b�N�X
		Character*		character;		//!< �L����
		bool			use;			//!< �g�p

		//! �R���X�g���N�^
		CharacterContainer() {
			this->character		= NULL;
			this->use			= false;
		}

		//! �L�����N�^�[���Z�b�g
		void SetCharacter( Character* character ) {
			this->character	= character;
			this->use		= true;
		}

		//! �L�����N�^�[���폜
		void DeleteCharacter( void ) {
			if( this->use ) {
				nk::SafeDelete( this->character );
				this->use	= false;
			}
		}

		//! �g�p���Ȃ�true��Ԃ�
		bool Using( void ) const {
			return this->use;
		}
	};

	typedef std::vector<CharacterContainer>	VecCharacter;		//!< �L���N�^�R���e�i

	
	//----------------------�ÓI�����o-----------------------
	static const s32	MAX_CHARACTER_NUM	= 128;	//!< �L�����N�^�[�����ő吔
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�L�����N�^�[�p�����[�^�[�Z�b�g�o�^
	*/
	//===========================================================================
	//u32				RegisterParameter( const CharacterParameter& param );

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
// 	void			Initialize( const CharacterManager* mng );

	//===========================================================================
	/*!	@brief		�I��
	*/
	//===========================================================================
// 	void			Terminate( void );

	//===========================================================================
	/*!	@brief		�������Z�b�g
	*/
	//===========================================================================
	void			SetGenerateInfo( const GenerateInfo& info );

	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	virtual Character*		Generate( void );

	//===========================================================================
	/*!	@brief		�L�����N�^�폜
	*/
	//===========================================================================
// 	void			Delete( Character* character );
	
	//===========================================================================
	/*!	@brief		�폜
	*/
	//===========================================================================
// 	virtual void	Delete( void );

protected:

	//===========================================================================
	/*!	@brief		���g�p�̃L�����N�^�i�[�ꏊ���擾
	*/
	//===========================================================================
// 	CharacterContainer*	GetUnusedContainer( void );

	//===========================================================================
	/*!	@brief		�R���e�i�ɃL�����N�^���i�[
	*/
	//===========================================================================
// 	void				AddCharacterToContainer( Character* character );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
// 	const CharacterManager*		m_characterManager;		//!< �L�����N�^�[�}�l�[�W���[
// 	VecCharacter				m_characters;			//!< �L�����N�^
// 	u32							m_unusedHeadIndex;		//!< ���g�p�C���f�b�N�X

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			CharacterGenerator();
	virtual~CharacterGenerator();
};


}	// namespace battle
	
}	// namespace game



#endif  // __CHARACTER_GENERATOR_H__