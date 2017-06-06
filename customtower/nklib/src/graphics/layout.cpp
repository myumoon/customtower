//=============================================================================
/*!	@file	layout.h

	@brief	���C�A�E�g

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================
//-------------------------------�C���N���[�h-------------------------------
#include <algorithm>
#include "../../include/graphics/layout.h"

#include "../../include/general.h"
#include "../../include/debug/layoutChanger.h"
#include "../../include/input/input.h"
#include "../../include/system.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
Layout::Layout()
{
	_Init();
}



//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	mouse	�}�E�X
*/
//===========================================================================
Layout::Layout( const nk::input::Mouse* mouse )
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Layout::~Layout()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Layout::_Init( void )
{
	m_eventObserver.m_eventListener	= NULL;
	
	m_mouse			= NULL;
	m_keyboard		= NULL;
	

	m_moveable		= false;
	
	LayoutChanger::GetInstance()->RegisterLayout( this );
	m_activeParts.reserve( 32 );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void Layout::_Term( void )
{
	LayoutChanger::GetInstance()->RemoveLayout( this );
	
	DeleteParts();

}


//===========================================================================
/*!	@brief		�L�[�{�[�h
	@param		mouse		�}�E�X
	@param		keyboard	�L�[�{�[�h
	@return		----
*/
//===========================================================================
void Layout::Initialize( const input::Mouse* mouse, const input::Keyboard* keyboard )
{
	m_mouse		= mouse;
	m_keyboard	= keyboard;
}

//===========================================================================
/*!	@brief		�p�[�c�̍폜
	@param		----
	@return		----
*/
//===========================================================================
void Layout::DeleteParts( void )
{
	m_root.DeleteParts();
}


//===========================================================================
/*!	@brief		�p�[�c�̍X�V
	@param		----
	@return		----
*/
//===========================================================================
void Layout::UpdateParts( void )
{
	m_root.UpdateParts();
}


//===========================================================================
/*!	@brief		�p�[�c�̕`��
	@param		----
	@return		----
*/
//===========================================================================
void Layout::DrawParts( void )
{
	m_root.DrawParts();
}

//===========================================================================
/*!	@brief		�p�[�c�̌���
	@param		partsname	�p�[�c��
	@return		----
*/
//===========================================================================
LayoutParts* Layout::FindParts( const char* partsname )
{
	
	return m_root.FindParts( partsname, true );
}


//===========================================================================
/*!	@brief		�p�[�c�̌���
	@param		partsboxname	�p�[�c��
	@return		----
*/
//===========================================================================
LayoutPartsBox* Layout::FindPartsBox( const char* partsboxname )
{
	
	return m_root.FindPartsBox( partsboxname, true );
}


//===========================================================================
/*!	@brief		���[�g�擾
	@param		----
	@return		----
*/
//===========================================================================
LayoutPartsBox* Layout::GetRoot( void )
{
	
	return &m_root;
}


//===========================================================================
/*!	@brief		�Z�b�g�A�b�v
	@param		layoutFilePath	�t�@�C���p�X
	@param		listener		�C�x���g���X�i�[
	@return		----
*/
//===========================================================================
bool Layout::Setup( const char* layoutFilePath, LayoutEventListener* listener )
{
	m_eventObserver.m_eventListener	= listener;

	// @@@@@ �t�@�C�����烍�[�h
	// �e�p�[�c��&m_eventObserver��ݒ肷��

	return true;
}


//===========================================================================
/*!	@brief		�Z�[�u
	@param		outputPath	�o�̓p�X
	@return		----
*/
//===========================================================================
bool Layout::SaveToFile( const char* outputPath )
{

	return true;
}

//===========================================================================
/*!	@brief		���C�A�E�g�ύX
	@param		----
	@return		----
*/
//===========================================================================
void Layout::UpdateLayoutChange( void )
{
	
	const bool	pressUp		= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_UP ) : false;
	const bool	pressDown	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_DOWN ) : false;
	const bool	pressRight	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_RIGHT ) : false;
	const bool	pressLeft	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_LEFT ) : false;
	const bool	pressCtrl	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_LCTRL ) | m_keyboard->IsPress( input::Keyboard::KEY_RCTRL ) : false;

	if( m_mouse ) {
		// �o�^
		if( m_mouse->IsPressed( input::Mouse::CLICK_LEFT ) ) {

			// �[�x�ݒ�
			const s32		depth			= 0;
			LayoutParts*	findParts		= NULL;
			s32				findPartsDepth	= 0;
			const bool		isFind			= m_root.GetIncludedPartsOf( &findParts, &findPartsDepth, m_mouse->GetPos(), depth );

			// ctrl�����ĂȂ��������U�N���A
			if( pressCtrl == false ) {
				if( isFind == false ) {
					_ClearActiveParts();
				}
			}
			
			if( isFind ) {
				_AddActiveParts( findParts, findPartsDepth );
				m_moveable	= true;
			}
			else {
				m_moveable	= false;
			}

			// �}�E�X�ʒu��ۑ�
			m_prevMousePos	= m_mouse->GetPos();
		}

		// �ړ�
		if( m_mouse->IsPress( input::Mouse::CLICK_LEFT ) ) {

			// �o�^�p�[�c������Έړ�
			if( m_activeParts.size() ) {

				if( m_moveable ) {

					// �}�E�X�ɍ��킹�Ĉړ�
					const math::Vector	diffMouseMove	= m_mouse->GetPos() - m_prevMousePos;

					VecParts::iterator	itr	= m_activeParts.begin();
					for( ; itr != m_activeParts.end(); ++itr ) {
						(*itr).parts->SetPos( (*itr).parts->GetPos() + diffMouseMove );
					}
				}
			}

			// �}�E�X�ʒu��ۑ�
			m_prevMousePos	= m_mouse->GetPos();
		}
	}

	// �L�[�{�[�h�ł̈ړ�
	else if( pressUp || pressDown || pressLeft || pressRight ) {
		math::Vector	moveAmount;
		
		if( pressUp ) {
			moveAmount.y	-= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}
		else if( pressDown ) {
			moveAmount.y	+= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}

		if( pressLeft ) {
			moveAmount.x	-= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}
		else if( pressRight ) {
			moveAmount.x	+= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}
		
		VecParts::iterator	itr	= m_activeParts.begin();
		for( ; itr != m_activeParts.end(); ++itr ) {
			(*itr).parts->SetPos( (*itr).parts->GetPos() + moveAmount );
		}
	}
}



