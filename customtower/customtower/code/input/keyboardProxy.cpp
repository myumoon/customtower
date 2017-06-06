/*-------------------------------------------------------------------------
	説　明：キーボードの設定を反映させるクラス
	作成日：2010/10/01
	更新日：2010/10/01
--------------------------------------------------------------------------*/
#include "KeyboardProxy.h"



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：コンストラクタ
//	引　数：なし
//	戻り値：
//	 memo ：
//========================================================================
CKeyboardProxy::CKeyboardProxy()
{

	Init();

}



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：デストラクタ
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
CKeyboardProxy::~CKeyboardProxy()
{


	Finalize();

}


//========================================================================
//	クラス：CKeyboardProxy
//	内　容：初期化
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
void CKeyboardProxy::Init()
{

	m_keyboard = NULL;

	/* 移動キーをセット */
	m_urdl[__UP]	= KEY_UP;
	m_urdl[__RIGHT]	= KEY_RIGHT;
	m_urdl[__DOWN]	= KEY_DOWN;
	m_urdl[__LEFT]	= KEY_LEFT;

}


//========================================================================
//	クラス：CKeyboardProxy
//	内　容：終了処理
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
void CKeyboardProxy::Finalize()
{


}


//========================================================================
//	クラス：Finalize
//	内　容：更新
//	引　数：なし
//	戻り値：なし
//	 memo ：
//========================================================================
void CKeyboardProxy::Update()
{

	if( !m_keyboard ) {
		m_keyboard = new CKeyboard();
	}

	m_keyboard->Update();

}



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：押されているか
//	引　数：c		: コマンド
//	戻り値：true	: 押されている
//			false	: 押されていない
//	 memo ：
//========================================================================
bool CKeyboardProxy::IsPress(Command c)
{

	return m_keyboard->IsPress(m_config[c]);
}



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：押したか
//	引　数：c		: コマンド
//	戻り値：true	: 押した
//			false	: 押していない
//	 memo ：
//========================================================================
bool CKeyboardProxy::IsPressed(Command c)
{

	return m_keyboard->IsPressed(m_config[c]);
}



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：離したか
//	引　数：c		: コマンド
//	戻り値：true	: 離している
//			false	: 離していない
//	 memo ：
//========================================================================
bool CKeyboardProxy::IsRelease(Command c)
{

	return m_keyboard->IsRelease(m_config[c]);
}



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：離したか
//	引　数：c		: コマンド
//	戻り値：true	: 離した
//			false	: その他
//	 memo ：
//========================================================================
bool CKeyboardProxy::IsReleased(Command c)
{

	return m_keyboard->IsReleased(m_config[c]);
}



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：配列に番号をセット
//	引　数：key_num	: セットするコマンド
//			num		: パッドのボタン
//	戻り値：
//	 memo ：
//========================================================================
void CKeyboardProxy::SetCommandButtom(int key_num, int cmd)
{

	assert((0 <= cmd) && (cmd < GetArraySize(m_buttom_idx)));

	m_buttom_idx[cmd] = key_num;

}



//========================================================================
//	クラス：m_urdl[_UP] = u;
//	内　容：移動キーをセット
//	引　数：u	: 上キー
//			r	: 右キー
//			d	: 下キー
//			l	: 左キー
//	戻り値：なし
//	 memo ：デフォルトでは[↑][→][↓][←]キー
//========================================================================
void CKeyboardProxy::SetURDL(int u, int r, int d, int l)
{
	
	m_urdl[__UP]	= u;
	m_urdl[__RIGHT]	= r;
	m_urdl[__DOWN]	= d;
	m_urdl[__LEFT]	= l;

}


//========================================================================
//	クラス：CKeyboardProxy
//	内　容：移動量を取得
//	引　数：なし
//	戻り値：傾き
//	 memo ：
//========================================================================
CVector CKeyboardProxy::GetTilt() const
{
	CVector tilt;

	if( m_keyboard->IsPress(m_urdl[__UP]) ) {
		tilt += CVector(0.0f, 1.0f, 0.0f);
	}
	if( m_keyboard->IsPress(m_urdl[__RIGHT]) ) {
		tilt += CVector(1.0f, 0.0f, 0.0f);
	}
	if( m_keyboard->IsPress(m_urdl[__DOWN]) ) {
		tilt += CVector(0.0f, -1.0f, 0.0f); 
	}
	if( m_keyboard->IsPress(m_urdl[__LEFT]) ) {
		tilt += CVector(-1.0f, 0.0f, 0.0f); 
	}

	tilt.Normalize();


	return tilt;
}



//========================================================================
//	クラス：CKeyboardProxy
//	内　容：プレイヤー番号のセット
//	引　数：p	: 番号
//	戻り値：なし
//	 memo ：
//========================================================================
void CKeyboardProxy::SetPlayerNum(int p)
{

	m_ctrl_num = p;

	for(int i = 0; i < CC_SIZE; i++) {
		m_config.insert(std::pair<Command, KEY_NUM>(CC[i].command, CC[i].key_num));
	}

}