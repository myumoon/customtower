//=============================================================================
/*!	@file	toyFile.h

	@brief	Toystudio�t�@�C����Ǎ��݁E�Ǘ�����

	@author	��� ���V��
	@date	2011/12/01
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/file/toyFile.h"
#include "../../include/utility/stringfunction.h"
#include "general.h"
#include "../../include/resource/resourcemanager.h"

#pragma warning (disable:4996)

namespace nk {
namespace resource {

//------------------------------�ÓI�����o��`------------------------------
nk::resource::ResourceManager*		ToyFile::m_resourceMng	= NULL;		// ���\�[�X�Ǘ��N���X


//===========================================================================
/*!	@brief	���\�[�X�Ǘ���o�^
	@param	mng	: ���\�[�X�Ǘ��N���X
	@return	�Ȃ�
*/
//===========================================================================
void ToyFile::SetResourceManager( nk::resource::ResourceManager* mng )
{
	m_resourceMng = mng;
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
ToyFile::ToyFile()
{
	
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
ToyFile::~ToyFile()
{
	_DeleteAllMesh( m_model.rootMesh );
}



//===========================================================================
/*!	@brief	�R���X�g���N�^(���[�h����Toystudio�t�@�C�����i�[
	@param	
*/
//===========================================================================)
ToyFile::ToyFile( LoadToyFile &file )
{
	SetFile( file );
}


//===========================================================================
/*!	@brief	toystudio�t�@�C�����Z�b�g
	@param	file	: �Z�b�g����toystudio�t�@�C��
	@return	�Ȃ�
*/
//===========================================================================
void ToyFile::operator =( nk::resource::LoadToyFile &file )
{
	SetFile( file );
}


//===========================================================================
/*!	@brief	�t�@�C�������擾
	@param	�Ȃ�
	@return	�t�@�C����
*/
//===========================================================================
std::string ToyFile::GetName() const
{
	return m_filePath;
}


//===========================================================================
/*!	@brief	toystudio�t�@�C�����Z�b�g
	@param	file	: toystudio�t�@�C��
	@return	�Ȃ�
*/
//===========================================================================
void ToyFile::SetFile(nk::resource::LoadToyFile &file)
{
	LoadToyFile::_Tag*	root	= file._GetTag( file.m_tagTree, "Model" );	// �������ԒZ�k�̈׃��[�g��ݒ�
	LoadToyFile::_Tag*	texTag	= file._GetTag( root, "Texture" );			// �e�N�X�`���^�O���擾
	std::string			texName	= texTag->GetPropertyValue("Path");			// �e�N�X�`�������擾
	std::string			dirPath	= GetDirectoryPath( file.m_filePath );

	
	/* ���[�g�̏����� */
	m_model.rootMesh		= new _Mesh;
	m_model.rootMesh->prev	= NULL;
	m_model.material.SetTexture( m_resourceMng->GetTexture(dirPath + texName) );
	//m_model.material.SetTexture( m_resourceMng->GetTexture(texName) );
	
	/* �t�@�C���p�X�̐ݒ� */
	m_filePath = file.m_filePath;

	/* ���b�V���c���[�̍쐬 */
	m_ctrlMesh = m_model.rootMesh;
	_CreateMeshTree( file, root );

	/* �A�j���[�V�����̍쐬 */
	LoadToyFile::_Tag*	animsTag	= file._GetTag( file.m_tagTree, "Anims" );	// �A�j���[�V�����^�O
	_CreateAnimation( animsTag );
}


//===========================================================================
/*!	@brief	���b�V���c���[�̍쐬
	@param	file	: �쐬����toystudio�t�@�C��
	@param	tag		: �������J�n����^�O
	@return	�Ȃ�
*/
//===========================================================================
void ToyFile::_CreateMeshTree( nk::resource::LoadToyFile &file, LoadToyFile::_Tag *tag )
{
	_Mesh* newMesh = NULL;
	if( tag->tagName == "Mesh" ) {
		newMesh		= _CreateMeshFromTag( tag );	// ���b�V���𐶐�
		
		m_ctrlMesh->mesh.push_back( newMesh );		// �ǉ�
		m_ctrlMesh	= newMesh;						// ���상�b�V���𐶐�������ɕύX
	}

	const u32 size = tag->tree.size();
	for( u32 i = 0; i < size; ++i ) {
		_CreateMeshTree( file, tag->tree[i] );
	}

	/*	�h���^�O�����Ă����ĐV�������b�V������������Ă��Ȃ�������
		����Ώۂ�1�߂�	*/
	if( m_ctrlMesh == newMesh ) {
		m_ctrlMesh = m_ctrlMesh->prev;
	}

}


//===========================================================================
/*!	@brief	�^�O���烁�b�V���𐶐�
	@param	tag		: �^�O
	@return	�����������b�V��
*/
//===========================================================================
ToyFile::_Mesh* ToyFile::_CreateMeshFromTag( nk::resource::LoadToyFile::_Tag *tag )
{
	_Mesh* newMesh	= new _Mesh;				// ���b�V���𐶐�
	newMesh->prev	= m_ctrlMesh;				// 1�O�̃��b�V����ݒ�

	/* ���O�^�O���擾���ă��b�V������ݒ� */
	LoadToyFile::_Tag* nameTag = tag->GetTagFromTree("Name");
	newMesh->name	= FindStr(nameTag->value.c_str(), "<![CDATA[", "]]>");	// ���b�V������ݒ�


	/* �^�O��ݒ� */
	LoadToyFile::_Tag*	vertexTag	= tag->GetTagFromTree("Vertices");
	u32			vertexCount	= atoi(vertexTag->GetPropertyValue("Count").c_str());
	size_t				strBufSize	= vertexTag->value.size();
	char*				strBuf		= NULL;
	

	strBuf	= new char[strBufSize];	// ������o�b�t�@���쐬

	/* ���_��������R�s�[ */
	for(u32 i = 0; i < strBufSize; ++i) {
		strBuf[i] = vertexTag->value.at(i);
	}

	/* �������f32�l�ɕϊ� */
	math::Vector vertex;								// ���_���i�[�����
	enum INSERT_FLAG { INSERT_X, INSERT_Y, INSERT_Z };	// �ǂ��ɓ���邩�̃t���O
	INSERT_FLAG insertFlag = INSERT_X;

	strtok(strBuf, " ");		// �Ƃ肠�����擪�͐؂�̂�
	
	for(u32 i = 0; i < vertexCount * 3; ++i) {
		char* token = strtok(NULL, " ,\n");
		if( !token ) {
			break;
		}
		const f32 value = static_cast<f32>(atof(token));
		if( insertFlag == INSERT_X )		{ vertex.x = value; insertFlag = INSERT_Y; }
		else if( insertFlag == INSERT_Y )	{ vertex.y = value; insertFlag = INSERT_Z; }
		else if( insertFlag == INSERT_Z )	{ vertex.z = value; insertFlag = INSERT_X; newMesh->vertex.Add(vertex); }
	}
	
	SafeDelete(strBuf);


	/* �ʏ����R�s�[ */
	LoadToyFile::_Tag*	faceTag		= tag->GetTagFromTree("Faces");
	u32			faceCount	= atoi(faceTag->GetPropertyValue("Count").c_str());
	bool				useUVFlag	= (faceTag->GetPropertyValue("UV") == "True");
	strBufSize						= faceTag->value.size();
	strBuf							= new char[strBufSize];

	for(u32 i = 0; i < strBufSize; ++i) {
		strBuf[i] = faceTag->value.at(i);
	}

	strtok(strBuf, " ");		// �擪�͐؂�̂�
	for(u32 i = 0; i < faceCount; ++i) {
		char* token = NULL;
		strtok(NULL, " ,;\n");	// �ʂ̍\�����͔�΂�

		char* idx[3];		// ���_�ԍ����i�[
		idx[0]	= strtok(NULL, " ,;\n");	// ���_�ԍ�1
		idx[1]	= strtok(NULL, " ,;\n");	// ���_�ԍ�2
		idx[2]	= strtok(NULL, " ,;\n");	// ���_�ԍ�3
		newMesh->face.AddFace(atoi(idx[0]));
		newMesh->face.AddFace(atoi(idx[1]));
		newMesh->face.AddFace(atoi(idx[2]));
		
		if( useUVFlag ) {
			char* uv[6] = { 0 };
			for(u32 j = 0; j < ARRAY_SIZE(uv); ++j) {
				uv[j]	= strtok(NULL, " ,;\n");
			}
			math::Vector faceUV0( static_cast<f32>(atof(uv[0])), static_cast<f32>(atof(uv[1])), 0.0f );
			math::Vector faceUV1( static_cast<f32>(atof(uv[2])), static_cast<f32>(atof(uv[3])), 0.0f );
			math::Vector faceUV2( static_cast<f32>(atof(uv[4])), static_cast<f32>(atof(uv[5])), 0.0f );
			newMesh->face.AddUV( faceUV0 );
			newMesh->face.AddUV( faceUV1 );
			newMesh->face.AddUV( faceUV2 );
		}

		{	/*	���̃X�R�[�v���͏����I�ɈӖ����Ȃ�
				���ʂȂƂ�����΂����߂ɂ��鏈��	*/
			for(s32 _i = 0; _i < 12; ++_i) {
				strtok(NULL, " ,;\n");	// 255�̕����͔�΂�
			}

			for(s32 _i = 0; _i < 3; ++_i) {
				strtok(NULL, " ,;\n");	// 1,1,0�݂����ɂȂ��Ă�Ƃ��͔�΂�
			}
			strtok(NULL, " ,;\n");		// �Ō��0�������Ă邩���΂�
		}
	}


	/* ���_�@�����i�[����\���� */
	typedef std::vector<math::Vector> VertexNormal;	// ���_�ԍ����܂ޖʖ@��

	/* ���_�@���̐���ݒ� */
	std::vector<VertexNormal> vertexNormal(newMesh->vertex.GetSize());

	for(u32 i = 0; i < newMesh->face.GetSize(); i += newMesh->face.GetBundle()) {
		math::Vector v0 = newMesh->vertex.GetVertex(newMesh->face.GetFace(i + 1)) - newMesh->vertex.GetVertex(newMesh->face.GetFace(i));
		math::Vector v1 = newMesh->vertex.GetVertex(newMesh->face.GetFace(i + 2)) - newMesh->vertex.GetVertex(newMesh->face.GetFace(i));
		math::Vector N	= math::CalcCrossProduct(v0, v1);

		vertexNormal[newMesh->face.GetFace(i + 0)].push_back(N);
		vertexNormal[newMesh->face.GetFace(i + 1)].push_back(N);
		vertexNormal[newMesh->face.GetFace(i + 2)].push_back(N);
	}

	for(u32 i = 0; i < newMesh->vertex.GetSize(); ++i) {
		math::Vector sum;
		for(u32 j = 0; j < vertexNormal[i].size(); ++j) {
			sum += vertexNormal[i].at(j);
		}
		sum.Normalize();
		newMesh->normal.Add(sum);
	}



	return newMesh;
}


//===========================================================================
/*!	@brief	�A�j���[�V�����z����쐬
	@param	tag		: �A�j���[�V�����̐擪�^�O
	@return	�Ȃ�
*/
//===========================================================================
void ToyFile::_CreateAnimation( nk::resource::LoadToyFile::_Tag *tag )
{
	typedef LoadToyFile::_Tag	_TAG;	// �����̂ŒZ�k

	for(u32 i = 0; i < tag->tree.size(); ++i) {
		_Animation	animation;		// �A�j���[�V�����������i�[����\����
		_TAG*		anim			= tag->tree[i];
		_TAG*		nameTag			= anim->GetTagFromTree("Name");
		_TAG*		fpsTag			= anim->GetTagFromTree("Fps");
		_TAG*		firstFrameTag	= anim->GetTagFromTree("FirstFrame");
		_TAG*		lastFrameTag	= anim->GetTagFromTree("LastFrame");
		_TAG*		objectItems		= anim->GetTagFromTree("ObjectItems");
		nameTag->value += '\0';
		animation.name				= FindStr(nameTag->value.c_str(), "<![CDATA[", "]]>");
		animation.fps				= atoi(fpsTag->value.c_str());
		animation.firstFrame		= atoi(firstFrameTag->value.c_str());
		animation.lastFrame			= atoi(lastFrameTag->value.c_str());

		/* �I�u�W�F�N�g�A�C�e���̓Ǎ��� */
		for(u32 j = 0; j < objectItems->tree.size(); ++j) {
			_AnimationItem	item;

			_TAG*	object	= objectItems->tree[j];
			std::string temp= FindStr(object->GetTagFromTree("Name")->value.c_str(), "<![CDATA[", "]]>");
			
			for(u32 i = 0; i < temp.size(); ++i) {
				item.name += temp.at(i);
				if( temp.at(i) == '\\' ) {
					item.name.clear();	// �o�b�N�X���b�V��������������폜
				}
			}


			_TAG*	items	= object->GetTagFromTree("Items");

			/* �ϊ��f�[�^�̓Ǎ��� */
			//item.transform.reserve(1);
			//item.transform.reserve(_AnimationItem::ITEM_TYPE_MAX);	// �v�f���m��
			for(u32 itemType = 0; itemType < _AnimationItem::ITEM_TYPE_MAX; ++itemType) {
				item.transform.push_back(_CreateTransformation(items->tree[itemType]));
				//item.transform[itemType] = _CreateTransformation(items->tree[itemType]);
			}

			animation.animationItem.push_back(item);	// �A�j���[�V�����A�C�e����ǉ�
		}
		
		m_animAry.push_back(animation);		// �A�j���[�V������ǉ�
	}

}


//===========================================================================
/*!	@brief	Items�^�O����_Transformation���쐬
	@param	itemTag		: �A�C�e���^�O�̐擪
	@return	���������ϊ��f�[�^
*/
//===========================================================================
ToyFile::_Transformation ToyFile::_CreateTransformation( nk::resource::LoadToyFile::_Tag *itemTag )
{
	enum {
		ATTITUDE_FRAME_NUM,			// ���t���[���ڂ�
		ATTITUDE_TRANSFERS,			// �ړ���
		ATTITUDE_SPLIT_FLAG,		// �����t���O
		ATTITUDE_SLOPE_TYPE_FRONT,	// �X���̎��(�O)
		ATTITUDE_SLOPE_TYPE_REAR,	// �X���̎��(��)
		ATTITUDE_SLOPE_HANDLE_FRONT,// �X���n���h��(�O)
		ATTITUDE_SLOPE_HANDLE_REAR,	// �X���n���h��(��)
		ATTITUDE_MAX				// 
	};

	_Transformation	retTrans;

	itemTag->value += '\0';
	char*			strBuf			= new char[itemTag->value.length()];
	u32		attitudeNum		= ATTITUDE_FRAME_NUM;


	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = '\0';
	}
	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = itemTag->value.at(i);
	}

	retTrans.keyNum		= atoi(strtok(strBuf, "\t ;,\n"));	// �L�[�̐�

	while( 1 ) {
		char* tp	= strtok(NULL, "\t ;,\n");
		if( !tp ) {
			break;
		}

		std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();

		switch( attitudeNum ) {
			case ATTITUDE_FRAME_NUM: {
				retTrans.attitude.push_back(_Attitude());
				std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();
				(*attitudeItr).frame	= atoi(tp);
				attitudeNum				= ATTITUDE_TRANSFERS;
				break;
			}
			
			case ATTITUDE_TRANSFERS: {
				(*attitudeItr).trans	= static_cast<f32>(atof(tp));
				attitudeNum				= ATTITUDE_SPLIT_FLAG;
				break;
			}
			
			case ATTITUDE_SPLIT_FLAG: {
				(*attitudeItr).splitFlag	= (atoi(tp) == 1);
				attitudeNum					= ATTITUDE_SLOPE_TYPE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_FRONT: {
				(*attitudeItr).slopeTypeFront	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_TYPE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_REAR: {
				(*attitudeItr).slopeTypeRear	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_FRONT: {
				math::Vector direcFront(-1.0f, static_cast<f32>(atof(tp)), 0.0f);
				(*attitudeItr).slopeHandleFront	= direcFront;
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_REAR: {
				math::Vector direcRear(1.0f, static_cast<f32>(atof(tp)), 0.0f);
				(*attitudeItr).slopeHandleRear	= direcRear;
				attitudeNum						= ATTITUDE_FRAME_NUM;
				break;
			}

			default:
				PRINTF("�����ɂ͂��Ȃ�\n");
				break;
		}
	}

	SafeDeleteArray(strBuf);

	return retTrans;
}

#if 0
//===========================================================================
/*!	@brief	Items�^�O����_Transformation���쐬
	@param	itemTag		: �A�C�e���^�O�̐擪
	@return	���������ϊ��f�[�^
*/
//===========================================================================
ToyFile::_Transformation ToyFile::_CreateTransformation(nk::resource::LoadToyFile::_Tag *itemTag)
{
	enum {
		ATTITUDE_FRAME_NUM,			// ���t���[���ڂ�
		ATTITUDE_TRANSFERS,			// �ړ���
		ATTITUDE_SPLIT_FLAG,		// �����t���O
		ATTITUDE_SLOPE_TYPE_FRONT,	// �X���̎��(�O)
		ATTITUDE_SLOPE_TYPE_REAR,	// �X���̎��(��)
		ATTITUDE_SLOPE_HANDLE_FRONT,// �X���n���h��(�O)
		ATTITUDE_SLOPE_HANDLE_REAR,	// �X���n���h��(��)
		ATTITUDE_MAX				// 
	};

	_Transformation	retTrans;

	itemTag->value += '\0';
	char*			strBuf			= new char[itemTag->value.length()];
	u32		attitudeNum		= ATTITUDE_FRAME_NUM;


	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = '\0';
	}
	for(u32 i = 0; i < itemTag->value.length(); ++i) {
		strBuf[i] = itemTag->value.at(i);
	}

	retTrans.keyNum		= atoi(strtok(strBuf, "\t ;,\n"));	// �L�[�̐�

	while( 1 ) {
		char* tp	= strtok(NULL, "\t ;,\n");
		if( !tp ) {
			break;
		}

		std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();

		switch( attitudeNum ) {
			case ATTITUDE_FRAME_NUM: {
				retTrans.attitude.push_back(_Attitude());
				std::vector<_Attitude>::reverse_iterator attitudeItr = retTrans.attitude.rbegin();
				(*attitudeItr).frame	= atoi(tp);
				attitudeNum				= ATTITUDE_TRANSFERS;
				break;
			}
			
			case ATTITUDE_TRANSFERS: {
				(*attitudeItr).trans	= static_cast<f32>(atof(tp));
				attitudeNum				= ATTITUDE_SPLIT_FLAG;
				break;
			}
			
			case ATTITUDE_SPLIT_FLAG: {
				(*attitudeItr).splitFlag	= (atoi(tp) == 1);
				attitudeNum					= ATTITUDE_SLOPE_TYPE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_FRONT: {
				(*attitudeItr).slopeTypeFront	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_TYPE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_TYPE_REAR: {
				(*attitudeItr).slopeTypeRear	= atoi(tp);
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_FRONT;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_FRONT: {
				math::Vector direcFront(-1.0, atof(tp), 0.0);
				(*attitudeItr).slopeHandleFront	= direcFront;
				attitudeNum						= ATTITUDE_SLOPE_HANDLE_REAR;
				break;
			}

			case ATTITUDE_SLOPE_HANDLE_REAR: {
				math::Vector direcRear(1.0, atof(tp), 0.0);
				(*attitudeItr).slopeHandleRear	= direcRear;
				attitudeNum						= ATTITUDE_FRAME_NUM;
				break;
			}

			default:
				PRINTF("�����ɂ͂��Ȃ�\n");
				break;
		}
	}

	SafeDeleteArray(strBuf);

	return retTrans;
}
#endif

//===========================================================================
/*!	@brief	���b�V���̑S�폜
	@param	mesh	: ���b�V��
	@return	�Ȃ�
*/
//===========================================================================
void ToyFile::_DeleteAllMesh(_Mesh* m)
{
	for(u32 i = 0; i < m->mesh.size(); ++i) {
		_DeleteAllMesh(m->mesh[i]);
	}
	SafeDelete(m);
}


//===========================================================================
/*!	@brief	���b�V���c���[�̐擪���擾
	@param	�Ȃ�
	@return	���b�V���c���[�̐擪
*/
//===========================================================================
ToyFile::_Mesh* ToyFile::GetRootMesh() const
{
	return m_model.rootMesh;
}


//===========================================================================
/*!	@brief	�}�e���A�����擾
	@param	�Ȃ�
	@return	�}�e���A��
*/
//===========================================================================
Material ToyFile::GetMaterial() const
{
	return m_model.material;
}

//===========================================================================
/*!	@brief	�A�j���[�V�������擾
	@param	animName	: �A�j���[�V������
	@return	�A�j���[�V�����f�[�^�ւ̃|�C���^
*/
//===========================================================================
const ToyFile::_Animation* ToyFile::GetAnimation(std::string animName) const
{

	for(u32 i = 0; i < m_animAry.size(); ++i) {
		if( m_animAry[i].name == animName ) {
			return &(m_animAry[i]);
		}
	}

	PRINTF("%s : �A�j���[�V��������������܂���ł����B\n");

	return NULL;
}

}	// namespace resource







//===============�t�@�C�����[�h===============


namespace resource {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	�Ȃ�
*/
//===========================================================================
LoadToyFile::LoadToyFile() : 
	m_controller(NULL),
	m_tagTree(NULL),
	m_fp(NULL)
{

	
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	path	: �t�@�C����
*/
//===========================================================================
LoadToyFile::LoadToyFile( std::string path ) :
	m_controller(NULL),
	m_tagTree(NULL),
	m_fp(NULL)
{
	Load(path);
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	
*/
//===========================================================================
LoadToyFile::~LoadToyFile()
{
	if( m_tagTree ) {
		_DeleteAllTag(m_tagTree);
	}
}


//===========================================================================
/*!	@brief	���[�h
	@param	path	: �t�@�C���p�X
	@return	�Ȃ�
*/
//===========================================================================
void LoadToyFile::Load( std::string path )
{
	/* �t�@�C�����J�� */
	m_fp = fopen(path.c_str(), "r");
	if( !m_fp ) {
		PRINTF("file open error : %s\n", path.c_str());
		return;
	}

	/* �t�@�C���p�X��ݒ� */
	m_filePath = path;


	/* �c���[���𐶐� */
	m_tagTree			= new _Tag;
	m_tagTree->close	= false;
	m_tagTree->prev		= NULL;
	m_tagTree->tagName	= "";

	m_controller = m_tagTree;
	m_loop = true;


	/* �^�O�Ǎ��� */
	while( m_loop ) {
		_Tag* next = _GetNextTag();
		if( next ) {
			m_controller->tree.push_back(next);
			if( !next->close ) {
				m_controller = next;
			}
		}
	}

	/* �t�@�C������� */
	fclose(m_fp);

}


//===========================================================================
/*!	@brief	���̃^�O���擾
	@param	�Ȃ�
	@return	�^�O		NULL : �t�@�C���I�[
*/
//===========================================================================
LoadToyFile::_Tag* LoadToyFile::_GetNextTag()
{
	bool	readTag		= false;	// �^�O�ǂݍ��ݒ����ǂ���
	char	buf[256]	= { 0 };	// �Ǎ��݃o�b�t�@
	s32		bufIdx		= 0;		// ���쒆�̓Ǎ��݃o�b�t�@�C���f�b�N�X


	while( 1 ) {

		/* �Ǎ��� */
		char c = fgetc(m_fp);


		/* �t�@�C���I�[�Ȃ甲���� */
		if( c == EOF ) {
			m_loop = false;
			return NULL;
		}

		/* �^�O�J�n */
		if( c == '<' ) {
			// �ŏ��́u<�v��ǂݍ��ގ���readFlag��false�Ȃ̂�
			// readFlag��true�̎���������悤�ɂ���Γr���ŏo������<�𔻕ʂł���
			//if( m_controller && readFlag ) {
			//	m_controller->value += '\0';
			//}
			readTag = true;
		}

		/* �o�b�t�@�Ɋi�[ */
		if( readTag ) {
			buf[bufIdx] = c;
			bufIdx++;
		} else {
			if( m_controller ) {
				m_controller->value += c;
			}
		}

		/* �^�O�I�� */
		if( c == '>' ) {
			buf[bufIdx] = '\0';
			break;
		}
	}

	
	/* �I���^�O�Ȃ甲���� */
	if( buf[1] == '/' ) {
		m_controller->close = true;			// �^�O�I���ݒ�
		m_controller = m_controller->prev;	// ����^�O��1�K�w�߂�
		return NULL;
	}

	/* <!�`�`>�^���̏ꏊ(�^�O����Ȃ�) */
	if( buf[1] == '!' ) {
		for(s32 i = 0; buf[i] != '\0'; ++i) {
			m_controller->value += buf[i];
		}
		return NULL;
	}

	/* �^�O�𐶐� */
	_Tag*	retTag	= new _Tag;		// ���^�[���p�̃^�O

	/* �^�O�������� */
	retTag->close	= false;
	retTag->prev	= m_controller;

	{	/* 1�̃^�O�ŏI������ꍇ */
		s32 i;
		for(i = 0; buf[i] != '>'; ++i)
			;
		if( buf[i - 1] == '/' ) {
			retTag->close	= true;				// �^�O�I���ݒ�
		}
	}

	/* �^�O����ݒ� */
	char* token = strtok(buf, "</ =\">");
	for(s32 i = 0; token[i] != '\0'; ++i) {
		retTag->tagName += token[i];
	}
	//retTag->tagName += '\0';


	/* �v���p�e�B��ݒ� */
	s32 attributeFlag	= 1;	// �������쒆�t���O
	s32 proNum			= 0;	// �v���p�e�B�ԍ�
	while( 1 ) {
		if( attributeFlag ) {
			token = strtok(NULL, "</ =\">");	// �����̂ق��̓X���b�V�����܂߂�
			if( !token ) {
				break;
			}
			retTag->pro.push_back(_Property());
			for(s32 i = 0; token[i] != '\0'; ++i) {
				retTag->pro[proNum].attribute += token[i];
			}
			//retTag->pro[proNum].attribute += '\0';

		} else {
			token = strtok(NULL, "< =\">");		// �l�̂ق��̓X���b�V���ł̋�؂���Ȃ�
			if( !token ) {
				break;
			}
			for(s32 i = 0; token[i] != '\0'; ++i) {
				retTag->pro[proNum].value += token[i];
			}
			//retTag->pro[proNum].value += '\0';
			
			++proNum;		// �v���p�e�B�ԍ������Z
		}

		attributeFlag = 1 - attributeFlag;		// �t���O����ւ�
	}

	return retTag;
}


//===========================================================================
/*!	@brief	�L���ȃ^�O���ǂ����𔻒f
	@param	tag	: ���f���s���^�O
	@return	true : �L��		false : ����
*/
//===========================================================================
bool LoadToyFile::_IsEnableTag( const _Tag* tag ) {

	if( tag->tagName == "Model" )			{ return true; }
	if( tag->tagName == "Name" )			{ return true; }
	if( tag->tagName == "Material" )		{ return true; }
	if( tag->tagName == "VertexColored" )	{ return true; }
	if( tag->tagName == "Textures" )		{ return true; }
	if( tag->tagName == "Visible" )			{ return true; }
	if( tag->tagName == "Mesh" )			{ return true; }
	if( tag->tagName == "Vertices" )		{ return true; }
	if( tag->tagName == "Faces" )			{ return true; }
	if( tag->tagName == "Objects" )			{ return true; }
	if( tag->tagName == "Anims" )			{ return true; }
	if( tag->tagName == "Anim" )			{ return true; }
	if( tag->tagName == "LastFrame" )		{ return true; }
	if( tag->tagName == "Item" )			{ return true; }

	return false;
}




//===========================================================================
/*!	@brief	�^�O��S�폜
	@param	tag		: �폜����^�O
	@return	�Ȃ�
	\note	��������c���[��ɂȂ��Ă���v�f��S�č폜
*/
//===========================================================================
void LoadToyFile::_DeleteAllTag( nk::resource::LoadToyFile::_Tag *tag )
{
	for(u32 i = 0; i < tag->tree.size(); ++i) {
		_DeleteAllTag(tag->tree[i]);
	}
	SafeDelete(tag);
}


//===========================================================================
/*!	@brief	�^�O���擾
	@param	tag		: ���̃^�O�ȏ�̊K�w����������
	@param	name	: ��������^�O��
	@return	��������	NULL : ������Ȃ������ꍇ
*/
//===========================================================================
LoadToyFile::_Tag* LoadToyFile::_GetTag( _Tag *tag, std::string name )
{
	if( tag->tagName == name ) {
		return tag;
	}
	for(u32 i = 0; i < tag->tree.size(); ++i) {
		_Tag* temp = _GetTag(tag->tree[i], name);
		if( temp ) {
			return temp;
		}
	}
	return NULL;
}



}	// namespace resource
}	// namespace nk