//=============================================================================
/*!	@file	stringfunction.cpp

	@brief	文字列操作関数

	@author	井手 竜之介
	@date	2011/11/24
	@todo	なし
	@bug	なし
*/
//=============================================================================
#include "../../include/utility/stringfunction.h"






namespace nk {


//===========================================================================
/*!	@brief	文字列比較
	@param	lhs		: 比較文字列1
	@param	rhs		: 比較文字列2
	@return	true.等しい		false.等しくない
*/
//===========================================================================
bool Compare( const char* lhs, const char* rhs )
{
	
	return strcmp(lhs, rhs) == 0;
}



//===========================================================================
/*!	@brief	文字列のから特定の文字で囲まれた中身を抽出する
	@param	origin	: 元の文字列
	@param	find1	: 検索文字列(前)
	@param	find2	: 検索文字列(後ろ)
	@return	文字列
*/
//===========================================================================
std::string FindStr( const char *origin, const char *find1, const char *find2 )
{
	s32 count = 0, num = 0;

	//	find1の検索
	//---------------------------------------
	char *top = const_cast<char *>( strstr(origin, find1) );
	if( !top ) {
		return std::string();
	}
	top += strlen( find1 );
	
	//	find2の検索
	//---------------------------------------
	char *last = const_cast<char *>( strstr(top, find2) );
	if( !last ) {
		return std::string();
	}

	//	コピー
	//---------------------------------------
	std::string retStr;
	for( s32 i = 0; &top[i] < last; i++ ) {
		retStr += top[i];
	}
	//retStr += '\0';

	return retStr;
}





//========================================================================
//	内　容：特定の文字列が含まれるインデックス番号を検索
//	引　数：origin	: 検索対象文字列
//			str		: 文字列
//	戻り値：インデックス番号
//	 memo ：検索文字列の先頭のインデックス番号を返す
//========================================================================
s32 SearchStrIndex(const char *origin, const char *find)
{
	s32 index = 0, count = 0;


	while(origin[index] != '\0') {

		if(origin[index] == find[count]) {
			count++;
		} else {
			count = 0;
		}
		index++;

		/* 一致した */
		if(count == strlen(find)) {
			break;
		}

	}

	return index - strlen(find);
}





//========================================================================
//	内　容：文字列の先頭アドレスを特定の文字の後ろに設定
//	引　数：origin				: 対称文字列
//			find				: サーチ文字
//	戻り値：見つかった			: 1
//			見つからなかった	: 0
//	 memo ：
//========================================================================
s32 ChangeStrTop(char **origin, const char *find)
{
	s32 count = 0, num = 0;


	
	
	while((*origin)[num] != '\0') {

		/* 1文字ずつチェック */
		if((*origin)[num] == find[count]) {
			count++;
		} else {
			count = 0;
		}

		num++;

		/* 検索文字列の長さとカウンタの長さが一致したら含まれている */
		if(count == strlen(find)) {
			*origin = &(*origin)[num];
			return 1;
		}
	}



	return 0;
}





//========================================================================
//	内　容：置換
//	引　数：origin	: 変換文字列
//			before	: 検索文字
//			after	: 置換文字
//	戻り値：なし
//	 memo ：
//========================================================================
void ChangeCharacter(char *origin, char before, char after)
{
	s32 index_max = strlen(origin) + 1;


	for(s32 i = 0; i < index_max; i++) {
		if(origin[i] == before) {
			origin[i] = after;
		}
	}

}

//===========================================================================
/*!	@brief	文字列をベクトルに変換
	@param	str		: 文字列
	@param	token	: 区切り文字 ",."のように数字を区切る文字を指定
	@return	生成したベクトル
*/
//===========================================================================
nk::math::Vector GetVectorFromString(char* str, const char* token)
{
	char*				tp;
	nk::math::Vector	retVec;

	// X
	tp = strtok(str, token);
	retVec.x = static_cast<f32>(atof(tp));

	// Y
	tp = strtok(NULL, token);
	retVec.y = static_cast<f32>(atof(tp));
	
	// Z
	tp = strtok(NULL, token);
	retVec.z = static_cast<f32>(atof(tp));

	return retVec;
}

//===========================================================================
/*!	@brief	ディレクトリパスを習得
	@param	filePath	: ファイルパス
	@return	ディレクトリパス
*/
//===========================================================================
std::string GetDirectoryPath( std::string filePath )
{
	std::string ret = filePath;

	// 最後のスラッシュ・バックスラッシュの位置を検索
	const s32	pathSize	= filePath.size();
	for( s32 i = pathSize - 1; 0 < i; --i ) {
		char searchChar	= filePath.at(i);

		if( (searchChar == '/') || (searchChar == '\\') ) {
			if( i == pathSize - 1 ) {
				continue;
			}
			//最後にヌル文字入れる？
			//ret.at(i + 1)	= '\0';	 
			//ret.resize(i + 1);
			ret.resize(i + 1);

			break;
		}
	}

	return ret;
}


}	// namespace nk


