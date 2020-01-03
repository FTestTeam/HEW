#include<d3dx9.h>
#include<d3d9.h>
#include"mydirect3d.h"
#include"texture.h"
#include"DebugPrintf.h"
#include"model.h"
#include"hammer.h"

static int g_model;

void BackGround_Init(int BG_W, int BG_H, float w, float h)
{
	g_model = Model_SetLoadFile("Asset/Model/sky3.x");
}

void BackGround_UnInit()
{

}

void BackGround_Update()
{

}

void BackGround_Draw()
{
	D3DXMATRIX mtxW, mtxS, mtxT;
	D3DXMatrixScaling(&mtxS, 400, 400, 400);
	D3DXMatrixTranslation(&mtxT, 0.0f, -30.0f, 0.0f);
	mtxW = mtxS * mtxT;
	Model_Draw(&mtxW, g_model);
}