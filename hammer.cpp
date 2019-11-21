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
static float g_positionZ ;
static float g_positionY ;
static float g_positionX ;
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
		g_angle -= 0.1f;
		g_positionY = 1.0f;
	}
	if (Keyboard_IsRelease(DIK_SPACE))
	{
		g_isFly = true;
		g_power = 1.0f;
	}

	if (g_isFly)
	{
		g_FlyCount+=1;
		g_positionZ += 1.5f;
		//g_power -= gravity;
		g_power -= gravity * g_FlyCount;
		g_positionY = (g_power * g_FlyCount);
		//g_positionY += (g_power * time) - (0.5f*gravity*(time*time));
		/*if (g_power > 0)
		{
			g_positionY += 0.2f;
		}
		else
		{
			g_positionY -= gravity * g_FlyCount;
			
		}*/
		if (g_positionY <= 0.0f)
		{
			g_isFly = false;
			g_positionY = 0.5f;
		}
	}
	else
	{
		g_FlyCount = 0;
	}
	DebugPrintf("%f",g_positionZ);
}

void Hammer_Draw(void)
{
	D3DXMATRIX mtxWorld, mtxRotation, mtxTranslation,mtxS,mtxhammerR;

	g_pDevice->SetTexture(0, NULL);
	D3DXMatrixRotationY(&mtxhammerR, D3DXToRadian(90));
	D3DXMatrixRotationY(&mtxRotation, g_angle);		//angleÉâÉWÉAÉìYé≤âÒì]Ç∑ÇÈçsóÒÇÃçÏê¨
	D3DXMatrixTranslation(&mtxTranslation, g_positionX, g_positionY, g_positionZ);
	D3DXMatrixScaling(&mtxS, 0.3f, 0.3f, 0.3f);
	mtxWorld = mtxS * mtxhammerR * mtxTranslation * mtxRotation;
	Model_Draw(&mtxWorld, g_model);
}

D3DXVECTOR3 HamPosition_Get(void)
{
	
	return D3DXVECTOR3 (g_positionX, g_positionY, g_positionZ);
}

void Hammer_SetPosition(D3DXVECTOR3 pos) 
{
	g_positionX = pos.x;
	g_positionY = pos.y;
	g_positionZ = pos.z;
}