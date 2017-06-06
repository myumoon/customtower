//=============================================================================
/*!	@file	mutex.h

	@brief	ミューテックス

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "./threadFunc.h"
#include "./mutex.h"

namespace nk {

//=============================================================================
/*!
								ミューテックス
*/
//=============================================================================
class Mutex {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! ロック
	void			Lock( void );

	//! アンロック
	void			Unlock( void );

	//! コピー
	Mutex&			operator =( const Mutex& mutex );
	
private:
	//-----------------------メソッド------------------------
	//! 生成
	void			_Create( void );

	//! 削除
	void			_Delete( void );

	//! コピー
	void			_Copy( const Mutex& mutex );

	//! 終了処理
	void			_Term( void );

	//----------------------メンバ変数-----------------------
	s32				m_copyCount;	//!< ミューテックスコピーカウンタ
	MUTEX_HANDLE	m_handle;		//!< ミューテックスハンドル	
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			Mutex();
			Mutex( MUTEX_HANDLE handle );
			Mutex( const Mutex& mutex );
	virtual~Mutex();
	
private:
	
};

	
}	// namespace nk






#endif  // __MUTEX_H__