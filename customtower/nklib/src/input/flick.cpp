//=============================================================================
/*!	@file	flick.cpp

	@brief	�t���b�N����

	@author	ryunosuke ide
	@date	2013.06.27
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/input/flick.h"
#include "../../include/input/mouse.h"
#include "../../include/general.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

namespace nk {
namespace input {
	
const f32	Flick::DEFAULT_DECELERATION		= 0.85f;	// �f�t�H���g������
	
}	// namespace input
}	// namespace nk

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {

namespace input {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
Flick::Flick()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Flick::~Flick()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Flick::_Init( void )
{
	m_mouse			= NULL;
	m_deceleration	= DEFAULT_DECELERATION;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Flick::_Term( void )
{

}


//===========================================================================
/*!	@brief		�}�E�X�ݒ�
	@param		mouse	�}�E�X
	@return		----
*/
//===========================================================================
void Flick::Initialize( const Mouse* mouse )
{
	m_mouse	= mouse;
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void Flick::Update( void )
{
	if( m_mouse == NULL ) {
		return;
	}

	for( s32 button = 0; button < Mouse::MOUSE_MAX; ++button ) {
		// �����ꂽ�u�Ԃ͉������Ȃ�
		if( m_mouse->IsPressed( button ) ) {
			m_prevPos[button]	= m_mouse->GetPos();
			m_flickVec[button].Clear();
		}
		// �������ςȂ��Ń}�E�X�ɂ��Ă���
		else if( m_mouse->IsPress( button ) ) {
			m_flickVec[button]	= m_mouse->GetPos() - m_prevPos[button];
			m_prevPos[button]	= m_mouse->GetPos();
		}
		// ���͂��Ȃ������猸��
		else {
			m_flickVec[button] *= m_deceleration;
			if( m_flickVec[button].GetNorm2() <= 1.0f ) {
				m_flickVec[button].Clear();
			}
		}
	}
	
}

//===========================================================================
/*!	@brief		�������ݒ�
	@param		deceleration	������
	@return		----
*/
//===========================================================================
void Flick::SetDeceleration( f32 deceleration )
{
	m_deceleration	= deceleration;
	
}

//===========================================================================
/*!	@brief		�t���b�N�ʎ擾
	@param		----
	@return		----
*/
//===========================================================================
math::Vector Flick::GetFlickVec( s32 button ) const
{
	INDEX_ASSERT( button, Mouse::MOUSE_MAX, "index error" );
	if( (0 <= button) && button < Mouse::MOUSE_MAX ) {
		return m_flickVec[button];
	}
	return math::Vector();
}
	
//===========================================================================
/*!	@brief		��~����true��Ԃ�
	@param		----
	@return		----
*/
//===========================================================================
bool Flick::IsStopping( s32 button ) const
{
	INDEX_ASSERT( button, Mouse::MOUSE_MAX, "index error" );
	if( (0 <= button) && button < Mouse::MOUSE_MAX ) {
		if( m_flickVec[button].GetNorm2() < 1.0f ) {
			return true;
		}
	}
	
	return false;
}
	
}	// namespace input
	
}	// namespace nk