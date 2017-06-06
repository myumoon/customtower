//=============================================================================
/*!	@file	character01.h

	@brief	�L�����N�^01

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __CHARACTER01_H__
#define __CHARACTER01_H__

#include "../character.h"


namespace game {
namespace battle {


//=============================================================================
/*!
							�e�X�g�L����
*/
//=============================================================================
class Character01 : public Character {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�ړ�
	*/
	//===========================================================================
	virtual void		Move( void );

	//===========================================================================
	/*!	@brief		�`��
	*/
	//===========================================================================
	virtual void		Render( void );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	nk::graphics::Model			m_model;

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Character01( void );
			Character01( const CharacterManager* mng );
	virtual~Character01( void );
};

}	// namespace battle

	
}	// namespace game


#endif  // __CHARACTER01_H__