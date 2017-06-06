//=============================================================================
/*!	@file	layoutXmlWriter.h

	@brief	レイアウトXML書き込み

	@author	ryunosuke ide
	@date	2013.06.10
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include "../../include/file/layoutXmlWriter.h"
#include "../../include/file/file.h"

#include "../../include/graphics/layout.h"


using namespace xercesc;

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

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
LayoutXmlWriter::LayoutXmlWriter()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
LayoutXmlWriter::~LayoutXmlWriter()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void LayoutXmlWriter::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void LayoutXmlWriter::_Term( void )
{

}

//===========================================================================
/*!	@brief		ファイル出力
	@param		file	出力ファイル名
	@param		layout	出力レイアウト
	@return		----
*/
//===========================================================================
void LayoutXmlWriter::WriteToFile( const char* file, graphics::Layout* layout )
{
	xercesc::DOMImplementation*	xml			= XercesUtility::CreateXML("Core");
	NULL_ASSERT( xml );
	xercesc::DOMDocument*		doc			= XercesUtility::CreateDocument( xml, "layout" );
	NULL_ASSERT( doc );

	XercesParser		parser;
	parser.RegisterDocument( doc );
	
	xercesc::DOMElement*			rootElement	= XercesUtility::CreateElement( parser.GetDocument(), "root" );
	XercesUtility::SetAttribute( rootElement, "height", "500" );
	XercesUtility::SetAttribute( rootElement, "width", "300" );
	XercesUtility::SetValue( rootElement, "abcdefg" );
	
	parser.GetRootElement()->appendChild( rootElement );


	// 実際の出力
	{
		XercesWriter		writer;
		writer.Write( file, doc );
	}
}
	
}	// namespace nk