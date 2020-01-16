#include<d3dx9.h>
#include"mydirect3d.h"
#include"texture.h"
#include"DebugPrintf.h"
#include"hammer.h"

typedef struct MESHFIELD_Tag {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR	color;
	D3DXVECTOR2	uv;
}MESH_FIELD_Vertex;
#define FVF_MESHFIELD (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//static MESH_FIELD_Vertex *g_MF_vertex;
static int g_textureID;

static int g_MF_VertexNum;
static int g_MF_PRIM;

static LPDIRECT3DINDEXBUFFER9	g_pIndexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9	g_VertexBuffer = NULL;

void MeshField_Init(int MF_W , int MF_H , float w ,float h)
{
	int MF_INDEX = (((MF_W * 2 + 2) * MF_H) + (MF_H - 1) * 2);	//�S�̂̃C���f�b�N�X�̐�
	g_MF_VertexNum = ((MF_W + 1)*(MF_H + 1));				//���_��
	g_MF_PRIM = (MF_INDEX - 2);		//�S�̂̃v���~�e�B�u��

	g_textureID = Texture_SetLoadFile("Asset/Texture/p0305_l_th.jpg", 0, 0);
	//g_textureID = Texture_SetLoadFile("Asset/Texture/spice_and_wolf.png", 0, 0);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//uv�Q�ƊO�̏ꍇ�J��Ԃ��ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�ۑ�p�@���C���[�t���[��
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(MESH_FIELD_Vertex) * g_MF_VertexNum, D3DUSAGE_WRITEONLY, FVF_MESHFIELD, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	MESH_FIELD_Vertex *g_MF_vertex = new MESH_FIELD_Vertex[g_MF_VertexNum];
	g_VertexBuffer->Lock(0, 0, (void**)&g_MF_vertex, D3DLOCK_DISCARD);
	//���_����ׂ�	billboard
	int VertexCount = 0;
	for (float i = 0; i < MF_H + 1; i++) {
		for (float j = 0; j < MF_W + 1; j++) {
			g_MF_vertex[VertexCount].position = { j * w - MF_W / 2,-0.1f,i * h};
			g_MF_vertex[VertexCount].uv = { j,i };
			g_MF_vertex[VertexCount].normal = { 0.0f,1.0f,0.0f };
			g_MF_vertex[VertexCount].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			VertexCount++;
		}
	}
	g_VertexBuffer->Unlock();		

	//�C���f�b�N�X�o�b�t�@
	pDevice->CreateIndexBuffer(sizeof(WORD) * MF_INDEX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	int j = 0;	//�|���S���̉��̖ʂɓ����钸�_�ԍ��̕ϐ�
	int EndSyukutaiIndex = MF_W + ((MF_W + 1)*(MF_H - 1));	//�Ō�̍s�ŏk�ރ|���S���̃C���f�b�N�X�����Ȃ��悤�ɂ��邽�߂̕ϐ�
	for (int i = 0; i < MF_INDEX; i += 2) {
		pIndex[i] = j;
		pIndex[i + 1] = j + MF_W + 1;	
		if (j % (MF_W+1) == MF_W && j != EndSyukutaiIndex) {	//�k�ރ|���S������邽�߂̃C���f�b�N�X
			pIndex[i + 2] = j + MF_W + 1;
			pIndex[i + 3] = j + 1;
			i += 2;
		}
		j++;
	}
	g_pIndexBuffer->Unlock();
}

void MeshField_UnInit()
{
	g_pIndexBuffer->Release();
	g_VertexBuffer->Release();
}

void MeshField_Update()
{
	
}

void MeshField_Draw(const D3DXMATRIX *mtx)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING,false);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

	pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(MESH_FIELD_Vertex));
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->SetFVF(FVF_MESHFIELD);
	
	pDevice->SetTexture(0, Texture_GetTexture(g_textureID));
	//�ۑ�p�@���C���[�t���[���ɂ������e�N�X�`������Ȃ��ق������₷������
	//pDevice->SetTexture(0, NULL);

	pDevice->SetTransform(D3DTS_WORLD, mtx);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_MF_VertexNum, 0, g_MF_PRIM);
}