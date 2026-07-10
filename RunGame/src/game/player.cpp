#include"player.h"
#include<DxLib.h>
#include"../lib/input.h"
#include"playershot.h"
#include"effect.h"
#include"common.h"

//定義関連＝＝＝＝＝＝＝＝＝＝＝＝
#define Player_SIZE_X (60.0f) 
#define Player_SIZE_Y (60.0f) 
#define PLAYER_SPEED (5.0f)
#define PLAYER_AIR_SPEED (3.5f)
#define PLAYER_JUMP_POW	(5.0f)
#define SHOT_SPEED (7.0)
#define SHOT2_SPEED (10.0)
#define SHOT_COOLTIME (30)
#define SLASH_ACTIVE_COUNT (60)
#define GRAPH_NUM (12)
//#define Screen_SiZE_X (640.0f)
//#define Screen_SiZE_Y (480.0f)
#define Shot2_TimeCount (180)
#define PlayerHP (50)
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void PlayerShot2();
void PlayerShot1L();
void PlayerShot1R();
void PlayerSlash();
void  PlayerJump();
void PlayerShot1MoveL();
int g_playerSpeed = PLAYER_SPEED;

//構造体を実際の変数で
PLAYER_DATA g_player;

static const int g_iAnimID[][4] = {
	{ 0, 1, 2, 1 }, { 3, 4, 5, 4 }, { 6, 7, 8, 7 }, { 9, 10, 11, 10 }
};
//プレイヤーデータの初期化
void IniPlayer()
{//player用
	//g_player.m_hndl = -1;
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		g_player.m_hndl[i] = -1;
	}
	g_player.m_pos.x = WINDOW_SIZE_X * 0.5f;
	g_player.m_pos.y = WINDOW_SIZE_Y * 0.8f;
	g_player.m_isActive = true;
	g_player.m_phndl = -1;
	g_playerSpeed = PLAYER_SPEED;
	g_player.m_timecount = 0;
	g_player.m_hp = PlayerHP;
	g_player.m_shotcooltime = 0;
	g_player.m_playerJump = false;
	g_player.m_dir = RIGHT;
	g_player.m_state = PLAYER_JUMP;
	g_player.m_animCnt = 0;
	g_player.m_slashActiveCount = SLASH_ACTIVE_COUNT;
//弾用
	//弾１
	g_player.m_shotHndl = -1;
	for (int i = 0; i < PL_SHOT_MAX; i++) 
	{
		g_player.m_shot[i].isActive = false;
		g_player.m_shot_r[i].isActive = false;
	}
	//弾２
	g_player.m_shot2Hndl = -1;
	
		g_player.m_shot2.isActive = false;
	
	//起爆までのカウント
	int m_timecount = Shot2_TimeCount;

}



//プレイヤーデータ画像読込関数
void LoadPlayer()
{
	if (g_player.m_phndl == -1)
	{
		g_player.m_phndl = LoadGraph("data/graphics/game/player.png");

	}
	if (g_player.m_shotHndl == -1)
	{
		g_player.m_shotHndl = LoadGraph("data/graphics/game/shot00.png");

	}
	if (g_player.m_shot2Hndl == -1)
	{
		g_player.m_shot2Hndl = LoadGraph("data/graphics/game/shot00.png");

	}
	if (g_player.m_slashHndl == -1)
	{
		g_player.m_slashHndl = LoadGraph("data/graphics/game/shot00.png");
	}
	if (g_player.m_hndl[0] == -1)
	{
		LoadDivGraph("data/graphics/game/player00.png", GRAPH_NUM, 3, 4,
			PLAYER_SIZE_X, PLAYER_SIZE_Y, g_player.m_hndl);
	}

}

