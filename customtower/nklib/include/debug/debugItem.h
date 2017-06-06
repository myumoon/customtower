//=============================================================================
/*!	@file	debugItem.h

	@brief	デバッグ項目

	@author	ryunosuke ide
	@date	2013.06.16
*/
//=============================================================================

#ifndef __DEBUG_ITEM_H__
#define __DEBUG_ITEM_H__


namespace nk {
namespace debug {

enum CALL_EVENT {
	CALL_EVENT_PLUS,
	CALL_EVENT_MUNUS,
	CALL_EVENT_DECIDE,
};

//=============================================================================
/*!
							呼び出し用インターフェース
*/
//=============================================================================
class DebugItemInterface {
public:

	//! 呼び出し
	virtual void		CallDebugFunc( u32 lineNo, CALL_EVENT event ) = 0;

	//! 描画文字列取得
	virtual std::string	GetDispValue( void ) = 0;

	//! オブジェクト比較
	virtual bool		IsEqualObject( void* obj ) const = 0;

	//! 表示文字列セット
	void				SetItemName( const char* itemName )
	{
		m_itemName.assign( itemName );
	}

	//! 表示文字列取得
	const char*			GetItemName( void ) const
	{
		return m_itemName.c_str();
	}

private:
	std::string		m_itemName;		//!< 表示文字列
};



//=============================================================================
/*!
							デバッグ呼び出し
*/
//=============================================================================
template<typename T>
class DebugItem : public DebugItemInterface {
public:
	//! 呼び出し関数
	typedef void 		(T::*EventCallbackFunc)( u32, CALL_EVENT );
	typedef std::string (T::*DispCallbackFunc)( void );

	//===========================================================================
	/*!	@brief		コンストラクタ
	*/
	//===========================================================================
	DebugItem( T* cls, EventCallbackFunc eventCallbackFunc, DispCallbackFunc dispCalbackFunc, const char* itemName )
	{
		m_debugTarget		= cls;
		m_eventCallbackFunc	= eventCallbackFunc;
		m_dispCallbackFunc	= dispCalbackFunc;
		SetItemName( itemName );
	}

	//===========================================================================
	/*!	@brief		デバッグ機能呼び出し
	*/
	//===========================================================================
	virtual void	CallDebugFunc( u32 lineNo, CALL_EVENT event )
	{
		if( m_debugTarget && m_eventCallbackFunc ) {
			(m_debugTarget->*m_eventCallbackFunc)( lineNo, event );
		}
	}

	//===========================================================================
	/*!	@brief		表示文字列取得
	*/
	//===========================================================================
	virtual std::string	GetDispValue( void )
	{
		if( m_debugTarget && m_dispCallbackFunc ) {
			return (m_debugTarget->*m_dispCallbackFunc)();
		}
		return "";
	}

	//===========================================================================
	/*!	@brief		オブジェクト比較
	*/
	//===========================================================================
	virtual bool	IsEqualObject( void* obj ) const
	{
		return reinterpret_cast<u32>(m_debugTarget) == reinterpret_cast<u32>(obj);
	}
private:
	T*					m_debugTarget;			//!< 呼び出しオブジェクト
	EventCallbackFunc	m_eventCallbackFunc;	//!< 呼び出しメンバ関数
	DispCallbackFunc	m_dispCallbackFunc;		//!< 描画時呼び出し関数

	DebugItem();	// 呼び出し負荷
};
	
}	// namespace debug
}	// namespace nk

#define DEBUG_ITEM_CREATE( type, memberfunc ) new nk::debug::DebugItem<type>( this, &type::memberfunc )


	
#endif  // __DEBUG_ITEM_H__