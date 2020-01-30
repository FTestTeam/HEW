#include <d3dx9.h>
#include "texture.h"
#include "common.h"
#include "mydirect3d.h"
#include "sprite.h"

/*----------------------------
	�\���̐錾
----------------------------*/
typedef struct Vertex2d_tag {
	D3DXVECTOR4	position;	//���W
	D3DCOLOR	color;		//���_�J���[
	D3DXVECTOR2	uv;			//�e�N�X�`����UV���W
}Vertex2d;
//�f�o�C�X�Ɍ`��`���邽�߂̃}�N���@���ς����炱����ς���
#define FVF_VERTEX2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);

//�\��
void Sprite_Draw(int textureId,float dx, float dy) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[] = {
			{D3DXVECTOR4(dx - 0.5f - w / 2		,dy - 0.5f - h / 2	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,0.0f)},
			{D3DXVECTOR4(dx + w - 0.5f - w / 2	,dy - 0.5f - h / 2    ,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,0.0f)},
			{D3DXVECTOR4(dx - 0.5f - w / 2		,dy + h - 0.5f - h / 2,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,1.0f)},
			{D3DXVECTOR4(dx + w - 0.5f - w / 2 	,dy + h - 0.5f - h / 2,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,1.0f)},
	};

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice=MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0,Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

//��]
void Sprite_Draw(int textureId,float dx, float dy, float center_x, float center_y, float angle) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f	 ,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(0 + w - 0.5f,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR4(0 - 0.5f	 ,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR4(0 + w - 0.5f,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,1.0f)},
	};

	//���s�ړ��s��
	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxR;
	D3DXMatrixRotationZ(&mtxR, angle);

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, dx - w / 2 + center_x, dy + center_y - h / 2, 0.0f);

		
	D3DXMATRIX mtxW = mtxT * mtxR * mtxIT;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

//�g��
void Sprite_Draw(int textureId,float dx, float dy, float scale_x, float scale_y ,float center_x,float center_y) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f		,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(0 + w - 0.5f	,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR4(0 - 0.5f		,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR4(0 + w - 0.5f	,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,1.0f)},
	};

	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, center_x + dx - w / 2, center_y + dy - h / 2, 0.0f);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, scale_x, scale_y, 0.0f);	//(&mtxT, x, y, z)

	
	D3DXMATRIX mtxW = mtxT * mtxS * mtxIT;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

//�g��E��]
void Sprite_Draw(int textureId,float dx, float dy, float scale_x, float scale_y, float center_x, float center_y, float angle) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f		,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(0 + w - 0.5f	,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR4(0 - 0.5f		,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR4(0 + w - 0.5f	,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,1.0f)},
	};

	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxR;
	D3DXMatrixRotationZ(&mtxR, angle);

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, center_x + dx - w / 2, center_y + dy - h, 0.0f);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, scale_x, scale_y, 0.0f);	//(&mtxT, x, y, z)

	
	D3DXMATRIX mtxW = mtxT * mtxR * mtxS * mtxIT ;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

void Sprite_Mirror_Draw(int textureId,float dx, float dy, float scale_x, float scale_y, float center_x, float center_y, float angle) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f		,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR4(0 + w - 0.5f	,0 - 0.5f	  ,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(0 - 0.5f		,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(1.0f,1.0f)},
		{D3DXVECTOR4(0 + w - 0.5f	,0 + h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(0.0f,1.0f)},
	};

	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxR;
	D3DXMatrixRotationZ(&mtxR, angle);

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, center_x + dx - w / 2, center_y + dy - h, 0.0f);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, scale_x, scale_y, 0.0f);	//(&mtxT, x, y, z)

	
	D3DXMATRIX mtxW = mtxT * mtxR * mtxS * mtxIT;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}


//�J�b�g�\��
void Sprite_Draw(int textureId,float dx, float dy,int cut_x, int cut_y, int cut_w, int cut_h) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	Vertex2d v[] = {
		{D3DXVECTOR4(dx - 0.5f		  ,dy - 0.5f		,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx + cut_w - 0.5f,dy - 0.5f		,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f		  ,dy + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx + cut_w - 0.5f,dy + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v1)},
	};

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

//�J�b�g�E��]
void Sprite_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h,float center_x,float center_y, float angle) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);
	
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f		 ,0 - 0.5f		  ,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 - 0.5f        ,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(0 - 0.5f		 ,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v1)},
	};

	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxR;
	D3DXMatrixRotationZ(&mtxR, angle);

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, center_x + dx , center_y + dy, 0.0f);

	
	D3DXMATRIX mtxW = mtxT * mtxR * mtxIT;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

//�J�b�g�E�g��
void Sprite_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float scale_x, float scale_y,float center_x, float center_y) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f		  ,0 - 0.5f		,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 - 0.5f		,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(0 - 0.5f		  ,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v1)},
	};

	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, center_x + dx, center_y + dy, 0.0f);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, scale_x, scale_y, 0.0f);	//(&mtxT, x, y, z)

	
	D3DXMATRIX mtxW = mtxT * mtxS * mtxIT;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}


//�J�b�g�E�g��E��]
void Sprite_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float scale_x, float scale_y, float center_x, float center_y, float angle) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f		 ,0 - 0.5f		  ,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 - 0.5f        ,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(0 - 0.5f		 ,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v1)},
	};

	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxR;
	D3DXMatrixRotationZ(&mtxR, angle);

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, center_x + dx, center_y + dy, 0.0f);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, scale_x, scale_y, 0.0f);	//(&mtxT, x, y, z)

	
	D3DXMATRIX mtxW = mtxT * mtxR * mtxS * mtxIT ;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

//�J�b�g�E�g��E��]�E���]
void Sprite_Mirror_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float scale_x, float scale_y, float center_x, float center_y, float angle) {
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	Vertex2d v[] = {
		{D3DXVECTOR4(0 - 0.5f		 ,0 - 0.5f		  ,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 - 0.5f        ,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(0 - 0.5f		 ,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u1,v1)},
		{D3DXVECTOR4(0 + cut_w - 0.5f,0 + cut_h - 0.5f,0.0f,1.0f),g_Color,D3DXVECTOR2(u0,v1)},
	};

	D3DXMATRIX mtxT;
	D3DXMatrixTranslation(&mtxT, -center_x, -center_y, 0.0f);	//(&mtxT, x, y, z)

	D3DXMATRIX mtxR;
	D3DXMatrixRotationZ(&mtxR, angle);

	D3DXMATRIX mtxIT;
	D3DXMatrixTranslation(&mtxIT, center_x + dx, center_y + dy, 0.0f);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, scale_x, scale_y, 0.0f);	//(&mtxT, x, y, z)

	
	D3DXMATRIX mtxW = mtxT * mtxR * mtxS * mtxIT;	//���s�ړ��[����]�[�����s�ړ�
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return;
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

	//Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	return;
}

void Sprite_SetColor(D3DCOLOR Color)
{
 	g_Color = Color;
}