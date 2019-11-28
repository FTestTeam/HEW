#include<d3d9.h>
#include<d3dx9.h>
#include"common.h"
#include"model.h"
#include"hammer.h"
#include"joycon.h"
#include"cube.h"
#include"input.h"
#include"DebugPrintf.h"

typedef struct PLAYER_Tag{
	LocalVecter LocalVec;
	D3DXVECTOR3 Position;
	int ModelId;
}PLAYER;

static PLAYER g_Player;
static float g_Rspeed;
static float g_Ratetion;
static int g_fream;
static bool g_Fly;

void Player_Init() 
{
	Cube_Init();

	g_Player.Position = {0.0f,0.0f,0.0f};
	g_Player.LocalVec.Front = { 0.0f, 0.0f, -1.0f };
	g_Player.ModelId = Model_SetLoadFile("Asset/Model/player.x");

	g_Fly = false;
	g_Rspeed = 0.0f;

	D3DXVECTOR3 w;
	w = g_Player.Position + g_Player.LocalVec.Front * 1.5f;
	Hammer_SetPosition(w);
}

void Player_UnInit()
{
	Cube_UnInit();
}

void Player_Update()
{
	if (Keyboard_IsPress(DIK_SPACE) || Joycon_IsPress(DIJOY_R_R)) {
		if (Joycon_GetAccel(DIJOY_ACCEL_SL1) < -30000 || Joycon_GetAccel(DIJOY_ACCEL_SL1) > 30000) {
			g_Rspeed += 0.005f;
			//g_Rspeed = min(g_Rspeed, 1.0f);
		}
		g_Ratetion -= g_Rspeed;
		g_fream++;
	}
	if (Keyboard_IsRelease(DIK_SPACE) || Joycon_IsRelease(DIJOY_R_R)) {
		g_Fly = true;
	}
	DebugPrintf("%f\n", Joycon_GetAccel(DIJOY_ACCEL_SL1));
}

void Player_Draw()
{
	D3DXMATRIX mtxW,mtxR,mtxRR,mtxS;
	D3DXMatrixRotationY(&mtxR, g_Ratetion);
	D3DXMatrixRotationX(&mtxRR, D3DXToRadian(-90));
	D3DXMatrixScaling(&mtxS, 0.01f, 0.01f, 0.01f);
	mtxW = mtxS*mtxRR*mtxR;
	Model_Draw(&mtxW, g_Player.ModelId);
}

D3DXVECTOR3 Player_GetFront(void)
{
	return g_Player.LocalVec.Front;
}

float Player_GetRotation(void)
{
	return g_Ratetion;
}

bool Player_IsFly(void)
{
	return g_Fly;
}