/*-------------------------------------------------------------------------
	���@���F�����_�����O�o�b�t�@�e�N�X�`���N���X
	�쐬���F2011/01/23
	�X�V���F2011/01/23
--------------------------------------------------------------------------*/

#ifndef __RENDERBLETEXTURE_H__
#define __RENDERBLETEXTURE_H__

#include <vector>
#if defined(NK_USE_SDLGL)
#include <SDL/SDL_opengl.h>
#endif
#include <GL/glut.h>
#include <GL/glext.h>
//#include <GL/glxext.h>
//#include "glxext.h"
//#include "wglext.h"
#include "../typedef.h"


#define RENDERABLE_TEXTURE RenderableTexture::GetInstance()


//-----------------------------------------------
//	�����_�����O�e�N�X�`�����
//-----------------------------------------------
typedef struct {
	u32			width;			//!< ��
	u32			height;			//!< ����
	GLuint		glTexID;		//!< OpenGL�e�N�X�`��ID
	GLuint		FrameBufferID;	//!< �t���[���o�b�t�@ID
	GLuint		RenderBufferID;	//!< �����_�[�o�b�t�@ID
} RenderTexInfo;

typedef u32 RenderTexId; //�����_�[�e�N�X�`��ID�^ 


/*----------------------------------*/
/*			FBO�N���X				*/
/*----------------------------------*/
class RenderableTexture {
public:
	bool	Init( void );

	/**	�`��\�ȃe�N�X�`���𐶐�
	
		@param	outTexId	: ���������e�N�X�`�����󂯎��
		@param	width		: ��������e�N�X�`���̕�
		@param	height		: ��������e�N�X�`���̍���
	*/
	bool	CreateRenderableTexture( RenderTexId *outTexId, u32 width, u32 height );
	bool	CreateRenderableHalfFloatTexture( RenderTexId *outTexId, u32 width, u32 height );


	/*	OpenGL�`���̃e�N�X�`��ID���擾
		
		@param	RTexId	: �擾�����������_�e�N�X�`��ID
		@retval	GL�̃e�N�X�`��ID
	*/
	GLuint	GetTextureID( RenderTexId RTexId );


	/**	�`�悷��e�N�X�`�����w��

		@param	RTexId	: �Z�b�g���郌���_�����OID
	*/
	void	SetRenderTarget( RenderTexId RTexId );

	
	/**	�`��Ώۂ�GL�̃o�b�t�@�ɖ߂�
	*/
	void	RestoreRenderTarget( void );

	/**	2D�e�N�X�`���ɕ`��i�V�F�[�_�[�ƕ����Ďg��)
	*/
	void	Render2D( RenderTexId RTexId );

	/**	GLtex�Ԃ̃e�N�X�`�����e��destFBOTex�ԂɃR�s�[
	*/
	void	CopyGL2FBOTexture( RenderTexId destRTexId, GLuint GLtex );

	/**	�e�N�X�`���̓��e���X�N���[���ɕ`��

		@param	RTexId		�e�N�X�`��ID
	*/
	void	OverWriteFrameBuffer( RenderTexId RTexId );

	/**	�w�肵�������_�����O�e�N�X�`���̓��e���N���A

		@param	RTexId		: �����_�����OID
	*/
	void	ClearTexBuffer( RenderTexId RTexId );


	void	ClearBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
	}

	//	�S�v�f��j��
	//---------------------------------------
	void	Destroy();

	//	�����E�폜�E�擾
	//---------------------------------------
	static void Create() {
		if( !m_instance ) {
			m_instance = new RenderableTexture();
		}
	}
	static void Delete() {
		delete m_instance;
		m_instance = NULL;
	}
	static RenderableTexture *GetInstance() {
		return m_instance;
	}
	
private:
	RenderableTexture() { Init(); }
	static RenderableTexture*			m_instance ;	//!< �V���O���g��
	bool								m_ready;		//!< �g�p�\�Ȃ�true
	std::vector<RenderTexInfo>			Info;			//!< �e�N�X�`�����
	
	PFNGLGENFRAMEBUFFERSEXTPROC         glGenFramebuffers;
	PFNGLBINDFRAMEBUFFEREXTPROC         glBindFramebuffer;
	PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    glFramebufferTexture2D;
	PFNGLGENRENDERBUFFERSEXTPROC        glGenRenderbuffers;
	PFNGLBINDRENDERBUFFEREXTPROC        glBindRenderbuffer;
	PFNGLRENDERBUFFERSTORAGEEXTPROC     glRenderbufferStorage;
	PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbuffer;
	PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  glCheckFramebufferStatus;
	PFNGLGENERATEMIPMAPEXTPROC          glGenerateMipmapExt;

	bool _CheckStatus();
};


//void CopyTexture( u32 destTex, GLuint texID );
//void OverWriteFrameBuffer( GLuint srctex );  //�ʏ�u�����h�Ńt���[���o�b�t�@�S��ʂɎw��e�N�X�`���`��
//void overWriteFrameBufferH( GLuint srctex ); //���Z�u�����h�Ńt���[���o�b�t�@�S��ʂɎw��e�N�X�`���`��









#endif  // __RENDERBLETEXTURE_H__