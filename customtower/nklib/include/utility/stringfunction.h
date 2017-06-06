//=============================================================================
/*!	@file	stringfunction.h

	@brief	�����񑀍�֐�

	@author	��� ���V��
	@date	2011/11/24
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================



#ifndef __STRINGFUNCTION_H__
#define __STRINGFUNCTION_H__

#include <shlwapi.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "../typedef.h"
#include "../math/vector.h"
#include "../math/matrix.h"

#pragma warning( disable : 4996 )	// �t�@�C���֌W�̌x��������

#define STR_SIZE 256		// ������ǂݍ��ݍő吔

namespace nk {

/*! �������r */
extern bool			Compare( const char* lhs, const char* rhs );

/*! ������̐擪�|�C���^���w�蕶����̎��܂ňړ����� */
std::string			FindStr( const char *origin, const char *find1, const char *find2 );

/*! ������̐擪�A�h���X�����̕����̌��ɐݒ� */
s32					ChangeStrTop( char **origin, const char *find );

/*! ����̕����񂪊܂܂�Ă���C���f�b�N�X�ԍ��𒲂ׂ� */
s32					SearchStrIndex( const char *origin, const char *find );

/*! �u�� */
void				ChangeCharacter( char *origin, char before, char after );

/*! �����񂩂�x�N�g���ɕϊ� */
nk::math::Vector	GetVectorFromString( char* str, const char* token );

/*! �f�B���N�g���p�X���K�� */
std::string			GetDirectoryPath( std::string filePath );

}	// namespace nk


#endif  // __STRINGFUNCTION_H__