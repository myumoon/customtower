//=============================================================================
/*!	@file	cameraManager.h

	@brief	�J�����Ǘ�

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/system/cameraManager.h"
#include "../../include/general.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

namespace nk {
namespace system {

const f32 CameraManager::DEFAULT_FIELD_OF_VISION	= 60.0f;	// �f�t�H���g����p(60)
const f32 CameraManager::DEFAULT_NEAR_DISTANCE		= 0.1f;		// �f�t�H���g�̌����n�߂鋗��(0.1f)
const f32 CameraManager::DEFAULT_FAR_DISTANCE		= 1000.0f;	// �f�t�H���g�̃J�������͂�����(1000.0f)

}	// namespace system
}	// namespace nk

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {

namespace system {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
CameraManager::CameraManager()
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
	\note	�S�J�������폜����
*/
//===========================================================================
CameraManager::~CameraManager()
{
	std::list<Camera*>::iterator itr = m_cameraList.begin();
	std::list<Camera*>::iterator end = m_cameraList.end();
	for( ; itr != end; ++itr ) {
		SafeDelete( *itr );	// �J�������폜
	}
	m_cameraList.clear();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----	
*/
//===========================================================================
bool CameraManager::Initialize( void )
{

#if defined(NK_USE_GL)
	/* �J�����s���ݒ� */
	//glMatrixMode( GL_PROJECTION );
	//glLoadIdentity();


	//gluPerspective( m_fieldOfVision, m_screenWidth / m_screenHeight, m_near, m_far );
	//glViewport(0, 0, width, height );
#endif

	

	
	return true;
}


	
//===========================================================================
/*!	@brief	���ݎg�p���̃J�����̍s����擾
	@param	�Ȃ�
	@return	�g�p���J�����̍s��
*/
//===========================================================================
math::Matrix44 CameraManager::GetUseCameraMatrix() const
{
	return m_useCamera->GetCameraMatrix();
}


//===========================================================================
/*!	@brief	�g�p�J������ύX
	@param	�J����ID
	@return	�Ȃ�
*/
//===========================================================================
void CameraManager::ChangeCamera( CAMERA_ID id)
{
	std::list<Camera*>::iterator itr = m_cameraList.begin();
	std::list<Camera*>::iterator end = m_cameraList.end();

	for( ; itr != end; ++itr ) {
		if( (*itr)->GetID() == id ) {
			m_useCamera = *itr;
			break;
		}
	}

}


//===========================================================================
/*!	@brief	�J�������擾
	@param	id	: �擾����J����ID
	@return	�J����
*/
//===========================================================================
Camera* CameraManager::GetCamera( CAMERA_ID id)
{
	std::list<Camera*>::iterator itr = m_cameraList.begin();
	std::list<Camera*>::iterator end = m_cameraList.end();

	for( ; itr != end; ++itr) {
		if( (*itr)->GetID() == id ) {
			return *itr;
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief	���ݎg�p���̃J�������擾
	@param	�Ȃ�
	@return	�J����
*/
//===========================================================================
Camera* CameraManager::GetUseCamera() const
{
	return m_useCamera;
}



//===========================================================================
/*!	@brief	���ݎg�p���̃J�����̌����n�߂�܂ł̋������擾
	@param	----
	@return	����
*/
//===========================================================================
f32 CameraManager::GetCurrentNearDistance( void ) const
{
	NULL_ASSERT( m_useCamera );
	
	return m_useCamera->GetNearDistance();
}


//===========================================================================
/*!	@brief	���ݎg�p���̃J�����̌����Ȃ��Ȃ�܂ł̋������擾
	@param	----
	@return	����
*/
//===========================================================================
f32 CameraManager::GetCurrentFarDistance( void ) const
{
	NULL_ASSERT( m_useCamera );
	
	return m_useCamera->GetFarDistance();
}



//===========================================================================
/*!	@brief	���ݎg�p���̃J�����̎���p���擾
	@param	----
	@return	����
*/
//===========================================================================
f32 CameraManager::GetCurrentFieldOfVision( void ) const
{
	NULL_ASSERT( m_useCamera );
	
	return m_useCamera->GetFieldOfVision();
}


//===========================================================================
/*!	@brief		�J�����ǉ�
	@param		addCamera	�ǉ��J����
	@return		----
*/
//===========================================================================
void CameraManager::AddControlCamera( Camera* addCamera )
{
	NULL_ASSERT( addCamera );
	if( addCamera ) {
		m_cameraList.push_back( addCamera );
	}
	
}
	
}	// namespace system
	
}	// namespace nk