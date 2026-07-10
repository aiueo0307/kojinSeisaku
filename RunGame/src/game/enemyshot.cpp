
#include"enemyshot.h"
#include"player.h"
#include<math.h>
#include"common.h"
//定義
#define ENEMY_SHOT_SPEED (5.0f)	//弾の移動速度
#define SHOT_SIZE (8.0f)	//弾の大きさ

//グローバル変数
ENEMYSHOT_MANAGER g_enemyShotManager;

extern PLAYER_DATA g_player;


//画像の初期化
void IniEnemyShot()
{
	g_enemyShotManager.m_hndl = -1;

	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{
		g_enemyShotManager.m_shot[i].m_isActive = false;
		g_enemyShotManager.m_shot[i].m_pos = { 0.0f,0.0f,0.0f };
		g_enemyShotManager.m_shot[i].m_speed = { 0.0f,0.0f,0.0f };
	}


}
//画像読込関数
void LoadEnemyShot()
{
	if (g_enemyShotManager.m_hndl == -1)
	{
		g_enemyShotManager.m_hndl = LoadGraph("data/graphics/game/shot01.PNG");
	}
}
//画像データの毎フレーム更新処理関数
void TickEnemyShot()
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{
		if (g_enemyShotManager.m_shot[i].m_isActive == false)
		{
			continue;
		}
		//速度を加算
		g_enemyShotManager.m_shot[i].m_pos
			= VAdd(g_enemyShotManager.m_shot[i].m_pos,
				g_enemyShotManager.m_shot[i].m_speed);

		/*if (g_enemyShotManager.m_shot[i].m_pos.x < 0.0f
			|| g_enemyShotManager.m_shot[i].m_pos.x>640.0f
			|| g_enemyShotManager.m_shot[i].m_pos.y < 0.0f
			|| g_enemyShotManager.m_shot[i].m_pos.y>640.0f)
		{
			g_enemyShotManager.m_shot[i].m_isActive = false;
		}*/


			if (g_player.m_pos.x + WINDOW_SIZE_X * 0.5f < g_enemyShotManager.m_shot[i].m_pos.x||
				g_player.m_pos.x - WINDOW_SIZE_X * 0.5f > g_enemyShotManager.m_shot[i].m_pos.x)
			{
				g_enemyShotManager.m_shot[i].m_isActive = false;
			}
	}
}
///画像表示関数
void DrawEnemyShot()
{
	//弾の画像表示
	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{
		if (g_enemyShotManager.m_shot[i].m_isActive == false)
		{
			continue;
		}

		DrawRotaGraph((int)g_enemyShotManager.m_shot[i].m_pos.x-GetWorldOffsetX(), (int)g_enemyShotManager.m_shot[i].m_pos.y-GetWorldOffsetY(),
			1.0, 0.0, g_enemyShotManager.m_hndl, TRUE);
	}
	
}
//終了前に行う必要がある処理関数
void ExitEnemyShot()
{
	if (g_enemyShotManager.m_hndl != -1)
	{
		DeleteGraph(g_enemyShotManager.m_hndl);
		g_enemyShotManager.m_hndl = -1;
	}
}
//敵の弾発射
//@pos:弾の発射位置
void RequestEnemyShot(VECTOR pos)
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{
		if (g_enemyShotManager.m_shot[i].m_isActive == true)
		{
			continue;
		}

		g_enemyShotManager.m_shot[i].m_isActive = true;
		g_enemyShotManager.m_shot[i].m_pos = pos;
		//発射するキャラとプレイヤーの位置を使い
		//方向ベクトルを計算
		VECTOR dir;
		dir.x = g_player.m_pos.x - pos.x;
		dir.y = g_player.m_pos.y - pos.y;
		dir.z = 0.0f;

		float len = dir.x * dir.x + dir.y * dir.y;
		len = sqrtf(len);

		dir.x = dir.x / len;
		dir.y = dir.y / len;

		//速度調整
		dir.x = dir.x * ENEMY_SHOT_SPEED;
		dir.y = dir.y * ENEMY_SHOT_SPEED;



		//計算結果を速度にセット
		g_enemyShotManager.m_shot[i].m_speed = dir;



		break;
	}

}