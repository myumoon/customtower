//=============================================================================
/*!	@file	collisionObjectManager.h

	@brief	������`�F�b�N�Ǘ�

	@author	ryunosuke ide
	@date	2013.05.29
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <algorithm>
#include <functional>

#include "collisionObjectManager.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
//namespace {

// �\�[�g�p��r
bool IsUpperRight( const game::battle::CollisionObjectManager::CollisionInfo& left, const game::battle::CollisionObjectManager::CollisionInfo& right )
{
	
  return left.priority < right.priority;
}

// �\�[�g�p��r
bool IsUpperLeft(const game::battle::CollisionObjectManager::CollisionInfo& left, const game::battle::CollisionObjectManager::CollisionInfo& right)
{
	
  return left.priority > right.priority;
}

//}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace game {
namespace battle {


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CollisionObjectManager::CollisionObjectManager()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
CollisionObjectManager::~CollisionObjectManager()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void CollisionObjectManager::_Init( void )
{
	m_hitObjects.reserve( 1024 );
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void CollisionObjectManager::_Term( void )
{

}


//===========================================================================
/*!	@brief		�ǉ�
	@param		bv			�ǉ�����BV
	@param		listener	���X�i�[
	@param		priority	�D��x
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
/*!	@brief		�\�[�g
	@param		ascendingOrder	true.����	false.�~��
	@return		----
*/
//===========================================================================
void CollisionObjectManager::SortByPriority( bool ascendingOrder )
{
	//����
	if( ascendingOrder ) {
		std::sort( m_hitObjects.begin(), m_hitObjects.end(), IsUpperRight );
	}
	//�~��
	else {
		std::sort( m_hitObjects.begin(), m_hitObjects.end(), IsUpperLeft );
	}
}


//===========================================================================
/*!	@brief		������`�F�b�N
	@param		----
	@return		----
*/
//===========================================================================
void CollisionObjectManager::CheckHit( void )
{
	for( u32 checkObjectNo = 0; checkObjectNo < m_hitObjects.size(); ++checkObjectNo ) {
		for( u32 targetNo = checkObjectNo; targetNo < m_hitObjects.size(); ++targetNo ) {
			
			if( checkObjectNo != targetNo ) {
				// �^�[�Q�b�g�̃q�b�g�`�F�N
				if( m_hitObjects[checkObjectNo].listener->AcceptEvent( m_hitObjects[targetNo].listener, HitListener::EVENT_TYPE_TARGET_CHECK ) ) {
					if( m_hitObjects[checkObjectNo].bv->IsHit( m_hitObjects[targetNo].bv ) ) {
						m_hitObjects[checkObjectNo].listener->AcceptEvent( m_hitObjects[targetNo].listener, HitListener::EVENT_TYPE_HIT_RESULT );
					}
				}
				// ���g�̃q�b�g�`�F�b�N
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
/*!	@brief		�폜
	@param		bv		�폜���鋫�E�{�����[��
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
/*!	@brief		�폜
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
