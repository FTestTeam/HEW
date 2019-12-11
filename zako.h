#pragma once
#ifndef ZAKO_H_
#define ZAKO_H_
#include<d3dx9.h>

#define ZAKO_MAX (20)

void Zako_Init(void);
void Zako_UnInit(void);
void Zako_Update(void);
void Zako_Draw(void);

void Zako_Delete(int Id);
D3DXVECTOR3 Zako_GetPosition(int Id);
int Zako_GetBreakCount(void);

#endif // !ZAKO_H_
