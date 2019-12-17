#pragma once
#ifndef ZAKO_H_
#define ZAKO_H_
#include<d3dx9.h>

#define ZAKO_MAX (10)

void Zako_Init(void);
void Zako_UnInit(void);
void Zako_Update(void);
void Zako_Draw(void);

//GðÁ·Ö
//øF
//	int Á·GÌiD
void Zako_Delete(int Id);

D3DXVECTOR3 Zako_GetPosition(int Id);

//Gðóµ½ÌQbgÖ
//ßèlF
//	int óµ½
int Zako_GetBreakCount(void);

#endif // !ZAKO_H_
