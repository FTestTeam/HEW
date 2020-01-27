#pragma once
#ifndef COLLECT_DATA_H_
#define COLLECT_DATA_H_

#include"Scene.h"

enum FILE_MODE {
	WRITE,
	READ,
};

struct COLLECT_DATA {
	float vol;
	float accel;
	bool bJoy_R_Press;
	bool bJoy_R_Release;
};

void Collect_Data_Init(FILE_MODE mode);
void Collect_Data_UnInit();

void Collect_Data_Save();

void Collect_Data_Load();
COLLECT_DATA Collect_Data_GetData();

#endif // !COLLECT_DATA_H_