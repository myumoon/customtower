//=============================================================================
/*!	@file	drawpacket.h

	@brief	描画パケットクラス

	@author	井手 竜之介
	@date	2011/11/16
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __DRAWPACKET_H__
#define __DRAWPACKET_H__

//-------------------------------インクルード-------------------------------
#include "../resource/material.h"
#include "../resource/vertex.h"
#include "../resource/texture.h"
#include "../math/matrix.h"
#include "../resource/face.h"
#include "../general.h"



namespace nk {
namespace graphics {


class RenderManager;

//=============================================================================
/*!
								描画パケットクラス
*/
//=============================================================================
class DrawPacket {
public:
	friend	RenderManager;
	
	//-----------------------型定義--------------------------
	enum {
		SPRITE_BILLBOARD	= BIT_SHIFT_LEFT(0),	//!< ビルボード
		LINE3D				= BIT_SHIFT_LEFT(1),	//!< 線(3D)
		SPRITE				= BIT_SHIFT_LEFT(2),	//!< スプライト
		MODEL				= BIT_SHIFT_LEFT(3),	//!< モデル
		MODEL_ANIMATION		= BIT_SHIFT_LEFT(4),	//!< アニメーションモデル
		LINE2D				= BIT_SHIFT_LEFT(5),	//!< 線(2D)
		
		DEAPTH_ON			= BIT_SHIFT_LEFT(5),	//!< デプス有効
		Z_BUFFER			= BIT_SHIFT_LEFT(6),	//!< Zバッファ
		SRC_ALPHA			= BIT_SHIFT_LEFT(7),	//!< 加算合成
	};
	typedef u32 DRAW_TYPE;

	//----------------------静的メンバ-----------------------
	static const u32	DEFAULT_PRIORITY;			//!< デフォルト描画優先度
	static const u32	DEFAULT_SPRITE_PRIORITY;	//!< デフォルトスプライト優先度
	static const u32	DEFAULT_LINE_PRIORITY;		//!< デフォルト線優先度
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		クリア
	*/
	//===========================================================================
	void				Clear( void );
	
	/*! テクスチャをセット */
	//void				SetTexture(const resource::Texture* tex);

	/*! テクスチャを取得 */
	//const resource::Texture*	GetTexture( void ) const;

	//! シェーダーデータをセット
	void				SetShaderData( const ShaderData& data );

	/*! マテリアルをセット */
	void				SetMaterial( const resource::Material& m );

	/*! マテリアルを取得 */
	resource::Material	GetMaterial( void ) const;

	/*! 頂点をセット */
	void				SetVertex( const resource::Vertex& v );
	void				AddVertex( const math::Vector& v );
	void				AddVertex( f32 x, f32 y, f32 z );

	/*! 頂点を取得 */
	resource::Vertex&		GetVertex( void );
	const resource::Vertex&	GetVertex( void ) const;

	/*! 面をセット */
	void				SetFace( const resource::Face& face );
	void				AddFace( u32 index, const math::Vector& uv );
	void				AddFace( u32 index, f32 u, f32 v );

	/*! 面を取得 */
	resource::Face&			GetFace( void );
	const resource::Face&	GetFace( void ) const;
	

	/*! 頂点法線をセット */
	void				SetNormalVertex( const resource::Vertex& n );

	/*! 頂点法線を習得 */
	resource::Vertex&	GetNormalVertex( void );
	
	/*! ワールドビュー変換行列をセット */
	void				SetWorldViewTransform(const math::Matrix44& mat);

	/*! ワールドビュー変換行列を取得 */
	const math::Matrix44&	GetWorldViewTransform( void ) const;
	math::Matrix44&			GetWorldViewTransform( void );

	/*! 描画タイプを設定 */
	void				SetDrawType( DRAW_TYPE type );

	/*! 描画パケットをマネージャに送る */
// 	void				SendToDrawManager( void );

	//! テクスチャ描画リストに転送
	//void				SendToDrawTextureList( void );

	//! 描画優先度を設定
	void				SetPriority( u32 num );

	//! 描画優先度を習得
	u32					GetPriority( void ) const;

	//! バッファクリアオブジェクトを挿入
// 	void				AddListForBufferClear( void );
// 
// 	bool				IsBufferClear( void ) const;

	//! スクリーンId
	void				SetScreenId( s32 screenId )					{ m_screenId = screenId; 	}
	s32					GetScreenId( void ) const					{ return m_screenId;		}
	
	//! ワールド行列
	void				SetWorldMatrix( const math::Matrix44& m )	{ m_world = m;				}
	math::Matrix44		GetWorldMatrix( void ) const				{ return m_world;			}

private:
	//----------------------メンバ変数-----------------------
	u32							m_priority;				//!< 描画優先順位
	resource::Material			m_material;				//!< マテリアル
	resource::Vertex			m_vertex;				//!< 頂点
	resource::Face				m_face;					//!< 面
	resource::Vertex			m_normal;				//!< 頂点法線
	math::Matrix44				m_worldViewTransform;	//!< ワールド変換行列
	math::Matrix44				m_world;				//!< ワールド行列
	DRAW_TYPE					m_type;					//!< 描画タイプ
	s32							m_screenId;				//!< 描画スクリーンID
	bool						m_isClearBuffer;		//!< バッファクリアフラグ

	static RenderManager*		m_drawManager;			//!< 描画マネージャ

	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 DrawPacket( void );
	 //DrawPacket( const DrawPacket& pack );
	~DrawPacket( void );
};


}	// namespace draw
}	// namespace nk







#endif  // __DRAWPACKET_H__
