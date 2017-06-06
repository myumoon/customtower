/*-------------------------------------------------------------------------
	���@���F�L�[�{�[�h�̐ݒ�𔽉f������N���X
	�쐬���F2010/10/01
	�X�V���F2010/10/01
--------------------------------------------------------------------------*/
#include "KeyboardProxy.h"



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F�R���X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F
//	 memo �F
//========================================================================
CKeyboardProxy::CKeyboardProxy()
{

	Init();

}



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F�f�X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
CKeyboardProxy::~CKeyboardProxy()
{


	Finalize();

}


//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F������
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CKeyboardProxy::Init()
{

	m_keyboard = NULL;

	/* �ړ��L�[���Z�b�g */
	m_urdl[__UP]	= KEY_UP;
	m_urdl[__RIGHT]	= KEY_RIGHT;
	m_urdl[__DOWN]	= KEY_DOWN;
	m_urdl[__LEFT]	= KEY_LEFT;

}


//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F�I������
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CKeyboardProxy::Finalize()
{


}


//========================================================================
//	�N���X�FFinalize
//	���@�e�F�X�V
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CKeyboardProxy::Update()
{

	if( !m_keyboard ) {
		m_keyboard = new CKeyboard();
	}

	m_keyboard->Update();

}



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F������Ă��邩
//	���@���Fc		: �R�}���h
//	�߂�l�Ftrue	: ������Ă���
//			false	: ������Ă��Ȃ�
//	 memo �F
//========================================================================
bool CKeyboardProxy::IsPress(Command c)
{

	return m_keyboard->IsPress(m_config[c]);
}



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F��������
//	���@���Fc		: �R�}���h
//	�߂�l�Ftrue	: ������
//			false	: �����Ă��Ȃ�
//	 memo �F
//========================================================================
bool CKeyboardProxy::IsPressed(Command c)
{

	return m_keyboard->IsPressed(m_config[c]);
}



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F��������
//	���@���Fc		: �R�}���h
//	�߂�l�Ftrue	: �����Ă���
//			false	: �����Ă��Ȃ�
//	 memo �F
//========================================================================
bool CKeyboardProxy::IsRelease(Command c)
{

	return m_keyboard->IsRelease(m_config[c]);
}



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F��������
//	���@���Fc		: �R�}���h
//	�߂�l�Ftrue	: ������
//			false	: ���̑�
//	 memo �F
//========================================================================
bool CKeyboardProxy::IsReleased(Command c)
{

	return m_keyboard->IsReleased(m_config[c]);
}



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F�z��ɔԍ����Z�b�g
//	���@���Fkey_num	: �Z�b�g����R�}���h
//			num		: �p�b�h�̃{�^��
//	�߂�l�F
//	 memo �F
//========================================================================
void CKeyboardProxy::SetCommandButtom(int key_num, int cmd)
{

	assert((0 <= cmd) && (cmd < GetArraySize(m_buttom_idx)));

	m_buttom_idx[cmd] = key_num;

}



//========================================================================
//	�N���X�Fm_urdl[_UP] = u;
//	���@�e�F�ړ��L�[���Z�b�g
//	���@���Fu	: ��L�[
//			r	: �E�L�[
//			d	: ���L�[
//			l	: ���L�[
//	�߂�l�F�Ȃ�
//	 memo �F�f�t�H���g�ł�[��][��][��][��]�L�[
//========================================================================
void CKeyboardProxy::SetURDL(int u, int r, int d, int l)
{
	
	m_urdl[__UP]	= u;
	m_urdl[__RIGHT]	= r;
	m_urdl[__DOWN]	= d;
	m_urdl[__LEFT]	= l;

}


//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F�ړ��ʂ��擾
//	���@���F�Ȃ�
//	�߂�l�F�X��
//	 memo �F
//========================================================================
CVector CKeyboardProxy::GetTilt() const
{
	CVector tilt;

	if( m_keyboard->IsPress(m_urdl[__UP]) ) {
		tilt += CVector(0.0f, 1.0f, 0.0f);
	}
	if( m_keyboard->IsPress(m_urdl[__RIGHT]) ) {
		tilt += CVector(1.0f, 0.0f, 0.0f);
	}
	if( m_keyboard->IsPress(m_urdl[__DOWN]) ) {
		tilt += CVector(0.0f, -1.0f, 0.0f); 
	}
	if( m_keyboard->IsPress(m_urdl[__LEFT]) ) {
		tilt += CVector(-1.0f, 0.0f, 0.0f); 
	}

	tilt.Normalize();


	return tilt;
}



//========================================================================
//	�N���X�FCKeyboardProxy
//	���@�e�F�v���C���[�ԍ��̃Z�b�g
//	���@���Fp	: �ԍ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void CKeyboardProxy::SetPlayerNum(int p)
{

	m_ctrl_num = p;

	for(int i = 0; i < CC_SIZE; i++) {
		m_config.insert(std::pair<Command, KEY_NUM>(CC[i].command, CC[i].key_num));
	}

}