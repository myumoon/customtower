//=============================================================================
/*!	@file	collisionObjectManager.h

	@brief	当たりチェック管理

	@author	ryunosuke ide
	@date	2013.05.29
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <algorithm>
#include <functional>

#include "collisionObjectManager.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
//namespace {

// ソート用比較
bool IsUpperRight( const game::battle::CollisionObjectManager::CollisionInfo& left, const game::battle::CollisionObjectManager::CollisionInfo& right )
{
	
  return left.priority < right.priority;
}

// ソート用比較
bool IsUpperLeft(const game::battle::CollisionObjectManager::CollisionInfo& left, const game::battle::CollisionObjectManager::CollisionInfo& right)
{
	
  return left.priority > right.priority;
}

//}	// unnamed

//---------------------------------関数定義---------------------------------

namespace game {
namespace battle {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CollisionObjectManager::CollisionObjectManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
CollisionObjectManager::~CollisionObjectManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void CollisionObjectManager::_Init( void )
{
	m_hitObjects.reserve( 1024 );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void CollisionObjectManager::_Term( void )
{

}


//===========================================================================
/*!	@brief		追加
	@param		bv			追加するBV
	@param		listener	リスナー
	@param		priority	優先度
	@return		----
*/
//===========================================================================
void CollisionObjectManager::AddCollisionObject(
	nk::BoundaryVolume*			bv,
	HitListener*				listener,
// 	const nk::BoundaryVolume*	bv,
// 	const HitListener*			listener,
	u32 						priority
)
{
	CollisionInfo	addInfo = {
		bv,
		listener,
		priority
	};
	
	m_hitObjects.push_back( addInfo );
	
}

//===========================================================================
/*!	@brief		ソート
	@param		ascendingOrder	true.昇順	false.降順
	@return		----
*/
//===========================================================================
void CollisionObjectManager::SortByPriority( bool ascendingOrder )
{
	//昇順
	if( ascendingOrder ) {
		std::sort( m_hitObjects.begin(), m_hitObjects.end(), IsUpperRight );
	}
	//降順
	else {
		std::sort( m_hitObjects.begin(), m_hitObjects.end(), IsUpperLeft );
	}
}


//===========================================================================
/*!	@brief		当たりチェック
	@param		----
	@return		----
*/
//===========================================================================
void CollisionObjectManager::CheckHit( void )
{
	for( u32 checkObjectNo = 0; checkObjectNo < m_hitObjects.size(); ++checkObjectNo ) {
		for( u32 targetNo = checkObjectNo; targetNo < m_hitObjects.size(); ++targetNo ) {
			
			if( checkObjectNo != targetNo ) {
				// ターゲットのヒットチェク
				if( m_hitObjects[checkObjectNo].listener->AcceptEvent( m_hitObjects[targetNo].listener, HitListener::EVENT_TYPE_TARGET_CHECK ) ) {
					if( m_hitObjects[checkObjectNo].bv->IsHit( m_hitObjects[targetNo].bv ) ) {
						m_hitObjects[checkObjectNo].listener->AcceptEvent( m_hitObjects[targetNo].listener, HitListener::EVENT_TYPE_HIT_RESULT );
					}
				}
				// 自身のヒットチェック
				if( m_hitObjects[targetNo].listener->AcceptEvent( m_hitObjects[checkObjectNo].listener, HitListener::EVENT_TYPE_TARGET_CHECK ) ) {
					if( m_hitObjects[targetNo].bv->IsHit( m_hitObjects[checkObjectNo].bv ) ) {
						m_hitObjects[targetNo].listener->AcceptEvent( m_hitObjects[checkObjectNo].listener, HitListener::EVENT_TYPE_HIT_RESULT );
					}
				}
			}
		}
	}
	
}

//===========================================================================
/*!	@brief		削除
	@param		bv		削除する境界ボリューム
	@return		----
*/
//===========================================================================
void CollisionObjectManager::RemoveCollisionObject( nk::BoundaryVolume* bv )
{
	std::vector<CollisionInfo>::iterator	itr	= m_hitObjects.begin();
	for( ; itr != m_hitObjects.end(); ) {
		if( (*itr).bv == bv ) {
			itr	= m_hitObjects.erase( itr );
		}
		else {
			++itr;
		}
	}
	
// 	m_hitObjects.erase(
// 		std::remove( m_hitObjects.begin(), m_hitObjects.end(), bv ),
// 		m_hitObjects.end()
// 	);
	
}

//===========================================================================
/*!	@brief		削除
	@param		----
	@return		----
*/
//===========================================================================
void CollisionObjectManager::RemoveCollisionObjects( void )
{
	m_hitObjects.clear();
	
}


}	// namespace battle
	
}	// namespace game
