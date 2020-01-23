#pragma once
#ifndef FADE_H_
#define FADE_H_

#include<d3d9.h>

void Fade_Init(void);
void Fade_Uninit(void);
void Fade_Update(void);
void Fade_Draw(void);

//フェードスタート
//fream
//	フェードの長さ
//color
//	フェードの色
//bOut
//	FadeInかFadeOutか？
void Fade_Stert(int frame, D3DCOLOR color, bool bOut);
bool Fade_IsFade(void);

#endif // !FADE_H_