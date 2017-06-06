//=============================================================================
/*!	@file	xercesParser.h

	@brief	xercesc parser

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/file/xercesParser.h"

#include "../../include/general.h"
#include "../../include/utility/utility.h"

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
XercesParser::XercesParser()
{
	_Init();
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
XercesParser::XercesParser( const char* xmlfile )
{
	_Init();
	Parse( xmlfile );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
XercesParser::~XercesParser()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void XercesParser::_Init( void )
{
	m_parser	= new XercesDOMParser();


}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void XercesParser::_Term( void )
{
	SafeDelete( m_parser );
}


//===========================================================================
/*!	@brief		解析
	@param		xmlfile		xmlファイル名
	@return		----
*/
//===========================================================================
bool XercesParser::Parse( const char* xmlfile )
{
	m_parser->parse( xmlfile );

	m_document		= m_parser->getDocument();
	m_elementRoot	= m_document->getDocumentElement();
	
	return true;
}


//===========================================================================
/*!	@brief		ドキュメントの関連付け
	@param		doc		ドキュメント
	@return		----
*/
//===========================================================================
void XercesParser::RegisterDocument( DOMDocument* doc )
{
	m_document		= doc;
	m_elementRoot	= m_document->getDocumentElement();
}


//===========================================================================
/*!	@brief		初期化済みならtrueを返す
	@param		----
	@return		----
*/
//===========================================================================
bool XercesParser::Initialized( void ) const
{

	return m_initialized;
}

//===========================================================================
/*!	@brief		ドキュメント取得
	@param		----
	@return		----
*/
//===========================================================================
DOMDocument* XercesParser::GetDocument( void )
{
	ASSERT( Initialized(), "not initialized." );

	return m_document;
}


//===========================================================================
/*!	@brief		ドキュメント取得
	@param		----
	@return		----
*/
//===========================================================================
DOMElement* XercesParser::GetRootElement( void )
{
	ASSERT( Initialized(), "not initialized." );

	return m_elementRoot;
}


//===========================================================================
/*!	@brief		タグ名で子供を検索
	@param		tagName		タグ名
	@return		----
*/
//==========================================================================
DOMNodeList* XercesParser::GetElementByTagName( DOMElement* elemenent, const char* tagName )
{
	CharToXMLCh		xmlch( tagName );
	DOMNodeList*	nodeList	= elemenent->getElementsByTagName( xmlch.GetXMLCh() );
	
	return nodeList;
}

	
}	// namespace nk