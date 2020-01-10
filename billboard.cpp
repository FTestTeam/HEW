#include<d3d9.h>
#include<d3dx9.h>
#include"mydirect3d.h"
#include"common.h"
#include"camera.h"
#include"texture.h"

typedef struct BillVertex_tag
{
	D3DXVECTOR3 position;
	D3DCOLOR	color;
	D3DXVECTOR2	uv;
}Bill_Vertex;
#define FVF_BILL (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//static Bill_Vertex g_bill_vertex[4];

static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;

void Billboard_Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(Bill_Vertex) * 4, D3DUSAGE_WRITEONLY, FVF_BILL, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	//(Length=借りるメモリの大きさ , usage=D3DUSAGE_WRITEONLYにしておけ , FVF , pool=D3DPOOL_MANAGED , VertexBufferのアドレス,NULL)

	//indexbuffer
	pDevice->CreateIndexBuffer(sizeof(WORD) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 3;
	g_pIndexBuffer->Unlock();

	Bill_Vertex* g_bill_vertex = new Bill_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_bill_vertex, D3DLOCK_DISCARD);//(ロックする初めのアドレス,どこまでロックするか？　0にすると全部,CPUにVRAMの仮想アドレスを作る (void**)&pV , D3DLOCK_DISCARD)
	g_bill_vertex[0] = { D3DXVECTOR3(-0.5f,0.5f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)};
	g_bill_vertex[1] = { D3DXVECTOR3(0.5f,0.5f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) };
	g_bill_vertex[2] = { D3DXVECTOR3(-0.5f,-0.5f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) };
	g_bill_vertex[3] = { D3DXVECTOR3(0.5f,-0.5f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) };
	g_VertexBuffer->Unlock();
}

void Billboard_UnInit(void)
{
	g_pIndexBuffer->Release();
	g_VertexBuffer->Release();
}

void Billboard_Update(void)
{
	
}

void Billboard_Draw(const D3DXMATRIX *mtx,int TextureID)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//ディフューズマテリアルは頂点カラー
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	D3DXMATRIX mtxW;
	mtxW = Camera_GetmtxViewInv() * *mtx;

	pDevice->SetTransform(D3DTS_WORLD, &mtxW);

	pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Bill_Vertex));
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->SetFVF(FVF_BILL);
	pDevice->SetTexture(0, Texture_GetTexture(TextureID));
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

	Bill_Vertex* g_bill_vertex = new Bill_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_bill_vertex, D3DLOCK_DISCARD);//(ロックする初めのアドレス,どこまでロックするか？　0にすると全部,CPUにVRAMの仮想アドレスを作る (void**)&pV , D3DLOCK_DISCARD)
	g_bill_vertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	g_bill_vertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	g_bill_vertex[2].uv = D3DXVECTOR2(0.0f, 1.0f);
	g_bill_vertex[3].uv = D3DXVECTOR2(1.0f, 1.0f);
	g_bill_vertex[0].color = D3DCOLOR_RGBA(255,255,255,255);
	g_bill_vertex[1].color = D3DCOLOR_RGBA(255,255,255,255);
	g_bill_vertex[2].color = D3DCOLOR_RGBA(255,255,255,255);
	g_bill_vertex[3].color = D3DCOLOR_RGBA(255,255,255,255);
	g_VertexBuffer->Unlock();

}

void Billboard_SetUV()
{
	Bill_Vertex* g_bill_vertex = new Bill_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_bill_vertex, D3DLOCK_DISCARD);//(ロックする初めのアドレス,どこまでロックするか？　0にすると全部,CPUにVRAMの仮想アドレスを作る (void**)&pV , D3DLOCK_DISCARD)
	g_bill_vertex[0].uv = D3DXVECTOR2(0.0f,0.0f);
	g_bill_vertex[1].uv = D3DXVECTOR2(1.0f,0.0f);
	g_bill_vertex[2].uv = D3DXVECTOR2(0.0f,1.0f);
	g_bill_vertex[3].uv = D3DXVECTOR2(1.0f,1.0f);
	g_VertexBuffer->Unlock();
}

void Billboard_SetUV(float CutX,float CutY,float CutW,float CutH,int TextureID)
{
	int w = Texture_GetWidth(TextureID);
	int h = Texture_GetHeight(TextureID);

	float u0 = CutX / (float)w;
	float v0 = CutY / (float)h;
	float u1 = (CutX + CutW) / (float)w;
	float v1 = (CutY + CutH) / (float)h;

	Bill_Vertex* g_bill_vertex = new Bill_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_bill_vertex, D3DLOCK_DISCARD);//(ロックする初めのアドレス,どこまでロックするか？　0にすると全部,CPUにVRAMの仮想アドレスを作る (void**)&pV , D3DLOCK_DISCARD)
	g_bill_vertex[0].uv = D3DXVECTOR2(u0, v0);
	g_bill_vertex[1].uv = D3DXVECTOR2(u1, v0);
	g_bill_vertex[2].uv = D3DXVECTOR2(u0, v1);
	g_bill_vertex[3].uv = D3DXVECTOR2(u1, v1);
	g_VertexBuffer->Unlock();
}

void Billboard_SetColor(D3DCOLOR color)
{
	Bill_Vertex* g_bill_vertex = new Bill_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_bill_vertex, D3DLOCK_DISCARD);//(ロックする初めのアドレス,どこまでロックするか？　0にすると全部,CPUにVRAMの仮想アドレスを作る (void**)&pV , D3DLOCK_DISCARD)
	g_bill_vertex[0].color = color;
	g_bill_vertex[1].color = color;
	g_bill_vertex[2].color = color;
	g_bill_vertex[3].color = color;
	g_VertexBuffer->Unlock();
}