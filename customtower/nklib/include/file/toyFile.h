//=============================================================================
/*!	@file	toyFile.h

	@brief	Toystudio�t�@�C����Ǎ��݁E�Ǘ�����

	@author	��� ���V��
	@date	2011/12/01
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __TOYFILE_H__
#define __TOYFILE_H__


//-------------------------------�C���N���[�h-------------------------------
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "../resource/vertex.h"
#include "../resource/face.h"
#include "../resource/material.h"


namespace nk {

namespace resource {

class	ResourceManager;


//=============================================================================
/*!
								Toystudio���[�h�N���X
*/
//=============================================================================
class LoadToyFile {
private:
	friend	class	ToyFile;

	//-----------------------�^��`--------------------------
	enum { STR_BUF_START_IDX = -1 };			// �C���f�b�N�X�J�E���g�J�n���̒l

	struct _Property {
		std::string					attribute;	// ����
		std::string					value;		// �l
	};
	
	struct _Tag {
		std::string					tagName;	// �^�O��
		std::vector<_Property>		pro;		// �v���p�e�B
		std::string					value;		// �^�O�̒��g�̕���
		bool						close;		// �����Ă��邩
		std::vector<_Tag*>			tree;		// �c���[�\��
		_Tag*						prev;		// ���̃^�O���������Ă���^�O�ւ̃|�C���^

		/* �v���p�e�B�̒��g���擾 */
		std::string GetPropertyValue(std::string attribute)
		{
			for(u32 i = 0; i < pro.size(); ++i) {
				if( pro[i].attribute == attribute ) {
					return pro[i].value;
				}
			}
			return std::string("");
		}

		/* �c���[����w�肳�ꂽ�^�O���擾(�ŏ��Ɍ����������) */
		_Tag* GetTagFromTree(std::string tagName)
		{
			_Tag*		retTag	= NULL;
			u32	size	= tree.size();
			for(u32 i = 0; i < size; ++i) {
				if( tree[i]->tagName == tagName ) {
					retTag = tree[i];
					break;
				}
			}
			return retTag;
		}
	};

public:

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------
	
	//! ���[�h
	void		Load( std::string path );
	
	
private:
	//----------------------�����o�ϐ�-----------------------
	_Tag*			m_controller;	// ���ݑ{�����̃^�O
	_Tag*			m_tagTree;		// �^�O�c���[
	FILE*			m_fp;			// �t�@�C���|�C���^
	bool			m_loop;			// ���[�v����t���O
	std::string		m_filePath;		// �t�@�C���p�X
	
	
	//-----------------------���\�b�h------------------------
	
	// ���̃^�O���擾
	_Tag*		_GetNextTag();

	// �L���ȃ^�O���ǂ������`�F�b�N
	bool		_IsEnableTag( const struct _Tag* tag );

	// �^�O��S�폜
	void		_DeleteAllTag( _Tag* tag );

	// �h����̎w��^�O���擾
	_Tag*		_GetTag( _Tag* tag, std::string  name );

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
	 LoadToyFile();
	 LoadToyFile( std::string path );			//! ���[�h
	~LoadToyFile();
};



//=============================================================================
/*!
								Toystudio�t�@�C���Ǘ��N���X
*/
//=============================================================================
class ToyFile {
public:

public:
	//-----------------------�^��`--------------------------

	/* ���b�V�� */
	struct _Mesh {
		std::string				name;		// ���b�V����
		resource::Vertex		vertex;		// ���_
		resource::Face			face;		// �ʍ\��
		resource::Vertex		normal;		// �@��
		std::vector<_Mesh*>		mesh;		// �h�����Ă��郁�b�V��
		_Mesh*					prev;		// �h�����̃��b�V��
	};

