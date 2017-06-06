//=============================================================================
/*!	@file	xfile.h

	@brief	Xファイルを扱う

	@author	井手 竜之介
	@date	2011/11/23
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/file/xfile.h"
#include "../../include/utility/stringfunction.h"
#include "general.h"
#include "../../include/resource/resourcemanager.h"


namespace nk {
namespace resource {

//------------------------------静的メンバ定義------------------------------
nk::resource::ResourceManager*		XFile::m_resourceMng	= NULL;		// リソース管理クラス


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
XFile::XFile()
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
XFile::~XFile()
{
	
}



//===========================================================================
/*!	@brief	ファイル名を取得
	@param	なし
	@return	ファイル名
*/
//===========================================================================
std::string XFile::GetName() const
{
	return m_name;
}


//===========================================================================
/*!	@brief	追加
	@param	obj	: 追加するオブジェクトアニメーション
	@return	なし
*/
//===========================================================================
void XFile::AddObjectAnimation( const nk::resource::XFile::_ObjAnimation& obj )
{
	m_objAnimAry.push_back( obj );
}


//===========================================================================
/*!	@brief	アニメーションを追加
	@param	anim	: 追加するアニメーション
	@param	name	: オブジェクト名
	@return	なし
*/
//===========================================================================
void XFile::AddAnimation( const _Animation& anim, std::string name )
{
	ObjAnimAry::iterator itr = m_objAnimAry.begin();
	ObjAnimAry::iterator end = m_objAnimAry.end();

	for( ; itr != end; ++itr ) {
		if( (*itr).object.name == name ) {
			(*itr).animation = anim;
			break;
		}
	}

}


//===========================================================================
/*!	@brief	ループ回数を取得
	@param	なし
	@return	ループ回数
*/
//===========================================================================
u32 XFile::GetSize() const 
{
	return m_objAnimAry.size();
}


//===========================================================================
/*!	@brief	オブジェクト構造体を取得
	@param	index	: 何番目のオブジェクトか
	@return	オブジェクトへの参照(変更不可)
*/
//===========================================================================
const XFile::_ModelObject& XFile::GetModelObject( u32 index ) const
{
	ObjAnimAry::const_iterator itr = m_objAnimAry.begin();
	ObjAnimAry::const_iterator end = m_objAnimAry.end();

	for(u32 i = 0; i < index; i++ ) {
		if( itr == end ) {
			break;
		}
		++itr;
	}

	return (*itr).object;
}


//===========================================================================
/*!	@brief	アニメーション構造体を取得
	@param	index	: 何番目のアニメーションか
	@return	アニメーションへの参照(変更不可)
*/
//===========================================================================
const XFile::_Animation& XFile::GetAnimation( u32 index ) const
{
	ObjAnimAry::const_iterator itr = m_objAnimAry.begin();
	ObjAnimAry::const_iterator end = m_objAnimAry.end();

	for(u32 i = 0; i < index; i++ ) {
		if( itr == end ) {
			break;
		}
		++itr;
	}

	return (*itr).animation;
}


//===========================================================================
/*!	@brief	リソース管理を登録
	@param	mng	: リソース管理クラス
	@return	なし
*/
//===========================================================================
void XFile::SetResourceManager( nk::resource::ResourceManager* mng )
{
	m_resourceMng = mng;
}


