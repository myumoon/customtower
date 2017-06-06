//=============================================================================
/*!	@file	modelTestScene.h
	@brief	�^�C�g��

	@author	ryunosuke ide
	@date	2013.05.25
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "system.h"

#include "modelTestScene.h"
#include "game/gameMain.h"



//--------------------------------define��`--------------------------------
using namespace nk;
using namespace math;


//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace game {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
ModelTestScene::ModelTestScene()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
ModelTestScene::~ModelTestScene()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void ModelTestScene::_Init( void )
{


}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void ModelTestScene::_Term( void )
{
	
}



//===========================================================================
/*!	@brief		���\�[�X����
	@param		parent	�e
	@return		----
*/
//===========================================================================
void ModelTestScene::InitializeScene( SceneInterface* parent )
{
	m_hitSphere.Init(math::Vector(), 50.0f);

	// �G
	m_animModel.Init("data/character/enemy/enemy1.toy");


	// �n��
	m_floor.Init("data/stage/floor/floor.mqo");
	//m_floor.Init("data/stage/earth/stage_01.mqo");

	// ����
	m_sphere.Init( "data/stage/earth/stage_01.mqo" );
	//m_sphere.SetScale( 0.3f );

}


//===========================================================================
/*!	@brief		���\�[�X�폜
	@param		parent	�e
	@return		----
*/
//===========================================================================
void ModelTestScene::TerminateScene( SceneInterface* parent )
{
	
}

