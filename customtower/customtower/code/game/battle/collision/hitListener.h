//=============================================================================
/*!	@file	hitListener.h

	@brief	�q�b�g���ʃ��X�i�[

	@author	ryunosuke ide
	@date	2013.05.29
*/
//=============================================================================


#ifndef __HIT_LISTENER_H__
#define __HIT_LISTENER_H__

#include "collision/boundaryVolume.h"

namespace game {
namespace battle {


class Stage;
class Character;

//=============================================================================
/*!
								�q�b�g���X�i�[
*/
//=============================================================================
class HitListener {
private:
public:
	//-----------------------�^��`--------------------------

	//! �C�x���g�^�C�v
	enum EVENT_TYPE {
		EVENT_TYPE_TARGET_CHECK,		//!< �^�[�Q�b�g�`�F�b�N
		EVENT_TYPE_HIT_RESULT,			//!< �q�b�g����
	};
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�C�x���g�`�F�b�N
	*/
	//===========================================================================
	virtual bool	AcceptEvent( HitListener* target, EVENT_TYPE event ) { return true; }


	//===========================================================================
	/*!	@brief		�q�b�g�^�[�Q�b�g�`�F�b�N
	*/
	//===========================================================================
	virtual bool	IsHitTarget( const Stage* target ) const { return true; }
	virtual bool	IsHitTarget( const Character* target ) const { return true; }

	//===========================================================================
	/*!	@brief		�q�b�g���R�[���o�b�N
	*/
	//===========================================================================
	virtual void	Hit( const Stage* target ) {}
	virtual void	Hit( const Character* target ) {}

	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			HitListener();
	virtual~HitListener();
};

}	// namespace battle

	
}	// namespace game






#endif  // __HIT_LISTENER_H__