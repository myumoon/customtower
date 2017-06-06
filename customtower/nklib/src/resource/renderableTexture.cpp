/*-------------------------------------------------------------------------
	説　明：レンダリングバッファテクスチャクラス
	作成日：2011/01/23
	更新日：2011/01/23
--------------------------------------------------------------------------*/
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include "../../include/general.h"
#include "../../include/resource/renderableTexture.h"

//===============================================
//	初期化
//===============================================
RenderableTexture* RenderableTexture::m_instance = NULL;




//========================================================================
//	内　容：初期化
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
bool RenderableTexture::Init()
{
	m_ready	= false;
	
	// 初期化が必要らしい
	//if( cgGLIsProfileSupported() ) {
	//}

	Info.reserve( 64 );

	//フレームバッファオブジェクト関連のGL拡張関数の関数ポインタをゲット
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
		//ポインタを取得できなかった場合
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
　　// フレームバッファオブジェクト、デプスとカラー用のテクスチャを作成
　　glGenFramebuffersEXT( 1, pFrame );
　　glGenTextures( 1, pColor );
　　glGenTextures( 1, pDepth );

　　// とりあえず、作るカラーバッファは HALF 型
　　glBindTexture( GL_TEXTURE_2D, *pColor );
　　glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width, height, 0, GL_RGBA, GL_HALF_FLOAT_ARB, NULL );

　　// 深度バッファも作成
　　glBindTexture( GL_TEXTURE_2D, *pDepth );
　　glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );

　　// テクスチャをフレームバッファオブジェクトにバインド
　　glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, *pFrame );
　　glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *pColor, 0 );
　　glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, *pDepth, 0 );

　　// デフォルトのレンダーターゲットに戻す
　　glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}
*/
//========================================================================
//	内　容：描画可能なテクスチャを生成
//	引　数：RTexID	: 生成したテクスチャのIDを格納する場所へのポインタ(GLのテクスチャIDとは違う)
//			width	: テクスチャ幅
//			height	: テクスチャ高
//	戻り値：
//	 memo ：
//========================================================================
bool RenderableTexture::CreateRenderableTexture( RenderTexId *outTexId, u32 width, u32 height )
{
	if( !m_ready ) {
		return false;
	}
	RenderTexInfo tmpTexInfo;
	GLuint  tmpFBID, tmpRBID, TexID;

	// テクスチャ作成
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width, height, 0, GL_RGBA, GL_HALF_FLOAT_ARB, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// フレームバッファとレンダーバッファ作成
	glGenFramebuffers(1, &tmpFBID);
	glGenRenderbuffers(1, &tmpRBID);

	// フレームバッファオブジェクトにテクスチャとZバッファ用の
	// レンダーバッファを結合させる
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, tmpFBID);
	glBindRenderbuffer(GL_RENDERBUFFER_EXT, tmpRBID);
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, TexID, 0);
	glRenderbufferStorage(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, tmpRBID);

	// テクスチャのバインド解除
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbuffer(GL_RENDERBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// ステータスチェック
	if( !_CheckStatus() ) {
		return false;
	}


	// テクスチャ情報を記録
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
//	内　容：浮動小数点テクスチャを作る
//	引　数：RTexID	: テンダリングテクスチャIDを格納するポインタ
//			width	: テクスチャの幅
//			height	: テクスチャの高さ
//	戻り値：
//	 memo ：
//========================================================================
bool RenderableTexture::CreateRenderableHalfFloatTexture( RenderTexId *outTexId, u32 width, u32 height )
{
	if( !m_ready ) {
		return false;
	}
	
	RenderTexInfo tmpTexInfo;
	GLuint   tmpFBID,tmpRBID,TexID;

	// テクスチャ作成
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width, height, 0,
				  GL_RGBA, GL_HALF_FLOAT_ARB, NULL);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	// フレームバッファとレンダーバッファ作成
	glGenFramebuffers ( 1, &tmpFBID );
	glGenRenderbuffers( 1, &tmpRBID );

	// フレームバッファオブジェクトにテクスチャとZバッファ用の
	// レンダーバッファを結合させる
	glBindFramebuffer(			GL_FRAMEBUFFER_EXT,	 tmpFBID );
	glBindRenderbuffer(			GL_RENDERBUFFER_EXT, tmpRBID );
	glFramebufferTexture2D(		GL_FRAMEBUFFER_EXT,  GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, TexID, 0 );
	glRenderbufferStorage(		GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height );
	glFramebufferRenderbuffer(	GL_FRAMEBUFFER_EXT,  GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, tmpRBID );

	// テクスチャのバインド解除
	glBindFramebuffer ( GL_FRAMEBUFFER_EXT , 0);
	glBindRenderbuffer( GL_RENDERBUFFER_EXT, 0);
	glBindTexture     ( GL_TEXTURE_2D, 0 );
	
	// ステータスチェック
	if( !_CheckStatus() ) {
		return false;
	}


	// テクスチャ情報を記録
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
//	内　容：レンダリング情報のGLテクスチャIDを取得
//	引　数：レンダリングID
//	戻り値：GLテクスチャID
//	 memo ：
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
//	内　容：描画ターゲットを設定
//	引　数：レンダリングID
//	戻り値：なし
//	 memo ：
//========================================================================
void RenderableTexture::SetRenderTarget(RenderTexId RTexId)
{
	if( !m_ready ) {
		return;
	}
	ASSERT( 0 <= RTexId &&  RTexId < Info.size(), "RenderTexId : %d", RTexId );

	// テクスチャへのレンダリング
	glEnable( GL_TEXTURE_2D );
	glBindFramebuffer( GL_FRAMEBUFFER_EXT, Info[RTexId].FrameBufferID );
	glFramebufferTexture2D( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, Info[RTexId].glTexID, 0 );
	
	// 描画処理
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(50.0f, (f64)Info[RTexId].width / (f64)Info[RTexId].height, 0.1, 10000.0);
	//glViewport(0, 0, Info[RTexId].width, Info[RTexId].height);

	//glMatrixMode(GL_MODELVIEW);
}


//========================================================================
//	内　容：描画対象をGLに戻す
//	引　数：なし
//	戻り値：なし
//	 memo ：
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
/*!	@brief	テクスチャの内容をクリア
	@param	RTexId		: レンダリングID
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
//	内　容：全内容を破棄
//	引　数：なし
//	戻り値：なし
//	 memo ：プログラム終了時に使用する
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
//	内　容：2Dテクスチャに描画（シェーダーと併せて使う)
//	引　数：レンダリングID
//	戻り値：なし
//	 memo ：
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
//	内　容：GLtex番のテクスチャ内容をdestFBOTex番にコピー
//	引　数：
//	戻り値：
//	 memo ：
//========================================================================
void RenderableTexture::CopyGL2FBOTexture( RenderTexId destFBOTex, GLuint GLtex )
{
	if( !m_ready ) {
		return;
	}
	
	GetInstance()->SetRenderTarget( destFBOTex );
	// z比較切る
	glDisable( GL_DEPTH_TEST );

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, GLtex );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// レンダーターゲットdestFBOTexにGLtexテクスチャをコピー
	// テクスチャ描画なのでUVのV値を反転させていることに注意。

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
	// z比較切る
	glDisable( GL_DEPTH_TEST );

	// スクリーンへ直接描画
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, srctex );
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ描画なのでUVのV値を反転させていることに注意。
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
//	内　容：現在の状態を取得
//	引　数：なし
//	戻り値：true	: 正常
//			false	: エラー
//	 memo ：
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


