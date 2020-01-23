#pragma once
#ifndef CUBE_H_
#define CUBE_H_

void Cube_Init(void);
void Cube_UnInit(void);
void Cube_Update(void);
void Cube_Draw(const D3DXMATRIX *mtx,int TextureID);

void Cube_SetUV(float CutX, float CutY, float CutW, float CutH, int TextureID);

#endif // !CUBE_H_
