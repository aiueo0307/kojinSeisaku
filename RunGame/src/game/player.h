#pragma once

#include"shot.h"
#include"playershot.h"
#include <Dxlib.h>
#define PLAYER_NUM (96)
#define PL_SHOT_MAX (2)	//プレイヤーの弾の最大数
//#define PL_SHOT2_MAX (1)
enum tagState {
	PLAYER_WAIT,
	PLAYER_MOVE,
	PLAYER_JUMP
};
// 方向
enum tagDir {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
//プレイヤーデータを表示するための構造体
typedef struct {
	int m_hndl[PLAYER_NUM];   //画像ハンドル
	int m_phndl;
	int m_shotHndl;
	int m_shot2Hndl;
	int m_slashHndl;
	int m_hp;
	bool m_isActive;
	int m_timecount;	//弾の起爆カウント
	float m_jumpPow;
	bool m_playerJump;
	int m_animCnt;
	int m_shotcooltime;
	int m_slashActiveCount;
	tagState m_state;
	tagDir m_dir;
	VECTOR m_pos;  //画像の位置表示
	//弾1
	SHOT_DATA m_shot[PL_SHOT_MAX];
	SHOT_DATA m_shot_r[PL_SHOT_MAX];
	//弾２
	SHOT2_DATA m_shot2;
	SHOT_DATA m_slash;

}PLAYER_DATA;



//画像の初期化
void IniPlayer();
//画像読込関数
void LoadPlayer();
//画像データの毎フレーム更新処理関数
void TickPlayer();
///画像表示関数
void DrawPlayer();
//終了前に行う必要がある処理関数
void ExitPlayer();

int GetWorldOffsetX();
int GetWorldOffsetY();

void PlayerMove();
void SetLandPlayer();
void SetJumpPlayer();
void WaitExec();

