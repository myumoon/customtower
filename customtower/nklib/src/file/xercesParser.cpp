//=============================================================================
/*!	@file	xercesParser.h

	@brief	xercesc parser

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "../../include/file/xercesParser.h"

#include "../../include/general.h"
#include "../../include/utility/utility.h"

using namespace xercesc;

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
XercesParser::XercesParser()
{
	_Init();
}


//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
XercesParser::XercesParser( const char* xmlfile )
{
	_Init();
	Parse( xmlfile );
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
XercesParser::~XercesParser()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void XercesParser::_Init( void )
{
	m_parser	= new XercesDOMParser();


}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void XercesParser::_Term( void )
{
	SafeDelete( m_parser );
}


//===========================================================================
/*!	@brief		���
	@param		xmlfile		xml�t�@�C����
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
/*!	@brief		�h�L�������g�̊֘A�t��
	@param		doc		�h�L�������g
	@return		----
*/
//===========================================================================
void XercesParser::RegisterDocument( DOMDocument* doc )
{
	m_document		= doc;
	m_elementRoot	= m_document->getDocumentElement();
}


//===========================================================================
/*!	@brief		�������ς݂Ȃ�true��Ԃ�
	@param		----
	@return		----
*/
//===========================================================================
bool XercesParser::Initialized( void ) const
{

	return m_initialized;
}

//===========================================================================
/*!	@brief		�h�L�������g�擾
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
/*!	@brief		�h�L�������g�擾
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
/*!	@brief		�^�O���Ŏq��������
	@param		tagName		�^�O��
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