//=============================================================================
/*!	@file	mouseEventGetter.h

	@brief	�}�E�X�C�x���g�擾

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/system/mouseEventGetter.h"
#include "../../include/system/eventGetter.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {
namespace system {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
MouseEventGetter::MouseEventGetter() : MouseEventGetterBase()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
MouseEventGetter::~MouseEventGetter()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void MouseEventGetter::_Init( void )
{
	
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void MouseEventGetter::_Term( void )
{

}


//===========================================================================
/*!	@brief		�����`�F�b�N
	@param		button	�{�^���ԍ�
	@return		----
*/
//===========================================================================
bool MouseEventGetter::IsOn( u32 button ) const
{
	
	return m_event.IsOn( button );
}

//===========================================================================
/*!	@brief		���W�擾
	@param[out]	x,y
	@return		----
*/
//===========================================================================
void MouseEventGetter::GetPos( u32* x, u32* y ) const
{
	
	if( x ) {
		*x	= m_event.x;
	}
	if( y ) {
		*y	= m_event.y;
	}
}

//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void MouseEventGetter::Update( void )
{
	
	m_event	= EventGetter::GetInstance()->GetMouseEvent();
	
}
	
}	// namespace system
}	// namespace nk