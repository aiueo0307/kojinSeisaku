#include"enemy.h"
#include"enemyshot.h"
#include<DxLib.h>
#include"../lib/input.h"
#include"player.h"
#include"common.h"
#include"score.h"

//定義関連＝＝＝＝＝＝＝＝＝＝＝＝
#define Enemy_SIZE_X (60.0f) 
#define Enemy_SIZE_Y (60.0f) 
#define ENEMY_SPEED (1.0)
#define ENEMY_COUNT (360)	//敵再出現までにかかる時間
#define SHOT_WAIT_COUNT (60) //敵が弾を撃つまでの時間



//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//構造体を実際の変数で
ENEMY_MANAGER g_enemyManager;
extern PLAYER_DATA g_player;

CScore score;

//敵データの初期化
void IniEnemy()
{//enemy用
	g_enemyManager.m_hndl = -1;
	g_enemyManager.m_waitCount = ENEMY_COUNT;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_enemyManager.m_enemy[i].m_pos.x = 0.0f;
		g_enemyManager.m_enemy[i].m_pos.y = 0.0f;
		g_enemyManager.m_enemy[i].m_isActive = false;
	}

}



//敵データ画像読込関数
void LoadEnemy()
{
	if (g_enemyManager.m_hndl == -1)
	{
		g_enemyManager.m_hndl = LoadGraph("data/graphics/game/enemy00.png");

	}

	
}

//敵データの毎フレーム更新処理関数
void TickEnemy()
{
	bool isAppear = false;
	//敵移動処理
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_enemyManager.m_enemy[i].m_isActive == false) continue;

		//g_enemyManager.m_enemy[i].m_pos.y += ENEMY_SPEED;
		/*if (g_enemyManager.m_enemy[i].m_pos.y > 500.f)
		{
			g_enemyManager.m_enemy[i].m_isActive = false;
		}
		else
		{
			isAppear = true;
		}*/

		//プレイヤーに向かって歩く
		
			if (g_player.m_pos.x <= g_enemyManager.m_enemy[i].m_pos.x)
			{
				g_enemyManager.m_enemy[i].m_pos.x -= ENEMY_SPEED;
			}
			if (g_player.m_pos.x >= g_enemyManager.m_enemy[i].m_pos.x)
			{
				g_enemyManager.m_enemy[i].m_pos.x += ENEMY_SPEED * 1.5;
			}
		

		//重力
		/*g_enemyManager.m_enemy[i].m_jumpPow -= GRAVITY;
		g_enemyManager.m_enemy[i].m_pos.y -= g_enemyManager.m_enemy[i].m_jumpPow;*/
		// 当たり判定がない間だけ使用する
		if (g_enemyManager.m_enemy[i].m_pos.y >= WINDOW_SIZE_Y)
		{
			g_enemyManager.m_enemy[i].m_pos.y = WINDOW_SIZE_Y;

		}


		//弾の発射管理＝＝＝＝＝＝＝＝＝＝
		//弾出さない
		/*g_enemyManager.m_enemy[i].m_shotWait--;
		if (g_enemyManager.m_enemy[i].m_shotWait <= 0)
		{
			RequestEnemyShot(g_enemyManager.m_enemy[i].m_pos);

			g_enemyManager.m_enemy[i].m_shotWait = SHOT_WAIT_COUNT;
		}*/

		//おいてかれた敵は消す
		if (g_enemyManager.m_enemy[i].m_pos.x <= g_player.m_pos.x - WINDOW_SIZE_X)
		{
			g_enemyManager.m_enemy[i].m_isActive = false;
		}

	}
	

		//出現カウント

		g_enemyManager.m_waitCount--;

		if (g_enemyManager.m_waitCount <= 0 || isAppear == false)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (g_enemyManager.m_enemy[i].m_isActive == true)
				{
					continue;
				}
				//敵データ初期化
				g_enemyManager.m_enemy[i].m_isActive = true;
				int rand;
				rand = GetRand(2);
				if (rand >= 1)
				{
					g_enemyManager.m_enemy[i].m_pos.x = (float)g_player.m_pos.x + WINDOW_SIZE_X * 0.5f + 32.0f + GetRand(240);
				}
				else
				{
					g_enemyManager.m_enemy[i].m_pos.x = (float)g_player.m_pos.x - WINDOW_SIZE_X * 0.5f - 32.0f;
			
				}
				int rand2=0;
				rand = GetRand(2);
				if (rand2 == 0)
				{
					g_enemyManager.m_enemy[i].m_pos.y = 700.0f;
				}
				if (rand2 == 1)
				{
					g_enemyManager.m_enemy[i].m_pos.y = 640.0f;
				}

				g_enemyManager.m_enemy[i].m_shotWait = SHOT_WAIT_COUNT;
				//待機カウント再設定
				g_enemyManager.m_waitCount = ENEMY_COUNT;
				//出現させたら終了
				break;
			}
		}


		//全敵即死
		/*if (IsInputRep(KEY_ULT) == true)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				g_enemyManager.m_enemy[i].m_isActive = false;
			}

		}*/

	
}
///敵表示関数
void DrawEnemy()
{
	//敵画像表示
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_enemyManager.m_enemy[i].m_isActive == true)
		{
			DrawRotaGraph((int)g_enemyManager.m_enemy[i].m_pos.x-GetWorldOffsetX(), (int)g_enemyManager.m_enemy[i].m_pos.y-GetWorldOffsetY(),
				1.0, 0.0, g_enemyManager.m_hndl, TRUE);
		}
	}

}

//終了前に行う必要がある処理関数
void ExitEnemy()
{
	//敵の画像破棄
	if (g_enemyManager.m_hndl != -1)
	{
		DeleteGraph(g_enemyManager.m_hndl);
		g_enemyManager.m_hndl = -1;
	}
	
}
