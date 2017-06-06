//=============================================================================
/*!	@file	characterManager.h

	@brief	�L�����N�^�[�}�l�[�W���[

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "characterManager.h"

#include "characterGenerator.h"

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
CharacterManager::CharacterManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
CharacterManager::~CharacterManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void CharacterManager::_Init( void )
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void CharacterManager::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::Initialize( void )
{
	
}


//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::Terminate( void )
{
	DeleteAll();
}


//===========================================================================
/*!	@brief		�L�����N�^�[�ǉ�
	@param		character	�ǉ��L�����N�^�[
	@return		----
*/
//===========================================================================
void CharacterManager::Add( Character* character )
{
	character->RegisterToRenderManager();
	m_characters.push_back( character );
}



//===========================================================================
/*!	@brief		�폜�L�����N�^�[�ǉ�
	@param		character	�폜�L�����N�^�[
	@return		----
*/
//===========================================================================
void CharacterManager::Remove( Character* character )
{
	character->RemoveFromRenderManager();
	m_removeCharacters.push_back( character );
	
}


//===========================================================================
/*!	@brief		�S�폜
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::DeleteAll( void )
{
	std::vector<Character*>::iterator	itr	= m_characters.begin();
	for( ; itr != m_characters.end(); ++itr ) {
		(*itr)->TerminateForBattle();
		nk::SafeDelete( *itr );
	}
	m_characters.clear();
	m_removeCharacters.clear();
}


//===========================================================================
/*!	@brief		�폜
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::RemoveReservedCharacters( void )
{
	std::vector<Character*>::iterator	itrDead	= m_removeCharacters.begin();
	std::vector<Character*>::iterator	itrLive	= m_characters.begin();
	
	for( ; itrDead != m_removeCharacters.end(); ++itrDead ) {
		for( itrLive = m_characters.begin(); itrLive != m_characters.end(); ++itrLive ) {
			if( *itrDead == *itrLive ) {
				(*itrLive)->TerminateForBattle();
				nk::SafeDelete( *itrLive );
				m_characters.erase( itrLive );
				break;
			}
		}
	}
	m_removeCharacters.clear();
	
		
}


//===========================================================================
/*!	@brief		�O��ʒu�L��
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::PushPrevPos( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i]->SetPrevPos( m_characters[i]->GetPos() );
	}
}


//===========================================================================
/*!	@brief		�ʒu�X�V
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::UpdatePosition( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i]->UpdatePosition();
	}
}

//===========================================================================
/*!	@brief		�ړ�
	@param		----
	@return		----
*/
//===========================================================================
void CharacterManager::UpdateMove( void )
{
	for( u32 i = 0; i < m_characters.size(); ++i ) {
		m_characters[i]->Move();
	}
	
}


}	// namespace battle
	
}	// namespace game