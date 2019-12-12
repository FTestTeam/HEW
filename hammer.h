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

//�n���}�[�~�߂�p�֐�
void Hammer_Stop();	

//���ʂɔ��ł�n���}�[�ɑ΂��Ă���ɗ͂�������悤
//�������F
//	XYZ��POS_���Ŏw��
//�������F
//	float �����鐔�l
void Hammer_AddPosition(int pos, float n);	

//�n���}�[�����̈ʒu�ɃZ�b�g
//�������F
//	D3DXVECTER3
void Hammer_SetPosition(D3DXVECTOR3 vec);

#endif // !_HAMMER_H_