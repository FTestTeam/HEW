#include<Windows.h>
#include<mmsystem.h>
#include<math.h>
#include"common.h"
#include"DebugPrintf.h"

static WAVEHDR g_inHdr[2];
static HWAVEIN g_Mic;

void Mic_Init(HWND hwnd)
{
	UINT a = waveInGetNumDevs();
	WAVEINCAPS caps;
	waveInGetDevCaps(0, &caps, sizeof(WAVEINCAPS));
	
	WAVEFORMATEX Format;
	Format.wFormatTag = WAVE_FORMAT_PCM;
	Format.nChannels = 2;
	Format.wBitsPerSample = 16;
	Format.nBlockAlign = 4;
	Format.nSamplesPerSec = 22050;
	Format.nAvgBytesPerSec = 22050 * 4;
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
	//DebugPrintf("%f\n", fabsf((float)*inHdr->lpData));
	g_inHdr->dwBytesRecorded = 0;
	waveInAddBuffer(g_Mic, g_inHdr, sizeof(WAVEHDR));
}

float Mic_GetVolume(void)
{
	return fabsf((float)*g_inHdr->lpData);
}