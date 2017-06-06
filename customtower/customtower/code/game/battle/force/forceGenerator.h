//=============================================================================
/*!	@file	forceGenerator.h

	@brief	�R����

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __FORCE_GENERATOR_H__
#define __FORCE_GENERATOR_H__

#include <vector>
#include "game/battle/battleInfo.h"
#include "game/battle/generator.h"
//#include "game/battle/battleExecutor.h"


namespace game {

namespace battle {

class Force;

//! �R�ꗗ
struct ForceList {
	std::vector<Force*>	forces;
};

//=============================================================================
/*!
								�R�W�F�l���[�^�[
*/
//=============================================================================
class ForceGenerator : public Generator<ForceList> {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
// 	const std::vector<Force*>&	Generate( void );
	ForceList*					Generate( void );

	//===========================================================================
	/*!	@brief		�폜
	*/
	//===========================================================================
	virtual void				Delete( void );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
// 	std::vector<Force*>			m_forces;		//!< �R
	ForceList*					m_forceList;	//!< �R

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			ForceGenerator();
	virtual~ForceGenerator();
};



}	// namespace battle
	
}	// namespace game


#endif  // __FORCE_GENERATOR_H__