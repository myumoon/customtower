//=============================================================================
/*!	@file	texture.h

	@brief	�e�N�X�`���N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
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
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
Texture::Texture()
{
	//m_surface	= NULL;
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
	\note	�e�N�X�`�����������
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
/*!	@brief	�T�[�t�F�C�X�̓o�^
	@param	surface		�o�^���s���T�[�t�F�C�X
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
/*!	@brief	�e�N�X�`�������Z�b�g
	@param	name	: �e�N�X�`����
	@return	�Ȃ�
*/
//===========================================================================
void Texture::SetTexName( const char* name )
{
	m_texName.assign( name );
	
}


	
//===========================================================================
/*!	@brief	�e�N�X�`�������Z�b�g
	@param	name	: �e�N�X�`����
	@return	�Ȃ�
*/
//===========================================================================
void Texture::SetTexName( std::string name )
{
	m_texName = name;
}


//===========================================================================
/*!	@brief	�e�N�X�`�������擾
	@param	�Ȃ�
	@return	�e�N�X�`����
*/
//===========================================================================
std::string Texture::GetTexName() const
{
	return m_texName;
}


//===========================================================================
/*!	@brief	�e�N�X�`��ID���Z�b�g
	@param	id	: �e�N�X�`��ID
	@return	�Ȃ�
*/
//===========================================================================
void Texture::SetID( u32 id )
{
	m_id = id;
}


//===========================================================================
/*!	@brief	�e�N�X�`��ID���擾
	@param	�Ȃ�
	@return	�e�N�X�`��ID
*/
//===========================================================================
u32 Texture::GetID() const
{
	return m_id;
}


//===========================================================================
/*!	@brief	�e�N�X�`��ID�̃A�h���X���擾
	@param	�Ȃ�
	@return	�e�N�X�`��ID�̃A�h���X
*/
//===========================================================================
const u32* Texture::GetIDPointer() const
{
	return &m_id;
}


//===========================================================================
/*!	@brief	�T�C�Y���Z�b�g
	@param	w	: ��
	@param	h	: ����
	@return	�Ȃ�
*/
//===========================================================================
void Texture::SetSize( s32 w, s32 h )
{
	m_width		= w;
	m_height	= h;
}


//===========================================================================
/*!	@brief	�����擾
	@param	�Ȃ�
	@return	�e�N�X�`����
*/
//===========================================================================
s32 Texture::GetWidth() const
{
	return m_width;
}


//===========================================================================
/*!	@brief	�������擾
	@param	�Ȃ�
	@return	�e�N�X�`������
*/
//===========================================================================
s32 Texture::GetHeight() const
{
	return m_height;
}



//===========================================================================
/*!	@brief	�e�N�X�`�����쐬
	@param	fileName	: �t�@�C���p�X
	@return	���������e�N�X�`���ւ̃|�C���^		NULL:���s
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
		glGenTextures(1, &texID);	//�e�N�X�`��ID�𓾂�

		glBindTexture( GL_TEXTURE_2D, texID );
		gluBuild2DMipmaps(
			GL_TEXTURE_2D, GL_RGBA,
			src.GetWidth(), src.GetHeight(),
			GL_RGBA, GL_UNSIGNED_BYTE,
			src.image->pixels
		);


		//	�e�N�X�`��ID�����X�g�ɒǉ�
		//---------------------------------------
		texture	= new Texture();
		texture->SetID( texID );
		texture->SetSize( src.image->w, src.image->h );
		texture->Register( src );
	}	
#elif defined(NK_USE_GL)
	{
		//	�e�N�X�`��ID�����X�g�ɒǉ�
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
/*!	@brief	�e�N�X�`�����쐬
	@param	fileName	: �t�@�C���p�X
	@return	���������e�N�X�`���ւ̃|�C���^		NULL:���s
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
/*!	@brief	�e�N�X�`�����쐬
	@param	fileName	: �t�@�C���p�X
	@return	���������e�N�X�`���ւ̃|�C���^		NULL:���s
*/
//===========================================================================
Texture* CreateTexture( std::string fileName )
{
#if defined(NK_USE_SDLGL)
	SDL_Surface *image;
	SDL_Surface *temp_image;

	PRINTF("IMG_Load %s\n", fileName.c_str());

	//	�摜�̓ǂݍ���
	//---------------------------------------
	image = IMG_Load(fileName.c_str());

	if( !image ) {
		PRINTF("�e�N�X�`���摜�Ǎ��ݎ��s : %s\n", fileName.c_str());
		return NULL;
	}



	// �t�H�[�}�b�g�ϊ��p�ɋ��SDL�C���[�W���
	temp_image= SDL_CreateRGBSurface(
		SDL_SWSURFACE, 0, 0, 32,
		0x000000ff,
		0x0000ff00,
		0x00ff0000,
		0xff000000 );


	// Image��tempImage�̃t�H�[�}�b�g�ɕϊ�����
	image = SDL_ConvertSurface(image, temp_image->format, SDL_SWSURFACE);
	SDL_FreeSurface(temp_image);


	Uint32 alpFlg;
	Uint8  alpGet;

	//�A���t�@�擾
	alpFlg = image->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
	alpGet = image->format->alpha;

	if( (alpFlg & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(image, 0, 0);
	}

	// ����������textureRegistant�ɔC����
#if 1
	// OpenGL�Ƀe�N�X�`������邱�Ƃ�\������
	GLuint texID;
	glGenTextures(1, &texID);//�e�N�X�`��ID�𓾂�

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
	

	// texID�Ԃ̃e�N�X�`���Ƀo�C���h����
	// �����̊֐��ȍ~��texID�Ԃ̃e�N�X�`��ID�Ɋւ��鑀��ɂȂ�
	glBindTexture( GL_TEXTURE_2D, texID );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 
	gluBuild2DMipmaps(
		GL_TEXTURE_2D, GL_RGBA,
		image->w, image->h,
		GL_RGBA, GL_UNSIGNED_BYTE,
		image->pixels);
	

	ImageSurface	surface;
	surface.Register( image );

	//	�e�N�X�`��ID�����X�g�ɒǉ�
	//---------------------------------------
	Texture* texture = new Texture();
	texture->SetID(texID);
	texture->SetSize(image->w, image->h);
	texture->SetTexName(fileName);
	texture->Register( surface );
#endif

	return texture;

#elif defined(NK_USE_GL)
	// png�ȊO�̓G���[�ɂ��Ă���
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

	//	�e�N�X�`��ID�����X�g�ɒǉ�
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
/*!	@brief	�e�N�X�`�����g�p����
	@param	texID	: �o�C���h����e�N�X�`��ID
	@return	�Ȃ�
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
/*!	@brief	��̃e�N�X�`���𐶐�
	@param	xsize, ysize	: �e�N�X�`���̃T�C�Y
	@return	�e�N�X�`��ID
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













