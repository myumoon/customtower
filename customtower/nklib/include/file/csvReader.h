//=============================================================================
/*!	@file	csvReader.h

	@brief	CSV読込み

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
								CSVロード
*/
//=============================================================================
class CsvReader {
	
public:

	//-----------------------型定義--------------------------
	
	//! 1マス
	struct CallData {
// 		std::string	cellData;			//!< データ
		char	cellData[256];			//!< データ

		//! コンストラクタ
		CallData( void );
		CallData( const char* data );
		CallData( const CallData& cell );

		//! データセット
		void	SetData( const char* data );
	};
	typedef std::vector<CallData>	VecCell;
	
	//! 行
	struct RowData {
		VecCell	colData;	//!< 列データ

		//! コンストラクタ
		RowData( void );

		//! データ追加
		void	AddCell( const char* cellData );

		//! データ数取得
		u32		GetLength( void ) const;
	};
	typedef std::vector<RowData> VecRow;
	
	//! データテーブル
	struct CsvDataTbl {
		VecRow	rowData;	//!< 行データ
		s32		row;		//!< 行
		s32		col;		//!< 列

		//! コンストラクタ
		CsvDataTbl( void );

		//! 行追加
		void AddRow( void );

		//! データ追加
		void AddCell( const char* cellData );

		//! 行数取得
		u32	GetRowSize( void ) const;
	};
	
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		ロード
	*/
	//===========================================================================
	bool		Load( const char* file );

	//===========================================================================
	/*!	@brief		行取得
	*/
	//===========================================================================
 	VecRow&		Row( void );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	// 解析
	void	_Parse( char* dataBuf, u32 bufSize );

	//----------------------メンバ変数-----------------------
	FileHandle			m_fileHandle;		//!< ファイルハンドル
	CsvDataTbl			m_data;				//!< ロードデータ

public:
	//-------------コンストラクタ・デストラクタ--------------
			CsvReader();
			CsvReader( const char* file );
	virtual~CsvReader();
};
	
}	// namespace nk



#endif  // __CSV_READER_H__