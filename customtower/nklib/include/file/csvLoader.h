//=============================================================================
/*!	@file	csvLoader.h

	@brief	CSV���[�h

	@author	ryunosuke ide
	@date	2013.05.30
*/
//=============================================================================


#ifndef __CSV_LOADER_H__
#define __CSV_LOADER_H__

#include <vector>
#include "file.h"


namespace nk {

//=============================================================================
/*!
								CSV���[�h
*/
//=============================================================================
class CsvLoader {
	//-----------------------�^��`--------------------------
private:
	
	// 1�}�X
	struct Cell {
		char	cellData[256];			//!< �f�[�^

		// �R���X�g���N�^
		Cell();
		Cell( const char* data );
		Cell( const Cell& cell );

		// �f�[�^�Z�b�g
		void	SetData( const char* data );
	};
	
	// �s
	struct Row {
		std::vector<Cell>	colData;	//!< ��f�[�^

		// �R���X�g���N�^
		Row();

		// �f�[�^�ǉ�
		void	AddCell( const char* cellData );
	};
	
	// �f�[�^�e�[�u��
	struct CsvDataTbl {
		std::vector<Row>	rowData;	//!< �s�f�[�^
		s32					row;		//!< �s
		s32					col;		//!< ��

		// �R���X�g���N�^
		CsvDataTbl();

		// �e�[�u���쐬
// 		void CreateTable( s32 row, s32 col );

		// �s�ǉ�
		void AddRow( void );

		// �f�[�^�ǉ�
		void AddCell( const char* cellData );
	};
	
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		���[�h
	*/
	//===========================================================================
	bool	Load( const char* file );
	
	
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
			CsvLoader();
			CsvLoader( const char* file );
	virtual~CsvLoader();
};
	
}	// namespace nk



#endif  // __CSV_LOADER_H__