//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
s32 ModelTestScene::ExecuteLocal( s32 parentMessage )
{
	if( GetGameManager()->GetKeyboard()->IsPressed(input::Keyboard::KEY_ESC) ) {
		GetGameManager()->SetNextScene( SceneManager::SCENE_ID_TITLE );
	}

		if( GetGameManager()->GetMouse()->IsPress(input::Mouse::CLICK_LEFT) ) {
			printf("left");
		}
		if( GetGameManager()->GetMouse()->IsPress(input::Mouse::CLICK_RIGHT) ) {
			printf("right");
		}
		if( GetGameManager()->GetMouse()->IsPress(input::Mouse::CLICK_WHEEL) ) {
			printf("center");
		}

		// �L�[�{�[�h����
		if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_UP) ) {
			if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_LCTRL) ) {
				m_pos += math::Vector(0.0f, 10.0f, 0.0f);
			} else {
				m_pos += math::Vector(0.0f, 0.0f, -10.0f);
			}
		}
		if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_DOWN) ) {
			if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_LCTRL) ) {
				m_pos += math::Vector(0.0f, -10.0f, 0.0f);
			} else {
				m_pos += math::Vector(0.0f, 0.0f, 10.0f);
			}
		}
		if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_RIGHT) ) {
			m_pos += math::Vector(10.0f, 0.0f, 0.0f);
		}
		if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_LEFT) ) {
			m_pos += math::Vector(-10.0f, 0.0f, 0.0f);
		}
		const float ROTATE_VALUE = 3.0f;
		if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_W) ) {
			math::Vector	pos		= GetGameManager()->GetCameraManager()->GetUseCamera()->GetPos();
			math::Vector	top		= GetGameManager()->GetCameraManager()->GetUseCamera()->GetTop();
			pos.Normalize();
			math::Vector	closs	= math::CalcCrossProduct( pos, top );
			//math::Matrix44	rot		= math::RotateAxis( math::Rad(ROTATE_VALUE), closs );
			math::Matrix44	rot		= math::RotateX( math::Rad(ROTATE_VALUE) );
			GetGameManager()->GetCameraManager()->GetUseCamera()->SetPos( rot * pos );
			GetGameManager()->GetCameraManager()->GetUseCamera()->SetTop( rot * top );
		}
		if( GetGameManager()->GetKeyboard()->IsPress(input::Keyboard::KEY_S) ) {
			math::Vector	pos		= GetGameManager()->GetCameraManager()->GetUseCamera()->GetPos();
			math::Vector	top		= GetGameManager()->GetCameraManager()->GetUseCamera()->GetTop();
			pos.Normalize();
			math::Vector	closs	= math::CalcCrossProduct( pos, top );
			//math::Matrix44	rot		= math::RotateAxis( math::Rad(ROTATE_VALUE), closs );
			math::Matrix44	rot		= math::RotateX( -math::Rad(ROTATE_VALUE) );
			GetGameManager()->GetCameraManager()->GetUseCamera()->SetPos( rot * pos );
			GetGameManager()->GetCameraManager()->GetUseCamera()->SetTop( rot * top );
		}

		if( GetGameManager()->GetMouse()->IsPressed(input::Mouse::CLICK_LEFT) ) {
			m_animModel.SetAnimation("walk");
		}
		if( GetGameManager()->GetMouse()->IsPressed(input::Mouse::CLICK_RIGHT) ) {
			m_animModel.SetAnimation("slash");
		}
		
		// 2D��3D���W�ϊ�
		//---------------�v���W�F�N�V�����s����擾---------------
		GLdouble projection[16];
		//math::CopyMatrix44ToArray(projection, m_PFOVmatrix);
		nk::math::CopyMatrix44ToArray( projection, GetGameManager()->GetPerspectiveFieldOfView() );

		//---------------�r���[�s����擾---------------
		math::Matrix44 view = GetGameManager()->GetCameraManager()->GetUseCamera()->GetCameraMatrix();
		GLdouble v[16];
		math::CopyMatrix44ToArray(v, view);

		//---------------�r���[�|�[�g�s����擾---------------
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		math::Matrix44 vp = GetGameManager()->GetWindow()->GetViewPortMatrix();


		// �t�s��
		math::Matrix44 invViewPort	= vp;
		//math::Matrix44 invProj		= m_PFOVmatrix;
		math::Matrix44 invProj		= GetGameManager()->GetPerspectiveFieldOfView();
		math::Matrix44 invView		= view;
		
		invViewPort.InverseMatrix();
		invProj.InverseMatrix();
		invView.InverseMatrix();


		// �}�E�X���W���K��
		math::Vector mousePos = GetGameManager()->GetMouse()->GetPos();

		math::Vector pos;
		if( 1 )
		{
			GetGameManager()->ChangeMode3D();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		
			glLoadMatrixf(GetGameManager()->GetCameraManager()->GetUseCamera()->GetCameraMatrix().GetMatrix().ary16);
		
			mousePos.z = 1.0f;
			mousePos.w = 1.0f;
			math::Vector wpos = invView * invProj * invViewPort * mousePos;
			wpos /= wpos.w;
			pos = wpos;

			//���肵���_��`��
			glColor3d(0, 0, 1);
			glBegin(GL_LINES);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(pos.x, pos.y, pos.z); //�ŏ���(0,0,0)
			glEnd();

			m_line.ClearPoints();
			m_line.AddPoint( math::Vector( 0.0f, 0.0f, 0.0f ) ); 
			m_line.AddPoint( math::Vector( pos.x, pos.y, pos.z ) );
		}

		//---------------�q�b�g����---------------
		m_hitSphere.SetPos(m_pos);
		m_hitRay.Init(GetGameManager()->GetCameraManager()->GetUseCamera()->GetPos(), pos);

		if( m_hitSphere.IsHit(&m_infinitie) ) {
			m_animModel.SetColor(nk::Color(1.0f, 0.0f, 0.0f, 1.0f));
		} else {
			m_animModel.SetColor(nk::Color(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//nk::BVRay ray;
		//ray.Init(GetGameManager()->GetCameraManager()->GetUseCamera()->GetPos(), pos);
		//if( ray.IsHit(&m_infinitie) ) {
		//	m_floor.SetColor(nk::Color(0.0f, 1.0f, 0.0f, 1.0f));
		//} else {
		//	m_floor.SetColor(nk::Color(1.0f, 1.0f, 1.0f, 1.0f));
		//}

		//nk::BVPolygon poly;
		//poly.Init(math::Vector(-500, 0, -500), math::Vector(-500, 0, 500), math::Vector(500, 0, -500));
		//if( poly.IsHit(&ray) ) {
		//	m_floor.SetColor(nk::Color(1.0f, 0.0f, 1.0f, 1.0f));
		//} else {
		//	m_floor.SetColor(nk::Color(1.0f, 1.0f, 1.0f, 1.0f));
		//}


		//m_sphere.AddRotate( math::Rad(3), math::Vector(1.0f, 0.0f, 0.0f) );
		// �`��

		//_DrawAxis();

#if 0
#elif 0

		//m_floor.SetScreenId( eSCREEN_ID_1 );
		//m_floor.Draw( math::Vector() );

		//if( m_mouse->IsPress( nk::input::Mouse::LEFT ) ) {
			m_loadIcon.SetScreenId( eSCREEN_ID_1 );
			m_loadIcon.Draw( math::Vector() );
		//}
#elif 0
		graphics::ShaderData data;
		data.shaderName	= "PhongShader";
		data.light.SetPos(math::Vector(30.0f, 1000.0f, 30.0f));
		data.light.SetLook(math::Vector(0.0f, 0.0f, 0.0f));
		data.light.SetTop(math::Vector(0.0f, 0.0f, 1.0f));

		// ��
		m_floor.SetScreenId( eSCREEN_ID_1 );
		m_floor.Draw( math::Vector(), data);
		//m_floor.Draw( math::Vector(0.0f, 0.0f, 500.0f) );
		//m_floor.Draw( math::Vector() );


		//m_sphere.SetPriority( 1002 );
		m_sphere.SetScreenId( eSCREEN_ID_1 );
		m_sphere.Draw( m_pos, data );
		//m_sphere.Draw( math::Vector(), data );
		m_sphere.SetRotate( m_sphereRot, math::Vector( 1.0f, 0.0f, 0.0f ) );
		m_sphereRot += math::Rad( 1.0f );

		// ���{�b�g
		//m_animModel.SetScale(0.5f);
		//m_animModel.SetScreenId( eSCREEN_ID_1 );
		//m_animModel.Draw( math::Vector(), data );
		//m_animModel.Draw( m_pos, data );
		//m_animModel.Draw( m_pos );
		//m_animModel.Update();

#else
		// �V���h�E�}�b�v�̐���
		graphics::ShaderData data;
		data.shaderName		= "ShadowMapping";
		data.mode			= nk::graphics::ShadowMapping::MODE_CREATE_SHADOWMAP;
		data.mappingTex		= GetGameManager()->GetScreen()->GetTexture( GameMain::eSCREEN_ID_SHADOWMAP );
		data.useTechnique	= 0;
		data.light.SetPos(math::Vector(0.0f, 1500.0f, 0.0f));
		data.light.SetLook(math::Vector(0.0f, 0.0f, 0.0f));
		data.light.SetTop(math::Vector(0.0f, 0.0f, 1.0f));

		m_floor.SetPriority(0);
		m_floor.SetScreenId( GameMain::eSCREEN_ID_SHADOWMAP );
		m_floor.Draw( math::Vector(), data );	// @

		m_animModel.SetPriority(1);
		m_animModel.SetScreenId( GameMain::eSCREEN_ID_SHADOWMAP );
		m_animModel.Draw( m_pos, data );	// @
		//m_animModel.Draw( math::Vector(), data );

		//m_sphere.SetScale( 0.3f );
		//m_sphere.SetPriority( 2 );
		//m_sphere.SetScreenId( eSCREEN_ID_SHADOWMAP );
		//m_sphere.Draw( m_pos, data );

		// �V���h�E�}�b�v���g�p���ĕ`��
		data.mode			= nk::graphics::ShadowMapping::MODE_DRAW_SHADOWMAP;
		data.useTechnique	= 1;

		m_floor.SetPriority(1000);
		m_floor.SetScreenId( GameMain::eSCREEN_ID_1 );
		m_floor.Draw( math::Vector(), data );	// @

		m_animModel.SetPriority( 1001 );
		m_animModel.SetScreenId( GameMain::eSCREEN_ID_1 );
		m_animModel.Draw( m_pos, data );	// @
		//m_animModel.Draw( math::Vector(), data );
		m_animModel.Update();

		//m_sphere.SetPriority( 1002 );
		//m_sphere.SetScreenId( eSCREEN_ID_1 );
		//m_sphere.Draw( m_pos, data );
		//m_sphere.SetRotate( m_sphereRot, math::Vector( 1.0f, 0.0f, 0.0f ) );
		//m_sphereRot += math::Rad( 1.0f );
		
		// �V���h�E�}�b�v��`��
		//m_shadowMapSprite.SetScreenId( eSCREEN_ID_1 );
		//m_shadowMapSprite.SetPriority( 2000 );
		//m_shadowMapSprite.SetScale(0.3f);
		//m_shadowMapSprite.Draw(math::Vector(250.0f, 250.0f, 0.0f));
		//m_shadowMapSprite.Draw( math::Vector() );
		//m_shadowMapSprite.SetColor( Color(1.0f, 1.0f, 1.0f, 1.0f) );

		m_line.SetPriority( 2000 );
		m_line.SetScreenId( GameMain::eSCREEN_ID_1 );
		m_line.SetColor( Color( 1.0f, 0.0f, 1.0f, 1.0f ) );
		m_line.Draw( math::Vector() );

		//DISP_PRINT( 300, 300, Color(0, 0, 0, 1), "test%s%d", " aaa", 0xFF );
#endif
	return MESSAGE_NONE;
}

//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void ModelTestScene::RenderLocal( void )
{
	nk::SystemPrint( 0, 0, "Model View Test" );

	SystemPrint( 30, 40, "Arrow          : move"			);
	SystemPrint( 30, 60, "Ctrl + Up Down : up down"		);
	SystemPrint( 30, 80, "Right click    : move motion"	);
	SystemPrint( 30, 100, "Left  click    : attack motion"	);

	SystemPrint( 430, 40, "Esc : Return title"	);

}



}	// namespace game
