#include<d3d9.h>
#include<d3dx9.h>
#include"mydirect3d.h"
#include"common.h"
#include"input.h"
#include"texture.h"

typedef struct CubeVertex_tag
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;		//�@���x�N�g��	���W�̎��J���[�̑O
	D3DCOLOR	color;
	D3DXVECTOR2	uv;
}Cube_Vertex;
#define FVF_CUBE (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)


static Cube_Vertex g_cube_vertex[] = {
	//�O��
	{D3DXVECTOR3(-0.5f,0.5f,0.1f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR3(0.5f,0.5f,0.1f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.1f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.1f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
};

static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;

void Cube_Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(Cube_Vertex) * 4, D3DUSAGE_WRITEONLY, FVF_CUBE, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	//(Length=�؂�郁�����̑傫�� , usage=D3DUSAGE_WRITEONLY�ɂ��Ă��� , FVF , pool=D3DPOOL_MANAGED , VertexBuffer�̃A�h���X,NULL)

	//indexbuffer
	pDevice->CreateIndexBuffer(sizeof(WORD) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0, pIndex[1] = 1, pIndex[2] = 2, pIndex[3] = 3;
	g_pIndexBuffer->Unlock();

	Cube_Vertex *pV;	//���z�A�h���X�@g_VertexBuffer->Unlock()���ĂԂƂ����g���Ȃ�
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//(���b�N���鏉�߂̃A�h���X,�ǂ��܂Ń��b�N���邩�H�@0�ɂ���ƑS��,CPU��VRAM�̉��z�A�h���X����� (void**)&pV , D3DLOCK_DISCARD)
	memcpy(pV, g_cube_vertex, sizeof(g_cube_vertex));
	g_VertexBuffer->Unlock();
}

void Cube_UnInit(void)
{
	g_pIndexBuffer->Release();
	g_VertexBuffer->Release();
}

void Cube_Update(void) 
{
	
}

void Cube_Draw(const D3DXMATRIX *mtx,int textureID)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//�f�B�t���[�Y�}�e���A���͒��_�J���[
	
	pDevice->SetTransform(D3DTS_WORLD, mtx);

	pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Cube_Vertex));
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->SetFVF(FVF_CUBE);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

	Cube_Vertex* g_cube_vertex = new Cube_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_cube_vertex, D3DLOCK_DISCARD);//(���b�N���鏉�߂̃A�h���X,�ǂ��܂Ń��b�N���邩�H�@0�ɂ���ƑS��,CPU��VRAM�̉��z�A�h���X����� (void**)&pV , D3DLOCK_DISCARD)
	g_cube_vertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	g_cube_vertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	g_cube_vertex[2].uv = D3DXVECTOR2(0.0f, 1.0f);
	g_cube_vertex[3].uv = D3DXVECTOR2(1.0f, 1.0f);
	g_VertexBuffer->Unlock();
}

void Cube_SetUV(float CutX, float CutY, float CutW, float CutH, int TextureID)
{
	int w = Texture_GetWidth(TextureID);
	int h = Texture_GetHeight(TextureID);

	float u0 = CutX / (float)w;
	float v0 = CutY / (float)h;
	float u1 = (CutX + CutW) / (float)w;
	float v1 = (CutY + CutH) / (float)h;

	Cube_Vertex* g_cube_vertex = new Cube_Vertex[4];
	g_VertexBuffer->Lock(0, 0, (void**)&g_cube_vertex, D3DLOCK_DISCARD);//(���b�N���鏉�߂̃A�h���X,�ǂ��܂Ń��b�N���邩�H�@0�ɂ���ƑS��,CPU��VRAM�̉��z�A�h���X����� (void**)&pV , D3DLOCK_DISCARD)
	g_cube_vertex[0].uv = D3DXVECTOR2(u0, v0);
	g_cube_vertex[1].uv = D3DXVECTOR2(u1, v0);
	g_cube_vertex[2].uv = D3DXVECTOR2(u0, v1);
	g_cube_vertex[3].uv = D3DXVECTOR2(u1, v1);
	g_VertexBuffer->Unlock();
}