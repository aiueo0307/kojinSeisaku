#include <DxLib.h>
#define FRAME_RATE (60)	//1秒あたりのフレーム
#define FRAMERATE_MILLI_SECOND (1000/FRAME_RATE - 1 )	//何ミリ秒で1フレームか

//FPSを表示する構造体
typedef struct {
	float m_frameRate;//今のフレームレートを保存
	int m_nowTime;//現在時間
	int m_prevTime;//ひとつ前の時間
	int m_prevDrawTime;	//1つ前の描画した時間
	int m_count;//カウント用
}FpsData;


static FpsData g_fps;//実際にFPS表示に使用する変数



//初期化関数
void InitFps()
{
	g_fps.m_frameRate = 0.0f;
	g_fps.m_nowTime = 0;
	g_fps.m_prevTime = GetNowCount();
	g_fps.m_count = 0;
	g_fps.m_prevDrawTime = 0;
}


//FPS表示関数
void PrintFps(void)
{
	//まずはカウントを増やす
	g_fps.m_count++;
	//前回更新してからどれだけ時間がかかったか計算
	int difTime = g_fps.m_nowTime - g_fps.m_prevDrawTime;
	//1秒ごとにフレームレートを再計算
	if (difTime >= 1000)
	{
		//カウントは60000担っているのが理想
		float frameCount = (float)(g_fps.m_count * 1000);
		//FPSを再計算しなおす
		g_fps.m_frameRate = frameCount / difTime;
		//カウントは初期化
		g_fps.m_count = 0;
		//ひとつ前の時間も更新
		g_fps.m_prevDrawTime = g_fps.m_nowTime;
	}

	//文字の表示　引数は「横の位置」「縦の位置」「色」「文字」
	DrawFormatString(32,32,GetColor(255,0,0), "%2f", g_fps.m_frameRate);
}

//次のフレームに進めていいか
bool IsNextFrame()
{
	//最新の時間を取得
	g_fps.m_nowTime = GetNowCount();
	//前回更新してからどれだけ時間がかかったか計算
	int difTime = g_fps.m_nowTime - g_fps.m_prevTime;

	//前回の時間から指定したフレーム分、時間が経過したかチェック
	if (difTime >= FRAMERATE_MILLI_SECOND)
	{
		return true;
	}
	else return false;
}


//FPS更新処理
void TickFps()
{
	g_fps.m_prevDrawTime = g_fps.m_nowTime;
}