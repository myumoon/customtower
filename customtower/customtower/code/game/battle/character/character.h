//=============================================================================
/*!	@file	character.h

	@brief	�L�����N�^�[

	@author	ryunosuke ide
	@date	2013.05.31
*/
//=============================================================================

#ifndef __CHARACTER_H__
#define __CHARACTER_H__


#include "graphics/model.h"
#include "graphics/animationModel.h"
#include "collision/boundaryVolume.h"

#include "system/renderObject.h"
#include "game/battle/battleObject.h"
//#include "game/gameObject.h"
#include "game/battle/collision/hitListener.h"


namespace game {

namespace battle {

class CharacterManager;
class Stage;

//=============================================================================
/*!
								�L�����N�^�[
*/
//=============================================================================
class Character : public BattleObject, public HitListener {
public:
	//-----------------------�^��`--------------------------
	

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
	/*!	@brief		�ړ�
	*/
	//===========================================================================
	virtual void		Move( void );

	//===========================================================================
	/*!	@brief		�U��
	*/
	//===========================================================================
	virtual void		Attack( void ) {}
	
	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	virtual void		Render( void ) {}

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
	virtual void		Hit( const Stage* target );
	virtual void		Hit( const Character* target );

	//===========================================================================
	/*!	@brief		�L�����N�^�[�}�l�[�W���[�Z�b�g
	*/
	//===========================================================================
	void				SetCharacterManager( const CharacterManager* mng );

	//===========================================================================
	/*!	@brief		�ړ����x�ݒ�
	*/
	//===========================================================================
	void				SetMoveSpeed( f32 speed );
	
protected:

	//===========================================================================
	/*!	@brief		�E�ړ�
	*/
	//===========================================================================
	virtual void			MoveRight( void );

	//===========================================================================
	/*!	@brief		���ړ�
	*/
	//===========================================================================
	virtual void			MoveLeft( void );
	
	//===========================================================================
	/*!	@brief		�L�����N�^�[�}�l�[�W���[�擾
	*/
	//===========================================================================
	const CharacterManager*	GetCharacterManager( void ) const;

protected:
	//----------------------�����o�ϐ�-----------------------
	const CharacterManager*		m_characterManager;		//!< �L�����N�^�[�}�l�[�W���[
	nk::BVSphere				m_bvSphere;				//!< ������

	f32							m_moveSpeed;			//!< �ړ����x
	f32							m_moveRotation;			//!< �ړ���]��
// 	nk::math::Quaternion		m_moveRotation;			//!< �ړ���]��
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );


public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Character( void );
			Character( const CharacterManager* mng );
	virtual~Character( void );
};


}	// namespace battle
	
}	// namespace game



#endif  // __CHARACTER_H__