//=============================================================================
/*!	@file	earthObjectManager.h

	@brief	地球オブジェクト管理

	@author	ryunosuke ide
	@date	2013.06.30
*/
//=============================================================================

#ifndef __EARTH_OBJECT_MANAGER_H__
#define __EARTH_OBJECT_MANAGER_H__


#include <vector>
#include "earthObject.h"


namespace game {
namespace battle {

//=============================================================================
/*!
								オブジェクト管理
*/
//=============================================================================
class EarthObjectManager {
public:
	//-----------------------型定義--------------------------
	typedef std::vector<EarthObject*>		VecEarthObject;			//!< 重力適用オブジェクト

	//----------------------静的メンバ-----------------------
	static const s32	MAX_REGISTER_OBJECTS_NUM	= 1024;	//!< 最大登録数
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		重力オブジェクト追加
	*/
	//===========================================================================
	bool			RegisterEarthObject( EarthObject* obj );

	//===========================================================================
	/*!	@brief		重力オブジェクト除外
	*/
	//===========================================================================
	void			RemoveEarthObject( EarthObject* obj );

	//===========================================================================
	/*!	@brief		投射処理
	*/
	//===========================================================================
	void			AcceptProjection( void );

	//===========================================================================
	/*!	@brief		登録オブジェクト全削除
	*/
	//===========================================================================
	void			Clear( void );
	
	
private:
	//-----------------------メソッド------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------メンバ変数-----------------------
	VecEarthObject		m_earthObjects;			//!< オブジェクト
	f32					m_gravity;				//!< 重力
	nk::math::Vector	m_centerPos;			//!< 中心位置

public:
	//-------------コンストラクタ・デストラクタ--------------
			EarthObjectManager();
	virtual~EarthObjectManager();
};
	
}	// namespace battle
}	// namespace game



#endif  // __EARTH_OBJECT_MANAGER_H__