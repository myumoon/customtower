//=============================================================================
/*!	@file	file.h

	@brief	�t�@�C������

	@author	��� ���V��
	@date	2013/02/04
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================



#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <string.h>
#include <string>

#include "../typedef.h"
#include "../result.h"

#include "./xercesUtility.h"
#include "./xercesParser.h"
#include "./xercesWriter.h"

#include "./layoutXmlWriter.h"
#include "./layoutParser.h"

#pragma warning( disable : 4996 )	// �t�@�C���֌W�̌x��������

#define STR_SIZE			256			// ������ǂݍ��ݍő吔

namespace nk {


/*================================================
				�t�@�C���n���h��
	status
		NK_FILE_NOT_OPEN
		NK_FILE_OPEN_OK
		NK_FILE_OPEN_ERROR
================================================*/
struct FileHandle {
	FILE*	fp;					//!< �t�@�C���|�C���^
	s32		status;				//!< �t�@�C���̏��
	char	fileName[128];		//!< �t�@�C����

	FileHandle( void ) {
		status	= NK_FILE_NOT_OPEN;
		fp		= NULL;
		memset( fileName, 0, sizeof(fileName) );
	}

	FileHandle( const FileHandle& rhs ) {
		status	= rhs.status;
		fp		= rhs.fp;
		std::strcpy( fileName, rhs.fileName );
	}

	//! ���p�\�Ȃ�true��Ԃ�
	bool	IsEnable( void ) const {
		return (fp != NULL);
	}
};


/*================================================
			�����N���[�Y�t�@�C���n���h��
================================================*/
struct AutoCloseFileHandle : public FileHandle {
	AutoCloseFileHandle( void ) {
	}
	AutoCloseFileHandle( const FileHandle& rhs ) : FileHandle( rhs ) {
	}
	virtual ~AutoCloseFileHandle( void ) {
		if( fp != NULL ) {
			fclose( fp );
		}
	}
	FileHandle	operator =( const FileHandle& rhs ) {
		if( fp ) {
			fclose( fp );
		}
		fp		= rhs.fp;
		status	= rhs.status;
		std::strcpy( fileName, rhs.fileName );
	}
};

/*================================================
			�t�@�C���I�[�v�����[�h
================================================*/
//enum {
//	FILE_OPEN_BINARY	= 0x00000001,
//	FILE_OPEN_TEXT		= 0x00000002,
//
//	FILE_OPEN_WRITE		= 0x00000004,
//	FILE_OPEN_READ		= 0x00000008,
//	
//
//	//FILE_OPEN_NEW		= 0x00000010,
//	FILE_OPEN_ADD		= 0x00000020,
//};
//typedef u32	FILE_OPEN_MODE;


	
//! �t�@�C���g���q���K��
extern const char*	GetExtension( const char* filePath );

	
//! �t�@�C���ǂݍ���
//extern FileHandle	OpenFile( const char* filePath, FILE_OPEN_MODE mode );
extern FileHandle	OpenFile( const char* filePath, const char* mode );

//! �t�@�C�������
extern void			CloseFile( FileHandle handle );
	
//! �t�@�C���ǂݍ���
extern u32			LoadFile( void* buf, u32 bufSize, FileHandle handle );

/*! �t�@�C���ǂݍ���
	@param	buf[out]	�o�̓o�b�t�@
	@param	bufSize		�o�̓o�b�t�@�T�C�Y
	@param	handle		�Ǎ��݃t�@�C���n���h��
	@param	readOffset	�Ǎ��݃I�t�Z�b�g
	@param	readSize	�Ǎ��݃T�C�Y
*/
extern u32			LoadFile( void* buf, u32 bufSize, FileHandle handle, u32 readOffset, u32 readSize );

//! �t�@�C���T�C�Y�擾
extern u32			GetFileSize( FileHandle handle );

}	// namespace nk


#endif  // __FILE_H__