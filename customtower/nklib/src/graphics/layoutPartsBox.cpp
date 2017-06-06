//=============================================================================
/*!	@file	layoutPartsBox.h

	@brief	���C�A�E�g�p�[�c����

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include <stdlib.h>

#include "../../include/graphics/layoutPartsBox.h"
#include "../../include/collision/collision.h"
#include "../../include/utility/utility.h"
#include "../../include/general.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
LayoutPartsBox::LayoutPartsBox()
{
	_Init();
}


//===========================================================================
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
LayoutPartsBox::~LayoutPartsBox()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutPartsBox::_Init( void )
{
	m_partsTree.reserve( 32 );
	
	SetTagName("box");
}


//===========================================================================
/*!	@brief	�I������
	@param	----
	@return	----
*/
//===========================================================================
void LayoutPartsBox::_Term( void )
{
	DeleteParts();	// ���ʎ��͎q�����E���Ă���
}


//===========================================================================
/*!	@brief		�q����ǉ�
	@param		parts	�ǉ��p�[�c
	@return		----
*/
//===========================================================================
void LayoutPartsBox::AddParts( LayoutParts* parts )
{
	m_partsTree.push_back( parts );
}


//===========================================================================
/*!	@brief		�q����ǉ�
	@param		parts	�ǉ��p�[�c
	@return		----
*/
//===========================================================================
void LayoutPartsBox::AddPartsBox( LayoutPartsBox* partsbox )
{
	m_partsBoxTree.push_back( partsbox );
}



//===========================================================================
/*!	@brief		�q�����폜
	@param		child	�폜�p�[�c
	@return		----
*/
//===========================================================================
void LayoutPartsBox::DeleteParts( LayoutParts* parts )
{
	// �t�폜
	VecParts::iterator	itr	= m_partsTree.begin();
	for( ; itr != m_partsTree.end(); ) {
		if( *itr == parts ) {
			LayoutParts*	deleteParts	= *itr;
			itr	= m_partsTree.erase( itr );
			SafeDelete( deleteParts );
		}
		else {
			++itr;
		}
	}
	
}




//===========================================================================
/*!	@brief		�q����S�폜
	@param		----
	@return		----
*/
//===========================================================================
void LayoutPartsBox::DeleteParts( void )
{
	// �t�폜
	{
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			SafeDelete( *itr );
		}
		m_partsTree.clear();
	}

	// �}�폜
	{
		VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
		for( ; itr != m_partsBoxTree.end(); ++itr ) {
			(*itr)->DeleteParts();
			SafeDelete( *itr );
		}
		m_partsBoxTree.clear();
	}
	
}


//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void LayoutPartsBox::UpdateParts( void )
{	
	VecParts::iterator	itr	= m_partsTree.begin();
	for( ; itr != m_partsTree.end(); ++itr ) {
		(*itr)->UpdateParts();
	}
	
}



//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void LayoutPartsBox::DrawParts( void )
{	
	VecParts::iterator	itr	= m_partsTree.begin();
	for( ; itr != m_partsTree.end(); ++itr ) {
		(*itr)->DrawParts();
	}
	
}


//===========================================================================
/*!	@brief		�q��������
	@param		partsname	�p�[�c��
	@param		recursive	�ċA����
	@return		----
*/
//===========================================================================
LayoutParts* LayoutPartsBox::FindParts( const char* partsname, bool recursive )
{
	
	// �Ƃ肠�����J�����g���[�g�̒�����T��
	{
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			if( (*itr)->IsSameName( partsname ) ) {
				return *itr;
			}
		}
	}

	// ������Ȃ�������q��������
	{
		LayoutParts*	findParts	= NULL;
		if( recursive ) {
			VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
			for( ; itr != m_partsBoxTree.end(); ++itr ) {
				findParts	= (*itr)->FindParts( partsname, true );
				if( findParts ) {
					return findParts;
				}
			}
		}
	}

	
	return NULL;
}


