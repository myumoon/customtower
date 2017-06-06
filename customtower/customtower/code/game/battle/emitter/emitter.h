//=============================================================================
/*!	@file	emitter.h
	@brief	エミッター

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
								エミッター
*/
//=============================================================================
template<typename T>
class Emitter : public EmitterBase {
private:
	typedef std::vector< EmitObjectHandle<T> > VecEmitObject;
	
public:
	//-----------------------型定義--------------------------
	static const u32	EMIT_OBJECT_MAX_SIZE	= 2048;

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		セットアップ
	*/
	//===========================================================================
	virtual void	Setup( BattleExecutor* battleExec, Generator<T>* generator, Manager<T>* manager )
	{
		m_battleExec	= battleExec;
		m_generator		= generator;
		m_manager		= manager;
	}

	//===========================================================================
	/*!	@brief		除外
	*/
	//===========================================================================
	virtual void	Remove( T* obj )
	{
	}

	//===========================================================================
	/*!	@brief		発射
	*/
	//===========================================================================
	virtual void	Emit( void )
	{
		EmitObjectHandle<T>	handle	= _Emit();
		m_emitObjcts.push_back( handle );
	}

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual void	Update( void )
	{
		NULL_ASSERT( m_manager );
		
		EmitterBase::Update();

		// 更新
		{
			VecEmitObject::iterator	itr	= m_emitObjcts.begin();
			for( ; itr != m_emitObjcts.end(); ++itr ) {
				(*itr).Update();
			}
		}

		// 削除
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
	/*!	@brief		発射
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
	//----------------------メンバ変数-----------------------
	Generator<T>*							m_generator;	//!< ジェネレーター
	Manager<T>*								m_manager;		//!< マネージャー
	VecEmitObject							m_emitObjcts;	//!< 生成オブジェクト
	BattleExecutor*							m_battleExec;	//!< バトル実行処理への参照
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void )
	{
	}
	void	_Term( void )
	{
	}

	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			Emitter() { _Init(); }
	virtual~Emitter() { _Term(); }
};


	
}	// namespace battle
}	// namespace game


#endif  // __EMITTER_H__