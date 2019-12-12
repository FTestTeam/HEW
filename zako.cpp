#include<d3d9.h>
#include<d3dx9.h>
#include"mydirect3d.h"
#include"common.h"
#include"input.h"
#include"texture.h"
#include"cube.h"
#include"zako.h"
#include"player.h"
#include"hammer.h"
#include"mic.h"
#include"Scene.h"
#include"score.h"

#define ZAKO_SCENE_CHANGE_FREAM (120)
#define ZAKO_STRIDE (5.0f)

typedef struct ZakoData_tag
{
	D3DXVECTOR3 position;
	bool use;
	bool bLast;
	int zSort;
}ZakoData;
static ZakoData g_ZakoData[ZAKO_MAX];

static int g_textureID = 0;
static D3DXVECTOR3 g_pos;
static bool g_bFly;
static int g_BreakCount;

static bool g_bScene;
static int g_SceneFream;

void Zako_Init(void)
{
	g_bFly = true;
	g_BreakCount = 0;

	g_bScene = false;
	g_SceneFream = ZAKO_SCENE_CHANGE_FREAM;

	//テクスチャの設定
	g_textureID = Texture_SetLoadFile("Asset/Texture/koku-nn.png", 1024, 1024);
	//初期化
	for (int i = 0; i < ZAKO_MAX; i++)
	{
		g_ZakoData[i].use = true;
		g_ZakoData[i].position = { 0.0f,-1.0f,(ZAKO_STRIDE*i) + 30.0f };
		g_ZakoData[i].bLast = i == ZAKO_MAX - 1;
		g_ZakoData[i].zSort = i;
	}
}

void Zako_UnInit(void)
{

}

void Zako_Update(void)
{
	for (int Id = 0; Id < ZAKO_MAX; Id++)
	{
		if (!g_ZakoData[Id].use) {
			for (int j = 0; j < ZAKO_MAX; j++) {
				if (!g_ZakoData[j].bLast) {
					continue;
				}
				g_ZakoData[Id].position = g_ZakoData[j].position;
				g_ZakoData[Id].position.z += ZAKO_STRIDE;
				g_ZakoData[Id].bLast = true;
				g_ZakoData[j].bLast = false;
				break;
			}
			g_ZakoData[Id].use = true;
		}

		if (Mic_GetVolume() < 10) {
			if (Zako_GetPosition(Id).z-1.0f < Hammer_GetPosition().z && Zako_GetPosition(Id).z + 0.3f > Hammer_GetPosition().z) {
				Hammer_Stop();
				g_bScene = true;
			}
		}
		else if (Hammer_IsFly()) {
			if (Zako_GetPosition(Id).z < Hammer_GetPosition().z) {
				if (g_ZakoData[Id].use) {
					g_BreakCount++;
					Score_AddScore(1);
				}
				g_ZakoData[Id].use = false;
			}
		}
	}

	int rank = 0;
	g_ZakoData[0].zSort = rank;
	for (int i = 0; i < ZAKO_MAX; i++) {
		for (int j=1; j<ZAKO_MAX; j++) {
			if (g_ZakoData[i].position.z > g_ZakoData[j].position.z) {
				g_ZakoData[i].zSort = rank;
				rank++;
			}
		}
	}

	if (g_bScene) {
		g_SceneFream--;
	}

	//if (g_SceneFream < 0) {
	//	Scene_SetNextScene(SCENE_RAID);
	//}
}

void Zako_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	for (int i = 0; i < ZAKO_MAX; i++)
	{

		if (g_ZakoData[i].use)
		{
			D3DXMATRIX mtxWorld, mtxRotation, mtxTranslation, mtxTranslation_Center, mtxScaling;
			D3DXMatrixTranslation(&mtxTranslation_Center, 0.0, 0.5, 0.5);//壁：手前の面の下辺中央を中心に変更
			D3DXMatrixTranslation(&mtxTranslation, g_ZakoData[i].position.x, g_ZakoData[i].position.y, g_ZakoData[i].position.z);//壁の座標変更
			D3DXMatrixScaling(&mtxScaling, 8.0f, 8.0f, 1.0f);//壁の拡大率
			mtxWorld = mtxTranslation_Center * mtxScaling * mtxTranslation;
			Cube_Draw(&mtxWorld, g_textureID);
		}
	}
}

void Zako_Delete(int Id)
{
	g_ZakoData[Id].use = false;
}

D3DXVECTOR3 Zako_GetPosition(int Id)
{
	return g_ZakoData[Id].position;
}

int Zako_GetBreakCount(void)
{
	return g_BreakCount;
}