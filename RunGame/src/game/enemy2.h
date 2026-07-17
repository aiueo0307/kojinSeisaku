#pragma once
#include<DxLib.h>

#define ENEMY2_MAX (2)

//===========================敵２
//敵データを表示するための構造体
typedef struct {

	VECTOR m_pos;  //画像の位置表示
	int m_shotWait;
	bool m_isActive;
}ENEMY2_DATA;


//敵を管理するマネージャー構造体
typedef struct {
	ENEMY2_DATA m_enemy[ENEMY2_MAX];
	int m_hndl;
	int m_waitCount;
}ENEMY2_MANAGER;


//画像の初期化
void IniEnemy2();
//画像読込関数
void LoadEnemy2();
//画像データの毎フレーム更新処理関数
void TickEnemy2();
///画像表示関数
void DrawEnemy2();
//終了前に行う必要がある処理関数
void ExitEnemy2();
