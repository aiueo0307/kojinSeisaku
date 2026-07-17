#include"hitcheck.h"
#include"player.h"
#include"enemy.h"
#include"enemy2.h"
#include"enemyshot.h"
#include"../lib/collision.h"
#include"effect.h"
#include"stage.h"

//プレイヤーとエネミーで用意したグローバル変数を
//このcppないで使えるように持ってくる
//wxternを使う場合は、externがついていない「本体」が
//プロジェクト内のどこかに定義されている必要がある

extern PLAYER_DATA g_player;
extern ENEMY_MANAGER g_enemyManager;
extern ENEMY2_MANAGER g_enemy2Manager;
extern ENEMYSHOT_MANAGER g_enemyShotManager;
extern ENEMYSHOT_DATA g_enemyShotData;
extern STAGE_DATA g_stageData;

//定義関連
#define ENEMY_SIZE_X (96)	//縦幅
#define ENEMY_SIZE_Y (96)	//横幅


//エネミーとプレイヤーの弾の当たり判定
void HitCheckEnemyToPlayerShot()
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_enemyManager.m_enemy[i].m_isActive == false)return;
		//==========弾１
		for (int j = 0; j < PL_SHOT_MAX; j++)
		{
			if (g_player.m_shot[j].isActive == false)
			{
				continue;
			}

			//弾と敵が当たったか判定
			bool isHit = CheckHitCircleToCircle(g_player.m_shot[j].m_pos, 16, g_enemyManager.m_enemy[i].m_pos, 16);
			//接触していた場合は敵と弾の両方のフラグをオフにする

			if (isHit == true)
			{
				g_player.m_shot[j].isActive = false;
				g_enemyManager.m_enemy[i].m_isActive = false;
				//エフェクトを呼び出す
				RequestExplosion(g_enemyManager.m_enemy[i].m_pos);
			}
		}
	}
}


//エネミーと弾2の当たり判定
void HitCheckEnemyToPlayerShot2()
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_enemyManager.m_enemy[i].m_isActive == false)continue;

		if (g_player.m_shot2.isActive == false)
		{
			continue;
		}

		//弾と敵が当たったか判定
		bool isHit = CheckHitCircleToCircle(g_player.m_shot2.m_pos, 48, g_enemyManager.m_enemy[i].m_pos, 16);
		//敵のフラグのみオフにする
		if (isHit == true)
		{
			g_enemyManager.m_enemy[i].m_isActive = false;
			/*g_player.m_shot2.isActive = false;*/

			//エフェクトを呼び出す
			RequestExplosion(g_enemyManager.m_enemy[i].m_pos);
			break;
		}
	}
}


//敵２とプレイヤーの弾の当たり判定
void HitCheckEnemy2ToPlayerShot()
{

	for (int i = 0; i < ENEMY2_MAX; i++)
	{

		for (int j = 0; j < PL_SHOT_MAX; j++)
		{
			if (g_enemy2Manager.m_enemy[i].m_isActive == false)continue;

			if (g_player.m_shot[j].isActive == false)
			{
				continue;
			}

			bool isHit = CheckHitCircleToCircle(g_player.m_shot[j].m_pos, 16, g_enemy2Manager.m_enemy[i].m_pos, 16);

			if (isHit == true)
			{
				g_player.m_shot[j].isActive = false;
				g_enemy2Manager.m_enemy[i].m_isActive = false;
				//エフェクトを呼び出す
				RequestExplosion(g_enemy2Manager.m_enemy[i].m_pos);

			}
		}
	}
}



//弾2と敵の弾
void HitCheckEnemyShotToPlayerShot2()
{


	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{

		if (g_enemyShotManager.m_shot[i].m_isActive == false)continue;

		//敵と弾が当たったか判定
		bool isHit = CheckHitCircleToCircle(g_player.m_shot2.m_pos, 64, g_enemyShotManager.m_shot[i].m_pos, 8);

		//接触していた場合は敵の弾のフラグをオフにする
		if (isHit == true)
		{

			g_enemyShotManager.m_shot[i].m_isActive = false;

			break;
		}


	}

}

//敵２とプレイヤーの弾2の当たり判定
void HitCheckEnemy2ToPlayerShot2()
{

	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		if (g_enemy2Manager.m_enemy[i].m_isActive == false)continue;

		if (g_player.m_shot2.isActive == false)
		{
			continue;
		}

		//弾と敵が当たったか判定
		bool isHit = CheckHitCircleToCircle(g_player.m_shot2.m_pos, 48, g_enemy2Manager.m_enemy[i].m_pos, 16);
		//敵のフラグのみオフにする
		if (isHit == true)
		{
			g_enemy2Manager.m_enemy[i].m_isActive = false;
			/*g_player.m_shot2.isActive = false;*/

			//エフェクトを呼び出す
			RequestExplosion(g_enemy2Manager.m_enemy[i].m_pos);
			break;
		}
	}
}


//敵とプレイヤーの当たり判定
bool HitCheckEnemyToPlayer()
{

	bool isHit = false;

	if (g_player.m_isActive == false)
	{
		return true;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_enemyManager.m_enemy[i].m_isActive == false)continue;
		isHit = CheckHitCircleToCircle(g_player.m_pos, 1, g_enemyManager.m_enemy[i].m_pos, 48);

		if (isHit == true)
		{
			//g_player.m_isActive = false;
			RequestExplosion(g_player.m_pos);
			break;
		}

	}

	return isHit;

}

