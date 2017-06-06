//=============================================================================
/*!	@file	selector.h

	@brief	�Z���N�^

	@author	ryunosuke ide
	@date	2013.05.20
*/
//=============================================================================

//-------------------------------�C���N���[�h-------------------------------
//#include "../../include/utility/selector.h"
//#include "../../include/math/math.h"
//#include "../../include/input/input.h"


//--------------------------------define��`--------------------------------



//--------------------------------static�ϐ�--------------------------------
namespace {

}	// unnamed

//--------------------------------static�֐�--------------------------------
namespace {

}	// unnamed

//---------------------------------�֐���`---------------------------------

//namespace nk {






//===========================================================================
/*!	@brief	�R���X�g���N�^
	@param	----
*/
//===========================================================================
template<typename T>
Selector<T>::Selector()
{
	_Init();
}

//===========================================================================
/*!	@brief	�R���X�g���N�^
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
/*!	@brief	�f�X�g���N�^
	@param	----
*/
//===========================================================================
template<typename T>
Selector<T>::~Selector()
{
	_Term();
}


//===========================================================================
/*!	@brief	������
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
/*!	@brief	�I������
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
/*!	@brief		�I�𒆔ԍ����擾
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
/*!	@brief		�X�V
	@param		----
	@return		true.�I�����ꂽ	false.���I��
*/
//===========================================================================
template<typename T>
bool Selector<T>::Update( void )
{
	if( m_cursorUpdater ) {
		s32	prevSelectNo	= m_nowSelectNo;
		
		m_nowSelectNo	= m_cursorUpdater->Update( m_nowSelectNo, m_inputChecker, m_prevButton, m_nextButton );

		if( NOT_SELECTED < m_nowSelectNo ) {

			// �[����
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
				// ��A�N�e�B�u���R�[���o�b�N
				if( m_callbackReceiver && m_callbackOffSelect ) {
					(m_callbackReceiver->*m_callbackOffSelect)( prevSelectNo );
				}

				// �A�N�e�B�u���R�[���o�b�N
				if( m_callbackReceiver && m_callbackOnSelect ) {
					(m_callbackReceiver->*m_callbackOnSelect)( m_nowSelectNo );
				}
			}


			// ����
			if( m_inputChecker->IsPressed( m_decisionButton ) ) {

				// ���莞�R�[���o�b�N
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
/*!	@brief		�R�[���o�b�N���V�[�o�ݒ�
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
/*!	@brief		on���R�[���o�b�N
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
/*!	@brief		off���R�[���o�b�N
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
/*!	@brief		off���R�[���o�b�N
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
/*!	@brief		�ő�ԍ��ݒ�
	@param		maxSelectNo		�ő�ԍ�
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetMaxSelectNo( s32 maxSelectNo )
{
	m_maxSelectNo	= maxSelectNo;
	
}


//===========================================================================
/*!	@brief		�ő�ԍ��ݒ�
	@param		maxSelectNo		�ő�ԍ�
	@return		----
*/
//===========================================================================
template<typename T>
void Selector<T>::SetNowSelectNo( s32 nowSelectNo )
{
	m_nowSelectNo	= nowSelectNo;
	
}

	
//}	// namespace nk
