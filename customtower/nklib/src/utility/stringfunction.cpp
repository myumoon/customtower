//=============================================================================
/*!	@file	stringfunction.cpp

	@brief	�����񑀍�֐�

	@author	��� ���V��
	@date	2011/11/24
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================
#include "../../include/utility/stringfunction.h"






namespace nk {


//===========================================================================
/*!	@brief	�������r
	@param	lhs		: ��r������1
	@param	rhs		: ��r������2
	@return	true.������		false.�������Ȃ�
*/
//===========================================================================
bool Compare( const char* lhs, const char* rhs )
{
	
	return strcmp(lhs, rhs) == 0;
}



//===========================================================================
/*!	@brief	������̂������̕����ň͂܂ꂽ���g�𒊏o����
	@param	origin	: ���̕�����
	@param	find1	: ����������(�O)
	@param	find2	: ����������(���)
	@return	������
*/
//===========================================================================
std::string FindStr( const char *origin, const char *find1, const char *find2 )
{
	s32 count = 0, num = 0;

	//	find1�̌���
	//---------------------------------------
	char *top = const_cast<char *>( strstr(origin, find1) );
	if( !top ) {
		return std::string();
	}
	top += strlen( find1 );
	
	//	find2�̌���
	//---------------------------------------
	char *last = const_cast<char *>( strstr(top, find2) );
	if( !last ) {
		return std::string();
	}

	//	�R�s�[
	//---------------------------------------
	std::string retStr;
	for( s32 i = 0; &top[i] < last; i++ ) {
		retStr += top[i];
	}
	//retStr += '\0';

	return retStr;
}





//========================================================================
//	���@�e�F����̕����񂪊܂܂��C���f�b�N�X�ԍ�������
//	���@���Forigin	: �����Ώە�����
//			str		: ������
//	�߂�l�F�C���f�b�N�X�ԍ�
//	 memo �F����������̐擪�̃C���f�b�N�X�ԍ���Ԃ�
//========================================================================
s32 SearchStrIndex(const char *origin, const char *find)
{
	s32 index = 0, count = 0;


	while(origin[index] != '\0') {

		if(origin[index] == find[count]) {
			count++;
		} else {
			count = 0;
		}
		index++;

		/* ��v���� */
		if(count == strlen(find)) {
			break;
		}

	}

	return index - strlen(find);
}





//========================================================================
//	���@�e�F������̐擪�A�h���X�����̕����̌��ɐݒ�
//	���@���Forigin				: �Ώ̕�����
//			find				: �T�[�`����
//	�߂�l�F��������			: 1
//			������Ȃ�����	: 0
//	 memo �F
//========================================================================
s32 ChangeStrTop(char **origin, const char *find)
{
	s32 count = 0, num = 0;


	
	
	while((*origin)[num] != '\0') {

		/* 1�������`�F�b�N */
		if((*origin)[num] == find[count]) {
			count++;
		} else {
			count = 0;
		}

		num++;

		/* ����������̒����ƃJ�E���^�̒�������v������܂܂�Ă��� */
		if(count == strlen(find)) {
			*origin = &(*origin)[num];
			return 1;
		}
	}



	return 0;
}





//========================================================================
//	���@�e�F�u��
//	���@���Forigin	: �ϊ�������
//			before	: ��������
//			after	: �u������
//	�߂�l�F�Ȃ�
//	 memo �F
//========================================================================
void ChangeCharacter(char *origin, char before, char after)
{
	s32 index_max = strlen(origin) + 1;


	for(s32 i = 0; i < index_max; i++) {
		if(origin[i] == before) {
			origin[i] = after;
		}
	}

}

//===========================================================================
/*!	@brief	��������x�N�g���ɕϊ�
	@param	str		: ������
	@param	token	: ��؂蕶�� ",."�̂悤�ɐ�������؂镶�����w��
	@return	���������x�N�g��
*/
//===========================================================================
nk::math::Vector GetVectorFromString(char* str, const char* token)
{
	char*				tp;
	nk::math::Vector	retVec;

	// X
	tp = strtok(str, token);
	retVec.x = static_cast<f32>(atof(tp));

	// Y
	tp = strtok(NULL, token);
	retVec.y = static_cast<f32>(atof(tp));
	
	// Z
	tp = strtok(NULL, token);
	retVec.z = static_cast<f32>(atof(tp));

	return retVec;
}

//===========================================================================
/*!	@brief	�f�B���N�g���p�X���K��
	@param	filePath	: �t�@�C���p�X
	@return	�f�B���N�g���p�X
*/
//===========================================================================
std::string GetDirectoryPath( std::string filePath )
{
	std::string ret = filePath;

	// �Ō�̃X���b�V���E�o�b�N�X���b�V���̈ʒu������
	const s32	pathSize	= filePath.size();
	for( s32 i = pathSize - 1; 0 < i; --i ) {
		char searchChar	= filePath.at(i);

		if( (searchChar == '/') || (searchChar == '\\') ) {
			if( i == pathSize - 1 ) {
				continue;
			}
			//�Ō�Ƀk�����������H
			//ret.at(i + 1)	= '\0';	 
			//ret.resize(i + 1);
			ret.resize(i + 1);

			break;
		}
	}

	return ret;
}


}	// namespace nk


