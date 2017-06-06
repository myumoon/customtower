//=============================================================================
/*!	@file	memory.h

	@brief	ÉÅÉÇÉäëÄçÏ

	@author	ryunosuke ide
	@date	2013.05.06
*/
//=============================================================================

#ifndef __MEMORY_H__
#define __MEMORY_H__


void*	operator new( std::size_t size );
void*	operator new( std::size_t size, const std::nothrow );
void	operator delete( void* ptr );
void	operator delete( void* ptr, const std::nothrow );

#endif  // __MEMORY_H__

