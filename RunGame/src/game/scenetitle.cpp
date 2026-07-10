#include"scenetitle.h"
#include<DxLib.h>
#include"../lib/input.h"
#include"../lib/fade.h"


#define TITLE_SIZE_X (640.0f)
#define TITLE_SIZE_Y (480.0f)





enum tagTitleScene {
	TITLESCENE_INIT,	//初期化処理
	TITLESCENE_LOAD,	//ロード処理
	TITLESCENE_STARTWAIT,
	TITLESCENE_MAIN,	//本編
	TITLESCENE_ENDWAIT,	//終了前演出
	TITLESCENE_END,		//終了後処理

	TITLESCENE_NUM	//シーンの数が自動で決まる
};

typedef struct {
	tagTitleScene m_state;
	int m_hndl;
}TITLESCENE_DATA;

TITLESCENE_DATA g_TitleScene;

void InitTitle()
{
	g_TitleScene.m_state = TITLESCENE_INIT;

}



int TickTitle()
{
	switch(g_TitleScene.m_state)
	{ 
		case TITLESCENE_INIT:
			//初期化
			g_TitleScene.m_hndl = -1;
			g_TitleScene.m_state = TITLESCENE_LOAD;
			break;
		case TITLESCENE_LOAD:
			if (g_TitleScene.m_hndl == -1)
			{
				//g_TitleScene.m_hndl = LoadGraph("data/graphics/title/title.jpg");
				
			}
			RequestFadeIn();

			
			g_TitleScene.m_state = TITLESCENE_MAIN;
			break;

		case TITLESCENE_MAIN:
			if (IsInputTrg(KEY_SHOT) == true)
			{
				g_TitleScene.m_state = TITLESCENE_END;
			}
			break;

		case TITLESCENE_ENDWAIT:
	
			break;
		case TITLESCENE_END:
			if (g_TitleScene.m_hndl != -1)
			{
				DeleteGraph(g_TitleScene.m_hndl);
					g_TitleScene.m_hndl = -1;
			}
			g_TitleScene.m_state = TITLESCENE_INIT;
			return 1;

			break;
	}

	return 0;
}

void DrawTitle()
{
	switch (g_TitleScene.m_state)
	{
	case TITLESCENE_STARTWAIT:
	case TITLESCENE_MAIN:
	case TITLESCENE_ENDWAIT:
		DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
			1.0, 0.0, g_TitleScene.m_hndl, TRUE);
		break;
	}

}
