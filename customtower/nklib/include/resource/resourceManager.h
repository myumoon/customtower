//=============================================================================
/*!	@file	resourcemanager.h

	@brief	リソース管理クラス

	@author	井手 竜之介
	@date	2011/11/18
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __RESOUREMANAGER_H__
#define __RESOUREMANAGER_H__

//-------------------------------インクルード-------------------------------
#include <string>
#include <vector>
#include <map>
#include "./texture.h"
#include "./material.h"
#include "./vertex.h"
#include "./face.h"
#include "../file/xfile.h"
#include "../file/toyFile.h"
#include "../file/mqoFile.h"
//#include "../file/csv.h"

namespace nk {
namespace resource {

//=============================================================================
/*!
								リソース管理クラス
*/
//=============================================================================
class ResourceManager {
private:
	//-----------------------型定義--------------------------
	typedef std::map<std::string, Vertex>		VertexMap;		//!< 頂点と名前
	typedef std::map<std::string, Face>			FaceMap;		//!< 面と名前
	typedef std::map<std::string, Material>		MaterialMap;	//!< マテリアルと名前
	typedef std::vector<const Texture*>			TextureAry;		//!< テクスチャ配列
	typedef std::vector<const XFile*>			XFileAry;		//!< Xファイル配列
	typedef std::vector<const ToyFile*>			ToyFileAry;		//!< ToyStudioファイル配列
	typedef std::vector<const MqoFile*>			MqoFileAry;		//!< mqoファイル配列
	//typedef std::vector<const Csv::DataTable*>	CsvAry;			//!< csv
public:

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//! ファイルの一括ロード(txt形式)
	void			LoadAllFile( std::string loadPath );

	//! ファイルのロード(ファイルごと)
	void			LoadFile( std::string loadFilePath );

	//! テクスチャ追加
	void			Register( Texture* tex );
	
	//! 頂点を取得
	//Vertex			GetVertex(std::string name);

	//! 面を取得
	//Face			GetFace(std::string name);

	//! マテリアルを取得
	//Material		GetMaterial(std::string name);

	//! テクスチャを取得
	const Texture*	GetTexture(std::string name);

	//! Xファイルを取得
	const XFile*	GetXFile(std::string name);

	//! ToyFileを取得
	const ToyFile*	GetToyFile(std::string name);

	//! mqoファイルを習得
	const MqoFile*	GetMqoFile(std::string name);

	//! csvファイルを取得
	//const Csv*		GetCsv( std::string name );
	
private:
	//----------------------メンバ変数-----------------------
	VertexMap		m_vertexAry;	//!< 頂点管理配列
	FaceMap			m_faceAry;		//!< 面管理配列
	MaterialMap		m_materialAry;	//!< マテリアル管理配列
	TextureAry		m_textureAry;	//!< テクスチャ管理配列
	XFileAry		m_xfileAry;		//!< Xファイル管理配列
	ToyFileAry		m_toyfileAry;	//!< ToyStudio管理配列
	MqoFileAry		m_mqofileAry;	//!< mqoファイル管理配列
	//CsvAry			m_csvAry;		//!< csv

	

	//-----------------------メソッド------------------------
	//! テクスチャを開放
	void	_DeleteTexture();

	//! Xファイルを解放
	void	_DeleteXFile();

	//! ToyStudioファイルを開放
	void	_DeleteToyFile();

	//! mqoファイルを開放
	void	_DeleteMqoFile();

public:
	//-------------コンストラクタ・デストラクタ--------------
	 ResourceManager();
	~ResourceManager();
};


}	// namespace resource
}	// namespace nk







#endif  // __RESOUREMANAGER_H__