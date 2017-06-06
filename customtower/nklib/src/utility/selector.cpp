//=============================================================================
/*!	@file	selector.h

	@brief	セレクタ

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
//#include "../../include/utility/selector.h"
//#include "../../include/math/math.h"
//#include "../../include/input/input.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
namespace {

}	// unnamed

//--------------------------------static関数--------------------------------
namespace {

}	// unnamed

//---------------------------------関数定義---------------------------------

//namespace nk {






//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
template<typename T>
Selector<T>::Selector()
{
	_Init();
}

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
template<typename T>
Selector<T>::Selector( T* callbackReceiver )
{
	_Init();
	SetCallbackReceiver( callbackReceiver );
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
template<typename T>
Selector<T>::~Selector()
{
	_Term();
}


//===========================================================================
/*!	@brief	初期化
	@param	----
	@return	----
*/
//===========================================================================
template<typename T>
void Selector<T>::_Init( void )
{
	m_nowSelectNo	= NOT_SELECTED;
	m_maxSelectNo	= 0;
	m_loop			= true;
	m_inputChecker	= NULL;
	m_cursorUpdater	= NULL;

	m_callbackOnSelect		= NULL;
	m_callbackOffSelect		= NULL;
	m_callbackDecideSelect	= NULL;
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
template<typename T>
void Selector<T>::_Term( void )
{
	SafeDelete( m_cursorUpdater );
}


//===========================================================================
/*!	@brief		選択中番号を取得
	@param		----
	@return		----
*/
//===========================================================================
template<typename T>
s32 Selector<T>::GetSelectNo( void ) const
{

	return m_nowSelectNo;
}


//===========================================================================
/*!	@brief		更新
	@param		----
	@return		true.選択された	false.未選択
*/
//===========================================================================
template<typename T>
bool Selector<T>::Update( void )
{
	if( m_cursorUpdater ) {
		s32	prevSelectNo	= m_nowSelectNo;
		
		m_nowSelectNo	= m_cursorUpdater->Update( m_nowSelectNo, m_inputChecker, m_prevButton, m_nextButton );

		if( NOT_SELECTED < m_nowSelectNo ) {

			// 端処理
			if( m_loop ) {
				if( m_nowSelectNo < 0 ) {
					m_nowSelectNo	= m_maxSelectNo - 1;
				}
				else if( m_maxSelectNo <= m_nowSelectNo ) {
					m_nowSelectNo	= 0;
				}
			}
			else {
				m_nowSelectNo	= math::Clamp( m_nowSelectNo, 0, m_maxSelectNo - 1 );
			}

			if( m_nowSelectNo != prevSelectNo ) {
				// 非アクティブ時コールバック
				if( m_callbackReceiver && m_callbackOffSelect ) {
					(m_callbackReceiver->*m_callbackOffSelect)( prevSelectNo );
				}

				// アクティブ時コールバック
				if( m_callbackReceiver && m_callbackOnSelect ) {
					(m_callbackReceiver->*m_callbackOnSelect)( m_nowSelectNo );
				}
			}


			// 決定
			if( m_inputChecker->IsPressed( m_decisionButton ) ) {

				// 決定時コールバック
				if( m_callbackReceiver && m_callbackDecideSelect ) {
					(m_callbackReceiver->*m_callbackDecideSelect)( m_nowSelectNo );
				}
				
				return true;
			}

		}
	}

	return false;
}


//===========================================================================
/*!	@brief		コールバックレシーバ設定
	@param		----
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetCallbackReceiver( T* callbackReceiver )
{
	m_callbackReceiver	= callbackReceiver;
	
}

//===========================================================================
/*!	@brief		on時コールバック
	@param		----
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetOnSelectCallback( SelectEventCallback callbackFunc )
{
	m_callbackOnSelect	= callbackFunc;
	
}

//===========================================================================
/*!	@brief		off時コールバック
	@param		----
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetOffSelectCallback( SelectEventCallback callbackFunc )
{
	m_callbackOffSelect	= callbackFunc;
	
}


//===========================================================================
/*!	@brief		off時コールバック
	@param		----
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetDecideCallback( SelectEventCallback callbackFunc )
{
	m_callbackDecideSelect	= callbackFunc;
	
}



//===========================================================================
/*!	@brief		最大番号設定
	@param		maxSelectNo		最大番号
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetMaxSelectNo( s32 maxSelectNo )
{
	m_maxSelectNo	= maxSelectNo;
	
}


//===========================================================================
/*!	@brief		最大番号設定
	@param		maxSelectNo		最大番号
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetNowSelectNo( s32 nowSelectNo )
{
	m_nowSelectNo	= nowSelectNo;
	
}

	
//}	// namespace nk
