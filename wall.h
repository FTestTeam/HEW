#pragma once
#ifndef WALL_H_
#define WALL_H_

void Wall_Init(void);
void Wall_UnInit(void);
void Wall_Update(void);
void Wall_Draw(void);

void Wall_Delete(void);
D3DXVECTOR3 Wall_GetPosition(void);

#endif // !WALL_H_
