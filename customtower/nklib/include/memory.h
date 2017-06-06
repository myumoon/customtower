//=============================================================================
/*!	@file	memory.h

	@brief	ÉÅÉÇÉäëÄçÏ

	@author	ryunosuke ide
	@date	2013.05.06
*/
//=============================================================================

#ifndef __MEMORY_H__
#define __MEMORY_H__


#if defined(__cplusplus)
extern "C" {
#endif


#if defined(__cplusplus)
void*	operator new( std::size_t size );
void*	operator new( std::size_t size, const std::nothrow );
void	operator delete( void* ptr );
void	operator delete( void* ptr, const std::nothrow );
#endif

	


#if defined(__cplusplus)
}
#endif

#endif  // __MEMORY_H__

