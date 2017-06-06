//=============================================================================
/*!	@file	rendermanager.cpp

	@brief	描画管理クラス

	@author	井手 竜之介
	@date	2011/11/17
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
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
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
RenderManager::RenderManager() : m_shaderMng(NULL)
{
	m_prevUseTexture			= NULL;
	DrawPacket::m_drawManager	= this;
	m_shaderMng					= new ShaderManager();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
RenderManager::~RenderManager()
{
	RenderableTexture::GetInstance()->Destroy();

	SafeDelete(m_shaderMng);
}



//===========================================================================
/*!	@brief	初期化
	@param	なし
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
/*!	@brief	描画オブジェクトを追加
	@param	packet	: 追加するオブジェクト
	@return	なし
*/
//===========================================================================
void RenderManager::Add(const nk::graphics::DrawPacket* packet)
{
	// ソートは描画時に移動
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
/*!	@brief	シェーダー読込み
	@param	shader	: シェーダーインスタンスへのポインタ
	@param	path	: cgへのパス
	@param	name	: 検索名
	@return	なし
*/
//===========================================================================
void RenderManager::LoadShader(nk::graphics::Shader *shader, std::string file, std::string name)
{
	m_shaderMng->LoadShader(shader, file, name);
}


//===========================================================================
/*!	@brief	描画
	@param	mainclass	: メインクラスへのポインタ
	@return	なし
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
/*!	@brief	オブジェクト別の描画
	@param	mainclass	: メインクラスへのポインタ
	@param	packet		: 描画するオブジェクト
	@return	なし
*/
//===========================================================================
void RenderManager::Draw(Main* mainclass, const nk::graphics::DrawPacket* packet)
{
#if defined(NK_USE_GL)

	// 使用配列を宣言
	glEnableClientState( GL_VERTEX_ARRAY | GL_INDEX_ARRAY | GL_TEXTURE_COORD_ARRAY );

	// ワールドビュー行列を設定
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glLoadMatrixf( packet->GetWorldViewTransform().GetMatrix().ary16 );

#endif	// #if defined(NK_USE_GL)

	// 線(3D)
	if( packet->m_type & DrawPacket::LINE3D ) {
		mainclass->ChangeMode3D();
		glDisable(GL_LINE_SMOOTH);
	}
	// 線(2D)
	if( packet->m_type & DrawPacket::LINE2D ) {
		mainclass->ChangeMode2D();
		//glDisable(GL_LINE_SMOOTH);
		//mainclass->ChangeMode3D();
		glEnable(GL_LINE_SMOOTH);
	}

	// 画面に張り付けるタイプ
	else if( packet->m_type & DrawPacket::SPRITE ) {
		mainclass->ChangeMode2D();

		// BindTextureは重いので前回の描画テクスチャと同じテクスチャを描画する場合はバインドしない
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
	// それ以外
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

			// 正射影設定（画面の見え方）右上原点
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

			/* 透視法射影（右手座標系） */
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

			// BindTextureは重いので前回の描画テクスチャと同じテクスチャを描画する場合はバインドしない
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

	// 色の設定
	{
		const Color& color = packet->m_material.GetColor();
		glColor4ub( color.r, color.g, color.b, color.a );
	}

	// シェーダーを適用させる
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
	// 描画するテクスチャを設定
	//if( packet->IsDrawRenderTexture() ) {
	{
		mainclass->GetScreen()->BindWindow( packet->GetScreenId() );
	}
#endif

	//if(0) {
	if( packet->m_type & (DrawPacket::MODEL | DrawPacket::MODEL_ANIMATION) ) {
		// 頂点の描画
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
		// 頂点の描画
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
	// レンダターゲットをウインドウに戻す
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
/*!	@brief	シェーダーを削除
	@param	なし
	@return	なし
*/
//===========================================================================
void RenderManager::DeleteShader()
{
	m_shaderMng->DeleteAll();
}







}	// namespace graphics
}	// namespace nk