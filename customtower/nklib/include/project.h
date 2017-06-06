//=============================================================================
/*!	@file	project.h

	@brief	プロジェクトタイプを設定

	@author	井手 竜之介
	@date	2011/11/15
	@todo	なし
	@bug	なし
*/
//=============================================================================

#ifndef __PROJECT_H__
#define __PROJECT_H__

#include "./projectDef.h"



#if defined(WIN32) || defined(_WIN32)

	// directX
	#if defined(USE_DIRECTX)
		//#define	GRAPHICS_TYPE	GRAPHICS_TYPE_DIRECTX9
		#define NK_WIN_DIRECTX
		
		#define	NK_USE_DIRECTX
		
		#error	"directX is not supported."

	// SDL+openGL
	#elif (defined(USE_OPENGL) && defined(USE_SDL)) || defined(USE_SDL_OPENGL)
		//#define GRAPHICS_TYPE	GRAPHICS_TYPE_SDL_OPENGL
		#ifndef NK_WIN_SDLGL
			#define NK_WIN_SDLGL
		#endif

		#ifndef NK_WIN_GL
			#define NK_WIN_GL
		#endif

		#ifndef NK_WIN_SDL
			#define NK_WIN_SDL
		#endif
		
		#ifndef NK_USE_SDL
			#define NK_USE_SDL
		#endif

		#ifndef NK_USE_GL
			#define NK_USE_GL
		#endif

		#ifndef NK_USE_SDLGL
			#define NK_USE_SDLGL
		#endif

	// openGL
	#elif defined(USE_OPENGL)
		//#define	GRAPHICS_TYPE	GRAPHICS_TYPE_OPENGL
		#define NK_WIN_GL
		
		#define NK_USE_GL
		
	// SDL
	#elif defined(USE_SDL)
		//#define GRAPHICS_TYPE	GRAPHICS_TYPE_SDL	
		#define NK_WIN_SDL
		
		#define NK_USE_SDL
		
	#else
		#error	"unknown project"
		
	#endif
	
#elif defined(_MAC)

	// 現状windows以外は未対応
	#error	"windows only."
	
#else

	// 現状windows以外は未対応
	#error	"windows only."
	
#endif



#endif  // __PROJECT_H__
