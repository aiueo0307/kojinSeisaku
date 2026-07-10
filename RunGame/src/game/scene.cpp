#include"scene.h"
#include"scenetitle.h"
#include"scenegame.h"
#include"sceneresult.h"
#include"../lib/fade.h"
#include"sceneclear.h"
#include"player.h"

extern PLAYER_DATA g_player;
enum tagScene
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_CLEAR,

	SCENE_NUM
};


typedef struct
{
	tagScene m_state;
	
} SCENE_DATA;

SCENE_DATA g_scene;

void InitScene()
{
	g_scene.m_state = SCENE_TITLE;

	InitTitle();
	InitGame();
	InitResult();
	InitFade();
	InitClear();

}

int TickScene()
{
	int ret = 0;

	switch (g_scene.m_state)
	{
	case SCENE_TITLE:
		if (TickTitle() == 1)
		{
			g_scene.m_state = SCENE_GAME;
		}
		break;

	case SCENE_GAME:
		/*if (TickGame() != 0)
		{*/
		if (TickGame() != 0)
		{
				g_scene.m_state = SCENE_RESULT;
		}
		
		
		break;

	case SCENE_RESULT:
		if (TickResult() != 0)
		{
			g_scene.m_state = SCENE_TITLE;
		}
		break;
	case SCENE_CLEAR:
		if (TickClear() != 0)
		{
			g_scene.m_state = SCENE_TITLE;
		}
	}

	TickFade();

	return ret;
}

void DrawScene()
{
	switch (g_scene.m_state)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_GAME:
		DrawGame();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;
	case SCENE_CLEAR:
		DrawClear();
		break;

	}

	DrawFade();
}