//プレイヤーデータの毎フレーム更新処理関数
void TickPlayer()
{

	switch (g_player.m_state) {
	case PLAYER_WAIT:
		SetLandPlayer();
		PlayerMove();
		PlayerJump();
		break;
	case PLAYER_MOVE:
		SetLandPlayer();
		PlayerMove();
		PlayerJump();
		break;
	case PLAYER_JUMP:
		PlayerMove();
		break;
	}
	//移動処理


	// g_player.m_animCnt = (g_player.m_animCnt + 1) % 40;



	// 重力処理
	g_player.m_jumpPow -= GRAVITY;
	g_player.m_pos.y -= g_player.m_jumpPow;

	// 仮
	if (g_player.m_pos.y >= WINDOW_SIZE_Y)
	{
		g_player.m_pos.y = WINDOW_SIZE_Y;
		SetLandPlayer();
	}
	g_player.m_animCnt = (g_player.m_animCnt + 1) % 40;
	
	PlayerShot1L();
	PlayerShot1R();
	PlayerShot2();
	PlayerSlash();
	
}
	

///プレイヤー表示関数
void DrawPlayer()
{

	int hndlNum = g_iAnimID[g_player.m_dir][g_player.m_animCnt / 10];
//2D画像表示
//第一引数：X座標、２：Y座標、３：拡大縮小率、４：回転角度（ラジアン角）
	//５：画像ハンドル、６：透過処理を有効にするか
	if (g_player.m_isActive == true)
	{
		
		//DrawRotaGraph((int)g_player.m_pos.x-GetWorldOffsetX(), (int)g_player.m_pos.y - GetWorldOffsetY(), 1.0, 0.0, g_player.m_phndl, TRUE);
		DrawRotaGraph((int)g_player.m_pos.x - GetWorldOffsetX(), (int)g_player.m_pos.y - GetWorldOffsetY(), 1.0, 0.0, g_player.m_hndl[hndlNum], TRUE);
	}

	//弾の画像表示
	//左
	for (int i = 0; i < PL_SHOT_MAX; i++)
	{
		if (g_player.m_shot[i].isActive == true)
		{
			DrawRotaGraph((int)g_player.m_shot[i].m_pos.x - GetWorldOffsetX(), (int)g_player.m_shot[i].m_pos.y - GetWorldOffsetY(), 1.0, 0.0, g_player.m_shotHndl, TRUE);
		}
	}
	//右
	for (int i = 0; i < PL_SHOT_MAX; i++)
	{
		if (g_player.m_shot_r[i].isActive == true)
		{
			DrawRotaGraph((int)g_player.m_shot_r[i].m_pos.x - GetWorldOffsetX(), (int)g_player.m_shot_r[i].m_pos.y - GetWorldOffsetY(), 1.0, 0.0, g_player.m_shotHndl, TRUE);
		}
	}
	//slash
	if (g_player.m_slash.isActive == true)
	{
		DrawRotaGraph((int)g_player.m_slash.m_pos.x - GetWorldOffsetX(), (int)g_player.m_slash.m_pos.y - GetWorldOffsetY(), 3.0, 0.0, g_player.m_slashHndl, TRUE);
	}


	
		if (g_player.m_shot2.isActive == true)
		{
			DrawRotaGraph((int)g_player.m_shot2.m_pos.x - GetWorldOffsetX(), (int)g_player.m_shot2.m_pos.y - GetWorldOffsetY(), 4.0, 0.0, g_player.m_shot2Hndl, TRUE);
		}
	
}

//終了前に行う必要がある処理関数
void ExitPlayer()
{
	//ハンドルが-1でなければ、何かしらロードされているはず
	if (g_player.m_shotHndl != -1)
	{
		DeleteGraph(g_player.m_shotHndl);
		g_player.m_shotHndl = -1;
	}
	for (int i = 0; i < GRAPH_NUM; i++)
	{
		if (g_player.m_hndl[i] != -1)
		{
			DeleteGraph(g_player.m_hndl[i]);
			g_player.m_hndl[i] = -1;
		}
	}
}


