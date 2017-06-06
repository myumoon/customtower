/*-------------------------------------------------------------------------
	説　明：スプライトアニメーションクラス
	作成日：2011/01/23
	更新日：2011/01/23
--------------------------------------------------------------------------*/

//#include "stdafx.h"
#include "../../include/graphics/spriteAnimation.h"



namespace nk {
namespace graphics {


//========================================================================
//	クラス：SpriteAnimation
//	内　容：コンストラクタ
//	引　数：なし
//	戻り値：
//	 memo ：
//========================================================================
SpriteAnimation::SpriteAnimation() : Sprite()
{

	Init();

}


//========================================================================
//	クラス：SpriteAnimation
//	内　容：コンストラクタ
//	引　数：なし
//	戻り値：
//	 memo ：
//========================================================================
SpriteAnimation::SpriteAnimation( const char *tex_path, int frame_w, int frame_h, int row, int col, int update_frame, bool loop )
{

	Init();
	Init( tex_path, frame_w, frame_h, row, col, update_frame, loop );

}



//========================================================================
//	クラス：SpriteAnimation
//	内　容：デストラクタ
//	引　数：なし
//	戻り値：
//	 memo ：
//========================================================================
SpriteAnimation::~SpriteAnimation()
{


}


//========================================================================
//	クラス：SpriteAnimation
//	内　容：初期化
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
void SpriteAnimation::Init()
{

	m_play_animation = 0;
	m_row = 1;
	m_col = 1;
	m_update_frequency = 1;
	m_play = false;
	m_loop = false;

	m_play_cnt = 0;
}



//========================================================================
//	クラス：SpriteAnimation
//	内　容：初期化
//	引　数：tex_path	: テクスチャパス
//			frame_w		: 1コマあたりの画像幅
//			frame_h		: 1コマあたりの画像高
//			row			: 縦方向のコマ数
//			col			: 横方向のコマ数
//			update_frame: 更新頻度	
//			loop		: ループさせるか
//	戻り値：なし
//	 memo ：
//========================================================================
void SpriteAnimation::Init(const char *tex_path, int frame_w, int frame_h, int row, int col, int update_frame, bool loop)
{
	m_texture = m_resourceMng->GetTexture( tex_path );
	SetFrame( row, col );
	SetUpdateFrequency( update_frame );
	SetAnimationLoop( loop );
	m_width		= static_cast<f32>( frame_w );
	m_height	= static_cast<f32>( frame_h );
	m_tex_u		= 0.0f;
	m_tex_v		= 0.0f;
	//SetWH( frame_w, frame_h );
	//SetUVWH( 0, 0, frame_w / m_texture->GetWidth(), frame_h / m_texture->GetHeight() );

	// パスしてい間違ってるよ
	NULL_ASSERT( tex_path );
}


//===========================================================================
/*!	@brief		アニメーションループ設定
	@param		loop	ループ
	@return		----
*/
//===========================================================================
void SpriteAnimation::SetAnimationLoop( bool loop )
{
	m_loop = loop;
	
}


//========================================================================
//	クラス：SpriteAnimation
//	内　容：コマ数を設定
//	引　数：row		: 縦方向
//			col		: 横方向
//	戻り値：なし
//	 memo ：
//========================================================================
void SpriteAnimation::SetFrame(int row, int col)
{

	m_row = row;
	m_col = col;

	if( m_texture && col == 1 ) {
		m_height = static_cast<f32>( m_texture->GetWidth() );
	}

}



//========================================================================
//	クラス：SpriteAnimation
//	内　容：再生するアニメーションを設定
//	引　数：num		: 画像の左から数えて何コマ目か
//	戻り値：なし
//	 memo ：
//========================================================================
void SpriteAnimation::SetPlayAnimation(int num)
{
	if( num < 0 ) {
		num = 0;
	}

	m_play_animation = num;

}

//========================================================================
//	クラス：SpriteAnimation
//	内　容：更新
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
void SpriteAnimation::Update()
{
	if( !m_play || !m_texture ) {
		return;
	}

	m_play_cnt++;


	/* 再生アニメーションを設定 */
	m_tex_u = (float)m_width / m_texture->GetWidth() * m_play_animation;

	/* 表示画像切替え */
	if( m_play_cnt % m_update_frequency == 0 ) {
		m_tex_v += (float)m_height / m_texture->GetHeight();
	}

	/* アニメーションの終了 */
	if( m_row * m_update_frequency <= m_play_cnt ) {
		if( m_loop ) {
			m_play_cnt = 0;
			m_tex_v = 0.0f;
		} else {
			m_play = false;
		}
	}

	SetUVWH( m_tex_u, m_tex_v, m_width / m_texture->GetWidth(), m_height / m_texture->GetHeight() );

}

//===========================================================================
/*!	@brief		再生
	@param		----
	@return		----
*/
//===========================================================================
void SpriteAnimation::Start( u32 startFrame )
{
	m_play 		= true;
	m_play_cnt	= m_update_frequency * startFrame;
	
}



//===========================================================================
/*!	@brief		停止
	@param		----
	@return		----
*/
//===========================================================================
void SpriteAnimation::Stop( void )
{
	m_play 		= false;
	m_play_cnt	= 0;
	
}


//===========================================================================
/*!	@brief		一時停止
	@param		----
	@return		----
*/
//===========================================================================
void SpriteAnimation::Pause( void )
{
	m_play 		= false;
	
}



//===========================================================================
/*!	@brief		再開
	@param		----
	@return		----
*/
//===========================================================================
void SpriteAnimation::Resume( void )
{
	m_play 		= true;
	
}



//===========================================================================
/*!	@brief		行取得
	@param		----
	@return		----
*/
//===========================================================================
u32 SpriteAnimation::GetRow( void ) const
{
	
	return m_row;
}

//===========================================================================
/*!	@brief		列取得
	@param		----
	@return		----
*/
//===========================================================================
u32 SpriteAnimation::GetCol( void ) const
{
	
	return m_col;
}



}	// namespace graphics
}	// namespac nk