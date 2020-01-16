#pragma once
#ifndef WALL_H_
#define WALL_H_

void Wall_Init(void);
void Wall_UnInit(void);
void Wall_Update(void);
void Wall_Draw(void);

void Wall_Delete(void);
D3DXVECTOR3 Wall_GetPosition(void);
D3DXCOLOR Wall_GetColor();
void Wall_MinAlpha(float n);
bool Wall_isUse();

#endif // !WALL_H_
