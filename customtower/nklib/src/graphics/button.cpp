//=============================================================================
/*!	@file	button.h

	@brief	ボタン

	@author	ryunosuke ide
	@date	2013.06.07
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/graphics/button.h"

#include "../../include/utility/utility.h"
#include "../../include/graphics/buttonEventListener.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

	
}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

namespace nk {

namespace graphics {


}	// namespace graphics
	
}	// namespace nk

//---------------------------------関数定義---------------------------------


namespace nk {

namespace graphics {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
Button::Button()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
Button::~Button()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void Button::_Init( void )
{
	SetTagName("button");
	
	m_spriteAnimation.resize( ANIMATION_MAX );
	for( u32 i = 0; i < m_spriteAnimation.size(); ++i ) {
		m_spriteAnimation[i].sprite	= NULL;
	}
	
	m_activeAnimation	= NULL;
	m_eventChecker		= NULL;
	m_prevPressedTime	= 0;

	m_updater			= NULL;
	m_eventListener		= NULL;
	m_screenID			= 0;

	m_outsizeFrame.SetColor( Color( 0x009cffff ) );	// 青～水色
	m_outsizeFrame.SetRenderMode( Line::RENDER_MODE_2D );
	m_outsizeFrameSize.SetVector( 60, 30, 0 );
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void Button::_Term( void )
{
	if( m_updater ) {
		m_updater->OnExit( this );
	}
	SafeDelete( m_updater );

	for( u32 i = 0; i < m_spriteAnimation.size(); ++i ) {
		if( m_spriteAnimation[i].innerCreate ) {
			SafeDelete( m_spriteAnimation[i].sprite );
		}
	}
	
}

//===========================================================================
/*!	@brief		イベントリスナー設定
	@param		eventChecker	チェッカー
	@return		----
*/
//===========================================================================
void Button::SetEventListener( ButtonEventListener* listener )
{
	m_eventListener	= listener;
}

	
//===========================================================================
/*!	@brief		イベントチェッカー設定
	@param		eventChecker	チェッカー
	@return		----
*/
//===========================================================================
void Button::SetEventChecker( EventChecker* eventChecker )
{
	m_eventChecker	= eventChecker;
}


