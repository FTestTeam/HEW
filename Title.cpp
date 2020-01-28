#include "Title.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "input.h"
#include "input.h"
#include "common.h"
#include "joycon.h"

static int g_Title_TextureID;
static int g_fream;

void Title_Init(void)
{
	g_Title_TextureID = Texture_SetLoadFile("Asset/Texture/title.png", 1280, 720);

	g_fream = 0;
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

	if (Keyboard_IsTrigger(DIK_R) || g_fream >= 300)
	{
		Scene_SetNextScene(SCENE_REPLAY_ZAKO);
	}

	g_fream++;
}

void Title_Draw(void)
{
	Sprite_Draw(g_Title_TextureID, 0 + SCREEN_WIDTH / 2, 0 + SCREEN_HEIGHT / 2);
}
