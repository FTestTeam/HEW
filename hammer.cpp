#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "mydirect3d.h"
#include "input.h"
#include "model.h"
#include"DebugPrintf.h"

static LPDIRECT3DDEVICE9 g_pDevice;
static float g_angle = 0.0f;
static int g_count = 0;
static D3DXVECTOR3 g_Position;
static float g_power = 0.0f;
bool g_isFly = false;
static int g_FlyCount = 0;
static int g_model;

void Hammer_Init(void)
{
	g_pDevice = MyDirect3D_GetDevice();
	g_model=Model_SetLoadFile("Asset/Model/hammer.x");
}

void Hammer_Uninit(void)
{
	
}

void Hammer_Update(void)
{
	float gravity = 0.005f;
	if (Keyboard_IsPress(DIK_SPACE))
	{
		g_angle += 0.1f;
	}
	if (Keyboard_IsRelease(DIK_SPACE))
	{
		g_isFly = true;
		g_power = 1.0f;
	}

	if (g_isFly)
	{
		g_FlyCount+=1;
		g_Position.z += 0.5f;
		g_power -= gravity * g_FlyCount;
		g_Position.y = (g_power * g_FlyCount);
		if (g_Position.y <= 0.0f)
		{
			g_isFly = false;
			g_Position.y = 0.5f;
		}
	}
	else
	{
		g_FlyCount = 0;
	}
}

void Hammer_Draw(void)
{
	D3DXMATRIX mtxWorld, mtxRotation, mtxTranslation,mtxS,mtxhammerR;

	g_pDevice->SetTexture(0, NULL);
	D3DXMatrixRotationY(&mtxhammerR, D3DXToRadian(180));
	D3DXMatrixRotationY(&mtxRotation, g_angle);		//angleÉâÉWÉAÉìYé≤âÒì]Ç∑ÇÈçsóÒÇÃçÏê¨
	D3DXMatrixTranslation(&mtxTranslation, g_Position.x, g_Position.y, g_Position.z);
	D3DXMatrixScaling(&mtxS, 0.1f, 0.1f, 0.1f);
	mtxWorld = mtxS * mtxhammerR * mtxTranslation * mtxRotation;
	Model_Draw(&mtxWorld, g_model);
}

D3DXVECTOR3 Hammer_GetPosition(void)
{
	return g_Position;
}

void Hammer_SetPosition(D3DXVECTOR3 pos) 
{
	g_Position.x = pos.x;
	g_Position.y = pos.y+1.0f;
	g_Position.z = pos.z;
}