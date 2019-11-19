#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<d3d9.h>

#define TEXTUREDATA_MAX	(256)

//�e�N�X�`���Ǘ����W���[���̏�����
void Texture_Init(void);
//���[�h�������t�@�C����ǂݍ��ށi�g���t�@�C���̗\��j
int Texture_SetLoadFile(const char *pFileName,int width,int height);	//�߂�l�����̃e�N�X�`���̗\��ԍ�
//�\�񂵂Ă����t�@�C�������ׂēǂݍ���
int Texture_Load(void);		//�߂�l���ǂݍ��݂Ɏ��s������
//�e�N�X�`�����J��
void Texture_Release(int ids[], int count);		//�iint�^�̐擪�A�h���X,����̗v�f���jinta[]={1,3,4} �Ǘ��ԍ�1,3,4���J������
//�e�N�X�`���S�����J��
void Texture_Release(void);
//
LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);	//(�Ǘ��ԍ�)
//
int Texture_GetWidth(int id);
//
int Texture_GetHeight(int id);

#endif // !TEXTURE_H
