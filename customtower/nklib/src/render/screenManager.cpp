//=============================================================================
/*!	@file	screen.cpp

	@brief	�X�N���[��

	@author	ryunosuke ide
	@date	2012.06.23
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/render/screenManager.h"
#include "../../include/graphics/attitude.h"
#include "../../include/math/math.h"
#include "../../include/general.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed



namespace nk {

//---------------------------------�֐���`---------------------------------

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
ScreenManager::ScreenManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
ScreenManager::~ScreenManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void ScreenManager::_Init()
{

}


//===========================================================================
/*!	@brief	�I������
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
/*!	@brief	�X�N���[���𐶐�
	@param	width		�X�N���[����
	@param	height		�X�N���[����
	@param	screenId	��������X�N���[��ID
	@return	�Ȃ�
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
/*!	@brief	�X�N���[��ID����e�N�X�`��ID���擾
	@param	screenId	: �X�N���[��ID
	@return	�e�N�X�`��ID
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
/*!	@brief	�X�N���[��ID����e�N�X�`�����擾
	@param	screenId	: �X�N���[��ID
	@return	�e�N�X�`��
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
/*!	@brief	�X�N���[���̓��e���N���A
	@param	screenId	�N���A���s���X�N���[��ID
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
/*!	@brief	�w�肵���X�N���[�����E�C���h�E�ɓ\��t����
	@param	screenId	�\��t����X�N���[��ID
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
/*!	@brief	�`��
	@param	screenId	�`����s���X�N���[��
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


	// z��r�؂�
	glDisable( GL_DEPTH_TEST );

	RENDERABLE_TEXTURE->RestoreRenderTarget();

	// �s���ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// �X�N���[���֒��ڕ`��
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texId );


	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	const f32 screenW	= static_cast<f32>(screenWidth);
	const f32 screenH	= static_cast<f32>(screenHeight);
	const f32 screenD	= 0;//static_cast<f32>(screenId);

	// �e�N�X�`���`��Ȃ̂�UV��V�l�𔽓]
	//glBegin( GL_QUADS );
	glBegin( GL_TRIANGLES );

		// ����O�p
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 0.0f, 0.0f, screenD );

		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 0.0f, screenH, screenD );

		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( screenW, 0.0f, screenD );
		
		// �E���O�p
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