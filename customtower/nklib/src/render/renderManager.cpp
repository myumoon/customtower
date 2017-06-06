//=============================================================================
/*!	@file	rendermanager.cpp

	@brief	�`��Ǘ��N���X

	@author	��� ���V��
	@date	2011/11/17
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "project.h"
#include "../../include/render/renderManager.h"
#include "../../include/system.h"

#if		defined(NK_USE_DIRECTX)

#elif	defined(NK_USE_GL)
#include <gl/gl.h>

#elif	defined(NK_USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#elif	defined(NK_USE_SDL) && defined(NK_USE_GL)
#include <SDL/SDL_opengl.h>
#include <gl/glut.h>

#endif




namespace nk {
namespace graphics {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
RenderManager::RenderManager() : m_shaderMng(NULL)
{
	m_prevUseTexture			= NULL;
	DrawPacket::m_drawManager	= this;
	m_shaderMng					= new ShaderManager();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
RenderManager::~RenderManager()
{
	RenderableTexture::GetInstance()->Destroy();

	SafeDelete(m_shaderMng);
}



//===========================================================================
/*!	@brief	������
	@param	�Ȃ�
*/
//===========================================================================
bool RenderManager::Initialize( void )
{
	NULL_ASSERT( m_shaderMng );

	bool	result	= true;

	m_prevUseTexture	= NULL;
	result	&= m_shaderMng->Initialize();

	return result;
}


//===========================================================================
/*!	@brief	�`��I�u�W�F�N�g��ǉ�
	@param	packet	: �ǉ�����I�u�W�F�N�g
	@return	�Ȃ�
*/
//===========================================================================
void RenderManager::Add(const nk::graphics::DrawPacket* packet)
{
	// �\�[�g�͕`�掞�Ɉړ�
// 	std::list<const DrawPacket*>::iterator itr = m_drawPacketList.begin();
// 	std::list<const DrawPacket*>::iterator end = m_drawPacketList.end();
// 
// 	for( ; itr != end; ++itr) {
// 		if( packet->GetPriority() < (*itr)->GetPriority() ) {
// 			break;
// 		}
// 	}
// 
// 	m_drawPacketList.insert(itr, packet);

	m_drawPacketList.push_back( packet );
}



//===========================================================================
/*!	@brief	�V�F�[�_�[�Ǎ���
	@param	shader	: �V�F�[�_�[�C���X�^���X�ւ̃|�C���^
	@param	path	: cg�ւ̃p�X
	@param	name	: ������
	@return	�Ȃ�
*/
//===========================================================================
void RenderManager::LoadShader(nk::graphics::Shader *shader, std::string file, std::string name)
{
	m_shaderMng->LoadShader(shader, file, name);
}


//===========================================================================
/*!	@brief	�`��
	@param	mainclass	: ���C���N���X�ւ̃|�C���^
	@return	�Ȃ�
*/
//===========================================================================
void RenderManager::Draw(Main* mainclass)
{

	class DrawPacketSort {
	public:
		bool operator ()( const DrawPacket* lhs, const DrawPacket* rhs ) const
		{
			return lhs->GetPriority() < rhs->GetPriority();
		}
	};

	m_drawPacketList.sort( DrawPacketSort() );

	m_prevUseTexture	= NULL;

	std::list<const DrawPacket*>::iterator itr = m_drawPacketList.begin();
	s32 _cnt = 0;
	for( ; itr != m_drawPacketList.end(); ++itr) {
// 		if( (*itr)->IsBufferClear() ) {
// 			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
// 		} else {
		Draw( mainclass, *itr );
// 		}
	}

	m_drawPacketList.clear();
	

}



