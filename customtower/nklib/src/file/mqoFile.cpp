//=============================================================================
/*!	@file	mqoModel.h

	@brief	mqoモデルクラス

	@author	井手 竜之介
	@date	2012/02/21
	@todo	なし
	@bug	なし
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <vector>
#include "../../include/file/mqoFile.h"
#include "../../include/resource/resourceManager.h"
#include "../../include/utility/stringfunction.h"


namespace nk {
namespace resource {

resource::ResourceManager* LoadMqoFile::m_resourceMng	= NULL;


//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
	@return	
*/
//===========================================================================
MqoFile::MqoFile() :
	m_name(),
	m_vertex(),
	m_face(),
	m_material(),
	m_normal()
{
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	ロードファイル
	@return	
*/
//===========================================================================
MqoFile::MqoFile(const LoadMqoFile& file) :
	m_name(file.m_path),
	m_vertex(file.m_vertex),
	m_face(file.m_face),
	m_material(file.m_material),
	m_normal(file.m_normal)
{
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
	@return	
*/
//===========================================================================
MqoFile::~MqoFile()
{
}


//===========================================================================
/*!	@brief	ファイル名をセット
	@param	name	: ファイル名
	@return	なし
*/
//===========================================================================
void MqoFile::SetFileName(std::string name)
{
	m_name = name;
}


//===========================================================================
/*!	@brief	ファイル名を習得
	@param	なし
	@return	ファイル名
*/
//===========================================================================
std::string MqoFile::GetFileName() const
{
	return m_name;
}


//===========================================================================
/*!	@brief	頂点データの追加
	@param	pos	: 追加する頂点データ
	@return	なし
*/
//===========================================================================
void MqoFile::AddVertex(const nk::math::Vector &pos)
{
	m_vertex.Add(pos);
}


//===========================================================================
/*!	@brief	頂点データを習得
	@param	なし
	@return	頂点データ
*/
//===========================================================================
const Vertex& MqoFile::GetVertex() const
{
	return m_vertex;
}


//===========================================================================
/*!	@brief	面データの追加
	@param	index	: 面番号
	@param	uv		: 面のUV座標
	@return	なし
*/
//===========================================================================
void MqoFile::AddFace(u32 index, const nk::math::Vector &uv)
{
	m_face.AddFaceUV(index, uv);
}


//===========================================================================
/*!	@brief	面データの習得
	@param	なし
	@return	面データ
*/
//===========================================================================
const Face& MqoFile::GetFace() const
{
	return m_face;
}


//===========================================================================
/*!	@brief	法線データを習得
	@param	なし
	@return	法線データ
*/
//===========================================================================
const Vertex& MqoFile::GetNormalVertex() const
{
	return m_normal;
}


//===========================================================================
/*!	@brief	マテリアルのセット
	@param	material	: マテリアルデータ
	@return	なし
*/
//===========================================================================
void MqoFile::SetMaterial(const nk::resource::Material &material)
{
	m_material = material;
}


//===========================================================================
/*!	@brief	マテリアルの習得
	@param	なし
	@return	マテリアル
*/
//===========================================================================
Material MqoFile::GetMaterial() const
{
	return m_material;
}


//===========================================================================
/*!	@brief	mqoファイルの読込み
	@param	path	: ファイルパス
	@return	生成したファイルへのポインタ
*/
//===========================================================================
LoadMqoFile::LoadMqoFile(std::string path) :
	m_vertex(),
	m_material(),
	m_face(),
	m_path(path)
{
	char strBuff[256];
	FILE *inPut;


	if((inPut = fopen(path.c_str(), "rb")) == NULL) {
		PRINTF("file open error : %s\n", path.c_str());
		return;
	}


	bool vertex_load_flag = false, face_load_flag = false;	// 読込みフラグ

	while( fgets(strBuff, sizeof(strBuff), inPut) != NULL ) {

		if( strstr(strBuff, "\t}") != NULL ) {
			vertex_load_flag = false;
			face_load_flag = false;
		}

		//	テクスチャ読み込み
		//---------------------------------------
		if( strstr(strBuff, "Material ") ) {
			
			// 次の行に移動
			fgets(strBuff, sizeof(strBuff), inPut);

			/* 色の取得 */
			f32 r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
			std::string color_num = FindStr(strBuff, "col(", ")");
			sscanf(color_num.c_str(), "%f %f %f %f", &r, &g, &b, &a);
			m_material.SetColor(Color(r, g, b, a));

			std::string dirPath		= GetDirectoryPath( path );
			std::string tex_name	= FindStr(strBuff, "tex(\"", "\")");

			// 既にロードされているかチェック
			// されていなかったらロード @@@@@

			m_material.SetTexture( m_resourceMng->GetTexture(dirPath + tex_name) );
			//m_material.SetTexture(m_resourceMng->GetTexture(tex_name));
		}

		//	頂点座標読込み
		//---------------------------------------
		if( vertex_load_flag ) {
			f32 x, y, z;
			sscanf(strBuff, "\t%f %f %f", &x, &y, &z);
			m_vertex.Add(math::Vector(x, y, z));
		}
		if( strstr(strBuff, "\tvertex ") != NULL ) {
			vertex_load_flag = true;
		}


		//	面情報読込み
		//---------------------------------------
		if( face_load_flag ) {
			s32 idx[3];
			f32 uv[6];
			sscanf(strBuff, "\t\t3 V(%d %d %d) M(0) UV(%f %f %f %f %f %f)",
				&idx[0], &idx[2], &idx[1],
				&uv[0], &uv[1], &uv[4], &uv[5], &uv[2], &uv[3]
			);
			m_face.AddFaceUV(idx[0], math::Vector(uv[0], uv[1], 0.0f));
			m_face.AddFaceUV(idx[1], math::Vector(uv[2], uv[3], 0.0f));
			m_face.AddFaceUV(idx[2], math::Vector(uv[4], uv[5], 0.0f));
		}
		if( strstr(strBuff, "\tface ") != NULL ) {
			face_load_flag = true;
		}

	}
	
	/* 頂点法線を格納する構造体 */
	typedef std::vector<math::Vector> VertexNormal;	// 頂点番号を含む面法線

	/* 頂点法線の数を設定 */
	std::vector<VertexNormal> vertexNormal(m_vertex.GetSize());

	for(u32 i = 0; i < m_face.GetSize(); i += m_face.GetBundle()) {
		math::Vector v0 = m_vertex.GetVertex(m_face.GetFace(i + 1)) - m_vertex.GetVertex(m_face.GetFace(i));
		math::Vector v1 = m_vertex.GetVertex(m_face.GetFace(i + 2)) - m_vertex.GetVertex(m_face.GetFace(i));
		math::Vector N	= math::CalcCrossProduct(v0, v1);

		vertexNormal[m_face.GetFace(i + 0)].push_back(N);
		vertexNormal[m_face.GetFace(i + 1)].push_back(N);
		vertexNormal[m_face.GetFace(i + 2)].push_back(N);
	}

	for(u32 i = 0; i < m_vertex.GetSize(); ++i) {
		math::Vector sum;
		for(u32 j = 0; j < vertexNormal[i].size(); ++j) {
			sum += vertexNormal[i].at(j);
		}
		sum.Normalize();
		m_normal.Add(sum);
	}




	fclose(inPut);
}

//===========================================================================
/*!	@brief	デストラクタ
	@param	
	@return	
*/
//===========================================================================
LoadMqoFile::~LoadMqoFile()
{
}


}	// namespace resource
}	// namespace nk
#if 0

