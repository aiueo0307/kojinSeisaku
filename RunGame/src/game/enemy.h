#pragma once
#include<DxLib.h>

#define ENEMY_MAX (3)


//敵データを表示するための構造体
typedef struct {

	VECTOR m_pos;  //画像の位置表示
	int m_shotWait;
	float m_jumpPow;
	bool m_isActive;
}ENEMY_DATA;

//敵を管理するマネージャー構造体
typedef struct {
	ENEMY_DATA m_enemy[ENEMY_MAX];
	int m_hndl;
	int m_waitCount;
}ENEMY_MANAGER;



//===========================

//画像の初期化
void IniEnemy();
//画像読込関数
void LoadEnemy();
//画像データの毎フレーム更新処理関数
void TickEnemy();
///画像表示関数
void DrawEnemy();
//終了前に行う必要がある処理関数
void ExitEnemy();

