/*-------------------------------------------------------------------------
	説　明：レンダリングバッファテクスチャクラス
	作成日：2011/01/23
	更新日：2011/01/23
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
//	レンダリングテクスチャ情報
//-----------------------------------------------
typedef struct {
	u32			width;			//!< 幅
	u32			height;			//!< 高さ
	GLuint		glTexID;		//!< OpenGLテクスチャID
	GLuint		FrameBufferID;	//!< フレームバッファID
	GLuint		RenderBufferID;	//!< レンダーバッファID
} RenderTexInfo;

typedef u32 RenderTexId; //レンダーテクスチャID型 


/*----------------------------------*/
/*			FBOクラス				*/
/*----------------------------------*/
class RenderableTexture {
public:
	bool	Init( void );

	/**	描画可能なテクスチャを生成
	
		@param	outTexId	: 生成したテクスチャを受け取る
		@param	width		: 生成するテクスチャの幅
		@param	height		: 生成するテクスチャの高さ
	*/
	bool	CreateRenderableTexture( RenderTexId *outTexId, u32 width, u32 height );
	bool	CreateRenderableHalfFloatTexture( RenderTexId *outTexId, u32 width, u32 height );


	/*	OpenGL形式のテクスチャIDを取得
		
		@param	RTexId	: 取得したいレンダテクスチャID
		@retval	GLのテクスチャID
	*/
	GLuint	GetTextureID( RenderTexId RTexId );


	/**	描画するテクスチャを指定

		@param	RTexId	: セットするレンダリングID
	*/
	void	SetRenderTarget( RenderTexId RTexId );

	
	/**	描画対象をGLのバッファに戻す
	*/
	void	RestoreRenderTarget( void );

	/**	2Dテクスチャに描画（シェーダーと併せて使う)
	*/
	void	Render2D( RenderTexId RTexId );

	/**	GLtex番のテクスチャ内容をdestFBOTex番にコピー
	*/
	void	CopyGL2FBOTexture( RenderTexId destRTexId, GLuint GLtex );

	/**	テクスチャの内容をスクリーンに描画

		@param	RTexId		テクスチャID
	*/
	void	OverWriteFrameBuffer( RenderTexId RTexId );

	/**	指定したレンダリングテクスチャの内容をクリア

		@param	RTexId		: レンダリングID
	*/
	void	ClearTexBuffer( RenderTexId RTexId );


	void	ClearBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
	}

	//	全要素を破棄
	//---------------------------------------
	void	Destroy();

	//	生成・削除・取得
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
	static RenderableTexture*			m_instance ;	//!< シングルトン
	bool								m_ready;		//!< 使用可能ならtrue
	std::vector<RenderTexInfo>			Info;			//!< テクスチャ情報
	
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
//void OverWriteFrameBuffer( GLuint srctex );  //通常ブレンドでフレームバッファ全画面に指定テクスチャ描画
//void overWriteFrameBufferH( GLuint srctex ); //加算ブレンドでフレームバッファ全画面に指定テクスチャ描画









#endif  // __RENDERBLETEXTURE_H__