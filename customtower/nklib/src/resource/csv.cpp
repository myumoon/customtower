//=============================================================================
/*!	@file	csv.h

	@brief	csv

	@author	ryunosuke ide
	@date	2013.05.28
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/utility/csv.h"
#include "../../include/file/file.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed
namespace nk {
const resource::ResourceManager*	Csv::ResourceMng	= NULL;
}

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

namespace nk {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
Csv::Csv()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
Csv::~Csv()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void Csv::_Init( void )
{
	m_innerCreate	= false;
}


//===========================================================================
/*!	@brief	�I������
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
/*!	@brief		�Ǎ���
	@param		file	�t�@�C����
	@return		----
*/
//===========================================================================
bool Csv::Load( const char* file )
{
	m_csvData		= new DataTable();
	m_innerCreate	= true;

	FileHandle	csvFileHandle	= OpenFile( file, FILE_OPEN_TEXT );
	u32	fileSize	= GetFileSize( csvFileHandle );

	// �Ǎ���
	{
		char	fileBuf	= new char[fileSize];

		LoadFile( fileBuf, fileSize, csvFileHandle );

		// ���
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
/*!	@brief		�o�^
	@param		file	�t�@�C����
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
