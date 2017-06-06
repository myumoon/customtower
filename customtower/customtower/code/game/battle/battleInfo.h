//=============================================================================
/*!	@file	battleInfo.h

	@brief	�ΐ���

	@author	ryunosuke ide
	@date	2013.06.02
*/
//=============================================================================


#ifndef __BATTLE_INFO_H__
#define __BATTLE_INFO_H__



namespace game {

	
namespace battle {


//=============================================================================
/*!
								�ΐ���
*/
//=============================================================================
struct BattleInfo {	
	
	//-----------------------�^��`--------------------------
	//! �X�e�[�W
	enum STAGE_TYPE {
		STAGE_TYPE_UNKNOWN,				//!< ���ݒ�
		STAGE_TYPE_STAGE01,				//!< �X�e�[�W01
	};

	//! �R���g���[���[
	enum CONTOROLLER_TYPE {
		CONTOROLLER_TYPE_NONE,			//!< ����
		CONTOROLLER_TYPE_USER,			//!< ���[�U�[����
		CONTOROLLER_TYPE_ONLINE_PLAYER,	//!< �I�����C�����[�U�[
		CONTOROLLER_TYPE_AI_NORMAL,		//!< AI(����)
	};

	//----------------------�ÓI�����o-----------------------
	static const	s32	MAX_CONTROLLER_NUM	= 4;	//!< �ő�ΐ�Ґ�
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�ݒ�
	*/
	//===========================================================================
	void		SetStage( STAGE_TYPE type );
	void		AddControler( CONTOROLLER_TYPE type );
	
	

	//----------------------�����o�ϐ�-----------------------
	s32			stageType;									//!< �X�e�[�W
	s32			stageSize;									//!< �X�e�[�W�T�C�Y(%)
	s32			contorollerNum;								//!< �ΐ�Ґ�
	s32			contorollerTypes[MAX_CONTROLLER_NUM];		//!< �R���g���[���[�^�C�v

private:
	//-----------------------���\�b�h------------------------
	void		_Init( void );
	void		_Term( void );
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			BattleInfo();
	virtual~BattleInfo();
};


}	// namespace battle
	
}	// namespace game





#endif  // __BATTLE_INFO_H__