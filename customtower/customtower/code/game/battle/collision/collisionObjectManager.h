//=============================================================================
/*!	@file	collisionObjectManager.h

	@brief	当たりチェック管理

	@author	ryunosuke ide
	@date	2013.05.29
*/
//=============================================================================


#ifndef __COLLISION_CHECKER_H__
#define __COLLISION_CHECKER_H__

#include <vector>
#include "collision/boundaryVolume.h"
#include "hitListener.h"



namespace game {

namespace battle {

//=============================================================================
/*!
							衝突オブジェクト管理
*/
//=============================================================================
class CollisionObjectManager {
public:
	//-----------------------型定義--------------------------
	//! 優先度
	static const u32	DEFAULT_PRIORITY	= 1000;

	//! ヒット情報
	struct CollisionInfo {
		nk::BoundaryVolume*			bv;			//!< 境界ボリューム
		HitListener*				listener;	//!< 結果リスナー
// 		const nk::BoundaryVolume*	bv;			//!< 境界ボリューム
// 		const HitListener*			listener;	//!< 結果リスナー
		u32							priority;	//!< 優先度
	};

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		追加
	*/
	//===========================================================================
	void	AddCollisionObject(
		nk::BoundaryVolume*			bv,
		HitListener*				listener,
// 		const nk::BoundaryVolume*	bv,
// 		const HitListener*			listener,
		u32 						priority = DEFAULT_PRIORITY
	);

	//===========================================================================
	/*!	@brief		削除
	*/
	//===========================================================================
	void	RemoveCollisionObject( nk::BoundaryVolume* bv );

	//===========================================================================
	/*!	@brief		削除
	*/
	//===========================================================================
	void	RemoveCollisionObjects( void );

	//===========================================================================
	/*!	@brief		ソート
		@param		ascendingOrder	true.昇順	false.降順
	*/
	//===========================================================================
	void	SortByPriority( bool ascendingOrder = true );

	//===========================================================================
	/*!	@brief		当たりチェック
	*/
	//===========================================================================
	void	CheckHit( void );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	std::vector<CollisionInfo>			m_hitObjects;		//!< 当たり

public:
	//-------------コンストラクタ・デストラクタ--------------
			CollisionObjectManager();
	virtual~CollisionObjectManager();
};


}	// namespace battle
	
}	// namespace game



#endif  // __COLLISION_CHECKER_H__