//=============================================================================
/*!	@file	mqoModel.h

	@brief	mqoモデルクラス

	@author	井手 竜之介
	@date	2012/02/21
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __MQOFILE_H__
#define __MQOFILE_H__


//-------------------------------インクルード-------------------------------
#include <string.h>
#include "../resource/vertex.h"
#include "../resource/material.h"
#include "../resource/face.h"
#include "../graphics/color.h"


namespace nk {
namespace resource {

class ResourceManager;
class LoadMqoFile;

//=============================================================================
/*!
								mqoファイルクラス
*/
//=============================================================================
class MqoFile {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! ファイル名をセット
	void			SetFileName(std::string name);

	//! ファイル名を習得
	std::string		GetFileName() const;

	//! 頂点データの追加
	void			AddVertex(const math::Vector& pos);

	//! 頂点データの習得
	const Vertex&	GetVertex() const;

	//! 面データの追加
	void			AddFace(u32 index, const math::Vector& uv);

	//! 面データの習得
	const Face&		GetFace() const;

	//! 法線データの習得
	const Vertex&	GetNormalVertex() const;

	//! マテリアルのセット
	void			SetMaterial(const Material& material);

	//! マテリアルの習得
	Material		GetMaterial() const;
	
	
private:
	//----------------------メンバ変数-----------------------
	std::string			m_name;		//!< ファイル名
	Vertex				m_vertex;	//!< 頂点データ
	Face				m_face;		//!< 面データ
	Material			m_material;	//!< マテリアル
	Vertex				m_normal;	//!< 法線データ
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			 MqoFile(const LoadMqoFile& file);
			 MqoFile();
	virtual ~MqoFile();
};


//=============================================================================
/*!
								mqoロードクラス
*/
//=============================================================================
class LoadMqoFile {
public:
	friend class MqoFile;
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	static void	SetResourceManager(ResourceManager* mng) { m_resourceMng = mng; }
	
	
private:
	//----------------------メンバ変数-----------------------
	static	resource::ResourceManager*	m_resourceMng;	//!< リソース管理
	Vertex								m_vertex;		//!< 頂点データ
	Material							m_material;		//!< マテリアル
	Face								m_face;			//!< 面データ
	std::string							m_path;			//!< ファイルパス
	Vertex								m_normal;		//!< 法線データ
	
	//-----------------------メソッド------------------------
	 LoadMqoFile() { }	// このコンストラクタは使用不可にする
	

public:
	//-------------コンストラクタ・デストラクタ--------------
	 LoadMqoFile(std::string path);
	~LoadMqoFile();
};


}	// namespace resource
}	// namespace nk


#endif	// __MQOFILE_H__