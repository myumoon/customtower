//=============================================================================
/*!	@file	csvLoader.h

	@brief	CSVロード

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
								CSVロード
*/
//=============================================================================
class CsvLoader {
	//-----------------------型定義--------------------------
private:
	
	// 1マス
	struct Cell {
		char	cellData[256];			//!< データ

		// コンストラクタ
		Cell();
		Cell( const char* data );
		Cell( const Cell& cell );

		// データセット
		void	SetData( const char* data );
	};
	
	// 行
	struct Row {
		std::vector<Cell>	colData;	//!< 列データ

		// コンストラクタ
		Row();

		// データ追加
		void	AddCell( const char* cellData );
	};
	
	// データテーブル
	struct CsvDataTbl {
		std::vector<Row>	rowData;	//!< 行データ
		s32					row;		//!< 行
		s32					col;		//!< 列

		// コンストラクタ
		CsvDataTbl();

		// テーブル作成
// 		void CreateTable( s32 row, s32 col );

		// 行追加
		void AddRow( void );

		// データ追加
		void AddCell( const char* cellData );
	};
	
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		ロード
	*/
	//===========================================================================
	bool	Load( const char* file );
	
	
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
			CsvLoader();
			CsvLoader( const char* file );
	virtual~CsvLoader();
};
	
}	// namespace nk



#endif  // __CSV_LOADER_H__