//=============================================================================
/*!	@file	resourcemanager.h

	@brief	リソース管理クラス

	@author	井手 竜之介
	@date	2011/11/18
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include "../../include/resource/resourceManager.h"
#include "../../include/general.h"


namespace nk {
namespace resource {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
ResourceManager::ResourceManager()
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	なし
*/
//===========================================================================
ResourceManager::~ResourceManager()
{
	_DeleteTexture();
	_DeleteXFile();
	_DeleteToyFile();
	_DeleteMqoFile();
}


//===========================================================================
/*!	@brief	ファイルの一括ロード
	@param	一括ロードを行うファイル名(txt)
	@return	なし
*/
//===========================================================================
void ResourceManager::LoadAllFile(std::string loadpath)
{
	std::ifstream ifs(loadpath.c_str());

	ASSERT( ifs.fail() == false, "file list open error." );
	if( ifs.fail() ) {
		return;
	}

	while( !ifs.eof() ) {
		std::string line;
		ifs >> line;
		PRINTF( "%s\n", line.c_str() );

		/* テクスチャ読み込み */
		if( strstr( line.c_str(), ".png" ) || 
			strstr( line.c_str(), ".jpg" ) ||
			strstr( line.c_str(), ".jpeg") ||
			strstr( line.c_str(), ".bmp" ) ) {
			

			Texture* tex = CreateTexture( line.c_str() );

			tex->SetTexName( line.c_str() );

			m_textureAry.push_back( tex );
		}

		/* モデル読み込み */
		else if( strstr(line.c_str(), ".mqo") ) {
			MqoFile* mqo = new MqoFile( LoadMqoFile(line) );
			m_mqofileAry.push_back( mqo );
		}

		/* ToyStudioで制作したアニメーションの読み込み */
		else if( strstr(line.c_str(), ".toy") ) {
			ToyFile* toy = new ToyFile(LoadToyFile(line.c_str()));
			m_toyfileAry.push_back(toy);
		}

		/* Xファイルの読込み */
		else if( strstr(line.c_str(), ".x") ) {
			m_xfileAry.push_back(CreateXFile(line.c_str()));
		}

		else if( strstr(line.c_str(), ".cgfx") ) {
			ASSERT( false, "cgfx" );
		}

		/* csv */
		else if( strstr(line.c_str(), ".csv") ) {
			//#error
		}
		
	}

}



//===========================================================================
/*!	@brief	ファイルのロード(ファイルごと)
	@param	loadFilePath	ファイルパス
	@return	なし
*/
//===========================================================================
void ResourceManager::LoadFile( std::string loadFilePath )
{
	/* テクスチャ読み込み */
	if( strstr( loadFilePath.c_str(), ".png" ) || 
		strstr( loadFilePath.c_str(), ".jpg" ) ||
		strstr( loadFilePath.c_str(), ".bmp" ) ) {

		Texture* tex = CreateTexture( loadFilePath.c_str() );
		tex->SetTexName( loadFilePath );
		m_textureAry.push_back( tex );
	}

	/* モデル読み込み */
	if( strstr( loadFilePath.c_str(), ".mqo" ) ) {
		MqoFile* mqo = new MqoFile( LoadMqoFile( loadFilePath ) );
		m_mqofileAry.push_back( mqo );
	}

	/* ToyStudioで制作したアニメーションの読み込み */
	if( strstr( loadFilePath.c_str(), ".toy" ) ) {
		ToyFile* toy = new ToyFile( LoadToyFile( loadFilePath.c_str() ) );
		m_toyfileAry.push_back( toy );
	}

	/* Xファイルの読込み */
	if( strstr( loadFilePath.c_str(), ".x" ) ) {
		m_xfileAry.push_back( CreateXFile( loadFilePath.c_str() ) );
	}

	/* シェーダー */
	if( strstr( loadFilePath.c_str(), ".cgfx" ) ) {
	}

}


//===========================================================================
/*!	@brief	テクスチャの追加
	@param	----
	@return	----
*/
//===========================================================================
void ResourceManager::Register( Texture* tex )
{
	m_textureAry.push_back( tex );
}