//===========================================================================
/*!	@brief		通常アニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Normal( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_NORMAL, sprite );
	
}


//===========================================================================
/*!	@brief		アクティブアニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Active( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_ACTIVE, sprite );
	
}



//===========================================================================
/*!	@brief		押下時アニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Pushed( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_PUSHED, sprite );
	
}




//===========================================================================
/*!	@brief		ホールドアニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Hold( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_HOLD, sprite );
	
}




//===========================================================================
/*!	@brief		離した時アニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Released( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_RELEASED, sprite );
	
}


//===========================================================================
/*!	@brief		決定時アニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::RegisterButton_Decide( SpriteAnimation* sprite )
{
	RegisterButton( ANIMATION_DECIDE, sprite );
	
}



//===========================================================================
/*!	@brief		既存アニメーション登録
	@param		idx			インデックス
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::RegisterButton( u32 idx, SpriteAnimation* sprite )
{
	ASSERT( idx < m_spriteAnimation.size(), "array size is not enough." );

	if( m_spriteAnimation[idx].sprite != NULL ) {
		if( m_spriteAnimation[idx].innerCreate ) {
			SafeDelete( m_spriteAnimation[idx].sprite );
		}
	}
	m_spriteAnimation[idx].sprite		= sprite;
	m_spriteAnimation[idx].innerCreate	= false;

	_SetScreenID();
}







//===========================================================================
/*!	@brief		通常アニメーション生成
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::CreateButton_Normal( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	CreateButton( ANIMATION_NORMAL, path, frame_w, frame_h, row, updateFrame, loop );

	SetSize( frame_w, frame_h );
}


//===========================================================================
/*!	@brief		アクティブアニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::CreateButton_Active( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	CreateButton( ANIMATION_ACTIVE, path, frame_w, frame_h, row, updateFrame, loop );
	
}



//===========================================================================
/*!	@brief		押下時アニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::CreateButton_Pushed( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame )
{
	CreateButton( ANIMATION_PUSHED, path, frame_w, frame_h, row, updateFrame, false );
	
}


//===========================================================================
/*!	@brief		ホールドアニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::CreateButton_Hold( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	CreateButton( ANIMATION_HOLD, path, frame_w, frame_h, row, updateFrame, loop );
	
}




//===========================================================================
/*!	@brief		離した時アニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::CreateButton_Released( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame )
{
	CreateButton( ANIMATION_RELEASED, path, frame_w, frame_h, row, updateFrame, false );
	
}


//===========================================================================
/*!	@brief		決定時アニメーション設定
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::CreateButton_Decide( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame )
{
	CreateButton( ANIMATION_DECIDE, path, frame_w, frame_h, row, updateFrame, false );
	
}



//===========================================================================
/*!	@brief		アニメーション生成
	@param		idx			インデックス
	@param		sprite		アニメーション画像
	@return		----
*/
//===========================================================================
void Button::CreateButton( u32 idx, const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop )
{
	ASSERT( idx < m_spriteAnimation.size(), "array size is not enough." );

	if( m_spriteAnimation[idx].sprite != NULL ) {
		if( m_spriteAnimation[idx].innerCreate ) {
			SafeDelete( m_spriteAnimation[idx].sprite );
		}
	}

	SpriteAnimation*	anim	= new SpriteAnimation( path, frame_w, frame_h, row, updateFrame, loop );
	m_spriteAnimation[idx].sprite		= anim;
	m_spriteAnimation[idx].innerCreate	= true;
}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		----
*/
//===========================================================================
void Button::Update( void )
{
	if( m_eventChecker == NULL ) {
		return;
	}
	
	
	m_eventChecker->Update();

	if( m_updater == NULL ) {
		m_updater	= new UpdateNormal();
		m_updater->OnEnter( this );
	}
	
	if( m_activeAnimation ) {
		m_activeAnimation->Update();
	}
	Updater*	nextUpdater	= m_updater->OnUpdate( this );
	
	if( nextUpdater != NULL ) {
		if( nextUpdater != m_updater ) {
			m_updater->OnExit( this );
			SafeDelete( m_updater );

			m_updater	= nextUpdater;
			m_updater->OnEnter( this );
		}
	}
	
}

//===========================================================================
/*!	@brief		イベントチェッカー取得
	@param		----
	@return		----
*/
//===========================================================================
const Button::EventChecker* Button::GetEventChecker( void ) const
{

	return m_eventChecker;
}


//===========================================================================
/*!	@brief		アクティブアニメーション設定
	@param		animType	アニメーション
	@return		----
*/
//===========================================================================
void Button::SetActiveAnimation( ANIMATION animType )
{
	SpriteAnimation*	nextAnim	= m_spriteAnimation[animType].sprite;
	if( nextAnim ) {
		m_activeAnimation	= nextAnim;
	}
	
}


//===========================================================================
/*!	@brief		設定可能ならtrueを返す
	@param		----
	@return		----
*/
//===========================================================================
bool Button::IsEnableSetting( void ) const
{

	return ((m_activeAnimation != NULL) && (m_eventChecker != NULL));
}



//===========================================================================
/*!	@brief		アニメーション開始
	@param		loop	ループ
	@return		----
*/
//===========================================================================
void Button::StartActiveAnimation( bool loop )
{
	if( m_activeAnimation ) {
		m_activeAnimation->SetVisible( true );
		m_activeAnimation->SetAnimationLoop( loop );
		m_activeAnimation->Start();
	}
	
}




//===========================================================================
/*!	@brief		アニメーション停止
	@param		----
	@return		----
*/
//===========================================================================
void Button::StopActiveAnimation( void )
{
	if( m_activeAnimation ) {
		m_activeAnimation->Stop();
		m_activeAnimation->SetVisible( false );
	}
	
}


