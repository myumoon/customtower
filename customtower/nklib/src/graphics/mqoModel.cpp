/*-------------------------------------------------------------------------
	���@���F���f���N���X
	�쐬���F2010/05/12
	�X�V���F2010/11/31
--------------------------------------------------------------------------*/

using namespace std;

const float CModel::NON_SET = -1.0f;

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
void CModel::SetPos(float x, float y, float z)
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
void CModel::SetObjType(int type)
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
void CModel::Move(float x, float y, float z)
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
void CModel::Rotate(float x, float y, float z)
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
void CModel::ZoomModel(float x, float y, float z)
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
	glColor4ub( m_color.r, m_color.g, m_color.b, m_color.a );

	glBegin(GL_TRIANGLES);
	const int idx_size =  m_material->GetIndexLength();
	for(int i = 0; i < idx_size; i++) {

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



