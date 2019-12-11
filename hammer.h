#ifndef _HAMMER_H_
#define _HAMMER_H_
#include<d3dx9.h>

#define POS_X	(0)
#define POS_Y	(1)
#define POS_Z	(2)

void Hammer_Init(void);
void Hammer_Uninit(void);
void Hammer_Update(void);
void Hammer_Draw(void);

D3DXVECTOR3 Hammer_GetPosition(void);
bool Hammer_IsFly();

//ハンマー止める用関数
void Hammer_Stop();	

//普通に飛んでるハンマーに対してさらに力を加えるよう
//第一引数：
//	XYZをPOS_□で指定
//第二引数：
//	float 加える数値
void Hammer_AddPosition(int pos, float n);	

//ハンマーをその位置にセット
//第一引数：
//	D3DXVECTER3
void Hammer_SetPosition(D3DXVECTOR3 vec);

#endif // !_HAMMER_H_