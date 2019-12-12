#include<d3dx9.h>
#include"texture.h"
#include"cube.h"

typedef struct STAGE_Tag {
	D3DXVECTOR3 Position;
	int TextureID;
}STAGE;

static STAGE g_Floor;
static STAGE g_Kannkyaku;

void Stage_Init()
{
	g_Floor.Position = {0.0f,0.0f,15.0f};
	g_Floor.TextureID = Texture_SetLoadFile("Asset/Texture/S__20209690.jpg", 0, 0);

	g_Kannkyaku.Position = { -15.0f,0.0f,30.0f };
	g_Kannkyaku.TextureID = Texture_SetLoadFile("Asset/Texture/kannkyaku.jpg", 0, 0);
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

	/*D3DXMatrixTranslation(&mtxST, 0.0f, 0.5f, 0.0f);
	D3DXMatrixTranslation(&mtxT, g_Kannkyaku.Position.x, g_Kannkyaku.Position.y, g_Kannkyaku.Position.z);
	D3DXMatrixScaling(&mtxS, 30.0f, 15.0f, 1.0f);
	D3DXMatrixRotationY(&mtxR, D3DXToRadian(-45));
	mtx =mtxST * mtxS * mtxR * mtxT;
	Cube_Draw(&mtx, g_Kannkyaku.TextureID);*/
}