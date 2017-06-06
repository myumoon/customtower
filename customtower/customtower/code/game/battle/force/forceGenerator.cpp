//=============================================================================
/*!	@file	forceGenerator.h

	@brief	�R����

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "forceGenerator.h"

#include "general.h"

#include "force.h"
#include "game/battle/battleInfo.h"
#include "controlPlayerForce/controlPlayerForce.h"

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
ForceGenerator::ForceGenerator()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
ForceGenerator::~ForceGenerator()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void ForceGenerator::_Init( void )
{
	m_forceList	= new ForceList();
	m_forceList->forces.reserve( BattleInfo::MAX_CONTROLLER_NUM );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void ForceGenerator::_Term( void )
{
	Delete();
	nk::SafeDelete( m_forceList );

}


//===========================================================================
/*!	@brief		����
	@param		m_battleInfo	�������
	@return		----
*/
//===========================================================================
// const std::vector<Force*>& ForceGenerator::Generate( void )
ForceList* ForceGenerator::Generate( void )
{
	Delete();

	Force*	createForce	= NULL;

	for( s32 forceNo = 0; forceNo < m_battleInfo.contorollerNum; ++forceNo ) {
		createForce	= NULL;
		
		switch( m_battleInfo.contorollerTypes[forceNo] ) {
			
			case BattleInfo::CONTOROLLER_TYPE_USER : {
				createForce	= new ControlPlayerForce();
			} break;

			default : {
				// @@@@@
				createForce	= new ControlPlayerForce();
			} break;
		}

		if( createForce ) {
			m_forceList->forces.push_back( createForce );
		}
	}

	return m_forceList;
}



//===========================================================================
/*!	@brief		�폜
	@param		----
	@return		----
*/
//===========================================================================
void ForceGenerator::Delete( void )
{
	NULL_ASSERT( m_forceList );

	for( u32 i = 0; i < m_forceList->forces.size(); ++i ) {
		nk::SafeDelete( m_forceList->forces[i] );
	}
	m_forceList->forces.clear();
	
// 	for( u32 i = 0; i < m_forces.size(); ++i ) {
// 		nk::SafeDelete( m_forces[i] );
// 	}
// 	m_forces.clear();

}


}	// namespace battle


	
}	// namespace game