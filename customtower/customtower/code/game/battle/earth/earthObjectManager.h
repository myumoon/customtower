//=============================================================================
/*!	@file	earthObjectManager.h

	@brief	�n���I�u�W�F�N�g�Ǘ�

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
								�I�u�W�F�N�g�Ǘ�
*/
//=============================================================================
class EarthObjectManager {
public:
	//-----------------------�^��`--------------------------
	typedef std::vector<EarthObject*>		VecEarthObject;			//!< �d�͓K�p�I�u�W�F�N�g

	//----------------------�ÓI�����o-----------------------
	static const s32	MAX_REGISTER_OBJECTS_NUM	= 1024;	//!< �ő�o�^��
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�d�̓I�u�W�F�N�g�ǉ�
	*/
	//===========================================================================
	bool			RegisterEarthObject( EarthObject* obj );

	//===========================================================================
	/*!	@brief		�d�̓I�u�W�F�N�g���O
	*/
	//===========================================================================
	void			RemoveEarthObject( EarthObject* obj );

	//===========================================================================
	/*!	@brief		���ˏ���
	*/
	//===========================================================================
	void			AcceptProjection( void );

	//===========================================================================
	/*!	@brief		�o�^�I�u�W�F�N�g�S�폜
	*/
	//===========================================================================
	void			Clear( void );
	
	
private:
	//-----------------------���\�b�h------------------------
	void			_Init( void );
	void			_Term( void );

	//----------------------�����o�ϐ�-----------------------
	VecEarthObject		m_earthObjects;			//!< �I�u�W�F�N�g
	f32					m_gravity;				//!< �d��
	nk::math::Vector	m_centerPos;			//!< ���S�ʒu

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			EarthObjectManager();
	virtual~EarthObjectManager();
};
	
}	// namespace battle
}	// namespace game



#endif  // __EARTH_OBJECT_MANAGER_H__