//===========================================================================
/*!	@brief		�A�N�e�B�u�p�[�c��ǉ�
	@param		parts		�ǉ��p�[�c
	@param		depth		�[��
	@return		----
*/
//===========================================================================
void Layout::_AddActiveParts( LayoutParts* parts, s32 depth )
{
	// �d���o�^����
	{
		VecParts::iterator	itr	= m_activeParts.begin();
		for( ; itr != m_activeParts.end(); ++itr ) {
			if( (*itr).parts == parts ) {
				return;
			}
		}
	}
	
	PartsInfo	addInfo;

	addInfo.parts	= parts;
	addInfo.depth	= depth;
	
	m_activeParts.push_back( addInfo );
	
}


//===========================================================================
/*!	@brief		�p�[�c���O
	@param		parts	�p�[�c
	@return		----
*/
//===========================================================================
void Layout::_RemoveActiveParts( LayoutParts* parts )
{
	m_activeParts.erase( std::remove( m_activeParts.begin(), m_activeParts.end(), parts ), m_activeParts.end() );
	
}


//===========================================================================
/*!	@brief		�A�N�e�B�u�p�[�c�N���A
	@param		----
	@return		----
*/
//===========================================================================
void Layout::_ClearActiveParts( void )
{
	m_activeParts.clear();
	
}


//===========================================================================
/*!	@brief		�A�N�e�B�u�p�[�c�̘g��`��
	@param		----
	@return		----
*/
//===========================================================================
void Layout::DrawActivePartsFrame( void )
{
	// �\�[�g����̂ň�U�R�s�[
	VecParts	vecDrawParts	= m_activeParts;

	std::sort( vecDrawParts.begin(), vecDrawParts.end() );

	const f32			frameAddSize	= 3.0f;	// �{���̃t���[���T�C�Y�ɉ��Z����T�C�Y

	math::Vector		addPoint;
	graphics::Line		drawLine;
	drawLine.SetRenderMode( graphics::Line::RENDER_MODE_2D );
	drawLine.SetColor( Color( 0x0000FFFF ) );
	
	
	const LayoutParts*	drawParts		= NULL;
	VecParts::iterator	itr				= vecDrawParts.begin();
	for( ; itr != vecDrawParts.end(); ++itr ) {
		drawParts	= (*itr).parts;

		const math::Vector&	partsPos	= drawParts->GetPos();

		// �N���A
		drawLine.ClearPoints();
		
		// ����
		drawLine.AddPoint( partsPos + math::Vector( -frameAddSize, -frameAddSize, 0.0f ) );

		// ����
		drawLine.AddPoint( partsPos + math::Vector( -frameAddSize, drawParts->GetSize().y + frameAddSize, 0.0f ) );
		
		// �E��
		drawLine.AddPoint( partsPos + math::Vector( drawParts->GetSize().x + frameAddSize, drawParts->GetSize().y + frameAddSize, 0.0f ) );

		// �E��
		drawLine.AddPoint( partsPos + math::Vector( drawParts->GetSize().x + frameAddSize, -frameAddSize, 0.0f ) );

		// ����
		drawLine.AddPoint( partsPos + math::Vector( -frameAddSize, -frameAddSize, 0.0f ) );

		// �`��
		drawLine.Draw();

		SystemPrint( partsPos.x - 20, partsPos.y - 25, "(%d, %d)", static_cast<s32>(partsPos.x), static_cast<s32>(partsPos.y) );
	}
	
}




	

//--------------------------------EventObserver--------------------------------

//===========================================================================
/*!	@brief		�{�^�������
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorOver( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorOver( eventButton );
	}
}

//===========================================================================
/*!	@brief		�{�^�����ꂽ
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorOut( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorOut( eventButton );
	}
}


//===========================================================================
/*!	@brief		�{�^�������A�j���[�V�����J�n
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorDownStart( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorDownStart( eventButton );
	}
}

//===========================================================================
/*!	@brief		�{�^�������A�j���[�V�����I��
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorDownEnd( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorDownEnd( eventButton );
	}
}

//===========================================================================
/*!	@brief		�{�^�������ꂽ�A�j���[�V�����J�n
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorUpStart( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorUpStart( eventButton );
	}
}

//===========================================================================
/*!	@brief		�{�^�����ꂽ�A�j���[�V�����I��
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorUpEnd( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorUpEnd( eventButton );
	}
}

//===========================================================================
/*!	@brief		�{�^���z�[���h�J�n
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnHold( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnHold( eventButton );
	}
}






	
}	// namespace graphics
}	// namespace nk