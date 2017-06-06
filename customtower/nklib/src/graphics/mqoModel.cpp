/*-------------------------------------------------------------------------
	説　明：モデルクラス
	作成日：2010/05/12
	更新日：2010/11/31
--------------------------------------------------------------------------*/

using namespace std;

const float CModel::NON_SET = -1.0f;

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
void CModel::SetPos(float x, float y, float z)
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
void CModel::SetObjType(int type)
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
void CModel::Move(float x, float y, float z)
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
void CModel::Rotate(float x, float y, float z)
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
void CModel::ZoomModel(float x, float y, float z)
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
	glColor4ub( m_color.r, m_color.g, m_color.b, m_color.a );

	glBegin(GL_TRIANGLES);
	const int idx_size =  m_material->GetIndexLength();
	for(int i = 0; i < idx_size; i++) {

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



