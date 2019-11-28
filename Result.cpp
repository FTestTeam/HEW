#include "Result.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "score.h"

static int g_Result_TextureID;
static int g_ResultScore = 0;
static int g_Score1 = 0, g_Score2 = 0, g_Score3 = 0;

void Result_Init(void)
{
	g_Result_TextureID = Texture_SetLoadFile("Texture/Score.png", 1280, 720);
	// 入れ替えソート
	Result_Sort();
}

void Result_Uninit(void)
{
	
}

void Result_Update(void)
{
	if (Keyboard_IsPress(DIK_SPACE))
	{
		Scene_SetNextScene(SCENE_TITLE);
	}
}

void Result_Draw(void)
{
	Sprite_Draw(g_Result_TextureID, 0, 0);
	//　Score_Draw(スコア,x座標,y座標,桁数,0埋め,左寄せ);
	Score_Draw(g_ResultScore, 652, 180, 7, false, true);
	Score_Draw(g_Score1, 652, 300, 7, false, true);
	Score_Draw(g_Score2, 652, 360, 7, false, true);
	Score_Draw(g_Score3, 652, 420, 7, false, true);
}

void Result_GetScore(int x)
{
	g_ResultScore = x;
}

void Result_Sort(void)
{
	if (g_ResultScore > g_Score1)
	{
		g_Score3 = g_Score2;
		g_Score2 = g_Score1;
		g_Score1 = g_ResultScore;
	}else if (g_ResultScore > g_Score2)
	{
		g_Score3 = g_Score2;
		g_Score2 = g_ResultScore;
	}else if (g_ResultScore > g_Score3)
	{
		g_Score3 = g_ResultScore;
	}
}