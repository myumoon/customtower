//=============================================================================
/*!	@file	mqoModel.h

	@brief	mqo���f���N���X

	@author	��� ���V��
	@date	2012/02/21
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <vector>
#include "../../include/file/mqoFile.h"
#include "../../include/resource/resourceManager.h"
#include "../../include/utility/stringfunction.h"


namespace nk {
namespace resource {

resource::ResourceManager* LoadMqoFile::m_resourceMng	= NULL;


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
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
/*!	@brief	�R���X�g���N�^
	@param	���[�h�t�@�C��
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
/*!	@brief	�f�X�g���N�^
	@param	
	@return	
*/
//===========================================================================
MqoFile::~MqoFile()
{
}


//===========================================================================
/*!	@brief	�t�@�C�������Z�b�g
	@param	name	: �t�@�C����
	@return	�Ȃ�
*/
//===========================================================================
void MqoFile::SetFileName(std::string name)
{
	m_name = name;
}


//===========================================================================
/*!	@brief	�t�@�C�������K��
	@param	�Ȃ�
	@return	�t�@�C����
*/
//===========================================================================
std::string MqoFile::GetFileName() const
{
	return m_name;
}


//===========================================================================
/*!	@brief	���_�f�[�^�̒ǉ�
	@param	pos	: �ǉ����钸�_�f�[�^
	@return	�Ȃ�
*/
//===========================================================================
void MqoFile::AddVertex(const nk::math::Vector &pos)
{
	m_vertex.Add(pos);
}


//===========================================================================
/*!	@brief	���_�f�[�^���K��
	@param	�Ȃ�
	@return	���_�f�[�^
*/
//===========================================================================
const Vertex& MqoFile::GetVertex() const
{
	return m_vertex;
}


//===========================================================================
/*!	@brief	�ʃf�[�^�̒ǉ�
	@param	index	: �ʔԍ�
	@param	uv		: �ʂ�UV���W
	@return	�Ȃ�
*/
//===========================================================================
void MqoFile::AddFace(u32 index, const nk::math::Vector &uv)
{
	m_face.AddFaceUV(index, uv);
}


//===========================================================================
/*!	@brief	�ʃf�[�^�̏K��
	@param	�Ȃ�
	@return	�ʃf�[�^
*/
//===========================================================================
const Face& MqoFile::GetFace() const
{
	return m_face;
}


//===========================================================================
/*!	@brief	�@���f�[�^���K��
	@param	�Ȃ�
	@return	�@���f�[�^
*/
//===========================================================================
const Vertex& MqoFile::GetNormalVertex() const
{
	return m_normal;
}


//===========================================================================
/*!	@brief	�}�e���A���̃Z�b�g
	@param	material	: �}�e���A���f�[�^
	@return	�Ȃ�
*/
//===========================================================================
void MqoFile::SetMaterial(const nk::resource::Material &material)
{
	m_material = material;
}


//===========================================================================
/*!	@brief	�}�e���A���̏K��
	@param	�Ȃ�
	@return	�}�e���A��
*/
//===========================================================================
Material MqoFile::GetMaterial() const
{
	return m_material;
}


