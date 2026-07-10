#include"item.h"
#include<math.h>
#include "player.h"


ITEM_MANAGER g_itemManager;

extern PLAYER_DATA g_player;

void InitItem()
{//item—p
	g_itemManager.m_hndl = -1;
	g_itemManager.m_waitCount = 0;
	for (int i = 0; i < ITEM_MAX; i++)
	{
		g_itemManager.m_item[i].m_pos.x = 0.0f;
		g_itemManager.m_item[i].m_pos.y = 0.0f;
		g_itemManager.m_item[i].m_isActive = true;
		g_itemManager.m_item[i].m_speed;
	}
}

void LoadItem()
{
	if (g_itemManager.m_hndl == -1)
	{
		//g_itemManager.m_hndl = LoadGraph("data/graphics/game/player.png");

	}
}

void TickItem()
{

	/*bool isAppear = false;*/

	
	for (int i = 0; i < ITEM_MAX; i++)
	{
		/*if (g_player.m_pos - g_itemManager.m_item[i].m_pos ==true)*/


		if (g_itemManager.m_item[i].m_isActive == false)
		{
			continue;
		}
		//‘¬“x‚ð‰ÁŽZ
		g_itemManager.m_item[i].m_pos
			= VAdd(g_itemManager.m_item[i].m_pos,
				//‚±‚±‚É‰ÁŽZ‚·‚é’l);
				g_itemManager.m_item[i].m_speed);
	}

}


void DrawItem()
{
	//“G‰æ‘œ•\Ž¦
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_itemManager.m_item[i].m_isActive == true)
		{
			DrawRotaGraph((int)g_itemManager.m_item[i].m_pos.x, (int)g_itemManager.m_item[i].m_pos.y,
				1.0, 0.0, g_itemManager.m_hndl, TRUE);
		}
	}
}

void ExitItem()
{
	//“G‚Ì‰æ‘œ”jŠü
	if (g_itemManager.m_hndl != -1)
	{
		DeleteGraph(g_itemManager.m_hndl);
		g_itemManager.m_hndl = -1;
	}
}