	/* �p�� */
	enum { LINEAR, SPLINE, STEP, STEPNEXT };
	typedef u32	SLOPE_TYPE;				// �X���^�C�v
	struct _Attitude {
		s32						frame;				// �t���[��
		f32						trans;				// �ړ��ʁE��]��
		bool					splitFlag;			// �����t���O
		SLOPE_TYPE				slopeTypeFront;		// �X���̎��(�O)
		SLOPE_TYPE				slopeTypeRear;		// �X���̎��(��)
		math::Vector			slopeHandleFront;	// �X���n���h��(�O)
		math::Vector			slopeHandleRear;	// �X���n���h��(��)
	};

	/* �A�j���[�V�����ω� */
	struct _Transformation {
		s32						keyNum;		// �L�[�̐�
		std::vector<_Attitude>	attitude;	// �p��
	};

	/* �A�j���[�V�����A�C�e�� */
	struct _AnimationItem {
		enum { RotateX, RotateY, RotateZ, TranslateX, TranslateY, TranslateZ, ITEM_TYPE_MAX };

		std::string						name;					// ���O
		std::vector<_Transformation>	transform;				// �ϊ�
	};

	/* �A�j���[�V���� */
	struct _Animation {
		std::string						name;					// �A�j���[�V������
		s32								fps;					// �t���[�����[�g
		s32								firstFrame;				// �ŏ��̃t���[��
		s32								lastFrame;				// �Ō�̃t���[��
		std::vector<_AnimationItem>		animationItem;			// �A�j���[�V�����A�C�e��
		
		const _AnimationItem* GetAnimationItem(std::string name) const
		{
			for(u32 i = 0; i < animationItem.size(); ++i) {
				if( animationItem[i].name == name ) {
					return &(animationItem[i]);
				}
			}
			return NULL;
		}
	};

	/* ���f�� */
	struct _Model {
		Material				material;	// �}�e���A��
		_Mesh*					rootMesh;	// ���b�V���̐擪
		//std::vector<_Animation>	anim;		// �A�j���[�V����
	};
	

public:
	//----------------------�ÓI�����o-----------------------

	
	
	//-----------------------���\�b�h------------------------

	//! ���[�h�����t�@�C�����i�[
	void				operator =(LoadToyFile& file);
	void				SetFile(LoadToyFile& file);
	
	//! �t�@�C�������擾
	std::string			GetName() const;

	//! ���b�V���c���[���擾
	_Mesh*				GetRootMesh() const;

	//! �}�e���A�����擾
	Material			GetMaterial() const;

	//! �A�j���[�V�������擾
	const _Animation*	GetAnimation(std::string animName) const;


	//! ���\�[�X�Ǘ��N���X��o�^
	static void			SetResourceManager(ResourceManager* mng);
	
private:
	//----------------------�ÓI�����o-----------------------
	static ResourceManager*	m_resourceMng;	//!< ���\�[�X�Ǘ�


	//----------------------�����o�ϐ�-----------------------
	_Model					m_model;		//!< ���f��
	std::vector<_Animation>	m_animAry;		//!< �A�j���[�V�����z��
	std::string				m_filePath;		//!< �t�@�C���p�X


	_Mesh*					m_ctrlMesh;		//!< ���쒆�̃��b�V��
	
	
	//-----------------------���\�b�h------------------------

	//! ���b�V���̑S�폜
	void	_DeleteAllMesh(_Mesh* mesh);

	//! ���b�V���c���[�̍쐬
	void	_CreateMeshTree(LoadToyFile& file, LoadToyFile::_Tag* tag);

	//! �^�O���烁�b�V���𐶐�
	_Mesh*	_CreateMeshFromTag(LoadToyFile::_Tag* tag);

	//! �^�O����A�j���[�V�����z����쐬
	void	_CreateAnimation(LoadToyFile::_Tag* tag);

	//! Items�^�O����_Transformation���쐬
	_Transformation _CreateTransformation(LoadToyFile::_Tag* itemTag);

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			 ToyFile();
			 ToyFile(LoadToyFile& file);		//! ���������t�@�C�����i�[
	virtual ~ToyFile();
};





}	// namespace resource
}	// namespace nk



#endif  // __TOYFILE_H__