//===========================================================================
/*!	@brief		描画
	@param		----
	@return		----
*/
//===========================================================================
void Button::Draw( void )
{
	if( m_activeAnimation ) {
		m_activeAnimation->Draw( GetPos() );
	}
	// スプライトが設定されていなかったら仮で線でボタンの枠を作る
	else {
		const math::Vector	lu( GetPos().x, 						GetPos().y							);	// 左上
		const math::Vector	ld( GetPos().x, 						GetPos().y + m_outsizeFrameSize.y	);	// 左下
		const math::Vector	rd( GetPos().x + m_outsizeFrameSize.x, GetPos().y + m_outsizeFrameSize.y	);	// 右下
		const math::Vector	ru( GetPos().x + m_outsizeFrameSize.x, GetPos().y							);	// 左上

		m_outsizeFrame.ClearPoints();
		m_outsizeFrame.AddPoint( lu );
		m_outsizeFrame.AddPoint( ld );
		m_outsizeFrame.AddPoint( rd );
		m_outsizeFrame.AddPoint( ru );
		m_outsizeFrame.AddPoint( lu );

		m_outsizeFrame.Draw();
	}
	
}



//===========================================================================
/*!	@brief		外枠サイズ設定
	@param		size	サイズ
	@return		----
*/
//===========================================================================
void Button::SetOutsideFrameSize( const math::Vector& size )
{
	m_outsizeFrameSize	= size;
	
}



//===========================================================================
/*!	@brief		外枠色設定
	@param		color	色
	@return		----
*/
//===========================================================================
void Button::SetOutsideFrameColor( const Color& color )
{
	m_outsizeFrame.SetColor( color );
	
}



//===========================================================================
/*!	@brief		リスナーに通知
	@param		----
	@return		----
*/
//===========================================================================
void Button::_CallEventListener( EVENT_LISTENER_CALLBACK callbackType )
{
	const EventCallback	eventCallbacks[] = {
		&nk::graphics::ButtonEventListener::OnCursorOver,
		&nk::graphics::ButtonEventListener::OnCursorOut,
		&nk::graphics::ButtonEventListener::OnCursorDownStart,
		&nk::graphics::ButtonEventListener::OnCursorDownEnd,
		&nk::graphics::ButtonEventListener::OnCursorUpStart,
		&nk::graphics::ButtonEventListener::OnCursorUpEnd,
		&nk::graphics::ButtonEventListener::OnHold,
	};

	if( m_eventListener ) {
		(m_eventListener->*eventCallbacks[callbackType])( this );
	}
	
}

	
//--------------------------------更新--------------------------------


	

