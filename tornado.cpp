#include<d3dx9.h>
#include"player.h"
#include"model.h"
#include"input.h"
#include"joycon.h"

static D3DXVECTOR3 g_pos;
static int g_ModelID;
static float g_angle;
static float g_scale;

void Tornado_Init()
{
	g_ModelID = Model_SetLoadFile("Asset/Model/tornado2.x");

	g_pos = Player_GetPosition();
	g_angle = Player_GetRotation();
	g_scale = 0;
}

void Tornado_UnInit()
{

}

void Tornado_Update()
{
	if (Keyboard_IsPress(DIK_SPACE) || Joycon_IsPress(DIJOY_R_R)) {
		if (Joycon_GetAccel(DIJOY_ACCEL_SL1) > -30000 || Joycon_GetAccel(DIJOY_ACCEL_SL1) < 30000 || Keyboard_IsPress(DIK_SPACE)) {
			g_scale += fabsf(Joycon_GetAccel(DIJOY_ACCEL_SL1) / 10000000) + 0.01f;
		}
	}
	g_angle = Player_GetRotation();
}

void Tornado_Draw()
{
	D3DXMATRIX mtxW, mtxR, mtxT, mtxS;
	D3DXMatrixRotationY(&mtxR, g_angle);
	D3DXMatrixTranslation(&mtxT, g_pos.x, g_pos.y, g_pos.z);
	D3DXMatrixScaling(&mtxS, g_scale, g_scale, g_scale);
	mtxW = mtxR * mtxS * mtxT;
	Model_Draw(&mtxW, g_ModelID);
}