
#include"soundmanager.h"
#include<DxLib.h>

//定義

static const char* SOUND_PATH[SOUND_NUM] = {
	"data/sound/title.mp3",
	"data/sound/bgm00.mp3",
	"data/sound/se_explore.mp3",
};

SOUND_MANAGER g_soundManager;



//初期化
void InitSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		g_soundManager.m_hndl[i] = -1;
	}
}

//画像読込関数
void LoadSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{


		if (g_soundManager.m_hndl[i] == -1)
		{
			g_soundManager.m_hndl[i] = LoadSoundMem(SOUND_PATH[i]);
		}
	}
}
//終了前に行う必要がある処理関数
void ExitSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		if (g_soundManager.m_hndl[i] != -1)
		{
			DeleteGraph(g_soundManager.m_hndl[i]);
			g_soundManager.m_hndl[i] = -1;
		}
	}
}

void RequestSound(int soundID,int type)
{
	PlaySoundMem(g_soundManager.m_hndl[soundID], type);

}


//音の停止要請
void StopSound(int stopID)
{
	StopSoundMem(g_soundManager.m_hndl[stopID]);
}
//全ての音の停止要請
void StopAllSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		StopSound(i);
	}
}
