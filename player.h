#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include<d3dx9.h>

void Player_Init();
void Player_UnInit();
void Player_Update();
void Player_Draw();

//プレイヤーの正面のベクトル取得
D3DXVECTOR3 Player_GetFront(void);
//プレイヤーの回転角度取得
float Player_GetRotation(void);

D3DXVECTOR3 Player_GetPosition();
//プレイヤーがハンマー飛ばしたか？
bool Player_IsFly(void);
float Player_GetForce();

#endif // !PLAYER_H_