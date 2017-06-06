//=============================================================================
/*!	@file	layoutChanger.h

	@brief	���C�A�E�g�ҏW

	@author	ryunosuke ide
	@date	2013.06.11
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <algorithm>
#include "../../include/debug/layoutChanger.h"
#include "../../include/graphics/layout.h"


//--------------------------------define��`--------------------------------
#if defined(_DEBUG)
	#define ENABLE_LAYOUT_CHANGER
#endif


//--------------------------------static�ϐ�--------------------------------
namespace nk {
LayoutChanger*	LayoutChanger::m_instance	= NULL;
}	// namespace nk

namespace {

}	// unnamed


//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
LayoutChanger::LayoutChanger()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
LayoutChanger::~LayoutChanger()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutChanger::_Init( void )
{
	m_updateLayout.reserve( 128 );
	m_layoutChange	= true;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutChanger::_Term( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
#endif
}


//===========================================================================
/*!	@brief		���C�A�E�g�o�^
	@param		layout	�o�^���C�A�E�g
	@return		----
*/
//===========================================================================
void LayoutChanger::RegisterLayout( graphics::Layout* layout )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_updateLayout.push_back( LayoutData( layout ) );
#endif
}


//===========================================================================
/*!	@brief		���C�A�E�g�o�^
	@param		layout	�o�^���C�A�E�g
	@return		----
*/
//===========================================================================
void LayoutChanger::RemoveLayout( graphics::Layout* layout )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_updateLayout.erase( std::remove( m_updateLayout.begin(), m_updateLayout.end(), layout ), m_updateLayout.end() );
#endif
}

//===========================================================================
/*!	@brief		�Z�[�u
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Save( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	VecLayoutData::iterator	itr	= m_updateLayout.begin();
	for( ; itr != m_updateLayout.end(); ++itr ) {
		if( (*itr).layout->Changed() ) {
			_Save( (*itr).layout );
		}
	}
#endif
}


//===========================================================================
/*!	@brief		�Z�[�u
	@param		layout	�Z�[�u���郌�C�A�E�g
	@return		----
*/
//===========================================================================
void  LayoutChanger::_Save( graphics::Layout* layout )
{
	if( layout ) {
		
	}
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Update( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	if( m_layoutChange ) {
		VecLayoutData::iterator	itr	= m_updateLayout.begin();
		for( ; itr != m_updateLayout.end(); ++itr ) {
			(*itr).layout->UpdateLayoutChange();
		}
	}
#endif
}


//===========================================================================
/*!	@brief		�J�n
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Start( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_layoutChange	= true;
#endif
}


//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		�ύX���������ꍇ��true��Ԃ�
*/
//===========================================================================
bool LayoutChanger::End( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_layoutChange	= false;

	VecLayoutData::iterator	itr	= m_updateLayout.begin();
	for( ; itr != m_updateLayout.end(); ++itr ) {
		if( (*itr).layout->Changed() ) {
			return true;
		}
	}
#endif
	return false;
}


//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Draw( void )
{
	VecLayoutData::iterator	itr	= m_updateLayout.begin();
	for( ; itr != m_updateLayout.end(); ++itr ) {
		(*itr).layout->DrawActivePartsFrame();
	}
}
	
}	// namespace nk