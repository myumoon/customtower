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
	//-----------------------�^��`--------------------------

	//! 1�}�X�̃f�[�^
	struct CellData {
		char	str[256];				
	};

	//! �s�f�[�^
	struct RowData {
		std::vector<CellData>	rowData;

		RowData() {
			rowData.reserve( 128 );
		}
	};

	//! �f�[�^�e�[�u��
	struct DataTable {
		std::vector<RowData>	dataTbl;	//!< �s�f�[�^
		s32						colNum;		//!< ��

		//! �R���X�g���N�^
		DataTable() {
			Init();
		}

		//! ������
		void Init( void ) {
			dataTbl.reserve( 1024 );
			colNum	= 0;
		}

		//! �s�ǉ�
		void AddLine( const RowData& rowData ) {
			dataTbl.push_back( rowData );
			if( static_cast<u32>(colNum) < rowData.rowData.size() ) {
				colNum	= rowData.rowData.size();
			}
		}

		//! �s���擾
		s32 GetRowNum( void ) const {
			return dataTbl.size();
		}

		//! �񐔎擾
		s32 GetColNum( void ) const {
			return colNum;
		}
	};
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�Ǎ���
	*/
	//===========================================================================
	bool		Load( const char* file );

	//===========================================================================
	/*!	@brief		���[�h���ꂽCSV�t�@�C����o�^
	*/
	//===========================================================================
	void		Register( const char* file );

	// ���\�[�X�Ǘ�
	static const resource::ResourceManager*	ResourceMng;
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	DataTable*		m_csvData;		//!< CSV�f�[�^
	bool			m_innerCreate;	//!< new�����Ȃ�true

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			Csv();
	virtual~Csv();
};
	
}	// namespace nk







#endif  // __CSV_H__