#pragma once

//エネミーとプレイヤーの弾の当たり判定
void HitCheckEnemyToPlayerShot();
void HitCheckEnemy2ToPlayerShot();
void HitCheckEnemy2ToPlayerShot2();
//Pの弾と敵の当たり判定
void HitCheckEnemyToPlayerShot2();

//エネミーとプレイヤーの当たり判定
bool HitCheckEnemyToPlayer();
bool HitCheckEnemy2ToPlayer();
//敵の弾とプレイヤーの当たり判定
bool HitCheckEnemyShotToPlayer();

//敵の弾とプレイヤーの弾当たり判定
void HitCheckEnemyShotToPlayerShot2();

void HitCheckPlayerToStage();