//=============================================================================
/*!	@file	csv.h

	@brief	csv

	@author	ryunosuke ide
	@date	2013.05.28
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/utility/csv.h"
#include "../../include/file/file.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed
namespace nk {
const resource::ResourceManager*	Csv::ResourceMng	= NULL;
}

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

namespace nk {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Csv::Csv()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Csv::~Csv()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Csv::_Init( void )
{
	m_innerCreate	= false;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Csv::_Term( void )
{
	if( m_innerCreate && m_csvData ) {
		SafeDelete( m_csvData );
	}
}


//===========================================================================
/*!	@brief		読込み
	@param		file	ファイル名
	@return		----
*/
//===========================================================================
bool Csv::Load( const char* file )
{
	m_csvData		= new DataTable();
	m_innerCreate	= true;

	FileHandle	csvFileHandle	= OpenFile( file, FILE_OPEN_TEXT );
	u32	fileSize	= GetFileSize( csvFileHandle );

	// 読込み
	{
		char	fileBuf	= new char[fileSize];

		LoadFile( fileBuf, fileSize, csvFileHandle );

		// 解析
		{
			for( u32 i = 0; i < fileSize; ++i ) {
				#error
			}
		}

		SafeDelete( fileBuf );
	}

	CloseFile( csvFileHandle );
	
	return true;
}


//===========================================================================
/*!	@brief		登録
	@param		file	ファイル名
	@return		----
*/
//===========================================================================
bool Csv::Register( const char* file )
{
	NULL_ASSERT( ResourceMng );

	m_csvData		= const_cast<DataTable*>( ResourceMng->GetCsv( file ) );
	m_innerCreate	= false;
	
	return true;
}

	
}	// namespace nk
