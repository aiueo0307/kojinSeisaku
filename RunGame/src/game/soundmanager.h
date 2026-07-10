#pragma once
#include <DXlib.h>

enum tagSound {
	BGMID_TITLE,	//タイトル画面のBGM
	BGM_GAME,		//ゲーム本編のBGM
	SEID_EXPLOSION,	//爆発効果音

	SOUND_NUM		//BGM,SEの総数
};


typedef struct {
	int m_hndl[SOUND_NUM];
}SOUND_MANAGER;

//初期化
void InitSound();
//読込関数
void LoadSound();
//終了前に行う必要がある処理関数
void ExitSound();
//音の再生要請
void RequestSound(int soundID, int type);
//音の停止要請
void StopSound(int stopID);
//全ての音の停止要請
void StopAllSound();
