#include<d3d9.h>
#include<d3dx9.h>
#include"common.h"
#include"mydirect3d.h"

typedef struct FadeVertex_tag 
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}FadeVertex;
#define FVF_VERTEX2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

static D3DCOLOR g_FadeColor = 0;	//フェードの色
static bool g_bFadeOut = false;		//インかアウトか
static bool g_bFade = false;		//フェード中か
static int g_FadeFrame = 0;			//フェードするframe数
static int g_FadeFrameCount = 0;	//フレームカウンター
static int g_FadeStartFrame = 0;	//フェードが始まった時間

void Fade_Init(void)
{
	g_bFade = false;
	g_FadeFrameCount = 0;
}

void Fade_Uninit(void)
{

}

void Fade_Update(void)
{
	if (g_bFade) {
		int elapsedFrame = g_FadeFrameCount - g_FadeStartFrame;	//経過時間
		float e = (float)elapsedFrame / g_FadeFrame;	//今の作業比率　何パーセント終わったか？
		if (e >= 1.0f) {
			e = 1;
			g_bFade = false;
		}

		float alpha = g_bFadeOut ? e : 1.0f - e;
		D3DXCOLOR color = g_FadeColor;	//D3DXCOLORは0～1で色を扱う
		color.a = alpha;
		g_FadeColor = color;
	}

	g_FadeFrameCount++;
}

void Fade_Draw(void)
{
	if (g_bFade) {
		D3DXCOLOR color = g_FadeColor;
		if (color.a <= 0.0001f) {
			return;
		}
		FadeVertex v[4] = {
			{D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),g_FadeColor},
			{D3DXVECTOR4(Window_GetWidth(),0.0f,0.0f,1.0f),g_FadeColor},
			{D3DXVECTOR4(0.0f,Window_GetHeight(),0.0f,1.0f),g_FadeColor},
			{D3DXVECTOR4(Window_GetWidth(),Window_GetHeight(),0.0f,1.0f),g_FadeColor}
		};

		LPDIRECT3DDEVICE9 pDevice = NULL;
		pDevice = MyDirect3D_GetDevice();
		if (!pDevice) {
			return;
		}
		pDevice->SetFVF(FVF_VERTEX2D);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));
	}
}

void Fade_Stert(int frame, D3DCOLOR color, bool bOut)
{
	g_FadeFrame = frame;
	g_FadeStartFrame = g_FadeFrameCount;

	g_FadeColor = color;

	g_bFadeOut = bOut;
	g_bFade = true;
}

bool Fade_IsFade(void)
{
	return g_bFade;
}