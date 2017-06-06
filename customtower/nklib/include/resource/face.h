//=============================================================================
/*!	@file	face.h

	@brief	�ʃN���X

	@author	��� ���V��
	@date	2011/11/18
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __FACE_H__
#define __FACE_H__

//-------------------------------�C���N���[�h-------------------------------
#include <vector>
#include "../math/vector.h"



namespace nk {
namespace resource {

//=============================================================================
/*!
								�ʃN���X
*/
//=============================================================================
class Face {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	static const u32	ADD_ARRAY_LENGTH	= 1024;
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�N���A
	*/
	//===========================================================================
	void				Clear( void );

	/*! �ʂ�UV���Z�b�g */
	void				AddFaceUV( u32 index, const math::Vector& uv );
	void				AddFaceUV( u32 index, f32 u, f32 v );
	void				AddFace( u32 index );
	void				AddUV( const math::Vector& uv );

	/*! �ʒ��_���擾 */
	u32					GetFace( u32 index ) const;

	/*! UV���W���擾 */
	const math::Vector&	GetUV( u32 index ) const;

	/*! �ʂ��\�����钸�_�����Z�b�g(�f�t�H���g��3) */
	void				SetBundle( u32 num );

	/*! �����_��1�̖ʂ��\�����邩���擾 */
	u32					GetBundle() const;

	/*! ���_�����擾 */
	u32					GetSize() const;

private:
	//===========================================================================
	/*!	@brief		�ʐݒ�
	*/
	//===========================================================================
	void				_AddFace( u32 index );

	//===========================================================================
	/*!	@brief		UV�ݒ�
	*/
	//===========================================================================
	void				_AddUV( f32 u, f32 v );
	
private:
	//----------------------�����o�ϐ�-----------------------
	std::vector<u32>			m_faceAry;		//!< �ʔz��
	u32							m_faceAddIndex;	//!< �ʔz��i�[�C���f�b�N�X
	std::vector<math::Vector>	m_uvAry;		//!< UV�z��
	u32							m_uvAddIndex;	//!< UV�z��i�[�C���f�b�N�X
	u32							m_bundle;		// ���̒��_��1�̖ʂ��\�����邩
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 Face();
	~Face();
};


}	// namespace resource
}	// namespace nk



#endif  // __FACE_H__