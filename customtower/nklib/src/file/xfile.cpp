//=============================================================================
/*!	@file	xfile.h

	@brief	X�t�@�C��������

	@author	��� ���V��
	@date	2011/11/23
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/file/xfile.h"
#include "../../include/utility/stringfunction.h"
#include "general.h"
#include "../../include/resource/resourcemanager.h"


namespace nk {
namespace resource {

//------------------------------�ÓI�����o��`------------------------------
nk::resource::ResourceManager*		XFile::m_resourceMng	= NULL;		// ���\�[�X�Ǘ��N���X


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
XFile::XFile()
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
XFile::~XFile()
{
	
}



//===========================================================================
/*!	@brief	�t�@�C�������擾
	@param	�Ȃ�
	@return	�t�@�C����
*/
//===========================================================================
std::string XFile::GetName() const
{
	return m_name;
}


//===========================================================================
/*!	@brief	�ǉ�
	@param	obj	: �ǉ�����I�u�W�F�N�g�A�j���[�V����
	@return	�Ȃ�
*/
//===========================================================================
void XFile::AddObjectAnimation( const nk::resource::XFile::_ObjAnimation& obj )
{
	m_objAnimAry.push_back( obj );
}


//===========================================================================
/*!	@brief	�A�j���[�V������ǉ�
	@param	anim	: �ǉ�����A�j���[�V����
	@param	name	: �I�u�W�F�N�g��
	@return	�Ȃ�
*/
//===========================================================================
void XFile::AddAnimation( const _Animation& anim, std::string name )
{
	ObjAnimAry::iterator itr = m_objAnimAry.begin();
	ObjAnimAry::iterator end = m_objAnimAry.end();

	for( ; itr != end; ++itr ) {
		if( (*itr).object.name == name ) {
			(*itr).animation = anim;
			break;
		}
	}

}


//===========================================================================
/*!	@brief	���[�v�񐔂��擾
	@param	�Ȃ�
	@return	���[�v��
*/
//===========================================================================
u32 XFile::GetSize() const 
{
	return m_objAnimAry.size();
}


//===========================================================================
/*!	@brief	�I�u�W�F�N�g�\���̂��擾
	@param	index	: ���Ԗڂ̃I�u�W�F�N�g��
	@return	�I�u�W�F�N�g�ւ̎Q��(�ύX�s��)
*/
//===========================================================================
const XFile::_ModelObject& XFile::GetModelObject( u32 index ) const
{
	ObjAnimAry::const_iterator itr = m_objAnimAry.begin();
	ObjAnimAry::const_iterator end = m_objAnimAry.end();

	for(u32 i = 0; i < index; i++ ) {
		if( itr == end ) {
			break;
		}
		++itr;
	}

	return (*itr).object;
}


//===========================================================================
/*!	@brief	�A�j���[�V�����\���̂��擾
	@param	index	: ���Ԗڂ̃A�j���[�V������
	@return	�A�j���[�V�����ւ̎Q��(�ύX�s��)
*/
//===========================================================================
const XFile::_Animation& XFile::GetAnimation( u32 index ) const
{
	ObjAnimAry::const_iterator itr = m_objAnimAry.begin();
	ObjAnimAry::const_iterator end = m_objAnimAry.end();

	for(u32 i = 0; i < index; i++ ) {
		if( itr == end ) {
			break;
		}
		++itr;
	}

	return (*itr).animation;
}


//===========================================================================
/*!	@brief	���\�[�X�Ǘ���o�^
	@param	mng	: ���\�[�X�Ǘ��N���X
	@return	�Ȃ�
*/
//===========================================================================
void XFile::SetResourceManager( nk::resource::ResourceManager* mng )
{
	m_resourceMng = mng;
}


