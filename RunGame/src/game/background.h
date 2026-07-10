#pragma once
#include <DxLib.h>

class CBackGround
{
private:
	int m_hndl;   //画像ハンドル
	VECTOR m_pos;  //画像の位置表示

public:
//背景データの初期化
void Init();
//背景データ画像読込関数
void Load();
//背景データの毎フレーム更新処理関数
void Tick();
///背景表示関数
void Draw();
//終了前に行う必要がある処理関数
void Exit();
};
