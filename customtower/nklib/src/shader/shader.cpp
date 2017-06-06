//=============================================================================
/*!	@file	shader.h

	@brief	シェーダー基底クラスと管理クラス

	@author	井手 竜之介
	@date	2012/02/23
	@todo	なし
	@bug	なし
*/
//=============================================================================

#include "../../include/shader/shader.h"
#include "../../include/general.h"
#include "../../include/resource/material.h"
#include "../../include/system/camera.h"

namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	なし
*/
//===========================================================================
Shader::Shader() : m_fileName(""), m_shaderMng(NULL)
{
	
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	
*/
//===========================================================================
Shader::~Shader()
{
	m_cgTechnique.clear();
	cgDestroyEffect( m_cgEffect );
}


//===========================================================================
/*!	@brief	シェーダー処理開始
	@param	なし
	@return	なし
*/
//===========================================================================
void Shader::Begin( nk::resource::Material* material, u32 teq, nk::system::Camera* camera )
{
	// シェーダーパラメータをセット
	SetParam( material, camera );

	// 頂点シェーダーとフラグメントシェーダーの
	// プロファイルを有効にする。
	cgGLEnableProfile( m_shaderMng->GetVPProfile() );
	cgGLEnableProfile( m_shaderMng->GetFPProfile() );

	// 描画パスをセットする
	m_cgPass = cgGetFirstPass( m_cgTechnique[teq] );
	cgSetPassState( m_cgPass );

}


//===========================================================================
/*!	@brief	シェーダー処理終了
	@param	なし
	@return	なし
*/
//===========================================================================
void Shader::End()
{

	cgGLUnbindProgram( m_shaderMng->GetVPProfile() );
	cgGLUnbindProgram( m_shaderMng->GetFPProfile() );
	cgGLDisableProfile( m_shaderMng->GetVPProfile() );
	cgGLDisableProfile( m_shaderMng->GetFPProfile() );

	ProcAfterDrawing();

}













//========================================================================
//	クラス：ShaderManager
//	内　容：コンストラクタ
//	引　数：なし
//	戻り値：
//	 memo ：
//========================================================================
ShaderManager::ShaderManager()
{
	m_ready		= false; 
	m_vpProfile	= CG_PROFILE_UNKNOWN;
	m_fpProfile	= CG_PROFILE_UNKNOWN;

#if 0
	//	シェーダーサポートを調べる
	//---------------------------------------

	// ARBvp1 および ARBfp1のサポートを調べる
	if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) ) {
		m_vpProfile = CG_PROFILE_ARBVP1;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) ) {
		m_fpProfile = CG_PROFILE_ARBFP1;
	}

	// VP20, FP20も調べる
	if( cgGLIsProfileSupported(CG_PROFILE_VP20) ) {
		m_vpProfile = CG_PROFILE_VP20;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP20) ) {
		m_fpProfile = CG_PROFILE_FP20;
	}

	// VP30, FP30も調べる
	if( cgGLIsProfileSupported(CG_PROFILE_VP30) ) {
		m_vpProfile = CG_PROFILE_VP30;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP30) ) {
		m_fpProfile = CG_PROFILE_FP30;
	}

	// シェーダー未サポート時は終了	
	if( m_vpProfile == CG_PROFILE_UNKNOWN || m_fpProfile == CG_PROFILE_UNKNOWN ) {
		RELEASE_PRINTF("Shader is not Supported. Application Terminated.\n");
	}
	else {
		// Cgコンテキストの作成
		m_cgContext = cgCreateContext();
		cgGLRegisterStates( m_cgContext );
		cgGLSetManageTextureParameters( m_cgContext, CG_TRUE );

		m_ready = CheckCgError("[Shader init]");
	}

#endif
	
}



//========================================================================
//	クラス：ShaderManager
//	内　容：デストラクタ
//	引　数：なし
//	戻り値：
//	 memo ：
//========================================================================
ShaderManager::~ShaderManager()
{
	// コンテキストの解放
	cgDestroyContext( m_cgContext );

}