//===========================================================================
/*!	@brief	頂点を取得
	@param	頂点の名前
	@return	頂点クラス
*/
//===========================================================================
//Vertex ResourceManager::GetVertex(std::string name)
//{
//	return m_vertexAry[name];
	//typedef std::map<std::string, Vertex> Map;
	//
	//Map::iterator itr = m_vertexAry.begin();
	//Map::iterator end = m_vertexAry.end();

	//for( ; itr != end; ++itr) {
	//	if( (*itr).first == name ) {
	//		return (*itr).second;
	//	}
	//}
	//
	//return Vertex();
//}


//===========================================================================
/*!	@brief	面を取得
	@param	面の名前
	@return	面クラス
*/
//===========================================================================
//Face ResourceManager::GetFace(std::string name)
//{
//	return m_faceAry[name];
//}


//===========================================================================
/*!	@brief	マテリアルを取得
	@param	マテリアルの名前
	@return	マテリアルクラス
*/
//===========================================================================
//Material ResourceManager::GetMaterial(std::string name)
//{
//	return m_materialAry[name];
//}


//===========================================================================
/*!	@brief	テクスチャを取得
	@param	テクスチャの名前
	@return	テクスチャクラス	null:見つからなかった場合
*/
//===========================================================================
const Texture* ResourceManager::GetTexture(std::string name)
{
	TextureAry::iterator itr = m_textureAry.begin();
	TextureAry::iterator end = m_textureAry.end();
	for( ; itr != end; ++itr) {
		if( (*itr)->GetTexName() == name ) {
			return *itr;
		}
	}

	return NULL;		// 名前が見つからなかった場合
}


//===========================================================================
/*!	@brief	Xファイルを取得
	@param	name	: 取得するXファイルの名前
	@return	Xファイル
*/
//===========================================================================
const XFile* ResourceManager::GetXFile(std::string name)
{
	XFileAry::iterator itr = m_xfileAry.begin();
	XFileAry::iterator end = m_xfileAry.end();
	for( ; itr != end; ++itr) {
		if( (*itr)->GetName() == name ) {
			return *itr;
		}
	}

	return NULL;		// 名前が見つからなかった場合
}


//===========================================================================
/*!	@brief	ToyFileを取得
	@param	name	: 取得するToyFileの名前
	@return	Xファイル
*/
//===========================================================================
const ToyFile* ResourceManager::GetToyFile(std::string name)
{
	ToyFileAry::iterator itr = m_toyfileAry.begin();
	ToyFileAry::iterator end = m_toyfileAry.end();

	for( ; itr != end; ++itr) {
		if( (*itr)->GetName() == name ) {
			return *itr;
		}
	}

	return NULL;		// 名前が見つからなかった場合
}


//===========================================================================
/*!	@brief	mqoファイルを習得
	@param	name	: ファイル名
	@return	mqoファイル
*/
//===========================================================================
const MqoFile* ResourceManager::GetMqoFile(std::string name)
{
	MqoFileAry::iterator itr = m_mqofileAry.begin();
	MqoFileAry::iterator end = m_mqofileAry.end();

	for( ; itr != end; ++itr) {
		if( (*itr)->GetFileName() == name ) {
			return *itr;
		}
	}

	return NULL;		// 名前が見つからなかった場合
}

//===========================================================================
/*!	@brief	テクスチャを開放
	@param	なし
	@return	なし
*/
//===========================================================================
void ResourceManager::_DeleteTexture()
{
	TextureAry::iterator itr = m_textureAry.begin();
	TextureAry::iterator end = m_textureAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}
}


//===========================================================================
/*!	@brief	Xファイルを解放
	@param	なし
	@return	なし
*/
//===========================================================================
void ResourceManager::_DeleteXFile()
{
	XFileAry::iterator itr = m_xfileAry.begin();
	XFileAry::iterator end = m_xfileAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}

}


//===========================================================================
/*!	@brief	ToyStudioファイルを開放
	@param	なし
	@return	なし
*/
//===========================================================================
void ResourceManager::_DeleteToyFile()
{
	ToyFileAry::iterator itr = m_toyfileAry.begin();
	ToyFileAry::iterator end = m_toyfileAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}
}


//===========================================================================
/*!	@brief	ToyStudioファイルを開放
	@param	なし
	@return	なし
*/
//===========================================================================
void ResourceManager::_DeleteMqoFile()
{
	MqoFileAry::iterator itr = m_mqofileAry.begin();
	MqoFileAry::iterator end = m_mqofileAry.end();

	for( ; itr != end; ++itr) {
		SafeDelete(*itr);
	}
}


}	// namespace resource
}	// namespace nk