using namespace std;

const f32 CModel::NON_SET = -1.0f;

//========================================================================
//	クラス：CModel
//	内　容：コンストラクタ
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
CModel::CModel() : UpdateObject(), m_pos(), m_rotate(), m_scale(1.0f), m_trans()
{

m_color.Set(1.0f, 1.0f, 1.0f, 1.0f);
m_use_tex_flag = true;

}



//========================================================================
//	クラス：CModel
//	内　容：デストラクタ
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
CModel::~CModel()
{


}




//========================================================================
//	クラス：CModel
//	内　容：位置をセット
//	引　数：x, y, z	: 座標
//	戻り値：
//	 memo ：
//========================================================================
void CModel::SetPos(const CVector &pos)
{

m_pos = pos;

}



//========================================================================
//	クラス：CModel
//	内　容：位置をセット
//	引　数：pos	: 座標
//	戻り値：
//	 memo ：
//========================================================================
void CModel::SetPos(f32 x, f32 y, f32 z)
{
m_pos.x = x;
m_pos.y = y;
m_pos.z = z;

}




//========================================================================
//	クラス：CModel
//	内　容：オブジェクトのタイプを設定
//	引　数：type	: タイプ
//	戻り値：なし
//	 memo ：
//========================================================================
void CModel::SetObjType(s32 type)
{

m_type = type;

}




//========================================================================
//	クラス：CModel
//	内　容：移動
//	引　数：移動量
//	戻り値：なし
//	 memo ：zにはデフォルトで0が入る
//========================================================================
void CModel::Move(f32 x, f32 y, f32 z)
{

m_pos.x += x;
m_pos.y += y;
m_pos.z += z;

}


