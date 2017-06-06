//=============================================================================
/*!	@file	layoutXmlWriter.h

	@brief	レイアウトXML書き込み

	@author	ryunosuke ide
	@date	2013.06.10
*/
//=============================================================================


#ifndef __LAYOUT_XML_WRITER_H__
#define __LAYOUT_XML_WRITER_H__

#include "./xercesUtility.h"
#include "./xercesParser.h"


namespace nk {

namespace graphics {
class Layout;
class LayoutPartsBox;
class LayoutParts;
}

//=============================================================================
/*!
							レイアウトXML出力
*/
//=============================================================================
class LayoutXmlWriter {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		ファイル出力
	*/
	//===========================================================================
	void	WriteToFile( const char* file, graphics::Layout* layout );
	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------メンバ変数-----------------------
	XercesParser			m_parser;		//!< パーサー

public:
	//-------------コンストラクタ・デストラクタ--------------
			LayoutXmlWriter();
	virtual~LayoutXmlWriter();
};
	
}	// namespace nk



#endif  // __LAYOUT_XML_WRITER_H__