void PlayerShot2()
{
	//弾２
	if (IsInputTrg(KEY_SHOT2) == true)
	{
		//弾の発射処理
		if (g_player.m_shot2.isActive == false)
		{
			g_player.m_shot2.m_pos = g_player.m_pos;
			g_player.m_shot2.isActive = true;
		}
	}
	//弾の移動処理2
	if (g_player.m_shot2.isActive == true)
	{
		//上下
		if (IsInputRep(KEY_JUMP) == true)
		{
			g_player.m_shot2.m_pos.y -= SHOT2_SPEED;
		}
		else if (IsInputRep(KEY_DOWN) == true)
		{
			g_player.m_shot2.m_pos.y += SHOT2_SPEED;
		}
		//左右
		if (IsInputRep(KEY_RIGHT) == true)
		{
			g_player.m_shot2.m_pos.x += SHOT2_SPEED;
		}
		else if (IsInputRep(KEY_LEFT) == true)
		{
			g_player.m_shot2.m_pos.x -= SHOT2_SPEED;
		}

		/*if (g_player.m_shot2.m_pos.y < 0.0f
			|| g_player.m_shot2.m_pos.x < 0.0f
			|| g_player.m_shot2.m_pos.y > WINDOW_SIZE_Y
			|| g_player.m_shot2.m_pos.x > WINDOW_SIZE_X
			)
		{
			g_player.m_shot2.isActive = false;
			g_player.m_timecount = Shot2_TimeCount;
			g_playerSpeed = PLAYER_SPEED;
		}*/
		if (g_player.m_pos.x + WINDOW_SIZE_X * 0.5f < g_player.m_shot2.m_pos.x
			|| g_player.m_pos.x - WINDOW_SIZE_X * 0.5f > g_player.m_shot2.m_pos.x
			|| g_player.m_pos.y + WINDOW_SIZE_Y * 0.5f < g_player.m_shot2.m_pos.y
			|| g_player.m_pos.y - WINDOW_SIZE_Y * 0.5f > g_player.m_shot2.m_pos.y)
		{
			g_player.m_shot2.isActive = false;
			g_player.m_timecount = Shot2_TimeCount;
			g_playerSpeed = PLAYER_SPEED;
		}


		//弾２の起爆
		if (g_player.m_shot2.isActive == true)
		{
			g_player.m_timecount++;
			g_playerSpeed = 0;
		}

		//もう一度押すと起爆
		if (g_player.m_timecount >= 30 && IsInputTrg(KEY_SHOT2) == true|| g_player.m_timecount >= 30 && IsInputTrg(KEY_SHOT))
		{
			g_player.m_shot2.isActive = false;
			RequestExplosion(g_player.m_shot2.m_pos);

			//ここで爆破時間、速度をリセット
			g_player.m_timecount = 0;

			g_playerSpeed = PLAYER_SPEED;
		}

		//指定時間で爆破
		if (g_player.m_timecount >= Shot2_TimeCount)
		{
			g_player.m_shot2.isActive = false;
			RequestExplosion(g_player.m_shot2.m_pos);

			//ここで爆破時間、速度をリセット
			g_player.m_timecount = 0;

			g_playerSpeed = PLAYER_SPEED;
		}

		if (g_player.m_shot2.isActive == false)
		{
			g_playerSpeed = PLAYER_SPEED;
		}
	}
}

