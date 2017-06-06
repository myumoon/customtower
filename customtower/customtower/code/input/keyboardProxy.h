/*-------------------------------------------------------------------------
	���@���F�L�[�{�[�h�̐ݒ�𔽉f������N���X
	�쐬���F2010/10/01
	�X�V���F2010/10/14
--------------------------------------------------------------------------*/

#ifndef __KEYBOARDPROXY_H__
#define __KEYBOARDPROXY_H__

#include <map>
#include "general.h"
#include "math/vector.h"
#include "input/keyboard.h"
#include "inputCommand.cpp"



/*----------------------------------*/
/*		�L�[�{�[�h�ݒ�N���X		*/
/*	proxy							*/
/*----------------------------------*/
class CKeyboardProxy : public Input {
public:

	//	�Z�b�g
	//---------------------------------------
	
	/* ������ */
	void Init();
	
	/* �I������ */
	void Finalize();

	/* ���g�̃R���g���[���[�ԍ����Z�b�g */
	void SetCtrlNum(int num) { m_ctrl_num = num; }
	
	/* �{�^���ɃR�}���h��o�^ */
	void SetCommandButtom(int key_num, int cmd);
	
	/* ��E�����L�[��ݒ�i�f�t�H���g�Ł��������j */
	void SetURDL(int u, int r, int d, int l);

	/* �v���C���[�ԍ� */
	void SetPlayerNum(int p);

	//	�擾
	//---------------------------------------
	
	/* ���͉��� */
	bool IsPress(Command c);						// ������Ă��邩
	bool IsPressed(Command c);						// �����ꂽ��
	bool IsRelease(Command c);						// �����Ă��邩
	bool IsReleased(Command c);						// �����ꂽ��
	CVector GetTilt() const;						// �ړ��ʂ��擾


	/* ���쌳�L�[�{�[�h�̎擾 */
	CKeyboard* GetOriginalKeyboard() const { return m_keyboard; }

	//	�X�V
	//---------------------------------------
	void Update();


private:

	/* �㉺���E�萔 */
	enum { __UP, __RIGHT, __DOWN, __LEFT, __URDL_MAX };

	//	�f�[�^
	//---------------------------------------
	CKeyboard			   *m_keyboard;					// �Ή�����L�[�{�[�h
	int					    m_buttom_idx[COMMAND_MAX];	// �L�[�R���t�B�O�p�{�^���z�u
	int					    m_urdl[__URDL_MAX];			// ��E�����{�^��
	int						m_ctrl_num;					// �R���g���[���ԍ�
	std::map<Command, KEY_NUM>	m_config;				// �L�[�ݒ�

public:
	 CKeyboardProxy();
	~CKeyboardProxy();

};





#endif  // __KEYBOARDPROXY_H__