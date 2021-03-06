#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include<d3dx9.h>
#include"common.h"

#define AT_L (3.0f)

typedef struct Camera_Tag {
	LocalVecter LocalVec;
	D3DXVECTOR3 Pos;
	float Fov;
	float MoveSpeed;
	float RotationSpeed;
}Camera;

void Camera_Init();
void Camera_Update();

Camera Camera_GetPosition(void);
D3DXMATRIX Camera_GetmtxViewInv();

#endif // !CAMERA_H_
