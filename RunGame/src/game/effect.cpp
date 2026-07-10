#include"background.h"
#include<DxLib.h>
#include"player.h"
//定義関連＝＝＝＝＝＝＝＝＝＝＝＝
#define ANIM_NUM	(10)	//画像枚数
#define ANIM_SPEED	(0.25f)	//アニメーション速度
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//爆発データを表示するための構造体

typedef struct {
	int m_hndl[ANIM_NUM];   //画像ハンドル
	VECTOR m_pos;  //画像の位置表示
	float m_animCount;	//時間カウント
	bool m_isActive;	//表示フラグ
	int m_hp;
}EXPLOSION_DATA;

//上記構造体を実際の変数で
static EXPLOSION_DATA g_explosion;

//爆発データの初期化
void InitExplosion()
{
	for (int i = 0; i < ANIM_NUM; i++)
	{
		g_explosion.m_hndl[i] = -1;

	}
	
	g_explosion.m_pos = { 0.0f,0.0f,0.0f };
	g_explosion.m_animCount = 0.0f;
	g_explosion.m_isActive = false;
}
//爆発データ画像読込関数
void LoadExplosion()
{
	int success = -1;
	if (g_explosion.m_hndl[0] == -1)
	
	{
		success = LoadDivGraph("data/graphics/game/effect_explosion00.png",ANIM_NUM,ANIM_NUM,1,180,180,g_explosion.m_hndl);
	}
}

//爆発データの毎フレーム更新処理関数
void TickExplosion()
{	
	//フラグがオフなら終了
	if (g_explosion.m_isActive == false)return;
	//アニメーションの時間をカウント
	g_explosion.m_animCount += ANIM_SPEED;


	g_explosion.m_animCount += ANIM_SPEED;

	if (g_explosion.m_animCount >= ANIM_NUM)
	{
		g_explosion.m_isActive = false;
	}
	
}
///爆発表示関数
void DrawExplosion() 
{
	
	if (g_explosion.m_isActive == true)
	{
		int nowHndl = g_explosion.m_hndl[(int)g_explosion.m_animCount];
			DrawRotaGraph((int)g_explosion.m_pos.x-GetWorldOffsetX(), (int)g_explosion.m_pos.y-GetWorldOffsetY(), 1.0, 0.0, nowHndl, TRUE);
	}
	
}

//終了前に行う必要がある処理関数
void ExitExplosion() 
{
	//ハンドルが-1でなければ、何かしらロードされているはず
	if (g_explosion.m_hndl[0] != -1)
	{
		for (int i=0;i<ANIM_NUM;i++)
		{
			DeleteGraph(g_explosion.m_hndl[i]);
			g_explosion.m_hndl[i] = -1;
		}
		
	}
}

void RequestExplosion(VECTOR pos)
{
	g_explosion.m_isActive = true;
	g_explosion.m_pos = pos;
	g_explosion.m_animCount = 0.0f;
}