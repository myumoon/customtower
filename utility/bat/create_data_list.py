#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import glob
import stat
import re
import relpath

# インクルードガード文字列
includeGuard	= "__DATA_PATH__"
newLine			= "\n"

# ヘッダファイルを開く
def createHeaderFile( filename ) :
	file	= open( filename, "w" )
	
	insertIncludeGuardHead( file )
	
	return file
	
	
# ヘッダファイルを閉じる
def closeHeaderFile( file ) :
	insertIncludeGuardTail( file )
	file.close()
	
	
# インクルードガードを書き込む(head)
def insertIncludeGuardHead( file ) :
	line1	= "#ifndef " + includeGuard + newLine
	line2	= "#define " + includeGuard + newLine
	
	file.write( line1 )
	file.write( line2 )
	file.write( newLine )
	
	
# インクルードガードを書き込む(tail)
def insertIncludeGuardTail( file ) :
	line1	= "#endif //" + includeGuard + newLine
	
	file.write( newLine )
	file.write( line1 )
		
	
# 指定ディレクトリ以下のファイルパスリストを取得
def reprDirInfo( dirpath, indent = 0 ) :
#    print " "*(indent-1),"+",dirpath
	dirs	= []
	
	for path in os.listdir( dirpath ) :
		full = os.path.join( dirpath, path )

		if os.path.isdir( full ) :
			dirs.extend( reprDirInfo( full,indent + 4 ) )
		elif os.path.isfile( full ) :
			dirs.append( full )

	return dirs

	
# define定義を書き込む
def writeDefine( file, path ) :
	defineStr	= convertPathToDefineStr( path )
	path		= re.sub( r'\\', '/', path )
	writeStr	= "#define " + defineStr + "\t" + "\"" + "data/" + path + "\"" + newLine
	file.write( writeStr )
	
	
# パスをdefine定義文字列に変換
# aaa/bbb/ccc.png -> AAA_BBB_CCC_IMG
def convertPathToDefineStr( path ) :
	dst	= path
	dst	= re.sub( r'^', 'DATA_', dst )
	dst	= re.sub( r'(\.png|\.jpg|\.jpeg|\.bmp|\.tga)', '_IMG', dst )	# 画像拡張子を"_IMG"に
	dst	= re.sub( r'(\.mqo|\.toy|\.x)', '_MODEL', dst )					# モデル拡張子を"_MODEL"に
	dst	= re.sub( r'[\\\/\.]', '_', dst )								# ディレクトリ区切り拡張子を"_"に
	dst	= dst.upper()													# 大文字変換
	
	return dst



# メイン
def main() :
	argv	= sys.argv
	argc	= len( argv )
	
	
	if argc < 3 :
		print u"----- usage -----"
		print u"create_data_list [rootpath] [filename]"
		
		return;
	
	inDataDir		= os.path.normpath( argv[1] )	
	outHeaderPath	= os.path.normpath( argv[2] )
	
	inDataDir		= re.sub( r'\\', '/', inDataDir )
	outHeaderPath	= re.sub( r'\\', '/', outHeaderPath )
	
	print "inDataDir     : ", inDataDir
	print "outHeaderPath : ", outHeaderPath
	
	# データフォルダがなかったらエラー
	if not os.path.exists( inDataDir ) :
		print "directory not exists : ", inDataDir
		
	
		
	# 出力ディレクトリが無かったら作成
	if not os.path.exists( os.path.dirname( outHeaderPath ) ) :
		os.mkdir( os.path.dirname( outHeaderPath ) )
	
	file		= createHeaderFile( outHeaderPath )
	rootPath	= re.sub( r'\\', '/', inDataDir )
	
	for d in reprDirInfo( rootPath ) :
		d			= re.sub( r'\\', '/', d )
		#relative	= os.path.relpath( d, rootPath )
		relative	= relpath.relpath( d, rootPath )
		relative	= re.sub( r'\\', '/', relative )
		writeDefine( file, relative )
	
	closeHeaderFile( file )
	
	
if __name__ == "__main__" :
	main()
