#include<d3d9.h>
#include<d3dx9.h>
#include"common.h"
#include"model.h"
#include"hammer.h"
#include"joycon.h"
#include"cube.h"

typedef struct PLAYER_Tag{
	LocalVecter LocalVec;
	D3DXVECTOR3 Position;
	int ModelId;
}PLAYER;

static PLAYER g_Player;

void Player_Init() 
{
	Cube_Init();

	g_Player.Position = {0.0f,0.0f,0.0f};
	g_Player.LocalVec.Front = { 0.0f, 0.0f, -1.0f };
	g_Player.ModelId = Model_SetLoadFile("Asset/Model/gradriel.x");

	D3DXVECTOR3 w = g_Player.Position + g_Player.LocalVec.Front * 1.5f;
	Hammer_SetPosition(w);
}

void Player_UnInit()
{
	Cube_UnInit();
}

void Player_Update()
{

}

static float g_fream;

void Player_Draw()
{
	g_fream += 0.3f;
	D3DXMATRIX mtx,mtxW,mtxR,mtxRT;
	D3DXMatrixTranslation(&mtxRT ,-0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationY(&mtxR, g_fream);
	D3DXMatrixTranslation(&mtx,0.0f,0.5f,0.0f);
	mtxW =mtxRT * mtxR * mtx;
	Cube_Draw(&mtxW);
}

D3DXVECTOR3 Player_GetFront(void)
{
	return g_Player.LocalVec.Front;
}