//===========================================================================
/*!	@brief		通常入場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateNormal::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_NORMAL );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( true );		
	}
}

//===========================================================================
/*!	@brief		通常更新
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateNormal::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		Button::EventChecker::CheckInfo	info( button->m_activeAnimation, button->GetPos() );
		const bool	active	= button->GetEventChecker()->IsActive( info );

		if( active ) {
			button->SetActiveAnimation( Button::ANIMATION_ACTIVE );
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_OVER );
			return new Button::UpdateActive();
		}
	}

	return NULL;
}


//===========================================================================
/*!	@brief		通常入場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateNormal::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}
	
}
	
//===========================================================================
/*!	@brief		アクティブ入場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateActive::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_ACTIVE );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( true );
	}
	m_pressTime		= 0;
	m_pushable		= (button->GetEventChecker()->IsPress() == false);
	m_reserveDecide	= false;
}

//===========================================================================
/*!	@brief		アクティブ更新
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateActive::OnUpdate( Button* button )
{
	static const u32	MOVE_HOLD_MILLISEC	= 100;

	// 決定予約が入っていたらそれを処理する
	if( m_reserveDecide ) {
		if( button->m_activeAnimation->IsEnd() ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END );
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_START );
			return new Button::UpdateDecide();
		}
	}
	else {
		if( button->IsEnableSetting() ) {
			Button::EventChecker::CheckInfo	info( button->m_activeAnimation, button->GetPos() );
			const bool	active	= button->GetEventChecker()->IsActive( info );
			const bool	press	= button->GetEventChecker()->IsPress();	

			if( active == false ) {
				button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_OUT );
				return new Button::UpdateRelease();
			}

			m_pushable	|= (button->GetEventChecker()->IsPress() == false);

			if( press ) {
				if(/* m_pushable &&*/ (m_pressTime == 0) ) {
					// アクティブアニメを終了
					button->StopActiveAnimation();

					// 押下アニメ再生
					button->SetActiveAnimation( ANIMATION_PUSHED );
					if( button->IsEnableSetting() ) {
						button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_START );
						button->StartActiveAnimation( false );
					}
					
					m_pressTime	= GetTimeMillSec();
				}
				else if( (MOVE_HOLD_MILLISEC <= m_pressTime) && (button->m_activeAnimation->IsEnd()) ) {
					button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END );
					button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_HOVER );
					return new Button::UpdateHold();
				}
			}
			else {
				if( m_pressTime != 0 ) {
					if( button->m_activeAnimation->IsEnd() ) {
						button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END );
						button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_START );
						return new Button::UpdateDecide();
					}
					else {
						m_reserveDecide	= true;
					}
				}
			}
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		アクティブ退場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateActive::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}

	
//===========================================================================
/*!	@brief		ホールド入場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateHold::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_HOLD );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( true );
	}
	
}

//===========================================================================
/*!	@brief		ホールド更新
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateHold::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		Button::EventChecker::CheckInfo	info( button->m_activeAnimation, button->GetPos() );
		const bool	active	= button->GetEventChecker()->IsActive( info );
		const bool	press	= button->GetEventChecker()->IsPress();	

		if( active == false ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_OUT );
			return new Button::UpdateRelease();
		}

		if( press == false ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_START );
			return new Button::UpdateDecide();
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		ホールド退場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateHold::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}



//===========================================================================
/*!	@brief		リリース入場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateRelease::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_RELEASED );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( false );
	}
	
}

//===========================================================================
/*!	@brief		リリース更新
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateRelease::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		if( button->m_activeAnimation->IsEnd() ) {
			return new Button::UpdateNormal();
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		リリース退場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateRelease::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}



//===========================================================================
/*!	@brief		決定入場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateDecide::OnEnter( Button* button )
{
	button->SetActiveAnimation( Button::ANIMATION_DECIDE );
	
	if( button->IsEnableSetting() ) {
		button->StartActiveAnimation( false );
	}
	
}

//===========================================================================
/*!	@brief		決定更新
	@param		----
	@return		----
*/
//===========================================================================
Button::Updater* Button::UpdateDecide::OnUpdate( Button* button )
{
	if( button->IsEnableSetting() ) {
		if( button->m_activeAnimation->IsEnd() ) {
			button->_CallEventListener( EVENT_LISTENER_CALLBACK_CURSOR_UP_END );
			return new Button::UpdateNormal();
		}
	}

	return NULL;
}

//===========================================================================
/*!	@brief		決定退場
	@param		----
	@return		----
*/
//===========================================================================
void Button::UpdateDecide::OnExit( Button* button )
{
	if( button->IsEnableSetting() ) {
		button->StopActiveAnimation();
	}

}


//===========================================================================
/*!	@brief		スクリーンID設定
	@param		screenID	id
	@return		----
*/
//===========================================================================
void Button::SetScreen( s32 screenID )
{
	m_screenID	= screenID;

	_SetScreenID();
	
}


//===========================================================================
/*!	@brief		スクリーンID設定
	@param		----
	@return		----
*/
//===========================================================================
void Button::_SetScreenID( void )
{
	for( u32 i = 0; i < m_spriteAnimation.size(); ++i ) {
		if( m_spriteAnimation[i].sprite ) {
			m_spriteAnimation[i].sprite->SetScreenId( m_screenID );
		}
	}
}

	
}	// namespace graphics
	
}	// namespace nk