//=============================================================================
/*!	@file	layoutEventListener.h

	@brief	���C�A�E�g�C�x���g���X�i�[

	@author	ryunosuke ide
	@date	2013.06.17
*/
//=============================================================================

#ifndef __LAYOUT_EVENT_LISTENER_H__
#define __LAYOUT_EVENT_LISTENER_H__


namespace nk {
namespace graphics {

class Button;

//=============================================================================
/*!
						���C�A�E�g�C�x���g���X�i�[
*/
//=============================================================================
class LayoutEventListener {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		���ꎞ
	*/
	//===========================================================================
	virtual void	ButtonOnCursorOver( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�ޏꎞ
	*/
	//===========================================================================
	virtual void	ButtonOnCursorOut( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����J�n��)
	*/
	//===========================================================================
	virtual void	ButtonOnCursorDownStart( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����I����)
	*/
	//===========================================================================
	virtual void	ButtonOnCursorDownEnd( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����J�n��)
	*/
	//===========================================================================
	virtual void	ButtonOnCursorUpStart( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�����ꂽ�u��(�A�j���[�V�����I����)
	*/
	//===========================================================================
	virtual void	ButtonOnCursorUpEnd( nk::graphics::Button* eventButton ) {}

	//===========================================================================
	/*!	@brief		�z�[���h��
	*/
	//===========================================================================
	virtual void	ButtonOnHold( nk::graphics::Button* eventButton ) {}
	
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			LayoutEventListener();
	virtual~LayoutEventListener();
};
	
}	// namespace graphics
}	// namespace nk




#endif  // __LAYOUT_EVENT_LISTENER_H__