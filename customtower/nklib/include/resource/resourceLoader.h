//=============================================================================
/*!	@file	resourceLoader.h

	@brief	���\�[�X���[�h

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

#ifndef __RESOURCE_LOADER_H__
#define __RESOURCE_LOADER_H__

#include "../thread/thread.h"
#include "./textureLoadThread.h"
#include "./resourceManager.h"

namespace nk {

namespace resource {

//=============================================================================
/*!
								���\�[�X���[�h
*/
//=============================================================================
class ResourceLoader : public Thread {
private:
	//-----------------------�^��`--------------------------
	struct _FileInfo {
		bool			isImage;
		std::string		fileName;
	};
public:
	
	
	
	
	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//! ���[�h�t�@�C��
	void			Load( const char* path );

	//! �X�V
	//! @return	true.���[�h����
	//! @note	���C���X���b�h����Ă΂Ȃ���΂Ȃ�Ȃ�
	bool			Update( void );


	// ���\�[�X�}�l�[�W���[�o�^
	static void		SetResourceMnager( ResourceManager* mng ) { m_resourceMng = mng; }
	
	
protected:
	void			ThreadFunc( void );
	
private:
	//----------------------�����o�ϐ�-----------------------
	TextureLoadThread*			m_texLoadThread;	//!< �e�N�X�`�����[�h�X���b�h
	std::vector<_FileInfo>		m_vecLoadFiles;		//!< ���[�h�t�@�C��
	bool						m_loadTexComplete;	//!< �e�N�X�`�����[�h��������true
	
	static ResourceManager*		m_resourceMng;		// ���\�[�X�Ǘ�
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			ResourceLoader();
	virtual~ResourceLoader();
};
	
}	// namespace resource
}	// namespace nk






#endif  // __RESOURCE_LOADER_H__