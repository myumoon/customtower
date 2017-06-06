//=============================================================================
/*!	@file	gameObject.h

	@brief	�Q�[���I�u�W�F�N�g

	@author	ryunosuke ide
	@date	2013.05.19
*/
//=============================================================================

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "system.h"

#include "system/updateObject.h"
#include "system/renderObject.h"

namespace game {

class GameMain;
class GameObjectManager;
	
//=============================================================================
/*!
					�Q�[���I�u�W�F�N�g�C���^�[�t�F�[�X
*/
//=============================================================================
class GameObject /*: public UpdateObject,*//* public RenderObject*/ {
private:
	friend class GameMain;
	
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------

	
	//-----------------------���\�b�h------------------------
	
	//===========================================================================
	/*!	@brief		�V�X�e���R�[���o�b�N
		@param		event	�C�x���g
	*/
	//===========================================================================
	virtual void		CallbackSystemEvent( nk::Main::SYSTEM_EVENT event ) {}
	
	
	//===========================================================================
	/*!	@brief		�Q�[���Ǘ�
	*/
	//===========================================================================
	static GameMain*	GetGameManager( void )				{ return m_gameManager;		}
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

	//----------------------�����o�ϐ�-----------------------

	static	GameObjectManager*	m_gameObjectManager;	//!< �Q�[���I�u�W�F�N�g�Ǘ�
	static	GameMain*			m_gameManager;			//!< �Q�[���Ǘ�
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			GameObject();
	virtual~GameObject();
};

}	// namespace game





#endif  // __GAME_OBJECT_H__