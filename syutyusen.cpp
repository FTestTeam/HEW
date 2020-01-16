#include<d3dx9.h>
#include"texture.h"
#include"sprite.h"
#include"common.h"
#include"mic.h"
#include"hammer.h"
#include"player.h"

static int g_textureID;
static D3DXVECTOR2 g_pos;
static float g_scale;
static bool g_bUse;

void Syutyusen_Init()
{
	g_textureID = Texture_SetLoadFile("Asset/Texture/syutyu.png", 1280, 720);

	g_pos = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };

	g_scale = 1.0f;

	g_bUse = false;
}

void Syutyusen_UnInit()
{

}

void Syutyusen_Update()
{
	g_scale += 0.05f;
	if (g_scale >= 2.5f) {
		g_scale = 1.0f;
	}

	g_bUse = false;
	if (Mic_GetVolume() > 40 && Hammer_IsFly() && Player_IsFly()) {
		g_bUse = true;
	}
}

void Syutyusen_Draw()
{
	if(g_bUse)
	Sprite_Draw(g_textureID, g_pos.x, g_pos.y, g_scale, g_scale, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
}