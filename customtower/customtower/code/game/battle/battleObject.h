//=============================================================================
/*!	@file	battleObject.h

	@brief	�ΐ�I�u�W�F�N�g

	@author	ryunosuke ide
	@date	2013.06.04
*/
//=============================================================================


#ifndef __BATTLE_OBJECT_H__
#define __BATTLE_OBJECT_H__

#include "game/gameObject.h"
#include "system/renderObject.h"
#include "earth/earthObject.h"

namespace game {
namespace battle {

class BattleExecutor;



//=============================================================================
/*!
							�ΐ�I�u�W�F�N�g
*/
//=============================================================================
class BattleObject : public EarthObject, public GameObject, public RenderObject {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�o�g��������������
	*/
	//===========================================================================
	virtual void				InitializeForBattle( BattleExecutor* battleExec )
	{
		m_battleExec	= battleExec;
	}

	//===========================================================================
	/*!	@brief		�o�g�����Ŏ��I������
	*/
	//===========================================================================
	virtual void				TerminateForBattle( void ) {}

	//===========================================================================
	/*!	@brief		�d�͈ړ�
	*/
	//===========================================================================
// 	virtual void				FreeFall( void );

	//===========================================================================
	/*!	@brief		�ʒu�ݒ�
	*/
	//===========================================================================
// 	void					 	SetPos( const nk::math::Vector& pos );

	//===========================================================================
	/*!	@brief		�ʒu�擾
	*/
	//===========================================================================
// 	const nk::math::Vector& 	GetPos( void ) const;

	//===========================================================================
	/*!	@brief		�O��ʒu�ݒ�
	*/
	//===========================================================================
 	void					 	SetPrevPos( const nk::math::Vector& pos );

	//===========================================================================
	/*!	@brief		�O��ʒu�擾
	*/
	//===========================================================================
 	const nk::math::Vector& 	GetPrevPos( void ) const;
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

protected:
	//----------------------�����o�ϐ�-----------------------
// 	nk::math::Vector		m_nowPos;			//!< ���݈ʒu
	nk::math::Vector		m_prevPos;			//!< �O��ʒu
	nk::math::Vector		m_direction;		//!< �����Ă������
// 	nk::math::Vector		m_rotation;			//!< ��]��

	BattleExecutor*			m_battleExec;		//!< �o�g��
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			BattleObject();
	virtual~BattleObject();
};

}	// namespace battle

	
}	// namespace game







#endif  // __BATTLE_OBJECT_H__