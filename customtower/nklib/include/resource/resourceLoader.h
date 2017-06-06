//=============================================================================
/*!	@file	resourceLoader.h

	@brief	リソースロード

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

#ifndef __RESOURCE_LOADER_H__
#define __RESOURCE_LOADER_H__

#include "../thread/thread.h"
#include "./textureLoadThread.h"
#include "./resourceManager.h"

namespace nk {

namespace resource {

//=============================================================================
/*!
								リソースロード
*/
//=============================================================================
class ResourceLoader : public Thread {
private:
	//-----------------------型定義--------------------------
	struct _FileInfo {
		bool			isImage;
		std::string		fileName;
	};
public:
	
	
	
	
	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! ロードファイル
	void			Load( const char* path );

	//! 更新
	//! @return	true.ロード完了
	//! @note	メインスレッドから呼ばなければならない
	bool			Update( void );


	// リソースマネージャー登録
	static void		SetResourceMnager( ResourceManager* mng ) { m_resourceMng = mng; }
	
	
protected:
	void			ThreadFunc( void );
	
private:
	//----------------------メンバ変数-----------------------
	TextureLoadThread*			m_texLoadThread;	//!< テクスチャロードスレッド
	std::vector<_FileInfo>		m_vecLoadFiles;		//!< ロードファイル
	bool						m_loadTexComplete;	//!< テクスチャロード完了時にtrue
	
	static ResourceManager*		m_resourceMng;		// リソース管理
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			ResourceLoader();
	virtual~ResourceLoader();
};
	
}	// namespace resource
}	// namespace nk






#endif  // __RESOURCE_LOADER_H__