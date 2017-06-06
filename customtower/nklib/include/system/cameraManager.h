//=============================================================================
/*!	@file	cameraManager.h

	@brief	カメラ管理

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================


#ifndef __CAMERA_MANAGER_H__
#define __CAMERA_MANAGER_H__

#include <list>
#include "../typedef.h"
#include "../math/vector.h"
#include "../math/matrix.h"
#include "./camera.h"


namespace nk {

namespace system {

//=============================================================================
/*!
								カメラマネージャ
*/
//=============================================================================
class CameraManager {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	static const f32	DEFAULT_FIELD_OF_VISION;	//!< デフォルト視野角(60)
	static const f32	DEFAULT_NEAR_DISTANCE;		//!< デフォルトの見え始める距離(0.1f)
	static const f32	DEFAULT_FAR_DISTANCE;		//!< デフォルトのカメラが届く距離(1000.0f)
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	bool			Initialize( void );

	//===========================================================================
	/*!	@brief		現在使用中のカメラ行列を取得
	*/
	//===========================================================================
	math::Matrix44	GetUseCameraMatrix( void ) const;

	//===========================================================================
	/*!	@brief		使用カメラを変更
	*/
	//===========================================================================
	void			ChangeCamera( CAMERA_ID id );

	//===========================================================================
	/*!	@brief		カメラを取得
	*/
	//===========================================================================
	Camera*			GetCamera( CAMERA_ID id );
	Camera*			GetUseCamera( void ) const;

	//===========================================================================
	/*!	@brief		使用中カメラの見え始めるまでの距離を取得
	*/
	//===========================================================================
	f32				GetCurrentNearDistance( void ) const;

	//===========================================================================
	/*!	@brief		使用中カメラの見えなくなるまでの距離を取得
	*/
	//===========================================================================
	f32				GetCurrentFarDistance( void ) const;

	//===========================================================================
	/*!	@brief		使用中カメラの視野角を取得
	*/
	//===========================================================================
	f32				GetCurrentFieldOfVision( void ) const;
	

	//===========================================================================
	/*!	@brief	新しいカメラを生成		
		@param	near			見え始める距離
		@param	far				見えなくなる距離
		@param	fieldOfView		視野角
		@return	カメラID
		@note	T:生成するカメラ
	*/
	//===========================================================================
	template<class T>
	T* CreateCamera(
		f32 near 			= DEFAULT_NEAR_DISTANCE,
		f32 far 			= DEFAULT_FAR_DISTANCE,
		f32 fieldOfVision 	= DEFAULT_FIELD_OF_VISION
	)
	{
		T*	ins		= new T;
		m_useCamera = ins;
		m_useCamera->Initialize( near, far, fieldOfVision );
		m_cameraList.push_back( m_useCamera );

		return ins;
	}
	
	template<class T>
	T* CreateCamera(
		const math::Vector& pos,
		const math::Vector& look,
		const math::Vector& top,
		f32	nearDistance	= DEFAULT_NEAR_DISTANCE,
		f32 farDistance		= DEFAULT_FAR_DISTANCE,
		f32 fieldOfVision	= DEFAULT_FIELD_OF_VISION
	)
	{
		T*	ins		= new T;
		m_useCamera = ins;
		m_useCamera->Initialize( nearDistance, farDistance, fieldOfVision );
		m_useCamera->SetPos( pos );
		m_useCamera->SetLook( look );
		m_useCamera->SetTop( top );
		m_cameraList.push_back( m_useCamera );

		return ins;
	}

	//===========================================================================
	/*!	@brief		カメラを追加
	*/
	//===========================================================================
	void	AddControlCamera( Camera* addCamera );

private:
	//----------------------メンバ変数-----------------------
	std::list<Camera*>		m_cameraList;	//!< カメラリスト
	Camera*					m_useCamera;	//!< 使用中カメラ

	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 CameraManager();
	~CameraManager();
};

	
}	// namespace system
	
}	// namespace nk




#endif  // __CAMERA_MANAGER_H__