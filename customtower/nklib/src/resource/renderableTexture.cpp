/*-------------------------------------------------------------------------
	���@���F�����_�����O�o�b�t�@�e�N�X�`���N���X
	�쐬���F2011/01/23
	�X�V���F2011/01/23
--------------------------------------------------------------------------*/
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include "../../include/general.h"
#include "../../include/resource/renderableTexture.h"

//===============================================
//	������
//===============================================
RenderableTexture* RenderableTexture::m_instance = NULL;




//========================================================================
//	���@�e�F������
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
bool RenderableTexture::Init()
{
	m_ready	= false;
	
	// ���������K�v�炵��
	//if( cgGLIsProfileSupported() ) {
	//}

	Info.reserve( 64 );

	//�t���[���o�b�t�@�I�u�W�F�N�g�֘A��GL�g���֐��̊֐��|�C���^���Q�b�g
	glGenFramebuffers =
		(PFNGLGENFRAMEBUFFERSEXTPROC)wglGetProcAddress("glGenFramebuffersEXT");
	glBindFramebuffer =
		(PFNGLBINDFRAMEBUFFEREXTPROC)wglGetProcAddress("glBindFramebufferEXT");
	glFramebufferTexture2D =
		(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)wglGetProcAddress("glFramebufferTexture2DEXT");
	glGenRenderbuffers =
		(PFNGLGENRENDERBUFFERSEXTPROC)wglGetProcAddress("glGenRenderbuffersEXT");
	glBindRenderbuffer =
		(PFNGLBINDRENDERBUFFEREXTPROC)wglGetProcAddress("glBindRenderbufferEXT");
	glRenderbufferStorage =
		(PFNGLRENDERBUFFERSTORAGEEXTPROC)wglGetProcAddress("glRenderbufferStorageEXT");
	glFramebufferRenderbuffer =
		(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)wglGetProcAddress("glFramebufferRenderbufferEXT");
	glCheckFramebufferStatus =
		(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)wglGetProcAddress("glCheckFramebufferStatusEXT");
	glGenerateMipmapExt =
		(PFNGLGENERATEMIPMAPEXTPROC)wglGetProcAddress("glGenerateMipmapEXT");
	
	if( !glGenFramebuffers  || !glBindFramebuffer || !glFramebufferTexture2D ||
		!glGenRenderbuffers || !glBindRenderbuffer|| !glRenderbufferStorage  ||
		!glFramebufferRenderbuffer || !glCheckFramebufferStatus || !glGenerateMipmapExt)
	{
		//�|�C���^���擾�ł��Ȃ������ꍇ
		RELEASE_PRINTF("Frame Buffer Object Initialization Failed..\n");
		//exit(-1);
		return false;
	}

	m_ready	= true;

	return true;
}



/*
void CreateRenderingBuffer( OUT GLuint *pFrame, OUT GLuint *pColor, OUT GLuint *pDepth, IN int width, IN int height )
{
�@�@// �t���[���o�b�t�@�I�u�W�F�N�g�A�f�v�X�ƃJ���[�p�̃e�N�X�`�����쐬
�@�@glGenFramebuffersEXT( 1, pFrame );
�@�@glGenTextures( 1, pColor );
�@�@glGenTextures( 1, pDepth );

�@�@// �Ƃ肠�����A���J���[�o�b�t�@�� HALF �^
�@�@glBindTexture( GL_TEXTURE_2D, *pColor );
�@�@glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width, height, 0, GL_RGBA, GL_HALF_FLOAT_ARB, NULL );

�@�@// �[�x�o�b�t�@���쐬
�@�@glBindTexture( GL_TEXTURE_2D, *pDepth );
�@�@glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );

�@�@// �e�N�X�`�����t���[���o�b�t�@�I�u�W�F�N�g�Ƀo�C���h
�@�@glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, *pFrame );
�@�@glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *pColor, 0 );
�@�@glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, *pDepth, 0 );

�@�@// �f�t�H���g�̃����_�[�^�[�Q�b�g�ɖ߂�
�@�@glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}
*/
//========================================================================
//	���@�e�F�`��\�ȃe�N�X�`���𐶐�
//	���@���FRTexID	: ���������e�N�X�`����ID���i�[����ꏊ�ւ̃|�C���^(GL�̃e�N�X�`��ID�Ƃ͈Ⴄ)
//			width	: �e�N�X�`����
//			height	: �e�N�X�`����
//	�߂�l�F
//	 memo �F
//========================================================================
bool RenderableTexture::CreateRenderableTexture( RenderTexId *outTexId, u32 width, u32 height )
{
	if( !m_ready ) {
		return false;
	}
	RenderTexInfo tmpTexInfo;
	GLuint  tmpFBID, tmpRBID, TexID;

	// �e�N�X�`���쐬
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width, height, 0, GL_RGBA, GL_HALF_FLOAT_ARB, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// �t���[���o�b�t�@�ƃ����_�[�o�b�t�@�쐬
	glGenFramebuffers(1, &tmpFBID);
	glGenRenderbuffers(1, &tmpRBID);

	// �t���[���o�b�t�@�I�u�W�F�N�g�Ƀe�N�X�`����Z�o�b�t�@�p��
	// �����_�[�o�b�t�@������������
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, tmpFBID);
	glBindRenderbuffer(GL_RENDERBUFFER_EXT, tmpRBID);
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, TexID, 0);
	glRenderbufferStorage(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, tmpRBID);

	// �e�N�X�`���̃o�C���h����
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbuffer(GL_RENDERBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// �X�e�[�^�X�`�F�b�N
	if( !_CheckStatus() ) {
		return false;
	}


	// �e�N�X�`�������L�^
	tmpTexInfo.width			= width;
	tmpTexInfo.height			= height;
	tmpTexInfo.glTexID			= TexID;
	tmpTexInfo.FrameBufferID	= tmpFBID;
	tmpTexInfo.RenderBufferID	= tmpRBID;

	Info.push_back(tmpTexInfo);

	*outTexId					= Info.size() - 1;
	
	return true;
}



