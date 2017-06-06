
//=============================================================================
/*!	@file	buttonInputChecker_Mouse.h

	@brief	�{�^���p�}�E�X���̓`�F�b�N

	@author	ryunosuke ide
	@date	2013.06.08
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/graphics/buttonInputChecker_Mouse.h"

#include "../../include/graphics/spriteAnimation.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {
//ButtonInputChecker_Mouse*	defaultChecker	= NULL;
}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------



namespace nk {

namespace graphics {
#if 0
//===========================================================================
/*!	@brief		�f�t�H���g�`�F�b�N�I�u�W�F�N�g�𐶐�
	@param		mouse	�}�E�X
	@return		----
*/
//===========================================================================
void InitializeDefaultButtonInputChecker_Mouse( const input::Mouse* mouse )
{
	if( defaultChecker == NULL ) {
		defaultChecker	= new ButtonInputChecker_Mouse();
		defaultChecker->Initialize( mouse );
	}
}


//===========================================================================
/*!	@brief		�f�t�H���g�`�F�b�N�I�u�W�F�N�g�̊J��
	@param		----
	@return		----
*/
//===========================================================================
void TerminateDefaultButtonInputChecker_Mouse( void )
{
	SafeDelete( defaultChecker );
}

//===========================================================================
/*!	@brief		�f�t�H���g�`�F�b�N�I�u�W�F�N�g���擾
	@param		----
	@return		----
*/
//===========================================================================
ButtonInputChecker_Mouse*	GetDefaultButtonInputChecker_Mouse( void )
{
	NULL_ASSERT( defaultChecker );
	
	return defaultChecker;
}
#endif
//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
ButtonInputChecker_Mouse::ButtonInputChecker_Mouse()
{
	_Init();
}

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
ButtonInputChecker_Mouse::ButtonInputChecker_Mouse( const input::Mouse* mouse )
{
	_Init();
	Initialize( mouse );
}

//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
ButtonInputChecker_Mouse::~ButtonInputChecker_Mouse()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void ButtonInputChecker_Mouse::_Init( void )
{
	m_mouse	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void ButtonInputChecker_Mouse::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		
	@return		----
*/
//===========================================================================
void ButtonInputChecker_Mouse::Initialize( const input::Mouse* mouse )
{
	m_mouse	= mouse;
}


//===========================================================================
/*!	@brief		�A�N�e�B�u�H
	@param		info	�{�^�����
	@return		----
*/
//===========================================================================
bool ButtonInputChecker_Mouse::IsActive( const CheckInfo& info ) const
{
	if( m_mouse ) {
		const math::Vector			mousePos		= m_mouse->GetPos();
		const resource::Texture*	tex				= info.sprite->GetTexture();
		const u32					buttonWidth		= tex->GetWidth() / info.sprite->GetCol();
		const u32					buttonHeight	= tex->GetHeight() / info.sprite->GetRow();
		
		const math::Vector			leftUp			= info.pos;												// �{�^��������W
		const math::Vector			rightDown		= leftUp + math::Vector( static_cast<f32>(buttonWidth), static_cast<f32>(buttonHeight), 0.0f );	// �{�^���E�����W

		const bool					includeLeftUp	= (leftUp.x < mousePos.x) && (leftUp.y < mousePos.y);
		const bool					includeRightDown= (mousePos.x < rightDown.x) && (mousePos.y < rightDown.y);
		
		if( includeLeftUp && includeRightDown ) {
			return true;
		}
	}

	return false;
}


//===========================================================================
/*!	@brief		�A�N�e�B�u�H
	@param		info	�{�^�����
	@return		----
*/
//===========================================================================
bool ButtonInputChecker_Mouse::IsPress( void ) const
{
	if( m_mouse ) {
		return m_mouse->IsPress( INPUT_CHECK_BUTTON );
	}
	return false;
}
	
}	// namespace graphics
	
}	// namespace nk