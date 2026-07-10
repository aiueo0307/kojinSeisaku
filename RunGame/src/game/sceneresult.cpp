#include"sceneresult.h"
#include<DxLib.h>
#include"../lib/input.h"
#include"../lib/fade.h"


#define RESULT_SIZE_X (640.0f)
#define RESULT_SIZE_Y (480.0f)


enum tagResultScene {
	RESULTSCENE_INIT,	//初期化処理
	RESULTSCENE_LOAD,	//ロード処理
	RESULTSCENE_STARTWAIT,
	RESULTSCENE_MAIN,	//本編
	RESULTSCENE_ENDWAIT,	//終了前演出
	RESULTSCENE_END,		//終了後処理

	RESULTSCENE_NUM	//シーンの数が自動で決まる
};

typedef struct {
	tagResultScene m_state;
	int m_hndl;
}RESULTSCENE_DATA;

RESULTSCENE_DATA g_ResultScene;

void InitResult()
{
	g_ResultScene.m_state = RESULTSCENE_INIT;

}



int TickResult()
{
	switch (g_ResultScene.m_state)
	{
	case RESULTSCENE_INIT:
		//初期化
		g_ResultScene.m_hndl = -1;
		g_ResultScene.m_state = RESULTSCENE_LOAD;
		break;
	case RESULTSCENE_LOAD:
		if (g_ResultScene.m_hndl == -1)
		{
			g_ResultScene.m_hndl = LoadGraph("data/graphics/title/result.jpg");
		}
		RequestFadeIn();
		g_ResultScene.m_state = RESULTSCENE_STARTWAIT;
		break;

	case RESULTSCENE_STARTWAIT:
		if (IsEndFadeIn() == true)
		{
			g_ResultScene.m_state = RESULTSCENE_MAIN;
		}



		break;

	case RESULTSCENE_MAIN:
		if (IsInputTrg(KEY_SHOT) == true)
		{
			RequestFadeOut();
			g_ResultScene.m_state = RESULTSCENE_END;
		}
		break;

	case RESULTSCENE_ENDWAIT:
		if(IsEndFadeOut()==true)
		{
			g_ResultScene.m_state = RESULTSCENE_END;
		}
		break;
	case RESULTSCENE_END:
		if (g_ResultScene.m_hndl != -1)
		{
			DeleteGraph(g_ResultScene.m_hndl);
			g_ResultScene.m_hndl = -1;
		}
		g_ResultScene.m_state = RESULTSCENE_INIT;
		return 1;

		break;
	}

	return 0;
}

void DrawResult()
{
	switch (g_ResultScene.m_state)
	{
	case RESULTSCENE_STARTWAIT:
	case RESULTSCENE_MAIN:
	case RESULTSCENE_ENDWAIT:
		DrawRotaGraph((int)(RESULT_SIZE_X * 0.5f), (int)(RESULT_SIZE_Y * 0.5f),
			1.0, 0.0, g_ResultScene.m_hndl, TRUE);
		break;
	}

}
