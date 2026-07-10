#pragma once

// ウィンドウのサイズ
#define WINDOW_SIZE_X (1280)		
#define WINDOW_SIZE_Y (720)


// プレイヤーのサイズ
#define PLAYER_SIZE_X (32)		
#define PLAYER_SIZE_Y (32)

// ステージに配置する物体のサイズ
#define OBJECT_SIZE_X		(32)
#define OBJECT_SIZE_Y		(32)


// ゲーム中の重力
#define GRAVITY	(0.1f)

enum tagStageID {
	STAGEID_BLOCK,		// 床・壁

	STAGEID_NUM
};