//=============================================================================
/*!	\file	renderManager.h

	\brief	描画管理クラス

	\author	井手 竜之介
	\date	2011/11/17
	\todo	なし
	\bug	なし
*/
//=============================================================================


#ifndef __RENDERMANAGER_H__
#define __RENDERMANAGER_H__


//-------------------------------インクルード-------------------------------
#include <list>
#include "./drawpacket.h"
#include "../shader/shader.h"



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
class DrawManager {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 描画オブジェクトを追加
	void	Add( const DrawPacket& packet );

	//! 描画前処理を追加(シャドウマップ生成など)
	//void	AddDrawTextureList(const DrawPacket& pacet);

	//! 描画
	void	Draw( Main* mainclass );

	//! シェーダーをロード
	void	LoadShader( Shader* shader, std::string file, std::string name );

	// シェーダーを削除
	void	DeleteShader();

private:

	//! オブジェクト別の描画
	void	Draw( Main* mainclass, const DrawPacket& packet );


private:
	//----------------------メンバ変数-----------------------
	std::list<DrawPacket>		m_drawPacketList;		//!< 描画パケットリスト
	//std::list<DrawPacket>		m_drawTextureList;		//!< テクスチャ描画リスト
	ShaderManager*				m_shaderMng;			//!< シェーダー管理
	Extension*					m_extension;			//!< 拡張機能
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 DrawManager();
	~DrawManager();
};



}	// namespace graphics
}	// namespace nk



#endif  // __RENDERMANAGER_H__