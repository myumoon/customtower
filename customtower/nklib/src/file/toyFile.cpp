//=============================================================================
/*!	@file	toyFile.h

	@brief	Toystudioファイルを読込み・管理する

	@author	井手 竜之介
	@date	2011/12/01
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/file/toyFile.h"
#include "../../include/utility/stringfunction.h"
#include "general.h"
#include "../../include/resource/resourcemanager.h"

#pragma warning (disable:4996)

namespace nk {
namespace resource {

//------------------------------静的メンバ定義------------------------------
nk::resource::ResourceManager*		ToyFile::m_resourceMng	= NULL;		// リソース管理クラス


//===========================================================================
/*!	@brief	リソース管理を登録
	@param	mng	: リソース管理クラス
	@return	なし
*/
//===========================================================================
void ToyFile::SetResourceManager( nk::resource::ResourceManager* mng )
{
	m_resourceMng = mng;
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
ToyFile::ToyFile()
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
ToyFile::~ToyFile()
{
	_DeleteAllMesh( m_model.rootMesh );
}



//===========================================================================
/*!	@brief	コンストラクタ(ロードしたToystudioファイルを格納
	@param	
*/
//===========================================================================)
ToyFile::ToyFile( LoadToyFile &file )
{
	SetFile( file );
}


//===========================================================================
/*!	@brief	toystudioファイルをセット
	@param	file	: セットするtoystudioファイル
	@return	なし
*/
//===========================================================================
void ToyFile::operator =( nk::resource::LoadToyFile &file )
{
	SetFile( file );
}


//===========================================================================
/*!	@brief	ファイル名を取得
	@param	なし
	@return	ファイル名
*/
//===========================================================================
std::string ToyFile::GetName() const
{
	return m_filePath;
}


//===========================================================================
/*!	@brief	toystudioファイルをセット
	@param	file	: toystudioファイル
	@return	なし
*/
//===========================================================================
void ToyFile::SetFile(nk::resource::LoadToyFile &file)
{
	LoadToyFile::_Tag*	root	= file._GetTag( file.m_tagTree, "Model" );	// 検索時間短縮の為ルートを設定
	LoadToyFile::_Tag*	texTag	= file._GetTag( root, "Texture" );			// テクスチャタグを取得
	std::string			texName	= texTag->GetPropertyValue("Path");			// テクスチャ名を取得
	std::string			dirPath	= GetDirectoryPath( file.m_filePath );

	
	/* ルートの初期化 */
	m_model.rootMesh		= new _Mesh;
	m_model.rootMesh->prev	= NULL;
	m_model.material.SetTexture( m_resourceMng->GetTexture(dirPath + texName) );
	//m_model.material.SetTexture( m_resourceMng->GetTexture(texName) );
	
	/* ファイルパスの設定 */
	m_filePath = file.m_filePath;

	/* メッシュツリーの作成 */
	m_ctrlMesh = m_model.rootMesh;
	_CreateMeshTree( file, root );

	/* アニメーションの作成 */
	LoadToyFile::_Tag*	animsTag	= file._GetTag( file.m_tagTree, "Anims" );	// アニメーションタグ
	_CreateAnimation( animsTag );
}


//===========================================================================
/*!	@brief	メッシュツリーの作成
	@param	file	: 作成するtoystudioファイル
	@param	tag		: 検索を開始するタグ
	@return	なし
*/
//===========================================================================
void ToyFile::_CreateMeshTree( nk::resource::LoadToyFile &file, LoadToyFile::_Tag *tag )
{
	_Mesh* newMesh = NULL;
	if( tag->tagName == "Mesh" ) {
		newMesh		= _CreateMeshFromTag( tag );	// メッシュを生成
		
		m_ctrlMesh->mesh.push_back( newMesh );		// 追加
		m_ctrlMesh	= newMesh;						// 操作メッシュを生成したやつに変更
	}

	const u32 size = tag->tree.size();
	for( u32 i = 0; i < size; ++i ) {
		_CreateMeshTree( file, tag->tree[i] );
	}

	/*	派生タグを見ていって新しいメッシュが生成されていなかったら
		操作対象を1個戻す	*/
	if( m_ctrlMesh == newMesh ) {
		m_ctrlMesh = m_ctrlMesh->prev;
	}

}


//===========================================================================
/*!	@brief	タグからメッシュを生成
	@param	tag		: タグ
	@return	生成したメッシュ
*/
//===========================================================================
ToyFile::_Mesh* ToyFile::_CreateMeshFromTag( nk::resource::LoadToyFile::_Tag *tag )
{
	_Mesh* newMesh	= new _Mesh;				// メッシュを生成
	newMesh->prev	= m_ctrlMesh;				// 1個前のメッシュを設定

	/* 名前タグを取得してメッシュ名を設定 */
	LoadToyFile::_Tag* nameTag = tag->GetTagFromTree("Name");
	newMesh->name	= FindStr(nameTag->value.c_str(), "<![CDATA[", "]]>");	// メッシュ名を設定


	/* タグを設定 */
	LoadToyFile::_Tag*	vertexTag	= tag->GetTagFromTree("Vertices");
	u32			vertexCount	= atoi(vertexTag->GetPropertyValue("Count").c_str());
	size_t				strBufSize	= vertexTag->value.size();
	char*				strBuf		= NULL;
	

	strBuf	= new char[strBufSize];	// 文字列バッファを作成

	/* 頂点文字列をコピー */
	for(u32 i = 0; i < strBufSize; ++i) {
		strBuf[i] = vertexTag->value.at(i);
	}

	/* 文字列をf32値に変換 */
	math::Vector vertex;								// 頂点を格納する為
	enum INSERT_FLAG { INSERT_X, INSERT_Y, INSERT_Z };	// どこに入れるかのフラグ
	INSERT_FLAG insertFlag = INSERT_X;

	strtok(strBuf, " ");		// とりあえず先頭は切り捨て
	
	for(u32 i = 0; i < vertexCount * 3; ++i) {
		char* token = strtok(NULL, " ,\n");
		if( !token ) {
			break;
		}
		const f32 value = static_cast<f32>(atof(token));
		if( insertFlag == INSERT_X )		{ vertex.x = value; insertFlag = INSERT_Y; }
		else if( insertFlag == INSERT_Y )	{ vertex.y = value; insertFlag = INSERT_Z; }
		else if( insertFlag == INSERT_Z )	{ vertex.z = value; insertFlag = INSERT_X; newMesh->vertex.Add(vertex); }
	}
	
	SafeDelete(strBuf);


	/* 面情報をコピー */
	LoadToyFile::_Tag*	faceTag		= tag->GetTagFromTree("Faces");
	u32			faceCount	= atoi(faceTag->GetPropertyValue("Count").c_str());
	bool				useUVFlag	= (faceTag->GetPropertyValue("UV") == "True");
	strBufSize						= faceTag->value.size();
	strBuf							= new char[strBufSize];

	for(u32 i = 0; i < strBufSize; ++i) {
		strBuf[i] = faceTag->value.at(i);
	}

	strtok(strBuf, " ");		// 先頭は切り捨て
	for(u32 i = 0; i < faceCount; ++i) {
		char* token = NULL;
		strtok(NULL, " ,;\n");	// 面の構成数は飛ばす

		char* idx[3];		// 頂点番号を格納
		idx[0]	= strtok(NULL, " ,;\n");	// 頂点番号1
		idx[1]	= strtok(NULL, " ,;\n");	// 頂点番号2
		idx[2]	= strtok(NULL, " ,;\n");	// 頂点番号3
		newMesh->face.AddFace(atoi(idx[0]));
		newMesh->face.AddFace(atoi(idx[1]));
		newMesh->face.AddFace(atoi(idx[2]));
		
		if( useUVFlag ) {
			char* uv[6] = { 0 };
			for(u32 j = 0; j < ARRAY_SIZE(uv); ++j) {
				uv[j]	= strtok(NULL, " ,;\n");
			}
			math::Vector faceUV0( static_cast<f32>(atof(uv[0])), static_cast<f32>(atof(uv[1])), 0.0f );
			math::Vector faceUV1( static_cast<f32>(atof(uv[2])), static_cast<f32>(atof(uv[3])), 0.0f );
			math::Vector faceUV2( static_cast<f32>(atof(uv[4])), static_cast<f32>(atof(uv[5])), 0.0f );
			newMesh->face.AddUV( faceUV0 );
			newMesh->face.AddUV( faceUV1 );
			newMesh->face.AddUV( faceUV2 );
		}

		{	/*	このスコープ内は処理的に意味がない
				無駄なところを飛ばすためにある処理	*/
			for(s32 _i = 0; _i < 12; ++_i) {
				strtok(NULL, " ,;\n");	// 255の部分は飛ばす
			}

			for(s32 _i = 0; _i < 3; ++_i) {
				strtok(NULL, " ,;\n");	// 1,1,0みたいになってるとこは飛ばす
			}
			strtok(NULL, " ,;\n");		// 最後に0が入ってるから飛ばす
		}
	}


	/* 頂点法線を格納する構造体 */
	typedef std::vector<math::Vector> VertexNormal;	// 頂点番号を含む面法線

	/* 頂点法線の数を設定 */
	std::vector<VertexNormal> vertexNormal(newMesh->vertex.GetSize());

	for(u32 i = 0; i < newMesh->face.GetSize(); i += newMesh->face.GetBundle()) {
		math::Vector v0 = newMesh->vertex.GetVertex(newMesh->face.GetFace(i + 1)) - newMesh->vertex.GetVertex(newMesh->face.GetFace(i));
		math::Vector v1 = newMesh->vertex.GetVertex(newMesh->face.GetFace(i + 2)) - newMesh->vertex.GetVertex(newMesh->face.GetFace(i));
		math::Vector N	= math::CalcCrossProduct(v0, v1);

		vertexNormal[newMesh->face.GetFace(i + 0)].push_back(N);
		vertexNormal[newMesh->face.GetFace(i + 1)].push_back(N);
		vertexNormal[newMesh->face.GetFace(i + 2)].push_back(N);
	}

	for(u32 i = 0; i < newMesh->vertex.GetSize(); ++i) {
		math::Vector sum;
		for(u32 j = 0; j < vertexNormal[i].size(); ++j) {
			sum += vertexNormal[i].at(j);
		}
		sum.Normalize();
		newMesh->normal.Add(sum);
	}



	return newMesh;
}


//===========================================================================
/*!	@brief	アニメーション配列を作成
	@param	tag		: アニメーションの先頭タグ
	@return	なし
*/
//===========================================================================
void ToyFile::_CreateAnimation( nk::resource::LoadToyFile::_Tag *tag )
{
	typedef LoadToyFile::_Tag	_TAG;	// 長いので短縮

	for(u32 i = 0; i < tag->tree.size(); ++i) {
		_Animation	animation;		// アニメーション情報をを格納する構造体
		_TAG*		anim			= tag->tree[i];
		_TAG*		nameTag			= anim->GetTagFromTree("Name");
		_TAG*		fpsTag			= anim->GetTagFromTree("Fps");
		_TAG*		firstFrameTag	= anim->GetTagFromTree("FirstFrame");
		_TAG*		lastFrameTag	= anim->GetTagFromTree("LastFrame");
		_TAG*		objectItems		= anim->GetTagFromTree("ObjectItems");
		nameTag->value += '\0';
		animation.name				= FindStr(nameTag->value.c_str(), "<![CDATA[", "]]>");
		animation.fps				= atoi(fpsTag->value.c_str());
		animation.firstFrame		= atoi(firstFrameTag->value.c_str());
		animation.lastFrame			= atoi(lastFrameTag->value.c_str());

		/* オブジェクトアイテムの読込み */
		for(u32 j = 0; j < objectItems->tree.size(); ++j) {
			_AnimationItem	item;

			_TAG*	object	= objectItems->tree[j];
			std::string temp= FindStr(object->GetTagFromTree("Name")->value.c_str(), "<![CDATA[", "]]>");
			
			for(u32 i = 0; i < temp.size(); ++i) {
				item.name += temp.at(i);
				if( temp.at(i) == '\\' ) {
					item.name.clear();	// バックスラッシュが見つかったら削除
				}
			}


			_TAG*	items	= object->GetTagFromTree("Items");

			/* 変換データの読込み */
			//item.transform.reserve(1);
			//item.transform.reserve(_AnimationItem::ITEM_TYPE_MAX);	// 要素を確保
			for(u32 itemType = 0; itemType < _AnimationItem::ITEM_TYPE_MAX; ++itemType) {
				item.transform.push_back(_CreateTransformation(items->tree[itemType]));
				//item.transform[itemType] = _CreateTransformation(items->tree[itemType]);
			}

			animation.animationItem.push_back(item);	// アニメーションアイテムを追加
		}
		
		m_animAry.push_back(animation);		// アニメーションを追加
	}

}


//===========================================================================
/*!	@brief	Itemsタグから_Transformationを作成
	@param	itemTag		: アイテムタグの先頭
	@return	生成した変換データ
*/
//===========================================================================
ToyFile::_Transformation ToyFile::_CreateTransformation( nk::resource::LoadToyFile::_Tag *itemTag )
{
	enum {
		ATTITUDE_FRAME_NUM,			// 何フレーム目か
		ATTITUDE_TRANSFERS,			// 移動量
		ATTITUDE_SPLIT_FLAG,		// 分割フラグ
		ATTITUDE_SLOPE_TYPE_FRONT,	// 傾きの種類(前)
		ATTITUDE_SLOPE_TYPE_REAR,	// 傾きの種類(後)
		ATTITUDE_SLOPE_HANDLE_FRONT,// 傾きハンドル(前)
		ATTITUDE_SLOPE_HANDLE_REAR,	// 傾きハンドル(後)
		ATTITUDE_MAX				// 
	};

	_Transformation	retTrans;

	itemTag->value += '\0';
	char*			strBuf			= new char[itemTag->value.length()];
	u32		attitudeNum		= ATTITUDE_FRAME_NUM;


	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = '\0';
	}
	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = itemTag->value.at(i);
	}

	retTrans.keyNum		= atoi(strtok(strBuf, "\t ;,\n"));	// キーの数

	while( 1 ) {
		char* tp	= strtok(NULL, "\t ;,\n");
		if( !tp ) {
			break;
		}

		std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();

		switch( attitudeNum ) {
			case ATTITUDE_FRAME_NUM: {
				retTrans.attitude.push_back(_Attitude());
				std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();
				(*attitudeItr).frame	= atoi(tp);
				attitudeNum				= ATTITUDE_TRANSFERS;
				break;
			}
			
			case ATTITUDE_TRANSFERS: {
				(*attitudeItr).trans	= static_cast<f32>(atof(tp));
				attitudeNum				= ATTITUDE_SPLIT_FLAG;
				break;
			}
			
			case ATTITUDE_SPLIT_FLAG: {
				(*attitudeItr).splitFlag	= (atoi(tp) == 1);
				attitudeNum					= ATTITUDE_SLOPE_TYPE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_FRONT: {
				(*attitudeItr).slopeTypeFront	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_TYPE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_REAR: {
				(*attitudeItr).slopeTypeRear	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_FRONT: {
				math::Vector direcFront(-1.0f, static_cast<f32>(atof(tp)), 0.0f);
				(*attitudeItr).slopeHandleFront	= direcFront;
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_REAR: {
				math::Vector direcRear(1.0f, static_cast<f32>(atof(tp)), 0.0f);
				(*attitudeItr).slopeHandleRear	= direcRear;
				attitudeNum						= ATTITUDE_FRAME_NUM;
				break;
			}

			default:
				PRINTF("ここにはこない\n");
				break;
		}
	}

	SafeDeleteArray(strBuf);

	return retTrans;
}

#if 0
//===========================================================================
/*!	@brief	Itemsタグから_Transformationを作成
	@param	itemTag		: アイテムタグの先頭
	@return	生成した変換データ
*/
//===========================================================================
ToyFile::_Transformation ToyFile::_CreateTransformation(nk::resource::LoadToyFile::_Tag *itemTag)
{
	enum {
		ATTITUDE_FRAME_NUM,			// 何フレーム目か
		ATTITUDE_TRANSFERS,			// 移動量
		ATTITUDE_SPLIT_FLAG,		// 分割フラグ
		ATTITUDE_SLOPE_TYPE_FRONT,	// 傾きの種類(前)
		ATTITUDE_SLOPE_TYPE_REAR,	// 傾きの種類(後)
		ATTITUDE_SLOPE_HANDLE_FRONT,// 傾きハンドル(前)
		ATTITUDE_SLOPE_HANDLE_REAR,	// 傾きハンドル(後)
		ATTITUDE_MAX				// 
	};

	_Transformation	retTrans;

	itemTag->value += '\0';
	char*			strBuf			= new char[itemTag->value.length()];
	u32		attitudeNum		= ATTITUDE_FRAME_NUM;


	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = '\0';
	}
	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = itemTag->value.at(i);
	}

	retTrans.keyNum		= atoi(strtok(strBuf, "\t ;,\n"));	// キーの数

	while( 1 ) {
		char* tp	= strtok(NULL, "\t ;,\n");
		if( !tp ) {
			break;
		}

		std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();

		switch( attitudeNum ) {
			case ATTITUDE_FRAME_NUM: {
				retTrans.attitude.push_back(_Attitude());
				std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();
				(*attitudeItr).frame	= atoi(tp);
				attitudeNum				= ATTITUDE_TRANSFERS;
				break;
			}
			
			case ATTITUDE_TRANSFERS: {
				(*attitudeItr).trans	= static_cast<f32>(atof(tp));
				attitudeNum				= ATTITUDE_SPLIT_FLAG;
				break;
			}
			
			case ATTITUDE_SPLIT_FLAG: {
				(*attitudeItr).splitFlag	= (atoi(tp) == 1);
				attitudeNum					= ATTITUDE_SLOPE_TYPE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_FRONT: {
				(*attitudeItr).slopeTypeFront	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_TYPE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_REAR: {
				(*attitudeItr).slopeTypeRear	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_FRONT: {
				math::Vector direcFront(-1.0, atof(tp), 0.0);
				(*attitudeItr).slopeHandleFront	= direcFront;
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_REAR: {
				math::Vector direcRear(1.0, atof(tp), 0.0);
				(*attitudeItr).slopeHandleRear	= direcRear;
				attitudeNum						= ATTITUDE_FRAME_NUM;
				break;
			}

			default:
				PRINTF("ここにはこない\n");
				break;
		}
	}

	SafeDeleteArray(strBuf);

	return retTrans;
}
#endif

//===========================================================================
/*!	@brief	メッシュの全削除
	@param	mesh	: メッシュ
	@return	なし
*/
//===========================================================================
void ToyFile::_DeleteAllMesh(_Mesh* m)
{
	for(u32 i = 0; i < m->mesh.size(); ++i) {
		_DeleteAllMesh(m->mesh[i]);
	}
	SafeDelete(m);
}


//===========================================================================
/*!	@brief	メッシュツリーの先頭を取得
	@param	なし
	@return	メッシュツリーの先頭
*/
//===========================================================================
ToyFile::_Mesh* ToyFile::GetRootMesh() const
{
	return m_model.rootMesh;
}


//===========================================================================
/*!	@brief	マテリアルを取得
	@param	なし
	@return	マテリアル
*/
//===========================================================================
Material ToyFile::GetMaterial() const
{
	return m_model.material;
}

//===========================================================================
/*!	@brief	アニメーションを取得
	@param	animName	: アニメーション名
	@return	アニメーションデータへのポインタ
*/
//===========================================================================
const ToyFile::_Animation* ToyFile::GetAnimation(std::string animName) const
{

	for(u32 i = 0; i < m_animAry.size(); ++i) {
		if( m_animAry[i].name == animName ) {
			return &(m_animAry[i]);
		}
	}

	PRINTF("%s : アニメーション名が見つかりませんでした。\n");

	return NULL;
}

}	// namespace resource







//===============ファイルロード===============


namespace resource {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
LoadToyFile::LoadToyFile() : 
	m_controller(NULL),
	m_tagTree(NULL),
	m_fp(NULL)
{

	
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	path	: ファイル名
*/
//===========================================================================
LoadToyFile::LoadToyFile( std::string path ) :
	m_controller(NULL),
	m_tagTree(NULL),
	m_fp(NULL)
{
	Load(path);
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
LoadToyFile::~LoadToyFile()
{
	if( m_tagTree ) {
		_DeleteAllTag(m_tagTree);
	}
}


//===========================================================================
/*!	@brief	ロード
	@param	path	: ファイルパス
	@return	なし
*/
//===========================================================================
void LoadToyFile::Load( std::string path )
{
	/* ファイルを開く */
	m_fp = fopen(path.c_str(), "r");
	if( !m_fp ) {
		PRINTF("file open error : %s\n", path.c_str());
		return;
	}

	/* ファイルパスを設定 */
	m_filePath = path;


	/* ツリー元を生成 */
	m_tagTree			= new _Tag;
	m_tagTree->close	= false;
	m_tagTree->prev		= NULL;
	m_tagTree->tagName	= "";

	m_controller = m_tagTree;
	m_loop = true;


	/* タグ読込み */
	while( m_loop ) {
		_Tag* next = _GetNextTag();
		if( next ) {
			m_controller->tree.push_back(next);
			if( !next->close ) {
				m_controller = next;
			}
		}
	}

	/* ファイルを閉じる */
	fclose(m_fp);

}


//===========================================================================
/*!	@brief	次のタグを取得
	@param	なし
	@return	タグ		NULL : ファイル終端
*/
//===========================================================================
LoadToyFile::_Tag* LoadToyFile::_GetNextTag()
{
	bool	readTag		= false;	// タグ読み込み中かどうか
	char	buf[256]	= { 0 };	// 読込みバッファ
	s32		bufIdx		= 0;		// 操作中の読込みバッファインデックス


	while( 1 ) {

		/* 読込み */
		char c = fgetc(m_fp);


		/* ファイル終端なら抜ける */
		if( c == EOF ) {
			m_loop = false;
			return NULL;
		}

		/* タグ開始 */
		if( c == '<' ) {
			// 最初の「<」を読み込む時はreadFlagがfalseなので
			// readFlagがtrueの時だけ入るようにすれば途中で出現した<を判別できる
			//if( m_controller && readFlag ) {
			//	m_controller->value += '\0';
			//}
			readTag = true;
		}

		/* バッファに格納 */
		if( readTag ) {
			buf[bufIdx] = c;
			bufIdx++;
		} else {
			if( m_controller ) {
				m_controller->value += c;
			}
		}

		/* タグ終了 */
		if( c == '>' ) {
			buf[bufIdx] = '\0';
			break;
		}
	}

	
	/* 終了タグなら抜ける */
	if( buf[1] == '/' ) {
		m_controller->close = true;			// タグ終了設定
		m_controller = m_controller->prev;	// 操作タグを1階層戻す
		return NULL;
	}

	/* <!～～>型式の場所(タグじゃない) */
	if( buf[1] == '!' ) {
		for(s32 i = 0; buf[i] != '\0'; ++i) {
			m_controller->value += buf[i];
		}
		return NULL;
	}

	/* タグを生成 */
	_Tag*	retTag	= new _Tag;		// リターン用のタグ

	/* タグを初期化 */
	retTag->close	= false;
	retTag->prev	= m_controller;

	{	/* 1個のタグで終了する場合 */
		s32 i;
		for(i = 0; buf[i] != '>'; ++i)
			;
		if( buf[i - 1] == '/' ) {
			retTag->close	= true;				// タグ終了設定
		}
	}

	/* タグ名を設定 */
	char* token = strtok(buf, "</ =\">");
	for(s32 i = 0; token[i] != '\0'; ++i) {
		retTag->tagName += token[i];
	}
	//retTag->tagName += '\0';


	/* プロパティを設定 */
	s32 attributeFlag	= 1;	// 属性操作中フラグ
	s32 proNum			= 0;	// プロパティ番号
	while( 1 ) {
		if( attributeFlag ) {
			token = strtok(NULL, "</ =\">");	// 属性のほうはスラッシュを含める
			if( !token ) {
				break;
			}
			retTag->pro.push_back(_Property());
			for(s32 i = 0; token[i] != '\0'; ++i) {
				retTag->pro[proNum].attribute += token[i];
			}
			//retTag->pro[proNum].attribute += '\0';

		} else {
			token = strtok(NULL, "< =\">");		// 値のほうはスラッシュでの区切りを省く
			if( !token ) {
				break;
			}
			for(s32 i = 0; token[i] != '\0'; ++i) {
				retTag->pro[proNum].value += token[i];
			}
			//retTag->pro[proNum].value += '\0';
			
			++proNum;		// プロパティ番号を加算
		}

		attributeFlag = 1 - attributeFlag;		// フラグ入れ替え
	}

	return retTag;
}


//===========================================================================
/*!	@brief	有効なタグかどうかを判断
	@param	tag	: 判断を行うタグ
	@return	true : 有効		false : 無効
*/
//===========================================================================
bool LoadToyFile::_IsEnableTag( const _Tag* tag ) {

	if( tag->tagName == "Model" )			{ return true; }
	if( tag->tagName == "Name" )			{ return true; }
	if( tag->tagName == "Material" )		{ return true; }
	if( tag->tagName == "VertexColored" )	{ return true; }
	if( tag->tagName == "Textures" )		{ return true; }
	if( tag->tagName == "Visible" )			{ return true; }
	if( tag->tagName == "Mesh" )			{ return true; }
	if( tag->tagName == "Vertices" )		{ return true; }
	if( tag->tagName == "Faces" )			{ return true; }
	if( tag->tagName == "Objects" )			{ return true; }
	if( tag->tagName == "Anims" )			{ return true; }
	if( tag->tagName == "Anim" )			{ return true; }
	if( tag->tagName == "LastFrame" )		{ return true; }
	if( tag->tagName == "Item" )			{ return true; }

	return false;
}




//===========================================================================
/*!	@brief	タグを全削除
	@param	tag		: 削除するタグ
	@return	なし
	\note	そこからツリー状になっている要素を全て削除
*/
//===========================================================================
void LoadToyFile::_DeleteAllTag( nk::resource::LoadToyFile::_Tag *tag )
{
	for(u32 i = 0; i < tag->tree.size(); ++i) {
		_DeleteAllTag(tag->tree[i]);
	}
	SafeDelete(tag);
}


//===========================================================================
/*!	@brief	タグを取得
	@param	tag		: このタグ以上の階層を検索する
	@param	name	: 検索するタグ名
	@return	検索結果	NULL : 見つからなかった場合
*/
//===========================================================================
LoadToyFile::_Tag* LoadToyFile::_GetTag( _Tag *tag, std::string name )
{
	if( tag->tagName == name ) {
		return tag;
	}
	for(u32 i = 0; i < tag->tree.size(); ++i) {
		_Tag* temp = _GetTag(tag->tree[i], name);
		if( temp ) {
			return temp;
		}
	}
	return NULL;
}



}	// namespace resource
}	// namespace nk