//===========================================================================
/*!	@brief	Xファイルをロード
	@param	path	: ロードパス
	@return	生成したXファイル	NULL:ファイルが無いor作成失敗
*/
//===========================================================================
XFile* CreateXFile( std::string path )
{
	std::ifstream ifs( path.c_str() );

	// ファイルがない場合はNULLを返す
	if( ifs.fail() ) {
		return NULL;
	}

	// データ入力用のインスタンスを生成
	XFile* xfile = new XFile();
	xfile->m_name = path;		// 名前をセット
	char line[256];

	// 現在どの処理を行なっているか
	enum {
		FLAG_NONE,				// フラグなし
		FLAG_VERTEX,			// 頂点座標
		FLAG_FACE,				// 面
		FLAG_NORMAL_VERTEX,		// 法線
		FLAG_NORMAL_FACE,		// 法線の構成
		FLAG_MATERIAL,			// マテリアル
		FLAG_TEXTURE_COORDS,	// UV座標
		FLAG_ANIMATION			// アニメーション
	};
	u32 lineFlag = FLAG_NONE;	// 現在行なっている処理

	XFile::_ObjAnimation*	objAnim		= NULL;

	bool	isFirstEntry	= true;		// 最初に入ったかどうか
	bool	isObjLine		= false;	// オブジェクトの行に入ったかどうか
	s32		brackets		= 0;		// 括弧の数

	// ファイルの内容を調べる
	while( !ifs.eof() ) {
		memset(line, '\0', sizeof(line)); 
		ifs.getline(line, sizeof(line));

		/* 括弧を数える */
		if( strstr(line, "{") ) {
			++brackets;
		}
		if( strstr(line, "}") ) {
			--brackets;
		}


		/* アニメーション */
		if( lineFlag == FLAG_ANIMATION ) {
			if( strstr(line, "AnimationKey") ) {
			}
		}

		/* アニメーションの登録 */
		if( strstr(line, "AnimationSet {") && !strstr(line, "template") ) {
			lineFlag = FLAG_ANIMATION;
		}

		/* オブジェクトの格納 */
		if( isObjLine && (brackets == 0) ) {
			isObjLine = false;
			xfile->AddObjectAnimation( *objAnim );
			SafeDelete( objAnim );
		}


		/* UV座標 */
		if( lineFlag == FLAG_TEXTURE_COORDS ) {
			if( strstr(line, "MeshTextureCoords {") ) {
				ifs.getline( line, sizeof(line) );	// 1行進める
				isFirstEntry = false;
			}
			else if( !isFirstEntry ) {
				if( !strstr(line, "}") ) {
					char* tp;
					math::Vector uv;
					tp = strtok(line, " \t,;");
					uv.x = static_cast<f32>( atof(tp) );
					tp = strtok(NULL, " \t,;");
					uv.y = static_cast<f32>( atof(tp) );
					objAnim->object.face.AddUV( uv );
				} else {
					isFirstEntry = true;
					lineFlag = FLAG_NONE;
				}
			}
			
		}

		/* テクスチャ */
		if( lineFlag == FLAG_MATERIAL ) {
			if( strstr(line, "TextureFilename {") ) {
				ifs.getline(line, sizeof(line));	// 1行進める
				std::string str = FindStr( line, "\"", "\";" );
				objAnim->object.material.SetTexture( XFile::m_resourceMng->GetTexture(str) );
				lineFlag = FLAG_TEXTURE_COORDS;
			}
		}

		/* 頂点法線の面構成 */
		if( lineFlag == FLAG_NORMAL_FACE ) {
			if( isFirstEntry ) {
				isFirstEntry = false;
			}
			else if( strstr(line, "}") ) {
				lineFlag = FLAG_MATERIAL;
				isFirstEntry = true;
			}
			else {
				char* tp;
				strtok(line, "\t,;");				// 最初の文字は捨てる
				for(s32 i = 0; i < 3; i++) {
					tp = strtok(NULL, "\t,;");
					objAnim->object.normalFace.AddFace( atoi(tp) );
				}
			}
		}

		/* 頂点法線情報 */
		if( lineFlag == FLAG_NORMAL_VERTEX ) {
			if( isFirstEntry ) {
				isFirstEntry = false;
				ifs.getline(line, sizeof(line));	// 1行進める
			}
			else if( !strcmp(line, "") ) {
				lineFlag = FLAG_NORMAL_FACE;
				isFirstEntry = true;
			}
			else {
				objAnim->object.normalVertex.Add( GetVectorFromString(line, "\t,;") );
			}
		}


		/* 面情報 */
		if( lineFlag == FLAG_FACE ) {
			if( isFirstEntry ) {
				isFirstEntry = false;
			}
			else if( !strcmp(line, "") ) {
				lineFlag = FLAG_NORMAL_VERTEX;
				isFirstEntry = true;
			}
			else {
				char* tp;
				strtok(line, "\t,;");				// 最初の文字は捨てる
				for(s32 i = 0; i < 3; i++) {
					tp = strtok(NULL, "\t,;");
					objAnim->object.face.AddFace( atoi(tp) );
				}
			}
		}

		/* 頂点処理 */
		if( lineFlag == FLAG_VERTEX ) {
			if( !strcmp(line, "") ) {
				lineFlag = FLAG_FACE;
				isFirstEntry = true;
			} else {
				objAnim->object.vertex.Add(GetVectorFromString( line, "\t,;") );
			}
		}
		
		/* オブジェクトの行に入る */
		if( strstr(line, "Frame ") && !strstr(line, "template") ) {
			lineFlag			= FLAG_VERTEX;	
			isFirstEntry		= false;
			isObjLine			= true;
			std::string objName = FindStr(line, "Frame ", " {");
			
			// 念のために削除
			SafeDelete(objAnim);

			objAnim					= new XFile::_ObjAnimation;	// 格納するオブジェクトを生成
			objAnim->object.name	= objName;					// オブジェクト名をセット
			ifs.getline(line, sizeof(line));// 2行進める
			ifs.getline(line, sizeof(line));
			++brackets;						// 進めた時に}をカウントしてないのでカウントする
		}

	}


	return xfile;
}

}	// namespace resource
}	// namespace nk
