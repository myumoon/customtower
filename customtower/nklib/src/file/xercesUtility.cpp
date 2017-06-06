//=============================================================================
/*!	@file	xercesUtility.h

	@brief	xercesc

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <xercesc/dom/DOM.hpp>

#include "../../include/general.h"
#include "../../include/file/xercesUtility.h"



//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {


using namespace xercesc;

//--------------------------------XercesUtility--------------------------------

	
//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
XercesUtility::XercesUtility()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
XercesUtility::~XercesUtility()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void XercesUtility::_Init( void )
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void XercesUtility::_Term( void )
{

}


//===========================================================================
/*!	@brief		������
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
/*!	@brief		�I������
	@param		----
	@return		----
*/
//===========================================================================
void XercesUtility::Terminate( void )
{
	XMLPlatformUtils::Terminate();
}


//===========================================================================
/*!	@brief		XML����
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
/*!	@brief		�h�L�������g����
	@param		docName			�h�L�������g��
	@param		namespaceName	�l�[���X�y�[�X
	@param		docType			�h�L�������g�^�C�v
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
/*!	@brief		�G�������g����
	@param		doc				�h�L�������g
	@param		elementName		�G�������g��
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
/*!	@brief		�����ݒ�
	@param		element		�ݒ�G�������g
	@param		attrName	������
	@param		zttrValue	����
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
/*!	@brief		�l�ݒ�
	@param		node	�m�[�h
	@param		value	�l
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
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
XMLChToChar::XMLChToChar()
{
	_Init();
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
XMLChToChar::XMLChToChar( XMLCh* xmlch )
{
	_Init();
	Convert( xmlch );
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
XMLChToChar::~XMLChToChar()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void XMLChToChar::_Init( void )
{
	m_data	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void XMLChToChar::_Term( void )
{
	_Release();
	
}


//===========================================================================
/*!	@brief		�ϊ�
	@param		xmlch	�ϊ�������
	@return		----
*/
//===========================================================================
void XMLChToChar::Convert( XMLCh* xmlch )
{
	m_data	= XMLString::transcode( xmlch );
}



//===========================================================================
/*!	@brief		char������擾
	@param		----
	@return		----
*/
//===========================================================================
char* XMLChToChar::GetChar( void )
{
	
	return m_data;
}


//===========================================================================
/*!	@brief		�����[�X
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
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CharToXMLCh::CharToXMLCh()
{
	_Init();
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
CharToXMLCh::CharToXMLCh( const char* str )
{
	_Init();
	Convert( str );
}
	
//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
CharToXMLCh::~CharToXMLCh()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void CharToXMLCh::_Init( void )
{
	m_data	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void CharToXMLCh::_Term( void )
{
	_Release();
}


//===========================================================================
/*!	@brief		�ϊ�
	@param		xmlch	�ϊ�������
	@return		----
*/
//===========================================================================
void CharToXMLCh::Convert( const char* str )
{
	m_data	= XMLString::transcode( str );
}



//===========================================================================
/*!	@brief		XMLCh������擾
	@param		----
	@return		----
*/
//===========================================================================
XMLCh* CharToXMLCh::GetXMLCh( void )
{
	
	return m_data;
}


//===========================================================================
/*!	@brief		�����[�X
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