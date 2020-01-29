#include "Title.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "input.h"
#include "input.h"
#include "common.h"

static int g_Title_TextureID;
static int g_Titleback_TextureID;
static int g_Startbutton_TextureID;

static float scale;
static float radius;

static float center_x;
static float center_y;


void Title_Init(void)
{
	g_Title_TextureID = Texture_SetLoadFile("Asset/Texture/title.png", 1280, 720);
	g_Titleback_TextureID = Texture_SetLoadFile("Asset/Texture/titleback.png", 2560, 1440);
	g_Startbutton_TextureID = Texture_SetLoadFile("Asset/Texture/startbutton.png", 1482, 560);


	scale = 1.0f;
	radius = 0.0f;
	center_x = (float)SCREEN_WIDTH / 2;
	center_y = (float)SCREEN_HEIGHT / 2;
}

void Title_Uninit(void)
{
}

void Title_Update(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		Scene_SetNextScene(SCENE_ZAKO);
	}
	radius += 0.07f;
	scale = sinf(radius)/20 + 0.8f;
}

void Title_Draw(void)
{
	Sprite_Draw(g_Titleback_TextureID, center_x,center_y);
	Sprite_Draw(g_Startbutton_TextureID, center_x + 50.0f, 500.0f,0.3f,0.3f, center_x + 50.0f,500.0f);
	Sprite_Draw(g_Title_TextureID, center_x, center_y, scale, scale, center_x, center_y - 50.0f);

}

