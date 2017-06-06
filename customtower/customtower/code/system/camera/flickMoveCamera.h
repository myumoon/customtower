//=============================================================================
/*!	@file	flickMoveCamera.h

	@brief	フリック移動カメラ

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================


#ifndef __FLICK_MOVE_CAMERA_H__
#define __FLICK_MOVE_CAMERA_H__

#include <vector>
#include "system/camera.h"
#include "input/mouse.h"
#include "input/flick.h"
#include "math/math.h"


//=============================================================================
/*!
							フリック移動カメラ
*/
//=============================================================================
class FlickMoveCamera : public nk::system::NormalCamera {
protected:
	typedef std::vector<nk::input::Mouse::MOUSE_NUM>	VecCheckButton;
	
	static const	f32	FLICK_DECELERATION;				//!< 減衰率
	static const	f32	DEFAULT_ZOOM_SPEED;				//!< ズーム時の速度
	static const	f32	DEFAULT_FIELD_OF_VISION;		//!< デフォルト視野角
	static const	f32	DEFAULT_MAX_FIELD_OF_VISION;	//!< 最大視野角
	static const	f32	DEFAULT_MIN_FIELD_OF_VISION;	//!< 最小視野角
	static const	f32	FLICK_SPEED;					//!< フリック速度
	
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	virtual void	Initialize( const nk::input::Mouse* mouse, nk::input::Mouse::MOUSE_NUM button );

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual void	Update( void );

	//===========================================================================
	/*!	@brief		ズーム速度設定
	*/
	//===========================================================================
	virtual void	SetZoomSpeed( f32 speed );
	
	//===========================================================================
	/*!	@brief		ズーム速度取得
	*/
	//===========================================================================
	virtual f32		GetZoomSpeed( void ) const;
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	const nk::input::Mouse*		m_mouse;		//!< マウス
	nk::input::Flick			m_flick;		//!< フリック
// 	VecCheckButton				m_checkButton;	//!< 監視ボタン
	u32							m_checkButton;	//!< 監視ボタン
	f32							m_zoomSpeed;	//!< ズーム速度
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			FlickMoveCamera();
	virtual~FlickMoveCamera();
};



#endif  // __FLICK_MOVE_CAMERA_H__