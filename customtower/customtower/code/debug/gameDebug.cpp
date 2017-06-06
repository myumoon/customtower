//=============================================================================
/*!	@file	gameDebug.h

	@brief	�f�o�b�O���j���[

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
#include "gameDebug.h"

#if defined(DEBUG_MENU_ENABLE)

#include "game/gameMain.h"

//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

// �f�o�b�O���j���[
nk::debug::DebugMenu		debugMenu;
	
}	// unnamed


	

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------


//===========================================================================
/*!	@brief		�f�o�b�O���j���[������
	@param		x, y		���W
	@param		dispLine	�\���s
	@return		----
*/
//===========================================================================
void DebugMenuInit( s32 x, s32 y, s32 dispLine )
{
	debugMenu.SetPos( x, y );
	debugMenu.SetMaxDispNum( dispLine );
}


//===========================================================================
/*!	@brief		�s�ǉ�
	@param		lineNo			�s�ԍ�
	@param		title			�^�C�g��
	@return		----
*/
//===========================================================================
void DebugMenuAddLine( DEBUG_MENU_LINE lineNo, const char* title )
{
	debugMenu.AddItemChunk( lineNo, title );
}


//===========================================================================
/*!	@brief		�A�C�e���Z�b�g
	@param		lineNo			�ǉ��s
	@param		item			�ǉ��f�o�b�O�@�\
	@return		----
*/
//===========================================================================
void DebugMenuAddItem( DEBUG_MENU_LINE lineNo, nk::debug::DebugItemInterface* item )
{
	debugMenu.AddItem( lineNo, item );
	
}


//===========================================================================
/*!	@brief		�w��s�폜
	@param		�s�ԍ�
	@return		----
*/
//===========================================================================
void DebugMenuDeleteLine( DEBUG_MENU_LINE lineNo )
{
	debugMenu.DeleteItemChunk( lineNo );
	
}

//===========================================================================
/*!	@brief		�S�s�폜
	@param		----
	@return		----
*/
//===========================================================================
void DebugMenuDeleteLineAll( void )
{
	debugMenu.DeleteItemChunkAll();
	
}

//===========================================================================
/*!	@brief		�X�V
	@param		----
	@return		----
*/
//===========================================================================
void DebugMenuUpdate( void )
{
	debugMenu.Update();
	
}

//===========================================================================
/*!	@brief		�`��
	@param		----
	@return		----
*/
//===========================================================================
void DebugMenuDraw( void )
{
	debugMenu.Draw();
	
}

#endif
