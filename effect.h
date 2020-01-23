#pragma once
#ifndef EFFECT_H_
#define EFFECT_H_

#include<d3d9.h>
#include<d3dx9.h>

void Effect_Init(void);
void Effect_UnInit(void);
void Effect_Update(void);
void Effect_Draw(void);

//エフェクト
//color->エフェクトの色
//life->エフェクトが残るフレーム数
void Effect_Create(D3DXVECTOR3 pos, D3DCOLOR color, int life, float size);	//今後弾の速度や種類などを追加する

#endif // !EFFECT_H_
