//=============================================================================
/*!	@file	soundManager.h

	@brief	�T�E���h�Ǘ�

	@author	ryunosuke ide
	@date	2013.02.10
*/
//=============================================================================

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__


namespace nk {

namespace sound {




//=============================================================================
/*!
					�T�E���h����
*/
//=============================================================================
class SoundManager {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ������
	static bool			Initialize( void );

	//! �I������
	static bool			Finalize( void );

	//! �I�[�f�B�I�o�^
	//virtual bool		Register( u32 id );

	//! �Đ�
	//virtual bool		Play( void );

	//! ��~
	//virtual bool		Stop( void );
	
private:
	//----------------------�����o�ϐ�-----------------------
	
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			SoundManager();
	virtual~SoundManager();
};
	
}	// namespace sound
	
}	// namespace nk







#endif  // __SOUND_MANAGER_H__