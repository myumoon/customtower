//=============================================================================
/*!	@file	csvLoader.h

	@brief	CSV���[�h

	@author	ryunosuke ide
	@date	2013.05.30
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/file/csvLoader.h"
#include "../../include/general.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace nk {

//--------------------------------Cell--------------------------------
	
//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CsvLoader::Cell::Cell()
{
	memset( this->cellData, 0, sizeof(this->cellData) );
}

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	data	�Z���f�[�^
	@param	----
*/
//===========================================================================
CsvLoader::Cell::Cell( const char* data )
{
	memset( this->cellData, 0, sizeof(this->cellData) );
	SetData( data );
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	cell	�Z���f�[�^
	@param	----
*/
//===========================================================================
CsvLoader::Cell::Cell( const CsvLoader::Cell& cell )
{
	memset( this->cellData, 0, sizeof(this->cellData) );
	SetData( cell.cellData );
}


//===========================================================================
/*!	@brief		�f�[�^�Z�b�g
	@param		data		�f�[�^
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
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CsvLoader::Row::Row()
{
	this->colData.reserve( 64 );
	
}

//===========================================================================
/*!	@brief		�Z���ǉ�
	@param		cellData	�ǉ�����Z���̃f�[�^
	@return		----
*/
//===========================================================================
void CsvLoader::Row::AddCell( const char* cellData )
{
	this->colData.push_back( Cell(cellData) );
	
}

//--------------------------------CsvDataTbl--------------------------------

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CsvLoader::CsvDataTbl::CsvDataTbl()
{
	this->row	= 1;
	this->rowData.resize( this->row );
	
}

//===========================================================================
/*!	@brief		�s�ǉ�
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
/*!	@brief		�Z���f�[�^�ǉ�
	@param		cellData	�f�[�^
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
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CsvLoader::CsvLoader()
{
	_Init();
}



//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CsvLoader::CsvLoader( const char* file )
{
	_Init();
	Load( file );
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
CsvLoader::~CsvLoader()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void CsvLoader::_Init( void )
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void CsvLoader::_Term( void )
{

}


//===========================================================================
/*!	@brief		���[�h
	@param		file	�t�@�C����
	@return		----
*/
//===========================================================================
bool CsvLoader::Load( const char* file )
{
	//FileHandle	fileHandle	= OpenFile( file, FILE_OPEN_TEXT | FILE_OPEN_READ );
	FileHandle	fileHandle	= OpenFile( file, "r+" );

	const u32	bufSize	= GetFileSize( fileHandle );
	char*		dataBuf	= new char[bufSize + 1];

	// ��U�S���o�b�t�@�ɏ悹��
	LoadFile( dataBuf, bufSize, fileHandle );

	_Parse( dataBuf, bufSize );

	SafeDeleteArray( dataBuf );

	CloseFile( fileHandle );
	
	return true;
}


//===========================================================================
/*!	@brief		���
	@param		dataBuf	�f�[�^�o�b�t�@
	@return		----
*/
//===========================================================================
void CsvLoader::_Parse( char* dataBuf, u32 bufSize )
{
	u32		dataIdx			= 0;	// ���݈ʒu
	u32		cellStartIdx	= 0;	// �Z���J�n�ʒu
	bool	newLine			= false;

	for( ; dataIdx < bufSize; ) {
		newLine		= false;

		if( dataBuf[dataIdx] == ',' ) {
			dataBuf[dataIdx]	= '\0';

			// �J���}���A���ő������ꍇ�͋󕶎������Ă���
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
