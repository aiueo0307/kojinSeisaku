#include"shot.h"
#include<DxLib.h>

//定義関連＝＝＝＝＝＝＝＝＝＝＝＝
#define SHOT_SIZE_X (640.0f) //画像横幅
#define SHOT_SIZE_Y (480.0f) //画像縦幅
#define SHOT_SPEED (8.0)
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//データを表示するための構造体
typedef struct {
	int m_hndl;   //画像ハンドル
	VECTOR m_pos;
}SHOT_DATA;
//上記構造体を実際の変数で
static SHOT_DATA g_shot;


//データの初期化
void IniShot()
{
	g_shot.m_hndl = -1;
	g_shot.m_pos.x = SHOT_SIZE_X * 0.5f;
	g_shot.m_pos.y = SHOT_SIZE_Y * 0.5f;
}
//データ画像読込関数
void LoadShot()
{
	if (g_shot.m_hndl == -1)
	{
		g_shot.m_hndl = LoadGraph("data/graphics/game/SHOT00.jpg");
	}
}

//データの毎フレーム更新処理関数
void TickShot()
{	//画像を毎フレーム下に移動
	g_shot.m_pos.y += SHOT_SPEED;

	//画像が特定の場所よりも下に来たら、画面サイズ分戻してやる
	if (g_shot.m_pos.y >= (SHOT_SIZE_Y * 0.5f) + SHOT_SIZE_Y)
	{//画像一枚分元に戻す
		g_shot.m_pos.y -= SHOT_SIZE_Y;
	}

}
///背景表示関数
void DrawShot() 
{
//2D画像表示
//第一引数：X座標、２：Y座標、３：拡大縮小率、４：回転角度（ラジアン角）
	//５：画像ハンドル、６：透過処理を有効にするか
	DrawRotaGraph((int)g_shot.m_pos.x, (int)g_shot.m_pos.y, 1.0, 0.0, g_shot.m_hndl, TRUE);

	//背景画像二枚目を表示
	DrawRotaGraph((int)g_shot.m_pos.x, (int)(g_shot.m_pos.y - SHOT_SIZE_Y), 1.0, 0.0, g_shot.m_hndl, TRUE);
}

//終了前に行う必要がある処理関数
void ExitShot() 
{
	//ハンドルが-1でなければ、何かしらロードされているはず
	if (g_shot.m_hndl != -1)
	{
		DeleteGraph(g_shot.m_hndl);
		g_shot.m_hndl = -1;
	}
}
