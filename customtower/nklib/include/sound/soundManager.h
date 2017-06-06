//=============================================================================
/*!	@file	soundManager.h

	@brief	サウンド管理

	@author	ryunosuke ide
	@date	2013.02.10
*/
//=============================================================================

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__


namespace nk {

namespace sound {




//=============================================================================
/*!
					サウンド処理
*/
//=============================================================================
class SoundManager {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 初期化
	static bool			Initialize( void );

	//! 終了処理
	static bool			Finalize( void );

	//! オーディオ登録
	//virtual bool		Register( u32 id );

	//! 再生
	//virtual bool		Play( void );

	//! 停止
	//virtual bool		Stop( void );
	
private:
	//----------------------メンバ変数-----------------------
	
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			SoundManager();
	virtual~SoundManager();
};
	
}	// namespace sound
	
}	// namespace nk







#endif  // __SOUND_MANAGER_H__