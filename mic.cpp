#include<Windows.h>
#include<mmsystem.h>
#include<math.h>
#include"common.h"
#include"DebugPrintf.h"

static WAVEHDR g_inHdr[2];
static HWAVEIN g_Mic;

static float g_MaxVol;
static float g_Vol;

static int g_fream;

void Mic_Init(HWND hwnd)
{
	g_fream = 0;
	g_MaxVol = g_Vol = 0.0f;

	UINT a = waveInGetNumDevs();
	WAVEINCAPS caps;
	waveInGetDevCaps(0, &caps, sizeof(WAVEINCAPS));
	
	WAVEFORMATEX Format;
	Format.wFormatTag = WAVE_FORMAT_PCM;
	Format.nChannels = 2;
	Format.wBitsPerSample = 16;
	Format.nBlockAlign = 4;
	Format.nSamplesPerSec = 5000;
	Format.nAvgBytesPerSec = 5000 * 4;
	Format.cbSize = 0;

	if (waveInOpen(&g_Mic, 0, &Format, (DWORD)hwnd, NULL, NULL) != MMSYSERR_NOERROR) {
		MessageBox(NULL, "マイクがオープンできません", "マイク", MB_ICONWARNING);
	}
	
	memset(g_inHdr, 0, sizeof(g_inHdr));
	for (int i = 0; i < 2; i++) {
		g_inHdr[i].lpData = new char[BUFSIZ];
		g_inHdr[i].dwBufferLength = BUFSIZ;
		if (waveInPrepareHeader(g_Mic, &g_inHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
			MessageBox(NULL, "データブロックを登録できません", "マイク", MB_ICONWARNING);
		}
	}
	
	for (DWORD i = 0; i < 2; i++) {
		g_inHdr[i].dwBytesRecorded = 0;
		if (waveInAddBuffer(g_Mic, &g_inHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
			MessageBox(NULL, "バッファを作れません", "マイク", MB_ICONWARNING);
		}
	}

	waveInStart(g_Mic);
}

void Mic_UnInit()
{
	waveInStop(g_Mic);
	waveInClose(g_Mic);
}

void Mic_Update()
{
	//DebugPrintf("%f\n", g_MaxVol);
	g_Vol = fabsf((float)*g_inHdr->lpData);
	if (g_Vol > g_MaxVol) {
		g_MaxVol = g_Vol;
		g_fream = 30;
	}
	else {
		g_fream--;
	}

	if (g_fream <= 0) {
		g_MaxVol-=5;
	}
	g_inHdr->dwBytesRecorded = 0;
	waveInAddBuffer(g_Mic, g_inHdr, sizeof(WAVEHDR));
}

float Mic_GetVolume(void)
{
	return g_MaxVol;
}