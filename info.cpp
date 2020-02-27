#include"texture.h"
#include"sprite.h"
#include"common.h"

static int g_textureID_Spin;
static int g_anim;
static int g_fream;

void Info_Init()
{
	g_textureID_Spin = Texture_SetLoadFile("Asset/Texture/info.png", 768, 192);
	g_anim = g_fream  = 0;
}

void Info_UnInit()
{

}

void Info_Update()
{
	if (g_anim > 5) {
		g_anim = 0;
	}
	if (g_fream % 5 == 0) {
		g_anim++;
	}
	g_fream++;
}

void Info_Draw()
{
	Sprite_Draw(g_textureID_Spin, Window_GetWidth() - 128.0f, 128, g_anim * 128, 0, 128, 192);
}