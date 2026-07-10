#include <DxLib.h>
#include "UI.h"

static SCOREDATA g_score;

void InitScore()
{
	g_score.m_score = 0;
}

void PrintScore()
{
	//文字の表示　引数は「横の位置」「縦の位置」「色」「文字」
	DrawFormatString(32, 64, GetColor(0, 0, 255), "%d", g_score.m_score);
}

