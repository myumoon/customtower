//=============================================================================
/*!	@file	�X�e�[�W

	@brief	�X�e�[�W

	@author	ryunosuke ide
	@date	2013.05.27
*/
//=============================================================================

#ifndef __STAGE_H__
#define __STAGE_H__

#include "graphics/model.h"
#include "graphics/animationModel.h"
#include "collision/boundaryVolume.h"

#include "game/gameObject.h"
#include "game/battle/collision/hitListener.h"

#include "game/battle/battleObject.h"

namespace game {

namespace battle {

class Character;

//=============================================================================
/*!
								�X�e�[�W
*/
//=============================================================================
class Stage : public BattleObject, public HitListener {
public:
	//-----------------------�^��`--------------------------

	//! �X�e�[�W���
	struct StageInfo {
		f32					radius;			//!< ���a
		nk::math::Vector	centerPos;		//!< ���S�ʒu
		f32					gravity;		//!< �d��
		f32					airResistance;	//!< ��C��R
	};

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�o�g��������������
	*/
	//===========================================================================
	void				InitializeForBattle( BattleExecutor* battleExec );

	//===========================================================================
	/*!	@brief		�o�g�����Ŏ��I������
	*/
	//===========================================================================
	void				TerminateForBattle( void );
	
	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual bool		Execute( void );

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	virtual void		Render( void );

	//===========================================================================
	/*!	@brief		�^�[�Q�b�g�`�F�b�N
	*/
	//===========================================================================
	virtual bool		AcceptEvent( HitListener* target, EVENT_TYPE event )
	{
		switch( event ) {
			case EVENT_TYPE_TARGET_CHECK : {
				return target->IsHitTarget( this );
			} break;
			
			case EVENT_TYPE_HIT_RESULT : {
				target->Hit( this );
			} break;
		}
		
		return false;
	}

	//===========================================================================
	/*!	@brief		�Ώۃ`�F�b�N
	*/
	//===========================================================================
	virtual bool		IsHitTarget( const Stage* target ) const { return true; }
	virtual bool		IsHitTarget( const Character* target ) const { return true; }

	//===========================================================================
	/*!	@brief		�q�b�g����
	*/
	//===========================================================================
	virtual void		Hit( const Stage* target ) {}
	virtual void		Hit( const Character* target ) {}


	//===========================================================================
	/*!	@brief		��{���擾
	*/
	//===========================================================================
	const StageInfo&	GetInfo( void ) const;
	
protected:
	//===========================================================================
	/*!	@brief		���[�J���X�V
	*/
	//===========================================================================
	virtual bool		ExecuteLocal( void ) { return true; }

protected:
	//----------------------�����o�ϐ�-----------------------
	nk::BVSphere				m_bvSphere;
	StageInfo					m_stageInfo;		//!< �X�e�[�W���
	nk::graphics::Model*		m_stageModel;		//!< ���f��
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Stage();
	virtual~Stage();
};


}	// namespace battle
	
}	// namespace game






#endif  // __STAGE_H__