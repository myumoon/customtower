//=============================================================================
/*!	@file	attitude.h

	@brief	姿勢行列生成クラス

	@author	井手 竜之介
	@date	2011/11/25
	@todo	なし
	@bug	なし
*/
//=============================================================================


#ifndef __ATTITUDE_H__
#define __ATTITUDE_H__

//-------------------------------インクルード-------------------------------
#include "../math/matrix.h"
#include "../math/vector.h"



namespace nk {
namespace graphics {


//=============================================================================
/*!
								姿勢クラス
*/
//=============================================================================
class Attitude {
public:
	//-----------------------型定義--------------------------
	//enum ROTATE_FLAG {
	//	FLAG_NONE,			// 無し
	//	FLAG_ROTATE_XYZ,	// XYZ軸を基準に回転
	//	FLAG_ROTATE_AXIS,	// 軸中心で回転
	//};
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//! 姿勢行列を取得
	math::Matrix44	GetAttitudeMatrix() const;

	//! 位置をセット
	void			SetPos( const math::Vector& pos );
	void			AddPos( const math::Vector& pos );

	//! スケールをセット
	void			SetScale( const math::Vector& scale );
	void			SetScale( f32 scale );
	void			AddScale( f32 scale );
 
	//! 回転量をセット
	//void			SetRotate(const math::Vector& rot);
	void			SetRotate( f32 amount, const math::Vector& axis );
	void			AddRotate( f32 amount, const math::Vector& axis );
	
private:
	//----------------------メンバ変数-----------------------
	//f32			m_rotate;		//!< 回転量
	//math::Vector	m_rotAxis;		//!< 回転軸
	math::Matrix44	m_rotate;		//!< 回転
	math::Vector	m_scale;		//!< スケール
	math::Vector	m_pos;			//!< 位置
	//ROTATE_FLAG		m_rotFlag;		//!< 回転方法フラグ
	
	
	//-----------------------メソッド------------------------
	
public:
	//-------------コンストラクタ・デストラクタ--------------
	 Attitude();
	~Attitude();
};

}	// namespace graphics
}	// namespace nk



#endif  // __ATTITUDE_H__