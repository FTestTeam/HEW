#pragma once
#ifndef MODEL_H_
#define MODEL_H_
#include<d3dx9.h>

void Model_Init();
void Model_UnInit();

//���f���`��
//�������F
//	*D3DMATRIX	�z�u�������s��
//�������F
//	int �`�悵�������f����ID
void Model_Draw(const D3DXMATRIX *mtx, int ModelID);

//���f���o�^
//�����F
//	�t�@�C����
//�߂�l�F
//	int	�o�^�������f����ID
int Model_SetLoadFile(const char *FileName);

//���f���ꊇ���[�h
int Model_Load();
#endif