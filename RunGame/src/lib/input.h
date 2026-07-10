#pragma once
//使用するボタン
#define KEY_JUMP	(0b1)		//上移動
#define KEY_DOWN	(0b10)		//下移動
#define KEY_RIGHT	(0b100)		//右移動
#define KEY_LEFT	(0b1000)	//左移動
#define KEY_SHOT	(0b10000)	//発射
#define KEY_SHOT2	(0b100000)	//発射2
//#define KEY_ULT	(0b1000000)		//ULT

//キー入力初期化
void InitInput();
//キー入力情報更新
void UpdateInput();
//キー入力判定(通常判定)
bool IsInputRep(unsigned int key);
//キー入力(トリガー判定)
bool IsInputTrg(unsigned int key);

