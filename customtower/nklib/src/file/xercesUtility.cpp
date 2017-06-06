//=============================================================================
/*!	@file	xercesUtility.h

	@brief	xercesc

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <xercesc/dom/DOM.hpp>

#include "../../include/general.h"
#include "../../include/file/xercesUtility.h"



//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {


using namespace xercesc;

//--------------------------------XercesUtility--------------------------------

	
//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
XercesUtility::XercesUtility()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
XercesUtility::~XercesUtility()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void XercesUtility::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void XercesUtility::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		----
	@return		----
*/
//===========================================================================
bool XercesUtility::Initialize( void )
{
	try {
		XMLPlatformUtils::Initialize();
	}
	catch( ... ) {
		return false;
	}

	return true;
}


//===========================================================================
/*!	@brief		終了処理
	@param		----
	@return		----
*/
//===========================================================================
void XercesUtility::Terminate( void )
{
	XMLPlatformUtils::Terminate();
}


//===========================================================================
/*!	@brief		XML生成
	@param		name
	@return		----
*/
//===========================================================================
DOMImplementation*	XercesUtility::CreateXML( const char* features )
{
	CharToXMLCh	xmlch( features );
	DOMImplementation*	ins	= DOMImplementationRegistry::getDOMImplementation( xmlch.GetXMLCh() );
	
	return ins;
}


//===========================================================================
/*!	@brief		ドキュメント生成
	@param		docName			ドキュメント名
	@param		namespaceName	ネームスペース
	@param		docType			ドキュメントタイプ
	@return		----
*/
//===========================================================================
DOMDocument* XercesUtility::CreateDocument(
	DOMImplementation*			xml,
	const char*					docName,
	const char* 				namespaceName,
	xercesc::DOMDocumentType*	docType
)
{
	NULL_ASSERT( xml );
	NULL_ASSERT( docName );
	CharToXMLCh		xmlchNamespaceName( namespaceName );
	CharToXMLCh		xmlchDocumentName( docName );
	
	return xml->createDocument( xmlchNamespaceName.GetXMLCh(), xmlchDocumentName.GetXMLCh(), docType );
}


//===========================================================================
/*!	@brief		エレメント生成
	@param		doc				ドキュメント
	@param		elementName		エレメント名
	@return		----
*/
//===========================================================================
DOMElement* XercesUtility::CreateElement( xercesc::DOMDocument* doc, const char* elementName )
{
	NULL_ASSERT( doc );
	NULL_ASSERT( elementName );

	if( !doc || !elementName ) {
		return NULL;
	}
			
	CharToXMLCh	xmlchElementName( elementName );
	DOMElement*	retElement	= doc->createElement( xmlchElementName.GetXMLCh() );
	
	return retElement;
}


//===========================================================================
/*!	@brief		属性設定
	@param		element		設定エレメント
	@param		attrName	属性名
	@param		zttrValue	属性
	@return		----
*/
//===========================================================================
void XercesUtility::SetAttribute( DOMElement* element, const char* attrName, const char* attrValue )
{
	NULL_ASSERT( element );
	NULL_ASSERT( attrName );

	if( element && attrName ) {
		const char*	setAttrValue	= attrValue ? attrValue : "";
		CharToXMLCh	xmlchAttrValue( setAttrValue );
		CharToXMLCh	xmlchAttrName( attrName );
		
		element->setAttribute( xmlchAttrName.GetXMLCh(), xmlchAttrValue.GetXMLCh() );
	}
	
}


//===========================================================================
/*!	@brief		値設定
	@param		node	ノード
	@param		value	値
	@return		----
*/
//===========================================================================
void XercesUtility::SetValue( xercesc::DOMNode* node, const char* value )
{
	NULL_ASSERT( node );

	if( node ) {
		CharToXMLCh	xmlchValue( value );
		//node->setNodeValue( xmlchValue.GetXMLCh() );
		node->setTextContent( xmlchValue.GetXMLCh() );
	}
	
}

//--------------------------------XMLChToChar--------------------------------



//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
XMLChToChar::XMLChToChar()
{
	_Init();
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
XMLChToChar::XMLChToChar( XMLCh* xmlch )
{
	_Init();
	Convert( xmlch );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
XMLChToChar::~XMLChToChar()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void XMLChToChar::_Init( void )
{
	m_data	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void XMLChToChar::_Term( void )
{
	_Release();
	
}


//===========================================================================
/*!	@brief		変換
	@param		xmlch	変換文字列
	@return		----
*/
//===========================================================================
void XMLChToChar::Convert( XMLCh* xmlch )
{
	m_data	= XMLString::transcode( xmlch );
}



//===========================================================================
/*!	@brief		char文字列取得
	@param		----
	@return		----
*/
//===========================================================================
char* XMLChToChar::GetChar( void )
{
	
	return m_data;
}


//===========================================================================
/*!	@brief		リリース
	@param		----
	@return		----
*/
//===========================================================================
void XMLChToChar::_Release( void )
{
	if( m_data ) {
		XMLString::release( &m_data );
	}
}





	
//--------------------------------CharToXMLCh--------------------------------


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CharToXMLCh::CharToXMLCh()
{
	_Init();
}


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
CharToXMLCh::CharToXMLCh( const char* str )
{
	_Init();
	Convert( str );
}
	
//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
CharToXMLCh::~CharToXMLCh()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void CharToXMLCh::_Init( void )
{
	m_data	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void CharToXMLCh::_Term( void )
{
	_Release();
}


//===========================================================================
/*!	@brief		変換
	@param		xmlch	変換文字列
	@return		----
*/
//===========================================================================
void CharToXMLCh::Convert( const char* str )
{
	m_data	= XMLString::transcode( str );
}



//===========================================================================
/*!	@brief		XMLCh文字列取得
	@param		----
	@return		----
*/
//===========================================================================
XMLCh* CharToXMLCh::GetXMLCh( void )
{
	
	return m_data;
}


//===========================================================================
/*!	@brief		リリース
	@param		----
	@return		----
*/
//===========================================================================
void CharToXMLCh::_Release( void )
{
	if( m_data ) {
		XMLString::release( &m_data );
	}
}

	
	
}	// namespace nk