#include<d3dx9.h>
#include<d3d9.h>
#include"mydirect3d.h"
#include"texture.h"
#include"DebugPrintf.h"
#include"model.h"
#include"hammer.h"

static int g_model;

void BackGround_Init()
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
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX mtxW, mtxS, mtxT;
	D3DXMatrixScaling(&mtxS, 400, 400, 400);
	D3DXMatrixTranslation(&mtxT, Hammer_GetPosition().x, -30.0f, Hammer_GetPosition().z);
	mtxW = mtxS * mtxT;
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	Model_Draw(&mtxW, g_model);
}