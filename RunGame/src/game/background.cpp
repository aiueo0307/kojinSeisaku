#include"background.h"
#include<DxLib.h>
#include"player.h"

//定義関連＝＝＝＝＝＝＝＝＝＝＝＝
#define BACKGROUND_SIZE_X (640.0f) //画像横幅
#define BACKGROUND_SIZE_Y (480.0f) //画像縦幅
#define MOVE_SPEED (8.0)
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

////背景データを表示するための構造体
//typedef struct {
//	int m_hndl;   //画像ハンドル
//	VECTOR m_pos;  //画像の位置表示
//}BG_DATA;

//上記構造体を実際の変数で
//static BG_DATA g_bg;

//背景データの初期化
void CBackGround::Init()
{
	m_hndl = -1;
	m_pos.x = BACKGROUND_SIZE_X * 0.5f;
	m_pos.y = BACKGROUND_SIZE_Y * 0.5f+ 360;
}
//背景データ画像読込関数
void CBackGround::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph("data/graphics/game/background.jpg");
	}
}

//背景データの毎フレーム更新処理関数 
void CBackGround::Tick()
{	
	if (m_pos.x >= (BACKGROUND_SIZE_X * 0.5f) + BACKGROUND_SIZE_X)
	
	m_pos.x -= BACKGROUND_SIZE_X;

}
///背景表示関数
void CBackGround::Draw()
{
//2D画像表示
//第一引数：X座標、２：Y座標、３：拡大縮小率、４：回転角度（ラジアン角）
	//５：画像ハンドル、６：透過処理を有効にするか
	

			DrawRotaGraph((int)m_pos.x-GetWorldOffsetX(), (int)m_pos.y-GetWorldOffsetY(), 1.0, 0.0, m_hndl, TRUE);

	
}

//終了前に行う必要がある処理関数
void CBackGround::Exit()
{
	//ハンドルが-1でなければ、何かしらロードされているはず
	if (m_hndl != -1)
	{
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
}




