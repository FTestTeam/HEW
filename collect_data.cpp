#include<fstream>
#include"collect_data.h"
#include"mic.h"
#include"joycon.h"
#include"DebugPrintf.h"
#include"Scene.h"

using namespace std;

static COLLECT_DATA g_data;
static ofstream g_fpW;
static ifstream g_fpR;
static float g_RaidStartHP;

void Collect_Data_Init(FILE_MODE mode)
{
	switch (mode)
	{
	case WRITE:
		g_fpW.open("Asset/data/replay.dat", ios::out | ios::binary | ios::trunc);
		if (!g_fpW) {
			MessageBox(NULL, "replay.datを開けません", "エラー", MB_ICONERROR);
		}
		break;
	case READ:
		g_fpR.open("Asset/data/replay_sample.dat", ios::in | ios::binary);
		if (!g_fpR) {
			MessageBox(NULL, "replay.datを開けません", "エラー", MB_ICONERROR);
		}
		break;
	default:
		break;
	}
	
}

void Collect_Data_UnInit()
{
	if(g_fpW) g_fpW.close();
	if (g_fpR) g_fpR.close();
}

void Collect_Data_Save()
{
	COLLECT_DATA data;

	data.accel = Joycon_GetAccel(DIJOY_ACCEL_SL1);
	data.bJoy_R_Press = Joycon_IsPress(DIJOY_R_R);
	data.bJoy_R_Release = Joycon_IsRelease(DIJOY_R_R);
	data.vol = Mic_GetVolume();
	data.raidHP = g_RaidStartHP;

	g_fpW.write((char *)&data, sizeof(COLLECT_DATA));
}

void Collect_Data_Load()
{
	g_fpR.read((char *)&g_data, sizeof(COLLECT_DATA));
}

COLLECT_DATA Collect_Data_GetData()
{
	return g_data;
}

void Collect_Data_SetRaidStartHP(float startHP) 
{
	g_RaidStartHP = startHP;
}