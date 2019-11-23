#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

void Player_Init();
void Player_UnInit();
void Player_Update();
void Player_Draw();

D3DXVECTOR3 Player_GetFront(void);
float Player_GetRotation(void);
bool Player_IsFly(void);

#endif // !PLAYER_H_