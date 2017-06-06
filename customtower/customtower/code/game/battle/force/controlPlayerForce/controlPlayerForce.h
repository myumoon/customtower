//=============================================================================
/*!	@file	controlPlayerForce.h

	@brief	�v���C���[����R

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================

#ifndef __CONTROL_PLAYER_FORCE_H__
#define __CONTROL_PLAYER_FORCE_H__

#include "../force.h"



namespace game {

namespace battle {

//=============================================================================
/*!
							�v���C���[����R
*/
//=============================================================================
class ControlPlayerForce : public Force {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	virtual void	Initialize( BattleExecutor* battleExec );

	//===========================================================================
	/*!	@brief		�I��
	*/
	//===========================================================================
	virtual void	Terminate( void );

	//===========================================================================
	/*!	@brief		����`�F�b�N
	*/
	//===========================================================================
	virtual void	UpdatePhase_Operate( const OpponentForce& opponent );

protected:

	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			ControlPlayerForce();
	virtual~ControlPlayerForce();
};


}	// namespace battle
	
}	// namespace game



#endif  // __CONTROL_PLAYER_FORCE_H__