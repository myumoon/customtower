//=============================================================================
/*!	@file	csvReader.h

	@brief	CSV読込み

	@author	ryunosuke ide
	@date	2013.05.30
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/file/csvReader.h"
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

//--------------------------------CallData--------------------------------
	
//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvReader::CallData::CallData()
{
	memset( this->cellData, 0, sizeof(this->cellData) );
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	data	セルデータ
	@param	----
*/
//===========================================================================
CsvReader::CallData::CallData( const char* data )
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
CsvReader::CallData::CallData( const CsvReader::CallData& cell )
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
void CsvReader::CallData::SetData( const char* data )
{
	if( data == NULL ) {
		return;
	}
	if( *data == '\0' ) {
		return;
	}
	
	strcpy_s( this->cellData, sizeof(this->cellData), data );
	
}

//--------------------------------RowData--------------------------------

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvReader::RowData::RowData()
{
	this->colData.reserve( 64 );
	
}

//===========================================================================
/*!	@brief		セル追加
	@param		cellData	追加するセルのデータ
	@return		----
*/
//===========================================================================
void CsvReader::RowData::AddCell( const char* cellData )
{
	this->colData.push_back( CallData(cellData) );
	
}



//===========================================================================
/*!	@brief		セル数取得
	@param		----
	@return		----
*/
//===========================================================================
u32 CsvReader::RowData::GetLength( void ) const
{
	
	return colData.size();
}

//--------------------------------CsvDataTbl--------------------------------

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvReader::CsvDataTbl::CsvDataTbl()
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
void CsvReader::CsvDataTbl::AddRow( void )
{
	this->rowData.push_back( CsvReader::RowData() );
	++this->row;
	
}


//===========================================================================
/*!	@brief		セルデータ追加
	@param		cellData	データ
	@return		----
*/
//===========================================================================
void CsvReader::CsvDataTbl::AddCell( const char* cellData )
{
	(*this->rowData.rbegin()).AddCell( cellData );
	++this->col;
}

//===========================================================================
/*!	@brief		行数取得
	@param		----
	@return		----
*/
//===========================================================================
u32 CsvReader::CsvDataTbl::GetRowSize( void ) const
{
	
	return rowData.size();
}

//--------------------------------CsvReader--------------------------------


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvReader::CsvReader()
{
	_Init();
}



//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CsvReader::CsvReader( const char* file )
{
	_Init();
	Load( file );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
CsvReader::~CsvReader()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void CsvReader::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void CsvReader::_Term( void )
{

}


//===========================================================================
/*!	@brief		ロード
	@param		file	ファイル名
	@return		----
*/
//===========================================================================
bool CsvReader::Load( const char* file )
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
void CsvReader::_Parse( char* dataBuf, u32 bufSize )
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

//===========================================================================
/*!	@brief		行取得
	@param		----
	@return		行vector
*/
//===========================================================================
CsvReader::VecRow& CsvReader::Row( void )
{

	return m_data.rowData;
}
	
}	// namespace nk
