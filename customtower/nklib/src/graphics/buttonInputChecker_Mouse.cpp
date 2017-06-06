
//=============================================================================
/*!	@file	buttonInputChecker_Mouse.h

	@brief	ボタン用マウス入力チェック

	@author	ryunosuke ide
	@date	2013.06.08
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/graphics/buttonInputChecker_Mouse.h"

#include "../../include/graphics/spriteAnimation.h"

//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {
//ButtonInputChecker_Mouse*	defaultChecker	= NULL;
}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------



namespace nk {

namespace graphics {
#if 0
//===========================================================================
/*!	@brief		デフォルトチェックオブジェクトを生成
	@param		mouse	マウス
	@return		----
*/
//===========================================================================
void InitializeDefaultButtonInputChecker_Mouse( const input::Mouse* mouse )
{
	if( defaultChecker == NULL ) {
		defaultChecker	= new ButtonInputChecker_Mouse();
		defaultChecker->Initialize( mouse );
	}
}


//===========================================================================
/*!	@brief		デフォルトチェックオブジェクトの開放
	@param		----
	@return		----
*/
//===========================================================================
void TerminateDefaultButtonInputChecker_Mouse( void )
{
	SafeDelete( defaultChecker );
}

//===========================================================================
/*!	@brief		デフォルトチェックオブジェクトを取得
	@param		----
	@return		----
*/
//===========================================================================
ButtonInputChecker_Mouse*	GetDefaultButtonInputChecker_Mouse( void )
{
	NULL_ASSERT( defaultChecker );
	
	return defaultChecker;
}
#endif
//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
ButtonInputChecker_Mouse::ButtonInputChecker_Mouse()
{
	_Init();
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
ButtonInputChecker_Mouse::ButtonInputChecker_Mouse( const input::Mouse* mouse )
{
	_Init();
	Initialize( mouse );
}

//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
ButtonInputChecker_Mouse::~ButtonInputChecker_Mouse()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
void ButtonInputChecker_Mouse::_Init( void )
{
	m_mouse	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
void ButtonInputChecker_Mouse::_Term( void )
{

}


//===========================================================================
/*!	@brief		初期化
	@param		
	@return		----
*/
//===========================================================================
void ButtonInputChecker_Mouse::Initialize( const input::Mouse* mouse )
{
	m_mouse	= mouse;
}


//===========================================================================
/*!	@brief		アクティブ？
	@param		info	ボタン情報
	@return		----
*/
//===========================================================================
bool ButtonInputChecker_Mouse::IsActive( const CheckInfo& info ) const
{
	if( m_mouse ) {
		const math::Vector			mousePos		= m_mouse->GetPos();
		const resource::Texture*	tex				= info.sprite->GetTexture();
		const u32					buttonWidth		= tex->GetWidth() / info.sprite->GetCol();
		const u32					buttonHeight	= tex->GetHeight() / info.sprite->GetRow();
		
		const math::Vector			leftUp			= info.pos;												// ボタン左上座標
		const math::Vector			rightDown		= leftUp + math::Vector( static_cast<f32>(buttonWidth), static_cast<f32>(buttonHeight), 0.0f );	// ボタン右下座標

		const bool					includeLeftUp	= (leftUp.x < mousePos.x) && (leftUp.y < mousePos.y);
		const bool					includeRightDown= (mousePos.x < rightDown.x) && (mousePos.y < rightDown.y);
		
		if( includeLeftUp && includeRightDown ) {
			return true;
		}
	}

	return false;
}


//===========================================================================
/*!	@brief		アクティブ？
	@param		info	ボタン情報
	@return		----
*/
//===========================================================================
bool ButtonInputChecker_Mouse::IsPress( void ) const
{
	if( m_mouse ) {
		return m_mouse->IsPress( INPUT_CHECK_BUTTON );
	}
	return false;
}
	
}	// namespace graphics
	
}	// namespace nk