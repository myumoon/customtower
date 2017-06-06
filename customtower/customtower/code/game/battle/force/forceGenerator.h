//=============================================================================
/*!	@file	forceGenerator.h

	@brief	軍生成

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __FORCE_GENERATOR_H__
#define __FORCE_GENERATOR_H__

#include <vector>
#include "game/battle/battleInfo.h"
#include "game/battle/generator.h"
//#include "game/battle/battleExecutor.h"


namespace game {

namespace battle {

class Force;

//! 軍一覧
struct ForceList {
	std::vector<Force*>	forces;
};

//=============================================================================
/*!
								軍ジェネレーター
*/
//=============================================================================
class ForceGenerator : public Generator<ForceList> {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		生成
	*/
	//===========================================================================
// 	const std::vector<Force*>&	Generate( void );
	ForceList*					Generate( void );

	//===========================================================================
	/*!	@brief		削除
	*/
	//===========================================================================
	virtual void				Delete( void );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
// 	std::vector<Force*>			m_forces;		//!< 軍
	ForceList*					m_forceList;	//!< 軍

public:
	//-------------コンストラクタ・デストラクタ--------------
			ForceGenerator();
	virtual~ForceGenerator();
};



}	// namespace battle
	
}	// namespace game


#endif  // __FORCE_GENERATOR_H__