//========================================================================
//	クラス：CModel
//	内　容：移動
//	引　数：s	: 移動ベクトル
//	戻り値：なし
//	 memo ：
//========================================================================
void CModel::Move(const CVector &s)
{

m_pos += s;

}


//========================================================================
//	クラス：CModel
//	内　容：回転
//	引　数：x	: X軸回転量
//			y	: Y軸回転量
//			z	: Z軸回転量
//	戻り値：なし
//	 memo ：
//========================================================================
void CModel::Rotate(f32 x, f32 y, f32 z)
{

m_rotate.x = x;
m_rotate.y = y;
m_rotate.z = z;


}




//========================================================================
//	クラス：CModel
//	内　容：拡大縮小
//	引　数：x	: X軸拡大量
//			y	: Y軸拡大量
//			z	: Z軸拡大量
//	戻り値：なし
//	 memo ：
//========================================================================
void CModel::ZoomModel(f32 x, f32 y, f32 z)
{

m_scale.x = x;
m_scale.y = y;
m_scale.z = z;


}




//========================================================================
//	クラス：CModel
//	内　容：ワールドビュー行列をセット
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
void CModel::SetWorldViewMatrix()
{
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

//	カメラ行列に変換
//---------------------------------------
CMatrix44 view = CAMERA_MNG->GetCameraMatrix();
SetGL(&view, &m_trans);


}


//========================================================================
//	クラス：CModel
//	内　容：描画
//	引　数：
//	戻り値：
//	 memo ：
//========================================================================
void CModel::Draw()
{


glEnableClientState(GL_VERTEX_ARRAY | GL_INDEX_ARRAY | GL_TEXTURE_COORD_ARRAY);


//	テクスチャを指定
//---------------------------------------
bool tex_flag = false;
if( m_use_tex_flag && m_material && m_material->GetTexture() ) {
glEnable(GL_TEXTURE_2D);		//テクスチャON
m_material->GetTexture()->BindTexture();
tex_flag = true;
} else {
//glDisable(GL_TEXTURE_2D);			//テクスチャOFF
}

//	描画
//---------------------------------------
glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);

glBegin(GL_TRIANGLES);
const s32 idx_size =  m_material->GetIndexLength();
for(s32 i = 0; i < idx_size; i++) {

/* 法線を設定 */
glNormal3f(
	m_vertex->GetVertexNormal(m_material->GetIndex(i)).x,
	m_vertex->GetVertexNormal(m_material->GetIndex(i)).y,
	m_vertex->GetVertexNormal(m_material->GetIndex(i)).z);

/* UVを設定 */
glTexCoord2f(m_material->GetU(i), m_material->GetV(i));

/* 頂点を設定 */
glVertex3f(
	m_vertex->GetVertex(m_material->GetIndex(i)).x,
	m_vertex->GetVertex(m_material->GetIndex(i)).y,
	m_vertex->GetVertex(m_material->GetIndex(i)).z);
}
glEnd();


glDisable(GL_TEXTURE_2D);//テクスチャOFF
glDisableClientState(GL_VERTEX_ARRAY | GL_INDEX_ARRAY | GL_TEXTURE_COORD_ARRAY);


}




//========================================================================
//	クラス：CModel
//	内　容：コピー
//	引　数：model	: コピーを行うデータ
//	戻り値：なし
//	 memo ：
//========================================================================
void CModel::Copy(const CModel &model)
{
//m_priority			= model.m_priority;
//m_priority_draw		= model.m_priority_draw;
m_pos				= model.m_pos;
m_pos_prev			= model.m_pos_prev;
m_rotate			= model.m_rotate;		
m_scale				= model.m_scale;		
m_trans				= model.m_trans;		
m_material			= model.m_material;			
m_vertex			= model.m_vertex;		
m_type				= model.m_type;			
m_color				= model.m_color;		
//m_key				= model.m_key;			
strcpy(m_key, model.m_key);

}


//========================================================================
//	内　容：処理優先度が左辺のほうが小さいか
//	引　数：rhs		: 右辺
//			lhs		: 左辺
//	戻り値：true	: 未満
//			false	: 以上
//	 memo ：
//========================================================================
//bool IsLessProcPriority(const CModel *lhs, const CModel *rhs)
//{
//	return lhs->GetPriority() < rhs->GetPriority();
//}



//========================================================================
//	内　容：描画優先度が左辺のほうが小さいか
//	引　数：rhs		: 右辺
//			lhs		: 左辺
//	戻り値：true	: 未満
//			false	: 以上
//	 memo ：
//========================================================================
//bool IsLessDrawPriority(const CModel *lhs, const CModel *rhs)
//{
//	return lhs->GetDrawPriority() < rhs->GetDrawPriority();
//}



#endif