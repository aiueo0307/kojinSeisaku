#pragma once

#include"DxLib.h"
// 定義関連-------------------------------------------
#define STAGE_WIDTH		(128)	// ステージの横に敷き詰められるマップチップの数
#define STAGE_HEIGHT	(40)	// ステージの縦に敷き詰められるマップチップの数
#define MAP_CHIP_SIZE_X	(32)// マップチップ一枚の縦横サイズ
#define MAP_CHIP_SIZE_Y	(32)
#define MAP_CHIP_X		(30)		// マップチップの画像枚数(横)
#define MAP_CHIP_Y		(16)	// マップチップの画像枚数(縦)

// ステージオブジェクト構造体
typedef struct {
	VECTOR m_pos;	// 座標
	int m_state;	// ステージデータ　0=床・壁　　-1=何もなし
}OBJECT_DATA;


// マップのデータを管理する構造体
typedef struct {
	OBJECT_DATA m_stageData[STAGE_HEIGHT][STAGE_WIDTH];
	//int m_mapData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_hndl[MAP_CHIP_X * MAP_CHIP_Y];
	int m_state;
}STAGE_DATA;

enum tagStageID {
	STAGEID_BLOCK,		// 床・壁

	STAGEID_NUM
};

void InitStage();
void LoadStage();
void DrawStage();
void ExitStage();
