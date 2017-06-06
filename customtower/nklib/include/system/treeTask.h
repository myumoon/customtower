//=============================================================================
/*!	@file	treeTask

	@brief	�c���[�^�X�N

	@author	ryunosuke ide
	@date	2013.03.17
*/
//=============================================================================


#ifndef __TREETASK_H__
#define __TREETASK_H__

#include <list>
#include "./task.h"


namespace nk {


namespace system {

//=============================================================================
/*!
								�c���[�^�X�N
*/
//=============================================================================
class TreeTask : public Task {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual void		Execute( void* parentParam )	{}

	//===========================================================================
	/*!	@brief		�q���̍X�V
	*/
	//===========================================================================
	virtual void		UpdateChild( void* parentParam );

	//===========================================================================
	/*!	@brief		�q����ǉ�
	*/
	//===========================================================================
	virtual void		ConnectChild( Task* task );

	//===========================================================================
	/*!	@brief		�q�����̂Ă�
	*/
	//===========================================================================
	virtual void		DisconnectChild( Task* task );
	virtual void		DisconnectAllChild( void );

	
private:
	//----------------------�����o�ϐ�-----------------------
	std::list<Task*>	m_childList;		//!< �q���c���[
	
	//-----------------------���\�b�h------------------------
	void	_Init();
	void	_Term();

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			TreeTask();
	virtual~TreeTask();
};

}	// namespace system
}	// namespace nk




#endif  // __TREETASK_H__