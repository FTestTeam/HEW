#pragma once
#ifndef COMMON_H_
#define COMMON_H_
#include<d3dx9.h>
/*----------------------------
	定数
----------------------------*/

/*----------------------------
	マクロ定義
----------------------------*/
//セーフリリースマクロ
#define SAFE_RELEASE(p) if(p!=NULL){ p->Release(); p=NULL;}

//ローカルベクトル用
typedef struct LocalVecter_Tag {
	D3DXVECTOR3 Front;
	D3DXVECTOR3 Right;
	D3DXVECTOR3 Up;
}LocalVecter;

int Window_GetWidth();
int Window_GetHeight();

#endif