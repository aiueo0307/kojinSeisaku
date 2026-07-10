#pragma once
#include<DxLib.h>

#define ITEM_MAX (1)

void InitItem();
void LoadItem();
void TickItem();
void DrawItem();
void ExitItem();

//アイテムデータを表示するための構造体
typedef struct {

	VECTOR m_pos;  //画像の位置表示
	int m_shotWait;
	bool m_isActive;
	VECTOR m_speed;
}ITEM_DATA;

//アイテムを管理するマネージャー構造体
typedef struct {
	ITEM_DATA m_item[ITEM_MAX];
	int m_hndl;
	int m_waitCount;
	
}ITEM_MANAGER;

