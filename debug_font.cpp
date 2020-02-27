#include <d3dx9.h>
#include "mydirect3d.h"
#include "common.h"
#include <stdio.h>


/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
#define DEBUG_PRINTF_BUFFER_MAX (256) // 文字列用バッファ量（少ないときは増やすこと）
#define PARAM_MAX (256)

struct DEBUG_PARAM {
	int x;
	int y;
	const char * pFormat;
	char buf[DEBUG_PRINTF_BUFFER_MAX];
	bool bUse;
};

/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
#if defined(_DEBUG) || defined(DEBUG)
static LPD3DXFONT g_pD3DXFont = NULL;
static DEBUG_PARAM g_param[PARAM_MAX];
#endif // _DEBUG || DEBUG


/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

// デバックフォントモジュールの初期化
void DebugFont_Initialize(void)
{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXCreateFont(pDevice,
		24, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH, 
		"HGP創英角ﾎﾟｯﾌﾟ体", 
		&g_pD3DXFont);

	for (int i = 0; i < PARAM_MAX; i++) {
		g_param[i].x = -1.0f;
		g_param[i].y = -1.0f;
		g_param[i].bUse = false;
	}

#endif // _DEBUG || DEBUG
}


// デバックフォントモジュールの終了処理
void DebugFont_Finalize(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	if( g_pD3DXFont ) {
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif // _DEBUG || DEBUG
}


// デバックフォントの描画
void DebugFont_Draw()
{
#if defined(_DEBUG) || defined(DEBUG)
	for (int i = 0; i < PARAM_MAX; i++) {
		if (g_param[i].x < 0) continue;

		RECT rect = { g_param[i].x, g_param[i].y, Window_GetWidth(), Window_GetHeight()
		};

		g_pD3DXFont->DrawText(NULL,
			g_param[i].buf,
			-1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(0, 255, 0, 255));
	}
#endif // _DEBUG || DEBUG
}

void DebugFont_SetParam(int slot,const char *pFormat, ...)
{
#if defined(_DEBUG) || defined(DEBUG)
	for (int i = 0; i < PARAM_MAX; i++) {
		if (g_param[i].bUse && g_param[i].y != slot * 24) continue;

		if (!g_param[i].bUse) {
			g_param[i].x = 1;
			g_param[i].y = slot * 24;
			g_param[i].pFormat = pFormat;
			g_param[i].bUse = true;
		}

		va_list argp;
		va_start(argp, pFormat);
		vsprintf_s(g_param[i].buf, DEBUG_PRINTF_BUFFER_MAX, pFormat, argp);
		va_end(argp);
		break;
	}
#else
	UNREFERENCED_PARAMETER(pFormat);
#endif
}