/*-------------------------------------------------------------------------
	���@���F�X�v���C�g�A�j���[�V�����N���X
	�쐬���F2011/01/23
	�X�V���F2011/01/23
--------------------------------------------------------------------------*/

//#include "stdafx.h"
#include "../../include/graphics/spriteAnimation.h"



namespace nk {
namespace graphics {


//========================================================================
//	�N���X�FSpriteAnimation
//	���@�e�F�R���X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F
//	 memo �F
//========================================================================
SpriteAnimation::SpriteAnimation() : Sprite()
{

	Init();

}


//========================================================================
//	�N���X�FSpriteAnimation
//	���@�e�F�R���X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F
//	 memo �F
//========================================================================
SpriteAnimation::SpriteAnimation( const char *tex_path, int frame_w, int frame_h, int row, int col, int update_frame, bool loop )
{

	Init();
	Init( tex_path, frame_w, frame_h, row, col, update_frame, loop );

}



//========================================================================
//	�N���X�FSpriteAnimation
//	���@�e�F�f�X�g���N�^
//	���@���F�Ȃ�
//	�߂�l�F
//	 memo �F
//========================================================================
SpriteAnimation::~SpriteAnimation()
{


}


//========================================================================
//	�N���X�FSpriteAnimation
//	���@�e�F������
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
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
//	�N���X�FSpriteAnimation
//	���@�e�F������
//	���@���Ftex_path	: �e�N�X�`���p�X
//			frame_w		: 1�R�}������̉摜��
//			frame_h		: 1�R�}������̉摜��
//			row			: �c�����̃R�}��
//			col			: �������̃R�}��
//			update_frame: �X�V�p�x	
//			loop		: ���[�v�����邩
//	�߂�l�F�Ȃ�
//	 memo �F
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

	// �p�X���Ă��Ԉ���Ă��
	NULL_ASSERT( tex_path );
}


//===========================================================================
/*!	@brief		�A�j���[�V�������[�v�ݒ�
	@param		loop	���[�v
	@return		----
*/
//===========================================================================
void SpriteAnimation::SetAnimationLoop( bool loop )
{
	m_loop = loop;
	
}


//========================================================================
//	�N���X�FSpriteAnimation
//	���@�e�F�R�}����ݒ�
//	���@���Frow		: �c����
//			col		: ������
//	�߂�l�F�Ȃ�
//	 memo �F
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
//	�N���X�FSpriteAnimation
//	���@�e�F�Đ�����A�j���[�V������ݒ�
//	���@���Fnum		: �摜�̍����琔���ĉ��R�}�ڂ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void SpriteAnimation::SetPlayAnimation(int num)
{
	if( num < 0 ) {
		num = 0;
	}

	m_play_animation = num;

}

//========================================================================
//	�N���X�FSpriteAnimation
//	���@�e�F�X�V
//	���@���F�Ȃ�
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void SpriteAnimation::Update()
{
	if( !m_play || !m_texture ) {
		return;
	}

	m_play_cnt++;


	/* �Đ��A�j���[�V������ݒ� */
	m_tex_u = (float)m_width / m_texture->GetWidth() * m_play_animation;

	/* �\���摜�ؑւ� */
	if( m_play_cnt % m_update_frequency == 0 ) {
		m_tex_v += (float)m_height / m_texture->GetHeight();
	}

	/* �A�j���[�V�����̏I�� */
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
/*!	@brief		�Đ�
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
/*!	@brief		��~
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
/*!	@brief		�ꎞ��~
	@param		----
	@return		----
*/
//===========================================================================
void SpriteAnimation::Pause( void )
{
	m_play 		= false;
	
}



//===========================================================================
/*!	@brief		�ĊJ
	@param		----
	@return		----
*/
//===========================================================================
void SpriteAnimation::Resume( void )
{
	m_play 		= true;
	
}



//===========================================================================
/*!	@brief		�s�擾
	@param		----
	@return		----
*/
//===========================================================================
u32 SpriteAnimation::GetRow( void ) const
{
	
	return m_row;
}

//===========================================================================
/*!	@brief		��擾
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