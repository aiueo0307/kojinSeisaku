#pragma once
#include <DXlib.h>

#define ENEMY_SHOT_MAX (50)


typedef struct {
	VECTOR m_pos;
	VECTOR m_speed;
	bool m_isActive;
}ENEMYSHOT_DATA;

typedef struct {
	ENEMYSHOT_DATA m_shot[ENEMY_SHOT_MAX];
	int m_hndl;
}ENEMYSHOT_MANAGER;

//画像の初期化
void IniEnemyShot();
//画像読込関数
void LoadEnemyShot();
//画像データの毎フレーム更新処理関数
void TickEnemyShot();
///画像表示関数
void DrawEnemyShot();
//終了前に行う必要がある処理関数
void ExitEnemyShot();
//敵の弾発射
//@pos:弾の発射位置
void RequestEnemyShot(VECTOR pos);
