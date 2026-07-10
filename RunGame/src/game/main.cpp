#include <DxLib.h>			// DxLibを使用するために必須
#include"../lib/debug.h"
#include"../lib/input.h"
#include"scene.h"
#include "../lib/fade.h"
#include"soundmanager.h"

// ゲームプログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);			// ウィンドウモードにするかどうか
	//SetGraphMode(640, 480, 32);		// ウィンドウの解像度を設定する
	 SetGraphMode(1280, 720, 32);
	//SetGraphMode(1920, 1080, 32);
#ifndef _DEBUG
	// リリース版はログを出さない
	SetOutApplicationLogValidFlag( false );
#endif

	// ＤＸライブラリ初期化処理　基本的にはこれより後でDxLib関数を使う
	if (DxLib_Init() == -1) return -1;

	// 一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);	// 画面のちらつきを無くす
	SetTransColor(255, 0, 255);		// 透過色指定　今回は真紫色を透明

//初期化はここで行う

	InitScene();
	InitFade();
	InitSound();
	LoadSound();

	//画像や音楽データの読み込み
	
	//ゲームメインループ
	while (ProcessMessage() != -1)	// 問題が発生したら終了
	{
		WaitTimer(1);

		// 「escキー」が押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		//想定のフレームに到達していなければ処理を待つ
		if (IsNextFrame() == false)continue;

		// 画面を一度何もない状態へ
		ClearDrawScreen();

		// ゲーム本体の命令はこれより下に書く
	

		//更新関連===========
		UpdateInput();
		TickScene();

		//描画関連===============
		//ゲーム全般の表示
		DrawScene();
		//FPSの表示
		PrintFps();
		
		// ゲーム本体の命令はこれより上に書く

		// 作成した画面をモニターへ転送
		ScreenFlip();

	}

	// 終了前処理==================
	ExitSound();

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	//=============================

	
	return 0;				// プログラムの終了 
}
