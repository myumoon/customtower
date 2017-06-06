//=============================================================================
/*!	@file	file.cpp

	@brief	�t�@�C������

	@author	��� ���V��
	@date	2013/02/04
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================


//-------------------------------�C���N���[�h-------------------------------
#include "../../include/file/file.h"

#ifdef _WINWOWS
#include <winsock2.h>
#include <windows.h>
#include <Shlwapi.h>
#endif

#include <stdio.h>
#include "general.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {
	
	
}	// unnamed


//---------------------------------�֐���`---------------------------------

namespace nk {

//===========================================================================
/*!	@brief	�t�@�C���g���q���K��
	@param	filePath	�t�@�C���p�X
	@return	�g���q
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
/*!	@brief	�t�@�C���I�[�v��
	@param	filePath	�t�@�C���p�X
	@return	true.����	false.���s
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
/*!	@brief	�t�@�C���I�[�v��
	@param	filePath	�t�@�C���p�X
	@return	true.����	false.���s
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
/*!	@brief	�t�@�C�������
	@param	handle	�t�@�C���n���h��
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
/*!	@brief	�t�@�C���Ǎ���
	@param	[out] buf			�o�̓o�b�t�@
	@param	[in]  bufSize		�o�̓o�b�t�@�T�C�Y
	@param	[in]  handle		�Ǎ��݃t�@�C���n���h��
	@return	���ۂɓǂݍ��񂾃T�C�Y
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
/*!	@brief	�t�@�C���Ǎ���
	@param	[out] buf			�o�̓o�b�t�@
	@param	[in]  bufSize		�o�̓o�b�t�@�T�C�Y
	@param	[in]  handle		�Ǎ��݃t�@�C���n���h��
	@param	[in]  readOffset	�Ǎ��݃I�t�Z�b�g
	@param	[in]  readSize		�Ǎ��݃T�C�Y
	@return	���ۂɓǂݍ��񂾃T�C�Y
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
/*!	@brief		�t�@�C���T�C�Y�擾
	@param		handle	�t�@�C���n���h��
	@return		----
*/
//===========================================================================
u32 GetFileSize( FileHandle handle )
{
	if( handle.status != NK_FILE_OPEN_OK ) {
		ASSERT( false, "file load error : %s", handle.fileName );
		return 0;
	}

	u32		nowPos	= ftell( handle.fp );	// ���݈ʒu��ۑ�

	fseek( handle.fp, 0, SEEK_END );
	u32	size	= ftell( handle.fp );

	fseek( handle.fp, nowPos, SEEK_SET );	// �߂��Ă���

	return size;
}

	
}	// namespace nk
