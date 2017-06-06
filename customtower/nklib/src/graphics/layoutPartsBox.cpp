//=============================================================================
/*!	@file	layoutPartsBox.h

	@brief	レイアウトパーツ入れ

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include <stdlib.h>

#include "../../include/graphics/layoutPartsBox.h"
#include "../../include/collision/collision.h"
#include "../../include/utility/utility.h"
#include "../../include/general.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------


namespace nk {
namespace graphics {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
LayoutPartsBox::LayoutPartsBox()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
LayoutPartsBox::~LayoutPartsBox()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void LayoutPartsBox::_Init( void )
{
	m_partsTree.reserve( 32 );
	
	SetTagName("box");
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void LayoutPartsBox::_Term( void )
{
	DeleteParts();	// 死ぬ時は子供も殺しておく
}


//===========================================================================
/*!	@brief		子供を追加
	@param		parts	追加パーツ
	@return		----
*/
//===========================================================================
void LayoutPartsBox::AddParts( LayoutParts* parts )
{
	m_partsTree.push_back( parts );
}


//===========================================================================
/*!	@brief		子供を追加
	@param		parts	追加パーツ
	@return		----
*/
//===========================================================================
void LayoutPartsBox::AddPartsBox( LayoutPartsBox* partsbox )
{
	m_partsBoxTree.push_back( partsbox );
}



//===========================================================================
/*!	@brief		子供を削除
	@param		child	削除パーツ
	@return		----
*/
//===========================================================================
void LayoutPartsBox::DeleteParts( LayoutParts* parts )
{
	// 葉削除
	VecParts::iterator	itr	= m_partsTree.begin();
	for( ; itr != m_partsTree.end(); ) {
		if( *itr == parts ) {
			LayoutParts*	deleteParts	= *itr;
			itr	= m_partsTree.erase( itr );
			SafeDelete( deleteParts );
		}
		else {
			++itr;
		}
	}
	
}




//===========================================================================
/*!	@brief		子供を全削除
	@param		----
	@return		----
*/
//===========================================================================
void LayoutPartsBox::DeleteParts( void )
{
	// 葉削除
	{
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			SafeDelete( *itr );
		}
		m_partsTree.clear();
	}

	// 枝削除
	{
		VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
		for( ; itr != m_partsBoxTree.end(); ++itr ) {
			(*itr)->DeleteParts();
			SafeDelete( *itr );
		}
		m_partsBoxTree.clear();
	}
	
}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void LayoutPartsBox::UpdateParts( void )
{	
	VecParts::iterator	itr	= m_partsTree.begin();
	for( ; itr != m_partsTree.end(); ++itr ) {
		(*itr)->UpdateParts();
	}
	
}



//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void LayoutPartsBox::DrawParts( void )
{	
	VecParts::iterator	itr	= m_partsTree.begin();
	for( ; itr != m_partsTree.end(); ++itr ) {
		(*itr)->DrawParts();
	}
	
}


//===========================================================================
/*!	@brief		子供を検索
	@param		partsname	パーツ名
	@param		recursive	再帰検索
	@return		----
*/
//===========================================================================
LayoutParts* LayoutPartsBox::FindParts( const char* partsname, bool recursive )
{
	
	// とりあえずカレントルートの中から探す
	{
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			if( (*itr)->IsSameName( partsname ) ) {
				return *itr;
			}
		}
	}

	// 見つからなかったら子供を検索
	{
		LayoutParts*	findParts	= NULL;
		if( recursive ) {
			VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
			for( ; itr != m_partsBoxTree.end(); ++itr ) {
				findParts	= (*itr)->FindParts( partsname, true );
				if( findParts ) {
					return findParts;
				}
			}
		}
	}

	
	return NULL;
}


