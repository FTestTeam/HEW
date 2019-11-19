#define _CRT_SECURE_NO_WARNINGS

#include<d3d9.h>
#include<d3dx9.h>
#include"mydirect3d.h"
#include"texture.h"

#define FILENAME_MAX	(128)

typedef struct Texture_data_tag {
	char FileName[FILENAME_MAX];
	int width;
	int height;
	LPDIRECT3DTEXTURE9 pTexture;
}Texture_Data;

static Texture_Data g_TextureDate[TEXTUREDATA_MAX];
static LPDIRECT3DDEVICE9 g_pDevice=NULL;

void Texture_Init(void) {
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		g_TextureDate[i].FileName[0] = 0;	//�擪��0�����邾���ŏ�����
		g_TextureDate[i].width = 0;
		g_TextureDate[i].height = 0;
		g_TextureDate[i].pTexture = NULL;
	}
}

int Texture_SetLoadFile(const char *pFileName, int width, int height) {
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (strcmp(g_TextureDate[i].FileName, pFileName)==0) {
			return i;	//���łɓo�^����Ă���Ǘ��ԍ���return
		}
	}

	//�f�[�^�x�[�X�̎g�p����Ă��Ȃ��������������A�o�^����
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_TextureDate[i].FileName[0] != 0) {
			continue;	//�g�p�����Ɏ�������
		}

		//�o�^
		strcpy(g_TextureDate[i].FileName, pFileName);
		g_TextureDate[i].width = width;
		g_TextureDate[i].height = height;
		return i;
	}
	MessageBox(NULL, "�e�N�X�`���f�[�^���g���؂�܂���", "�G���[", MB_OK);
	return -1;//�o�^�ł���ꏊ���Ȃ�
}

int Texture_Load(void) {
	int error_count = 0;	//�G���[�ɂȂ�������Ԃ����߂̕ϐ�

	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_TextureDate[i].FileName[0] == 0) {
			continue;
		}
		if (g_TextureDate[i].pTexture != NULL) {
			continue;
		}
		
		g_pDevice=MyDirect3D_GetDevice();
		HRESULT hr = D3DXCreateTextureFromFile(g_pDevice,g_TextureDate[i].FileName, &g_TextureDate[i].pTexture);
		if (FAILED(hr)) {
			error_count++;
		}
	}
	return error_count;
}

void Texture_Release(int ids[], int count) {
	for (int i = 0; i < count; i++) {
		if (!g_TextureDate[i].pTexture) {	//NULL�`�F�b�N
			continue;
		}
		if (ids[i] < 0) {
			continue;
		}
		g_TextureDate[ids[i]].pTexture->Release();
		g_TextureDate[ids[i]].pTexture = NULL;
		g_TextureDate[ids[i]].height = 0;
		g_TextureDate[ids[i]].width = 0;
		g_TextureDate[ids[i]].FileName[0] = 0;
	}
}

void Texture_Release(void) {
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (!g_TextureDate[i].pTexture) {	//NULL�`�F�b�N
			continue;
		}
		g_TextureDate[i].pTexture->Release();
		g_TextureDate[i].pTexture = NULL;
		g_TextureDate[i].height = 0;
		g_TextureDate[i].width = 0;
		g_TextureDate[i].FileName[0] = 0;
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int id) {
	return g_TextureDate[id].pTexture;
}

int Texture_GetWidth(int id) {
	return g_TextureDate[id].width;
}

int Texture_GetHeight(int id) {
	return g_TextureDate[id].height;
}