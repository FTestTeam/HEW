#include "Result.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "common.h"
#include "score.h"
#include "input.h"
#include "joycon.h"

#define  SCORE_MAX (3)


static int g_Result_TextureID;
static int g_ResultScore = 0;
static int g_Score[SCORE_MAX] = { 0 };

void Result_Init(void)
{
	g_Result_TextureID = Texture_SetLoadFile("Asset/Texture/ranking.png", 1280, 720);
	Result_Sort();
}

void Result_Uninit(void)
{
	g_ResultScore = 0;
}

void Result_Update(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN) || Joycon_IsTrigger(DIJOY_R_A))
	{
		Scene_SetNextScene(SCENE_TITLE);
	}
}

void Result_Draw(void)
{
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 150));
	Sprite_Draw(g_Result_TextureID, 0 + SCREEN_WIDTH / 2, 0 + SCREEN_HEIGHT / 2, 0.75f, 0.75f, 1280.0f / 2, 720.0f / 2);

	Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
	Score_Draw(g_ResultScore, 1000, SCORE_POS_NOW, 7, false, true);
	Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
	Score_Draw(g_Score[0], 1000 , SCORE_POS_1, 7, false, true);
	Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
	Score_Draw(g_Score[1], 1000, SCORE_POS_2, 7, false, true);
	Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
	Score_Draw(g_Score[2], 1000, SCORE_POS_3, 7, false, true);
}

void Result_GetScore(int x)
{
	g_ResultScore = x;
}

void Result_Sort(void)
{
	if (g_ResultScore > g_Score[0])
	{
		g_Score[2] = g_Score[1];
		g_Score[1] = g_Score[0];
		g_Score[0] = g_ResultScore;
	}else if (g_ResultScore > g_Score[1])
	{
		g_Score[2] = g_Score[1];
		g_Score[1] = g_ResultScore;
	}else if (g_ResultScore > g_Score[2])
	{
		g_Score[2] = g_ResultScore;
	}
}