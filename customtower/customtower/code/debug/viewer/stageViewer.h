//=============================================================================
/*!	@file	stageViewer.h

	@brief	ステージビューアー

	@author	ryunosuke ide
	@date	2013.05.28
*/
//=============================================================================


#ifndef __STAGE_VIEWER_H__
#define __STAGE_VIEWER_H__

#include "game/battle/stage/stage01/stage01.h"
#include "game/scene/sceneInterface.h"

namespace game {

namespace debug {

//=============================================================================
/*!
							ステージビューアー
*/
//=============================================================================
class StageViewer : public SceneInterface {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	virtual void	RenderLocal( void );

	//===========================================================================
	/*!	@brief		リソース生成
	*/
	//===========================================================================
	virtual void	InitializeScene( SceneInterface* parent );

	//===========================================================================
	/*!	@brief		リソース削除
	*/
	//===========================================================================
	virtual void	TerminateScene( SceneInterface* parent );
	
protected:
	
	//===========================================================================
	/*!	@brief		ローカル更新
	*/
	//===========================================================================
	virtual s32		ExecuteLocal( s32 parentMessage );

	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	

public:
	//-------------コンストラクタ・デストラクタ--------------
			StageViewer();
	virtual~StageViewer();
};
	
}	// namespace debug

}	// namespace game


#endif  // __STAGE_VIEWER_H__