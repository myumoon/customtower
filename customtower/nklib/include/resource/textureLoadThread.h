//=============================================================================
/*!	@file	textureLoadThread.h

	@brief	テクスチャロードスレッド

	@author	ryunosuke ide
	@date	2013.03.09
*/
//=============================================================================


#ifndef __TEXTURE_LOAD_THREAD_H__
#define __TEXTURE_LOAD_THREAD_H__

#include <string>
#include "../thread/thread.h"
#include "./textureUtility.h"


namespace nk {


namespace resource {


class Texture;

//=============================================================================
/*!
						テクスチャロードスレッド
*/
//=============================================================================
class TextureLoadThread : public Thread {
private:
	//-----------------------型定義--------------------------
	struct _LoadSurface {
		std::string		path;
		ImageSurface	surface;

		_LoadSurface() {
		}
	};
	typedef std::vector<_LoadSurface>		VecSurface;
	
public:
	
	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! ロードテクスチャを追加
	void				Add( const char* path );

	//! 全ファイルロードしていたらtrueを返す
	bool				IsComplete( void ) const;

	//! ロード完了時にtrueを返す
	bool				IsComplete( const char* path ) const;

	//! テクスチャを習得
	//! メインスレッドから実行してください
	Texture*			PopTexture( const char* path );

protected:
	//! スレッド処理
	virtual void		ThreadFunc( void );
	
private:
	Texture*			_CreateTexture( const _LoadSurface& surface ) const;
	
	//! ロード
	//ImageSurface*		_LoadSurface( const char* path );
	
	//----------------------メンバ変数-----------------------
	VecSurface			m_vecSurface;			//!< テクスチャ
	//Mutex*				m_mutex;				//!< ミューテックス
	CriticalSection		m_criticalSection;		//!< クリティカルセクション
	bool				m_completed;			//!< ロード完了
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			TextureLoadThread();
	virtual~TextureLoadThread();
};


}	// namespace resource

}	// namespace nk

#endif  // __TEXTURE_LOAD_THREAD_H__