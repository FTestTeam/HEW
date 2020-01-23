#pragma once
#ifndef EFFECT_H_
#define EFFECT_H_

#include<d3d9.h>
#include<d3dx9.h>

void Effect_Init(void);
void Effect_UnInit(void);
void Effect_Update(void);
void Effect_Draw(void);

//�G�t�F�N�g
//color->�G�t�F�N�g�̐F
//life->�G�t�F�N�g���c��t���[����
void Effect_Create(D3DXVECTOR3 pos, D3DCOLOR color, int life, float size);	//����e�̑��x���ނȂǂ�ǉ�����

#endif // !EFFECT_H_
