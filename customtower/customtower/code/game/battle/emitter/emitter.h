//=============================================================================
/*!	@file	emitter.h
	@brief	�G�~�b�^�[

	@author	ryunosuke ide
	@date	2013.07.03
*/
//=============================================================================



#ifndef __EMITTER_H__
#define __EMITTER_H__

#include <vector>
#include "emitterBase.h"
#include "emitObjectHandle.h"
#include "game/battle/generator.h"
#include "game/battle/manager/manager.h"
#include "game/battle/battleExecutor.h"

namespace game {
namespace battle {


//=============================================================================
/*!
								�G�~�b�^�[
*/
//=============================================================================
template<typename T>
class Emitter : public EmitterBase {
private:
	typedef std::vector< EmitObjectHandle<T> > VecEmitObject;
	
public:
	//-----------------------�^��`--------------------------
	static const u32	EMIT_OBJECT_MAX_SIZE	= 2048;

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�Z�b�g�A�b�v
	*/
	//===========================================================================
	virtual void	Setup( BattleExecutor* battleExec, Generator<T>* generator, Manager<T>* manager )
	{
		m_battleExec	= battleExec;
		m_generator		= generator;
		m_manager		= manager;
	}

	//===========================================================================
	/*!	@brief		���O
	*/
	//===========================================================================
	virtual void	Remove( T* obj )
	{
	}

	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	virtual void	Emit( void )
	{
		EmitObjectHandle<T>	handle	= _Emit();
		m_emitObjcts.push_back( handle );
	}

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual void	Update( void )
	{
		NULL_ASSERT( m_manager );
		
		EmitterBase::Update();

		// �X�V
		{
			VecEmitObject::iterator	itr	= m_emitObjcts.begin();
			for( ; itr != m_emitObjcts.end(); ++itr ) {
				(*itr).Update();
			}
		}

		// �폜
		{
			VecEmitObject::iterator	itr	= m_emitObjcts.begin();
			for( ; itr != m_emitObjcts.end(); ) {
				if( (*itr).IsDead() ) {
					m_manager->Remove( (*itr).GetRegisteredObject() );
					itr	= m_emitObjcts.erase( itr );
				}
				else {
					++itr;
				}
			}
		}
		
	}

protected:
	//===========================================================================
	/*!	@brief		����
	*/
	//===========================================================================
	EmitObjectHandle<T>		_Emit( void )
	{
		NULL_ASSERT( m_generator );
		NULL_ASSERT( m_manager );
		
		T*	emitObj	= m_generator->Generate();
		emitObj->InitializeForBattle( m_battleExec );
		emitObj->SetPos( m_pos );
		emitObj->Start( m_direction * m_velocity );
		m_manager->Add( emitObj );

		EmitObjectHandle<T>	handle;
		handle.Register( emitObj );
		handle.SetLife( m_life );

		return handle;
	}
	
protected:
	//----------------------�����o�ϐ�-----------------------
	Generator<T>*							m_generator;	//!< �W�F�l���[�^�[
	Manager<T>*								m_manager;		//!< �}�l�[�W���[
	VecEmitObject							m_emitObjcts;	//!< �����I�u�W�F�N�g
	BattleExecutor*							m_battleExec;	//!< �o�g�����s�����ւ̎Q��
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void )
	{
	}
	void	_Term( void )
	{
	}

	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Emitter() { _Init(); }
	virtual~Emitter() { _Term(); }
};


	
}	// namespace battle
}	// namespace game


#endif  // __EMITTER_H__