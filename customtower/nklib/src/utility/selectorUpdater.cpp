//=============================================================================
/*!	@file	selectorUpdater.h

	@brief	セレクタ

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

//-------------------------------インクルード-------------------------------
#include "../../include/utility/selectorUpdater.h"
#include "../../include/math/math.h"
#include "../../include/input/input.h"



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
/*!	@brief		once
	@param		----
	@return		----
*/
//===========================================================================
s32 UpdateOnce::Update( s32 nowSelectNo, input::Input* input, s32 prevButton, s32 nextButton )
{
	
	if( input->IsPressed( prevButton ) ) {
		--nowSelectNo;
	}
	if( input->IsPressed( nextButton ) ) {
		++nowSelectNo;
	}


	return nowSelectNo;	
}


//===========================================================================
/*!	@brief		repeat
	@param		----
	@return		----
*/
//===========================================================================
s32 UpdateRepeat::Update( s32 nowSelectNo, input::Input* input, s32 prevButton, s32 nextButton )
{
	
	if( input->IsPressed( prevButton ) ) {
		--nowSelectNo;
		m_counter = 1;

		return nowSelectNo;
	}
	if( input->IsPressed( nextButton ) ) {
		++nowSelectNo;
		m_counter = 1;
		
		return nowSelectNo;
	}

	if( m_counter == 0 ) {
		return nowSelectNo;
	}

	if( STOP_COUNT <= m_counter ) {
		if( m_counter % UPDATE_INTERVAL == 0 ) {
			if( input->IsPress( prevButton ) ) {
				--nowSelectNo;
			}
			if( input->IsPress( nextButton ) ) {
				++nowSelectNo;
			}
		}
	}

	++m_counter;

	if( input->IsReleased( prevButton ) || input->IsReleased( nextButton ) ) {
		m_counter	= 0;
	}

	return nowSelectNo;	
}

}	// namespace nk