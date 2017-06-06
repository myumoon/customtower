//=============================================================================
/*!	@file	file.cpp

	@brief	ファイル操作

	@author	井手 竜之介
	@date	2013/02/04
	@todo	なし
	@bug	なし
*/
//=============================================================================


//-------------------------------インクルード-------------------------------
#include "../../include/file/file.h"

#ifdef _WINWOWS
#include <winsock2.h>
#include <windows.h>
#include <Shlwapi.h>
#endif

#include <stdio.h>
#include "general.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {
	
	
}	// unnamed


//---------------------------------関数定義---------------------------------

namespace nk {

//===========================================================================
/*!	@brief	ファイル拡張子を習得
	@param	filePath	ファイルパス
	@return	拡張子
*/
//===========================================================================
const char* GetExtension( const char* filePath )
{
	const char*	extension = NULL;
	
	extension	= strrchr( filePath, '.' );
	if( extension ) {
		if( *extension == '.' ) {
			++extension;
		}
	}

	return extension;
}


#if 0
//===========================================================================
/*!	@brief	ファイルオープン
	@param	filePath	ファイルパス
	@return	true.成功	false.失敗
*/
//===========================================================================
FileHandle OpenFile( const char* filePath, FILE_OPEN_MODE mode )
{
	FileHandle	handle;

	handle.status	= NK_FILE_NOT_OPEN;
	
#if 1//defined(_WINDOWS)

	char	modeStr[32]	= { 0 };
	s32		index		= 0;
	
	#define	ADD_MODE_STR(c)	{modeStr[index++]=c;}


	if( mode & FILE_OPEN_WRITE ) {
		ADD_MODE_STR('w');
	}
	else {
		if( mode & FILE_OPEN_ADD ) {
			ADD_MODE_STR('a');
		}
		else {
			ADD_MODE_STR('r');
		}
	}
	
	if( mode & FILE_OPEN_BINARY ) {
		ADD_MODE_STR('b')
	}

	ADD_MODE_STR('\0');

	
	handle.fp		= fopen( filePath, modeStr );
	if( handle.fp ) {
		handle.status	|= NK_FILE_OPEN_OK;
	}
	else {
		handle.status	|= NK_FILE_OPEN_ERROR;
	}
	
	#undef ADD_MODE_STR
#else
	#error
#endif

	strcpy( handle.fileName, filePath );
	
	return handle;
}
#endif

//===========================================================================
/*!	@brief	ファイルオープン
	@param	filePath	ファイルパス
	@return	true.成功	false.失敗
*/
//===========================================================================
FileHandle OpenFile( const char* filePath, const char* mode )
{
	FileHandle	handle;

	handle.status	= NK_FILE_NOT_OPEN;
	
#if 1//defined(_WINDOWS)
	handle.fp		= fopen( filePath, mode );
	if( handle.fp ) {
		handle.status	|= NK_FILE_OPEN_OK;
	}
	else {
		handle.status	|= NK_FILE_OPEN_ERROR;
	}
	
#else
	#error
#endif

	strcpy( handle.fileName, filePath );
	
	return handle;
}


//===========================================================================
/*!	@brief	ファイルを閉じる
	@param	handle	ファイルハンドル
	@return	----
*/
//===========================================================================
void CloseFile( FileHandle handle )
{
	
	if( handle.status & NK_FILE_OPEN_OK ) {
#if 1//defined(_WINDOWS)
		fclose( handle.fp );
#else
	#error
#endif
	}
	
}
	
//===========================================================================
/*!	@brief	ファイル読込み
	@param	[out] buf			出力バッファ
	@param	[in]  bufSize		出力バッファサイズ
	@param	[in]  handle		読込みファイルハンドル
	@return	実際に読み込んだサイズ
*/
//===========================================================================
u32 LoadFile( void* buf, u32 bufSize, FileHandle handle)
{
	s32 result = 0;
	
	if( handle.status != NK_FILE_OPEN_OK ) {
		ASSERT( false, "file load error : %s", handle.fileName );
		return 0;
	}
	
#if 1//defined(_WINDOWS)
	s32 c;
	u32	bufIdx	= 0;
	u8*	copyBuf	= reinterpret_cast<u8*>(buf);
	while( (c = getc(handle.fp)) != EOF ) {
		copyBuf[bufIdx] = c;
		++bufIdx;
	}
	result = bufIdx;
#else
	#error
#endif
	
	
	return result;
}

	
//===========================================================================
/*!	@brief	ファイル読込み
	@param	[out] buf			出力バッファ
	@param	[in]  bufSize		出力バッファサイズ
	@param	[in]  handle		読込みファイルハンドル
	@param	[in]  readOffset	読込みオフセット
	@param	[in]  readSize		読込みサイズ
	@return	実際に読み込んだサイズ
*/
//===========================================================================
u32 LoadFile( void* buf, u32 bufSize, FileHandle handle, u32 readOffset, u32 readSize )
{
	s32 result = 0;

	if( handle.status != NK_FILE_OPEN_OK ) {
		ASSERT( false, "file load error : %s", handle.fileName );
		return 0;
	}

	if( bufSize < readSize ) {
		readSize	= bufSize;
	}

#if 1//defined(_WINDOWS)
	fseek( handle.fp, (long)readOffset, SEEK_SET );
	fread( buf, readSize, 1,  handle.fp );

#else
	#error
#endif
	
	result	= readSize;

	
	return result;
}


//===========================================================================
/*!	@brief		ファイルサイズ取得
	@param		handle	ファイルハンドル
	@return		----
*/
//===========================================================================
u32 GetFileSize( FileHandle handle )
{
	if( handle.status != NK_FILE_OPEN_OK ) {
		ASSERT( false, "file load error : %s", handle.fileName );
		return 0;
	}

	u32		nowPos	= ftell( handle.fp );	// 現在位置を保存

	fseek( handle.fp, 0, SEEK_END );
	u32	size	= ftell( handle.fp );

	fseek( handle.fp, nowPos, SEEK_SET );	// 戻しておく

	return size;
}

	
}	// namespace nk
