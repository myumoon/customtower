//=============================================================================
/*!	@file	utility.h

	@brief	���ʊ֐�

	@author	ryunosuke ide
	@date	2013.02.14
*/
//=============================================================================


#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "../typedef.h"
#include "./selector.h"
//#include "./stringfunction.h"
//#include "./csvLoader.h"
//#include "./csvReader.h"

namespace nk {


//! �^�C�}�[�̏�����
extern void InitializeTimer( void );

//! �N��������̌o�ߎ��Ԃ��~���b�ŏK��
extern u64 GetTimeMillSec( void );

//! �N��������̌o�ߎ��Ԃ��}�C�N���b�ŏK��
//extern u64 GetTimeMicSec( void );

//! �w��~���b��~
extern void SleepThread( u64 millsec );


	


}	// namespace nk


#endif  // __UTILITY_H__