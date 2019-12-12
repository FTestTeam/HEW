#pragma once
#ifndef ZAKO_H_
#define ZAKO_H_
#include<d3dx9.h>

#define ZAKO_MAX (4)

void Zako_Init(void);
void Zako_UnInit(void);
void Zako_Update(void);
void Zako_Draw(void);

//雑魚を消す関数
//引数：
//	int 消す雑魚のiD
void Zako_Delete(int Id);

D3DXVECTOR3 Zako_GetPosition(int Id);

//雑魚を壊した数のゲット関数
//戻り値：
//	int 壊した数
int Zako_GetBreakCount(void);

#endif // !ZAKO_H_
