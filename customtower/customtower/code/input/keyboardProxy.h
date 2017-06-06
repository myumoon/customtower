/*-------------------------------------------------------------------------
	説　明：キーボードの設定を反映させるクラス
	作成日：2010/10/01
	更新日：2010/10/14
--------------------------------------------------------------------------*/

#ifndef __KEYBOARDPROXY_H__
#define __KEYBOARDPROXY_H__

#include <map>
#include "general.h"
#include "math/vector.h"
#include "input/keyboard.h"
#include "inputCommand.cpp"



/*----------------------------------*/
/*		キーボード設定クラス		*/
/*	proxy							*/
/*----------------------------------*/
class CKeyboardProxy : public Input {
public:

	//	セット
	//---------------------------------------
	
	/* 初期化 */
	void Init();
	
	/* 終了処理 */
	void Finalize();

	/* 自身のコントローラー番号をセット */
	void SetCtrlNum(int num) { m_ctrl_num = num; }
	
	/* ボタンにコマンドを登録 */
	void SetCommandButtom(int key_num, int cmd);
	
	/* 上右下左キーを設定（デフォルトで↑→↓←） */
	void SetURDL(int u, int r, int d, int l);

	/* プレイヤー番号 */
	void SetPlayerNum(int p);

	//	取得
	//---------------------------------------
	
	/* 入力応答 */
	bool IsPress(Command c);						// 押されているか
	bool IsPressed(Command c);						// 押されたか
	bool IsRelease(Command c);						// 離しているか
	bool IsReleased(Command c);						// 離されたか
	CVector GetTilt() const;						// 移動量を取得


	/* 操作元キーボードの取得 */
	CKeyboard* GetOriginalKeyboard() const { return m_keyboard; }

	//	更新
	//---------------------------------------
	void Update();


private:

	/* 上下左右定数 */
	enum { __UP, __RIGHT, __DOWN, __LEFT, __URDL_MAX };

	//	データ
	//---------------------------------------
	CKeyboard			   *m_keyboard;					// 対応するキーボード
	int					    m_buttom_idx[COMMAND_MAX];	// キーコンフィグ用ボタン配置
	int					    m_urdl[__URDL_MAX];			// 上右下左ボタン
	int						m_ctrl_num;					// コントロール番号
	std::map<Command, KEY_NUM>	m_config;				// キー設定

public:
	 CKeyboardProxy();
	~CKeyboardProxy();

};





#endif  // __KEYBOARDPROXY_H__