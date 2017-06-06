//=============================================================================
/*!	@file	shader.h

	@brief	シェーダー基底クラスと管理クラス

	@author	井手 竜之介
	@date	2012/02/23
	@todo	なし
	@bug	なし
*/
//=============================================================================
#ifndef __SHADER_H__
#define __SHADER_H__

//-------------------------------インクルード-------------------------------
#include <vector>
#include <string>
#include <map>
#include <list>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include "../math/matrix.h"
#include "../math/vector.h"
#include "../system/camera.h"
#include "../system/cameraManager.h"

namespace nk {

namespace resource {
	class Material;
	class Texture;
}
namespace system {
	class Camera;
}

namespace graphics {


//----------------------------------構造体----------------------------------
//! シェーダーで使用するデータ
struct ShaderData {
	std::string			shaderName;		//!< 使用するシェーダー名
	u32					useTechnique;	//!< 使用するテクニック(デフォルトで0)
	math::Matrix44		worldMat;		//!< ワールド行列
	system::Light		light;			//!< ライト情報
	math::Vector		screenSize;		//!< スクリーンサイズ
	u32					useTexId;		//!< シャドウマップ等に使用するテクスチャID
	resource::Texture*	mappingTex;		//!< マッピング用のテクスチャID
	u32			mode;			//!< モード

	ShaderData() {
		useTechnique	= 0;
		mappingTex		= NULL;
		mode			= 0;
		useTexId		= 0;
	}

	void SetupPhongShader( const system::Light& light )
	{
		this->shaderName	= "PhongShader";
		this->light			= light;
	}
};

//=============================================================================
/*!
								シェーダー基底クラス
*/
//=============================================================================
class Shader {
public:
	friend	class	ShaderManager;

	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------
	
	//! ロード
	//bool Load(const char *file_name);
	
	//! シェーダー描画開始
	void Begin( nk::resource::Material* material, u32 teq, nk::system::Camera* camera );

	//! シェーダー描画終了
	void End();

protected:

	//! 初期化
	virtual void	Init() = 0;

	//! 値のセット
	virtual void	SetParam( nk::resource::Material* material, nk::system::Camera* camera ) = 0;

	//! 描画終了後処理
	virtual	void	ProcAfterDrawing()	{}

	//! Matrix値を逆転置行列に変換して valに関連付けられたシェーダーパラメータにセット
	void SetIT( CGparameter val, math::Matrix44 &m )
	{
		math::Matrix44 mat_IT( m );
		//mat_IT.InverseMatrix();	// phong:コメントしてもしなくても変わらない
		//mat_IT.Transpose();

		f32 *p = mat_IT.GetMatrix().ary16;
		cgGLSetMatrixParameterfc( val, p );
	}		

	//----------------------メンバ変数-----------------------
	std::string					m_fileName;			// ファイル名
	CGprogram					m_vertexShader;		// シェーダープログラム
	CGeffect					m_cgEffect;			// エフェクト
	CGpass						m_cgPass;			// パス
	std::vector<CGtechnique>	m_cgTechnique;		// Cgのシェーダーテクニック数
	ShaderManager*				m_shaderMng;		// シェーダー管理
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 Shader();
	~Shader();
};


//=============================================================================
/*!
								シェーダー管理クラス
*/
//=============================================================================
class ShaderManager {
public:
	//-----------------------型定義--------------------------
	typedef std::map<std::string, Shader *> ShaderMap;
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 初期化
	bool		Initialize( void );

	//! エラーチェック
	bool		CheckCgError(const char *situation);
	
	//! Cgコンテキストを取得
	CGcontext	GetCgContext() { return m_cgContext; }

	//! vpプロファイルを取得
	CGprofile	GetVPProfile() { return m_vpProfile; }
	
	//! fpプロファイルを取得
	CGprofile	GetFPProfile() { return m_fpProfile; }

	//! シェーダーの読込み
	void ShaderManager::LoadShader(Shader* shader, std::string file, std::string name);

	//! シェーダーの取得
	Shader*	GetShader(std::string name) const;

	//! 全シェーダーの削除
	void		DeleteAll();

	//! シェーダー使用可能か？
	bool		Ready( void ) const	{ return m_ready;	}
	
	
private:
	//----------------------メンバ変数-----------------------
	bool								m_ready;		// シェーダーが利用可能か
	CGcontext							m_cgContext;	// Cgコンテキスト
	CGprofile							m_vpProfile;	// vpプロファイル
	CGprofile							m_fpProfile;	// fpプロファイル
	CGeffect							m_cgEffect;		// エフェクト
	std::map<std::string, Shader *>	m_shaderMap;	// 各シェーダーへのポインタ
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 ShaderManager();
	~ShaderManager();
};



}	// namespace graphics
}	// namespace nk




#endif  // __SHADER_H__