#pragma once
#ifndef ZAKO_H_
#define ZAKO_H_
#include<d3dx9.h>

#define ZAKO_MAX (4)

void Zako_Init(void);
void Zako_UnInit(void);
void Zako_Update(void);
void Zako_Draw(void);

//�G���������֐�
//�����F
//	int �����G����iD
void Zako_Delete(int Id);

D3DXVECTOR3 Zako_GetPosition(int Id);

//�G�����󂵂����̃Q�b�g�֐�
//�߂�l�F
//	int �󂵂���
int Zako_GetBreakCount(void);

#endif // !ZAKO_H_
