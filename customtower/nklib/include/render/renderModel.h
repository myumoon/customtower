//=============================================================================
/*!	@file	renderModel.h

	@brief	描画モデル基底クラス

	@author	井手 竜之介
	@date	2012/03/03
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __RENDERMODEL_H__
#define __RENDERMODEL_H__

//-------------------------------インクルード-------------------------------
#include "drawPacketManager.h"
#include "../resource/resourcemanager.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"
#include "../graphics/attitude.h"


namespace nk {
namespace graphics {

//=============================================================================
/*!
								描画基底クラス
*/
//=============================================================================
class RenderModel {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	static system::CameraManager*			m_cameraMng;		//!< カメラ管理
	static resource::ResourceManager*		m_resourceMng;		//!< リソース管理クラス
	static graphics::DrawPacketManager*		m_drawPacketMng;	//!< 描画パケット管理
	
	
	//-----------------------メソッド------------------------

	//! 描画
	virtual void	Draw( const math::Vector& pos )	{};
	
	//! 回転量をセット
	virtual void	SetRotate( f32 amount, const math::Vector& axis );
	virtual void	AddRotate( f32 amount, const math::Vector& axis );

	//! スケールをセット
	virtual void	SetScale( f32 scale );
	virtual void	AddScale( f32 scale );

	//! 色をセット
	virtual void	SetColor(Color color);

	//! 描画優先度を設定
	virtual void	SetPriority( u32 pri );

	//! 描画スクリーン
	virtual void	SetScreenId( s32 screenId );

	//! 表示・非表示をセット
	virtual void	SetVisible( bool visible );

	//! 表示・非表示を取得
	virtual bool	Visible( void ) const;
	
	//! リソース管理をセット
	static void	SetResourceManager( resource::ResourceManager* mng )	{ m_resourceMng = mng; }
	
	//! カメラ管理をセット
	static void SetCameraManager( system::CameraManager* mng )			{ m_cameraMng = mng; }

	//! 描画パケット管理をセット
	static void	SetDrawPacketManager( graphics::DrawPacketManager* mng )	{ m_drawPacketMng = mng; }
	
protected:
	//----------------------メンバ変数-----------------------
	Attitude		m_attitude;		//!< 姿勢
	Color			m_color;		//!< 色
	u32				m_priority;		//!< 描画優先度
	s32				m_screenId;		//!< 描画スクリーン
	bool			m_visible;		//!< 表示
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			 RenderModel();
	virtual ~RenderModel();
};


}	// namespace graphics
}	// namespace nk







#endif  // __RENDERMODEL_H__