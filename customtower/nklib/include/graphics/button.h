//=============================================================================
/*!	@file	button.h

	@brief	ボタン

	@author	ryunosuke ide
	@date	2013.06.07
*/
//=============================================================================


#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "../math/vector.h"
#include "layoutParts.h"
#include "spriteAnimation.h"
#include "buttonEventListener.h"
#include "line.h"


namespace nk {

namespace graphics {

class SpriteAnimation;

//=============================================================================
/*!
								ボタン
*/
//=============================================================================
class Button : public LayoutParts {
public:
	//-----------------------型定義--------------------------

	//! 状態チェッカー
	class EventChecker {
	public:
		struct CheckInfo {
			SpriteAnimation*	sprite;
			math::Vector		pos;
			
			CheckInfo() {
				this->sprite	= NULL;
			}
			CheckInfo( SpriteAnimation* sprite, const math::Vector& pos ) {
				this->sprite	= sprite;
				this->pos		= pos;
			}
		};
	public:
		virtual void	Update( void ) 							{}						//!< 状態更新
		virtual bool	IsActive( const CheckInfo& info ) const	{ return true; }		//!< アクティブ？
		virtual bool	IsPress( void ) const					{ return false; }		//!< 押されている？
	};
	
	//! アニメーション種類
	enum ANIMATION {
		ANIMATION_NORMAL,			//!< 通常
		ANIMATION_ACTIVE,			//!< アクティブ
		ANIMATION_PUSHED,			//!< 押された
		ANIMATION_HOLD,				//!< ホールド
		ANIMATION_RELEASED,			//!< 離された
		ANIMATION_DECIDE,			//!< 決定
		
		ANIMATION_MAX,				//!< アニメーション最大
	};

	//! スプライト情報
	struct SpriteInfo {
		SpriteAnimation*	sprite;			//!< スプライト
		bool				innerCreate;	//!< 内部生成？

		//! コンストラクタ
		SpriteInfo() {
			this->sprite		= NULL;
			this->innerCreate	= false;
		}
	};

	typedef std::vector<SpriteInfo>	VecSprite;

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		描画スクリーン設定
	*/
	//===========================================================================
	void			SetScreen( s32 screenID );

	//===========================================================================
	/*!	@brief		イベントリスナー設定
	*/
	//===========================================================================
	void			SetEventListener( ButtonEventListener* listener );

	//===========================================================================
	/*!	@brief		イベントチェック処理設定
	*/
	//===========================================================================
	void			SetEventChecker( EventChecker* eventChecker );	

