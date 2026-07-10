#include "score.h"
#include <DxLib.h>

// 定義関連=============================
#define NUMBER (10)			// 読み込む画像「0」～「9」
#define NUMBER_SIZE_X (16)	// 数字画像のサイズ　横
#define NUMBER_SIZE_Y (32)	// 数字画像のサイズ　縦
#define DIGIT_NUMBER (5)	// 表示可能な桁数(今回は99999がカンスト)
#define ADD_SCORE_SPD (10)	// 1フレームで加算されるスコア数

#define START_POS_X (1200)	// スコア表示開始位置　横
#define START_POS_Y (48)	// スコア表示開始位置　縦

// 画像のパス
#define SCORE_GRAPH_PATH ("data/graphics/game/number16x32_03.png")
// 効果音
#define SCORE_SOUND_PATH ("data/sound/se2.mp3")
typedef struct {
	int m_hndl[NUMBER];
	int m_soundHndl;
	int m_score;
	int m_DispScore;
}SCORE_DATA;

SCORE_DATA g_score;

//======================================

void CScore::Init()
{
	for (int i = 0; i < NUMBER; i++)
	{
		g_score.m_hndl[i] = -1;
	}
	g_score.m_soundHndl = -1;
	g_score.m_score = 0;
	g_score.m_DispScore = 0;
}
void CScore::Load()
{
	LoadDivGraph(SCORE_GRAPH_PATH,
		NUMBER, NUMBER, 1, NUMBER_SIZE_X,
		NUMBER_SIZE_Y,g_score.m_hndl);
}
void CScore::Tick()
{
	if (g_score.m_score == g_score.m_DispScore)
		return;

	g_score.m_DispScore += ADD_SCORE_SPD;

	if (g_score.m_DispScore > g_score.m_score)
	{
		g_score.m_DispScore =  g_score.m_score;
	}
}
void CScore::Draw()
{
	int tempScore = g_score.m_DispScore;

	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		int num = tempScore % 10;
		DrawRotaGraph(START_POS_X - NUMBER_SIZE_X * i, START_POS_Y,
			1.0, 0.0, g_score.m_hndl[num], TRUE);
		tempScore /= 10;
	}
}
void CScore::Exit()
{
	for (int i = 0; i < NUMBER; i++)
	{
		if (g_score.m_hndl[i] != -1)
		{
			DeleteGraph(g_score.m_hndl[i]);
			g_score.m_hndl[i] = -1;
		}
	}

	if (g_score.m_soundHndl != 1)
	{
		DeleteSoundMem(g_score.m_soundHndl);
		g_score.m_soundHndl = -1;
	}
}

void CScore::Add(int score)
{
	g_score.m_score += score;
}

void CScore::Set(int score)
{
	 g_score.m_score=g_score.m_DispScore=score;
}
int CScore::Get()
{
	return g_score.m_score;
}