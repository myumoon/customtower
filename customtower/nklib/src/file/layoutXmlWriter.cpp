//=============================================================================
/*!	@file	layoutXmlWriter.h

	@brief	���C�A�E�gXML��������

	@author	ryunosuke ide
	@date	2013.06.10
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
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
LayoutXmlWriter::LayoutXmlWriter()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
LayoutXmlWriter::~LayoutXmlWriter()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutXmlWriter::_Init( void )
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutXmlWriter::_Term( void )
{

}

//===========================================================================
/*!	@brief		�t�@�C���o��
	@param		file	�o�̓t�@�C����
	@param		layout	�o�̓��C�A�E�g
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


	// ���ۂ̏o��
	{
		XercesWriter		writer;
		writer.Write( file, doc );
	}
}
	
}	// namespace nk