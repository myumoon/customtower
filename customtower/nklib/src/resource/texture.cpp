//=============================================================================
/*!	@file	texture.h

	@brief	テクスチャクラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/resource/texture.h"
//#include "project.h"

#if defined(_WINDOWS)
#include <winsock2.h>
#include <windows.h>
#endif

#if defined(NK_USE_DIRECTX)
#elif	defined(NK_USE_SDLGL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#elif		defined(NK_USE_GL)
#include <gl/gl.h>
#include <gl/glpng.h>
#elif	defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

#include "../../include/general.h"
#include "../../include/file/file.h"
#include "../../include/utility/stringfunction.h"

namespace nk {
namespace resource {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Texture::Texture()
{
	//m_surface	= NULL;
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
	\note	テクスチャを解放する
*/
//===========================================================================
Texture::~Texture()
{
#if defined(NK_USE_SDL)
	ReleaseImageSurface( &m_surface );
#endif
	
#if	defined(NK_USE_GL)
	glDeleteTextures( 1, &m_id );
		
#endif
	
}


//===========================================================================
/*!	@brief	サーフェイスの登録
	@param	surface		登録を行うサーフェイス
	@return	----
*/
//===========================================================================
void Texture::Register( ImageSurface surface )
{
	ASSERT( m_surface.created == false, "registered surface." );
	if( m_surface.created != false ) {
		m_surface	= surface;
	#if defined(NK_USE_SDL)
		m_width		= surface.image->w;
		m_width		= surface.image->h;
	#endif
	}
}


//===========================================================================
/*!	@brief	テクスチャ名をセット
	@param	name	: テクスチャ名
	@return	なし
*/
//===========================================================================
void Texture::SetTexName( const char* name )
{
	m_texName.assign( name );
	
}


	
//===========================================================================
/*!	@brief	テクスチャ名をセット
	@param	name	: テクスチャ名
	@return	なし
*/
//===========================================================================
void Texture::SetTexName( std::string name )
{
	m_texName = name;
}


//===========================================================================
/*!	@brief	テクスチャ名を取得
	@param	なし
	@return	テクスチャ名
*/
//===========================================================================
std::string Texture::GetTexName() const
{
	return m_texName;
}


//===========================================================================
/*!	@brief	テクスチャIDをセット
	@param	id	: テクスチャID
	@return	なし
*/
//===========================================================================
void Texture::SetID( u32 id )
{
	m_id = id;
}


//===========================================================================
/*!	@brief	テクスチャIDを取得
	@param	なし
	@return	テクスチャID
*/
//===========================================================================
u32 Texture::GetID() const
{
	return m_id;
}


//===========================================================================
/*!	@brief	テクスチャIDのアドレスを取得
	@param	なし
	@return	テクスチャIDのアドレス
*/
//===========================================================================
const u32* Texture::GetIDPointer() const
{
	return &m_id;
}


//===========================================================================
/*!	@brief	サイズをセット
	@param	w	: 幅
	@param	h	: 高さ
	@return	なし
*/
//===========================================================================
void Texture::SetSize( s32 w, s32 h )
{
	m_width		= w;
	m_height	= h;
}


//===========================================================================
/*!	@brief	幅を取得
	@param	なし
	@return	テクスチャ幅
*/
//===========================================================================
s32 Texture::GetWidth() const
{
	return m_width;
}


//===========================================================================
/*!	@brief	高さを取得
	@param	なし
	@return	テクスチャ高さ
*/
//===========================================================================
s32 Texture::GetHeight() const
{
	return m_height;
}



//===========================================================================
/*!	@brief	テクスチャを作成
	@param	fileName	: ファイルパス
	@return	生成したテクスチャへのポインタ		NULL:失敗
*/
//===========================================================================
Texture* CreateTexture( ImageSurface src )
{
	Texture* texture = NULL;

	if( src.created == false ) {
		return NULL;
	}
	
#if defined(NK_USE_SDLGL)
	{
		GLuint texID;
		glGenTextures(1, &texID);	//テクスチャIDを得る

		glBindTexture( GL_TEXTURE_2D, texID );
		gluBuild2DMipmaps(
			GL_TEXTURE_2D, GL_RGBA,
			src.GetWidth(), src.GetHeight(),
			GL_RGBA, GL_UNSIGNED_BYTE,
			src.image->pixels
		);


		//	テクスチャIDをリストに追加
		//---------------------------------------
		texture	= new Texture();
		texture->SetID( texID );
		texture->SetSize( src.image->w, src.image->h );
		texture->Register( src );
	}	
#elif defined(NK_USE_GL)
	{
		//	テクスチャIDをリストに追加
		//---------------------------------------
		texture = new Texture();
		texture->SetID( src.image->texId );
		texture->SetSize( src.GetWidth(), src.GetHeight() );
		texture->Register( src );
	}
#endif

	return texture;
}