	//===========================================================================
	/*!	@brief		通常アニメーション設定
	*/
	//===========================================================================
	void			RegisterButton_Normal( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		アクティブ時アニメーション設定
	*/
	//===========================================================================
	void			RegisterButton_Active( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		押された時アニメーション設定
	*/
	//===========================================================================
	void			RegisterButton_Pushed( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		押しっぱなし時アニメーション設定
	*/
	//===========================================================================
	void			RegisterButton_Hold( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		離された時アニメーション設定
	*/
	//===========================================================================
	void			RegisterButton_Released( SpriteAnimation* sprite );

	//===========================================================================
	/*!	@brief		決定時アニメーション設定
	*/
	//===========================================================================
	void			RegisterButton_Decide( SpriteAnimation* sprite );


	//===========================================================================
	/*!	@brief		通常アニメーション生成
	*/
	//===========================================================================
	void			CreateButton_Normal( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop = true );

	//===========================================================================
	/*!	@brief		アクティブ時アニメーション設定
	*/
	//===========================================================================
	void			CreateButton_Active( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop = true );

	//===========================================================================
	/*!	@brief		押された時アニメーション設定
	*/
	//===========================================================================
	void			CreateButton_Pushed( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame );

	//===========================================================================
	/*!	@brief		押しっぱなし時アニメーション設定
	*/
	//===========================================================================
	void			CreateButton_Hold( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop = true );

	//===========================================================================
	/*!	@brief		離された時アニメーション設定
	*/
	//===========================================================================
	void			CreateButton_Released( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame );

	//===========================================================================
	/*!	@brief		決定時アニメーション設定
	*/
	//===========================================================================
	void			CreateButton_Decide( const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame );


	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual void	UpdateParts( void )	{ if( IsActive() ) { Update(); } }

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	virtual void	DrawParts( void ) { if( IsVisible() ) { Draw(); } }
	
	//===========================================================================
	/*!	@brief		更新
	*/
	//===========================================================================
	virtual void	Update( void );

	//===========================================================================
	/*!	@brief		描画
	*/
	//===========================================================================
	void			Draw( void );

	//===========================================================================
	/*!	@brief		外枠設定
	*/
	//===========================================================================
	void			SetOutsideFrameSize( const math::Vector& size );	//!< サイズ
	void			SetOutsideFrameColor( const Color& color );			//!< 色


protected:
	//===========================================================================
	/*!	@brief		アニメーション設定
	*/
	//===========================================================================
	void					RegisterButton( u32 idx, SpriteAnimation* sprite );
	
	//===========================================================================
	/*!	@brief		アニメーション生成
	*/
	//===========================================================================
	void					CreateButton( u32 idx, const char* path, s32 frame_w, s32 frame_h, s32 row, s32 updateFrame, bool loop );

	//===========================================================================
	/*!	@brief		イベントチェッカー取得
	*/
	//===========================================================================
	const EventChecker*		GetEventChecker( void ) const;

	//===========================================================================
	/*!	@brief		画像チェック
	*/
	//===========================================================================
	bool					IsEnableSetting( void ) const;

	//===========================================================================
	/*!	@brief		アクティブアニメーションを設定
	*/
	//===========================================================================
	void					SetActiveAnimation( ANIMATION animType );

	//===========================================================================
	/*!	@brief		アニメーション開始
	*/
	//===========================================================================
	void					StartActiveAnimation( bool loop );

	//===========================================================================
	/*!	@brief		アニメーション停止
	*/
	//===========================================================================
	void					StopActiveAnimation( void );


	
private:
	//-----------------------メソッド------------------------
	void	_Init( void );
	void	_Term( void );

	enum EVENT_LISTENER_CALLBACK {
		EVENT_LISTENER_CALLBACK_CURSOR_OVER,
		EVENT_LISTENER_CALLBACK_CURSOR_OUT,
		EVENT_LISTENER_CALLBACK_CURSOR_DOWN_START,
		EVENT_LISTENER_CALLBACK_CURSOR_DOWN_END,
		EVENT_LISTENER_CALLBACK_CURSOR_UP_START,
		EVENT_LISTENER_CALLBACK_CURSOR_UP_END,
		EVENT_LISTENER_CALLBACK_CURSOR_HOVER,
		
		EVENT_LISTENER_CALLBACK_MAX,
	};
		
	typedef void (nk::graphics::ButtonEventListener::*EventCallback)( nk::graphics::Button* );

	
	//===========================================================================
	/*!	@brief		リスナーに通知
	*/
	//===========================================================================
	void		_CallEventListener( EVENT_LISTENER_CALLBACK eventType );

	//===========================================================================
	/*!	@brief		スクリーンID設定
	*/
	//===========================================================================
	void		_SetScreenID( void );

private:
	//-----------------------型定義--------------------------
	//! 更新
	//! 次のモードをOnUpdateで返す
	class Updater {
	public:
		virtual void		OnEnter( Button* button )  {}				//!< 入場
		virtual Updater*	OnUpdate( Button* button ) { return NULL; }	//!< 更新
		virtual void		OnExit( Button* button )   {}				//!< 退場
	};
	//! 通常時
	class UpdateNormal : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	//! アクティブ時
	class UpdateActive : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	private:
		u64					m_pressTime;
		bool				m_pushable;
		bool				m_reserveDecide;
	};
	//! ホールド時
	class UpdateHold : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	//! リリース時
	class UpdateRelease : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	//! 決定時
	class UpdateDecide : public Updater {
	public:
		virtual void		OnEnter( Button* button );
		virtual Updater*	OnUpdate( Button* button );
		virtual void		OnExit( Button* button );
	};
	
private:
	//----------------------メンバ変数-----------------------
	VecSprite					m_spriteAnimation;		//!< アニメーション
	SpriteAnimation*			m_activeAnimation;		//!< アクティブなアニメーション
	EventChecker*				m_eventChecker;			//!< イベントチェッカー
	u32							m_prevPressedTime;		//!< 前回押下時間
	Updater*					m_updater;				//!< 更新処理
	s32							m_screenID;				//!< スクリーンID

	ButtonEventListener*		m_eventListener;		//!< イベントリスナー

	//! 仮描画設定
	Line						m_outsizeFrame;			//!< 外枠
	math::Vector				m_outsizeFrameSize;		//!< 外枠サイズ
	
public:
	//-------------コンストラクタ・デストラクタ--------------
			Button();
	virtual~Button();
};


	
}	// namespace graphics
	
}	// namespace nk


#endif  // __BUTTON_H__