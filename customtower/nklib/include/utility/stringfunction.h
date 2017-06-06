//=============================================================================
/*!	@file	stringfunction.h

	@brief	文字列操作関数

	@author	井手 竜之介
	@date	2011/11/24
	@todo	なし
	@bug	なし
*/
//=============================================================================



#ifndef __STRINGFUNCTION_H__
#define __STRINGFUNCTION_H__

#include <shlwapi.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "../typedef.h"
#include "../math/vector.h"
#include "../math/matrix.h"

#pragma warning( disable : 4996 )	// ファイル関係の警告を消す

#define STR_SIZE 256		// 文字列読み込み最大数

namespace nk {

/*! 文字列比較 */
extern bool			Compare( const char* lhs, const char* rhs );

/*! 文字列の先頭ポインタを指定文字列の次まで移動する */
std::string			FindStr( const char *origin, const char *find1, const char *find2 );

/*! 文字列の先頭アドレスを特定の文字の後ろに設定 */
s32					ChangeStrTop( char **origin, const char *find );

/*! 特定の文字列が含まれているインデックス番号を調べる */
s32					SearchStrIndex( const char *origin, const char *find );

/*! 置換 */
void				ChangeCharacter( char *origin, char before, char after );

/*! 文字列からベクトルに変換 */
nk::math::Vector	GetVectorFromString( char* str, const char* token );

/*! ディレクトリパスを習得 */
std::string			GetDirectoryPath( std::string filePath );

}	// namespace nk


#endif  // __STRINGFUNCTION_H__