//===========================================================================
/*!	@brief		ボックスを検索
	@param		partsname	パーツ名
	@param		recursive	再帰検索
	@return		----
*/
//===========================================================================
LayoutPartsBox* LayoutPartsBox::FindPartsBox( const char* partsboxname, bool recursive )
{

	// とりあえずカレントルートから調べる
	{
		VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
		for( ; itr != m_partsBoxTree.end(); ++itr ) {
			if( (*itr)->IsSameName( partsboxname ) ) {
				return *itr;
			}
		}
	}

	// 子供内を検索
	{
		LayoutPartsBox*	findParts	= NULL;
		if( recursive ) {
			VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
			for( ; itr != m_partsBoxTree.end(); ++itr ) {
				findParts	= (*itr)->FindPartsBox( partsboxname, true );
				if( findParts ) {
					return findParts;
				}
			}
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief		位置設定
	@param		pos		位置
	@return		----
*/
//===========================================================================
void LayoutPartsBox::SetPos( const math::Vector& pos )
{
	_SetPosWithChildren( static_cast<s32>(pos.x), static_cast<s32>(pos.y) );
	
}


//===========================================================================
/*!	@brief		位置設定
	@param		x		x座標
	@param		y		y座標
	@return		----
*/
//===========================================================================
void LayoutPartsBox::SetPos( s32 x, s32 y )
{
	_SetPosWithChildren( x, y );
	
}


//===========================================================================
/*!	@brief		子供と一緒に位置設定
	@param		x		x座標
	@param		y		y座標
	@return		----
*/
//===========================================================================
void LayoutPartsBox::_SetPosWithChildren( s32 x, s32 y )
{
	// 移動量
	const math::Vector	moveAmount	= math::Vector( static_cast<f32>(x), static_cast<f32>(y), 0.0f ) - GetPos();

	// 自身移動
	{
		m_pos	= math::Vector( static_cast<f32>(x), static_cast<f32>(y), 0.0f );
	}
	
	// パーツ
	{
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			(*itr)->SetPos( (*itr)->GetPos() + moveAmount );
		}
	}
	
	// ボックス
	{
		VecPartsBox::iterator	itrBox	= m_partsBoxTree.begin();
		for( ; itrBox != m_partsBoxTree.end(); ++itrBox ) {
			(*itrBox)->SetPos( (*itrBox)->GetPos() + moveAmount );
		}
	}
}



//===========================================================================
/*!	@brief		マウス座標を含んでいるパーツを取得
	@param[out]	findParts			検索結果
	@param[out]	findPartsDepath		検索結果パーツの深さ
	@param[in]	mousePos			マウス座標
	@param[in]	depth				現在の深さ
	@return		true.見つかった		false.見つからなかった
*/
//===========================================================================
bool LayoutPartsBox::GetIncludedPartsOf( LayoutParts** outFindParts, s32* outFindPartsDepth, const math::Vector& mousePos, s32 depth )
{
	const s32		thisPartsDepth	= depth + 1;
	
	LayoutParts*	retParts		= NULL;
	s32				retPartsDepth	= 0;

	// ボックスから検索
	{
		bool			isFind				= false;	// 見つかったらtrue
		s32				findPartsDepth		= 0;		// 検索結果パーツの深さ
		LayoutParts*	findParts			= NULL;		// 検索結果
		
		LayoutParts*	deepestParts		= NULL;		// 一番深い場所にあるパーツ
		s32				deepestPartsDepth	= 0;		// 検索結果パーツの深さ
		
		VecPartsBox::iterator	itr	= m_partsBoxTree.begin();
		for( ; itr != m_partsBoxTree.end(); ++itr ) {
			
			isFind	= (*itr)->GetIncludedPartsOf( &findParts, &findPartsDepth, mousePos, thisPartsDepth );

			if( isFind ) {
				// 一番深いパーツを選択
				if( deepestPartsDepth < findPartsDepth ) {
					deepestParts		= findParts;
					deepestPartsDepth	= findPartsDepth;
				}
			}
		}

		retParts	= deepestParts;
	}

	// 子供から検索
	if( retParts == NULL ) {
		const Collision2D::Point		mousePoint( mousePos );
		
		VecParts::iterator	itr	= m_partsTree.begin();
		for( ; itr != m_partsTree.end(); ++itr ) {
			if( Collision2D::IsHit( Collision2D::Rect( (*itr)->GetPos(), (*itr)->GetSize() ), mousePoint ) ) {
				retParts		= *itr;
				retPartsDepth	= thisPartsDepth;
			}		
		}
	}

	if( retParts ) {
		*outFindParts		= retParts;
		*outFindPartsDepth	= retPartsDepth;
	}

	return (retParts != NULL);
}
	
}	// namespace graphics
}	// namespace nk