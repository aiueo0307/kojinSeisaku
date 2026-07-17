#include "scenegame.h"
#include"background.h"
#include"score.h"
#include"player.h"
#include"../lib/fade.h"
#include"stage.h"
#include"hitcheck.h"

#define END_WAIT (60)

extern PLAYER_DATA g_player;
CBackGround g_bg;
CScore g_score;

//ゲームの流れを一つずつ設定
enum tagGameScene {
	GAMESCENE_INIT,	//初期化処理
	GAMESCENE_LOAD,	//ロード処理
	GAMESCENE_STARTWAIT,
	GAMESCENE_MAIN,	//ゲーム本編
	GAMESCENE_ENDWAIT,	//終了前演出
	GAMESCENE_END,//終了後処理
	GMANESCENE_CLEAR,
	GAMESCENE_SESULT,

	GAMESCENE_NUM	//シーンの数が自動で決まる
};

typedef struct {
	tagGameScene m_state;
	int m_endWaitCount;
}GAMESCENE_DATA;

GAMESCENE_DATA g_gameScene;

//変数周りの初期化
void InitGame()
{
	g_gameScene.m_state = GAMESCENE_INIT;

}
//ゲームの全体の処理管理
//　@return :
int TickGame() 
{
	switch (g_gameScene.m_state)
	{
	case GAMESCENE_INIT:

		g_bg.Init();
		IniPlayer();
		g_score.Init();
		InitStage();
		g_gameScene.m_state = GAMESCENE_LOAD;
			break;
	
	case GAMESCENE_LOAD:
		g_bg.Load();
		LoadPlayer();
		g_score.Load();
		LoadStage();
		g_gameScene.m_state = GAMESCENE_STARTWAIT;
			break;

	case GAMESCENE_STARTWAIT:
		if (IsEndFadeIn() == true)
		{
			g_gameScene.m_state = GAMESCENE_MAIN;
		}
		break;
	case GAMESCENE_MAIN:
		g_bg.Tick();
		TickPlayer();
		g_score.Tick();


		HitCheckPlayerToStage();

		if (g_player.m_pos.y >= 1280)
		{
			g_gameScene.m_endWaitCount = 60;
			g_gameScene.m_state = GAMESCENE_ENDWAIT;
		}

		/*{
			g_gameScene.m_endWaitCount = 60;
			g_gameScene.m_state = GAMESCENE_ENDWAIT;
		}*/

		//if ()
		//{
		//	g_gameScene.m_state = GMANESCENE_CLEAR;
		//}
		break;
	case GAMESCENE_ENDWAIT:

		g_gameScene.m_endWaitCount--;
		if (g_gameScene.m_endWaitCount <= 0)
		{
			g_gameScene.m_state = GAMESCENE_END;
		}
		break;
	case GAMESCENE_END:
		g_bg.Exit();
		ExitPlayer();
		g_score.Exit();
		ExitStage();
		g_gameScene.m_state = GAMESCENE_INIT;
		
			return 1;
		
		
		break;
	}


	return 0;
}
//ゲーム全体の描画管理
void DrawGame()
{
	switch (g_gameScene.m_state)
	{
		
		case GAMESCENE_MAIN:
		case GAMESCENE_ENDWAIT:
			g_bg.Draw();
			DrawPlayer();
			g_score.Draw();
			DrawStage();
			break;
	}
}
