#include "Title.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "input.h"
#include "input.h"
#include "common.h"
#include "joycon.h"
#include "collect_data.h"

static int g_Title_TextureID;

static int g_Titleback_TextureID;
static int g_Startbutton_TextureID;

static float scale;
static float radius;

static float center_x;
static float center_y;

static int g_fream;


void Title_Init(void)
{
	g_Title_TextureID = Texture_SetLoadFile("Asset/Texture/title.png", 1280, 720);

	g_Titleback_TextureID = Texture_SetLoadFile("Asset/Texture/titleback.png", Window_GetWidth(), Window_GetHeight());
	g_Startbutton_TextureID = Texture_SetLoadFile("Asset/Texture/startbutton.png", 1482, 560);


	scale = 1.0f;
	radius = 0.0f;
	center_x = (float)Window_GetWidth() / 2;
	center_y = (float)Window_GetHeight() / 2;

	g_fream = 0;

	Collect_Data_UnInit();
}

void Title_Uninit(void)
{
}

void Title_Update(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN) || Joycon_IsTrigger(DIJOY_R_A))
	{
		Scene_SetNextScene(SCENE_ZAKO);
	}

	radius += 0.07f;
	scale = sinf(radius)/20 + 0.8f;


	if (Keyboard_IsTrigger(DIK_R))
	{
		Scene_SetNextScene(SCENE_REPLAY_ZAKO);
	}

	g_fream++;

}

void Title_Draw(void)
{
	Sprite_Draw(g_Titleback_TextureID, center_x,center_y);
	Sprite_Draw(g_Startbutton_TextureID, center_x + 50.0f, 500.0f,0.3f,0.3f, center_x + 50.0f,500.0f);
	Sprite_Draw(g_Title_TextureID, center_x, center_y, scale, scale, center_x, center_y - 50.0f);

}