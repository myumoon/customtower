//=============================================================================
/*!	@file	debugItem.h

	@brief	�f�o�b�O����

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
							�Ăяo���p�C���^�[�t�F�[�X
*/
//=============================================================================
class DebugItemInterface {
public:

	//! �Ăяo��
	virtual void		CallDebugFunc( u32 lineNo, CALL_EVENT event ) = 0;

	//! �`�敶����擾
	virtual std::string	GetDispValue( void ) = 0;

	//! �I�u�W�F�N�g��r
	virtual bool		IsEqualObject( void* obj ) const = 0;

	//! �\��������Z�b�g
	void				SetItemName( const char* itemName )
	{
		m_itemName.assign( itemName );
	}

	//! �\��������擾
	const char*			GetItemName( void ) const
	{
		return m_itemName.c_str();
	}

private:
	std::string		m_itemName;		//!< �\��������
};



//=============================================================================
/*!
							�f�o�b�O�Ăяo��
*/
//=============================================================================
template<typename T>
class DebugItem : public DebugItemInterface {
public:
	//! �Ăяo���֐�
	typedef void 		(T::*EventCallbackFunc)( u32, CALL_EVENT );
	typedef std::string (T::*DispCallbackFunc)( void );

	//===========================================================================
	/*!	@brief		�R���X�g���N�^
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
	/*!	@brief		�f�o�b�O�@�\�Ăяo��
	*/
	//===========================================================================
	virtual void	CallDebugFunc( u32 lineNo, CALL_EVENT event )
	{
		if( m_debugTarget && m_eventCallbackFunc ) {
			(m_debugTarget->*m_eventCallbackFunc)( lineNo, event );
		}
	}

	//===========================================================================
	/*!	@brief		�\��������擾
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
	/*!	@brief		�I�u�W�F�N�g��r
	*/
	//===========================================================================
	virtual bool	IsEqualObject( void* obj ) const
	{
		return reinterpret_cast<u32>(m_debugTarget) == reinterpret_cast<u32>(obj);
	}
private:
	T*					m_debugTarget;			//!< �Ăяo���I�u�W�F�N�g
	EventCallbackFunc	m_eventCallbackFunc;	//!< �Ăяo�������o�֐�
	DispCallbackFunc	m_dispCallbackFunc;		//!< �`�掞�Ăяo���֐�

	DebugItem();	// �Ăяo������
};
	
}	// namespace debug
}	// namespace nk

#define DEBUG_ITEM_CREATE( type, memberfunc ) new nk::debug::DebugItem<type>( this, &type::memberfunc )


	
#endif  // __DEBUG_ITEM_H__