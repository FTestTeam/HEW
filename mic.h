#pragma once
#ifndef MIC_H_
#define MIC_H_

void Mic_Init(HWND hwnd);
void Mic_UnInit();
void Mic_Update();

float Mic_GetVolume(void);

#endif // !MIC_H_
