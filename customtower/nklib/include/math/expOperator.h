//=============================================================================
/*!	@file	expOperator.h
	@brief	Expression Template

	@author	ryunosuke ide
	@date	2013.12.15
*/
//=============================================================================

#ifndef __EXP_OPERATOR_H__
#define __EXP_OPERATOR_H__



namespace nk {

#if 0
//=============================================================================
/*!
								+
*/
//=============================================================================
template<class T, class U>
struct OpPlus {
	static float	Apply( const T& lhs, const U& rhs )
	{
		return lhs + rhs;
	}
};

//=============================================================================
/*!
								-
*/
//=============================================================================
template<class T, class U>
struct OpMinus {
	static float	Apply( const T& lhs, const U& rhs )
	{
		return lhs - rhs;
	}
};

//=============================================================================
/*!
								*
*/
//=============================================================================
template <class T, class U>
struct OpMul {
	static float	Apply( const T& lhs, const U& rhs )
	{
		return lhs * rhs;
	}
};


//=============================================================================
/*!
								/
*/
//=============================================================================
template<class T, class U>
struct OpDiv {
	static float	Apply( const T& lhs, const U& rhs )
	{
		return lhs / rhs;
	}
};
#else
//=============================================================================
/*!
								+
*/
//=============================================================================
struct OpPlus {
	static float	Apply( float lhs, float rhs )
	{
		return lhs + rhs;
	}
};

//=============================================================================
/*!
								-
*/
//=============================================================================
struct OpMinus {
	static float	Apply( float lhs, float rhs )
	{
		return lhs - rhs;
	}
};

//=============================================================================
/*!
								*
*/
//=============================================================================
struct OpMul {
	static float	Apply( float lhs, float rhs )
	{
		return lhs * rhs;
	}
};


//=============================================================================
/*!
								/
*/
//=============================================================================
struct OpDiv {
	static float	Apply( float lhs, float rhs )
	{
		return lhs / rhs;
	}
};
#endif

//=============================================================================
/*!
								演算保持
*/
//=============================================================================
template <class L, class Op, class R>
class Exp {
public:
	//-----------------------型定義--------------------------
	

	//----------------------静的メンバ-----------------------
	
	
	//-----------------------メソッド------------------------

	template<class R2>
	Exp<Exp<L, Op, R>, OpPlus, R2>	operator+( const R2& r2 )
	{
		return Exp<Exp<L, Op, R>, OpPlus, R2>( *this, r2 );
	}

	template<class R2>
	Exp<Exp<L, Op, R>, OpMinus, R2>	operator-( const R2& r2 )
	{
		return Exp<Exp<L, Op, R>, OpMinus, R2>( *this, r2 );
	}

	template<class R2>
	Exp<Exp<L, Op, R>, OpMul, R2>	operator*( const R2& r2 )
	{
		return Exp<Exp<L, Op, R>, OpMul, R2>( *this, r2 );
	}

	template<class R2>
	Exp<Exp<L, Op, R>, OpDiv, R2>	operator/( const R2& r2 )
	{
		return Exp<Exp<L, Op, R>, OpDiv, R2>( *this, r2 );
	}

	//===========================================================================
	/*!	@brief		実際の計算
	*/
	//===========================================================================
	float	operator[]( std::size_t i ) const
	{
		return Op::Apply( m_lhs[i], m_rhs[i] );
	}
	
private:
	//-----------------------メソッド------------------------

	//----------------------メンバ変数-----------------------
	const L&	m_lhs;		//!< 左辺
	const R&	m_rhs;		//!< 右辺

public:
	//-------------コンストラクタ・デストラクタ--------------
	Exp( const L& lhs, const R& rhs ) : m_lhs(lhs), m_rhs(rhs) {}
	virtual~Exp( void ) {}
};

	
}	// namespace nk



#endif  // __EXP_OPERATOR_H__