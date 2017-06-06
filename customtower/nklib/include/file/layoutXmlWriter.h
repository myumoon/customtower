//=============================================================================
/*!	@file	layoutXmlWriter.h

	@brief	���C�A�E�gXML��������

	@author	ryunosuke ide
	@date	2013.06.10
*/
//=============================================================================


#ifndef __LAYOUT_XML_WRITER_H__
#define __LAYOUT_XML_WRITER_H__

#include "./xercesUtility.h"
#include "./xercesParser.h"


namespace nk {

namespace graphics {
class Layout;
class LayoutPartsBox;
class LayoutParts;
}

//=============================================================================
/*!
							���C�A�E�gXML�o��
*/
//=============================================================================
class LayoutXmlWriter {
public:
	//-----------------------�^��`--------------------------
	

	//----------------------�ÓI�����o-----------------------
	
	
	//-----------------------���\�b�h------------------------

	//===========================================================================
	/*!	@brief		�t�@�C���o��
	*/
	//===========================================================================
	void	WriteToFile( const char* file, graphics::Layout* layout );
	
private:
	//-----------------------���\�b�h------------------------
	void	_Init( void );
	void	_Term( void );

	//----------------------�����o�ϐ�-----------------------
	XercesParser			m_parser;		//!< �p�[�T�[

public:
	//-------------�R���X�g���N�^�E�f�X�g���N�^--------------
			LayoutXmlWriter();
	virtual~LayoutXmlWriter();
};
	
}	// namespace nk



#endif  // __LAYOUT_XML_WRITER_H__