//===========================================================================
/*!	@brief	X�t�@�C�������[�h
	@param	path	: ���[�h�p�X
	@return	��������X�t�@�C��	NULL:�t�@�C��������or�쐬���s
*/
//===========================================================================
XFile* CreateXFile( std::string path )
{
	std::ifstream ifs( path.c_str() );

	// �t�@�C�����Ȃ��ꍇ��NULL��Ԃ�
	if( ifs.fail() ) {
		return NULL;
	}

	// �f�[�^���͗p�̃C���X�^���X�𐶐�
	XFile* xfile = new XFile();
	xfile->m_name = path;		// ���O���Z�b�g
	char line[256];

	// ���݂ǂ̏������s�Ȃ��Ă��邩
	enum {
		FLAG_NONE,				// �t���O�Ȃ�
		FLAG_VERTEX,			// ���_���W
		FLAG_FACE,				// ��
		FLAG_NORMAL_VERTEX,		// �@��
		FLAG_NORMAL_FACE,		// �@���̍\��
		FLAG_MATERIAL,			// �}�e���A��
		FLAG_TEXTURE_COORDS,	// UV���W
		FLAG_ANIMATION			// �A�j���[�V����
	};
	u32 lineFlag = FLAG_NONE;	// ���ݍs�Ȃ��Ă��鏈��

	XFile::_ObjAnimation*	objAnim		= NULL;

	bool	isFirstEntry	= true;		// �ŏ��ɓ��������ǂ���
	bool	isObjLine		= false;	// �I�u�W�F�N�g�̍s�ɓ��������ǂ���
	s32		brackets		= 0;		// ���ʂ̐�

	// �t�@�C���̓��e�𒲂ׂ�
	while( !ifs.eof() ) {
		memset(line, '\0', sizeof(line)); 
		ifs.getline(line, sizeof(line));

		/* ���ʂ𐔂��� */
		if( strstr(line, "{") ) {
			++brackets;
		}
		if( strstr(line, "}") ) {
			--brackets;
		}


		/* �A�j���[�V���� */
		if( lineFlag == FLAG_ANIMATION ) {
			if( strstr(line, "AnimationKey") ) {
			}
		}

		/* �A�j���[�V�����̓o�^ */
		if( strstr(line, "AnimationSet {") && !strstr(line, "template") ) {
			lineFlag = FLAG_ANIMATION;
		}

		/* �I�u�W�F�N�g�̊i�[ */
		if( isObjLine && (brackets == 0) ) {
			isObjLine = false;
			xfile->AddObjectAnimation( *objAnim );
			SafeDelete( objAnim );
		}


		/* UV���W */
		if( lineFlag == FLAG_TEXTURE_COORDS ) {
			if( strstr(line, "MeshTextureCoords {") ) {
				ifs.getline( line, sizeof(line) );	// 1�s�i�߂�
				isFirstEntry = false;
			}
			else if( !isFirstEntry ) {
				if( !strstr(line, "}") ) {
					char* tp;
					math::Vector uv;
					tp = strtok(line, " \t,;");
					uv.x = static_cast<f32>( atof(tp) );
					tp = strtok(NULL, " \t,;");
					uv.y = static_cast<f32>( atof(tp) );
					objAnim->object.face.AddUV( uv );
				} else {
					isFirstEntry = true;
					lineFlag = FLAG_NONE;
				}
			}
			
		}

		/* �e�N�X�`�� */
		if( lineFlag == FLAG_MATERIAL ) {
			if( strstr(line, "TextureFilename {") ) {
				ifs.getline(line, sizeof(line));	// 1�s�i�߂�
				std::string str = FindStr( line, "\"", "\";" );
				objAnim->object.material.SetTexture( XFile::m_resourceMng->GetTexture(str) );
				lineFlag = FLAG_TEXTURE_COORDS;
			}
		}

		/* ���_�@���̖ʍ\�� */
		if( lineFlag == FLAG_NORMAL_FACE ) {
			if( isFirstEntry ) {
				isFirstEntry = false;
			}
			else if( strstr(line, "}") ) {
				lineFlag = FLAG_MATERIAL;
				isFirstEntry = true;
			}
			else {
				char* tp;
				strtok(line, "\t,;");				// �ŏ��̕����͎̂Ă�
				for(s32 i = 0; i < 3; i++) {
					tp = strtok(NULL, "\t,;");
					objAnim->object.normalFace.AddFace( atoi(tp) );
				}
			}
		}

		/* ���_�@����� */
		if( lineFlag == FLAG_NORMAL_VERTEX ) {
			if( isFirstEntry ) {
				isFirstEntry = false;
				ifs.getline(line, sizeof(line));	// 1�s�i�߂�
			}
			else if( !strcmp(line, "") ) {
				lineFlag = FLAG_NORMAL_FACE;
				isFirstEntry = true;
			}
			else {
				objAnim->object.normalVertex.Add( GetVectorFromString(line, "\t,;") );
			}
		}


		/* �ʏ�� */
		if( lineFlag == FLAG_FACE ) {
			if( isFirstEntry ) {
				isFirstEntry = false;
			}
			else if( !strcmp(line, "") ) {
				lineFlag = FLAG_NORMAL_VERTEX;
				isFirstEntry = true;
			}
			else {
				char* tp;
				strtok(line, "\t,;");				// �ŏ��̕����͎̂Ă�
				for(s32 i = 0; i < 3; i++) {
					tp = strtok(NULL, "\t,;");
					objAnim->object.face.AddFace( atoi(tp) );
				}
			}
		}

		/* ���_���� */
		if( lineFlag == FLAG_VERTEX ) {
			if( !strcmp(line, "") ) {
				lineFlag = FLAG_FACE;
				isFirstEntry = true;
			} else {
				objAnim->object.vertex.Add(GetVectorFromString( line, "\t,;") );
			}
		}
		
		/* �I�u�W�F�N�g�̍s�ɓ��� */
		if( strstr(line, "Frame ") && !strstr(line, "template") ) {
			lineFlag			= FLAG_VERTEX;	
			isFirstEntry		= false;
			isObjLine			= true;
			std::string objName = FindStr(line, "Frame ", " {");
			
			// �O�̂��߂ɍ폜
			SafeDelete(objAnim);

			objAnim					= new XFile::_ObjAnimation;	// �i�[����I�u�W�F�N�g�𐶐�
			objAnim->object.name	= objName;					// �I�u�W�F�N�g�����Z�b�g
			ifs.getline(line, sizeof(line));// 2�s�i�߂�
			ifs.getline(line, sizeof(line));
			++brackets;						// �i�߂�����}���J�E���g���ĂȂ��̂ŃJ�E���g����
		}

	}


	return xfile;
}

}	// namespace resource
}	// namespace nk