//========================================================================
//	���@�e�F���������_�e�N�X�`�������
//	���@���FRTexID	: �e���_�����O�e�N�X�`��ID���i�[����|�C���^
//			width	: �e�N�X�`���̕�
//			height	: �e�N�X�`���̍���
//	�߂�l�F
//	 memo �F
//========================================================================
bool RenderableTexture::CreateRenderableHalfFloatTexture( RenderTexId *outTexId, u32 width, u32 height )
{
	if( !m_ready ) {
		return false;
	}
	
	RenderTexInfo tmpTexInfo;
	GLuint   tmpFBID,tmpRBID,TexID;

	// �e�N�X�`���쐬
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width, height, 0,
				  GL_RGBA, GL_HALF_FLOAT_ARB, NULL);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	// �t���[���o�b�t�@�ƃ����_�[�o�b�t�@�쐬
	glGenFramebuffers ( 1, &tmpFBID );
	glGenRenderbuffers( 1, &tmpRBID );

	// �t���[���o�b�t�@�I�u�W�F�N�g�Ƀe�N�X�`����Z�o�b�t�@�p��
	// �����_�[�o�b�t�@������������
	glBindFramebuffer(			GL_FRAMEBUFFER_EXT,	 tmpFBID );
	glBindRenderbuffer(			GL_RENDERBUFFER_EXT, tmpRBID );
	glFramebufferTexture2D(		GL_FRAMEBUFFER_EXT,  GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, TexID, 0 );
	glRenderbufferStorage(		GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height );
	glFramebufferRenderbuffer(	GL_FRAMEBUFFER_EXT,  GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, tmpRBID );

	// �e�N�X�`���̃o�C���h����
	glBindFramebuffer ( GL_FRAMEBUFFER_EXT , 0);
	glBindRenderbuffer( GL_RENDERBUFFER_EXT, 0);
	glBindTexture     ( GL_TEXTURE_2D, 0 );
	
	// �X�e�[�^�X�`�F�b�N
	if( !_CheckStatus() ) {
		return false;
	}


	// �e�N�X�`�������L�^
	tmpTexInfo.width          = width  ;
	tmpTexInfo.height         = height ;
	tmpTexInfo.glTexID        = TexID  ;
	tmpTexInfo.FrameBufferID  = tmpFBID;
	tmpTexInfo.RenderBufferID = tmpRBID;

	Info.push_back( tmpTexInfo );
	*outTexId = (GLuint)Info.size() - 1;
	
	return true;
}



//========================================================================
//	���@�e�F�����_�����O����GL�e�N�X�`��ID���擾
//	���@���F�����_�����OID
//	�߂�l�FGL�e�N�X�`��ID
//	 memo �F
//========================================================================
GLuint RenderableTexture::GetTextureID(RenderTexId RTexId)
{
	if( !m_ready ) {
		return -1;
	}
	ASSERT( 0 <= RTexId &&  RTexId < Info.size(), "RenderTexId : %d", RTexId );

	return Info[RTexId].glTexID;
}


//========================================================================
//	���@�e�F�`��^�[�Q�b�g��ݒ�
//	���@���F�����_�����OID
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void RenderableTexture::SetRenderTarget(RenderTexId RTexId)
{
	if( !m_ready ) {
		return;
	}
	ASSERT( 0 <= RTexId &&  RTexId < Info.size(), "RenderTexId : %d", RTexId );

	// �e�N�X�`���ւ̃����_�����O
	glEnable( GL_TEXTURE_2D );
	glBindFramebuffer( GL_FRAMEBUFFER_EXT, Info[RTexId].FrameBufferID );
	glFramebufferTexture2D( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, Info[RTexId].glTexID, 0 );
	
	// �`�揈��
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(50.0f, (f64)Info[RTexId].width / (f64)Info[RTexId].height, 0.1, 10000.0);
	//glViewport(0, 0, Info[RTexId].width, Info[RTexId].height);

	//glMatrixMode(GL_MODELVIEW);
}


