//=============================================================================
/*!	@file	xfile.h

	@brief	Xファイルを扱う

	@author	井手 竜之介
	@date	2011/11/23
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __XFILE_H__
#define __XFILE_H__

//-------------------------------インクルード-------------------------------
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../math/matrix.h"
#include "../resource/vertex.h"
#include "../resource/face.h"
#include "../resource/material.h"


namespace nk {
namespace resource {

//---------------------------------前方宣言---------------------------------
class ResourceManager;

//=============================================================================
/*!
								Xファイルクラス
*/
//=============================================================================
class XFile {
private:
public:
	//-----------------------型定義--------------------------
	struct _ObjAnimation;
	typedef std::vector<_ObjAnimation> ObjAnimAry;	// オブジェクトアニメーション配列型
	
	// モデルオブジェクト
	struct _ModelObject {
		std::string			name;			// オブジェクト名
		resource::Vertex	vertex;			// 頂点
		resource::Face		face;			// 面
		resource::Vertex	normalVertex;	// 面法線
		resource::Face		normalFace;		// 面法線のインデックス
		resource::Material	material;		// マテリアル
	};

	// アニメーション
	struct _Animation {
		std::string					objName;	// 対応するオブジェクト名
		std::vector<math::Matrix44>	matrix;		// アニメーション行列
	};

	// モデルアニメーション
	struct _ObjAnimation {
		_ModelObject	object;		// オブジェクト
		_Animation		animation;	// アニメーション
	};
	
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! オブジェクトアニメーションを追加
	void		AddObjectAnimation( const _ObjAnimation& obj );

	//! アニメーションを追加
	void		AddAnimation( const _Animation& anim, std::string name );

	//! ファイル名を取得
	std::string	GetName() const;

	//! ループ回数を取得
	u32		GetSize() const;

	//! オブジェクト構造体を取得
	const _ModelObject&	GetModelObject( u32 index ) const;

	//! アニメーション構造体を取得
	const _Animation&	GetAnimation( u32 index ) const;


	//! リソース管理クラスを登録
	static void	SetResourceManager( ResourceManager* mng );
	
	// 生成するときはメンバを公開する
	friend XFile* CreateXFile( std::string path );
	
private:
	//----------------------メンバ変数-----------------------
	ObjAnimAry		m_objAnimAry;	//!< オブジェクトアニメーション配列
	std::string		m_name;			//!< ファイル名
	
	static ResourceManager*	m_resourceMng;	//!< リソース管理
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 XFile();
	~XFile();
};


//! Xファイルをロード
XFile* CreateXFile( std::string path );

//! 文字列から頂点を取得
math::Vector GetVertexFromString();

}	// namespace resource
}	// namespace nk



#endif  // __XFILE_H__