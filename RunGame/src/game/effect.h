#pragma once
#include <DxLib.h>
//背景データの初期化
void InitExplosion();
//背景データ画像読込関数
void LoadExplosion();
//背景データの毎フレーム更新処理関数
void TickExplosion();
///背景表示関数
void DrawExplosion();
//終了前に行う必要がある処理関数
void ExitExplosion();


//エフェクトを呼び出すための関数
//@pos:エフェクトの表示場所
void RequestExplosion(VECTOR pos);


