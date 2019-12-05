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
void Hammer_SetPosition(int pos, float n);

#endif // !_HAMMER_H_