//敵２とプレイヤーの当たり判定
bool HitCheckEnemy2ToPlayer()
{

	bool isHit = false;

	if (g_player.m_isActive == false)
	{
		return true;
	}

	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		if (g_enemy2Manager.m_enemy[i].m_isActive == false)continue;
		isHit = CheckHitCircleToCircle(g_player.m_pos, 1, g_enemy2Manager.m_enemy[i].m_pos, 48);

		if (isHit == true)
		{
			//	g_player.m_isActive = false;
			RequestExplosion(g_player.m_pos);
			break;
		}

	}

	return isHit;
}

//敵の弾とプレイヤーの当たり判定
bool HitCheckEnemyShotToPlayer()
{
	bool isHit = false;

	if (g_player.m_isActive == false)
	{
		return true;
	}

	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{
		if (g_enemyShotManager.m_shot[i].m_isActive == false)continue;

		//プレイヤーと弾が当たったか判定
		bool isHit = CheckHitCircleToCircle(g_player.m_pos, 8, g_enemyShotManager.m_shot[i].m_pos, 8);

		//接触していた場合はプレイヤーと弾の両方のフラグをオフにする
		if (isHit == true)
		{
			g_player.m_isActive = false;
			g_enemyShotManager.m_shot[i].m_isActive = false;

			//エフェクトを呼び出す
			RequestExplosion(g_enemyShotManager.m_shot[i].m_pos);
			break;
		}
	}

	return isHit;

}

void HitCheckPlayerToStage()
{
	bool isHitGround = false;

	// ステージすべてのマップチップと判定
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			// 調べている場所がブロックでなければ次へ進む
			if (g_stageData.m_stageData[y][x].m_state != STAGEID_BLOCK
				&& g_stageData.m_stageData[y][x].m_state != 8)
			{
				continue;
			}

			// プレイヤーとマップを矩形同士の当たり判定で調べる
			bool isHit = CheckHitSquareToSquare(g_player.m_pos,
				32, 32,
				g_stageData.m_stageData[y][x].m_pos,
				32, 32);

			// 当たっていないブロックなら次へ
			if (isHit == false) continue;

			// プレイヤーの座標をいったん入れる
			int posX = (int)g_player.m_pos.x;
			int posY = (int)g_player.m_pos.y;
			// プレイヤーの座標をもとに、二次元配列の
			// どこにプレイヤーがいるかを計算する
			posX /= 32;
			posY /= 32;
			// プレイヤーとブロックの位置関係を計算
			posX -= x;
			posY -= y;

			// めり込んだ距離を計算する-------------
			// プレイヤーと物体の距離を計算する
			float lenX = g_player.m_pos.x - g_stageData.m_stageData[y][x].m_pos.x;
			float lenY = g_player.m_pos.y - g_stageData.m_stageData[y][x].m_pos.y;
			// 距離はマイナスにはならない
			if (lenX < 0.0f) lenX *= -1.0f;
			if (lenY < 0.0f) lenY *= -1.0f;
			// 本来離れているべき距離から現在の離れている距離を引き算すると
			// めり込んだ距離が計算できる
			lenX = (32 / 2) + (32 / 2) - lenX;
			lenY = (32 / 2) + (32 / 2) - lenY;
			//--------------------------------------
			// 横のほうに押し戻す想定
			if (lenX < lenY)
			{
				// 押し戻す方向にブロックがなければ横に押し戻す
				if (g_stageData.m_stageData[y][x + posX].m_state != STAGEID_BLOCK)
				{
					// posXをかけることにより左右の+-が正しく設定される！
					lenX *= posX;
					// 想定の方向にめり込んだ分だけ押し戻す！
					g_player.m_pos.x += lenX;
				}
				// 横がダメだったときは第二候補の上下で押し戻す
				else if (g_stageData.m_stageData[y + posY][x].m_state != STAGEID_BLOCK)
				{
					// posYをかけることにより上下の+-が正しく設定される！
					lenY *= posY;
					// 想定の方向にめり込んだ分だけ押し戻す！
					g_player.m_pos.y += lenY;
					// 床として接触した場合は、プレイヤーを待機状態に
					if (lenY < 0)
					{
						SetLandPlayer();
						isHitGround = true;
					}
				}
			}
			// 縦のほうに押し戻す想定
			else
			{
				if (g_stageData.m_stageData[y + posY][x].m_state != STAGEID_BLOCK)
				{
					// posYをかけることにより上下の+-が正しく設定される！
					lenY *= posY;
					// 想定の方向にめり込んだ分だけ押し戻す！
					g_player.m_pos.y += lenY;
					// 床として接触した場合は、プレイヤーを待機状態に
					if (lenY < 0)
					{
						SetLandPlayer();
						isHitGround = true;
					}
				}
				// 押し戻す方向にブロックがなければ横に押し戻す
				else if (g_stageData.m_stageData[y][x + posX].m_state != STAGEID_BLOCK)
				{
					// posXをかけることにより左右の+-が正しく設定される！
					lenX *= posX;
					// 想定の方向にめり込んだ分だけ押し戻す！
					g_player.m_pos.x += lenX;
				}
			}
		}
	}

	if (!isHitGround) SetJumpPlayer();
}
