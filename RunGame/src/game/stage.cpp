
#include "stage.h"
#include <DxLib.h>
#include "player.h"

// 画像のファイルパス
#define MAP_CHIP_PATH ("data/graphics/game/map1.png")
// マップデータのファイルパス
#define MAP_DATA_PATH ("data/stage/stage.csv")


STAGE_DATA g_stageData;

extern PLAYER_DATA g_playerData;

void InitStage(void)
{
	for (int i = 0; i < MAP_CHIP_X * MAP_CHIP_Y; i++)
	{
		g_stageData.m_hndl[i] = -1;
	}

	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			g_stageData.m_stageData[y][x].m_pos.x = MAP_CHIP_SIZE_X / 2 + x * MAP_CHIP_SIZE_X;
			g_stageData.m_stageData[y][x].m_pos.y = MAP_CHIP_SIZE_Y / 2 + y * MAP_CHIP_SIZE_Y;
		}
	}
}

void LoadStage(void)
{
	int ret = LoadDivGraph(MAP_CHIP_PATH, MAP_CHIP_X * MAP_CHIP_Y,
		MAP_CHIP_X, MAP_CHIP_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, g_stageData.m_hndl);

	FILE* fp;
	if (fopen_s(&fp, MAP_DATA_PATH, "r") != 0)
		return;

	
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			char c;
			c = fgetc(fp);
			if (c == ',' || c == '\n')
			{
				g_stageData.m_stageData[y][x].m_state = -1;
			}
			else
			{
				fseek(fp, -1, SEEK_CUR);
				fscanf_s(fp, "%d", &g_stageData.m_stageData[y][x].m_state);
				fgetc(fp);
			}
			
		}
	}


	fclose(fp);
}


void DrawStage(void)
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			int id = g_stageData.m_stageData[y][x].m_state;
			if (id == -1) continue;
			DrawRotaGraph(g_stageData.m_stageData[y][x].m_pos.x - GetWorldOffsetX(),
				g_stageData.m_stageData[y][x].m_pos.y - GetWorldOffsetY(),
				1.0, 0.0, g_stageData.m_hndl[id], TRUE);
		}
	}
}


void ExitStage(void)
{
	for (int i = 0; i < MAP_CHIP_X * MAP_CHIP_Y; i++)
	{
		if (g_stageData.m_hndl[i] != -1)
		{
			DeleteGraph(g_stageData.m_hndl[i]);
			g_stageData.m_hndl[i] = -1;
		}
	}
}