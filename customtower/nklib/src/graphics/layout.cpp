//=============================================================================
/*!	@file	layout.h

	@brief	レイアウト

	@author	ryunosuke ide
	@date	2013.06.09
*/
//=============================================================================
//-------------------------------インクルード-------------------------------
#include <algorithm>
#include "../../include/graphics/layout.h"

#include "../../include/general.h"
#include "../../include/debug/layoutChanger.h"
#include "../../include/input/input.h"
#include "../../include/system.h"

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
Layout::Layout()
{
	_Init();
}



//===========================================================================
/*!	@brief	コンストラクタ
	@param	mouse	マウス
*/
//===========================================================================
Layout::Layout( const nk::input::Mouse* mouse )
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Layout::~Layout()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Layout::_Init( void )
{
	m_eventObserver.m_eventListener	= NULL;
	
	m_mouse			= NULL;
	m_keyboard		= NULL;
	

	m_moveable		= false;
	
	LayoutChanger::GetInstance()->RegisterLayout( this );
	m_activeParts.reserve( 32 );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Layout::_Term( void )
{
	LayoutChanger::GetInstance()->RemoveLayout( this );
	
	DeleteParts();

}


//===========================================================================
/*!	@brief		キーボード
	@param		mouse		マウス
	@param		keyboard	キーボード
	@return		----
*/
//===========================================================================
void Layout::Initialize( const input::Mouse* mouse, const input::Keyboard* keyboard )
{
	m_mouse		= mouse;
	m_keyboard	= keyboard;
}

//===========================================================================
/*!	@brief		パーツの削除
	@param		----
	@return		----
*/
//===========================================================================
void Layout::DeleteParts( void )
{
	m_root.DeleteParts();
}


//===========================================================================
/*!	@brief		パーツの更新
	@param		----
	@return		----
*/
//===========================================================================
void Layout::UpdateParts( void )
{
	m_root.UpdateParts();
}


//===========================================================================
/*!	@brief		パーツの描画
	@param		----
	@return		----
*/
//===========================================================================
void Layout::DrawParts( void )
{
	m_root.DrawParts();
}

//===========================================================================
/*!	@brief		パーツの検索
	@param		partsname	パーツ名
	@return		----
*/
//===========================================================================
LayoutParts* Layout::FindParts( const char* partsname )
{
	
	return m_root.FindParts( partsname, true );
}


//===========================================================================
/*!	@brief		パーツの検索
	@param		partsboxname	パーツ名
	@return		----
*/
//===========================================================================
LayoutPartsBox* Layout::FindPartsBox( const char* partsboxname )
{
	
	return m_root.FindPartsBox( partsboxname, true );
}


//===========================================================================
/*!	@brief		ルート取得
	@param		----
	@return		----
*/
//===========================================================================
LayoutPartsBox* Layout::GetRoot( void )
{
	
	return &m_root;
}


//===========================================================================
/*!	@brief		セットアップ
	@param		layoutFilePath	ファイルパス
	@param		listener		イベントリスナー
	@return		----
*/
//===========================================================================
bool Layout::Setup( const char* layoutFilePath, LayoutEventListener* listener )
{
	m_eventObserver.m_eventListener	= listener;

	// @@@@@ ファイルからロード
	// 各パーツに&m_eventObserverを設定する

	return true;
}


//===========================================================================
/*!	@brief		セーブ
	@param		outputPath	出力パス
	@return		----
*/
//===========================================================================
bool Layout::SaveToFile( const char* outputPath )
{

	return true;
}

//===========================================================================
/*!	@brief		レイアウト変更
	@param		----
	@return		----
*/
//===========================================================================
void Layout::UpdateLayoutChange( void )
{
	
	const bool	pressUp		= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_UP ) : false;
	const bool	pressDown	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_DOWN ) : false;
	const bool	pressRight	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_RIGHT ) : false;
	const bool	pressLeft	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_LEFT ) : false;
	const bool	pressCtrl	= m_keyboard ? m_keyboard->IsPress( input::Keyboard::KEY_LCTRL ) | m_keyboard->IsPress( input::Keyboard::KEY_RCTRL ) : false;

	if( m_mouse ) {
		// 登録
		if( m_mouse->IsPressed( input::Mouse::CLICK_LEFT ) ) {

			// 深度設定
			const s32		depth			= 0;
			LayoutParts*	findParts		= NULL;
			s32				findPartsDepth	= 0;
			const bool		isFind			= m_root.GetIncludedPartsOf( &findParts, &findPartsDepth, m_mouse->GetPos(), depth );

			// ctrl押してなかったら一旦クリア
			if( pressCtrl == false ) {
				if( isFind == false ) {
					_ClearActiveParts();
				}
			}
			
			if( isFind ) {
				_AddActiveParts( findParts, findPartsDepth );
				m_moveable	= true;
			}
			else {
				m_moveable	= false;
			}

			// マウス位置を保存
			m_prevMousePos	= m_mouse->GetPos();
		}

		// 移動
		if( m_mouse->IsPress( input::Mouse::CLICK_LEFT ) ) {

			// 登録パーツがあれば移動
			if( m_activeParts.size() ) {

				if( m_moveable ) {

					// マウスに合わせて移動
					const math::Vector	diffMouseMove	= m_mouse->GetPos() - m_prevMousePos;

					VecParts::iterator	itr	= m_activeParts.begin();
					for( ; itr != m_activeParts.end(); ++itr ) {
						(*itr).parts->SetPos( (*itr).parts->GetPos() + diffMouseMove );
					}
				}
			}

			// マウス位置を保存
			m_prevMousePos	= m_mouse->GetPos();
		}
	}

	// キーボードでの移動
	else if( pressUp || pressDown || pressLeft || pressRight ) {
		math::Vector	moveAmount;
		
		if( pressUp ) {
			moveAmount.y	-= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}
		else if( pressDown ) {
			moveAmount.y	+= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}

		if( pressLeft ) {
			moveAmount.x	-= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}
		else if( pressRight ) {
			moveAmount.x	+= pressCtrl ? CTRL_KEYBOARD_MOVE_AMOUNT : KEYBOARD_MOVE_AMOUNT;
		}
		
		VecParts::iterator	itr	= m_activeParts.begin();
		for( ; itr != m_activeParts.end(); ++itr ) {
			(*itr).parts->SetPos( (*itr).parts->GetPos() + moveAmount );
		}
	}
}



