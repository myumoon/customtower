//=============================================================================
/*!	@file	updateObject.h

	@brief	更新オブジェクト

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

#ifndef __UPDATE_OBJECT_H__
#define __UPDATE_OBJECT_H__

namespace game {

//=============================================================================
/*!
							更新オブジェクト
*/
//=============================================================================
class UpdateObject {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual bool		Execute( void ) = 0;
	
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			UpdateObject();
	virtual~UpdateObject();
};

	
}	// namespace game







#endif  // __UPDATE_OBJECT_H__