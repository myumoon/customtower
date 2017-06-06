//=============================================================================
/*!	@file	collisionObjectManager.h

	@brief	������`�F�b�N�Ǘ�

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
							�Փ˃I�u�W�F�N�g�Ǘ�
*/
//=============================================================================
class CollisionObjectManager {
public:
	//-----------------------�^��`--------------------------
	//! �D��x
	static const u32	DEFAULT_PRIORITY	= 1000;

	//! �q�b�g���
	struct CollisionInfo {
		nk::BoundaryVolume*			bv;			//!< ���E�{�����[��
		HitListener*				listener;	//!< ���ʃ��X�i�[
// 		const nk::BoundaryVolume*	bv;			//!< ���E�{�����[��
// 		const HitListener*			listener;	//!< ���ʃ��X�i�[
		u32							priority;	//!< �D��x
	};

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�ǉ�
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
	/*!	@brief		�폜
	*/
	//===========================================================================
	void	RemoveCollisionObject( nk::BoundaryVolume* bv );

	//===========================================================================
	/*!	@brief		�폜
	*/
	//===========================================================================
	void	RemoveCollisionObjects( void );

	//===========================================================================
	/*!	@brief		�\�[�g
		@param		ascendingOrder	true.����	false.�~��
	*/
	//===========================================================================
	void	SortByPriority( bool ascendingOrder = true );

	//===========================================================================
	/*!	@brief		������`�F�b�N
	*/
	//===========================================================================
	void	CheckHit( void );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	std::vector<CollisionInfo>			m_hitObjects;		//!< ������

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			CollisionObjectManager();
	virtual~CollisionObjectManager();
};


}	// namespace battle
	
}	// namespace game



#endif  // __COLLISION_CHECKER_H__