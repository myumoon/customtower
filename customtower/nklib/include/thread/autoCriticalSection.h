//=============================================================================
/*!	@file	autoCriticalSection.h

	@brief	�~���[�e�b�N�X

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

#ifndef __AUTO_CRITICAL_SECTION_H__
#define __AUTO_CRITICAL_SECTION_H__

#include "./threadFunc.h"
#include "./criticalSection.h"

#define SCOPE_CRITICAL_SECTION(criticalSection)	nk::AutoCriticalSection _autoCriticalSection(criticalSection)

namespace nk {

//=============================================================================
/*!
								�~���[�e�b�N�X
*/
//=============================================================================
class AutoCriticalSection {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
private:
	//----------------------�����o�ϐ�-----------------------
	CriticalSection*		m_criticalSection;			//!< �N���e�B�J���Z�N�V����
	
	//-----------------------���\�b�h------------------------

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			AutoCriticalSection( CriticalSection& rhs );
			AutoCriticalSection( const CriticalSection& rhs );
	virtual~AutoCriticalSection();
	
private:
	AutoCriticalSection();
};

	
}	// namespace nk






#endif  // __AUTO_CRITICAL_SECTION_H__