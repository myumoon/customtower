//=============================================================================
/*!	@file	autoCriticalSection.h

	@brief	ミューテックス

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

#ifndef __AUTO_CRITICAL_SECTION_H__
#define __AUTO_CRITICAL_SECTION_H__

#include "./threadFunc.h"
#include "./criticalSection.h"

#define SCOPE_CRITICAL_SECTION(criticalSection)	nk::AutoCriticalSection _autoCriticalSection(criticalSection)

namespace nk {

//=============================================================================
/*!
								ミューテックス
*/
//=============================================================================
class AutoCriticalSection {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
private:
	//----------------------メンバ変数-----------------------
	CriticalSection*		m_criticalSection;			//!< クリティカルセクション
	
	//-----------------------メソッド------------------------

public:
	//-------------コンストラクタ・デストラクタ--------------
			AutoCriticalSection( CriticalSection& rhs );
			AutoCriticalSection( const CriticalSection& rhs );
	virtual~AutoCriticalSection();
	
private:
	AutoCriticalSection();
};

	
}	// namespace nk






#endif  // __AUTO_CRITICAL_SECTION_H__