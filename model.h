#pragma once
#ifndef MODEL_H_
#define MODEL_H_
#include<d3dx9.h>

void Model_Init();
void Model_UnInit();

//モデル描画
//第一引数：
//	*D3DMATRIX	配置したい行列
//第二引数：
//	int 描画したいモデルのID
void Model_Draw(const D3DXMATRIX *mtx, int ModelID);

//モデル登録
//引数：
//	ファイル名
//戻り値：
//	int	登録したモデルのID
int Model_SetLoadFile(const char *FileName);

//モデル一括ロード
int Model_Load();
#endif