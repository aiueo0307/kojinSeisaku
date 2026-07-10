#include "fade.h"
#include <DxLib.h>

//定義関連=====================
#define FADE_SPEED (10)		//フェード速度
#define FADE_SIZE_X (640)		//フェード画面の横幅
#define FADE_SIZE_Y (480)	//フェード画面の縦幅
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

enum tagFadeState {
	FADE_NON,		//フェードなし
	FADE_IN,		//フェードイン中
	FADE_OUT,		//フェードアウト中
	FADE_OUT_WAIT,	//真っ暗
};

//フェード処理用構造体
typedef struct {
	tagFadeState m_state;	//現在のフェード情報
	int m_count;		//フェード時間のカウント
}FADE_DATA;

FADE_DATA g_fade;


//フェード初期化
void InitFade()
{
	g_fade.m_state = FADE_NON;
	g_fade.m_count = 0;
}


void TickFade()
{
	//状態に合わせて行動変化
	switch (g_fade.m_state)
	{
	case FADE_IN:
		//徐々に数字を減らして明るくする
		g_fade.m_count -= FADE_SPEED;
		if (g_fade.m_count <= 0)
		{
			g_fade.m_count = 0;
			g_fade.m_state = FADE_NON;

		}
		break;
	case FADE_OUT:
		//徐々に数字を増やして暗くする
		g_fade.m_count += FADE_SPEED;
		if (g_fade.m_count >= 255)
		{
			g_fade.m_count = 255;
			g_fade.m_state = FADE_OUT_WAIT;
		}
		break;
	}
}

void DrawFade()
{
	switch (g_fade.m_state)
	{
	case FADE_IN:
	case FADE_OUT:
	case FADE_OUT_WAIT:
		//アルファ値をセット
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_fade.m_count);
		//フェード用の四角を表示
		DrawBox(0, 0, FADE_SIZE_X, FADE_SIZE_Y,
			GetColor(0, 0, 0), TRUE);
		//初期設定に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		break;
	}
}


void RequestFadeIn()
{

	g_fade.m_count = 255;
	g_fade.m_state = FADE_IN;

}

void RequestFadeOut()
{
	g_fade.m_count = 0;
	g_fade.m_state = FADE_OUT;

}

bool IsEndFadeIn()
{
	if (g_fade.m_state == FADE_IN)
	{
		return false;
	}

	else return true;
}


bool IsEndFadeOut()
{
	if (g_fade.m_state == FADE_OUT)
	{
		return false;
	}
	else return true;
}
