//=============================================================================
/*!	@file	layoutParser.h

	@brief	���C�A�E�gXML�p�[�T�[

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/util/XMLString.hpp>


#include "../../include/file/layoutParser.h"
#include "../../include/general.h"
#include "../../include/file/xercesUtility.h"

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
LayoutParser::LayoutParser()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
LayoutParser::~LayoutParser()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutParser::_Init( void )
{
	m_xercesParser	= NULL;
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutParser::_Term( void )
{
	SafeDelete( m_xercesParser );
}



//===========================================================================
/*!	@brief		���
	@param		path	��̓t�@�C��
	@param		root	�p�[�c���[�g
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