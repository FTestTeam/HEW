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
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},
	//{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	//{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},

	//�E����
	{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},
	{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},
	//{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	//{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},

	//������
	{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},
	//{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),	D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	//{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},

	//���
	{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},
	{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	//{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.25f)},
	//{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},

	//����
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.5f)},
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	//{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.5f)},
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	//{D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},

	//���
	{D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	//{D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	{D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.5f)},
	//{D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
};

static int g_textureID = 0;

static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;

void Cube_Init(void)
{
	g_textureID=Texture_SetLoadFile("Asset/Texture/spice_and_wolf.png", 1024, 1024);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(Cube_Vertex) * 24, D3DUSAGE_WRITEONLY, FVF_CUBE, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	//(Length=�؂�郁�����̑傫�� , usage=D3DUSAGE_WRITEONLY�ɂ��Ă��� , FVF , pool=D3DPOOL_MANAGED , VertexBuffer�̃A�h���X,NULL)

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

void Cube_Draw(const D3DXMATRIX *mtx)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//�f�B�t���[�Y�}�e���A���͒��_�J���[
	
	pDevice->SetTransform(D3DTS_WORLD, mtx);

	pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Cube_Vertex));
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->SetFVF(FVF_CUBE);
	pDevice->SetTexture(0, Texture_GetTexture(g_textureID));
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 36);
}