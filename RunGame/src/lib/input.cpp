#include "input.h"
#include<DxLib.h>

//キーボード入力用構造体
typedef struct {
	unsigned int m_nowKey;
	unsigned int m_PrevKey;
}INPUT_DATA;

//キー入力用にグローバル変数を作成
static INPUT_DATA g_inputData;


//キー入力初期化
void InitInput()
{
	g_inputData.m_nowKey = g_inputData.m_PrevKey = 0;
}
//キー入力情報更新
void UpdateInput()
{
	//前回の入力情報を最新に更新
	g_inputData.m_PrevKey = g_inputData.m_nowKey;
	//今回の入力情報をいったん０にする
	g_inputData.m_nowKey = 0;

	//上キー情報取得
	if (CheckHitKey(KEY_INPUT_W))g_inputData.m_nowKey |= KEY_JUMP;
	//下キー情報取得
	if (CheckHitKey(KEY_INPUT_S))g_inputData.m_nowKey |= KEY_DOWN;
	//右キー情報取得
	if (CheckHitKey(KEY_INPUT_D))g_inputData.m_nowKey |= KEY_RIGHT;
	//左キー情報取得
	if (CheckHitKey(KEY_INPUT_A))g_inputData.m_nowKey |= KEY_LEFT;
	//ショットキー情報取得
	if (CheckHitKey(KEY_INPUT_SPACE))g_inputData.m_nowKey |= KEY_SHOT;
	//ショット２取得
	if (CheckHitKey(KEY_INPUT_Q))g_inputData.m_nowKey |= KEY_SHOT2;
	//ULTキー情報取得
	//if (CheckHitKey(KEY_INPUT_W))g_inputData.m_nowKey |= KEY_ULT;




}
//キー入力判定(通常判定)
bool IsInputRep(unsigned int key)
{
	if ((g_inputData.m_nowKey & key) != 0)
	{
		return true;
	}
	else {
		return false;
	}
}
//キー入力(トリガー判定)
bool IsInputTrg(unsigned int key)
{
	if ((g_inputData.m_nowKey & key) &&
		!(g_inputData.m_PrevKey & key)) return 1;
	else return 0;
}
