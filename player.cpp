#include<d3d9.h>
#include<d3dx9.h>
#include"common.h"
#include"model.h"
#include"hammer.h"

typedef struct PLAYER_Tag{
	LocalVecter LocalVec;
	D3DXVECTOR3 Position;
	int ModelId;
}PLAYER;

static PLAYER g_Player;

void Player_Init() 
{
	g_Player.Position = {0.0f,0.0f,0.0f};
	g_Player.LocalVec.Front = { 0.0f, 0.0f, -1.0f };
	g_Player.ModelId = Model_SetLoadFile("Asset/Model/gradriel.x");

	D3DXVECTOR3 w = g_Player.Position + g_Player.LocalVec.Front * 1.5f;
	Hammer_SetPosition(w);
}

void Player_UnInit()
{

}

void Player_Update()
{

}

void Player_Draw()
{
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	Model_Draw(&mtx, g_Player.ModelId);
}