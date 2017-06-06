//=============================================================================
/*!	@file	csvLoader.h

	@brief	CSVロード

	@author	ryunosuke ide
	@date	2013.05.30
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/file/csvLoader.h"
#include "../../include/general.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace nk {

//--------------------------------Cell--------------------------------
	
//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvLoader::Cell::Cell()
{
	memset( this->cellData, 0, sizeof(this->cellData) );
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	data	セルデータ
	@param	----
*/
//===========================================================================
CsvLoader::Cell::Cell( const char* data )
{
	memset( this->cellData, 0, sizeof(this->cellData) );
	SetData( data );
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	cell	セルデータ
	@param	----
*/
//===========================================================================
CsvLoader::Cell::Cell( const CsvLoader::Cell& cell )
{
	memset( this->cellData, 0, sizeof(this->cellData) );
	SetData( cell.cellData );
}


//===========================================================================
/*!	@brief		データセット
	@param		data		データ
	@return		----
*/
//===========================================================================
void CsvLoader::Cell::SetData( const char* data )
{
	if( data == NULL ) {
		return;
	}
	if( *data == '\0' ) {
		return;
	}
	
	strcpy_s( this->cellData, sizeof(this->cellData), data );
	
}

//--------------------------------Row--------------------------------

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvLoader::Row::Row()
{
	this->colData.reserve( 64 );
	
}

//===========================================================================
/*!	@brief		セル追加
	@param		cellData	追加するセルのデータ
	@return		----
*/
//===========================================================================
void CsvLoader::Row::AddCell( const char* cellData )
{
	this->colData.push_back( Cell(cellData) );
	
}

//--------------------------------CsvDataTbl--------------------------------

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvLoader::CsvDataTbl::CsvDataTbl()
{
	this->row	= 1;
	this->rowData.resize( this->row );
	
}

//===========================================================================
/*!	@brief		行追加
	@param		----
	@return		----
*/
//===========================================================================
void CsvLoader::CsvDataTbl::AddRow( void )
{
	this->rowData.push_back( Row() );
	++this->row;
	
}


//===========================================================================
/*!	@brief		セルデータ追加
	@param		cellData	データ
	@return		----
*/
//===========================================================================
void CsvLoader::CsvDataTbl::AddCell( const char* cellData )
{
	(*this->rowData.rbegin()).AddCell( cellData );
	++this->col;
}

//--------------------------------CsvLoader--------------------------------


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvLoader::CsvLoader()
{
	_Init();
}



//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvLoader::CsvLoader( const char* file )
{
	_Init();
	Load( file );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
CsvLoader::~CsvLoader()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void CsvLoader::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void CsvLoader::_Term( void )
{

}


//===========================================================================
/*!	@brief		ロード
	@param		file	ファイル名
	@return		----
*/
//===========================================================================
bool CsvLoader::Load( const char* file )
{
	//FileHandle	fileHandle	= OpenFile( file, FILE_OPEN_TEXT | FILE_OPEN_READ );
	FileHandle	fileHandle	= OpenFile( file, "r+" );

	const u32	bufSize	= GetFileSize( fileHandle );
	char*		dataBuf	= new char[bufSize + 1];

	// 一旦全部バッファに乗せる
	LoadFile( dataBuf, bufSize, fileHandle );

	_Parse( dataBuf, bufSize );

	SafeDeleteArray( dataBuf );

	CloseFile( fileHandle );
	
	return true;
}


//===========================================================================
/*!	@brief		解析
	@param		dataBuf	データバッファ
	@return		----
*/
//===========================================================================
void CsvLoader::_Parse( char* dataBuf, u32 bufSize )
{
	u32		dataIdx			= 0;	// 現在位置
	u32		cellStartIdx	= 0;	// セル開始位置
	bool	newLine			= false;

	for( ; dataIdx < bufSize; ) {
		newLine		= false;

		if( dataBuf[dataIdx] == ',' ) {
			dataBuf[dataIdx]	= '\0';

			// カンマが連続で続いた場合は空文字を入れておく
			if( dataBuf[cellStartIdx] == '\0' ) {
				m_data.AddCell( "" );
			}
			else {
				m_data.AddCell( &dataBuf[cellStartIdx] );
			}
			cellStartIdx	= dataIdx + 1;
		}

		if( dataBuf[dataIdx] == '\n' ) {
			dataBuf[dataIdx]	= '\0';
			newLine				= true;
			++dataIdx;
		}
		if( dataBuf[dataIdx] == '\r' ) {
			dataBuf[dataIdx]	= '\0';
			newLine				= true;
			++dataIdx;
		}

		if( newLine ) {
			m_data.AddCell( &dataBuf[cellStartIdx] );
			m_data.AddRow();
			cellStartIdx	= dataIdx;
		}
		else {
			++dataIdx;
		}
	}

	dataBuf[dataIdx]	= '\0';
	m_data.AddCell( &dataBuf[cellStartIdx] );
	
}

	
}	// namespace nk
