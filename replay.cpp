#include<d3d9.h>
#include"sprite.h"
#include"texture.h"
#include"common.h"

static int g_textureID;

void Replay_Init()
{
	g_textureID = Texture_SetLoadFile("Asset/Texture/replay.png", 1280, 720);
}

void Replay_UnInit()
{

}

void Replay_Update()
{

}

void Replay_Draw()
{
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 100));
	Sprite_Draw(g_textureID, 0 + SCREEN_WIDTH / 2, 0 + SCREEN_HEIGHT / 2);
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}