//=============================================================================
/*!	@file	xercesWriter.h

	@brief	xerces出力

	@author	ryunosuke ide
	@date	2013.06.10
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "../../include/file/xercesWriter.h"

#include "../../include/file/xercesParser.h"
#include "../../include/general.h"

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
XercesWriter::XercesWriter()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
XercesWriter::~XercesWriter()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void XercesWriter::_Init( void )
{

}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void XercesWriter::_Term( void )
{

}


//===========================================================================
/*!	@brief		出力
	@param		filepath	出力パス
	@param		parser		出力パーサー
	@return		----
*/
//===========================================================================
void XercesWriter::Write( const char* filepath, DOMDocument* doc )
{
	// LS設定
	DOMImplementation*	implementation	= DOMImplementationRegistry::getDOMImplementation(L"LS");
	DOMLSSerializer*	serializer		= ((DOMImplementationLS*)implementation)->createLSSerializer();

	// インデントを有効に
	if(serializer->getDomConfig()->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true ) ) {
	    serializer->getDomConfig()->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true );
	}

	serializer->setNewLine( XMLString::transcode("\r\n") );

	// ファイル名称をXMLChに変更
	CharToXMLCh	tempFilePath( filepath );

	// ファイルの作成
	XMLFormatTarget*	formatTarget	= new LocalFileFormatTarget( tempFilePath.GetXMLCh() );
	DOMLSOutput*		output			= ((DOMImplementationLS*)implementation)-> createLSOutput();
	output->setByteStream( formatTarget );

	// 書き出し
	serializer->write( doc, output );

	// 解放
	serializer->release();
	SafeDelete( formatTarget );
	output->release();
	
}
	
}	// namespace nk
