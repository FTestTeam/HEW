#include<d3dx9.h>
#include"texture.h"
#include"cube.h"

typedef struct STAGE_Tag {
	D3DXVECTOR3 Position;
	int TextureID;
}STAGE;

static STAGE g_Floor;
static STAGE g_Sky;

void Stage_Init()
{
	g_Floor.Position = {0.0f,0.0f,15.0f};
	g_Floor.TextureID = Texture_SetLoadFile("Asset/Texture/S__20209690.jpg", 0, 0);

	g_Sky.Position = { 0.0f,15.0f,0.0f };
	g_Sky.TextureID = Texture_SetLoadFile("Asset/Texture/th6EMS6ZVG.jpg", 0, 0);
}

void Stage_UnInit()
{

}

void Stage_Update()
{

}

void Stage_Draw()
{
	D3DXMATRIX mtx,mtxT,mtxS,mtxR;
	D3DXMatrixTranslation(&mtxT, g_Floor.Position.x, g_Floor.Position.y, g_Floor.Position.z);
	D3DXMatrixScaling(&mtxS, 50.0f, 0.0f, 50.0f);
	D3DXMatrixRotationX(&mtxR, D3DXToRadian(90));
	mtx = mtxR * mtxS * mtxT;
	Cube_Draw(&mtx, g_Floor.TextureID);

	/*D3DXMatrixTranslation(&mtxT, g_Sky.Position.x, g_Sky.Position.y, g_Sky.Position.z);
	D3DXMatrixScaling(&mtxS, 500.0f, 0.0f, 500.0f);
	mtx = mtxR * mtxS * mtxT;
	Cube_Draw(&mtx, g_Sky.TextureID);*/
}