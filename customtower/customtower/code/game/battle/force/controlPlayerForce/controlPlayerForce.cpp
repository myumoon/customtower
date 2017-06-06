//=============================================================================
/*!	@file	controlPlayerForce.h

	@brief	�v���C���[����R

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "controlPlayerForce.h"


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
ControlPlayerForce::ControlPlayerForce()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
ControlPlayerForce::~ControlPlayerForce()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void ControlPlayerForce::_Init( void )
{
	
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void ControlPlayerForce::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
	@param		----
	@return		----
*/
//===========================================================================
void ControlPlayerForce::Initialize( BattleExecutor* battleExec )
{
	Force::Initialize( battleExec );
	
	m_characterEmitter.SetPos( nk::math::Vector( 0.0f, 100.0f, 0.0f ) );
	m_characterEmitter.SetDirection( nk::math::Vector( -1.0f, 1.0f, 0.0f ), 10 );
	m_characterEmitter.SetVelocity( 30.0f );
	m_characterEmitter.SetRotation( nk::math::Vector(0.0f, 0.0f, 5.0f) );
 	m_characterEmitter.SetEmitInterval( 30 );
	m_characterEmitter.SetLife( 30 * 60 );
  	m_characterEmitter.Emit();
}


//===========================================================================
/*!	@brief		�I��
	@param		----
	@return		----
*/
//===========================================================================
void ControlPlayerForce::Terminate( void )
{
	Force::Terminate();
}

//===========================================================================
/*!	@brief		����`�F�b�N
	@param		----
	@return		----
*/
//===========================================================================
void ControlPlayerForce::UpdatePhase_Operate( const OpponentForce& opponent )
{
// 	m_characterEmitter.Update();
}



}	// namespace battle

	
}	// namespace game