#include "Result.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "input.h"
#include "common.h"

static int g_Result_TextureID;

void Result_Init(void)
{
	g_Result_TextureID = Texture_SetLoadFile("Asset/Texture/Result.png", 1280, 720);
}

void Result_Uninit(void)
{
	
}

void Result_Update(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		Scene_SetNextScene(SCENE_TITLE);
	}
}

void Result_Draw(void)
{
	Sprite_Draw(g_Result_TextureID, 0 + SCREEN_WIDTH / 2, 0 + SCREEN_HEIGHT / 2);
}
