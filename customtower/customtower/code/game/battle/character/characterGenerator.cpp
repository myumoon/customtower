//=============================================================================
/*!	@file	characterGenerator.h

	@brief	�L�����N�^�W�F�l���[�^�[

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "characterGenerator.h"
#include "character01/character01.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace game {

namespace battle {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CharacterGenerator::CharacterGenerator()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
CharacterGenerator::~CharacterGenerator()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void CharacterGenerator::_Init( void )
{
#if 0
	m_characterManager	= NULL;
	
	m_characters.resize( MAX_CHARACTER_NUM );
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i].index	= i;
	}
	m_unusedHeadIndex	= 0;
#endif
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void CharacterGenerator::_Term( void )
{
#if 0
	Terminate();
#endif
}

#if 0
//===========================================================================
/*!	@brief		������
	@param		----
	@return		----
*/
//===========================================================================
void CharacterGenerator::Initialize( const CharacterManager* mng )
{
	m_characterManager	= mng;
}


//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		----
*/
//===========================================================================
void CharacterGenerator::Terminate( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i].DeleteCharacter();
	}
}
#endif

//===========================================================================
/*!	@brief		�������ݒ�
	@param		info	�������
	@return		----
*/
//===========================================================================
void CharacterGenerator::SetGenerateInfo( const GenerateInfo& info )
{

}

	
//===========================================================================
/*!	@brief		�L�����N�^����
	@param		info	�������
	@return		----
*/
//===========================================================================
Character* CharacterGenerator::Generate( void )
{
	{
		Character*	createdCharacter	= new Character01();
// 		AddCharacterToContainer( createdCharacter );
// 
// 		createdCharacter->SetCharacterManager( m_characterManager );
// 		createdCharacter->InitializeForBattle();
		
		return createdCharacter;
	}
	
	return NULL;
}
#if 0
//===========================================================================
/*!	@brief		�L�����N�^�폜
	@param		character	�폜�L�����N�^
	@return		----
*/
//===========================================================================
void CharacterGenerator::Delete( Character* character )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		if( m_characters[i].character == character ) {
			m_characters[i].character->TerminateForBattle();
			m_characters[i].DeleteCharacter();

			if( i < m_unusedHeadIndex ) {
				m_unusedHeadIndex	= i;
			}
			break;
		}
	}
	
}

//===========================================================================
/*!	@brief		�L�����N�^�폜
	@param		----
	@return		----
*/
//===========================================================================
void CharacterGenerator::Delete( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i].DeleteCharacter();
	}
	m_unusedHeadIndex	= 0;
}


//===========================================================================
/*!	@brief		���g�p�̃R���e�i���擾
	@param		----
	@return		----
*/
//===========================================================================
CharacterGenerator::CharacterContainer* CharacterGenerator::GetUnusedContainer( void )
{
	// �������ԒZ�k�̂��߂ɖ��g�p�C���f�b�N�X���Q��
	if( m_unusedHeadIndex != m_characters.size() ) {
		return &m_characters[m_unusedHeadIndex];
	}

	// �z�񐔂�����Ă��Ȃ�������d���Ȃ����₵�čċA�Ăяo��
	{
		const u32	prevSize	= m_characters.size();
		m_characters.resize( prevSize + MAX_CHARACTER_NUM );
		for( u32 i = prevSize; i < m_characters.size(); ++i ) {
			m_characters[i].index	= i;
		}
	}

	return GetUnusedContainer();
}

//===========================================================================
/*!	@brief		�R���e�i�ɃL�����N�^���i�[
	@param		character	�ǉ��L����
	@return		----
*/
//===========================================================================
void CharacterGenerator::AddCharacterToContainer( Character* character )
{
	CharacterContainer*	container	= GetUnusedContainer();
	
	container->SetCharacter( character );

	// ���̐������ԒZ�k�̂��߂ɖ��g�p�R���e�i������
	do {
		++m_unusedHeadIndex;
	} while( m_characters[m_unusedHeadIndex].Using() );
	
}
#endif

}	// namespace battle

	
}	// namespace game