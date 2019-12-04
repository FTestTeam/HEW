#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "mydirect3d.h"
#include "input.h"
#include "model.h"
#include "player.h"
#include "wall.h"
#include "score.h"

static LPDIRECT3DDEVICE9 g_pDevice;
static D3DXVECTOR3 g_Position;
static bool g_bFly;
static float g_speed;
static int g_model;

void Hammer_Init(void)
{
	g_pDevice = MyDirect3D_GetDevice();
	g_model=Model_SetLoadFile("Asset/Model/hammer.x");
	g_bFly = true;
}

void Hammer_Uninit(void)
{
	
}

void Hammer_Update(void)
{
	if (!Keyboard_IsPress(DIK_SPACE)) {
		if (Wall_GetPosition().z - 1.0f < g_Position.z && Wall_GetPosition().z + 1.0f > g_Position.z) {
			g_bFly = false;
		}
	}
	else if(Player_IsFly() && Keyboard_IsPress(DIK_SPACE)) {
		if (Wall_GetPosition().z - 1.0f < g_Position.z) {
			Wall_Delete();
		}
		g_Position.z += 0.1f;
	}

	if (Player_IsFly() && g_bFly) {
		g_Position.z += 0.3f;
		g_Position.y += 0.05f;
		g_Position.y = min(g_Position.y, 3.0f);
		AddScore();
	}
	if (!g_bFly) {
		g_Position.z = Wall_GetPosition().z - 1.0f;
		g_Position.y -= 0.05f;
		g_Position.y = max(g_Position.y, -0.5f);
	}
}

void Hammer_Draw(void)
{
	D3DXMATRIX mtxW,mtxS,mtxR,mtxRR,mtxT;

	if (!Player_IsFly()) {
		D3DXMatrixIdentity(&mtxT);
		D3DXMatrixRotationY(&mtxR, Player_GetRotation());
	}
	else {
		D3DXMatrixTranslation(&mtxT, g_Position.x, g_Position.y, g_Position.z);
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(180));
	}
	D3DXMatrixRotationX(&mtxRR, D3DXToRadian(-90));
	D3DXMatrixScaling(&mtxS, 0.01f, 0.01f, 0.01f);
	mtxW = mtxS * mtxRR* mtxR * mtxT;
	Model_Draw(&mtxW, g_model);
}

D3DXVECTOR3 Hammer_GetPosition(void)
{
	return g_Position;
}

void Hammer_SetPosition(D3DXVECTOR3 pos) 
{
	g_Position.x = pos.x;
	g_Position.y = pos.y + 1.0f;
	g_Position.z = pos.z;
}