//=============================================================================
/*!	@file	drawmanager.h

	@brief	描画管理クラス

	@author	井手 竜之介
	@date	2011/11/17
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __DRAWMANAGER_H__
#define __DRAWMANAGER_H__


//-------------------------------インクルード-------------------------------
#include <list>
#include "./drawpacket.h"
#include "../shader/shader.h"
#include "../resource/renderableTexture.h"



namespace nk {

class Main;

namespace graphics {

//=============================================================================
/*!
								描画拡張機能
*/
//=============================================================================
class Extension {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	virtual void		Proc();		//!< 更新処理
	
private:
	//----------------------メンバ変数-----------------------
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			 Extension();
	virtual ~Extension();
};


//=============================================================================
/*!
								描画管理クラス
*/
//=============================================================================
class RenderManager {
private:
#if 0
	struct ScreenTexId {
		s32				screenId;
		RenderTexId		texId;
	};
	typedef std::vector<ScreenTexId>	VecScreenId;

#endif

public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	//! 初期化
	bool	Initialize( void );

	//! 描画オブジェクトを追加
// 	void	Add( const DrawPacket& packet );
	void	Add( const DrawPacket* packet );

	//! 描画前処理を追加(シャドウマップ生成など)
	//void	AddDrawTextureList(const DrawPacket& pacet);

	//! 描画
	void	Draw( Main* mainclass );

	//! シェーダーをロード
	void	LoadShader( Shader* shader, std::string file, std::string name );

	//!	シェーダーを削除
	void	DeleteShader();

#if 0
	//! 描画スクリーン生成
	void	CreateRenderScreen( Main* mainclass, s32 screenId );

	//! スクリーンIDからテクスチャIDを取得
	RenderTexId GetTextureId( s32 screenId );

#endif
private:

	//! オブジェクト別の描画
	void	Draw( Main* mainclass, const DrawPacket* packet );


private:
	//----------------------メンバ変数-----------------------
	std::list<const DrawPacket*>		m_drawPacketList;		//!< 描画パケットリスト
	//std::list<DrawPacket>		m_drawTextureList;		//!< テクスチャ描画リスト
	ShaderManager*				m_shaderMng;			//!< シェーダー管理
	Extension*					m_extension;			//!< 拡張機能
	const resource::Texture*	m_prevUseTexture;		//!< 前回の描画で使用したテクスチャ
	
#if 0
	VecScreenId					m_vecScreenId;			//!< スクリーンID

#endif
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 RenderManager();
	~RenderManager();
};



}	// namespace graphics
}	// namespace nk



#endif  // __DRAWMANAGER_H__