#pragma once
#ifndef MESHFIELD_H_
#define MESHFIELD_H_

void MeshField_Init(int MF_W, int MF_H , float w=1 , float h=1);
void MeshField_UnInit();
void MeshField_Update();
void MeshField_Draw(const D3DXMATRIX *mtx);

#endif // !MESHFIELD_H_