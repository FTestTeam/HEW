#include<d3dx9.h>
#include"texture.h"
#include"cube.h"
#include"model.h"
#include"hammer.h"
#include"meshfield.h"
#include"debug_font.h"

#define HOUSE_MAX (10)

typedef struct STAGE_Tag {
	D3DXVECTOR3 Position;
	int TextureID;
}STAGE;

static STAGE g_Floor;
static STAGE g_Kannkyaku;
static STAGE g_House[HOUSE_MAX];

static float g_FieldZ[3];

void Stage_Init()
{
	MeshField_Init(300, 100);

	g_Floor.Position = {0.0f,0.0f,15.0f};
	g_Floor.TextureID = Texture_SetLoadFile("Asset/Texture/S__20209690.jpg", 0, 0);

	g_Kannkyaku.Position = { -15.0f,0.0f,30.0f };
	g_Kannkyaku.TextureID = Texture_SetLoadFile("Asset/Texture/kannkyaku.jpg", 0, 0);

	for (int i = 0; i < HOUSE_MAX; i++) {
		g_House[i].TextureID = -1;
	}

	g_House[0].TextureID = Model_SetLoadFile("Asset/Model/build3.x");
	g_House[1].TextureID = Model_SetLoadFile("Asset/Model/build1.x");
	g_House[2].TextureID = Model_SetLoadFile("Asset/Model/7-11.x");
	

	g_House[0].Position = { -30.0f,0.3f,100.0f };
	g_House[1].Position = { 30.0f,0.3f,100.0f };
	g_House[2].Position = { -30.0f,0.3f,150.0f };
	

	g_FieldZ[0] = 0.0f;
	g_FieldZ[1] = 100.0f;
	g_FieldZ[2] = 200.0f;
}

void Stage_UnInit()
{
	MeshField_UnInit();
}

void Stage_Update()
{
	MeshField_Update();
}

void Stage_Draw()
{
	D3DXMATRIX mtx,mtxST,mtxT,mtxS,mtxR;
	D3DXMatrixTranslation(&mtxT, g_Floor.Position.x, g_Floor.Position.y, g_Floor.Position.z);
	D3DXMatrixScaling(&mtxS, 50.0f, 0.0f, 50.0f);
	D3DXMatrixRotationX(&mtxR, D3DXToRadian(90));
	mtx = mtxR * mtxS * mtxT;
	Cube_Draw(&mtx, g_Floor.TextureID);

	if (Hammer_GetPosition().z > g_FieldZ[0] + 100.0f) {
		g_FieldZ[0] += 300.0f;
	}
	D3DXMatrixTranslation(&mtxT, 0.0f, 0.0f, g_FieldZ[0]);
	mtx = mtxT;
	MeshField_Draw(&mtx);

	if (Hammer_GetPosition().z > g_FieldZ[1] + 100.0f) {
		g_FieldZ[1] += 300.0f;
	}
	D3DXMatrixTranslation(&mtxT, 0.0f, 0.0f, g_FieldZ[1]);
	mtx = mtxT;
	MeshField_Draw(&mtx);

	if (Hammer_GetPosition().z > g_FieldZ[2] + 100.0f) {
		g_FieldZ[2] += 300.0f;
	}
	D3DXMatrixTranslation(&mtxT, 0.0f, 0.0f, g_FieldZ[2]);
	mtx = mtxT;
	MeshField_Draw(&mtx);

	for (int i = 0; i < HOUSE_MAX; i++) {
		if (g_House[i].TextureID < 0) continue;
		D3DXMatrixTranslation(&mtxT, g_House[i].Position.x, g_House[i].Position.y, g_House[i].Position.z);
		D3DXMatrixScaling(&mtxS, 0.3f, 0.3f, 0.3f);
		mtx = mtxS * mtxT;
		Model_Draw(&mtx, g_House[i].TextureID);
	}

	//D3DXMatrixTranslation(&mtxST, 0.0f, 0.5f, 0.0f);
	//D3DXMatrixTranslation(&mtxT, g_Kannkyaku.Position.x, g_Kannkyaku.Position.y, g_Kannkyaku.Position.z);
	//D3DXMatrixScaling(&mtxS, 30.0f, 15.0f, 1.0f);
	//D3DXMatrixRotationY(&mtxR, D3DXToRadian(-45));
	//mtx =mtxST * mtxS * mtxR * mtxT;
	//Cube_Draw(&mtx, g_Kannkyaku.TextureID);
}