#include<d3dx9.h>
#include"texture.h"
#include"cube.h"
#include"model.h"
#include"hammer.h"
#include"meshfield.h"
#include"debug_font.h"
#include"mydirect3d.h"

#define HOUSE_MAX (10)

enum MODEL_NUM {
	MODEL_BUILD1,
	MODEL_BUILD2,
	MODEL_BUILD3,
	MODEL_711,
	MODEL_MAX,
};
static const char *g_ModelName[MODEL_MAX]{
	"Asset/Model/build1.x",
	"Asset/Model/build2.x",
	"Asset/Model/build3.x",
	"Asset/Model/7-11.x",
};

typedef struct STAGE_Tag {
	D3DXVECTOR3 Position;
	float scale;
	float angle;
	MODEL_NUM Model;
}OBJECT;

static D3DXVECTOR3 g_FloorPos;
static int g_TextureID_Floor;

static D3DXVECTOR3 g_SekiPos[2];
static int g_ModelID_Seki;

static float g_FieldZ[3];

static const OBJECT g_House[]
{
	{D3DXVECTOR3(-30.0f,0.3f,100.0f),0.3f,0.0f,MODEL_711},
	{D3DXVECTOR3(30.0f,0.3f,100.0f),0.3f,0.0f,MODEL_BUILD1},
	{D3DXVECTOR3(-30.0f,0.3f,150.0f),0.3f,0.0f,MODEL_BUILD2},
	{D3DXVECTOR3(30.0f,0.3f,150.0f),0.3f,0.0f,MODEL_BUILD3},
	{D3DXVECTOR3(50.0f,0.3f,150.0f),0.3f,0.0f,MODEL_711},
};

void Stage_Init()
{
	MeshField_Init(300, 100);

	
	g_FloorPos = { 0.0f,0.0f,15.0f };
	g_TextureID_Floor = Texture_SetLoadFile("Asset/Texture/S__20209690.jpg", 0, 0);
	
	
	for (int i = 0; i < MODEL_MAX; i++) {
		Model_SetLoadFile(g_ModelName[i]);
	}
	
	
	g_SekiPos[0] = { -20.0f,4.0f,20.0f };
	g_SekiPos[1] = { 20.0f,4.0f,20.0f };
	g_ModelID_Seki = Model_SetLoadFile("Asset/Model/seki.x");
	
	
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
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX mtx,mtxT,mtxS,mtxR;

	D3DXMatrixTranslation(&mtxT, g_FloorPos.x, g_FloorPos.y, g_FloorPos.z);
	D3DXMatrixScaling(&mtxS, 50.0f, 0.0f, 50.0f);
	D3DXMatrixRotationX(&mtxR, D3DXToRadian(90));
	mtx = mtxR * mtxS * mtxT;
	Cube_Draw(&mtx, g_TextureID_Floor);
	
	
	D3DXMatrixTranslation(&mtxT, g_SekiPos[0].x, g_SekiPos[0].y, g_SekiPos[0].z);
	D3DXMatrixScaling(&mtxS, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&mtxR, D3DXToRadian(45));
	mtx = mtxS * mtxR * mtxT;
	Model_Draw(&mtx,g_ModelID_Seki);

	D3DXMatrixTranslation(&mtxT, g_SekiPos[1].x, g_SekiPos[1].y, g_SekiPos[1].z);
	D3DXMatrixScaling(&mtxS, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&mtxR, D3DXToRadian(135));
	mtx = mtxS * mtxR * mtxT;
	Model_Draw(&mtx, g_ModelID_Seki);
	
	
	int objNum = sizeof(g_House) / sizeof(g_House[0]);

	if (Hammer_GetPosition().z > g_FieldZ[0] + 150.0f) {
		g_FieldZ[0] += 300.0f;
	}
	for (int i = 0; i < objNum; i++) {
		D3DXMatrixTranslation(&mtxT, g_House[i].Position.x, g_House[i].Position.y, g_House[i].Position.z + g_FieldZ[0]);
		D3DXMatrixScaling(&mtxS, g_House[i].scale, g_House[i].scale, g_House[i].scale);
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(g_House[i].angle));
		mtx = mtxS * mtxR * mtxT;
		Model_Draw(&mtx, Model_SetLoadFile(g_ModelName[g_House[i].Model]));
	}
	D3DXMatrixTranslation(&mtxT, 0.0f, 0.0f, g_FieldZ[0]);
	mtx = mtxT;
	MeshField_Draw(&mtx);

	if (Hammer_GetPosition().z > g_FieldZ[1] + 150.0f) {
		g_FieldZ[1] += 300.0f;
	}
	for (int i = 0; i < objNum; i++) {
		D3DXMatrixTranslation(&mtxT, g_House[i].Position.x, g_House[i].Position.y, g_House[i].Position.z + g_FieldZ[1]);
		D3DXMatrixScaling(&mtxS, g_House[i].scale, g_House[i].scale, g_House[i].scale);
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(g_House[i].angle));
		mtx = mtxS * mtxR * mtxT;
		Model_Draw(&mtx, Model_SetLoadFile(g_ModelName[g_House[i].Model]));
	}
	D3DXMatrixTranslation(&mtxT, 0.0f, 0.0f, g_FieldZ[1]);
	mtx = mtxT;
	MeshField_Draw(&mtx);

	if (Hammer_GetPosition().z > g_FieldZ[2] + 150.0f) {
		g_FieldZ[2] += 300.0f;
	}
	for (int i = 0; i < objNum; i++) {
		D3DXMatrixTranslation(&mtxT, g_House[i].Position.x, g_House[i].Position.y, g_House[i].Position.z + g_FieldZ[2]);
		D3DXMatrixScaling(&mtxS, g_House[i].scale, g_House[i].scale, g_House[i].scale);
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(g_House[i].angle));
		mtx = mtxS * mtxR * mtxT;
		Model_Draw(&mtx, Model_SetLoadFile(g_ModelName[g_House[i].Model]));
	}
	D3DXMatrixTranslation(&mtxT, 0.0f, 0.0f, g_FieldZ[2]);
	mtx = mtxT;
	MeshField_Draw(&mtx);
}