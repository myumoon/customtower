//=============================================================================
/*!	@file	battleInfo.h

	@brief	対戦情報

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
								対戦情報
*/
//=============================================================================
struct BattleInfo {	
	
	//-----------------------型定義--------------------------
	//! ステージ
	enum STAGE_TYPE {
		STAGE_TYPE_UNKNOWN,				//!< 未設定
		STAGE_TYPE_STAGE01,				//!< ステージ01
	};

	//! コントローラー
	enum CONTOROLLER_TYPE {
		CONTOROLLER_TYPE_NONE,			//!< 無し
		CONTOROLLER_TYPE_USER,			//!< ユーザー操作
		CONTOROLLER_TYPE_ONLINE_PLAYER,	//!< オンラインユーザー
		CONTOROLLER_TYPE_AI_NORMAL,		//!< AI(普通)
	};

	//----------------------静的メンバ-----------------------
	static const	s32	MAX_CONTROLLER_NUM	= 4;	//!< 最大対戦者数
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		設定
	*/
	//===========================================================================
	void		SetStage( STAGE_TYPE type );
	void		AddControler( CONTOROLLER_TYPE type );
	
	

	//----------------------メンバ変数-----------------------
	s32			stageType;									//!< ステージ
	s32			stageSize;									//!< ステージサイズ(%)
	s32			contorollerNum;								//!< 対戦者数
	s32			contorollerTypes[MAX_CONTROLLER_NUM];		//!< コントローラータイプ

private:
	//-----------------------メソッド------------------------
	void		_Init( void );
	void		_Term( void );
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			BattleInfo();
	virtual~BattleInfo();
};


}	// namespace battle
	
}	// namespace game





#endif  // __BATTLE_INFO_H__