//===========================================================================
/*!	@brief	mqo�t�@�C���̓Ǎ���
	@param	path	: �t�@�C���p�X
	@return	���������t�@�C���ւ̃|�C���^
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


	bool vertex_load_flag = false, face_load_flag = false;	// �Ǎ��݃t���O

	while( fgets(strBuff, sizeof(strBuff), inPut) != NULL ) {

		if( strstr(strBuff, "\t}") != NULL ) {
			vertex_load_flag = false;
			face_load_flag = false;
		}

		//	�e�N�X�`���ǂݍ���
		//---------------------------------------
		if( strstr(strBuff, "Material ") ) {
			
			// ���̍s�Ɉړ�
			fgets(strBuff, sizeof(strBuff), inPut);

			/* �F�̎擾 */
			f32 r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
			std::string color_num = FindStr(strBuff, "col(", ")");
			sscanf(color_num.c_str(), "%f %f %f %f", &r, &g, &b, &a);
			m_material.SetColor(Color(r, g, b, a));

			std::string dirPath		= GetDirectoryPath( path );
			std::string tex_name	= FindStr(strBuff, "tex(\"", "\")");

			// ���Ƀ��[�h����Ă��邩�`�F�b�N
			// ����Ă��Ȃ������烍�[�h @@@@@

			m_material.SetTexture( m_resourceMng->GetTexture(dirPath + tex_name) );
			//m_material.SetTexture(m_resourceMng->GetTexture(tex_name));
		}

		//	���_���W�Ǎ���
		//---------------------------------------
		if( vertex_load_flag ) {
			f32 x, y, z;
			sscanf(strBuff, "\t%f %f %f", &x, &y, &z);
			m_vertex.Add(math::Vector(x, y, z));
		}
		if( strstr(strBuff, "\tvertex ") != NULL ) {
			vertex_load_flag = true;
		}


		//	�ʏ��Ǎ���
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
	
	/* ���_�@�����i�[����\���� */
	typedef std::vector<math::Vector> VertexNormal;	// ���_�ԍ����܂ޖʖ@��

	/* ���_�@���̐���ݒ� */
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
/*!	@brief	�f�X�g���N�^
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
//	�N���X�FCModel
//	���@�e�F�R���X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
CModel::CModel() : UpdateObject(), m_pos(), m_rotate(), m_scale(1.0f), m_trans()
{

m_color.Set(1.0f, 1.0f, 1.0f, 1.0f);
m_use_tex_flag = true;

}



//========================================================================
//	�N���X�FCModel
//	���@�e�F�f�X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
CModel::~CModel()
{


}




//========================================================================
//	�N���X�FCModel
//	���@�e�F�ʒu���Z�b�g
//	���@���Fx, y, z	: ���W
//	�߂�l�F
//	 memo �F
//========================================================================
void CModel::SetPos(const CVector &pos)
{

m_pos = pos;

}



//========================================================================
//	�N���X�FCModel
//	���@�e�F�ʒu���Z�b�g
//	���@���Fpos	: ���W
//	�߂�l�F
//	 memo �F
//========================================================================
void CModel::SetPos(f32 x, f32 y, f32 z)
{
m_pos.x = x;
m_pos.y = y;
m_pos.z = z;

}




//========================================================================
//	�N���X�FCModel
//	���@�e�F�I�u�W�F�N�g�̃^�C�v��ݒ�
//	���@���Ftype	: �^�C�v
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CModel::SetObjType(s32 type)
{

m_type = type;

}




//========================================================================
//	�N���X�FCModel
//	���@�e�F�ړ�
//	���@���F�ړ���
//	�߂�l�F�Ȃ�
//	 memo �Fz�ɂ̓f�t�H���g��0������
//========================================================================
void CModel::Move(f32 x, f32 y, f32 z)
{

m_pos.x += x;
m_pos.y += y;
m_pos.z += z;

}


//========================================================================
//	�N���X�FCModel
//	���@�e�F�ړ�
//	���@���Fs	: �ړ��x�N�g��
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CModel::Move(const CVector &s)
{

m_pos += s;

}


//========================================================================
//	�N���X�FCModel
//	���@�e�F��]
//	���@���Fx	: X����]��
//			y	: Y����]��
//			z	: Z����]��
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CModel::Rotate(f32 x, f32 y, f32 z)
{

m_rotate.x = x;
m_rotate.y = y;
m_rotate.z = z;


}




//========================================================================
//	�N���X�FCModel
//	���@�e�F�g��k��
//	���@���Fx	: X���g���
//			y	: Y���g���
//			z	: Z���g���
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CModel::ZoomModel(f32 x, f32 y, f32 z)
{

m_scale.x = x;
m_scale.y = y;
m_scale.z = z;


}




//========================================================================
//	�N���X�FCModel
//	���@�e�F���[���h�r���[�s����Z�b�g
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CModel::SetWorldViewMatrix()
{
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

//	�J�����s��ɕϊ�
//---------------------------------------
CMatrix44 view = CAMERA_MNG->GetCameraMatrix();
SetGL(&view, &m_trans);


}


//========================================================================
//	�N���X�FCModel
//	���@�e�F�`��
//	���@���F
//	�߂�l�F
//	 memo �F
//========================================================================
void CModel::Draw()
{


glEnableClientState(GL_VERTEX_ARRAY | GL_INDEX_ARRAY | GL_TEXTURE_COORD_ARRAY);


//	�e�N�X�`�����w��
//---------------------------------------
bool tex_flag = false;
if( m_use_tex_flag && m_material && m_material->GetTexture() ) {
glEnable(GL_TEXTURE_2D);		//�e�N�X�`��ON
m_material->GetTexture()->BindTexture();
tex_flag = true;
} else {
//glDisable(GL_TEXTURE_2D);			//�e�N�X�`��OFF
}

//	�`��
//---------------------------------------
glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);

glBegin(GL_TRIANGLES);
const s32 idx_size =  m_material->GetIndexLength();
for(s32 i = 0; i < idx_size; i++) {

/* �@����ݒ� */
glNormal3f(
	m_vertex->GetVertexNormal(m_material->GetIndex(i)).x,
	m_vertex->GetVertexNormal(m_material->GetIndex(i)).y,
	m_vertex->GetVertexNormal(m_material->GetIndex(i)).z);

/* UV��ݒ� */
glTexCoord2f(m_material->GetU(i), m_material->GetV(i));

/* ���_��ݒ� */
glVertex3f(
	m_vertex->GetVertex(m_material->GetIndex(i)).x,
	m_vertex->GetVertex(m_material->GetIndex(i)).y,
	m_vertex->GetVertex(m_material->GetIndex(i)).z);
}
glEnd();


glDisable(GL_TEXTURE_2D);//�e�N�X�`��OFF
glDisableClientState(GL_VERTEX_ARRAY | GL_INDEX_ARRAY | GL_TEXTURE_COORD_ARRAY);


}




//========================================================================
//	�N���X�FCModel
//	���@�e�F�R�s�[
//	���@���Fmodel	: �R�s�[���s���f�[�^
//	�߂�l�F�Ȃ�
//	 memo �F
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
//	���@�e�F�����D��x�����ӂ̂ق�����������
//	���@���Frhs		: �E��
//			lhs		: ����
//	�߂�l�Ftrue	: ����
//			false	: �ȏ�
//	 memo �F
//========================================================================
//bool IsLessProcPriority(const CModel *lhs, const CModel *rhs)
//{
//	return lhs->GetPriority() < rhs->GetPriority();
//}



//========================================================================
//	���@�e�F�`��D��x�����ӂ̂ق�����������
//	���@���Frhs		: �E��
//			lhs		: ����
//	�߂�l�Ftrue	: ����
//			false	: �ȏ�
//	 memo �F
//========================================================================
//bool IsLessDrawPriority(const CModel *lhs, const CModel *rhs)
//{
//	return lhs->GetDrawPriority() < rhs->GetDrawPriority();
//}



#endif