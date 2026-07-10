#pragma once
#include"DxLib.h"
enum goalTagState {

};
typedef struct {

	int m_Hndl;
	goalTagState m_state;
	VECTOR m_pos;
}GOAL_DATA;

void InitGoal();
void LoadGoal();
void TickGoal();
void DrawGoal();
void ExitGoal();