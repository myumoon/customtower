//=============================================================================
/*!	@file	layoutParser.h

	@brief	レイアウトXMLパーサー

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/util/XMLString.hpp>


#include "../../include/file/layoutParser.h"
#include "../../include/general.h"
#include "../../include/file/xercesUtility.h"

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
LayoutParser::LayoutParser()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
LayoutParser::~LayoutParser()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void LayoutParser::_Init( void )
{
	m_xercesParser	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void LayoutParser::_Term( void )
{
	SafeDelete( m_xercesParser );
}



//===========================================================================
/*!	@brief		解析
	@param		path	解析ファイル
	@param		root	パーツルート
	@return		----
*/
//===========================================================================
bool LayoutParser::Parse( const char* path, LayoutPartsBox* root )
{
	if( m_xercesParser == NULL ) {
		m_xercesParser	= new XercesParser();
	}
	
	m_xercesParser->Parse( path );

		
	
	return true;
}
	
}	// namespace nk