//=============================================================================
/*!	@file	xercesWriter.h

	@brief	xerces�o��

	@author	ryunosuke ide
	@date	2013.06.10
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "../../include/file/xercesWriter.h"

#include "../../include/file/xercesParser.h"
#include "../../include/general.h"

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
XercesWriter::XercesWriter()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
XercesWriter::~XercesWriter()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void XercesWriter::_Init( void )
{

}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void XercesWriter::_Term( void )
{

}


//===========================================================================
/*!	@brief		�o��
	@param		filepath	�o�̓p�X
	@param		parser		�o�̓p�[�T�[
	@return		----
*/
//===========================================================================
void XercesWriter::Write( const char* filepath, DOMDocument* doc )
{
	// LS�ݒ�
	DOMImplementation*	implementation	= DOMImplementationRegistry::getDOMImplementation(L"LS");
	DOMLSSerializer*	serializer		= ((DOMImplementationLS*)implementation)->createLSSerializer();

	// �C���f���g��L����
	if(serializer->getDomConfig()->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true ) ) {
	    serializer->getDomConfig()->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true );
	}

	serializer->setNewLine( XMLString::transcode("\r\n") );

	// �t�@�C�����̂�XMLCh�ɕύX
	CharToXMLCh	tempFilePath( filepath );

	// �t�@�C���̍쐬
	XMLFormatTarget*	formatTarget	= new LocalFileFormatTarget( tempFilePath.GetXMLCh() );
	DOMLSOutput*		output			= ((DOMImplementationLS*)implementation)-> createLSOutput();
	output->setByteStream( formatTarget );

	// �����o��
	serializer->write( doc, output );

	// ���
	serializer->release();
	SafeDelete( formatTarget );
	output->release();
	
}
	
}	// namespace nk
