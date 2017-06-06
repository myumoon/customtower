//=============================================================================
/*!	@file	material.h

	@brief	�}�e���A���N���X

	@author	��� ���V��
	@date	2011/11/15
	@todo	�V�F�[�_�[�������o�ɓ����
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __MATERIAL_H__
#define __MATERIAL_H__


//-------------------------------�C���N���[�h-------------------------------
#include "../math/vector.h"
#include "./texture.h"
#include "../graphics/color.h"
#include "../shader/shader.h"



namespace nk {

namespace resource {

//=============================================================================
/*!
								�}�e���A���N���X
*/
//=============================================================================
class Material {
public:
	//-----------------------�^��`--------------------------
	//! UV���W�i�[�\����
	struct UV {
		f32	u;
		f32	v;
	};
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�N���A
	*/
	//===========================================================================
	void				Clear( void );

	//! �e�N�X�`��
	void				SetTexture( const Texture* tex );
	const Texture*		GetTexture() const;

	//! �}�e���A���ԍ�
	void				SetMaterialNum( u32 num );
	u32					GetMaterialNum() const;

	//! �F
	void				SetColor( const Color& color );
	Color				GetColor() const;

	//! �f�B�t���[�Y
	void				SetDiffuse( const Color& dif );
	Color				GetDiffuse() const;

	//! �A���r�G���g
	void				SetAmbient( const Color& amb );
	Color				GetAmbient() const;

	//! �X�y�L�����[
	void				SetSpecular( const Color& spec );
	Color				GetSpecular() const;

	//! �V�F�[�_�[���Z�b�g
	void				SetShaderData( const graphics::ShaderData& data );
	
	//! �V�F�[�_�[�f�[�^���K��
	graphics::ShaderData	GetShaderData() const;
	
private:
	//----------------------�����o�ϐ�-----------------------
	u32						m_materialNum;	//!< �}�e���A���ԍ�
	Color					m_color;		//!< ���_���Ƃ̐F���i�[����z��
	const Texture*			m_texture;		//!< �e�N�X�`��
	Color					m_diffuse;		//!< �f�B�t���[�Y
	Color					m_ambient;		//!< �A���r�G���g
	Color					m_specular;		//!< �X�y�L�����[
	//graphics::Shader*		m_shader;		//!< �V�F�[�_�[������\��
	graphics::ShaderData	m_shaderData;	//!< �V�F�[�_�[�Ɏg�p����f�[�^
	
	
	//-----------------------���\�b�h------------------------
	
public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 Material();
			 Material( const Material& obj );
	virtual ~Material();
};

}	// namespace resource

}	// namespace nk




//static const s32 FACE_VERTEX;		//!< �����_��1�̖ʂ��\�����邩
//std::vector<nk::math::Vector>		m_index;	//!< �ʂ��\�����钸�_�z��
//std::vector<UV>							m_uv;		//!< UV���W�i�[�z��
//std::string				m_key;			// �����L�[
//s32					   *m_index;		// ���_�C���f�b�N�X�z��
//s32						m_index_idx;	// ���ݑ��삵�Ă���z��̃C���f�b�N�X
//tUV					   *m_uv;			// UV�z��
//s32						m_uv_idx;		// ���ݑ��삵�Ă���UV�z��̃C���f�b�N�X
//s32						m_face_max;		// �ʂ̐�
//Color					m_color;		// �F
//CTexture			   *m_texture;		// �e�N�X�`��

#if 0
/*----------------------------------*/
/*		�}�e���A���N���X			*/
/*----------------------------------*/
class CMaterial {
public:

	//	�萔
	//---------------------------------------
	static const s32 FACE_SET;		// �����_��1�̖ʂ��\�����邩


	//	UV�\����
	//---------------------------------------
	struct tUV {
		f32 u;
		f32 v;
	};


	//	�R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------
	 CMaterial();
	~CMaterial();


	//	������
	//---------------------------------------
	void Init();

	//	UV�z��̃C���f�b�N�X��������
	//---------------------------------------
	void InitUVIndex() { m_uv_idx = 0; }


	//	�ʂ̐����Z�b�g
	//---------------------------------------
	void SetFaceNum(s32 num);

	//	���ʃL�[���Z�b�g
	//---------------------------------------
	void SetKey(std::string key);

	//	���_�C���f�b�N�X���Z�b�g
	//---------------------------------------
	void SetIndex(s32 num);

	//	UV���W���Z�b�g
	//---------------------------------------
	void SetUV(f32 u, f32 v);

	//	�F�̃Z�b�g
	//---------------------------------------
	void SetColor(const Color& color)
	{
		m_color = color;
	}
	void SetColor(f32 r, f32 g, f32 b, f32 a = 1.0f)
	{
		m_color.Set(r, g, b, a);
	}

	//	�e�N�X�`�����Z�b�g
	//---------------------------------------
	void SetTexture(CTexture *texture);


	//	���ʃL�[�̎擾
	//---------------------------------------
	const std::string& GetKey() const { return m_key; }

	//	���_�C���f�b�N�X�̎擾
	//---------------------------------------
	const s32& GetIndex(s32 idx) const { return m_index[idx]; }

	//	U���W�̎擾
	//---------------------------------------
	const f32& GetU(s32 idx) const { return m_uv[idx].u; }

	//	V���W�̎擾
	//---------------------------------------
	const f32& GetV(s32 idx) const { return m_uv[idx].v; }

	//	�F�̎擾
	//---------------------------------------
	const Color& GetColor() const { return m_color; }

	//	�e�N�X�`���̎擾
	//---------------------------------------
	const CTexture *GetTexture() const { return m_texture; }

	//	�C���f�b�N�X�z��̃T�C�Y���擾
	//---------------------------------------
	s32 GetIndexLength() const { return m_face_max * FACE_SET; }


	//	�ȈՕ\��
	//---------------------------------------
	void Disp();

private:
	
	//	�f�[�^
	//---------------------------------------
	std::string				m_key;			// �����L�[
	s32					   *m_index;		// ���_�C���f�b�N�X�z��
	s32						m_index_idx;	// ���ݑ��삵�Ă���z��̃C���f�b�N�X
	tUV					   *m_uv;			// UV�z��
	s32						m_uv_idx;		// ���ݑ��삵�Ă���UV�z��̃C���f�b�N�X
	s32						m_face_max;		// �ʂ̐�
	Color					m_color;		// �F
	CTexture			   *m_texture;		// �e�N�X�`��
};


#endif







#endif  // __MATERIAL_H__