//========================================================================
//	���@�e�F�`��Ώۂ�GL�ɖ߂�
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void RenderableTexture::RestoreRenderTarget()
{
	if( !m_ready ) {
		return;
	}
	glBindFramebuffer( GL_FRAMEBUFFER_EXT, 0 );

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(50.0, 1024.0 / 768.0, 0.1, 1000.0);
	//gluPerspective(50.0, (f64)SYSTEM->GetScreenWidth() / (f64)SYSTEM->GetScreenHeight(), 0.1, 1000.0);
	//glViewport(0, 0, 1024.0, 1024.0);

	//glMatrixMode(GL_MODELVIEW);
}


//===========================================================================
/*!	@brief	�e�N�X�`���̓��e���N���A
	@param	RTexId		: �����_�����OID
	@return	----
*/
//===========================================================================
void RenderableTexture::ClearTexBuffer( RenderTexId RTexId )
{
	if( !m_ready ) {
		return;
	}
	ASSERT( 0 <= RTexId &&  RTexId < Info.size(), "RenderTexId : %d", RTexId );

	SetRenderTarget( RTexId );
	
	
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );


	RestoreRenderTarget();

}

//========================================================================
//	���@�e�F�S���e��j��
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F�v���O�����I�����Ɏg�p����
//========================================================================
void RenderableTexture::Destroy()
{
	if( !m_ready ) {
		return;
	}
	
	for(u32 i = 0; i < Info.size(); i++)
	{
		glDeleteTextures( 1, &(Info[i].glTexID) );
	}

	Info.clear();
}


//========================================================================
//	���@�e�F2D�e�N�X�`���ɕ`��i�V�F�[�_�[�ƕ����Ďg��)
//	���@���F�����_�����OID
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void RenderableTexture::Render2D( RenderTexId RTexId )
{
	if( !m_ready ) {
		return;
	}
	GetInstance()->SetRenderTarget( RTexId );
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin( GL_QUADS );

		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -1.0f,-1.0f, 0.0f );

		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 0.0f );
		
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f,  1.0f, 0.0f );

		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, 0.0f );

	glEnd();
	GetInstance()->RestoreRenderTarget();
}



//========================================================================
//	���@�e�FGLtex�Ԃ̃e�N�X�`�����e��destFBOTex�ԂɃR�s�[
//	���@���F
//	�߂�l�F
//	 memo �F
//========================================================================
void RenderableTexture::CopyGL2FBOTexture( RenderTexId destFBOTex, GLuint GLtex )
{
	if( !m_ready ) {
		return;
	}
	
	GetInstance()->SetRenderTarget( destFBOTex );
	// z��r�؂�
	glDisable( GL_DEPTH_TEST );

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, GLtex );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// �����_�[�^�[�Q�b�gdestFBOTex��GLtex�e�N�X�`�����R�s�[
	// �e�N�X�`���`��Ȃ̂�UV��V�l�𔽓]�����Ă��邱�Ƃɒ��ӁB

	glBegin( GL_QUADS );

		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -1.0f,-1.0f, 0.0f );

		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 0.0f );
		
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f,  1.0f, 0.0f );

		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, 0.0f );

	glEnd();

    glEnable( GL_DEPTH_TEST );
	GetInstance()->RestoreRenderTarget();
}



void RenderableTexture::OverWriteFrameBuffer( RenderTexId RTexId )
{
	if( !m_ready ) {
		return;
	}
	GLuint srctex = GetInstance()->GetTextureID( RTexId );
	// z��r�؂�
	glDisable( GL_DEPTH_TEST );

	// �X�N���[���֒��ڕ`��
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, srctex );
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`���`��Ȃ̂�UV��V�l�𔽓]�����Ă��邱�Ƃɒ��ӁB
	glBegin( GL_QUADS );

		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -1.0f,-1.0f, 0.0f );

		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 0.0f );
		
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f,  1.0f, 0.0f );

		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, 0.0f );

	glEnd();
	glEnable( GL_DEPTH_TEST );
}




//========================================================================
//	���@�e�F���݂̏�Ԃ��擾
//	���@���F�Ȃ�
//	�߂�l�Ftrue	: ����
//			false	: �G���[
//	 memo �F
//========================================================================
bool RenderableTexture::_CheckStatus() 
{ 
	GLenum status; 
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT); 
	switch(status) { 
		case GL_FRAMEBUFFER_COMPLETE_EXT: 
			return true;
			break; 
		case GL_FRAMEBUFFER_UNSUPPORTED_EXT: 
			PRINTF( "FBO error : choose different formats\n" ); 
			break; 
		default: 
			PRINTF( "FBO error; will fail on all hardware: %04x\n", status); 
	} 
	return false;
}


