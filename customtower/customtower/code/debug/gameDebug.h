//=============================================================================
/*!	@file	gameDebug.h

	@brief	�f�o�b�O���j���[

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================


#ifndef __GAME_DEBUG_H__
#define __GAME_DEBUG_H__

#include "debug/debug.h"

#if defined(_DEBUG)
	#define DEBUG_MENU_ENABLE
#endif

enum DEBUG_MENU_LINE {
	DEBUG_MENU_LINE_SCENE_CHANGE,	//!< �V�[���ύX

	DEBUG_MENU_LINE_MAX,			//!< �ő�
};


#if defined(DEBUG_MENU_ENABLE)


//! �f�o�b�O���j���[������
void	DebugMenuInit( s32 x, s32 y, s32 dispLine );

//! �s�ǉ�
void	DebugMenuAddLine( DEBUG_MENU_LINE lineNo, const char* title );

//! �w��s�ɃA�C�e���ǉ�
void	DebugMenuAddItem( DEBUG_MENU_LINE lineNo, nk::debug::DebugItemInterface* item );

//! �w��s�폜
void	DebugMenuDeleteLine( DEBUG_MENU_LINE lineNo );

//! �S�s�폜
void	DebugMenuDeleteLineAll( void );

//! �X�V
void	DebugMenuUpdate( void );

//! �`��
void	DebugMenuDraw( void );


#define DEBUG_MENU_INIT( x, y, dispLine )													DebugMenuInit( x, y, dispLine )
#define DEBUG_MENU_ADD_LINE( lineNo, title )												DebugMenuAddLine( lineNo, title )
#define DEBUG_MENU_ADD_ITEM( lineNo, className, procFunc, itemName )						DebugMenuAddItem( lineNo, new nk::debug::DebugItem<className>( this, &className::procFunc, NULL, itemName ) )
#define DEBUG_MENU_ADD_ITEM_WITH_DISP( lineNo, className, procFunc, dispFunc, itemName )	DebugMenuAddItem( lineNo, new nk::debug::DebugItem<className>( this, &className::procFunc, &className::dispFunc, itemName ) )
#define DEBUG_MENU_DELETE_LINE( lineNo )													DebugMenuDeleteLine( lineNo )
#define DEBUG_MENU_DELETE_LINE_ALL															DebugMenuDeleteLineAll
#define DEBUG_MENU_UPDATE																	DebugMenuUpdate
#define DEBUG_MENU_DRAW																		DebugMenuDraw
#define DEBUG_MENU_PROC_CALLBACK( funcName )												void funcName( u32 lineNo, nk::debug::CALL_EVENT )
#define DEBUG_MENU_DRAW_CALLBACK( funcName )												void funcName( void )

#else	// #if defined(DEBUG_MENU_ENABLE)

#define DEBUG_MENU_INIT( x, y, dispLine )													((void)0)
#define DEBUG_MENU_ADD_LINE( lineNo, title )												((void)0)
#define DEBUG_MENU_ADD_ITEM( lineNo, className, procFunc, itemName )						((void)0)
#define DEBUG_MENU_ADD_ITEM_WITH_DISP( lineNo, className, procFunc, dispFunc, itemName )	((void)0)
#define DEBUG_MENU_DELETE_LINE( lineNo )													((void)0)
#define DEBUG_MENU_DELETE_LINE_ALL()														((void)0)
#define DEBUG_MENU_UPDATE()																	((void)0)
#define DEBUG_MENU_DRAW()																	((void)0)
#define DEBUG_MENU_PROC_CALLBACK( funcName )												void funcName( u32 lineNo, nk::debug::CALL_EVENT )
#define DEBUG_MENU_DRAW_CALLBACK( funcName )												void funcName( void )

#endif	// #if defined(DEBUG_MENU_ENABLE)

	
#endif  // __GAME_DEBUG_H__