//===========================================================================
/*!	@brief	テクスチャを作成
	@param	fileName	: ファイルパス
	@return	生成したテクスチャへのポインタ		NULL:失敗
*/
//===========================================================================
Texture* CreateTexture( const char* filename )
{
	ImageSurface	createSurface;
	LoadImageSurface( &createSurface, filename );

	Texture*	createTex	= CreateTexture( createSurface );
	createTex->SetTexName( filename );
	
	return createTex;
}

	
#if 0
//===========================================================================
/*!	@brief	テクスチャを作成
	@param	fileName	: ファイルパス
	@return	生成したテクスチャへのポインタ		NULL:失敗
*/
//===========================================================================
Texture* CreateTexture( std::string fileName )
{
#if defined(NK_USE_SDLGL)
	SDL_Surface *image;
	SDL_Surface *temp_image;

	PRINTF("IMG_Load %s\n", fileName.c_str());

	//	画像の読み込み
	//---------------------------------------
	image = IMG_Load(fileName.c_str());

	if( !image ) {
		PRINTF("テクスチャ画像読込み失敗 : %s\n", fileName.c_str());
		return NULL;
	}



	// フォーマット変換用に空のSDLイメージ作る
	temp_image= SDL_CreateRGBSurface(
		SDL_SWSURFACE, 0, 0, 32,
		0x000000ff,
		0x0000ff00,
		0x00ff0000,
		0xff000000 );


	// ImageをtempImageのフォーマットに変換する
	image = SDL_ConvertSurface(image, temp_image->format, SDL_SWSURFACE);
	SDL_FreeSurface(temp_image);


	Uint32 alpFlg;
	Uint8  alpGet;

	//アルファ取得
	alpFlg = image->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
	alpGet = image->format->alpha;

	if( (alpFlg & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(image, 0, 0);
	}

	// ここから先はtextureRegistantに任せる
#if 1
	// OpenGLにテクスチャを作ることを申請する
	GLuint texID;
	glGenTextures(1, &texID);//テクスチャIDを得る

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
	

	// texID番のテクスチャにバインドする
	// ↓この関数以降はtexID番のテクスチャIDに関する操作になる
	glBindTexture( GL_TEXTURE_2D, texID );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 
	gluBuild2DMipmaps(
		GL_TEXTURE_2D, GL_RGBA,
		image->w, image->h,
		GL_RGBA, GL_UNSIGNED_BYTE,
		image->pixels);
	

	ImageSurface	surface;
	surface.Register( image );

	//	テクスチャIDをリストに追加
	//---------------------------------------
	Texture* texture = new Texture();
	texture->SetID(texID);
	texture->SetSize(image->w, image->h);
	texture->SetTexName(fileName);
	texture->Register( surface );
#endif

	return texture;

#elif defined(NK_USE_GL)
	// png以外はエラーにしておく
	{
		const char*	ext	= GetExtension( fileName.c_str() );
		ASSERT( Compare( ext, "png" ), "png only. %s", fileName.c_str() );
		if( Compare( ext, "png" ) == false ) {
			return NULL;
		}
	}
	
	pngInfo info;
	GLuint	texId	= pngBind( fileName.c_str(), PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST );
	ASSERT( texId != 0, "fileName : %s\n", fileName.c_str() );
	if( texId == 0 ) {
		PRINTF( "texture load error : %s\n", fileName.c_str() );

		return NULL;
	}

	//	テクスチャIDをリストに追加
	//---------------------------------------
	Texture* texture = new Texture();
	texture->SetID( texId );
	texture->SetSize( info.Width, info.Height );
	texture->SetTexName( fileName );

	return texture;
	
#else
	
#endif
	return NULL;
}
#endif

	

//===========================================================================
/*!	@brief	テクスチャを使用する
	@param	texID	: バインドするテクスチャID
	@return	なし
*/
//===========================================================================
void BindTexture( const Texture* tex )
{
#if defined(NK_USE_GL)
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, tex->GetID() );
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
#endif
}


	
//===========================================================================
/*!	@brief	空のテクスチャを生成
	@param	xsize, ysize	: テクスチャのサイズ
	@return	テクスチャID
*/
//===========================================================================
Texture* CreateEmptyTexture( s32 width, s32 height )
{
	resource::Texture*	tex = NULL;
	
#if defined(NK_USE_GL)
	
	tex		= new Texture();
	GLuint	id;

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);
	glDisable(GL_TEXTURE_2D);

	tex->SetID(id);
	tex->SetSize(width, height);
	tex->SetTexName("");
#endif
	
	return tex;
}


	
}	// namespace resource
}	// namespace nk













