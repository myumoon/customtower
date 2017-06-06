//=============================================================================
/*!	@file	socketManager.h

	@brief	ソケット管理

	@author	ryunosuke ide
	@date	2013.05.12
*/
//=============================================================================


#ifndef __SOCKET_MANAGER_H__
#define __SOCKET_MANAGER_H__


#include "socket.h"


namespace nk {
	
namespace net {

//=============================================================================
/*!
								ソケット管理
*/
//=============================================================================
class SocketManager {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	//===========================================================================
	/*!	@brief		初期化
	*/
	//===========================================================================
	void		Initialize( void );

	//===========================================================================
	/*!	@brief		終了処理
	*/
	//===========================================================================
	void		Finalize( void );
	
	
private:
	//----------------------メンバ変数-----------------------
	bool	m_initialized;		//!< 初期化済みならtrue
	
	//-----------------------メソッド------------------------
	void	_Init();
	void	_Term();

public:
	//-------------コンストラクタ・デストラクタ--------------
			SocketManager();
	virtual~SocketManager();
};
	
}	// namespace net
	
}	// namespace nk



#endif  // __SOCKET_MANAGER_H__