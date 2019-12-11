#include<d3d9.h>
#include<d3dx9.h>
#include"mydirect3d.h"
#include"common.h"
#include"input.h"
#include"texture.h"

typedef struct WallVertex_tag
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;		//法線ベクトル	座標の次カラーの前
	D3DCOLOR	color;
	D3DXVECTOR2	uv;
}Wall_Vertex;
#define FVF_WALL (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)


static Wall_Vertex g_wall_vertex[] = {
	//前面
	{D3DXVECTOR3(-0.5f,0.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR3(0.5f,0.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
};

static int g_textureID = 0;
static bool g_WallUse = true;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;
static D3DXVECTOR3 g_pos;

void Wall_Init(void)
{
	g_textureID=Texture_SetLoadFile("Asset/Texture/koku-nn.png", 1024, 1024);

	g_pos = { 0.0f,-1.0f,30.0f };
	g_WallUse = true;

	for (int i = 0; i < 4; i++) {
		g_wall_vertex[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}

void Wall_UnInit(void)
{

}

void Wall_Update(void) 
{
	for (int i = 0; i < 4; i++) {
		D3DXCOLOR color = g_wall_vertex[i].color;
		if (color.a <= 0) {
			g_WallUse = false;
		}
	}
}

void Wall_Draw(void)
{
	if (g_WallUse)
	{
		LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

		pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//ディフューズマテリアルは頂点カラー

		D3DXMATRIX mtxWorld, mtxRotation, mtxTranslation, mtxTranslation_Center, mtxScaling;
		D3DXMatrixTranslation(&mtxTranslation_Center, 0.0f, 0.5f, 0.0f);//壁：手前の面の下辺中央を中心に変更
		D3DXMatrixTranslation(&mtxTranslation, g_pos.x, g_pos.y, g_pos.z);//壁の座標変更
		D3DXMatrixScaling(&mtxScaling, 8.0f, 8.0f, 8.0f);//壁の拡大率
		mtxWorld = mtxTranslation_Center * mtxScaling * mtxTranslation;
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		pDevice->SetFVF(FVF_WALL);
		pDevice->SetTexture(0, Texture_GetTexture(g_textureID));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,g_wall_vertex,sizeof(g_wall_vertex[0]));
	}
}

void Wall_Delete(void)
{
	g_WallUse = false;
}

D3DXVECTOR3 Wall_GetPosition(void)
{
	return g_pos;
}

void Wall_MinAlpha(float n)
{
	for (int i = 0; i < 4; i++) {
		D3DXCOLOR color = g_wall_vertex[i].color;
		color.a -= n;
		g_wall_vertex[i].color = color;
	}
}

bool Wall_isUse() 
{
	return g_WallUse;
}

D3DXCOLOR Wall_GetColor()
{
	return g_wall_vertex[0].color;
}