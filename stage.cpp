#include<d3dx9.h>
#include"texture.h"
#include"cube.h"
#include"model.h"

#define HOUSE_MAX (10)

typedef struct STAGE_Tag {
	D3DXVECTOR3 Position;
	int TextureID;
}STAGE;

static STAGE g_Floor;
static STAGE g_Kannkyaku;
static STAGE g_House[HOUSE_MAX];

void Stage_Init()
{
	g_Floor.Position = {0.0f,0.0f,15.0f};
	g_Floor.TextureID = Texture_SetLoadFile("Asset/Texture/S__20209690.jpg", 0, 0);

	g_Kannkyaku.Position = { -15.0f,0.0f,30.0f };
	g_Kannkyaku.TextureID = Texture_SetLoadFile("Asset/Texture/kannkyaku.jpg", 0, 0);

	for (int i = 0; i < HOUSE_MAX; i++) {
		g_House[i].TextureID = Model_SetLoadFile("Asset/Model/tatemono.x");
	}

	for (int i = 0; i < HOUSE_MAX; i++) {
		g_House[i].Position = { -10.0f,0.3f,10.0f + i * 10.0f };
	}
}

void Stage_UnInit()
{

}

void Stage_Update()
{

}

void Stage_Draw()
{
	D3DXMATRIX mtx,mtxST,mtxT,mtxS,mtxR;
	D3DXMatrixTranslation(&mtxT, g_Floor.Position.x, g_Floor.Position.y, g_Floor.Position.z);
	D3DXMatrixScaling(&mtxS, 50.0f, 0.0f, 50.0f);
	D3DXMatrixRotationX(&mtxR, D3DXToRadian(90));
	mtx = mtxR * mtxS * mtxT;
	Cube_Draw(&mtx, g_Floor.TextureID);

	for (int i = 0; i < HOUSE_MAX; i++) {
		D3DXMatrixTranslation(&mtxT, g_House[i].Position.x, g_House[i].Position.y, g_House[i].Position.z);
		mtx = mtxT;
		Model_Draw(&mtx, g_House[i].TextureID);
	}

	//D3DXMatrixTranslation(&mtxST, 0.0f, 0.5f, 0.0f);
	//D3DXMatrixTranslation(&mtxT, g_Kannkyaku.Position.x, g_Kannkyaku.Position.y, g_Kannkyaku.Position.z);
	//D3DXMatrixScaling(&mtxS, 30.0f, 15.0f, 1.0f);
	//D3DXMatrixRotationY(&mtxR, D3DXToRadian(-45));
	//mtx =mtxST * mtxS * mtxR * mtxT;
	//Cube_Draw(&mtx, g_Kannkyaku.TextureID);
}