//===========================================================================
/*!	@brief		�{�b�N�X������
	@param		partsname	�p�[�c��
	@param		recursive	�ċA����
	@return		----
*/
//===========================================================================
LayoutPartsBox* LayoutPartsBox::FindPartsBox( const char* partsboxname, bool recursive )
{

	// �Ƃ肠�����J�����g���[�g���璲�ׂ�
	{
		VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
		for( ; itr != m_partsBoxTree.end(); ++itr ) {
			if( (*itr)->IsSameName( partsboxname ) ) {
				return *itr;
			}
		}
	}

	// �q����������
	{
		LayoutPartsBox*	findParts	= NULL;
		if( recursive ) {
			VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
			for( ; itr != m_partsBoxTree.end(); ++itr ) {
				findParts	= (*itr)->FindPartsBox( partsboxname, true );
				if( findParts ) {
					return findParts;
				}
			}
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief		�ʒu�ݒ�
	@param		pos		�ʒu
	@return		----
*/
//===========================================================================
void LayoutPartsBox::SetPos( const math::Vector& pos )
{
	_SetPosWithChildren( static_cast<s32>(pos.x), static_cast<s32>(pos.y) );
	
}


//===========================================================================
/*!	@brief		�ʒu�ݒ�
	@param		x		x���W
	@param		y		y���W
	@return		----
*/
//===========================================================================
void LayoutPartsBox::SetPos( s32 x, s32 y )
{
	_SetPosWithChildren( x, y );
	
}


//===========================================================================
/*!	@brief		�q���ƈꏏ�Ɉʒu�ݒ�
	@param		x		x���W
	@param		y		y���W
	@return		----
*/
//===========================================================================
void LayoutPartsBox::_SetPosWithChildren( s32 x, s32 y )
{
	// �ړ���
	const math::Vector	moveAmount	= math::Vector( static_cast<f32>(x), static_cast<f32>(y), 0.0f ) - GetPos();

	// ���g�ړ�
	{
		m_pos	= math::Vector( static_cast<f32>(x), static_cast<f32>(y), 0.0f );
	}
	
	// �p�[�c
	{
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			(*itr)->SetPos( (*itr)->GetPos() + moveAmount );
		}
	}
	
	// �{�b�N�X
	{
		VecPartsBox::iterator	itrBox	= m_partsBoxTree.begin();
		for( ; itrBox != m_partsBoxTree.end(); ++itrBox ) {
			(*itrBox)->SetPos( (*itrBox)->GetPos() + moveAmount );
		}
	}
}



//===========================================================================
/*!	@brief		�}�E�X���W���܂�ł���p�[�c���擾
	@param[out]	findParts			��������
	@param[out]	findPartsDepath		�������ʃp�[�c�̐[��
	@param[in]	mousePos			�}�E�X���W
	@param[in]	depth				���݂̐[��
	@return		true.��������		false.������Ȃ�����
*/
//===========================================================================
bool LayoutPartsBox::GetIncludedPartsOf( LayoutParts** outFindParts, s32* outFindPartsDepth, const math::Vector& mousePos, s32 depth )
{
	const s32		thisPartsDepth	= depth + 1;
	
	LayoutParts*	retParts		= NULL;
	s32				retPartsDepth	= 0;

	// �{�b�N�X���猟��
	{
		bool			isFind				= false;	// ����������true
		s32				findPartsDepth		= 0;		// �������ʃp�[�c�̐[��
		LayoutParts*	findParts			= NULL;		// ��������
		
		LayoutParts*	deepestParts		= NULL;		// ��Ԑ[���ꏊ�ɂ���p�[�c
		s32				deepestPartsDepth	= 0;		// �������ʃp�[�c�̐[��
		
		VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
		for( ; itr != m_partsBoxTree.end(); ++itr ) {
			
			isFind	= (*itr)->GetIncludedPartsOf( &findParts, &findPartsDepth, mousePos, thisPartsDepth );

			if( isFind ) {
				// ��Ԑ[���p�[�c��I��
				if( deepestPartsDepth < findPartsDepth ) {
					deepestParts		= findParts;
					deepestPartsDepth	= findPartsDepth;
				}
			}
		}

		retParts	= deepestParts;
	}

	// �q�����猟��
	if( retParts == NULL ) {
		const Collision2D::Point		mousePoint( mousePos );
		
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			if( Collision2D::IsHit( Collision2D::Rect( (*itr)->GetPos(), (*itr)->GetSize() ), mousePoint ) ) {
				retParts		= *itr;
				retPartsDepth	= thisPartsDepth;
			}		
		}
	}

	if( retParts ) {
		*outFindParts		= retParts;
		*outFindPartsDepth	= retPartsDepth;
	}

	return (retParts != NULL);
}
	
}	// namespace graphics
}	// namespace nk