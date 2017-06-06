//=============================================================================
/*!	@file	material.h

	@brief	マテリアルクラス

	@author	井手 竜之介
	@date	2011/11/15
	@todo	シェーダーをメンバに入れる
	@bug	なし
*/
//=============================================================================

#ifndef __MATERIAL_H__
#define __MATERIAL_H__


//-------------------------------インクルード-------------------------------
#include "../math/vector.h"
#include "./texture.h"
#include "../graphics/color.h"
#include "../shader/shader.h"



namespace nk {

namespace resource {

//=============================================================================
/*!
								マテリアルクラス
*/
//=============================================================================
class Material {
public:
	//-----------------------型定義--------------------------
	//! UV座標格納構造体
	struct UV {
		f32	u;
		f32	v;
	};
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		クリア
	*/
	//===========================================================================
	void				Clear( void );

	//! テクスチャ
	void				SetTexture( const Texture* tex );
	const Texture*		GetTexture() const;

	//! マテリアル番号
	void				SetMaterialNum( u32 num );
	u32					GetMaterialNum() const;

	//! 色
	void				SetColor( const Color& color );
	Color				GetColor() const;

	//! ディフューズ
	void				SetDiffuse( const Color& dif );
	Color				GetDiffuse() const;

	//! アンビエント
	void				SetAmbient( const Color& amb );
	Color				GetAmbient() const;

	//! スペキュラー
	void				SetSpecular( const Color& spec );
	Color				GetSpecular() const;

	//! シェーダーをセット
	void				SetShaderData( const graphics::ShaderData& data );
	
	//! シェーダーデータを習得
	graphics::ShaderData	GetShaderData() const;
	
private:
	//----------------------メンバ変数-----------------------
	u32						m_materialNum;	//!< マテリアル番号
	Color					m_color;		//!< 頂点ごとの色を格納する配列
	const Texture*			m_texture;		//!< テクスチャ
	Color					m_diffuse;		//!< ディフューズ
	Color					m_ambient;		//!< アンビエント
	Color					m_specular;		//!< スペキュラー
	//graphics::Shader*		m_shader;		//!< シェーダーを入れる予定
	graphics::ShaderData	m_shaderData;	//!< シェーダーに使用するデータ
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			 Material();
			 Material( const Material& obj );
	virtual ~Material();
};

}	// namespace resource

}	// namespace nk




//static const s32 FACE_VERTEX;		//!< 何頂点で1つの面を構成するか
//std::vector<nk::math::Vector>		m_index;	//!< 面を構成する頂点配列
//std::vector<UV>							m_uv;		//!< UV座標格納配列
//std::string				m_key;			// 検索キー
//s32					   *m_index;		// 頂点インデックス配列
//s32						m_index_idx;	// 現在操作している配列のインデックス
//tUV					   *m_uv;			// UV配列
//s32						m_uv_idx;		// 現在操作しているUV配列のインデックス
//s32						m_face_max;		// 面の数
//Color					m_color;		// 色
//CTexture			   *m_texture;		// テクスチャ

#if 0
/*----------------------------------*/
/*		マテリアルクラス			*/
/*----------------------------------*/
class CMaterial {
public:

	//	定数
	//---------------------------------------
	static const s32 FACE_SET;		// 何頂点で1つの面を構成するか


	//	UV構造体
	//---------------------------------------
	struct tUV {
		f32 u;
		f32 v;
	};


	//	コンストラクタ・デストラクタ
	//---------------------------------------
	 CMaterial();
	~CMaterial();


	//	初期化
	//---------------------------------------
	void Init();

	//	UV配列のインデックスを初期化
	//---------------------------------------
	void InitUVIndex() { m_uv_idx = 0; }


	//	面の数をセット
	//---------------------------------------
	void SetFaceNum(s32 num);

	//	識別キーをセット
	//---------------------------------------
	void SetKey(std::string key);

	//	頂点インデックスをセット
	//---------------------------------------
	void SetIndex(s32 num);

	//	UV座標をセット
	//---------------------------------------
	void SetUV(f32 u, f32 v);

	//	色のセット
	//---------------------------------------
	void SetColor(const Color& color)
	{
		m_color = color;
	}
	void SetColor(f32 r, f32 g, f32 b, f32 a = 1.0f)
	{
		m_color.Set(r, g, b, a);
	}

	//	テクスチャをセット
	//---------------------------------------
	void SetTexture(CTexture *texture);


	//	識別キーの取得
	//---------------------------------------
	const std::string& GetKey() const { return m_key; }

	//	頂点インデックスの取得
	//---------------------------------------
	const s32& GetIndex(s32 idx) const { return m_index[idx]; }

	//	U座標の取得
	//---------------------------------------
	const f32& GetU(s32 idx) const { return m_uv[idx].u; }

	//	V座標の取得
	//---------------------------------------
	const f32& GetV(s32 idx) const { return m_uv[idx].v; }

	//	色の取得
	//---------------------------------------
	const Color& GetColor() const { return m_color; }

	//	テクスチャの取得
	//---------------------------------------
	const CTexture *GetTexture() const { return m_texture; }

	//	インデックス配列のサイズを取得
	//---------------------------------------
	s32 GetIndexLength() const { return m_face_max * FACE_SET; }


	//	簡易表示
	//---------------------------------------
	void Disp();

private:
	
	//	データ
	//---------------------------------------
	std::string				m_key;			// 検索キー
	s32					   *m_index;		// 頂点インデックス配列
	s32						m_index_idx;	// 現在操作している配列のインデックス
	tUV					   *m_uv;			// UV配列
	s32						m_uv_idx;		// 現在操作しているUV配列のインデックス
	s32						m_face_max;		// 面の数
	Color					m_color;		// 色
	CTexture			   *m_texture;		// テクスチャ
};


#endif







#endif  // __MATERIAL_H__
