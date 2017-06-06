//=============================================================================
/*!	@file	systemEventGetter.h

	@brief	�V�X�e���C�x���g�擾

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/system/systemEventGetter.h"
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
SystemEventGetter::SystemEventGetter() : SystemEventGetterBase()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
SystemEventGetter::~SystemEventGetter()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void SystemEventGetter::_Init( void )
{
	
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void SystemEventGetter::_Term( void )
{

}


//===========================================================================
/*!	@brief		�����`�F�b�N
	@param		eventType	�C�x���g
	@return		----
*/
//===========================================================================
bool SystemEventGetter::IsOn( u32 eventType ) const
{
	
	return m_event.IsOn( eventType );
}

//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void SystemEventGetter::Update( void )
{
	
	m_event	= EventGetter::GetInstance()->GetSystemEvent();
	
}
	
}	// namespace system
}	// namespace nk