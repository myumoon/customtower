//=============================================================================
/*!	@file	face.h

	@brief	面クラス

	@author	井手 竜之介
	@date	2011/11/18
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __FACE_H__
#define __FACE_H__

//-------------------------------インクルード-------------------------------
#include <vector>
#include "../math/vector.h"



namespace nk {
namespace resource {

//=============================================================================
/*!
								面クラス
*/
//=============================================================================
class Face {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	static const u32	ADD_ARRAY_LENGTH	= 1024;
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		クリア
	*/
	//===========================================================================
	void				Clear( void );

	/*! 面とUVをセット */
	void				AddFaceUV( u32 index, const math::Vector& uv );
	void				AddFaceUV( u32 index, f32 u, f32 v );
	void				AddFace( u32 index );
	void				AddUV( const math::Vector& uv );

	/*! 面頂点を取得 */
	u32					GetFace( u32 index ) const;

	/*! UV座標を取得 */
	const math::Vector&	GetUV( u32 index ) const;

	/*! 面を構成する頂点数をセット(デフォルトで3) */
	void				SetBundle( u32 num );

	/*! 何頂点で1つの面を構成するかを取得 */
	u32					GetBundle() const;

	/*! 頂点数を取得 */
	u32					GetSize() const;

private:
	//===========================================================================
	/*!	@brief		面設定
	*/
	//===========================================================================
	void				_AddFace( u32 index );

	//===========================================================================
	/*!	@brief		UV設定
	*/
	//===========================================================================
	void				_AddUV( f32 u, f32 v );
	
private:
	//----------------------メンバ変数-----------------------
	std::vector<u32>			m_faceAry;		//!< 面配列
	u32							m_faceAddIndex;	//!< 面配列格納インデックス
	std::vector<math::Vector>	m_uvAry;		//!< UV配列
	u32							m_uvAddIndex;	//!< UV配列格納インデックス
	u32							m_bundle;		// 何個の頂点で1つの面を構成するか
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 Face();
	~Face();
};


}	// namespace resource
}	// namespace nk



#endif  // __FACE_H__