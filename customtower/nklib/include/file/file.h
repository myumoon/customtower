//=============================================================================
/*!	@file	file.h

	@brief	ファイル操作

	@author	井手 竜之介
	@date	2013/02/04
	@todo	なし
	@bug	なし
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

#pragma warning( disable : 4996 )	// ファイル関係の警告を消す

#define STR_SIZE			256			// 文字列読み込み最大数

namespace nk {


/*================================================
				ファイルハンドル
	status
		NK_FILE_NOT_OPEN
		NK_FILE_OPEN_OK
		NK_FILE_OPEN_ERROR
================================================*/
struct FileHandle {
	FILE*	fp;					//!< ファイルポインタ
	s32		status;				//!< ファイルの状態
	char	fileName[128];		//!< ファイル名

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

	//! 利用可能ならtrueを返す
	bool	IsEnable( void ) const {
		return (fp != NULL);
	}
};


/*================================================
			自動クローズファイルハンドル
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
			ファイルオープンモード
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


	
//! ファイル拡張子を習得
extern const char*	GetExtension( const char* filePath );

	
//! ファイル読み込み
//extern FileHandle	OpenFile( const char* filePath, FILE_OPEN_MODE mode );
extern FileHandle	OpenFile( const char* filePath, const char* mode );

//! ファイルを閉じる
extern void			CloseFile( FileHandle handle );
	
//! ファイル読み込み
extern u32			LoadFile( void* buf, u32 bufSize, FileHandle handle );

/*! ファイル読み込み
	@param	buf[out]	出力バッファ
	@param	bufSize		出力バッファサイズ
	@param	handle		読込みファイルハンドル
	@param	readOffset	読込みオフセット
	@param	readSize	読込みサイズ
*/
extern u32			LoadFile( void* buf, u32 bufSize, FileHandle handle, u32 readOffset, u32 readSize );

//! ファイルサイズ取得
extern u32			GetFileSize( FileHandle handle );

}	// namespace nk


#endif  // __FILE_H__