//===========================================================================
/*!	@brief	初期化
	@param	なし
*/
//===========================================================================
bool ShaderManager::Initialize( void )
{

	//	シェーダーサポートを調べる
	//---------------------------------------

	// ARBvp1 および ARBfp1のサポートを調べる
	if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) ) {
		m_vpProfile = CG_PROFILE_ARBVP1;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) ) {
		m_fpProfile = CG_PROFILE_ARBFP1;
	}

	// VP20, FP20も調べる
	if( cgGLIsProfileSupported(CG_PROFILE_VP20) ) {
		m_vpProfile = CG_PROFILE_VP20;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP20) ) {
		m_fpProfile = CG_PROFILE_FP20;
	}

	// VP30, FP30も調べる
	if( cgGLIsProfileSupported(CG_PROFILE_VP30) ) {
		m_vpProfile = CG_PROFILE_VP30;
	}
	if( cgGLIsProfileSupported(CG_PROFILE_FP30) ) {
		m_fpProfile = CG_PROFILE_FP30;
	}

	// シェーダー未サポート時は終了	
	if( m_vpProfile == CG_PROFILE_UNKNOWN || m_fpProfile == CG_PROFILE_UNKNOWN ) {
		RELEASE_PRINTF("Shader is not Supported. Application Terminated.\n");
	}
	else {
		// Cgコンテキストの作成
		m_cgContext = cgCreateContext();
		cgGLRegisterStates( m_cgContext );
		cgGLSetManageTextureParameters( m_cgContext, CG_TRUE );

		m_ready = CheckCgError("[Shader init]");
	}

	return m_ready;
}




//===========================================================================
/*!	@brief	シェーダーを読込み
	@param	shader		: シェーダークラスへのポインタ
	@param	file		: ファイルパス
	@param	name		: シェーダー名(検索に使用)
	@return	なし
	\note	シェーダーはマネージャーでdeleteする
*/
//===========================================================================
void ShaderManager::LoadShader( Shader* shader, std::string file, std::string name )
{
	if( m_ready ) {
		
		shader->m_cgEffect = cgCreateEffectFromFile( m_cgContext, file.c_str(), NULL );
		CheckCgError( "Shader Load-Compile" );

		// シェーダーがエラーなく読めたかチェック
		if( shader->m_cgEffect == 0 ) {
			PRINTF( "\nShader Compile Error.\n" );
			SafeDelete( shader );
			return;
		}

		// 先頭テクニックを読み込む
		CGtechnique tech = cgGetFirstTechnique( shader->m_cgEffect );

		// テクニックが見つかったか？
		while( tech ) {
			if( !tech ) {
				PRINTF( "%s: No valid technique\n", file.c_str() );
				SafeDelete( shader );
				return;
			}
			tech = cgGetNextTechnique( tech );
		}

		// テクニックを登録
		tech = cgGetFirstTechnique( shader->m_cgEffect );

		while( tech ) {
			shader->m_cgTechnique.push_back( tech );
			tech = cgGetNextTechnique( tech );	
		}


		// シェーダークラスをセットアップ
		shader->m_shaderMng			= this;
		shader->m_fileName			= file;

		// シェーダーマップに追加
		m_shaderMap.insert( std::pair<std::string, Shader *>(name, shader) );

		// シェーダーを初期化
		shader->Init();
	}

	return;	
}



//===========================================================================
/*!	@brief	エラーチェック
	@param	situation	: チェック項目文字列
	@return	true		: エラー無し
	@return	false		: エラー
*/
//===========================================================================
bool ShaderManager::CheckCgError( const char *situation )
{
	CGerror err = cgGetError();

	if( err != CG_NO_ERROR ) {
		RELEASE_PRINTF( "%s : %s\n", situation, cgGetErrorString(err) );

		if( err == CG_COMPILER_ERROR ) {
			RELEASE_PRINTF( "%s\n", cgGetLastListing(m_cgContext) );
			return false;
		}
	}

	return true;
}


//===========================================================================
/*!	@brief	シェーダーの習得
	@param	検索名
	@return	シェーダー
*/
//===========================================================================
Shader* ShaderManager::GetShader( std::string name ) const
{
	ASSERT( m_ready, "shader not initialized" );
	
	if( m_ready ) {
		ShaderMap::const_iterator itr = m_shaderMap.begin();
		ShaderMap::const_iterator end = m_shaderMap.end();

		for( ; itr != end; ++itr ) {
			if( (*itr).first == name ) {
				return (*itr).second;
			}
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief	全シェーダーを削除
	@param	なし
	@return	なし
*/
//===========================================================================
void ShaderManager::DeleteAll()
{
	ShaderMap::iterator itr = m_shaderMap.begin();
	ShaderMap::iterator end = m_shaderMap.end();

	//	シェーダー全てのインスタンスを削除
	//---------------------------------------
	for( ; itr != end; itr++) {
		SafeDelete( (*itr).second );
	}
	m_shaderMap.clear();

}


}	// namespace graphics
}	// namespace nk













