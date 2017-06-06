//=============================================================================
/*!	@file	flickMoveCamera.h

	@brief	�t���b�N�ړ��J����

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================


#ifndef __FLICK_MOVE_CAMERA_H__
#define __FLICK_MOVE_CAMERA_H__

#include <vector>
#include "system/camera.h"
#include "input/mouse.h"
#include "input/flick.h"
#include "math/math.h"


//=============================================================================
/*!
							�t���b�N�ړ��J����
*/
//=============================================================================
class FlickMoveCamera : public nk::system::NormalCamera {
protected:
	typedef std::vector<nk::input::Mouse::MOUSE_NUM>	VecCheckButton;
	
	static const	f32	FLICK_DECELERATION;				//!< ������
	static const	f32	DEFAULT_ZOOM_SPEED;				//!< �Y�[�����̑��x
	static const	f32	DEFAULT_FIELD_OF_VISION;		//!< �f�t�H���g����p
	static const	f32	DEFAULT_MAX_FIELD_OF_VISION;	//!< �ő压��p
	static const	f32	DEFAULT_MIN_FIELD_OF_VISION;	//!< �ŏ�����p
	static const	f32	FLICK_SPEED;					//!< �t���b�N���x
	
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	virtual void	Initialize( const nk::input::Mouse* mouse, nk::input::Mouse::MOUSE_NUM button );

	//===========================================================================
	/*!	@brief		�X�V
	*/
	//===========================================================================
	virtual void	Update( void );

	//===========================================================================
	/*!	@brief		�Y�[�����x�ݒ�
	*/
	//===========================================================================
	virtual void	SetZoomSpeed( f32 speed );
	
	//===========================================================================
	/*!	@brief		�Y�[�����x�擾
	*/
	//===========================================================================
	virtual f32		GetZoomSpeed( void ) const;
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	const nk::input::Mouse*		m_mouse;		//!< �}�E�X
	nk::input::Flick			m_flick;		//!< �t���b�N
// 	VecCheckButton				m_checkButton;	//!< �Ď��{�^��
	u32							m_checkButton;	//!< �Ď��{�^��
	f32							m_zoomSpeed;	//!< �Y�[�����x
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			FlickMoveCamera();
	virtual~FlickMoveCamera();
};



#endif  // __FLICK_MOVE_CAMERA_H__