//===========================================================================
/*!	@brief		アクティブパーツを追加
	@param		parts		追加パーツ
	@param		depth		深さ
	@return		----
*/
//===========================================================================
void Layout::_AddActiveParts( LayoutParts* parts, s32 depth )
{
	// 重複登録無し
	{
		VecParts::iterator	itr	= m_activeParts.begin();
		for( ; itr != m_activeParts.end(); ++itr ) {
			if( (*itr).parts == parts ) {
				return;
			}
		}
	}
	
	PartsInfo	addInfo;

	addInfo.parts	= parts;
	addInfo.depth	= depth;
	
	m_activeParts.push_back( addInfo );
	
}


//===========================================================================
/*!	@brief		パーツ除外
	@param		parts	パーツ
	@return		----
*/
//===========================================================================
void Layout::_RemoveActiveParts( LayoutParts* parts )
{
	m_activeParts.erase( std::remove( m_activeParts.begin(), m_activeParts.end(), parts ), m_activeParts.end() );
	
}


//===========================================================================
/*!	@brief		アクティブパーツクリア
	@param		----
	@return		----
*/
//===========================================================================
void Layout::_ClearActiveParts( void )
{
	m_activeParts.clear();
	
}


//===========================================================================
/*!	@brief		アクティブパーツの枠を描画
	@param		----
	@return		----
*/
//===========================================================================
void Layout::DrawActivePartsFrame( void )
{
	// ソートするので一旦コピー
	VecParts	vecDrawParts	= m_activeParts;

	std::sort( vecDrawParts.begin(), vecDrawParts.end() );

	const f32			frameAddSize	= 3.0f;	// 本来のフレームサイズに加算するサイズ

	math::Vector		addPoint;
	graphics::Line		drawLine;
	drawLine.SetRenderMode( graphics::Line::RENDER_MODE_2D );
	drawLine.SetColor( Color( 0x0000FFFF ) );
	
	
	const LayoutParts*	drawParts		= NULL;
	VecParts::iterator	itr				= vecDrawParts.begin();
	for( ; itr != vecDrawParts.end(); ++itr ) {
		drawParts	= (*itr).parts;

		const math::Vector&	partsPos	= drawParts->GetPos();

		// クリア
		drawLine.ClearPoints();
		
		// 左上
		drawLine.AddPoint( partsPos + math::Vector( -frameAddSize, -frameAddSize, 0.0f ) );

		// 左下
		drawLine.AddPoint( partsPos + math::Vector( -frameAddSize, drawParts->GetSize().y + frameAddSize, 0.0f ) );
		
		// 右下
		drawLine.AddPoint( partsPos + math::Vector( drawParts->GetSize().x + frameAddSize, drawParts->GetSize().y + frameAddSize, 0.0f ) );

		// 右上
		drawLine.AddPoint( partsPos + math::Vector( drawParts->GetSize().x + frameAddSize, -frameAddSize, 0.0f ) );

		// 左上
		drawLine.AddPoint( partsPos + math::Vector( -frameAddSize, -frameAddSize, 0.0f ) );

		// 描画
		drawLine.Draw();

		SystemPrint( partsPos.x - 20, partsPos.y - 25, "(%d, %d)", static_cast<s32>(partsPos.x), static_cast<s32>(partsPos.y) );
	}
	
}




	

//--------------------------------EventObserver--------------------------------

//===========================================================================
/*!	@brief		ボタン乗った
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorOver( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorOver( eventButton );
	}
}

//===========================================================================
/*!	@brief		ボタン離れた
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorOut( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorOut( eventButton );
	}
}


//===========================================================================
/*!	@brief		ボタン押下アニメーション開始
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorDownStart( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorDownStart( eventButton );
	}
}

//===========================================================================
/*!	@brief		ボタン押下アニメーション終了
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorDownEnd( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorDownEnd( eventButton );
	}
}

//===========================================================================
/*!	@brief		ボタン離されたアニメーション開始
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorUpStart( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorUpStart( eventButton );
	}
}

//===========================================================================
/*!	@brief		ボタン離れたアニメーション終了
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnCursorUpEnd( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnCursorUpEnd( eventButton );
	}
}

//===========================================================================
/*!	@brief		ボタンホールド開始
	@return		----
*/
//===========================================================================
void Layout::EventObserver::OnHold( nk::graphics::Button* eventButton )
{
	if( m_eventListener ) {
		m_eventListener->ButtonOnHold( eventButton );
	}
}






	
}	// namespace graphics
}	// namespace nk