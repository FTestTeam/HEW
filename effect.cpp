#include<d3d9.h>
#include<d3dx9.h>
#include"texture.h"
#include"billboard.h"
#include"mydirect3d.h"
#include"Scene.h"

#define EFFECT_TEXTURE_SIZE_W (80)
#define EFFECT_TEXTURE_SIZE_H (80)
#define EFFECT_MAX (6400)

typedef struct EFFECT_tag
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
	int life;
	int BirthFrame;
	float scale;
}EFFECT;

static int g_TextureID;
static int g_Flame;
static EFFECT g_effect[EFFECT_MAX];

void Effect_Init(void) 
{
	g_TextureID = Texture_SetLoadFile("Asset/Texture/effect.jpg", EFFECT_TEXTURE_SIZE_W, EFFECT_TEXTURE_SIZE_H);
	for (int i = 0; i < EFFECT_MAX; i++) {
		g_effect[i].life = 0;
		g_effect[i].BirthFrame = 0;
		g_effect[i].scale = 1.0f;
	}
}

void Effect_UnInit(void) 
{

}

void Effect_Update(void) 
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (g_effect[i].life == 0) {
			continue;
		}

		int age = g_Flame - g_effect[i].BirthFrame;	//何フレーム生きているかが出る

		//生死判定
		if (g_effect[i].life <= age) {
			g_effect[i].life = 0;
			g_effect[i].BirthFrame = 0;
			continue;	//この死んだi番目はこれ以降やることがないからcontinue
		}

		//色調節　RGB*αなのでαを調節すれば全部変わる
		float e = age / (float)g_effect[i].life;
		D3DXCOLOR color = g_effect[i].color;
		color.a = 1-e;
		g_effect[i].color = color;
	}

	g_Flame++;
}

void Effect_Draw(void) 
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	D3DXMATRIX mtxW, mtxT, mtxS;

	if (Scene_GetScene() == SCENE_ZAKO || Scene_GetScene() == SCENE_REPLAY_ZAKO) {
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (g_effect[i].life == 0) {
				continue;
			}

			D3DXMatrixTranslation(&mtxT, g_effect[i].position.x, g_effect[i].position.y, g_effect[i].position.z);
			D3DXMatrixScaling(&mtxS, g_effect[i].scale, g_effect[i].scale, g_effect[i].scale);
			mtxW = mtxS * mtxT;
			Billboard_SetColor(g_effect[i].color);
			Billboard_Draw(&mtxW, g_TextureID);
		}
	}

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

void Effect_Create(D3DXVECTOR3 pos, D3DCOLOR color, int life,float size)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (g_effect[i].life != 0) {
			continue;
		}
		g_effect[i].position = pos;
		g_effect[i].color = color;
		g_effect[i].life = life;
		g_effect[i].BirthFrame = g_Flame;
		g_effect[i].scale = size;
		break;
	}
}