//===========================================================================
/*!	@brief	�I�u�W�F�N�g�ʂ̕`��
	@param	mainclass	: ���C���N���X�ւ̃|�C���^
	@param	packet		: �`�悷��I�u�W�F�N�g
	@return	�Ȃ�
*/
//===========================================================================
void RenderManager::Draw(Main* mainclass, const nk::graphics::DrawPacket* packet)
{
#if defined(NK_USE_GL)

	// �g�p�z���錾
	glEnableClientState( GL_VERTEX_ARRAY | GL_INDEX_ARRAY | GL_TEXTURE_COORD_ARRAY );

	// ���[���h�r���[�s���ݒ�
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glLoadMatrixf( packet->GetWorldViewTransform().GetMatrix().ary16 );

#endif	// #if defined(NK_USE_GL)

	// ��(3D)
	if( packet->m_type & DrawPacket::LINE3D ) {
		mainclass->ChangeMode3D();
		glDisable(GL_LINE_SMOOTH);
	}
	// ��(2D)
	if( packet->m_type & DrawPacket::LINE2D ) {
		mainclass->ChangeMode2D();
		//glDisable(GL_LINE_SMOOTH);
		//mainclass->ChangeMode3D();
		glEnable(GL_LINE_SMOOTH);
	}

	// ��ʂɒ���t����^�C�v
	else if( packet->m_type & DrawPacket::SPRITE ) {
		mainclass->ChangeMode2D();

		// BindTexture�͏d���̂őO��̕`��e�N�X�`���Ɠ����e�N�X�`����`�悷��ꍇ�̓o�C���h���Ȃ�
		if( m_prevUseTexture != packet->m_material.GetTexture() ) {
			resource::BindTexture( packet->m_material.GetTexture() );
			m_prevUseTexture	= packet->m_material.GetTexture();
		}
		else {
			glEnable( GL_TEXTURE_2D );
		}
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	}
	// ����ȊO
	else {
		mainclass->ChangeMode3D();

	#if 0
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		if( 0 )
		{
 			mainclass->ChangeMode3D();
		}

		if( 0 )
		{
 			mainclass->ChangeMode2D();
		}	

		if( 0 )
		{
			const f32	screenWidth		= mainclass->GetWindow()->GetScreenParam().x;
			const f32	screenHeight	= mainclass->GetWindow()->GetScreenParam().y;
			const f32	screenDeapth	= mainclass->GetWindow()->GetScreenParam().z;

			// ���ˉe�ݒ�i��ʂ̌������j�E�㌴�_
			glOrtho(0, screenWidth, screenHeight, 0, screenDeapth, -screenDeapth);
			glViewport(0, 0, static_cast<s32>(screenWidth), static_cast<s32>(screenHeight));
		}

		if( 0 )
		{
			const f32	fieldOfVision	= mainclass->GetCameraManager()->GetCurrentFieldOfVision();
			const f32	nearDistance	= mainclass->GetCameraManager()->GetCurrentNearDistance();
			const f32	farDistance		= mainclass->GetCameraManager()->GetCurrentFarDistance();
			const f32	screenWidth		= mainclass->GetWindow()->GetScreenParam().x;
			const f32	screenHeight	= mainclass->GetWindow()->GetScreenParam().y;

			/* �����@�ˉe�i�E����W�n�j */
			gluPerspective( fieldOfVision, screenWidth / screenHeight, nearDistance, farDistance );
			glViewport(0, 0, static_cast<s32>(screenWidth), static_cast<s32>(screenHeight));
		}

		if( 1 )
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			math::Matrix44	matPFOV		= mainclass->GetPerspectiveFieldOfView();
			math::Matrix44	matViewPort	= mainclass->GetWindow()->GetViewPortMatrix();
			math::Matrix44	matScreen	= matPFOV/* * matViewPort*/;
			glLoadMatrixf( matScreen.GetMatrix().ary16 );
		}
				
	#endif
		
		if( packet->m_material.GetTexture() ) {

			// BindTexture�͏d���̂őO��̕`��e�N�X�`���Ɠ����e�N�X�`����`�悷��ꍇ�̓o�C���h���Ȃ�
// 			if( m_prevUseTexture != packet->m_material.GetTexture() )
			{
				resource::BindTexture( packet->m_material.GetTexture() );
				m_prevUseTexture	= packet->m_material.GetTexture();
			}
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		}
	}

	glMatrixMode( GL_MODELVIEW );

	// �F�̐ݒ�
	{
		const Color& color = packet->m_material.GetColor();
		glColor4ub( color.r, color.g, color.b, color.a );
	}

	// �V�F�[�_�[��K�p������
	resource::Material&			material	= packet->GetMaterial();
	graphics::ShaderData		shaderData	= material.GetShaderData();
	Shader*					shader		= m_shaderMng->GetShader(shaderData.shaderName);
	if( m_shaderMng->Ready() && shader ) {
		shaderData.screenSize	= math::Vector(mainclass->GetScreenWidth(), mainclass->GetScreenHeight(), 0.0f);
		shaderData.worldMat		= packet->GetWorldMatrix();	
		material.SetShaderData( shaderData );
		shader->Begin(&material, shaderData.useTechnique, mainclass->GetCameraManager()->GetUseCamera());
	}



