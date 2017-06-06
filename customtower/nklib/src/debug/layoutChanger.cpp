//=============================================================================
/*!	@file	layoutChanger.h

	@brief	レイアウト編集

	@author	ryunosuke ide
	@date	2013.06.11
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <algorithm>
#include "../../include/debug/layoutChanger.h"
#include "../../include/graphics/layout.h"


//--------------------------------define定義--------------------------------
#if defined(_DEBUG)
	#define ENABLE_LAYOUT_CHANGER
#endif


//--------------------------------static変数--------------------------------
namespace nk {
LayoutChanger*	LayoutChanger::m_instance	= NULL;
}	// namespace nk

namespace {

}	// unnamed


//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {


//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
LayoutChanger::LayoutChanger()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
LayoutChanger::~LayoutChanger()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void LayoutChanger::_Init( void )
{
	m_updateLayout.reserve( 128 );
	m_layoutChange	= true;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void LayoutChanger::_Term( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
#endif
}


//===========================================================================
/*!	@brief		レイアウト登録
	@param		layout	登録レイアウト
	@return		----
*/
//===========================================================================
void LayoutChanger::RegisterLayout( graphics::Layout* layout )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_updateLayout.push_back( LayoutData( layout ) );
#endif
}


//===========================================================================
/*!	@brief		レイアウト登録
	@param		layout	登録レイアウト
	@return		----
*/
//===========================================================================
void LayoutChanger::RemoveLayout( graphics::Layout* layout )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_updateLayout.erase( std::remove( m_updateLayout.begin(), m_updateLayout.end(), layout ), m_updateLayout.end() );
#endif
}

//===========================================================================
/*!	@brief		セーブ
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Save( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	VecLayoutData::iterator	itr	= m_updateLayout.begin();
	for( ; itr != m_updateLayout.end(); ++itr ) {
		if( (*itr).layout->Changed() ) {
			_Save( (*itr).layout );
		}
	}
#endif
}


//===========================================================================
/*!	@brief		セーブ
	@param		layout	セーブするレイアウト
	@return		----
*/
//===========================================================================
void  LayoutChanger::_Save( graphics::Layout* layout )
{
	if( layout ) {
		
	}
}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Update( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	if( m_layoutChange ) {
		VecLayoutData::iterator	itr	= m_updateLayout.begin();
		for( ; itr != m_updateLayout.end(); ++itr ) {
			(*itr).layout->UpdateLayoutChange();
		}
	}
#endif
}


//===========================================================================
/*!	@brief		開始
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Start( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_layoutChange	= true;
#endif
}


//===========================================================================
/*!	@brief		終了
	@param		----
	@return		変更が合った場合はtrueを返す
*/
//===========================================================================
bool LayoutChanger::End( void )
{
#if defined(ENABLE_LAYOUT_CHANGER)
	m_layoutChange	= false;

	VecLayoutData::iterator	itr	= m_updateLayout.begin();
	for( ; itr != m_updateLayout.end(); ++itr ) {
		if( (*itr).layout->Changed() ) {
			return true;
		}
	}
#endif
	return false;
}


//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void LayoutChanger::Draw( void )
{
	VecLayoutData::iterator	itr	= m_updateLayout.begin();
	for( ; itr != m_updateLayout.end(); ++itr ) {
		(*itr).layout->DrawActivePartsFrame();
	}
}
	
}	// namespace nk