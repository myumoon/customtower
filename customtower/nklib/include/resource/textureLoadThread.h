//=============================================================================
/*!	@file	textureLoadThread.h

	@brief	�e�N�X�`�����[�h�X���b�h

	@author	ryunosuke ide
	@date	2013.03.09
*/
//=============================================================================


#ifndef __TEXTURE_LOAD_THREAD_H__
#define __TEXTURE_LOAD_THREAD_H__

#include <string>
#include "../thread/thread.h"
#include "./textureUtility.h"


namespace nk {


namespace resource {


class Texture;

//=============================================================================
/*!
						�e�N�X�`�����[�h�X���b�h
*/
//=============================================================================
class TextureLoadThread : public Thread {
private:
	//-----------------------�^��`--------------------------
	struct _LoadSurface {
		std::string		path;
		ImageSurface	surface;

		_LoadSurface() {
		}
	};
	typedef std::vector<_LoadSurface>		VecSurface;
	
public:
	
	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ���[�h�e�N�X�`����ǉ�
	void				Add( const char* path );

	//! �S�t�@�C�����[�h���Ă�����true��Ԃ�
	bool				IsComplete( void ) const;

	//! ���[�h��������true��Ԃ�
	bool				IsComplete( const char* path ) const;

	//! �e�N�X�`�����K��
	//! ���C���X���b�h������s���Ă�������
	Texture*			PopTexture( const char* path );

protected:
	//! �X���b�h����
	virtual void		ThreadFunc( void );
	
private:
	Texture*			_CreateTexture( const _LoadSurface& surface ) const;
	
	//! ���[�h
	//ImageSurface*		_LoadSurface( const char* path );
	
	//----------------------�����o�ϐ�-----------------------
	VecSurface			m_vecSurface;			//!< �e�N�X�`��
	//Mutex*				m_mutex;				//!< �~���[�e�b�N�X
	CriticalSection		m_criticalSection;		//!< �N���e�B�J���Z�N�V����
	bool				m_completed;			//!< ���[�h����
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			TextureLoadThread();
	virtual~TextureLoadThread();
};


}	// namespace resource

}	// namespace nk

#endif  // __TEXTURE_LOAD_THREAD_H__