#if !__SHADOWMAP_TEST
	// �`�悷��e�N�X�`����ݒ�
	//if( packet->IsDrawRenderTexture() ) {
	{
		mainclass->GetScreen()->BindWindow( packet->GetScreenId() );
	}
#endif

	//if(0) {
	if( packet->m_type & (DrawPacket::MODEL | DrawPacket::MODEL_ANIMATION) ) {
		// ���_�̕`��
		glBegin(GL_TRIANGLES);
		const u32 idxSize =  packet->m_face.GetSize();
		for(u32 i = 0; i < idxSize; ++i) {
			const u32&			FACE_NUM	= packet->m_face.GetFace(i);
			const math::Vector&	VERTEX		= packet->m_vertex.GetVertex(FACE_NUM);
			const math::Vector& NORMAL		= packet->m_normal.GetVertex(FACE_NUM);
			const math::Vector& UV			= packet->m_face.GetUV(i);

			glNormal3f( NORMAL.x, NORMAL.y, NORMAL.z );

			glTexCoord2f( UV.x, UV.y );

			glVertex3f( VERTEX.x, VERTEX.y, VERTEX.z );
		}
		glEnd();
	}
	else if( packet->m_type & (DrawPacket::LINE2D | DrawPacket::LINE3D) ) {
		glBegin( GL_LINE_STRIP );
		for( u32 i = 0; i < packet->m_vertex.GetSize(); ++i ) {
			const math::Vector&	pos	= packet->m_vertex.GetVertex( i );
			
			glVertex3f( pos.x, pos.y, pos.z );
		}
		glEnd();
	}
	else {
		// ���_�̕`��
		glBegin(GL_TRIANGLES);
		const u32 idxSize =  packet->m_face.GetSize();
		for(u32 i = 0; i < idxSize; ++i) {
			const u32&			FACE_NUM	= packet->m_face.GetFace(i);
			const math::Vector&	VERTEX		= packet->GetVertex().GetVertex(FACE_NUM);
			const math::Vector& UV			= packet->m_face.GetUV(i);

			glTexCoord2f( UV.x, UV.y );

			glVertex3f(VERTEX.x, VERTEX.y, VERTEX.z);
		}
		glEnd();
	}

	if( m_shaderMng->Ready() && shader ) {
		shader->End();
	}
		
#if !__SHADOWMAP_TEST
	// �����_�^�[�Q�b�g���E�C���h�E�ɖ߂�
	//if( packet->IsDrawRenderTexture() ) {
	{
		RenderableTexture::GetInstance()->RestoreRenderTarget();
	}
#endif

#if defined(NK_USE_GL)
	glDisable( GL_TEXTURE_2D );
	glDisableClientState( GL_VERTEX_ARRAY | GL_INDEX_ARRAY | GL_TEXTURE_COORD_ARRAY );

#endif	// #if defined(NK_USE_GL)
}


//===========================================================================
/*!	@brief	�V�F�[�_�[���폜
	@param	�Ȃ�
	@return	�Ȃ�
*/
//===========================================================================
void RenderManager::DeleteShader()
{
	m_shaderMng->DeleteAll();
}







}	// namespace graphics
}	// namespace nk