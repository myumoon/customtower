//=============================================================================
/*!	@file	emitter.h
	@brief	エミッター

	@author	ryunosuke ide
	@date	2013.07.03
*/
//=============================================================================

//-------------------------------インクルード-------------------------------



//--------------------------------define定義--------------------------------



//--------------------------------static変数--------------------------------


//--------------------------------static関数--------------------------------


//---------------------------------関数定義---------------------------------

namespace game {
namespace battle {

//===========================================================================
/*!	@brief	コンストラクタ
	@param	----
*/
//===========================================================================
template<typename T>
Emitter::Emitter()
{
	_Init();
}


//===========================================================================
/*!	@brief	デストラクタ
	@param	----
*/
//===========================================================================
template<typename T>
Emitter::~Emitter()
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
void Emitter::_Init( void )
{
	
}


//===========================================================================
/*!	@brief	終了処理
	@param	----
	@return	----
*/
//===========================================================================
template<typename T>
void Emitter::_Term( void )
{

}


}	// namespace battle
}	// namespace game
