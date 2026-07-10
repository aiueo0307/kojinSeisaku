#include"sceneclear.h"
#include<DxLib.h>
#include"../lib/input.h"
#include"../lib/fade.h"


#define CLEAR_SIZE_X (640.0f)
#define CLEAR_SIZE_Y (480.0f)


enum tagClearScene {
	CLEARSCENE_INIT,	//初期化処理
	CLEARSCENE_LOAD,	//ロード処理
	CLEARSCENE_STARTWAIT,
	CLEARSCENE_MAIN,	//本編
	CLEARSCENE_ENDWAIT,	//終了前演出
	CLEARSCENE_END,		//終了後処理

	CLEARSCENE_NUM	//シーンの数が自動で決まる
};

typedef struct {
	tagClearScene m_state;
	int m_hndl;
}CLEARSCENE_DATA;

CLEARSCENE_DATA g_ClearScene;

void InitClear()
{
	g_ClearScene.m_state = CLEARSCENE_INIT;

}



int TickClear()
{
	switch (g_ClearScene.m_state)
	{
	case CLEARSCENE_INIT:
		//初期化
		g_ClearScene.m_hndl = -1;
		g_ClearScene.m_state = CLEARSCENE_LOAD;
		break;
	case CLEARSCENE_LOAD:
		if (g_ClearScene.m_hndl == -1)
		{
			g_ClearScene.m_hndl = LoadGraph("data/graphics/title/clear.png");
		}
		RequestFadeIn();
		g_ClearScene.m_state = CLEARSCENE_STARTWAIT;
		break;

	case CLEARSCENE_STARTWAIT:
		if (IsEndFadeIn() == true)
		{
			g_ClearScene.m_state = CLEARSCENE_MAIN;
		}



		break;

	case CLEARSCENE_MAIN:
		if (IsInputTrg(KEY_SHOT) == true)
		{
			RequestFadeOut();
			g_ClearScene.m_state = CLEARSCENE_END;
		}
		break;

	case CLEARSCENE_ENDWAIT:
		if (IsEndFadeOut() == true)
		{
			g_ClearScene.m_state = CLEARSCENE_END;
		}
		break;
	case CLEARSCENE_END:
		if (g_ClearScene.m_hndl != -1)
		{
			DeleteGraph(g_ClearScene.m_hndl);
			g_ClearScene.m_hndl = -1;
		}
		g_ClearScene.m_state = CLEARSCENE_INIT;
		return 1;

		break;
	}

	return 0;
}

void DrawClear()
{
	switch (g_ClearScene.m_state)
	{
	case CLEARSCENE_STARTWAIT:
	case CLEARSCENE_MAIN:
	case CLEARSCENE_ENDWAIT:
		DrawRotaGraph((int)(CLEAR_SIZE_X * 0.5f), (int)(CLEAR_SIZE_Y * 0.5f),
			1.0, 0.0, g_ClearScene.m_hndl, TRUE);
		break;
	}

}
