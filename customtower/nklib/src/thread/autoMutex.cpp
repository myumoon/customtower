//=============================================================================
/*!	@file	autoMutex.cpp

	@brief	ミューテックス

	@author	ryunosuke ide
	@date	2013.03.10
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/thread/autoMutex.h"


//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------
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
AutoMutex::AutoMutex( Mutex& mutex ) : m_mutex(mutex)
{
	//m_mutex	= mutex;
	m_mutex.Lock();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
AutoMutex::~AutoMutex()
{
	m_mutex.Unlock();
}




	
}	// namespace nk