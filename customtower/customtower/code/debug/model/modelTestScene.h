//=============================================================================
/*!	@file	modelTestScene.h

	@brief	モデル描画テスト

	@author	ryunosuke ide
	@date	2013.05.25
*/
//=============================================================================

#ifndef __MODEL_TEST_SCENE_H__
#define __MODEL_TEST_SCENE_H__

#include "utility/selector.h"
#include "system.h"

#include "game/scene/sceneInterface.h"



namespace game {


//=============================================================================
/*!
								タイトル
*/
//=============================================================================
class ModelTestScene : public SceneInterface {
public: 
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		ローカル更新
	*/
	//===========================================================================
	virtual s32		ExecuteLocal( s32 parentMessage );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	virtual void	RenderLocal( void );
	
	//===========================================================================
	/*!	@brief		ツリー生成
	*/
	//===========================================================================
	virtual void	CreateTree( void ) {}

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

	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );


	//----------------------メンバ変数-----------------------
	f32									m_sphereRot;		// 
	FILE*								m_fpOut;			// ファイル
	nk::graphics::Model					m_floor;			// 地面
	nk::graphics::Model					m_sphere;			// 球体
	nk::graphics::AnimationModel		m_animModel;		// 機械モデル
	nk::math::Vector					m_pos;				// 機械モデルの位置
	nk::BVRay							m_hitRay;			// 線分ヒット
	nk::BVSphere						m_hitSphere;		// 球ヒット
	nk::BVInfiniteFace					m_infinitie;		// 無限平面
	nk::graphics::Sprite				m_shadowMapSprite;	// シャドウマップスプライト
	nk::graphics::Sprite				m_loadIcon;			// ロードアイコン
	nk::graphics::Line					m_line;				// 線
	nk::resource::ResourceLoader*		m_resourceLoader;	// リソースロード
	bool								m_modelInit;		// モデル初期化

public:
	//-------------コンストラクタ・デストラクタ--------------
			ModelTestScene();
	virtual~ModelTestScene();
};
	
}	// namespace game




#endif  // __MODEL_TEST_SCENE_H__