//=============================================================================
/*!	@file	cameraManager.h

	@brief	カメラ管理

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/system/cameraManager.h"
#include "../../include/general.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

namespace nk {
namespace system {

const f32 CameraManager::DEFAULT_FIELD_OF_VISION	= 60.0f;	// デフォルト視野角(60)
const f32 CameraManager::DEFAULT_NEAR_DISTANCE		= 0.1f;		// デフォルトの見え始める距離(0.1f)
const f32 CameraManager::DEFAULT_FAR_DISTANCE		= 1000.0f;	// デフォルトのカメラが届く距離(1000.0f)

}	// namespace system
}	// namespace nk

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {

namespace system {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
CameraManager::CameraManager()
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
	\note	全カメラを削除する
*/
//===========================================================================
CameraManager::~CameraManager()
{
	std::list<Camera*>::iterator itr = m_cameraList.begin();
	std::list<Camera*>::iterator end = m_cameraList.end();
	for( ; itr != end; ++itr ) {
		SafeDelete( *itr );	// カメラを削除
	}
	m_cameraList.clear();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----	
*/
//===========================================================================
bool CameraManager::Initialize( void )
{

#if defined(NK_USE_GL)
	/* カメラ行列を設定 */
	//glMatrixMode( GL_PROJECTION );
	//glLoadIdentity();


	//gluPerspective( m_fieldOfVision, m_screenWidth / m_screenHeight, m_near, m_far );
	//glViewport(0, 0, width, height );
#endif

	

	
	return true;
}


	
//===========================================================================
/*!	@brief	現在使用中のカメラの行列を取得
	@param	なし
	@return	使用中カメラの行列
*/
//===========================================================================
math::Matrix44 CameraManager::GetUseCameraMatrix() const
{
	return m_useCamera->GetCameraMatrix();
}


//===========================================================================
/*!	@brief	使用カメラを変更
	@param	カメラID
	@return	なし
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
/*!	@brief	カメラを取得
	@param	id	: 取得するカメラID
	@return	カメラ
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
/*!	@brief	現在使用中のカメラを取得
	@param	なし
	@return	カメラ
*/
//===========================================================================
Camera* CameraManager::GetUseCamera() const
{
	return m_useCamera;
}



//===========================================================================
/*!	@brief	現在使用中のカメラの見え始めるまでの距離を取得
	@param	----
	@return	距離
*/
//===========================================================================
f32 CameraManager::GetCurrentNearDistance( void ) const
{
	NULL_ASSERT( m_useCamera );
	
	return m_useCamera->GetNearDistance();
}


//===========================================================================
/*!	@brief	現在使用中のカメラの見えなくなるまでの距離を取得
	@param	----
	@return	距離
*/
//===========================================================================
f32 CameraManager::GetCurrentFarDistance( void ) const
{
	NULL_ASSERT( m_useCamera );
	
	return m_useCamera->GetFarDistance();
}



//===========================================================================
/*!	@brief	現在使用中のカメラの視野角を取得
	@param	----
	@return	距離
*/
//===========================================================================
f32 CameraManager::GetCurrentFieldOfVision( void ) const
{
	NULL_ASSERT( m_useCamera );
	
	return m_useCamera->GetFieldOfVision();
}


//===========================================================================
/*!	@brief		カメラ追加
	@param		addCamera	追加カメラ
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