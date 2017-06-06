//=============================================================================
/*!	@file	toyFile.h

	@brief	Toystudioファイルを読込み・管理する

	@author	井手 竜之介
	@date	2011/12/01
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __TOYFILE_H__
#define __TOYFILE_H__


//-------------------------------インクルード-------------------------------
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "../resource/vertex.h"
#include "../resource/face.h"
#include "../resource/material.h"


namespace nk {

namespace resource {

class	ResourceManager;


//=============================================================================
/*!
								Toystudioロードクラス
*/
//=============================================================================
class LoadToyFile {
private:
	friend	class	ToyFile;

	//-----------------------型定義--------------------------
	enum { STR_BUF_START_IDX = -1 };			// インデックスカウント開始時の値

	struct _Property {
		std::string					attribute;	// 属性
		std::string					value;		// 値
	};
	
	struct _Tag {
		std::string					tagName;	// タグ名
		std::vector<_Property>		pro;		// プロパティ
		std::string					value;		// タグの中身の文字
		bool						close;		// 閉じられているか
		std::vector<_Tag*>			tree;		// ツリー構造
		_Tag*						prev;		// このタグを所持しているタグへのポインタ

		/* プロパティの中身を取得 */
		std::string GetPropertyValue(std::string attribute)
		{
			for(u32 i = 0; i < pro.size(); ++i) {
				if( pro[i].attribute == attribute ) {
					return pro[i].value;
				}
			}
			return std::string("");
		}

		/* ツリーから指定されたタグを取得(最初に見つかったやつ) */
		_Tag* GetTagFromTree(std::string tagName)
		{
			_Tag*		retTag	= NULL;
			u32	size	= tree.size();
			for(u32 i = 0; i < size; ++i) {
				if( tree[i]->tagName == tagName ) {
					retTag = tree[i];
					break;
				}
			}
			return retTag;
		}
	};

public:

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//! ロード
	void		Load( std::string path );
	
	
private:
	//----------------------メンバ変数-----------------------
	_Tag*			m_controller;	// 現在捜査中のタグ
	_Tag*			m_tagTree;		// タグツリー
	FILE*			m_fp;			// ファイルポインタ
	bool			m_loop;			// ループ制御フラグ
	std::string		m_filePath;		// ファイルパス
	
	
	//-----------------------メソッド------------------------
	
	// 次のタグを取得
	_Tag*		_GetNextTag();

	// 有効なタグかどうかをチェック
	bool		_IsEnableTag( const struct _Tag* tag );

	// タグを全削除
	void		_DeleteAllTag( _Tag* tag );

	// 派生先の指定タグを取得
	_Tag*		_GetTag( _Tag* tag, std::string  name );

public:
	//-------------コンストラクタ・デストラクタ--------------
	 LoadToyFile();
	 LoadToyFile( std::string path );			//! ロード
	~LoadToyFile();
};



//=============================================================================
/*!
								Toystudioファイル管理クラス
*/
//=============================================================================
class ToyFile {
public:

public:
	//-----------------------型定義--------------------------

	/* メッシュ */
	struct _Mesh {
		std::string				name;		// メッシュ名
		resource::Vertex		vertex;		// 頂点
		resource::Face			face;		// 面構成
		resource::Vertex		normal;		// 法線
		std::vector<_Mesh*>		mesh;		// 派生しているメッシュ
		_Mesh*					prev;		// 派生元のメッシュ
	};

	/* 姿勢 */
	enum { LINEAR, SPLINE, STEP, STEPNEXT };
	typedef u32	SLOPE_TYPE;				// 傾きタイプ
	struct _Attitude {
		s32						frame;				// フレーム
		f32						trans;				// 移動量・回転量
		bool					splitFlag;			// 分割フラグ
		SLOPE_TYPE				slopeTypeFront;		// 傾きの種類(前)
		SLOPE_TYPE				slopeTypeRear;		// 傾きの種類(後)
		math::Vector			slopeHandleFront;	// 傾きハンドル(前)
		math::Vector			slopeHandleRear;	// 傾きハンドル(後)
	};

	/* アニメーション変化 */
	struct _Transformation {
		s32						keyNum;		// キーの数
		std::vector<_Attitude>	attitude;	// 姿勢
	};

	/* アニメーションアイテム */
	struct _AnimationItem {
		enum { RotateX, RotateY, RotateZ, TranslateX, TranslateY, TranslateZ, ITEM_TYPE_MAX };

		std::string						name;					// 名前
		std::vector<_Transformation>	transform;				// 変換
	};

	/* アニメーション */
	struct _Animation {
		std::string						name;					// アニメーション名
		s32								fps;					// フレームレート
		s32								firstFrame;				// 最初のフレーム
		s32								lastFrame;				// 最後のフレーム
		std::vector<_AnimationItem>		animationItem;			// アニメーションアイテム
		
		const _AnimationItem* GetAnimationItem(std::string name) const
		{
			for(u32 i = 0; i < animationItem.size(); ++i) {
				if( animationItem[i].name == name ) {
					return &(animationItem[i]);
				}
			}
			return NULL;
		}
	};

	/* モデル */
	struct _Model {
		Material				material;	// マテリアル
		_Mesh*					rootMesh;	// メッシュの先頭
		//std::vector<_Animation>	anim;		// アニメーション
	};
	

public:
	//----------------------静的メンバ-----------------------

	
	
	//-----------------------メソッド------------------------

	//! ロードしたファイルを格納
	void				operator =(LoadToyFile& file);
	void				SetFile(LoadToyFile& file);
	
	//! ファイル名を取得
	std::string			GetName() const;

	//! メッシュツリーを取得
	_Mesh*				GetRootMesh() const;

	//! マテリアルを取得
	Material			GetMaterial() const;

	//! アニメーションを取得
	const _Animation*	GetAnimation(std::string animName) const;


	//! リソース管理クラスを登録
	static void			SetResourceManager(ResourceManager* mng);
	
private:
	//----------------------静的メンバ-----------------------
	static ResourceManager*	m_resourceMng;	//!< リソース管理


	//----------------------メンバ変数-----------------------
	_Model					m_model;		//!< モデル
	std::vector<_Animation>	m_animAry;		//!< アニメーション配列
	std::string				m_filePath;		//!< ファイルパス


	_Mesh*					m_ctrlMesh;		//!< 操作中のメッシュ
	
	
	//-----------------------メソッド------------------------

	//! メッシュの全削除
	void	_DeleteAllMesh(_Mesh* mesh);

	//! メッシュツリーの作成
	void	_CreateMeshTree(LoadToyFile& file, LoadToyFile::_Tag* tag);

	//! タグからメッシュを生成
	_Mesh*	_CreateMeshFromTag(LoadToyFile::_Tag* tag);

	//! タグからアニメーション配列を作成
	void	_CreateAnimation(LoadToyFile::_Tag* tag);

	//! Itemsタグから_Transformationを作成
	_Transformation _CreateTransformation(LoadToyFile::_Tag* itemTag);

public:
	//-------------コンストラクタ・デストラクタ--------------
			 ToyFile();
			 ToyFile(LoadToyFile& file);		//! 生成したファイルを格納
	virtual ~ToyFile();
};





}	// namespace resource
}	// namespace nk



#endif  // __TOYFILE_H__