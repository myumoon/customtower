//=============================================================================
/*!	@file	csvReader.h

	@brief	CSV�Ǎ���

	@author	ryunosuke ide
	@date	2013.05.30
*/
//=============================================================================


#ifndef __CSV_READER_H__
#define __CSV_READER_H__

#include <vector>
#include "file.h"


namespace nk {

//=============================================================================
/*!
								CSV���[�h
*/
//=============================================================================
class CsvReader {
	
public:

	//-----------------------�^��`--------------------------
	
	//! 1�}�X
	struct CallData {
// 		std::string	cellData;			//!< �f�[�^
		char	cellData[256];			//!< �f�[�^

		//! �R���X�g���N�^
		CallData( void );
		CallData( const char* data );
		CallData( const CallData& cell );

		//! �f�[�^�Z�b�g
		void	SetData( const char* data );
	};
	typedef std::vector<CallData>	VecCell;
	
	//! �s
	struct RowData {
		VecCell	colData;	//!< ��f�[�^

		//! �R���X�g���N�^
		RowData( void );

		//! �f�[�^�ǉ�
		void	AddCell( const char* cellData );

		//! �f�[�^���擾
		u32		GetLength( void ) const;
	};
	typedef std::vector<RowData> VecRow;
	
	//! �f�[�^�e�[�u��
	struct CsvDataTbl {
		VecRow	rowData;	//!< �s�f�[�^
		s32		row;		//!< �s
		s32		col;		//!< ��

		//! �R���X�g���N�^
		CsvDataTbl( void );

		//! �s�ǉ�
		void AddRow( void );

		//! �f�[�^�ǉ�
		void AddCell( const char* cellData );

		//! �s���擾
		u32	GetRowSize( void ) const;
	};
	
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		���[�h
	*/
	//===========================================================================
	bool		Load( const char* file );

	//===========================================================================
	/*!	@brief		�s�擾
	*/
	//===========================================================================
 	VecRow&		Row( void );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	// ���
	void	_Parse( char* dataBuf, u32 bufSize );

	//----------------------�����o�ϐ�-----------------------
	FileHandle			m_fileHandle;		//!< �t�@�C���n���h��
	CsvDataTbl			m_data;				//!< ���[�h�f�[�^

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			CsvReader();
			CsvReader( const char* file );
	virtual~CsvReader();
};
	
}	// namespace nk



#endif  // __CSV_READER_H__