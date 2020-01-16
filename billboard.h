#pragma once
#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include<d3dx9.h>

void Billboard_Init(void);
void Billboard_UnInit(void);
void Billboard_Update(void);
void Billboard_Draw(const D3DXMATRIX *mtx, int TextureID);

//í èÌUVê›íË
void Billboard_SetUV();
void Billboard_SetUV(float CutX, float CutY, float CutW, float CutH, int TextureID);
void Billboard_SetColor(D3DCOLOR color);

#endif // !BILLBOARD_H_
