//=============================================================================
/*!	@file	csv.h

	@brief	csv

	@author	ryunosuke ide
	@date	2013.05.28
*/
//=============================================================================

#ifndef __CSV_H__
#define __CSV_H__


#include <vector>



namespace nk {


//=============================================================================
/*!
								CSV
*/
//=============================================================================
class Csv {
public:
	//-----------------------型定義--------------------------

	//! 1マスのデータ
	struct CellData {
		char	str[256];				
	};

	//! 行データ
	struct RowData {
		std::vector<CellData>	rowData;

		RowData() {
			rowData.reserve( 128 );
		}
	};

	//! データテーブル
	struct DataTable {
		std::vector<RowData>	dataTbl;	//!< 行データ
		s32						colNum;		//!< 列数

		//! コンストラクタ
		DataTable() {
			Init();
		}

		//! 初期化
		void Init( void ) {
			dataTbl.reserve( 1024 );
			colNum	= 0;
		}

		//! 行追加
		void AddLine( const RowData& rowData ) {
			dataTbl.push_back( rowData );
			if( static_cast<u32>(colNum) < rowData.rowData.size() ) {
				colNum	= rowData.rowData.size();
			}
		}

		//! 行数取得
		s32 GetRowNum( void ) const {
			return dataTbl.size();
		}

		//! 列数取得
		s32 GetColNum( void ) const {
			return colNum;
		}
	};
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		読込み
	*/
	//===========================================================================
	bool		Load( const char* file );

	//===========================================================================
	/*!	@brief		ロードされたCSVファイルを登録
	*/
	//===========================================================================
	void		Register( const char* file );

	// リソース管理
	static const resource::ResourceManager*	ResourceMng;
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	DataTable*		m_csvData;		//!< CSVデータ
	bool			m_innerCreate;	//!< newしたならtrue

public:
	//-------------コンストラクタ・デストラクタ--------------
			Csv();
	virtual~Csv();
};
	
}	// namespace nk







#endif  // __CSV_H__