#include "Title.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"

static int g_Title_TextureID;

void Title_Init(void)
{
	g_Title_TextureID = Texture_SetLoadFile("Texture/title.png", 1280, 720);
}

void Title_Uninit(void)
{
	
}

void Title_Update(void)
{
	if (Keyboard_IsPress(DIK_O))
	{
		Scene_SetNextScene(SCENE_GAME);
	}
}

void Title_Draw(void)
{
	Sprite_Draw(g_Title_TextureID, 0, 0);
}
