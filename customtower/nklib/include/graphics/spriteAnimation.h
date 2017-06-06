/*-------------------------------------------------------------------------
	���@���F�X�v���C�g�A�j���[�V�����N���X
	�쐬���F2011/01/23
	�X�V���F2011/01/23
--------------------------------------------------------------------------*/

#ifndef __SPRITEANIMATION_H__
#define __SPRITEANIMATION_H__

#include "./sprite.h"

namespace nk {
namespace graphics {

	
/*----------------------------------*/
/*	�X�v���C�g�A�j���[�V�����N���X	*/
/*----------------------------------*/
class SpriteAnimation : public Sprite {
public:
	//	������
	//---------------------------------------
	void Init();	
	void Init( const char *tex_path, int frame_w, int frame_h, int row, int col, int update_frame, bool loop = false );

	//	�R�}�����w��
	//---------------------------------------
	void SetFrame(int row, int col = 1);

	//	�Đ�����A�j���[�V������ݒ�i�摜�̍���0�Ƃ��ĉ��Ԗڂ̂���j
	//---------------------------------------
	void SetPlayAnimation(int num);

	//	�X�V�p�x��ݒ�
	//---------------------------------------
	void SetUpdateFrequency(int frame)
	{
		if( frame < 1 ) { frame = 1; }
		m_update_frequency = frame;
	}
	
	//===========================================================================
	/*!	@brief		�Đ��J�n
	*/
	//===========================================================================	
	void	Start( u32 startFrame = 0 );

	//===========================================================================
	/*!	@brief		��~
	*/
	//===========================================================================	
	void	Stop( void );

	//===========================================================================
	/*!	@brief		�|�[�Y
	*/
	//===========================================================================
	void	Pause( void );

	//===========================================================================
	/*!	@brief		�ĊJ
	*/
	//===========================================================================
	void	Resume( void );

	

	//	�A�j���[�V���������[�v������
	//---------------------------------------
	void 	SetAnimationLoop( bool flag = true );

	//	�X�V
	//---------------------------------------
	void 	Update();

	//	�I��������
	//---------------------------------------
	bool 	IsEnd() const { return !m_play; }

	//===========================================================================
	/*!	@brief		�s��擾
	*/
	//===========================================================================
	u32		GetRow( void ) const;
	u32		GetCol( void ) const;

private:
	//	�f�[�^
	//---------------------------------------
	int			m_play_animation;		// ���ݍĐ����̃A�j���[�V����
	int			m_row;					// �c�����̃R�}��
	int			m_col;					// �������̃R�}��
	int			m_update_frequency;		// �X�V�p�x
	bool		m_play;					// �A�j���[�V�����J�n�t���O
	bool		m_loop;					// �A�j���[�V�������[�v�t���O
	f32			m_width;				//!< �\����
	f32			m_height;				//!< �\������
	f32			m_tex_u;				//!< U
	f32			m_tex_v;				//!< V

	int			m_play_cnt;				// �Đ��J�E���^

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
	 SpriteAnimation( const char *tex_path, int frame_w, int frame_h, int row, int col, int update_frame, bool loop = false );
	 SpriteAnimation();
	~SpriteAnimation();

};
	

}	// namespace graphics
}	// namespace nk

#endif  // __SPRITEANIMATION_H__