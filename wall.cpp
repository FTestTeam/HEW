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
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},
	//{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	//{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},

	//右側面
	{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},
	{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},
	//{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	//{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},

	//左側面
	{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},
	//{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),	D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	//{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},

	//後面
	{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},
	{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	//{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.25f)},
	//{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},

	//下面
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.5f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	//{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.5f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	//{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},

	//上面
	{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	//{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.5f)},
	//{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
};

static int g_textureID = 0;
static bool g_WallUse = true;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;
static D3DXVECTOR3 g_pos;

void Wall_Init(void)
{
	g_textureID=Texture_SetLoadFile("Asset/Texture/spice_and_wolf.png", 1024, 1024);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(Wall_Vertex) * 24, D3DUSAGE_WRITEONLY, FVF_WALL, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	//(Length=借りるメモリの大きさ , usage=D3DUSAGE_WRITEONLYにしておけ , FVF , pool=D3DPOOL_MANAGED , VertexBufferのアドレス,NULL)

	//indexbuffer
	pDevice->CreateIndexBuffer(sizeof(WORD) * 36, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	int j = 0;
	for (int i = 0 ; i < 36; i += 6 ) {
		pIndex[0 + i] = 0 + j;
		pIndex[1 + i] = 1 + j;
		pIndex[2 + i] = 2 + j;
		pIndex[3 + i] = 1 + j;
		pIndex[4 + i] = 3 + j;
		pIndex[5 + i] = 2 + j;
		j += 4;
	}
	g_pIndexBuffer->Unlock();

	Wall_Vertex *pV;	//仮想アドレス　g_VertexBuffer->Unlock()を呼ぶともう使えない
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//(ロックする初めのアドレス,どこまでロックするか？　0にすると全部,CPUにVRAMの仮想アドレスを作る (void**)&pV , D3DLOCK_DISCARD)
	memcpy(pV, g_wall_vertex, sizeof(g_wall_vertex));
	g_VertexBuffer->Unlock();

	g_pos = { 0.0f,0.0f,20.0f };
}

void Wall_UnInit(void)
{
	g_pIndexBuffer->Release();
	g_VertexBuffer->Release();
}

void Wall_Update(void) 
{
	
}

void Wall_Draw(void)
{
	if (g_WallUse)
	{
		LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

		pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//ディフューズマテリアルは頂点カラー

		D3DXMATRIX mtxWorld, mtxRotation, mtxTranslation, mtxTranslation_Center, mtxScaling;
		D3DXMatrixTranslation(&mtxTranslation_Center, 0.0, 0.0, 0.5);//壁：手前の面の下辺中央を中心に変更
		D3DXMatrixTranslation(&mtxTranslation, g_pos.x, g_pos.y, g_pos.z);//壁の座標変更
		D3DXMatrixScaling(&mtxScaling, 4.0f, 12.0f, 0.4f);//壁の拡大率
		mtxWorld = mtxTranslation_Center * mtxScaling * mtxTranslation;
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Wall_Vertex));
		pDevice->SetIndices(g_pIndexBuffer);

		pDevice->SetFVF(FVF_WALL);
		pDevice->SetTexture(0, Texture_GetTexture(g_textureID));
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 36);
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