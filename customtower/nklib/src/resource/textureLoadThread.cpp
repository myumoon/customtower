//=============================================================================
/*!	@file	textureLoadThread.h

	@brief	テクスチャロードスレッド

	@author	ryunosuke ide
	@date	2013.03.09
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/resource/textureLoadThread.h"
#include "../../include/utility/utility.h"
#include "../../include/resource/texture.h"
#include "../../include/general.h"
#include "../../include/utility/stringfunction.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------
namespace nk {

namespace resource {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
TextureLoadThread::TextureLoadThread()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
TextureLoadThread::~TextureLoadThread()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void TextureLoadThread::_Init()
{
	m_vecSurface.reserve( 256 );

	m_completed			= false;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void TextureLoadThread::_Term()
{
	
}


//===========================================================================
/*!	@brief	ロードを行うテクスチャを追加
	@param	path	ロードテクスチャ
	@return	----
*/
//===========================================================================
void TextureLoadThread::Add( const char* path )
{
	_LoadSurface	addSurface;
	addSurface.path.assign( path );

	{
		SCOPE_CRITICAL_SECTION( m_criticalSection );
		
		m_vecSurface.push_back( addSurface );

		m_completed	= false;
	}

}


//===========================================================================
/*!	@brief	ロード完了ならtrueを返す
	@param	----
	@return	----
*/
//===========================================================================
bool TextureLoadThread::IsComplete( void ) const
{
	
	return m_completed;
}


//===========================================================================
/*!	@brief	ロード完了ならtrueを返す
	@param	----
	@return	----
*/
//===========================================================================
bool TextureLoadThread::IsComplete( const char* path ) const
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	for( u32 i = 0; i < m_vecSurface.size(); ++i ) {
		if( m_vecSurface[i].surface.created == false ) {
			if( m_vecSurface[i].path == path ) {
				return true;
			}
		}
	}

	return false;
}


//===========================================================================
/*!	@brief	テクスチャを取得
	@param	path		取得するテクスチャパス
	@return	テクスチャへのポインタ
	
	@note	取得したテクスチャはリストから削除されます
			テクスチャの解放はユーザーが行ってください
*/
//===========================================================================
Texture* TextureLoadThread::PopTexture( const char* path )
{
	SCOPE_CRITICAL_SECTION( m_criticalSection );
	
	for( u32 i = 0; i < m_vecSurface.size(); ++i ) {
		if( nk::Compare( m_vecSurface[i].path.c_str(), path ) ) {
			return _CreateTexture( m_vecSurface[i] );
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief	スレッド処理
	@param	----
	@return	----
*/
//===========================================================================
void TextureLoadThread::ThreadFunc( void )
{
	while( 1 ) {
		{
			SCOPE_CRITICAL_SECTION( m_criticalSection );
			
			if( IsComplete() == false ) {
				for( u32 i = 0; i < m_vecSurface.size(); ++i ) {
					if( m_vecSurface[i].surface.created == false ) {
						ImageSurface	surface;
						LoadImageSurface( &surface, m_vecSurface[i].path.c_str() );
						m_vecSurface[i].surface.Register( surface.image );
					}
				}

				m_completed	= true;
			}
		}

		if( IsCancel() ) {
			printf("TextureLoadThread::ThreadFunc() cancel\n");
			break;
		}
		
		SleepThread( 1 );
	}

	printf("TextureLoadThread::ThreadFunc() end\n");
}

//===========================================================================
/*!	@brief	サーフェスからテクスチャを生成
	@param	surface		ソース
	@return	テクスチャ
*/
//===========================================================================
Texture* TextureLoadThread::_CreateTexture( const _LoadSurface& surface ) const
{
	Texture*	texture	= CreateTexture( surface.surface );

	NULL_ASSERT( texture );

	texture->SetTexName( surface.path.c_str() );
	

	return texture;
}
	
}	// namespace resource
	
}	// namespace nk

