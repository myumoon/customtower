//=============================================================================
/*!	@file	screen.cpp

	@brief	スクリーン

	@author	ryunosuke ide
	@date	2012.06.23
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/render/screenManager.h"
#include "../../include/graphics/attitude.h"
#include "../../include/math/math.h"
#include "../../include/general.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed



namespace nk {

//---------------------------------関数定義---------------------------------

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
ScreenManager::ScreenManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
ScreenManager::~ScreenManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void ScreenManager::_Init()
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void ScreenManager::_Term()
{

	for( u32 i = 0; i < m_vecScreenId.size(); ++i ) {
		SafeDelete( m_vecScreenId[i].texture );
	}

}



//===========================================================================
/*!	@brief	スクリーンを生成
	@param	width		スクリーン幅
	@param	height		スクリーン高
	@param	screenId	生成するスクリーンID
	@return	なし
*/
//===========================================================================
void ScreenManager::CreateScreen( u32 width, u32 height, s32 screenId )
{
	RenderTexId	id;
	RENDERABLE_TEXTURE->CreateRenderableTexture( &id, width, height );
	//RENDERABLE_TEXTURE->CreateRenderableHalfFloatTexture( &id, width, height );

	ScreenTexId screenTex;
	screenTex.screenId	= screenId;
	screenTex.texId		= id;
	screenTex.width		= width;
	screenTex.height	= height;
	
	screenTex.texture	= new resource::Texture();
	screenTex.texture->SetSize( width, height );
	screenTex.texture->SetID( RENDERABLE_TEXTURE->GetTextureID(id) );

	m_vecScreenId.push_back( screenTex );
}


//===========================================================================
/*!	@brief	スクリーンIDからテクスチャIDを取得
	@param	screenId	: スクリーンID
	@return	テクスチャID
*/
//===========================================================================
RenderTexId ScreenManager::GetTextureId( s32 screenId ) const
{
	RenderTexId	retId = 0;

	for( u32 i = 0; i < m_vecScreenId.size(); ++i ) {
		if( m_vecScreenId[i].screenId == screenId ) {
			retId = m_vecScreenId[i].texId;
			break;
		}
	}

	return retId;
}



//===========================================================================
/*!	@brief	スクリーンIDからテクスチャを取得
	@param	screenId	: スクリーンID
	@return	テクスチャ
*/
//===========================================================================
resource::Texture* ScreenManager::GetTexture( s32 screenId ) const
{
	resource::Texture*	retTex = NULL;

	for( u32 i = 0; i < m_vecScreenId.size(); ++i ) {
		if( m_vecScreenId[i].screenId == screenId ) {
			retTex = m_vecScreenId[i].texture;
			break;
		}
	}

	return retTex;
}



//===========================================================================
/*!	@brief	スクリーンの内容をクリア
	@param	screenId	クリアを行うスクリーンID
	@return	----
*/
//===========================================================================
void ScreenManager::ClearScreen( s32 screenId )
{
	for( u32 i = 0; i < m_vecScreenId.size(); ++i ) {
		if( screenId == m_vecScreenId[i].screenId ) {
			RENDERABLE_TEXTURE->ClearTexBuffer( m_vecScreenId[i].texId );
			break;
		}
	}

}


//===========================================================================
/*!	@brief	指定したスクリーンをウインドウに貼り付ける
	@param	screenId	貼り付けるスクリーンID
	@return	----
*/
//===========================================================================
void ScreenManager::BindWindow( s32 screenId )
{
	for( u32 i = 0; i < m_vecScreenId.size(); ++i ) {
		if( screenId == m_vecScreenId[i].screenId ) {
			RENDERABLE_TEXTURE->SetRenderTarget( m_vecScreenId[i].texId );
			break;
		}
	}

}


//===========================================================================
/*!	@brief	描画
	@param	screenId	描画を行うスクリーン
	@return	----
*/
//===========================================================================
void ScreenManager::Draw( s32 screenId )
{
	GLuint	texId			= 0;
	u32		screenWidth		= 0;
	u32		screenHeight	= 0;

	for( u32 i = 0; i < m_vecScreenId.size(); ++i ) {
		if( screenId == m_vecScreenId[i].screenId ) {
			texId			= RENDERABLE_TEXTURE->GetTextureID( m_vecScreenId[i].texId );
			screenWidth		= m_vecScreenId[i].width;
			screenHeight	= m_vecScreenId[i].height;
			break;
		}
	}


	// z比較切る
	glDisable( GL_DEPTH_TEST );

	RENDERABLE_TEXTURE->RestoreRenderTarget();

	// 行列を設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// スクリーンへ直接描画
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texId );


	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	const f32 screenW	= static_cast<f32>(screenWidth);
	const f32 screenH	= static_cast<f32>(screenHeight);
	const f32 screenD	= 0;//static_cast<f32>(screenId);

	// テクスチャ描画なのでUVのV値を反転
	//glBegin( GL_QUADS );
	glBegin( GL_TRIANGLES );

		// 左上三角
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 0.0f, 0.0f, screenD );

		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 0.0f, screenH, screenD );

		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( screenW, 0.0f, screenD );
		
		// 右下三角
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( screenW,  screenH, screenD );

		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( screenW, 0.0f, screenD );

		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 0.0f, screenH, screenD );

	glEnd();

	glEnable( GL_DEPTH_TEST );


}


}	// namespace nk