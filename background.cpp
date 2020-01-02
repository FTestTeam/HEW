#include<d3dx9.h>
#include<d3d9.h>
#include"mydirect3d.h"
#include"texture.h"
#include"DebugPrintf.h"

typedef struct BG_Tag {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR	color;
	D3DXVECTOR2	uv;
}BG_Vertex;
#define FVF_BG (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//static BG_Vertex *g_BG_vertex;
static int g_textureID;

static int g_BG_VertexNum;
static int g_BG_PRIM;

static LPDIRECT3DINDEXBUFFER9	g_pIndexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9	g_VertexBuffer = NULL;

void BackGround_Init(int BG_W, int BG_H, float w, float h)
{
	int BG_INDEX = (((BG_W * 2 + 2) * BG_H) + (BG_H - 1) * 2);	//全体のインデックスの数
	g_BG_VertexNum = ((BG_W + 1)*(BG_H + 1));				//頂点数
	g_BG_PRIM = (BG_INDEX - 2);		//全体のプリミティブ数

	g_textureID = Texture_SetLoadFile("Asset/Texture/th6EMS6ZVG.jpg", 0, 0);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//uv参照外の場合繰り返す設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//課題用　ワイヤーフレーム
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(BG_Vertex) * 4, D3DUSAGE_WRITEONLY, FVF_BG, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	BG_Vertex *g_BG_vertex = new BG_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_BG_vertex, D3DLOCK_DISCARD);
	//頂点を並べる	billboard
	int VertexCount = 0;
	g_BG_vertex[0].position = { -800.0f,800.0f,500.0f };
	g_BG_vertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	g_BG_vertex[1].position = {  800.0f,800.0f,500.0f };
	g_BG_vertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	g_BG_vertex[2].position = {  800.0f,-100.0f,500.0f };
	g_BG_vertex[2].uv = D3DXVECTOR2(0.0f, 1.0f);
	g_BG_vertex[3].position = { -800.0f,-100.0f,500.0f };
	g_BG_vertex[3].uv = D3DXVECTOR2(1.0f, 1.0f);

	for (int i = 0; i < 4; i++) {
		g_BG_vertex[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_BG_vertex[i].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}
	g_VertexBuffer->Unlock();

	//インデックスバッファ
	pDevice->CreateIndexBuffer(sizeof(WORD) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 3;
	g_pIndexBuffer->Unlock();
}

void BackGround_UnInit()
{
	g_pIndexBuffer->Release();
	g_VertexBuffer->Release();
}

void BackGround_Update()
{

}

void BackGround_Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(BG_Vertex));
	pDevice->SetIndices(g_pIndexBuffer);

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	pDevice->SetTransform(D3DTS_WORLD, &mtx);
	pDevice->SetFVF(FVF_BG);

	pDevice->SetTexture(0, Texture_GetTexture(g_textureID));
	//課題用　ワイヤーフレームにした時テクスチャ張らないほうが見やすかった
	//pDevice->SetTexture(0, NULL);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 3);
	
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}