void PlayerShot1L()
{
	g_player.m_shotcooltime--;

	//弾１
	if (IsInputTrg(KEY_SHOT) == true&&g_player.m_dir == LEFT&& g_player.m_shotcooltime<=0)
	{
		
	
		for (int i = 0; i < PL_SHOT_MAX; i++)
		{
			//弾の発射処理
			
			if (g_player.m_shot[i].isActive == false)
			{
				g_player.m_shot[i].m_pos = g_player.m_pos;
				g_player.m_shot[i].isActive = true;
				g_player.m_shotcooltime = SHOT_COOLTIME;
				break;	//一発でも玉を飛ばすと終了

			}
		}
	}

	//弾の移動処理1
	PlayerShot1MoveL();
		
	

}
void PlayerShot1R()
{
	//弾１
	if (IsInputTrg(KEY_SHOT) == true && g_player.m_dir == RIGHT && g_player.m_shotcooltime <= 0)
	{
		for (int i = 0; i < PL_SHOT_MAX; i++)
		{
			//弾の発射処理

			if (g_player.m_shot_r[i].isActive == false)
			{
				g_player.m_shot_r[i].m_pos = g_player.m_pos;
				g_player.m_shot_r[i].isActive = true;
				g_player.m_shotcooltime = SHOT_COOLTIME;
				break;	//一発でも玉を飛ばすと終了

			}
		}
	}

	//弾の移動処理1
	
		for (int i = 0; i < PL_SHOT_MAX; i++)
		{

			if (g_player.m_shot_r[i].isActive == true)
			{
				g_player.m_shot_r[i].m_pos.x += SHOT_SPEED;
				/*if (g_player.m_shot_r[i].m_pos.y < 0.0f || g_player.m_shot_r[i].m_pos.y > WINDOW_SIZE_Y ||
					g_player.m_shot_r[i].m_pos.x < 0.0f || g_player.m_shot_r[i].m_pos.x > WINDOW_SIZE_X)
				{
					g_player.m_shot_r[i].isActive = false;
				}*/


				//プレイヤーの位置から一定まで離れると消える
				if (g_player.m_pos.x + WINDOW_SIZE_X * 0.5f<g_player.m_shot_r[i].m_pos.x)
				{
					g_player.m_shot_r[i].isActive = false;
				}
				

			}
		}
	
}

void PlayerShot1MoveL()
{
	for (int i = 0; i < PL_SHOT_MAX; i++)
	{

		if (g_player.m_shot[i].isActive == true)
		{
			g_player.m_shot[i].m_pos.x -= SHOT_SPEED;
			/*if (g_player.m_shot[i].m_pos.y < 0.0f || g_player.m_shot[i].m_pos.y > WINDOW_SIZE_Y ||
				g_player.m_shot[i].m_pos.x < 0.0f || g_player.m_shot[i].m_pos.x > WINDOW_SIZE_X)
			{
				g_player.m_shot[i].isActive = false;
			}*/
			//プレイヤーの位置から一定まで離れると消える
			if (g_player.m_pos.x - WINDOW_SIZE_X * 0.5f > g_player.m_shot[i].m_pos.x)
			{
				g_player.m_shot[i].isActive = false;
			}

		}
	}
}

void PlayerSlash()
{
	
}
void PlayerMove()
{
	
	//左右
	
		if (IsInputRep(KEY_RIGHT) == true)
		{
			g_player.m_pos.x += g_playerSpeed;
			g_player.m_dir = RIGHT;
		}
		else if (IsInputRep(KEY_LEFT) == true)
		{
			g_player.m_pos.x -= g_playerSpeed;
			g_player.m_dir = LEFT;
		}
	
}

void PlayerJump()
{
	if (IsInputTrg(KEY_JUMP))
	{
		g_player.m_state = PLAYER_JUMP;
		g_player.m_jumpPow = PLAYER_JUMP_POW;
		g_playerSpeed = PLAYER_AIR_SPEED;
	}

}

//着地時にセット
void SetLandPlayer()
{
	g_player.m_jumpPow = 0.0f;
	g_player.m_state = PLAYER_WAIT;
	g_playerSpeed = PLAYER_SPEED;
}

void SetJumpPlayer()
{
	g_player.m_state = PLAYER_JUMP;
}

void WaitExec()
{
	
}



int GetWorldOffsetX()
{
	int offset;
	offset = g_player.m_pos.x - WINDOW_SIZE_X * 0.5f;
	return offset;
}

int GetWorldOffsetY()
{
	int offset;
	offset = g_player.m_pos.y - WINDOW_SIZE_Y * 0.5f;
	return offset;
}