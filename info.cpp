#include"texture.h"
#include"sprite.h"
#include"common.h"
#include"player.h"

static int g_textureID_Spin;
static int g_anim;
static int g_fream;

static int g_textureID_Shout;

void Info_Init()
{
	g_textureID_Spin = Texture_SetLoadFile("Asset/Texture/info.png", 768, 192);
	g_anim = g_fream  = 0;

	g_textureID_Shout = Texture_SetLoadFile("Asset/Texture/info_sakebe.png", 3840, 384);
}

void Info_UnInit()
{

}

void Info_Update()
{
	if (g_anim > (Player_IsFly() ? 10 : 5)) {
		g_anim = 0;
	}
	if ((g_fream % (Player_IsFly() ? 10 : 5)) == 0) {
		g_anim++;
	}
	
	g_fream++;
}

void Info_Draw()
{
	Player_IsFly() ? Sprite_Draw(g_textureID_Shout, Window_GetWidth() - 256.0f, 128.0f, g_anim * 256, 0, 256, 384) : Sprite_Draw(g_textureID_Spin, Window_GetWidth() - 128.0f, 128, g_anim * 128, 0, 128, 192);
}