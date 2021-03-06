//=============================================================================
/*!	@file	earthObject.h

	@brief	位置計算

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================



#ifndef __EARTH_OBJECT_H__
#define __EARTH_OBJECT_H__

#include "math/vector.h"

namespace game {

namespace battle {


//=============================================================================
/*!
							オブジェクト位置計算
*/
//=============================================================================
class EarthObject {
public:
	//-----------------------型定義--------------------------
	typedef void (EarthObject::*CalcFunc)( void );

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		中心点設定
	*/
	//===========================================================================
	virtual void		Setup(
		f32 					gravityAcc,
		const nk::math::Vector& centerPos 	= nk::math::Vector()
	);

	//===========================================================================
	/*!	@brief		空気抵抗設定
	*/
	//===========================================================================
	virtual void		SetAirResistance( f32 resistance );

	//===========================================================================
	/*!	@brief		移動開始
		@param		firstVelocity			初速度
		@param		true.現在の速度に加算	false.新しく計算
	*/
	//===========================================================================
	virtual void		Start(
		const nk::math::Vector& moveVec	= nk::math::Vector(),
		bool add 						= true
	);

	//===========================================================================
	/*!	@brief		位置設定
	*/
	//===========================================================================
	virtual void			SetPos( const nk::math::Vector& pos );

	//===========================================================================
	/*!	@brief		位置取得
	*/
	//===========================================================================
	virtual nk::math::Vector GetPos( void ) const;

	//===========================================================================
	/*!	@brief		一時停止
	*/
	//===========================================================================
	virtual void		Pause( void );

	//===========================================================================
	/*!	@brief		停止
	*/
	//===========================================================================
	virtual void		Stop( void );

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual void		UpdatePosition( void );

	//===========================================================================
	/*!	@brief		現在の速度ベクトル取得
	*/
	//===========================================================================
	virtual nk::math::Vector	GetProjectionVelocity( void ) const;

	//===========================================================================
	/*!	@brief		垂直ベクトル取得
	*/
	//===========================================================================
	virtual nk::math::Vector	GetVerticalVelocityVec( void ) const;

	//===========================================================================
	/*!	@brief		水平ベクトル取得
	*/
	//===========================================================================
	virtual nk::math::Vector	GetHorizonalVelocityVec( void ) const;

	//===========================================================================
	/*!	@brief		垂直成分取得
	*/
	//===========================================================================
	virtual f32					GetVerticalVelocity( void ) const;

	//===========================================================================
	/*!	@brief		平行移動成分取得
	*/
	//===========================================================================
	virtual f32					GetHrizonalVelocity( void ) const;

	//===========================================================================
	/*!	@brief		グローバル回転量を計算
	*/
	//===========================================================================
	virtual void				CalcGlobalRotation( void );

	//===========================================================================
	/*!	@brief		グローバル回転量加算
	*/
	//===========================================================================
	virtual void				AddGlobalRotation( f32 rotation );
	
	//===========================================================================
	/*!	@brief		グローバル回転量を取得
	*/
	//===========================================================================
	virtual f32					GetGlobalRotation( void ) const;

	//===========================================================================
	/*!	@brief		自動更新中
	*/
	//===========================================================================
	bool						IsAutoUpdate( void ) const;
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//===========================================================================
	/*!	@brief		移動
	*/
	//===========================================================================
	void	_UpdatePosition( void );

	//===========================================================================
	/*!	@brief		停止
	*/
	//===========================================================================
	void	_UpdateWait( void );

	//===========================================================================
	/*!	@brief		速度更新
	*/
	//===========================================================================
	void	_UpdateVelocity( void );

	//----------------------メンバ変数-----------------------
	//! 設定項目
	nk::math::Vector	m_centerPos;				//!< 中心位置
	f32					m_gravityAcceleration;		//!< 加速度
	f32					m_airResistance;			//!< 空気抵抗
	f32					m_firstVirticalVelocity;	//!< 初速度(垂直)
	f32					m_firstHorizonalVelocity;	//!< 初速度(水平)

	//! 更新結果
	nk::math::Vector	m_objectPos;				//!< 現在位置
	f32					m_virticalVelocity;			//!< 垂直成分
	f32					m_horizonalVelocity;		//!< 水平税分
	s32					m_frameCount;				//!< フレームカウンタ
	f32					m_globalRotation;			//!< 回転量(rad)
	bool				m_autoUpdate;				//!< 飛んでいるならtrue
	
	CalcFunc			m_calcFunc;					//!< 計算関数
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			EarthObject();
	virtual~EarthObject();
};
	
}	// namespace battle
	
}	// namespace game






#endif  // __EARTH_OBJECT_H__