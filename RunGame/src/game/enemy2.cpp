#include "enemy2.h"
#include"../lib/input.h"
#include"common.h"
#include "player.h"
#define Enemy2_SIZE_Y (60.0f) 
#define ENEMY2_SPEED (4.0)
#define ENEMY2_SPEEDY (2.0)
#define ENEMY2_COUNT (60)	//敵再出現までにかかる時間

ENEMY2_MANAGER g_enemy2Manager;

extern PLAYER_DATA g_player;

void IniEnemy2()
{
	//enemy2用
	g_enemy2Manager.m_hndl = -1;
	g_enemy2Manager.m_waitCount = 0;
	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		g_enemy2Manager.m_enemy[i].m_pos.x = 0.0f;
		g_enemy2Manager.m_enemy[i].m_pos.y = 0.0f;
		g_enemy2Manager.m_enemy[i].m_isActive = false;
	}

}

void LoadEnemy2()
{
	if (g_enemy2Manager.m_hndl == -1)
	{
		g_enemy2Manager.m_hndl = LoadGraph("data/graphics/game/enemy00.png");

	}

}

void TickEnemy2()
{
	bool isAppear = false;
	//敵移動処理
	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		//if (g_enemy2Manager.m_enemy[i].m_isActive == false) continue;


		g_enemy2Manager.m_enemy[i].m_pos.x += ENEMY2_SPEED;
		g_enemy2Manager.m_enemy[i].m_pos.y += ENEMY2_SPEEDY;
		if (g_enemy2Manager.m_enemy[i].m_pos.y>1000)
		{
			g_enemy2Manager.m_enemy[i].m_isActive = false;
		}
		else
		{
			isAppear = true;
		}

		if (g_enemy2Manager.m_enemy[i].m_pos.x <= g_player.m_pos.x - WINDOW_SIZE_X)
		{
			g_enemy2Manager.m_enemy[i].m_isActive = false;
		}

		g_enemy2Manager.m_waitCount--;

		if (g_enemy2Manager.m_waitCount <= 0 || isAppear == false)
		{
			for (int i = 0; i < ENEMY2_MAX; i++)
			{
				if (g_enemy2Manager.m_enemy[i].m_isActive == true)
				{
					continue;
				}

				//敵データ初期化
				g_enemy2Manager.m_enemy[i].m_isActive = true;
				g_enemy2Manager.m_enemy[i].m_pos.x = -20.0f;
				g_enemy2Manager.m_enemy[i].m_pos.y = (float)(GetRand(480));
				//待機カウント再設定
				g_enemy2Manager.m_waitCount = ENEMY2_COUNT;
				//出現させたら終了
				break;
			}
		}
	}

	//全敵即死
	/*if (IsInputRep(KEY_ULT) == true)
	{
		for (int i = 0; i < ENEMY2_MAX; i++)
		{
			g_enemy2Manager.m_enemy[i].m_isActive = false;
		}
	}*/

}

void DrawEnemy2()
{
	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		if (g_enemy2Manager.m_enemy[i].m_isActive == true)
		{
				DrawRotaGraph((int)g_enemy2Manager.m_enemy[i].m_pos.x - GetWorldOffsetX(), (int)g_enemy2Manager.m_enemy[i].m_pos.y - GetWorldOffsetY(),
					1.0, 0.0, g_enemy2Manager.m_hndl, TRUE);
		}
	}

}


void ExitEnemy2()
{
	if (g_enemy2Manager.m_hndl != -1)
	{
		DeleteGraph(g_enemy2Manager.m_hndl);
		g_enemy2Manager.m_hndl = -1;
	}
}
	

