//=============================================================================
/*!	@file	cameraManager.h

	@brief	�J�����Ǘ�

	@author	ryunosuke ide
	@date	2013.06.28
*/
//=============================================================================


#ifndef __CAMERA_MANAGER_H__
#define __CAMERA_MANAGER_H__

#include <list>
#include "../typedef.h"
#include "../math/vector.h"
#include "../math/matrix.h"
#include "./camera.h"


namespace nk {

namespace system {

//=============================================================================
/*!
								�J�����}�l�[�W��
*/
//=============================================================================
class CameraManager {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	static const f32	DEFAULT_FIELD_OF_VISION;	//!< �f�t�H���g����p(60)
	static const f32	DEFAULT_NEAR_DISTANCE;		//!< �f�t�H���g�̌����n�߂鋗��(0.1f)
	static const f32	DEFAULT_FAR_DISTANCE;		//!< �f�t�H���g�̃J�������͂�����(1000.0f)
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		������
	*/
	//===========================================================================
	bool			Initialize( void );

	//===========================================================================
	/*!	@brief		���ݎg�p���̃J�����s����擾
	*/
	//===========================================================================
	math::Matrix44	GetUseCameraMatrix( void ) const;

	//===========================================================================
	/*!	@brief		�g�p�J������ύX
	*/
	//===========================================================================
	void			ChangeCamera( CAMERA_ID id );

	//===========================================================================
	/*!	@brief		�J�������擾
	*/
	//===========================================================================
	Camera*			GetCamera( CAMERA_ID id );
	Camera*			GetUseCamera( void ) const;

	//===========================================================================
	/*!	@brief		�g�p���J�����̌����n�߂�܂ł̋������擾
	*/
	//===========================================================================
	f32				GetCurrentNearDistance( void ) const;

	//===========================================================================
	/*!	@brief		�g�p���J�����̌����Ȃ��Ȃ�܂ł̋������擾
	*/
	//===========================================================================
	f32				GetCurrentFarDistance( void ) const;

	//===========================================================================
	/*!	@brief		�g�p���J�����̎���p���擾
	*/
	//===========================================================================
	f32				GetCurrentFieldOfVision( void ) const;
	

	//===========================================================================
	/*!	@brief	�V�����J�����𐶐�		
		@param	near			�����n�߂鋗��
		@param	far				�����Ȃ��Ȃ鋗��
		@param	fieldOfView		����p
		@return	�J����ID
		@note	T:��������J����
	*/
	//===========================================================================
	template<class T>
	T* CreateCamera(
		f32 near 			= DEFAULT_NEAR_DISTANCE,
		f32 far 			= DEFAULT_FAR_DISTANCE,
		f32 fieldOfVision 	= DEFAULT_FIELD_OF_VISION
	)
	{
		T*	ins		= new T;
		m_useCamera = ins;
		m_useCamera->Initialize( near, far, fieldOfVision );
		m_cameraList.push_back( m_useCamera );

		return ins;
	}
	
	template<class T>
	T* CreateCamera(
		const math::Vector& pos,
		const math::Vector& look,
		const math::Vector& top,
		f32	nearDistance	= DEFAULT_NEAR_DISTANCE,
		f32 farDistance		= DEFAULT_FAR_DISTANCE,
		f32 fieldOfVision	= DEFAULT_FIELD_OF_VISION
	)
	{
		T*	ins		= new T;
		m_useCamera = ins;
		m_useCamera->Initialize( nearDistance, farDistance, fieldOfVision );
		m_useCamera->SetPos( pos );
		m_useCamera->SetLook( look );
		m_useCamera->SetTop( top );
		m_cameraList.push_back( m_useCamera );

		return ins;
	}

	//===========================================================================
	/*!	@brief		�J������ǉ�
	*/
	//===========================================================================
	void	AddControlCamera( Camera* addCamera );

private:
	//----------------------�����o�ϐ�-----------------------
	std::list<Camera*>		m_cameraList;	//!< �J�������X�g
	Camera*					m_useCamera;	//!< �g�p���J����

	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 CameraManager();
	~CameraManager();
};

	
}	// namespace system
	
}	// namespace nk




#endif  // __CAMERA_MANAGER_H__